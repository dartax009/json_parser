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