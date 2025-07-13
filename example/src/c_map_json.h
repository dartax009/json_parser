#ifndef C_MAP_JSON_H
#define C_MAP_JSON_H

#define JSON_FORM_CHECK_HEAD
#include "../../json_parser/json_form_check.h"

static const json_map_t c_addres_map[] =
{
    {"street", NULL, JSMN_STRING, NULL},
    {"city", NULL, JSMN_STRING, NULL},

    END_MAP_JSON
};

static const json_map_t c_addreses_map[] =
{
    {"type", NULL, JSMN_STRING, NULL},
    {"address", NULL, JSMN_OBJECT, c_addres_map},

    END_MAP_JSON
};

static const json_map_t c_addreses_obj[] =
{
    {NULL, NULL, JSMN_OBJECT, c_addreses_map},

    END_MAP_JSON
};

static const json_map_t c_phoneN_map[] =
{
    {"type", NULL, JSMN_STRING, NULL},
    {"number", NULL, JSMN_STRING, NULL},

    END_MAP_JSON
};

static const json_map_t c_phoneN_obj[] =
{
    {NULL, NULL, JSMN_OBJECT, c_phoneN_map},

    END_MAP_JSON
};

static const json_map_t c_name_map[] =
{
    {"first", NULL, JSMN_STRING, NULL},
    {"last", NULL, JSMN_STRING, NULL},

    END_MAP_JSON
};

static const json_map_t c_teams_map[] =
{
    {"name", NULL, JSMN_STRING, NULL},
    {"role", NULL, JSMN_STRING, NULL},

    END_MAP_JSON
};

static const json_map_t c_teams_obj[] =
{
    {NULL, NULL, JSMN_OBJECT, c_teams_map},

    END_MAP_JSON
};

static const json_map_t c_details_map[] =
{
    {"favoriteSport", NULL, JSMN_STRING, NULL},
    {"teams", NULL, JSMN_ARRAY, c_teams_obj},

    END_MAP_JSON
};

static const json_map_t c_hobbies_obj[] =
{
    {"type", NULL, JSMN_STRING, NULL},
    {"details", NULL, JSMN_OBJECT, c_details_map},

    END_MAP_JSON
};

static const json_map_t c_hobbies_map[] =
{
    {NULL, NULL, JSMN_STRING, NULL},
    {NULL, NULL, JSMN_OBJECT, c_hobbies_obj},

    END_MAP_JSON
};

static const json_map_t c_any_array_map[] =
{
    {NULL, NULL, JSMN_STRING, NULL},

    END_MAP_JSON
};

static const json_map_t c_any_object_map[] =
{
    {"any1", NULL, JSMN_PRIMITIVE, NULL},
    {"any2", NULL, JSMN_PRIMITIVE, NULL},
    {"any3", NULL, JSMN_PRIMITIVE, NULL},

    END_MAP_JSON
};

static const json_map_t c_person_map[] =
{
    {"id", NULL, JSMN_PRIMITIVE, NULL},
    {"name", NULL, JSMN_OBJECT, c_name_map},
    {"age", NULL, JSMN_PRIMITIVE, NULL},
    {"phoneNumbers", NULL, JSMN_ARRAY, c_phoneN_obj},
    {"addresses", NULL, JSMN_ARRAY, c_addreses_obj},
    {"isEmployed", NULL, JSMN_PRIMITIVE, NULL},
    {"any_null", NULL, JSMN_PRIMITIVE, NULL},
    {"hobbies", NULL, JSMN_ARRAY, c_hobbies_map},

    END_MAP_JSON
};

static const json_map_t c_person[] =
{
    {"person", NULL, JSMN_OBJECT, c_person_map},

    {"any_array", NULL, JSMN_ARRAY, c_any_array_map},
    {"any_object", NULL, JSMN_OBJECT, c_any_object_map},

    END_MAP_JSON
};


#endif
