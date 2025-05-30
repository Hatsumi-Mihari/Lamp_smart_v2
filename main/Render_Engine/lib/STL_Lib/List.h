#define LIST_H
#ifdef LIST_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct List
{
   void* data;
   size_t size;
   size_t element_size;
   size_t capacity;
   bool dynamic_list;
}List;

void list_init(List *list, size_t element_size, bool type_list);
void list_push(List *list, void* element);
void *list_get(List *list, uint16_t index);
void list_update(List *list, uint16_t index, void* elem);
void list_remove(List *list, uint16_t index);
void list_free(List *list);
void list_debug_info(List* list);

#endif