#include <stdlib.h>
#include <stdio.h>

#define PP_LIST_IMPLEMENTATION
#include "pp_list.h"

int main() {
    char* words[5] = {"We", "believe", "in", "nah-sing", "Lebowski!"};

    pp_list_t* list = pp_list_create(words[0]);
    pp_list_t* tail = list;
    for (int i = 1; i < 5; i++) {
        tail = pp_list_append(tail, words[i]);
    }

    pp_list_t* iter = list;
    while (iter != NULL) {
        printf("%s\n", (char*)(iter->data));
        iter = iter->next;
    }

    bool should_free_data = false;
    pp_list_deep_free(&list, should_free_data);

    return EXIT_SUCCESS;
}
