#include <stdio.h>

#include "cw_map_json.h"
#include "c_map_json.h"

#define TEST_JSON_PATH  "test.json"

// Проверка и обработка json 
void check_and_work ()
{
    uint8_t ret = 0;
    file_inf_t fl_inf = {0};
    init_json_mmap(TEST_JSON_PATH, &fl_inf);

    if ( (ret = parsing_json(&fl_inf, cw_person)) > 0)
    {
        printf("Возникла ошибка при обработке json %u\n", ret);
    }

    deinit_json_mmap(&fl_inf);
}

// Только проверка на сигнатуру
void only_check ()
{
    uint8_t ret = 0;
    file_inf_t fl_inf = {0};
    init_json_mmap(TEST_JSON_PATH, &fl_inf);

    if ( (ret = parsing_json(&fl_inf, c_person)) > 0)
    {
        printf("Возникла ошибка при обработке json %u\n", ret);
    }
    printf("Все норм\n");
    deinit_json_mmap(&fl_inf);
}

int main ()
{
    check_and_work();
    only_check();

    return 0;
}