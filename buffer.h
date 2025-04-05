#ifndef BUFFER_H
#define BUFFER_H

#define buffer_item int
#define BUFFER_SIZE 5

// init buffer
void buffer_init();

// insert item into buffer
int insert_item(buffer_item item);

// remove an object from buffer
int remove_item(buffer_item *item);
#endif