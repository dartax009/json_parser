#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <stdint.h>

#define JSMN_HEADER
#include "jsmn/jsmn.h"

#define END_MAP_JSON    {NULL, NULL, JSMN_UNDEFINED, NULL}

/**
 * @brief Функция обработки текущее поле
 * 
 * @param fild  [in] указатель на начало поля, данные которого необходимо сохранить
 * @param size  [in] размер строки данных
 * @return uint8_t - код завершения работы
 * [0] - Успешное заверешние работы
 * [>0] - Пользовательский код ошибки
 */
typedef uint8_t (*handler_json)(const char *fild_value, size_t size);

/**
 * @brief Структура для хранения информации открытого файла
 * 
 */
typedef struct s_file_inf
{
    int fd;             ///< Файловый дискриптор (если json в файле)
    size_t file_len;    ///< Длинна открытого файла (или длинна строки json)
    char *file;         ///< Указатель на память в ОЗУ json
}file_inf_t;

struct s_json_map
{
    const char *field_name;                 ///< Имя поля "fild_name" : fild_value
    handler_json func;                      ///< Функция сохранения значения поля fild_value
    jsmntype_t field_type;                  ///< Тип значения поля (используется для проверки соответствия с ожидаемой схемой)

    const struct s_json_map *json_map;      ///< Вложенные структуры для массивов или объектов (массив->[], объект->{})
};
typedef struct s_json_map json_map_t;

/**
 * @brief Разбирает json в соответствии с переданной json_map
 * 
 * @param file_inf  [in] информация о ранее открытом файле
 * @param json_map  [in] карта json для разбора
 * @return uint8_t - код завершения работы
 * [0] - Успешное завершение работы функции
 * [>0] - Ошибка
 */
uint8_t parsing_json (file_inf_t *file_inf, const json_map_t *json_map);

#ifdef __linux__
/**
 * @brief Открыть файл json и спроецировать его в ОЗУ для дальнейшей работы
 * 
 * @param path      [in]    путь до файла
 * @param file_inf  [out]   информация об открытом файле
 * @return uint8_t - код завершения работы
 * [0] - Успешное завершение работы функции
 * [1] - Ошибка. Не удалось открыть файл
 * [2] - Ошибка. Не удалось получить информацию о размере файла
 * [3] - Ошибка. Не одудлось спроецировать файл в ОЗУ
 */
uint8_t init_json_mmap (char *path, file_inf_t *file_inf);

/**
 * @brief Закрыть файл json и удалить его проекцию в ОЗУ
 * 
 * @param file_inf [in] инфорация о ранее открытом файле
 * @return uint8_t - код завершения работы
 * [0] - Успешное завершение работы функции
 * [1] - Ошибка. Не удалось удалить проекцию файла из ОЗУ
 * [2] - Ошибка. Не удалось закрыть файл
 */
uint8_t deinit_json_mmap (file_inf_t *file_inf);
#endif

#endif