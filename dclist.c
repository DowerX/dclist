#include "dclist.h"
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

DCL_element* DCL_create_element(
    void* data,
    size_t size,
    struct DCL_element* before,
    struct DCL_element* after)
{
    DCL_element* this = (DCL_element*) malloc(sizeof(DCL_element));
    this->data = (void*) malloc(size);
    memcpy(this->data, data, size);
    this->before = before;
    this->after = after;
    if (before != NULL)
        before->after = this;
    if (after != NULL)
        after->before = this;
    return this;
}

DCL_element* DCL_delete_element(DCL_element* this){
    if (this == NULL) return NULL;
    if (this->before != NULL)
        this->before->after = this->after;
    if (this->after != NULL)
        this->after->before = this->before;
    DCL_element* next = this->after;
    free(this->data);
    free(this);
    return next;
}

DCL_element* DCL_next_element(DCL_element* this){
    if (this==NULL) return NULL;
    return this->after;
}

DCL_element* DCL_prev_element(DCL_element* this){
    if (this==NULL) return NULL;
    return this->before;
}

void DCL_delete_list(DCL_element* this){
    while (this->before != NULL){
        this = this->before;
    }

    while((this=DCL_delete_element(this)) != NULL){};
}

DCL_element* DCL_first_element(DCL_element* this){
    if (this==NULL) return NULL;
    while (this->before != NULL){
        this = DCL_prev_element(this);
    }
    return this;
}

DCL_element* DCL_last_element(DCL_element* this){
    while (this->after != NULL){
        this = DCL_next_element(this);
    }
    return this;
}

unsigned int DCL_list_size(DCL_element* this){
    if (this==NULL) return 0;
    this = DCL_first_element(this);
    unsigned int i = 1;
    while ((this=DCL_next_element(this))!=NULL) i++;
    return i;
}

DCL_element* DCL_index_element(DCL_element* this, int n){
    if (this==NULL) return NULL;
    this = DCL_first_element(this);
    unsigned int size = DCL_list_size(this);
    if (n<0) n+=size;
    n%=size;
    for (int i = 0; i<n; i++){
        this = DCL_next_element(this);
    }
    return this;
}