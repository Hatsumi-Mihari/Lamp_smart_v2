#include "List.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <esp_log.h>
#include <stdbool.h>
#define LIST_RESERVE_CAPACITY 4

void list_init(List *list, size_t element_size, bool type_list)
{
    list->data = NULL;
    list->size = 0;
    list->element_size = element_size;
    list->capacity = 0;
    list->dynamic_list = type_list;
}

void list_push(List *list, void *element)
{
    if (list->size >= list->capacity)
    {
        size_t new_capacity = list->capacity == 0 ? 4 : list->capacity + LIST_RESERVE_CAPACITY;
        void *new_data = realloc(list->data, new_capacity * list->element_size);
        if (!new_data) {
            ESP_LOGE("INVELID DATA", "LIST");
            return;
        }
        list->data = new_data;
        list->capacity = new_capacity;
    }
    void *dest = (char *)list->data + (list->size * list->element_size);
    memcpy(dest, element, list->element_size);
    list->size++;
}

void *list_get(List *list, uint16_t index)
{
    if (index >= list->size)
        return NULL;
    return (char*)list->data + (index * list->element_size);
}

void list_update(List *list, uint16_t index, void* elem){
    void* elem_geted_by_index = list_get(list, index);
    elem_geted_by_index = elem;
}

void list_remove(List *list, uint16_t index)
{
    if (index >= list->size)
        return;
    void *target = (char *)list->data + index * list->element_size;
    void *next = (char *)target + list->element_size;
    size_t bytes_to_move = (list->size - index - 1) * list->element_size;
    memmove(target, next, bytes_to_move);
    list->size--;
}

void list_free(List *list)
{

    free(list->data);
    list->data = NULL;
    list->size = 0;
    list->capacity = 0;
}

void list_debug_info(List *list)
{
    ESP_LOGI("LIST",
             "last_link_obj = %d, size = %d, element_size = %d, capacity = %d",
             (int)list->data,
             list->size,
             list->element_size,
             list->capacity);
}