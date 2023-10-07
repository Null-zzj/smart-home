#ifndef __CLIENT_MSG_H__
#define __CLIENT_MSG_H__

#include <stdio.h>
#include <stdbool.h>

#define USB_TYPE_SIZE 36


#define MAX_NUMBER_OF_CONNECTIONS 10

// Structure for the message queue
typedef struct 
{
    int socket_descriptor[MAX_NUMBER_OF_CONNECTIONS];
    int front;
    int rear;
} client_msg_queue_t;

void initializeQueue(client_msg_queue_t *queue);
int isFull(client_msg_queue_t *queue);
int isEmpty(client_msg_queue_t *queue);
void enqueue(client_msg_queue_t *queue, int item);
int dequeueValue(client_msg_queue_t *queue, int value);

#endif // !__CLIENT_MSG_
