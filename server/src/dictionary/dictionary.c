#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dictionary.h"

#define BASE_ELEMENTS_PER_SLOT 64

static size_t djb33x_hash(const char* key, const size_t keylen)
{
    size_t hash = 5381;
    for(size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }

    return hash;
}

dictionary_t* dict_init(const size_t value_type_size)
{
    dictionary_t* dict = malloc(sizeof(dictionary_t));
    if(!dict)
    {
        perror("malloc()");
        return NULL;
    }

    dict->value_type_size = value_type_size;
    dict->slots = NULL;
    dict->slots_number = 0;
    return dict;
}

int dict_setup(dictionary_t* dict, const size_t num_slots)
{
    
    if(dict->slots_number == 0)
    {
        dict->slots_number = num_slots;
        dict->slots = malloc(sizeof(dictionary_slot_t) * dict->slots_number);
        memset(dict->slots, 0, sizeof(dictionary_slot_t) * dict->slots_number);
        for(size_t slot_index = 0; slot_index < dict->slots_number; slot_index++)
        {
            dictionary_slot_t* current_slot = &dict->slots[slot_index];
            if(dynarray_init(&current_slot->keys, BASE_ELEMENTS_PER_SLOT, sizeof(char**)))
            {
                printf("could not initialize dictionary keys for slot number: %llu\n", slot_index);
            }
            if(dynarray_init(&current_slot->values, BASE_ELEMENTS_PER_SLOT, dict->value_type_size))
            {
                printf("could not initialize dictionary values for slot number: %llu\n", slot_index);
            }
        }
    }
    else
    {
        dictionary_slot_t* new_slots = malloc(sizeof(dictionary_slot_t) * num_slots);
        memset(new_slots, 0, sizeof(dictionary_slot_t) * num_slots);
        if(!new_slots)
        {
            return -1;
        }

        for(size_t i = 0; i < num_slots; i++)
        {
            if(dynarray_init(&new_slots[i].keys, BASE_ELEMENTS_PER_SLOT, sizeof(char**)))
            {
                printf("dictionary keys initialization failed during rehashing at slot number: %llu", i);
            }

            if(dynarray_init(&new_slots[i].values, BASE_ELEMENTS_PER_SLOT, dict->value_type_size))
            {
                printf("dictionary values initialization failed during rehashing at slot number: %llu", i);
            }
        } 

        for(size_t slot_index = 0; slot_index < dict->slots_number; slot_index++)
        {
            dictionary_slot_t* curr_slot = &dict->slots[slot_index];
            for(size_t item_index = 0; item_index < curr_slot->keys.length; item_index++)
            {
                const char* key = *(char**)dynarray_get_at_index(&curr_slot->keys, item_index);
                const void* value = dynarray_get_at_index(&curr_slot->values, item_index);
                const size_t hash = djb33x_hash(key, strlen(key));
                const size_t new_slot = hash % num_slots;

                dynarray_append(&new_slots[new_slot].keys, &key);
                dynarray_append(&new_slots[new_slot].values, value);
            }
        }

        free(dict->slots);
        dict->slots = new_slots;
        dict->slots_number = num_slots;
    }

    return 0;
}

int dict_add(dictionary_t* map, const char* item, void* value)
{
    if(!dict_contains_key(map, item))
    {
        return 0;
    }
    // calcolo l'hash
    const size_t hash = djb33x_hash(item, strlen(item));
    // calcolo lo slot in cui va collocato il nuovo item
    const size_t slot_number = hash % map->slots_number;

    // // prendo il puntatore allo slot in cui va collocato il nuovo item
    dictionary_slot_t* map_slot = &map->slots[slot_number];

    // vedo quanti item sono già presenti nello slot
    size_t curr_item_number = map->slots[slot_number].keys.length;

    if(curr_item_number > 1)
    {
        if(dict_setup(map, map->slots_number * 2))
        {
            printf("REHASHING failed!\n");
            return -1;
        }

        const size_t new_slot = hash % map->slots_number;
        map_slot = &map->slots[new_slot];
        curr_item_number = map_slot->keys.length;

        if(curr_item_number >= BASE_ELEMENTS_PER_SLOT)
        {
            return -1;
        }
    }

    dynarray_append(&map_slot->keys, &item);
    dynarray_append(&map_slot->values, value);

    return 0;
}

void* dict_get_value_by_key(dictionary_t* map, const char* key)
{
    const size_t hash = djb33x_hash(key, strlen(key));
    const size_t slot = hash % map->slots_number;

    dictionary_slot_t* selected_slot = &map->slots[slot];

    for(size_t i = 0; i < selected_slot->keys.length; i++)
    {
        if(!strcmp(*(char**)dynarray_get_at_index(&selected_slot->keys, i), key))
        {
            return dynarray_get_at_index(&selected_slot->values, i);
        }
    }

    return NULL;
}

int dict_contains_key(dictionary_t* map, const char* item)
{
    const size_t hash = djb33x_hash(item, strlen(item));
    const size_t slot = hash % map->slots_number;

    dictionary_slot_t* selected_slot = &map->slots[slot];

    for(size_t i = 0; i < selected_slot->keys.length; i++)
    {   
        if(!strcmp(*(char**)dynarray_get_at_index(&selected_slot->keys, i), item))
        {
            return 0;
        }
    }

    return -1;
}

void dict_iter_keys(dictionary_t* map, void (*callback)(const char* key))
{
    for(size_t map_index = 0; map_index < map->slots_number; map_index++)
    {
        dictionary_slot_t* current_slot = &map->slots[map_index];
        for(size_t slot_index = 0; slot_index < current_slot->keys.length; slot_index++)
        {
            const char* key = (char*)dynarray_get_at_index(&current_slot->keys, slot_index);
            callback(key);
        }
    }
}


int dict_remove(dictionary_t * map, const char* key)
{
    const size_t hash = djb33x_hash(key, strlen(key));
    const size_t slot = hash % map->slots_number;

    dictionary_slot_t* selected_slot = &map->slots[slot];

    for(size_t i = 0; i < selected_slot->keys.length; i++)
    {
        if(!strcmp(*(char**)dynarray_get_at_index(&selected_slot->keys, i), key))
        {
            dynarray_remove(&selected_slot->keys, i);
            dynarray_remove(&selected_slot->values, i);
            return 0;
        }
    }

    return -1;
}

static void print_key(const char* key)
{
    printf("Hello I am print key for: %s\n", *(char**)key);
}