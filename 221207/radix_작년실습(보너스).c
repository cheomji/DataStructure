#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int element;
typedef struct NODE{
    element data[100];
    int front, rear;
}node;
typedef node* nodePointer;

int isEmpty(nodePointer q);
int isFull(nodePointer q);
void addQ(nodePointer q, element item);
element deleteQ(nodePointer q);
void radixSort(int list[], int n);

int main(void)
{
    int size, range, i, j;
    printf("Input size: ");
    scanf("%d", &size);
    printf("Input range(10~ 9999): ");
    scanf("%d", &range);
    int* arr = (int*)malloc(sizeof(int) * size);

    srand((unsigned int)time(NULL));
    printf("before radix sort...\n");
    for (i = 0; i < size; i++)
        arr[i] = rand() % range;
    for (j = 0; j < size; j++)
        printf("%d ", arr[j]);
    printf("\n\n");
    radixSort(arr, size);

    printf("after radix sort...\n");
    for (i = size - 1; i > 0; i--)
        printf("%d ", arr[i]);
    printf("\n");

    free(arr);
    return 0;
}

int isEmpty(nodePointer q){
    return (q->front == q->rear);
}
int isFull(nodePointer q){
    return ((q->rear + 1) % 100 == q->front);
}
void addQ(nodePointer q, element item){
    q->rear = (q->rear + 1) % 100;
    q->data[q->rear] = item;
}
element deleteQ(nodePointer q){
    q->front = (q->front + 1) % 100;
    return q->data[q->front];
}
void radixSort(int a[], int n){
    int i, b, d, factor = 1;
    node queues[10];
    for (b = 0; b < 10; b++) 
        queues[b].front = queues[b].rear = 0;

    for (d = 0; d < 4; d++)
    {
        for (i = 0; i < n; i++)
            addQ(&queues[(a[i] / factor) % 10], a[i]);
        for (b = i = 0; b < 10; b++)
            while (!isEmpty(&queues[b]))
                a[i++] = deleteQ(&queues[b]);
        factor *= 10;
    }
}
