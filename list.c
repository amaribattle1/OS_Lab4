#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Allocate and initialize a new list
list_t* list_alloc() {
    list_t *list = malloc(sizeof(list_t));
    if (list != NULL) {
        list->head = NULL;
    }
    return list;
}

// Free all nodes in the list and the list itself
void list_free(list_t *list) {
    if (list == NULL) return;
    node_t *current = list->head;
    node_t *temp;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

// Get the length of the list
int list_length(list_t *list) {
    if (list == NULL) {
        printf("Warning: Attempted to get length of an uninitialized list.\n");
        return 0;
    }
    int count = 0;
    node_t *current = list->head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// Add an element to the front of the list
void list_add_to_front(list_t *list, elem value) {
    if (list == NULL) {
        printf("Error: Cannot add to an uninitialized list.\n");
        return;
    }
    node_t *new_node = malloc(sizeof(node_t));
    if (new_node == NULL) {
        printf("Memory allocation unsuccessful.\n");
        return;
    }
    new_node->value = value;
    new_node->next = list->head;
    list->head = new_node;
}

// Add an element to the back of the list
void list_add_to_back(list_t *list, elem value) {
    if (list == NULL) {
        printf("Error: Cannot add to an uninitialized list.\n");
        return;
    }
    node_t *new_node = malloc(sizeof(node_t));
    if (new_node == NULL) {
        printf("Memory allocation unsuccessful.\n");
        return;
    }
    new_node->value = value;
    new_node->next = NULL;
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        node_t *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

// Additional methods updated similarly...
