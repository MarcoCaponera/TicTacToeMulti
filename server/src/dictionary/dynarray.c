#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynarray.h"

// EXERCISE 1 - use realloc - DONE
// EXERCISE 2 - type independent - DONE

static size_t malloc_counter = 0;
static size_t malloc_total_allocations = 0;

static void* dynarray_malloc(const size_t length)
{
    void* data = malloc(length);
    if(!data)
    {
        return NULL;    
    }
    malloc_counter++;
    malloc_total_allocations += length;
    return data;
}

static void* dynarray_realloc(void* buffer, const size_t prev_length, const size_t length)
{
    void* data = realloc(buffer, length);
    if(!data)
    {
        return NULL;
    }
    malloc_counter++;
    malloc_total_allocations += length - prev_length;
    return data;
}

void dynarray_free(void* data, const size_t amount)
{
    malloc_total_allocations -= amount;
    free(data);
}

int dynarray_append(dynarray_t* arr, const void* new_item)
{
    return dynarray_insert(arr, arr->length, new_item);
}

int dynarray_init(dynarray_t* arr, const size_t capacity, const size_t type_size)
{
    arr->length = 0;
    arr->type_size = type_size;
    arr->capacity = 0;
    if(dynarray_set_capacity(arr, capacity))
    {
        return -1;
    }

    return 0;
}

int dynarray_insert(dynarray_t* arr, const size_t index, const void* new_item)
{
    if(!new_item)
    {
        return -1;
    }

    if(arr->length + 1 > arr->capacity)
    {
        if(dynarray_reserve(arr, 1))
        {
            return -1;
        }
    }

    char* char_arr = (char*)arr->data;

    if(index < arr->length)
    {
        memmove(&char_arr[(index  + 1) * arr->type_size], &char_arr[index * arr->type_size], arr->type_size * (arr->length - index));
    }
    
    memcpy(&char_arr[index * arr->type_size], new_item, arr->type_size);
    arr->length++;

    return 0;
}

int dynarray_reserve(dynarray_t* arr, const size_t elements)
{
    return dynarray_set_capacity(arr, arr->capacity + elements);
}

int dynarray_remove(dynarray_t* arr, const size_t index)
{
    if(index >= arr->length)
    {
        return -1;
    }

    if(arr->length > 0 && index == arr->length - 1)
    {
        arr->length--;
        return 0;
    }

    memmove(&arr->data[index * arr->type_size], &arr->data[(index + 1) * arr->type_size], arr->type_size * (arr->length - index));
    arr->length--;

    return 0;
}

int dynarray_set_capacity(dynarray_t* arr, const size_t new_capacity)
{
    if(new_capacity < arr->length)
    {
        return -1;
    }

    if(new_capacity == 0)
    {
        arr->data = NULL;
        arr->capacity = 0;
        return 0;
    }

    // void* new_data = dynarray_malloc(arr->typesize * new_capacity);
    // if(!new_data)
    // {
    //     perror("malloc()");
    //     return -1;
    // }

    // if(arr->capacity > 0)
    // {
    //     memcpy(new_data, arr->data, arr->typesize * arr->length);
    //     dynarray_free(arr->data, arr->typesize * arr->length);
    // }
    void* new_data = NULL;
    if(arr->capacity > 0)
    {
        new_data = dynarray_realloc(arr->data, arr->type_size * arr->capacity, arr->type_size * new_capacity);
        if(!new_data)
        {
            perror("realloc()");
            return -1;
        }
    }
    else
    {
        new_data = dynarray_malloc(arr->type_size * new_capacity);
        if(!new_data)
        {
            perror("malloc()");
            return -1;
        }
    }


    arr->data = new_data;
    arr->capacity = new_capacity;
    return 0;
}

int dynarray_empty(dynarray_t* arr)
{
    arr->length = 0;
    return 0;
}

void* dynarray_get_at_index(dynarray_t* arr, size_t index)
{
    if(index >= arr->length)
    {
        printf("index out of range");
        return NULL;
    }
    char* new_data = (char*)arr->data;
    return &new_data[index * arr->type_size];
}