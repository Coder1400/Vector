/**
 * Machine Problem: Vector
 * CS 241 - Fall 2016
 */

#include "vector.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>


void *my_copy_ctor(void *elem) {
    char *str = elem;
    assert(str);
    return strdup(str);
}

void my_destructor(void *elem) { free(elem); }

// Test your vector here
int main() {
    
    
    Vector* v = Vector_create(my_copy_ctor, my_destructor);
    
    Vector_resize(v, 31);
    printf("Size: %d, Capacity: %d\n", (int)Vector_size(v),(int)Vector_capacity(v));
    
    Vector_set(v, 30, "MIZU!");
    
    Vector_insert(v, 30, "week");
    Vector_insert(v, 30, "this");
    Vector_insert(v, 30, "food");
    Vector_insert(v, 30, "junk");
    Vector_insert(v, 30, "eat");
    Vector_insert(v, 30, "not");
    Vector_insert(v, 30, "I will");
    Vector_append(v, "But I would love to see if append works!");
    Vector_resize(v, 0);
    Vector_append(v, "1");
    Vector_append(v, "2");
    Vector_append(v, "3");
    Vector_append(v, "4");
     Vector_delete(v, 3);
    Vector_append(v, "5");
    Vector_append(v, "6");
    Vector_append(v, "7");
    Vector_append(v, "8");
    Vector_append(v, "9");
    Vector_append(v, "10");
    Vector_append(v, "11");
    printf("Size: %d, Capacity: %d\n", (int)Vector_size(v),(int)Vector_capacity(v));
    
    Vector_delete(v, 3);
    Vector_delete(v, 3);
    Vector_delete(v, 3);
    
    Vector_resize(v, 100);
    
    Vector_insert(v, 98, "eat");
    Vector_delete(v, 98);
    
  
   // Vector_resize(v, 20);
    printf("Size: %d, Capacity: %d\n", (int)Vector_size(v),(int)Vector_capacity(v));
    
    Vector_insert(v, 159, "I LOVE");
    printf("Size: %d, Capacity: %d\n", (int)Vector_size(v),(int)Vector_capacity(v));

    Vector_set(v, 9, "LAST element");
    
    //Vector_resize(v, 6);
    printf("Size: %d, Capacity: %d\n", (int)Vector_size(v),(int)Vector_capacity(v));

    
    
    
    //PRINT CONTENTS
    size_t i = 0;
    size_t size = Vector_size(v);
    while (i <  size) {
        printf("Item %d: %s\n", (int)i, Vector_get(v, i));
        i++;
    }
    
    Vector_destroy(v);
    
    return 0;

}
