#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the functions

list_t* list_alloc() {
    list_t* list = (list_t*)malloc(sizeof(list_t));
    list->head = NULL;
    return list;
}

void list_free(list_t* list) {
    node_t* current = list->head;
    node_t* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

void list_add_to_front(list_t* list, int value) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->data = value;
    new_node->next = list->head;
    list->head = new_node;
}

void list_add_to_back(list_t* list, int value) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->data = value;
    new_node->next = NULL;
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        node_t* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void list_add_at_index(list_t* list, int index, int value) {
    if (index == 0) {
        list_add_to_front(list, value);
        return;
    }
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->data = value;
    node_t* current = list->head;
    for (int i = 0; i < index - 1; i++) {
        if (current == NULL) return;  // Index out of bounds
        current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
}

int list_remove_from_front(list_t* list) {
    if (list->head == NULL) return -1;
    node_t* temp = list->head;
    int removed_data = temp->data;
    list->head = list->head->next;
    free(temp);
    return removed_data;
}

int list_remove_from_back(list_t* list) {
    if (list->head == NULL) return -1;
    if (list->head->next == NULL) {
        int removed_data = list->head->data;
        free(list->head);
        list->head = NULL;
        return removed_data;
    }
    node_t* current = list->head;
    while (current->next->next != NULL) {
        current = current->next;
    }
    int removed_data = current->next->data;
    free(current->next);
    current->next = NULL;
    return removed_data;
}

int list_remove_at_index(list_t* list, int index) {
    if (index == 0) {
        return list_remove_from_front(list);
    }
    node_t* current = list->head;
    for (int i = 0; i < index - 1; i++) {
        if (current == NULL || current->next == NULL) return -1;
        current = current->next;
    }
    node_t* temp = current->next;
    int removed_data = temp->data;
    current->next = temp->next;
    free(temp);
    return removed_data;
}

int list_get_elem_at(list_t* list, int index) {
    node_t* current = list->head;
    for (int i = 0; i < index; i++) {
        if (current == NULL) return -1;
        current = current->next;
    }
    return current->data;
}

int list_length(list_t* list) {
    int length = 0;
    node_t* current = list->head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}

char* listToString(list_t* list) {
    static char buffer[1024];
    buffer[0] = '\0';
    node_t* current = list->head;
    while (current != NULL) {
        char temp[16];
        sprintf(temp, "%d -> ", current->data);
        strcat(buffer, temp);
        current = current->next;
    }
    strcat(buffer, "NULL");
    return buffer;
}
