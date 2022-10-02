#include <stddef.h>

typedef struct DCL_element DCL_element;

typedef struct DCL_element {
    struct DCL_element* before;
    struct DCL_element* after;
    void* data;
} DCL_element;

DCL_element* DCL_create_element(void*,size_t,DCL_element*,DCL_element*);
DCL_element* DCL_delete_element(DCL_element*);

DCL_element* DCL_next_element(DCL_element*);
DCL_element* DCL_prev_element(DCL_element*);
DCL_element* DCL_first_element(DCL_element*);
DCL_element* DCL_last_element(DCL_element*);

void DCL_delete_list(DCL_element*);
unsigned int DCL_list_size(DCL_element*);
DCL_element* DCL_index_element(DCL_element*, int);