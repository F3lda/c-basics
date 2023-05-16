#include <stdio.h>
#include <stdlib.h>

#define QUEUE_SIZE 50
int queue_array[QUEUE_SIZE];
int queue_rear = -1;
int queue_front = -1;


int queueInsert(int value)
{
    if (queue_rear == QUEUE_SIZE - 1) {
        return 0;
    } else {
        if (queue_front == -1) {
            queue_front = 0;
        }
        queue_array[++queue_rear] = value;
        return 1;
    }
}

int queueRemove()
{
    if (queue_front == -1 || queue_front > queue_rear) {
        return 0;
    } else {
        return queue_array[queue_front++];
    }
}

int isInQueue(int value)
{
    if (queue_front != - 1) {
        int i;
        for (i = queue_front; i <= queue_rear; i++) {
            if (queue_array[i] == value) {
                return 1;
            }
        }
    }
    return 0;
}

void display()
{
    if (queue_front == - 1) {
        printf("Queue is empty\n");
    } else {
        printf("Queue is : \n");
        int i;
        for (i = queue_front; i <= queue_rear; i++) {
            printf("%d ", queue_array[i]);
        }
        printf("\n");
    }
}

int main()
{
    queueInsert(1);
    queueRemove();
    queueInsert(2);
    queueInsert(3);
    queueInsert(4);
    queueInsert(5);
    queueRemove();

    display();

    printf("%d\n", isInQueue(2));
    printf("%d\n", isInQueue(4));

    printf("%d\n", queue_rear - queue_front);

    return 0;
}
