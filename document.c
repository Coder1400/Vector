/**
 * Machine Problem: Vector
 * CS 241 - Fall 2016
 */

#include "document.h"
#include "vector.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

//Wrapper struct around vector struct for usability and updated, user-friendly features
struct _document {
  Vector *vector;
};

// This is the constructor function for string element.
// Use this as copy_constructor callback in vector.
void *my_copy_ctor(void *elem) {
  char *str = elem;
  assert(str);
  return strdup(str);
}

// This is the destructor function for string element.
// Use this as destructor callback in vector.
void my_destructor(void *elem) { free(elem); }

Document *Document_create() {
    Document* document = (Document*) malloc(sizeof(Document));
    Vector* vector = Vector_create(my_copy_ctor, my_destructor);
    document->vector = vector;
    return document;
}

void Document_write_to_file(Document *document, const char *filename) {
    assert(document);
    assert(filename);
  
    FILE* file = fopen(filename, "w+");
    if (!file) return;
    size_t size = Document_size(document);
    size_t i = 1;
    while (i <= size) {
        if (!Document_get_line(document, i)){
            fprintf(file, "\n");
        }
        else
            fprintf(file, "%s\n", Document_get_line(document,i));
        i++;
    }
    fclose(file);
    
    
}

Document *Document_create_from_file(const char *filename) {
    assert(filename);
  
    Document* doc = Document_create();
    
    FILE* file = fopen(filename, "r");
    if (!file) return doc;
    
    char* buf = NULL;
    size_t capacity = 0;
    int insert_at = 1;
    while(1){
        
        int read = getline(&buf, &capacity, file);
        if (read < 0) break;
        if (*buf == '\n' && read == 1) {
             Vector_insert(doc->vector, insert_at - 1, NULL);
        }
        else{
        
            if (buf[read - 1] == '\n')
                buf[read - 1] = '\0';
            if(strlen(buf)) Document_insert_line(doc, insert_at, buf);
        }
        
        insert_at++;
        
    }
    
    fclose(file);
    if (buf) free(buf);
    return doc;
}

void Document_destroy(Document *document) {
  assert(document);
  Vector_destroy(document->vector);
  free(document);
}

size_t Document_size(Document *document) {
  assert(document);
  return Vector_size(document->vector);
}

void Document_set_line(Document *document, size_t line_number,
                       const char *str) {
  assert(document);
  assert(str);
  assert(line_number > 0);
  size_t index = line_number - 1;
  Vector_set(document->vector, index, (void *)str);
}

const char *Document_get_line(Document *document, size_t line_number) {
  assert(document);
  assert(line_number > 0);
  size_t index = line_number - 1;
  return (const char *)Vector_get(document->vector, index);
}

void Document_insert_line(Document *document, size_t line_number,
                          const char *str) {
  assert(document);
  assert(str);
  assert(line_number > 0);
  size_t index = line_number - 1;
  Vector_insert(document->vector, index, (void *)str);
}

void Document_delete_line(Document *document, size_t line_number) {
  assert(document);
  assert(line_number > 0);
  size_t index = line_number - 1;
  Vector_delete(document->vector, index);
}
