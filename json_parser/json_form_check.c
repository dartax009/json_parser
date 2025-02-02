#include <stdlib.h>
#include <string.h>

#ifdef __linux__
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#endif

#include "json_form_check.h"

#ifdef PRINT_ERROR_INFO
	#include <stdio.h>
	#define print_error(...)	printf(__VA_ARGS__)
#else
	#define print_error(...)	while(0){}
#endif

#ifdef __linux__
uint8_t init_json_mmap (char *path, file_inf_t *file_inf)
{
    struct stat stat;

	file_inf->fd = open(path, O_RDONLY);

	if (file_inf->fd == -1)
	{
		print_error("Не удалось открыть файл\n");
		return 1;
	}

	if (fstat(file_inf->fd, &stat) != 0)
	{
		print_error("Не удалось получить информацию о файле\n");
		return 2;
	}
	file_inf->file_len = stat.st_size;

	if ( (file_inf->file = (char *)mmap(0, file_inf->file_len, PROT_READ, MAP_SHARED, file_inf->fd, 0)) == MAP_FAILED )
	{
		print_error("Не удалось спроецировать файл в ОЗУ\n");
		return 3;
	}

	return 0;
}

uint8_t deinit_json_mmap (file_inf_t *file_inf)
{
	if (munmap(file_inf->file, file_inf->file_len) < 0)
	{
		print_error("Не удалось освободить спроецированную память\n");
		return 1;
	}

	if (close(file_inf->fd) < 0)
	{
		print_error("Не удалось закрыть файл\n");
		return 2;
	}

	return 0;
}
#endif

static int check_field(const json_map_t *json_map, char *file, jsmntok_t *tok)
{
	int map_count = 0;

	while(json_map[map_count].field_name != NULL || json_map[map_count].field_type != JSMN_UNDEFINED)
	{
		if (json_map[map_count].field_name == NULL)
		{
			if (json_map[map_count].field_type == tok->type)
			{
				break;
			}
		}else
		if (strncmp(file + tok->start, json_map[map_count].field_name, strlen(json_map[map_count].field_name)) == 0)
		{
			break;
		}
		map_count++;
	}

	if (json_map[map_count].field_name == NULL)
	{
		if (json_map[map_count].field_type != JSMN_UNDEFINED)
		{
			return map_count;
		}

		print_error("Встретилось не ожидаемое поле %.*s\n", tok->end - tok->start, file + tok->start);
		print_error("Допустимые поля для текущей связанной подгруппы:\n");

		#ifdef PRINT_ERROR_INFO
		map_count = 0;
		while(json_map[map_count].field_name != NULL)
		{
			print_error("%s\n", json_map[map_count].field_name);
			map_count++;
		}
		#endif

		return -1;
	}

	if (tok->type != JSMN_STRING)
	{
		print_error("Не корректно заполнен json поле %.*s не является строкой\n", tok->end - tok->start, file + tok->start);
		return -1;
	}

	if ( (json_map[map_count].field_type & tok[1].type) != tok[1].type)
	{
		print_error("Не ожидаемый тип поля у %.*s\n", tok->end - tok->start, file + tok->start);
		print_error("Ожидается: %u, указано: %u\n", json_map[map_count].field_type, tok[1].type);
		return -1;
	}

	return map_count;
}

static int work_json_map (const json_map_t *json_map, char *file, jsmntok_t *tok)
{
	int tok_pos = 0;
	int tok_count = 0;
	int map_pos = 0;
	uint8_t ret = 0;

	int size_tok = tok[tok_count].size;
	tok_count++;

	while(tok[tok_count].type != JSMN_UNDEFINED && size_tok != 0)
	{
		map_pos = check_field(json_map, file, &tok[tok_count]);
		if (map_pos < 0)
		{
			return -1;
		}

		if (json_map[map_pos].field_name != NULL)
		{
			tok_count++;
		}

		if (json_map[map_pos].func != NULL)
		{
			ret = json_map[map_pos].func(file + tok[tok_count].start, tok[tok_count].end - tok[tok_count].start);
			if (ret > 0)
			{
				return ret * -1;
			}
		}

		if ( tok[tok_count].type == JSMN_ARRAY || tok[tok_count].type == JSMN_OBJECT)
		{
			tok_pos = work_json_map((json_map[map_pos].json_map != NULL) ? json_map[map_pos].json_map : json_map, file, &tok[tok_count]);
			if (tok_pos < 0)
			{
				return tok_pos;
			}
			tok_count += tok_pos;
		}
		else
		{
			tok_count++;
		}
		size_tok--;
	}

	return tok_count;
}

uint8_t parsing_json (file_inf_t *file_inf, const json_map_t *json_map)
{
	jsmn_parser parser;
	jsmntok_t *tok = NULL;
	int max_tok = 0;
	int ret = 0;

	jsmn_init(&parser);

	max_tok = jsmn_parse(&parser, file_inf->file, file_inf->file_len, NULL, 0);
	if (max_tok < 1)
	{
		print_error("Не удалось подсчитать токены, что-то не то с переданной строкой %d\n", max_tok);
		return 1;
	}

	tok = (jsmntok_t *)malloc(sizeof(jsmntok_t)*max_tok);
	if (tok == NULL)
	{
		print_error("Не удалось выделить память для токенов\n");
		return 1;
	}

	jsmn_init(&parser);
	max_tok = jsmn_parse(&parser, file_inf->file, file_inf->file_len, tok, max_tok);
	if (max_tok < 1)
	{
		print_error("Во второй раз не удалось подсчитать токены, что-то не то с переданной строкой %d\n", max_tok);
		free(tok);
		return 1;
	}

	ret = work_json_map(json_map, file_inf->file, tok);

	free(tok);

	if (ret < 0)
	{
		return ret * -1;
	}

	return 0;
}