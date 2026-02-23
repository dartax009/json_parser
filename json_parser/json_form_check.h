#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <stdint.h>

#define JSMN_HEADER
#include "jsmn/jsmn.h"

#define END_MAP_JSON    {NULL, NULL, JSMN_UNDEFINED, NULL}      ///> Заврешение структуры json_map_t

/**
 * @brief Функция обработки текущее поле
 * 
 * @param fild  [in] указатель на начало поля, данные которого необходимо сохранить
 * @param size  [in] размер строки данных. Если поле является объектом ({}) или массивом ([]), то будет передано кол-во входящих элементов
 * @return uint8_t - код завершения работы
 * [0] - Успешное заверешние работы
 * [>0] - Пользовательский код ошибки
 */
typedef uint8_t (*handler_json)(const char * const field_value, const size_t size);

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

/**
 * @brief Структуа одного поля json
 * 
 */
struct s_json_map
{
    const char * const field_name;              ///< Имя поля "fild_name" : fild_value
    const handler_json func;                    ///< Функция сохранения значения поля fild_value
    const jsmntype_t field_type;                ///< Тип значения поля (используется для проверки соответствия с ожидаемой схемой)

    struct s_json_map *json_map;          ///< Вложенные структуры для массивов или объектов (массив->[], объект->{})
    const uint32_t min_count;                   ///< Обязатлеьное кол-во появлений данного поля при обработке (если 0, то данного поля может не быть в json)
    uint32_t count;                             ///< Счетчик кол-во вхождений. Всегда должен инициализироваться 0
};
typedef struct s_json_map json_map_t;           /// Структура одного поля json

/**
 * @brief Разбирает json в соответствии с переданной json_map
 * 
 * @param file_inf  [in] информация о ранее открытом файле
 * @param json_map  [in] карта json для разбора
 * @param check_required [in] использовать ли проверку на кол-во вхождений элемента (0 - не использовать/1 - использовать) 
 * @return uint8_t - код завершения работы
 * [0] - Успешное завершение работы функции
 * [>0] - Ошибка
 */
uint8_t parsing_json (const file_inf_t * const file_inf, json_map_t *const json_map, const uint8_t check_required);

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
uint8_t init_json_mmap (const char * const path, file_inf_t *file_inf);

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