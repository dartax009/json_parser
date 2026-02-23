#include <stdio.h>

#include "cw_map_json.h"
#include "c_map_json.h"
#include "cc_map_json.h"

#define CLEAR_TEST_JSON_PATH            "clear_test.json"
#define NO_COUT_JSON_PATH               "no_cout.json"
#define NO_REQUIRED_FILD_JSON_PATH      "no_required_fild.json"

// Проверка и обработка json 
void check_and_work (char *path)
{
    uint8_t ret = 0;
    file_inf_t fl_inf = {0};
    init_json_mmap(path, &fl_inf);

    if ( (ret = parsing_json(&fl_inf, cw_person, 0)) > 0)
    {
        printf("\033[31mВозникла ошибка при обработке json %u\033[0m\n", ret);
    }
    else
    {
        printf("\033[32mОбработка проведена. Все норм\033[0m\n");
    }
    deinit_json_mmap(&fl_inf);
}

// Только проверка на сигнатуру
void only_check (char *path)
{
    uint8_t ret = 0;
    file_inf_t fl_inf = {0};
    init_json_mmap(path, &fl_inf);

    if ( (ret = parsing_json(&fl_inf, c_person, 0)) > 0)
    {
        printf("\033[31mВозникла ошибка при обработке json %u\033[0m\n", ret);
    }
    else
    {
        printf("\033[32mСигнатура проверена. Все норм\033[0m\n");
    }
    deinit_json_mmap(&fl_inf);
}

// На обязательность вхождения
void required_check (char *path)
{
    uint8_t ret = 0;
    file_inf_t fl_inf = {0};
    init_json_mmap(path, &fl_inf);

    if ( (ret = parsing_json(&fl_inf, cc_person, 1)) > 0)
    {
        printf("\033[31mВозникла ошибка при обработке json %u\033[0m\n", ret);
    }
    else
    {
        printf("\033[32mОбязатлеьное вхожение проверено. Все норм\033[0m\n");
    }
    deinit_json_mmap(&fl_inf);
}

int main ()
{
    // Проверка чистого json
    check_and_work(CLEAR_TEST_JSON_PATH);
    only_check(CLEAR_TEST_JSON_PATH);
    required_check(CLEAR_TEST_JSON_PATH);

    // Проверка json с левым (не ожидаемым) полем error_fild
    only_check(NO_REQUIRED_FILD_JSON_PATH);

    // Проверка json c отсутствующем полем city
    required_check(NO_COUT_JSON_PATH);

    return 0;
}