#include <stdio.h>
#include <stdlib.h>

typedef int element;
element* queue;
int front, rear;

void addq(element input, int size);
void deleteq(int size);
void printq(int size);
int createq(FILE *fp);
void addAnddelete(FILE *fp, int size);

int main(void) {
    FILE* f1, *f2, *f3;
    int size;

    f1 = fopen("in1.txt", "r");
    size = createq(f1);
    printf("Queue size: %d\n", size);
    addAnddelete(f1, size);
    fclose(f1);
    free(queue);
    front = 0;
    rear = 0;
    printf("\n");
    f2 = fopen("in2.txt", "r");
    size = createq(f2);
    printf("Queue size: %d\n", size);
    addAnddelete(f2, size);
    fclose(f2);
    free(queue);
    front = 0;
    rear = 0;
    printf("\n\n");
    f3 = fopen("in3.txt", "r");
    size = createq(f3);
    printf("Queue size: %d\n", size);
    addAnddelete(f1, size);
    fclose(f3);
    free(queue);
    
    return 0;
}
void addAnddelete(FILE *fp, int size){
    char ch;
    int input;
    while(!feof(fp)) {
        fscanf(fp, "\n%c", &ch);
        //printf("%c> ", ch);
        if (ch == 'a') {
            fscanf(fp, "%d", &input);
            addq(input, size);
        }
        else if (ch == 'd') {
            if (front == rear) {
                printf("queue empty: cannot delete");
                break;
            }
            deleteq(size);
        }
        else
            printf("error");
        printf("\n");
    }
}
void addq(element input, int size) {
    int check = (rear + 1) % size;
    if (front == check) {
        printf("queue full: cannot add");
        return;
    }
    rear = check;
    queue[rear] = input;
    printq(size);
}
void deleteq(int size) {
    front = (front + 1) % size;
    if (front == rear)
        printf("Circular queue is empty");
    else
        printq(size);
}
void printq(int size) {
    printf("Circular queue:");
    int i = front + 1;
    while (1) {
        if (i == size)
            i = 0;
        if (i == rear) {
            printf("%2d", queue[i]);
            break;
        }
        printf("%2d", queue[i++]);
    }
}
int createq(FILE *fp){
    int n;
    fscanf(fp, "%d", &n);
    queue = (element*)malloc(n * sizeof(element));
    return n;
}
