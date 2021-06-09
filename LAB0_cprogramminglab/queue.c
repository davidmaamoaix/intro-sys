/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    /* Remember to handle the case if malloc returned NULL */
    queue_t *queue = malloc(sizeof(queue_t));
    MALLOC_CHECK(queue, NULL);

    queue->head = NULL;
    queue->size = 0;

    return queue;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q == NULL) return;

    list_ele_t *node = q->head;
    while (node != NULL) {
        list_ele_t *temp = node->next;
        free(node);
        node = temp;
    }
    
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_head(queue_t *q, int v)
{
    if (q == NULL) return false;
    list_ele_t *head = malloc(sizeof(list_ele_t));
    MALLOC_CHECK(head, false);

    head->next = q->head;
    head->value = v;
    q->head = head;
    if (q->size == 0) q->tail = head;

    ++(q->size);

    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_tail(queue_t *q, int v)
{
    if (q == NULL) return false;
    list_ele_t *tail = malloc(sizeof(list_ele_t));
    MALLOC_CHECK(tail, false);

    tail->value = v;
    tail->next = NULL;

    if (q->size == 0) {
        q->head = tail;
        q->tail = tail;

        return true;
    }

    q->tail->next = tail;
    q->tail = tail;
    ++(q->size);

    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If vp non-NULL and element removed, store removed value at *vp.
  Any unused storage should be freed
*/
bool q_remove_head(queue_t *q, int *vp)
{
    if (q == NULL || q->size == 0) return false;

    if (vp != NULL) *vp = q->head->value;
    list_ele_t *temp = q->head;
    q->head = q->head->next;
    free(temp);

    --(q->size);

    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (q == NULL) return 0;

    return q->size;
}

/*
  Reverse elements in queue.

  Your implementation must not allocate or free any elements (e.g., by
  calling q_insert_head or q_remove_head).  Instead, it should modify
  the pointers in the existing data structure.
 */
void q_reverse(queue_t *q)
{
    if (q == NULL || q->size == 0) return;

    list_ele_t *head = q->head;
    list_ele_t *next = head->next;
    head->next = NULL;
    q->tail = head;

    while (next != NULL) {
        list_ele_t *temp = next->next;
        next->next = head;
        head = next;
        next = temp;
    }

    q->head = head;
}

