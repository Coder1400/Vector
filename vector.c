/**
 * Machine Problem: Vector
 * CS 241 - Fall 2016
 */

/* An automatically-expanding array of strings. */
#include "vector.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 10

/*
 * Vector structure
 * Do not modify the structure
 * array: Void pointer to the beginning of an array of void pointers to
 * arbitrary data.
 * size: The number of elements in the vector. This is the number of actual
 * objects held in the vector, which is not necessarily equal to its capacity.
 * capacity: The size of the storage space currently allocated for the vector,
 * expressed in terms of elements.
 * copyt_constructor: the function callback for you to define the way you want
 * to copy elements
 * destructor:  the function callback for you to define the way you want to
 * destroy elements
 */
struct Vector {
  copy_constructor_type copy_constructor;
  destructor_type destructor;

  void **array;
  size_t size;
  size_t capacity;
};

Vector* Vector_create(copy_constructor_type copy_constructor,
                      destructor_type destructor) {
  
    Vector* vector = (Vector*)malloc(sizeof(Vector));
    vector->capacity = INITIAL_CAPACITY;
    vector->array = (void**)malloc(sizeof(void*) * vector->capacity);
    vector->copy_constructor = copy_constructor;
    vector->destructor = destructor;
    vector->size = 0;
    return vector;
}

void Vector_destroy(Vector *vector) {
    assert(vector);
    
    // go through and destruct any elements that we have allocated in the array --
    // We assert that elements past size will not need to be destructed.
    size_t x = 0;
    size_t size = vector->size;
    destructor_type destruct = vector->destructor;
    while (x < size) {
        destruct(vector->array[x]);
        x++;
    }
    //free the array of pointers then finally the vector struct at last
    free(vector->array);
    free(vector);
}


size_t Vector_size(Vector *vector) {
    assert(vector);
    return vector->size;
}

size_t Vector_capacity(Vector *vector) {
    assert(vector);
    return vector->capacity;
}

void Vector_resize(Vector *vector, size_t new_size) {
    assert(vector);
    assert(new_size >= 0);
    size_t old_size = vector->size;
    
    if (new_size > old_size) {
        //grow the vector's size
        if (new_size > vector->capacity) {
            //new size > size && > capacity
            
            //calculate new capacity
            size_t new_capacity = vector->capacity;
            while (new_capacity <= new_size)
                new_capacity *= 2;
            
            void** new_arr = (void**) realloc(vector->array, sizeof(void*)*new_capacity);
            vector->array = new_arr;
            vector->capacity = new_capacity;
            
        }

        //new size > size && <= capacity
        size_t temp_size = old_size;
        while (temp_size < new_size)
            vector->array[temp_size++] = NULL;
        
        //change vector's size attribute to new_size
        vector->size = new_size;

        
    
    }
    else if(new_size < old_size){
        
        
        size_t temp_size = old_size;
        while (temp_size > new_size) {
            
            if (vector->array[temp_size -1] != NULL)
                vector->destructor(vector->array[temp_size - 1]);
            temp_size = temp_size -1;

            
        }
        
        vector->size = new_size;
        
        size_t capacity = vector->capacity;
        size_t new_capacity = capacity;
        //manage capacity accordingly
        if( new_size <= (capacity/4) ){
            
            while(new_capacity > (new_size*2))
                new_capacity = new_capacity/2;
            if(new_capacity < 10) new_capacity = 10;
        }
        
        
        void** new_arr = (void**)realloc(vector->array, sizeof(void*) * new_capacity);
        vector->array = new_arr;
        vector->capacity = new_capacity;
        
        
    }
    else{
        return;
        
    }

    

}

void Vector_set(Vector *vector, size_t index, void *elem) {
    assert(vector);
    assert(index < vector->size);
    if (index >= vector->size) return;
    
    //if pointer is null just set null in the array
    if(!elem) vector->array[index] = NULL;
    else{
        //Copy element, then store pointer to cpoy in the vector array at index
        copy_constructor_type copy_constructor = vector->copy_constructor;
        void* copied_element = copy_constructor(elem);
        vector->array[index] = copied_element;
    }
}

void *Vector_get(Vector *vector, size_t index) {
    assert(vector);
    assert(index < vector->size);
    if (index >= vector->size) return NULL;
    
    return vector->array[index];
}

void Vector_insert(Vector *vector, size_t index, void *elem) {
    assert(vector);
    assert(index >= 0);
    
    size_t size = vector->size;
    
    //index goes beyond the current bounds
    if ( index >= size )
        Vector_resize(vector, index+1);
    
    // index is within the range of current size!
    else{
        //resize by exactly size + 1 element.
        Vector_resize(vector, vector->size + 1);
        //move indexes DOWN :) SIZE CHANGED - re-fetch from mem
        size = (vector->size)-1; // index actually
       
        while ( size > index) {
            vector->array[size] = vector->array[size-1];
            size--;
        }
        
    }
    
    if (elem)
        vector->array[index] = vector->copy_constructor(elem);
    else vector->array[index] = NULL;
    
}

void Vector_delete(Vector *vector, size_t index) {
    assert(vector);
    assert(index < vector->size);
    
    size_t start = index;
    size_t size = vector->size;
    
    void* elem = vector->array[index];
    
    while( start < size - 1 ){
        vector->array[start] = vector->array[start +1];
        start++;
    }
    
    //let resize free the last element :)
    vector->array[size - 1] = elem;
    Vector_resize(vector, vector->size - 1);
    
}

void Vector_append(Vector *vector, void *elem) {
    assert(vector);
    Vector_resize(vector, vector->size + 1);
    if (elem)
        vector->array[vector->size - 1] = vector->copy_constructor(elem);
    else vector->array[vector->size - 1] = NULL;
    
}













