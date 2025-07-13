#include "../../json_parser/json_form_check.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

uint8_t print_string (const char *fild_value, size_t size)
{
    printf("%.*s\n", (int)size, fild_value);

    return 0;
}

uint8_t print_num (const char *fild_value, size_t size)
{
    printf("%d\n", atoi(fild_value));

    return 0;
}

uint8_t print_bool (const char *fild_value, size_t size)
{
    printf("%d\n", (fild_value[0] == 't') ? true : false);

    return 0;
}

uint8_t print_null (const char *fild_value, size_t size)
{
    printf("%p\n", NULL);

    return 0;
}

uint8_t any_array_handler (const char *fild_value, size_t size)
{
    printf("В массив входит %lu элементов\n", size);

    return 0;
}

uint8_t any_object_handler (const char *fild_value, size_t size)
{
    printf("В объект входит %lu элементов\n", size);

    return 0;
}