#include "client_msg.h"


void initializeQueue(client_msg_queue_t *queue) 
{
    queue->front = -1;
    queue->rear = -1;
}

int isFull(client_msg_queue_t *queue) 
{
    return (queue->front == (queue->rear + 1) % MAX_NUMBER_OF_CONNECTIONS);
}

int isEmpty(client_msg_queue_t *queue) 
{
    return (queue->front == -1);
}

void enqueue(client_msg_queue_t *queue, int item) 
{
    if (isFull(queue)) 
    {
        printf("Queue is full.\n");
        return;
    }

    if (isEmpty(queue))
        queue->front = 0;

    queue->rear = (queue->rear + 1) % MAX_NUMBER_OF_CONNECTIONS;
    queue->socket_descriptor[queue->rear] = item;
}

int dequeueValue(client_msg_queue_t *queue, int value) 
{
    if (isEmpty(queue)) 
    {
        printf("Queue is empty.\n");
        return -1;
    }

    int index = queue->front;
    while (index != (queue->rear + 1) % MAX_NUMBER_OF_CONNECTIONS) 
    {
        if (queue->socket_descriptor[index] == value) 
        {
            for (int i = index; i != queue->rear; i = (i + 1) % MAX_NUMBER_OF_CONNECTIONS)
                queue->socket_descriptor[i] = queue->socket_descriptor[(i + 1) % MAX_NUMBER_OF_CONNECTIONS];

            if (queue->front == queue->rear)
                initializeQueue(queue);
            else
                queue->rear = (queue->rear - 1 + MAX_NUMBER_OF_CONNECTIONS) % MAX_NUMBER_OF_CONNECTIONS;

            return value;
        }

        index = (index + 1) % MAX_NUMBER_OF_CONNECTIONS;
    }

    printf("Value not found in the queue.\n");
    return -1;
}

// int main() 
// {
//     client_msg_queue_t queue;
//     initializeQueue(&queue);

//     enqueue(&queue, 10);
//     enqueue(&queue, 20);
//     enqueue(&queue, 30);
//     enqueue(&queue, 40);

//     printf("Queue elements: ");
//     for (int i = queue.front; i != (queue.rear + 1) % MAX_NUMBER_OF_CONNECTIONS; i = (i + 1) % MAX_NUMBER_OF_CONNECTIONS)
//         printf("%d ", queue.socket_descriptor[i]);
//     printf("\n");

//     int value_to_remove = 20;
//     int removed_value = dequeueValue(&queue, value_to_remove);

//     if (removed_value != -1)
//         printf("Removed value: %d\n", removed_value);

//     printf("Queue elements after removing %d: ", value_to_remove);
//     for (int i = queue.front; i != (queue.rear + 1) % MAX_NUMBER_OF_CONNECTIONS; i = (i + 1) % MAX_NUMBER_OF_CONNECTIONS)
//         printf("%d ", queue.socket_descriptor[i]);
//     printf("\n");

//     return 0;
// }

