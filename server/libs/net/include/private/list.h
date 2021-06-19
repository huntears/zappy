/*
** EPITECH PROJECT, 2019
** LIST
** File description:
** List header
*/

#ifndef LIST_H_
#define LIST_H_

#include <stdbool.h>

//////////////////////// VAR ////////////////////////

// def struct
typedef struct list_s list_t;
typedef struct list_it_s list_it_t;

typedef struct list_it_s list_it_t;

// struct
struct list_s {
    int size;
    void (*destructor)(void *);
    struct list_it_s *list;
    struct list_it_s *end;
};
struct list_it_s {
    void *data;
    struct list_it_s *prev;
    struct list_it_s *next;
};

///////////////////// PROTOTYPE /////////////////////

// Create and destroy list struct
list_t *list_create(void (*destructor)(void *));
void *list_destroy(list_t *list);

// Get destructor function of data
void (*list_get_destructor(list_t *list))(void *);

// Set destructor function of data
int list_set_destructor(list_t *list, void (*destructor)(void *));

// Appends the specified element to the end of this list
int list_add(list_t *list, void *data);

// Inserts the specified element at the specified position in this list
int list_add_at(list_t *list, void *data, int index);

// Removes the element at the specified position in this list and destroy it
int list_remove(list_t *list, int index);

// Removes the first occurrence of the specified element from this list
int list_remove_data(list_t *list, void *data);

// Removes all occurrence of the specified element from this list
int list_remove_all_data(list_t *list, void *data);

// Removes from this list all of the elements whose index is between
// fromIndex, inclusive, and toIndex, exclusive
int list_remove_range(list_t *list, int index_from, int index_to);

// Reverse order of list
int list_reverse(list_t *list);

// Replaces the element at the specified position in this list with
// the specified element without destroy
int list_set(list_t *list, void *data, int index);

// Returns the element at the specified position in this list
void *list_get(list_t *list, int index);

// Replaces the element at the specified position in this list with
// the specified element with destroy
int list_replace(list_t *list, void *data, int index);

// Returns the number of elements in this list
int list_get_size(list_t *list);

// Returns the number of elements occurrence in this list
int list_count(list_t *list, void *data);

// Returns the index of the first occurrence of the specified element in list
// or -1 if this list does not contain the element
int list_index_of(list_t *list, void *data);

// Returns the index of the last occurrence of the specified element in list
// or -1 if this list does not contain the element
int list_last_index_of(list_t *list, void *data);

// Returns 1 if this list contains the specified element and 0 else
int list_contain(list_t *list, void *data);

// Returns 1 if this list contains no elements and 0 else
int list_is_empty(list_t *list);

// Removes all of the elements from this list
int list_clear(list_t *list);

// Removes from this list all of the elements whose index is not between
// fromIndex, inclusive, and toIndex, exclusive
int list_sub_list(list_t *list, int index_from, int index_to);

// Returns a full copy of this list
list_t *list_clone(list_t *list);

// Returns an array containing all of the elements in this list
// (from first to last element).
void **list_to_array(list_t *list);

// Get list iterator
list_it_t *list_get_it(list_t *list);

// Iterate iterator
// /!/ Do iterate after delete current node
bool next_it(list_it_t **list_it);

#endif /* !LIST_H_ */