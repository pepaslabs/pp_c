#include <stdlib.h>

#define PP_TREE_IMPLEMENTATION
#include "../pp_tree.h"

int main() {

    char* left = "1";
    char* op = "+";
    char* right = "2";

    pp_tree_t* tree = pp_tree_create(op);
    tree->left = pp_tree_create(left);
    tree->right = pp_tree_create(right);

    bool should_free_data = false;
    pp_tree_deep_free(&tree, should_free_data);

    return EXIT_SUCCESS;
}
