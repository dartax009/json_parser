#ifndef CW_MAP_JSON_H
#define CW_MAP_JSON_H

#define JSON_FORM_CHECK_HEAD
#include "../../json_parser/json_form_check.h"

uint8_t print_string (const char *fild_value, size_t size);
uint8_t print_num (const char *fild_value, size_t size);
uint8_t print_bool (const char *fild_value, size_t size);
uint8_t print_null (const char *fild_value, size_t size);
uint8_t any_array_handler (const char *fild_value, size_t size);
uint8_t any_object_handler (const char *fild_value, size_t size);


static const json_map_t cw_addres_map[] =
{
    {"street", print_string, JSMN_STRING, NULL},
    {"city", print_string, JSMN_STRING, NULL},

    END_MAP_JSON
};

static const json_map_t cw_addreses_map[] =
{
    {"type", print_string, JSMN_STRING, NULL},
    {"address", NULL, JSMN_OBJECT, cw_addres_map},

    END_MAP_JSON
};

static const json_map_t cw_addreses_obj[] =
{
    {NULL, NULL, JSMN_OBJECT, cw_addreses_map},

    END_MAP_JSON
};

static const json_map_t cw_phoneN_map[] =
{
    {"type", print_string, JSMN_STRING, NULL},
    {"number", print_string, JSMN_STRING, NULL},

    END_MAP_JSON
};

static const json_map_t cw_phoneN_obj[] =
{
    {NULL, NULL, JSMN_OBJECT, cw_phoneN_map},

    END_MAP_JSON
};

static const json_map_t cw_name_map[] =
{
    {"first", print_string, JSMN_STRING, NULL},
    {"last", print_string, JSMN_STRING, NULL},

    END_MAP_JSON
};

static const json_map_t cw_teams_map[] =
{
    {"name", print_string, JSMN_STRING, NULL},
    {"role", print_string, JSMN_STRING, NULL},

    END_MAP_JSON
};

static const json_map_t cw_teams_obj[] =
{
    {NULL, NULL, JSMN_OBJECT, cw_teams_map},

    END_MAP_JSON
};

static const json_map_t cw_details_map[] =
{
    {"favoriteSport", print_string, JSMN_STRING, NULL},
    {"teams", NULL, JSMN_ARRAY, cw_teams_obj},

    END_MAP_JSON
};

static const json_map_t cw_hobbies_obj[] =
{
    {"type", print_string, JSMN_STRING, NULL},
    {"details", NULL, JSMN_OBJECT, cw_details_map},

    END_MAP_JSON
};

static const json_map_t cw_hobbies_map[] =
{
    {NULL, print_string, JSMN_STRING, NULL},
    {NULL, NULL, JSMN_OBJECT, cw_hobbies_obj},

    END_MAP_JSON
};

static const json_map_t cw_any_array_map[] =
{
    {NULL, NULL, JSMN_STRING, NULL},

    END_MAP_JSON
};

static const json_map_t cw_any_object_map[] =
{
    {"any1", NULL, JSMN_PRIMITIVE, NULL},
    {"any2", NULL, JSMN_PRIMITIVE, NULL},
    {"any3", NULL, JSMN_PRIMITIVE, NULL},

    END_MAP_JSON
};

static const json_map_t cw_person_map[] =
{
    {"id", print_num, JSMN_PRIMITIVE, NULL},
    {"name", NULL, JSMN_OBJECT, cw_name_map},
    {"age", print_num, JSMN_PRIMITIVE, NULL},
    {"phoneNumbers", NULL, JSMN_ARRAY, cw_phoneN_obj},
    {"addresses", NULL, JSMN_ARRAY, cw_addreses_obj},
    {"isEmployed", print_bool, JSMN_PRIMITIVE, NULL},
    {"any_null", print_null, JSMN_PRIMITIVE, NULL},
    {"hobbies", NULL, JSMN_ARRAY, cw_hobbies_map},

    END_MAP_JSON
};

static const json_map_t cw_person[] =
{
    {"person", NULL, JSMN_OBJECT, cw_person_map},

    {"any_array", any_array_handler, JSMN_ARRAY, cw_any_array_map},
    {"any_object", any_object_handler, JSMN_OBJECT, cw_any_object_map},

    END_MAP_JSON
};


#endif
