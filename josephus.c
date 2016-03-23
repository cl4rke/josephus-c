#include<stdio.h>
#include<stdlib.h>

#define string char*
typedef struct CircularQueue CircularQueue;

int input(string query) {
    int x;

    printf("%s: ", query);
    scanf("%d", &x);

    return x;
}

struct CircularQueue {
    int* elements;
    int length;
    int front;
    int rear;
};

CircularQueue* initialize_queue(int* elements, int length, int front, int rear) {
    CircularQueue* queue = malloc(sizeof(CircularQueue));

    queue->elements = elements;
    queue->length = length;
    queue->front = front;
    queue->rear = rear;

    return queue;
}

int* initialize_incrementing_int_array(int players_count) {
    int* array = malloc(players_count*sizeof(int));
    for (int i = 0; i < players_count; i++) {
        array[i] = i + 1;
    }
    return array;
}

void enqueue(CircularQueue* queue, int value) {
    queue->rear = (queue->rear + 1) % queue->length;

    queue->elements[queue->rear] = value; 
}

int dequeue(CircularQueue* queue) {
    int value = queue->elements[queue->front];

    queue->front = (queue->front + 1) % queue->length;

    return value;
}

void print(CircularQueue* queue) {
    printf("\nElements: ");
    for (int i = 0; i < queue->length; i++) {
        printf("%d ", queue->elements[i]);
    }
    printf("\n");
    printf("Front:    %d\n", queue->front);
    printf("Rear:     %d\n", queue->rear);
}

int main() {
    int players_count = input("Players count (N)");
    int pass_count    = input("Passes count  (L)");

    CircularQueue* players = initialize_queue(initialize_incrementing_int_array(players_count),
            players_count, 0, players_count-1);

    // start counting from the 2nd player in the first round.
    // this is to be consistent with (pass_count - 1) below.
    enqueue(players, dequeue(players));
    
    // cycle through all (players - 1)
    // there is a -1 to ensure that only one player lives by the end of the loop.
    for (int j = 1; j < players_count; j++) {
        for (int i = 1; i < pass_count; i++) {
            // cycle through the players (pass_count - 1) times
            // there is a -1 because the previous player has already been dequeued
            // or it's the first round and an additional cycle has already been done above.
            enqueue(players, dequeue(players));
        }
        // kill the next player
        dequeue(players);
    }

    // this is last player alive.
    printf("%d\n", dequeue(players));

    return 0;
}

