/*
 * File: jt_queue.h
 * Author: JT Cho
 * [jonathan.t.cho@gmail.com | joncho@seas.upenn.edu]
 * ----------------------
 * Implements a bounded integer queue
 * in C, for the KPCB Fellows Challenge.
 */

#ifndef _jtqueue_h
#define _jtqueue_h

/*
 * Conceals the JTQueueImplementation struct from
 * clients! 
 */
typedef struct JTQueueImplementation JTQueue;

/* !!!!CONSTRUCTOR!!!!
 * Function: jtq_create
 * --------------------
 * Creates a JTQueue for the client, 
 *
 * @param max_capacity - the fixed max capacity of the queue
 * @return JTQueue - the newly allocated queue container
 */
JTQueue *jtq_create(int max_capacity);

/* !!!!ENQUEUE!!!!
 * Function: jtq_enqueue
 * ---------------------
 * Enqueues the given value.
 * If the queue is full, the method returns 0 and
 * does not do anything.
 * Otherwise, enqueues the value at the end.
 *
 * @param queue - queue to enqueue the value in
 * @param value - the value to enqueue
 * @return 1 if the value was enqueued or 0 if full
 */
int jtq_enqueue(JTQueue *queue, int value);

/* !!!!DEQUEUE!!!!
 * Function: jtq_dequeue
 * ---------------------
 * Dequeues a value from the given queue.
 * Halts execution of the code with a failure
 * code if the queue is empty.
 *
 * @param queue - queue to dequeue from
 */
int jtq_dequeue(JTQueue *queue);

/*
 * Function: jtq_peek
 * ------------------
 * Returns the value stored at the front
 * of the queue.
 *
 * @param queue - queue to peek into
 */
int jtq_peek(JTQueue *queue);

/*
 * Function: jtq_peekback
 * ----------------------
 *  Returns the value stored at the back
 *  of the queue.
 *
 *  @param queue - the queue to peek into
 */
int jtq_peekback(JTQueue *queue);

/*
 * Function: jtq_size
 * ------------------
 * Returns the current size of the
 * queue, i.e. the number of stored
 * elements.
 *
 * @param queue
 */
int jtq_size(JTQueue *queue);

/*
 * Function: jtq_isfull
 * --------------------
 * Returns whether the given
 * queue is full or not.
 */
int jtq_isfull(JTQueue *queue);

/*
 * Function: jtq_dispose
 * -------------------
 * Cleans up the memory allocated for the
 * given queue.
 * Presumes that the queue given is valid.
 *
 * @param queue - the queue to clean up
 */
void jtq_dispose(JTQueue *queue);

#endif
