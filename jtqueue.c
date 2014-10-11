/*
 * File: jtqueue.c
 * Author: JT Cho
 * [jonathan.t.cho@gmail.com | joncho@seas.upenn.edu]
 * ---------------
 * Source file for the bounded integer priority queue
 * designed for the KPCB Fellows Challenge!
 *
 * Please see the header file for more documentation.
 * Thanks! :)
 */

#include "jtqueue.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>

/* 
 * Struct: JTQueue
 * ---------------
 * Implements the JTQueue type.
 * Hidden from the client!
 *
 * Contains information regarding its
 *      - maximum capacity
 *      - number of current elements
 *      - front
 *      - end
 */
struct JTQueueImplementation {
    int max_capacity;
    //The number of elements stored in the queue.
    int size;

    //Pointer to the starting memory pointer of the queue.
    uintptr_t start_ptr;
    //Pointer to the very end of the allocated memory.
    uintptr_t end_ptr;

    //Pointer to front of queue.
    int *front;
    //Pointer to the back of the queue.
    int *back;
};

//See header file for documentation.
JTQueue *jtq_create(int max_capacity) {
    //Make sure that we have enough space for the queue.
    assert(max_capacity > 0);
    
    //Allocate memory for the queue container.
    JTQueue *queue = malloc(sizeof(JTQueue));
    assert(queue != NULL);

    queue->max_capacity = max_capacity;
    queue->size = 0;
    queue->front = queue->back = malloc(max_capacity * sizeof(int));
    assert(queue->front != NULL);

    queue->start_ptr = (uintptr_t) queue->front;
    queue->end_ptr = queue->start_ptr + max_capacity*sizeof(int);
    return queue;
}

//See header file for documentation.
int jtq_enqueue(JTQueue *queue, int value) {
    //Can't add to a full queue!
    if (queue->size == queue->max_capacity)
        return 0;

    //Simply add to end and update.
    *queue->back = value;
    queue->back++;

    //Wrap around if we've overreached.
    if ((uintptr_t)queue->back >= queue->end_ptr)
        queue->back = (int *)queue->start_ptr;

    queue->size++;

    return 1;
}

//See header file for documentation.
int jtq_dequeue(JTQueue *queue) {
    //Can't remove from an empty queue!
    if (queue->size == 0) {
        fprintf(stderr, "JTQueue: Can't remove from an empty queue!\n");
        exit(EXIT_FAILURE);
    }
    
    //Store the head value.
    int value = *queue->front;
    queue->size--;

    //If the size is now 0, simply reset.
    if (queue->size == 0) {
        queue->front = queue->back = (int *)queue->start_ptr;
    }
    else {
        queue->front++;
        if ((uintptr_t)queue->front >= queue->end_ptr) {
            queue->front = (int *)queue->start_ptr;
        }
    }
    
    //Return the value.
    return value;
}

//See header file for documentation.
int jtq_peek(JTQueue *queue) {
    if (queue->size == 0) {
        fprintf(stderr, "JTQueue: Can't peek into an empty queue!\n");
        exit(EXIT_FAILURE);
    }

    return *queue->front;
}

//See header file for documentation.
int jtq_peekback(JTQueue *queue) {
    if (queue->size == 0) {
        fprintf(stderr, "JTQueue: Can't peek into an empty queue!");
        exit(EXIT_FAILURE);
    }
    if ((uintptr_t)queue->back == queue->start_ptr) {
        return *(((int *)queue->end_ptr) - 1);
    }
    return *(queue->back - 1);
}

//See header file for documentation.
int jtq_size(JTQueue *queue) {
    return queue->size;
}

//See header file for documentation.
int jtq_isfull(JTQueue *queue) {
    return queue->size == queue->max_capacity;
}

//See header file for documentation.
void jtq_dispose(JTQueue *queue) {
    free((void *)queue->start_ptr);
    free(queue);
}
