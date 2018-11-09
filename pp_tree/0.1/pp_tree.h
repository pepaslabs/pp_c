/*

pp_tree.h: a trivial binary tree implementation.
See https://github.com/pepaslabs/pp-c

Copyright (c) 2018 Jason Pepas
Released under the terms of the MIT License.
See https://opensource.org/licenses/MIT

This is a single-file C library.
See https://github.com/nothings/stb/blob/master/docs/stb_howto.txt

How to use this file:

- From only one file in your codebase, include this as an implementation:
#define PP_TREE_IMPLEMENTATION
#include "pp_tree.h"

- From as many files as needed, include this as a header: 
#include "pp_tree.h"

History:
- v0.1 (2018/11/9): intial release

*/


// MARK: - Header

#ifndef PP_TREE_HEADER
#define PP_TREE_HEADER

#include <stdbool.h>

struct _pp_tree_t {
    void* data;
    struct _pp_tree_t* left;
    struct _pp_tree_t* right;
};
typedef struct _pp_tree_t pp_tree_t;

// Malloc and initialize a tree node.
pp_tree_t* pp_tree_create(void* data);

// Free a single tree node.
// This function will nil-out the tree pointer reference passed in.
// 'should_free_data' controls whether 'data' is also freed.
void pp_tree_free(pp_tree_t** tree, bool should_free_data);

// Similar to 'pp_tree_free', but recursively frees the entire subtree.
void pp_tree_deep_free(pp_tree_t** tree, bool should_free_data);

#endif // PP_TREE_HEADER


// MARK: - Implementation

#ifdef PP_TREE_IMPLEMENTATION

// #include <stdlib.h> // for NULL, EXIT_SUCCESS
#include <assert.h>

typedef unsigned int uint;

pp_tree_t* pp_tree_create(void* data) {
    pp_tree_t* t = (pp_tree_t*)malloc(sizeof(pp_tree_t));
    t->data = data;
    t->left = NULL;
    t->right = NULL;
    return t;
}

void pp_tree_free(pp_tree_t** tree, bool should_free_data) {
    assert(tree != NULL && *tree != NULL);
    pp_tree_t* t = *tree;
    if (should_free_data && t->data != NULL) {
        free(t->data);
    }
    t->data = NULL;
    free(t);
    *tree = NULL;
}

void pp_tree_deep_free(pp_tree_t** tree, bool should_free_data) {
    assert(tree != NULL && *tree != NULL);
    pp_tree_t* t = *tree;
    if (t->left != NULL) {
        pp_tree_deep_free(&(t->left), should_free_data);
    }
    if (t->right != NULL) {
        pp_tree_deep_free(&(t->right), should_free_data);
    }
    pp_tree_free(tree, should_free_data);
}

#endif // PP_TREE_IMPLEMENTATION
