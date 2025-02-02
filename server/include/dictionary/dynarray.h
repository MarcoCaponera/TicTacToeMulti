typedef struct dynarray_t
{
    void* data; // array di puntatori a void
    size_t length; 
    size_t capacity;
    size_t type_size;
} dynarray_t;


int dynarray_set_capacity(dynarray_t* arr, const size_t new_capacity);
int dynarray_reserve(dynarray_t* arr, const size_t elements);
int dynarray_insert(dynarray_t* arr, const size_t index, const void* new_item);
void dynarray_free(void* data, const size_t amount);
int dynarray_append(dynarray_t* arr, const void* new_item);
int dynarray_init(dynarray_t* arr, const size_t capacity, const size_t type_size);
int dynarray_insert(dynarray_t* arr, const size_t index, const void* new_item);
int dynarray_reserve(dynarray_t* arr, const size_t elements);
int dynarray_remove(dynarray_t* arr, const size_t index);
int dynarray_set_capacity(dynarray_t* arr, const size_t new_capacity);
int dynarray_empty(dynarray_t* arr);
void* dynarray_get_at_index(dynarray_t* arr, size_t index);
