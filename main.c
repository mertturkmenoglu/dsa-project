/**
 * Data Structures and Algorithms Semester Project
 *
 * Problem: For given two words, on each step, changing only one letter, find
 * if you can convert the first word to second word and if you can,
 * print the path.
 *
 * Written and tested on Linux Mint 19 Cinnamon
 * Kernel 4.15.0-47-generic
 * gcc (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0
 * GNU Make 4.1
 * Built for x86_64-pc-linux-gnu
 *
 * IDE:
 * CLion 2019.1.2
 * Build #CL-191.6707.69, built on April 18, 2019
 *
 *
 * stdPath = /home/mert/codes/dsa-project/kelime.txt
 *
 * @author Mert Turkmenoglu
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#define MAX_WORD_LENGTH 10
#define MAX_STDIN_LENGTH 255


struct Node {
    char word[MAX_WORD_LENGTH];
};


struct Queue {
    struct QueueNode *front;
    struct QueueNode *rear;
};


struct QueueNode{
    struct Node value;
    struct QueueNode *next;
};


int bfs(int **matrix, struct Node *wordList, int wordCount, int startingPoint, int endingPoint);

void bfsHandler(int **matrix, struct Node *wordList, int wordCount);

int createAdjacencyMatrix(FILE *fptr, int **matrix, struct Node *wordList, int lineCount);

int choiceHandler(int choice, int **matrix, struct Node *wordList, int lineCount);

int connection(const char *first, const char *second);

void connectionHandler();

int fileLineCount(FILE *fptr);

int getIndex(struct Node *wordList, const char str[MAX_WORD_LENGTH], int wordCount);

void printMatrix(int **matrix, struct Node *wordList, int n);

void printMenu();

void printMatrixHandler(int **matrix, struct Node *wordList, int lineCount);

struct QueueNode* newNode(struct Node value);

struct Queue *createQueue();

void enqueue(struct Queue *q, struct Node value);

struct QueueNode *dequeue(struct Queue *q);

void printQueue(struct Queue *q);

void printNeighbours(int **matrix, struct Node *wordList, char str[MAX_WORD_LENGTH], int wordCount);

void printNeighboursHandler(int **matrix, struct Node *wordList, int lineCount);


extern int errno;


int main() {
    FILE *fptr = NULL;

    int **matrix = NULL;
    struct Node *wordList = NULL;

    char *charptr;
    char str[MAX_STDIN_LENGTH];
    char path[MAX_STDIN_LENGTH];

    int i;
    int result;
    int choice;
    int flag;
    int errnum;

    printf("\nEnter word file path: ");
    scanf("%s", path);

    fptr = fopen(path, "r");

    if (fptr == NULL) {
        errnum = errno;
        fprintf(stderr, "Error No: %d\n", errno);
        perror("Unsuccessful file operation");
        fprintf(stderr, "Error file opening: %s\n", strerror(errnum));
        exit(EXIT_FAILURE);
    }

    int lineCount = fileLineCount(fptr);

    matrix = (int**) malloc(lineCount * sizeof(int*));

    if (matrix == NULL) {
        errnum = errno;
        fprintf(stderr, "Error No: %d\n", errno);
        perror("Unsuccessful matrix creation");
        fprintf(stderr, "Error memory allocation: %s\n", strerror(errnum));
        exit(EXIT_FAILURE);
    }

    for(i = 0; i < lineCount; i++)
        matrix[i] = (int*)calloc(lineCount, sizeof(int));

    wordList = (struct Node*) malloc(lineCount * sizeof(struct Node));

    if (wordList == NULL) {
        errnum = errno;
        fprintf(stderr, "Error No: %d\n", errno);
        perror("Unsuccessful word list creation");
        fprintf(stderr, "Error memory allocation: %s\n", strerror(errnum));
        exit(EXIT_FAILURE);
    }

    result = createAdjacencyMatrix(fptr, matrix, wordList, lineCount);

    if (result == 1) {
        printf("Adjacency Matrix created successfully\n");
    } else {
        errnum = errno;
        fprintf(stderr, "Error No: %d\n", errno);
        perror("Unsuccessful adjacency matrix creation");
        fprintf(stderr, "Error memory allocation: %s\n", strerror(errnum));
        exit(EXIT_FAILURE);
    }

    do {
        printMenu();
        printf("Enter your choice: ");
        scanf("%s", str);
        choice = strtol(str, &charptr, 10);

        flag = choiceHandler(choice, matrix, wordList, lineCount);

    } while(flag == 1);

    fclose(fptr);
    free(matrix);
    free(wordList);

    return 0;
}


void printNeighboursHandler(int **matrix, struct Node *wordList, int lineCount) {
    char str[MAX_WORD_LENGTH];

    printf("\nEnter your word: ");
    scanf("%s", str);

    printNeighbours(matrix, wordList, str, lineCount);
}


int choiceHandler(int choice, int **matrix, struct Node *wordList, int lineCount) {
    switch (choice) {
        case 1:
            printMatrixHandler(matrix, wordList, lineCount);
            break;
        case 2:
            connectionHandler();
            break;
        case 3:
            bfsHandler(matrix, wordList, lineCount);
            break;
        case 4:
            printNeighboursHandler(matrix, wordList, lineCount);
            break;
        case 0:
            break;
        default:
            printf("Invalid input\n");
    }

    return (choice == 0) ? 0 : 1;
}


void printNeighbours(int **matrix, struct Node *wordList, char str[MAX_WORD_LENGTH], int wordCount) {
    int i;
    int index = getIndex(wordList, str, wordCount);

    for(i = 0; i < wordCount; i++) {
        if (matrix[index][i] == 1) {
            printf("%s\n", wordList[i].word);
        }
    }
}


int createAdjacencyMatrix(FILE *fptr, int **matrix, struct Node *wordList, int lineCount) {
    char tmp[MAX_WORD_LENGTH];
    int i, j;

    i = 0;
    // Read line by line, create node and insert into matrix
    while (fgets(tmp, MAX_WORD_LENGTH - 1, fptr) != NULL) {
        struct Node *structNode = malloc(sizeof(struct Node));
        strcpy(structNode->word, tmp);
        wordList[i++] = *structNode;
    }

    // Traverse matrix
    for (i = 0; i < lineCount; i++) {
        for (j = 0; j < lineCount; j++) {
            matrix[i][j] = connection(wordList[i].word, wordList[j].word);
            matrix[j][i] = matrix[i][j];
            if (i == j) {
                matrix[i][j] = 0;
            }
        }
    }

    return 1;
}


int connection(const char *first, const char *second) {
    size_t len = 5;
    size_t i = 0;
    int counter = 0;

    while ((i < len) && (counter < 2)) {
        if (first[i] != second[i]) {
            counter++;
        }
        i++;
    }

    return (counter >= 2) ? 0 : 1;
}


int fileLineCount(FILE *fptr) {
    if (fptr == NULL) {
        return -1;
    }

    int counter = 0;
    char tmp;

    while(!feof(fptr)) {
        tmp = fgetc(fptr);
        if(tmp == '\n')
            counter++;
    }

    rewind(fptr);

    return  counter+1;
}


void printMatrix(int **matrix, struct Node *wordList, int n) {
    int i, j;

    printf("\t\t");
    for(i = 0; i < n; i++) {
        printf("%d\t", i+1);
    }

    printf("\n");
    for(i = 0 ; i < 5 * n; i++) {
        printf("-");
    }
    printf("\n");

    for(i = 0; i < n; i++) {
        printf("%d|\t\t", i+1);
        for (j = 0; j < n; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

    for (i = 0; i < n; i++) {
        printf("%d-%s", i+1, wordList[i].word);
    }
}


void printMenu() {
    printf("1- Print Adjacency Matrix\n");
    printf("2- isDifferentOneLetter\n");
    printf("3- isTransformable\n");
    printf("4- printNeighbours\n");
    printf("0- Exit\n");
    printf("-------------------------\n");
}


void printMatrixHandler(int **matrix, struct Node *wordList, int lineCount) {
    char *charptr;
    char str[MAX_STDIN_LENGTH];
    int tmp;

    do {
        printf("\nHow many rows do you want to see?\n");
        scanf("%s", str);
        tmp = strtol(str, &charptr, 10);
    } while ((tmp <= 0) || (tmp > lineCount));

    printMatrix(matrix, wordList, tmp);
}


void connectionHandler() {
    char first[MAX_WORD_LENGTH];
    char second[MAX_WORD_LENGTH];
    int result;

    printf("\nEnter your first word: ");
    scanf("%s", first);

    printf("\nEnter your second word: ");
    scanf("%s", second);

    result = connection(first, second);

    if (result == 1) {
        printf("Same or one letter difference\n");
    } else {
        printf("More than one letter is different\n");
    }
}


void bfsHandler(int **matrix, struct Node *wordList, int wordCount) {
    struct Node *first = (struct Node*) malloc(sizeof(struct Node));
    struct Node *second = (struct Node*) malloc(sizeof(struct Node));
    int result;

    printf("\nEnter your first word: ");
    scanf("%s", first->word);

    printf("\nEnter your second word: ");
    scanf("%s", second->word);

    int s = getIndex(wordList, first->word, wordCount);
    int e = getIndex(wordList, second->word, wordCount);
    result = bfs(matrix, wordList, wordCount, s, e);

    printf("\n\nResult: %d\n\n", result);

}


int bfs(int **matrix, struct Node *wordList, int wordCount, int startingPoint, int endingPoint) {
    struct Queue *q = createQueue();

    enqueue(q, wordList[startingPoint]);
    assert(q->front != NULL);
    printQueue(q);

    int *visited = (int*) calloc(wordCount, sizeof(int));
    visited[startingPoint] = 1;

    int i;

    while(q->front != NULL) {
        struct Node v = dequeue(q)->value;
        printf("\nCurrent node: %s\n", v.word);
        int index = getIndex(wordList, v.word, wordCount);

        for (i = 0; i < wordCount; i++) {
            // Is it a neighbour?
            if(matrix[index][i] == 1) {
                int j = 0;
                while ((j < 5) && (wordList[endingPoint].word[j] == wordList[i].word[j]))
                    j++;
                if (j == 5)
                    return 1;
                // Is it visited?
                if (visited[i] != 1) {
                    enqueue(q, wordList[i]);
                    visited[i] = 1;
                }
            }
        }
        printQueue(q);
    }

    return 0;
}


int getIndex(struct Node *wordList,  const char str[MAX_WORD_LENGTH], int wordCount) {
    int i = 0;
    char tmp[MAX_WORD_LENGTH];
    while (i < wordCount) {
        strcpy(tmp, wordList[i].word);
        int j = 0;
        while ((j < 5) && (tmp[j] == str[j]))
            j++;
        if (j == 5)
            return i;
        i++;
    }

    return -1;
}


struct QueueNode* newNode(struct Node value) {
    struct QueueNode *temp = (struct QueueNode*)malloc(sizeof(struct QueueNode));

    temp->value = value;
    temp->next = NULL;

    return temp;
}


struct Queue *createQueue() {
    struct Queue *q = (struct Queue*)malloc(sizeof(struct Queue));

    q->front = NULL;
    q->rear = NULL;

    return q;
}


void enqueue(struct Queue *q, struct Node value) {
    struct QueueNode *temp = newNode(value);

    if (q->rear == NULL) {
        q->front = temp;
        q->rear = temp;
        return;
    }

    q->rear->next = temp;
    q->rear = temp;
}


struct QueueNode *dequeue(struct Queue *q) {
    if (q->front == NULL)
        return NULL;

    struct QueueNode *temp = q->front;
    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    return temp;
}

void printQueue(struct Queue *q) {
    struct QueueNode *iter = q->front;

    while(iter != NULL) {
        printf("%s\n", iter->value.word);
        iter = iter->next;
    }

    printf("----------\n");
}