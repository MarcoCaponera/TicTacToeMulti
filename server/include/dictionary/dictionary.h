#include "dynarray.h"

typedef struct dictionary_slot
{
    dynarray_t keys;
    dynarray_t values;
} dictionary_slot_t;

typedef struct dictionary
{
    dictionary_slot_t* slots;
    size_t slots_number;
    size_t value_type_size;
} dictionary_t;

dictionary_t* dict_init(const size_t value_type_size);
int dict_setup(dictionary_t* map, const size_t num_slots);
int dict_add(dictionary_t* map, const char* key, void* value);
int dict_contains_key(dictionary_t* map, const char* key);
void dict_iter_keys(dictionary_t* map, void (*callback)(const char* key));
int dict_remove(dictionary_t * map, const char* key);
void* dict_get_value_by_key(dictionary_t* dict, const char* key);