#ifndef CC_MAP_JSON_H
#define CC_MAP_JSON_H

#define JSON_FORM_CHECK_HEAD
#include "../../json_parser/json_form_check.h"

static json_map_t cc_addres_map[] =
{
    {"street", NULL, JSMN_STRING, NULL, 1},
    {"city", NULL, JSMN_STRING, NULL, 1},

    END_MAP_JSON
};

static json_map_t cc_addreses_map[] =
{
    {"type", NULL, JSMN_STRING, NULL, 1},
    {"address", NULL, JSMN_OBJECT, cc_addres_map, 1},

    END_MAP_JSON
};

static json_map_t cc_addreses_obj[] =
{
    {NULL, NULL, JSMN_OBJECT, cc_addreses_map, 1},

    END_MAP_JSON
};

static json_map_t cc_phoneN_map[] =
{
    {"type", NULL, JSMN_STRING, NULL, 1},
    {"number", NULL, JSMN_STRING, NULL, 1},

    END_MAP_JSON
};

static json_map_t cc_phoneN_obj[] =
{
    {NULL, NULL, JSMN_OBJECT, cc_phoneN_map, 1},

    END_MAP_JSON
};

static json_map_t cc_name_map[] =
{
    {"first", NULL, JSMN_STRING, NULL, 1},
    {"last", NULL, JSMN_STRING, NULL},

    END_MAP_JSON
};

static json_map_t cc_teams_map[] =
{
    {"name", NULL, JSMN_STRING, NULL},
    {"role", NULL, JSMN_STRING, NULL},

    END_MAP_JSON
};

static json_map_t cc_teams_obj[] =
{
    {NULL, NULL, JSMN_OBJECT, cc_teams_map},

    END_MAP_JSON
};

static json_map_t cc_details_map[] =
{
    {"favoriteSport", NULL, JSMN_STRING, NULL},
    {"teams", NULL, JSMN_ARRAY, cc_teams_obj},

    END_MAP_JSON
};

static json_map_t cc_hobbies_obj[] =
{
    {"type", NULL, JSMN_STRING, NULL},
    {"details", NULL, JSMN_OBJECT, cc_details_map},

    END_MAP_JSON
};

static json_map_t cc_hobbies_map[] =
{
    {NULL, NULL, JSMN_STRING, NULL},
    {NULL, NULL, JSMN_OBJECT, cc_hobbies_obj},

    END_MAP_JSON
};

static json_map_t cc_any_array_map[] =
{
    {NULL, NULL, JSMN_STRING, NULL},

    END_MAP_JSON
};

static json_map_t cc_any_object_map[] =
{
    {"any1", NULL, JSMN_PRIMITIVE, NULL},
    {"any2", NULL, JSMN_PRIMITIVE, NULL},
    {"any3", NULL, JSMN_PRIMITIVE, NULL},

    END_MAP_JSON
};

static json_map_t cc_person_map[] =
{
    {"id", NULL, JSMN_PRIMITIVE, NULL, 1},
    {"name", NULL, JSMN_OBJECT, cc_name_map, 1},
    {"age", NULL, JSMN_PRIMITIVE, NULL, 1},
    {"phoneNumbers", NULL, JSMN_ARRAY, cc_phoneN_obj, 1},
    {"addresses", NULL, JSMN_ARRAY, cc_addreses_obj, 1},
    {"isEmployed", NULL, JSMN_PRIMITIVE, NULL},
    {"any_null", NULL, JSMN_PRIMITIVE, NULL},
    {"hobbies", NULL, JSMN_ARRAY, cc_hobbies_map},

    END_MAP_JSON
};

static json_map_t cc_person[] =
{
    {"person", NULL, JSMN_OBJECT, cc_person_map},

    {"any_array", NULL, JSMN_ARRAY, cc_any_array_map},
    {"any_object", NULL, JSMN_OBJECT, cc_any_object_map},

    END_MAP_JSON
};


#endif
