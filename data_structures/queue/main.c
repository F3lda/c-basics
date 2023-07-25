#include <stdio.h>
#include <stdlib.h>

#define QUEUE_SIZE 5
int queue_array[QUEUE_SIZE];
int queue_front = -1;
int queue_rear = -1;



int queueLength()
{
    if (queue_front == -1 && queue_rear == -1) {
        return 0;
    } else if (queue_front == queue_rear) {
        return 1;
    } else if (queue_front < queue_rear) {
        return (queue_rear-queue_front)+1;
    } else if (queue_front > queue_rear) {
        return (QUEUE_SIZE-queue_front)+queue_rear+1;
    }
    return -1;
}

int queueInsert(int value)
{
    printf("Length: %d, Front: %d, Rear: %d;\n", queueLength(), queue_front, queue_rear);
    if (queueLength() == QUEUE_SIZE) {
        printf("FULL (%d)\n", queueLength());
        return -1;
    } else {
        if (queueLength() == 0) {
            queue_front = 0;
            queue_rear = 0;
        } else {
            if (queue_rear+1 == QUEUE_SIZE) {
                queue_rear = 0;
            } else {
                queue_rear++;
            }
        }
        queue_array[queue_rear] = value;

        return 1;
    }
}

int queueRemove()
{
    printf("Length: %d, Front: %d, Rear: %d;\n", queueLength(), queue_front, queue_rear);
    if (queueLength() == 0) {
        printf("EMPTY (%d)\n", queueLength());
        return -1;
    } else {
        int value = queue_array[queue_front];
        if (queueLength() == 1) {
            queue_front = -1;
            queue_rear = -1;
        } else {
            if (queue_front+1 == QUEUE_SIZE) {
                queue_front = 0;
            } else {
                queue_front++;
            }
        }

        return value;
    }
}

void display()
{
    if (queueLength() == 0) {
        printf("Queue is empty\n");
    } else {
        printf("Queue is: ");
        int i;
        for (i = queue_front; i < queueLength()+queue_front; i++) {
            if (i >= QUEUE_SIZE) {
                printf("%d ", queue_array[i-QUEUE_SIZE]);
            } else {
                printf("%d ", queue_array[i]);
            }
        }
        printf("\n");
    }
}

int queuePeek()
{
    if (queueLength() == 0) {
        printf("EMPTY (%d)\n", queueLength());
        return -1;
    } else {
        return queue_array[queue_front];
    }
}

void queueClear()
{
    queue_front = -1;
    queue_rear = -1;
}

int isInQueue(int value)
{
    printf("Front: %d, Rear: %d;\n", queue_front, queue_rear);
    if (queueLength() != 0) {
        int i;
        for (i = queue_front; i < queueLength()+queue_front; i++) {
            if (i >= QUEUE_SIZE) {
                if (queue_array[i-QUEUE_SIZE] == value) {
                    return 1;
                }
            } else {
                if (queue_array[i] == value) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int main()
{
    queueInsert(1);
    queueInsert(2);
    queueInsert(3);
    queueInsert(4);
    queueInsert(5);
    queueInsert(6);
    printf("Queue peek: %d\n", queuePeek());

    queueRemove();
    queueRemove();
    queueRemove();


    queueInsert(6);
    queueInsert(7);
    queueInsert(8);
    queueInsert(9);
    queueInsert(10);


    display();
    printf("Queue peek: %d\n", queuePeek());


    printf("Is in queue (7): %d\n", isInQueue(7));
    printf("Is in queue (1): %d\n", isInQueue(3));


    queueRemove();
    queueRemove();
    queueRemove();
    queueRemove();
    queueInsert(11);
    queueInsert(12);
    queueInsert(13);

    queueRemove();
    queueRemove();
    queueRemove();
    queueRemove();

    display();

    return 0;
}
