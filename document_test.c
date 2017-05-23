/**
 * Machine Problem: Vector
 * CS 241 - Fall 2016
 */

#include "document.h"
#include <stdio.h>
// test your document here
int main() {

//    Document* doc = Document_create();
//    Document_insert_line(doc, 10, "My name is Bob!");
//    Document_set_line(doc, 1, "I am Awesome" );
//     Document_set_line(doc, 2, "I am Awesome" );
//     Document_set_line(doc, 3, "I am Awesome" );
//     Document_set_line(doc, 4, "I am Awesome" );
//     Document_set_line(doc, 5, "I am Awesome" );
//     Document_set_line(doc, 6, "I am Awesome" );
//     Document_set_line(doc, 7, "I am Awesome" );
//    Document_set_line(doc, 8, "I am Awesome" );
// 
//   // Document_insert_line(doc, 5, "Move over!");
//    Document_write_to_file(doc, "doc.txt");
//    Document_destroy(doc);
    
    Document* doc = Document_create_from_file("input.txt");
    printf("%d\n", (int)Document_size(doc));
    Document_write_to_file(doc, "doc.txt");
    Document_destroy(doc);


    return 0;
}
