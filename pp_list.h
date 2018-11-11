/*

pp_list.h: a trivial linked-list implementation.
See https://github.com/pepaslabs/pp_c

Copyright (c) 2018 Jason Pepas
Released under the terms of the MIT License.
See https://opensource.org/licenses/MIT

This is a single-file C library.
See https://github.com/nothings/stb/blob/master/docs/stb_howto.txt

How to use this file:

- From only one file in your codebase, include this as an implementation:
#define PP_LIST_IMPLEMENTATION
#include "pp_list.h"

- From as many files as needed, include this as a header: 
#include "pp_list.h"

History:
- v0.1 (2018/11/11): intial release

*/


// MARK: - Header

#ifndef PP_LIST_HEADER
#define PP_LIST_HEADER

#include <stdbool.h>

struct _pp_list_t {
    void* data;
    struct _pp_list_t* next;
};
typedef struct _pp_list_t pp_list_t;

// Allocate and initialize a list node.
pp_list_t* pp_list_create(void* data);

// Free a list node (return its memory to the operating system).
void pp_list_free(pp_list_t** ptr, bool should_free_data);
// Free an entire list.
void pp_list_deep_free(pp_list_t** ptr, bool should_free_data);

// Append 'data' to the list node.
// Note: this function does not walk to the end of the list.
// Returns the newly created list node.
pp_list_t* pp_list_append(pp_list_t* tail, void* data);

#endif // PP_LIST_HEADER


// MARK: - Implementation

#ifdef PP_LIST_IMPLEMENTATION

#include <assert.h>

pp_list_t* pp_list_create(void* data) {
    pp_list_t* list = (pp_list_t*)malloc(sizeof(pp_list_t));
    list->data = data;
    list->next = NULL;
    return list;
}

void pp_list_free(pp_list_t** ptr, bool should_free_data) {
    assert(ptr != NULL && *ptr != NULL);
    if (should_free_data) {
        free((*ptr)->data);
        (*ptr)->data = NULL;
    }
    free(*ptr);
    *ptr = NULL;
}

void pp_list_deep_free(pp_list_t** ptr, bool should_free_data) {
    assert(ptr != NULL && *ptr != NULL);
    pp_list_t* next = (*ptr)->next;
    while (next != NULL) {
        next = next->next;
        pp_list_free(&next, should_free_data);
    }
    *ptr = NULL;
}

pp_list_t* pp_list_append(pp_list_t* tail, void* data) {
    assert(tail != NULL);
    pp_list_t* new_tail = pp_list_create(data);
    tail->next = new_tail;
    return new_tail;
}

#endif // PP_LIST_IMPLEMENTATION
