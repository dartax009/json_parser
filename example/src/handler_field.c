#include "../../json_parser/json_form_check.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

uint8_t print_string (const char *const field_value, size_t size)
{
    printf("%.*s\n", (int)size, field_value);

    return 0;
}

uint8_t print_num (const char *const field_value, size_t size)
{
    printf("%d\n", atoi(field_value));

    return 0;
}

uint8_t print_bool (const char *const field_value, size_t size)
{
    printf("%d\n", (field_value[0] == 't') ? true : false);

    return 0;
}

uint8_t print_null (const char *const field_value, size_t size)
{
    printf("%p\n", NULL);

    return 0;
}

uint8_t any_array_handler (const char *const field_value, size_t size)
{
    printf("В массив входит %lu элементов\n", size);

    return 0;
}

uint8_t any_object_handler (const char *const field_value, size_t size)
{
    printf("В объект входит %lu элементов\n", size);

    return 0;
}

uint8_t print_any_array (const char *const field_value, const size_t size)
{
    static uint8_t i = 0;
    printf("В массиве элемент [%u] %.*s\n", i, (int)size, field_value);
    i++;

    return 0;
}

uint8_t print_any_object (const char *const field_value, const size_t size)
{
    printf("Объект содержит %u\n", (uint8_t)atoi(field_value));

    return 0;
}
