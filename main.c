/**
 * Data Structures and Algorithms Semester Project
 *
 * Problem: For given two words, on each step, changing only one letter, find
 * if you can convert the first word to second word and if you can,
 * print the path.
 *
 * prove → prose → prese → prest → wrest → weest → geest → guest → guess
 *
 * You must use graph data structure.
 * Nodes of the graph must be words.
 * If you can convert a word to another one with changing one letter on each
 * step, there is a connection between these two words.
 * There is a connection between "prove" and "prose".
 * But there is no connection between "prove" and "wrest"
 *
 * All words are has a length of five.
 * All letters are lowercase.
 * You must use
 * <a href="https://drive.google.com/open?id=1AoOQ8swqJ_bzUBRz1c1xDI9cZCyzUP9W">
 * kelime.txt</a>
 *
 * Create the word graph(12 pointes): Each word on the file must be a node.
 * Create an adjaceny matrix of NxN where 1-st word on the
 * file is the first node etc. For this node, check all other nodes.
 * If you can connect them(see above for explanation) mark the relevant
 * row-column element as 1, otherwise 0.
 *
 * Write a function shows that you create the graph correctly.
 * For given two input, it writes if there is a connection or not.
 *
 * Find if there is a transformation between two words(48 points):
 * If there is, show how many steps it takes.
 *
 * You must use BFS.
 * Steps of BFS:
 *      * Add the first word(node) to queue.
 *      * Do these steps until queue becomes empty or you
 *          reach the final node(second word):
 *          * Remove the first element of the queue.
 *          * If this the second word, it is done.
 *          * If not, print the word. Add all neighbour nodes that
 *              haven't added to queue. Use another array for this.
 *          * If queue is empty, there is no transformation.
 * First word: beer     Second word: beat
 * Way-1: beer -> bear -> fear -> feat -> beat           4 letter changing
 * Way-2: beer -> bear -> dear -> fear -> feat -> beat   5 letter changing
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_WORD_LENGTH 10
#define MAX_STDIN_LENGTH 255
#define KELIME_FILE_LINE_COUNT 2415

struct Queue {
    int front;
    int rear;
    int size;
    unsigned int capacity;
    int *array;
};

struct Node {
    char word[MAX_WORD_LENGTH];
};

// Create a Queue instance
struct Queue *createQueue(unsigned int initCapacity);

// Query if Queue is full
int isQueueFull(struct Queue *q);

// Query if Queue is empty
int isQueueEmpty(struct Queue *q);

// Add item to queue
int enqueue(struct Queue *q, int item);

// Remove item from queue
int dequeue(struct Queue *q, int *var);

// Get the front item
int getFront(struct Queue *q, int *var);

// Get the rear item
int getRear(struct Queue *q, int *var);

// Print queue to stdout
void printQueue(struct Queue *q);

// Memory deallocate
void finalizeQueue(struct Queue *q);

int createAdjacencyMatrix(FILE *fptr, int **matrix, struct Node *wordList, int lineCount);

int connection(char *first, char *second);

int fileLineCount(FILE *fptr);

void printMatrix(int **matrix, struct Node *wordList, int n);

void printMenu();

void printMatrixHandler(int **matrix, struct Node *wordList, int lineCount);

void connectionHandler();

void bfsHandler();


int main() {
    FILE *fptr;
    int **matrix = NULL;
    int i;
    struct Node *wordList = NULL;
    int result;
    char *stdPath = "/home/mert/codes/dsa-project/kelime.txt";
    int choice;
    char *charptr;
    char str[MAX_STDIN_LENGTH];
    int flag = 1;

    fptr = fopen(stdPath, "r");
    assert(fptr);

    int lineCount = fileLineCount(fptr);
    assert(lineCount == KELIME_FILE_LINE_COUNT);

    matrix = (int**) malloc(lineCount * sizeof(int*));
    assert(matrix != NULL);

    for(i = 0; i < lineCount; i++)
        matrix[i] = (int*)calloc(lineCount, sizeof(int));

    wordList = (struct Node*) malloc(lineCount * sizeof(struct Node));
    assert(wordList != NULL);

    result = createAdjacencyMatrix(fptr, matrix, wordList, lineCount);
    assert(result == 1);
    assert(matrix != NULL);


    do {
        printMenu();
        scanf("%s", str);
        choice = strtol(str, &charptr, 10);

        switch (choice) {
            case 1:
                printMatrixHandler(matrix, wordList, lineCount);
                break;
            case 2:
                connectionHandler();
                break;
            case 3:
                bfsHandler();
                break;
            case 0:
                flag = 0;
                break;
            default:
                printf("Invalid input\n");
        }

    } while(flag == 1);

    fclose(fptr);
    free(matrix);
    free(wordList);
    fptr = NULL;
    matrix = NULL;
    wordList = NULL;
    return 0;
}


void printMenu() {
    printf("1- Print Adjacency Matrix\n");
    printf("2- isDifferentOneLetter\n");
    printf("3- isTransformable\n");
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
        printf("One letter difference\n");
    } else {
        printf("More than one letter is different\n");
    }
}


void bfsHandler() {
    // TODO: IMPLEMENT
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
        }
    }

    return 1;
}


/*
 * BFS PSEUDO-CODE
 *
 * def BFS(G, s):
 *      enqueue(s)
 *      mark s as valid
 *      while (queue is not empty):
 *          v = dequeue()
 *          for all neighbors of w of v in graph G:
 *              if w is not visited:
 *                  enqueue(w)
 *                  mark w as visited
 */


/**
 * Create a queue with
 * @param initCapacity
 * @return a pointer to queue
 */
struct Queue *createQueue(unsigned int initCapacity) {
    struct Queue *q = (struct Queue *) malloc(sizeof(struct Queue));
    q->capacity = initCapacity;
    q->front = 0;
    q->size = 0;
    q->rear = q->capacity - 1;
    q->array = (int *) malloc(q->capacity * sizeof(int));
    return q;
}


/**
 * If size of the queue is equal to its capacity(max)
 * then return 1 (true) else 0 (false)
 */
int isQueueFull(struct Queue *q) {
    return (q->size == q->capacity);
}


/**
 * If size of the queue is equal to 0, then there is no
 * element in the queue return 1 (true) else 0 (false)
 */
int isQueueEmpty(struct Queue *q) {
    return (q->size == 0);
}


/**
 * Add item to queue
 */
int enqueue(struct Queue *q, int item) {
    if (isQueueFull(q))
        return 0;
    q->rear = (q->rear + 1) % q->capacity;
    q->array[q->rear] = item;
    q->size++;
    return 1;
}


/**
 * Remove item from queue
 * @param var is the pointer of the variable that will
 * hold the removed item
 * @return 1(true) if operation is successfull
 * else 0(false).
 */
int dequeue(struct Queue *q, int *var) {
    if (isQueueEmpty(q))
        return 0;
    *var = q->array[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return 1;
}


/**
 * Get the front item of the queue and assign it to
 * @param var
 * @return 1(true) if operation is successfull
 * else 0(false).
 */
int getFront(struct Queue *q, int *var) {
    if (isQueueEmpty(q))
        return 0;
    *var = q->array[q->front];
    return 1;
}


/**
 * Get the rear item of the queue and assign it to
 * @param var
 * @return 1(true) if operation is successfull
 * else 0(false).
 */
int getRear(struct Queue *q, int *var) {
    if (isQueueEmpty(q))
        return 0;
    *var = q->array[q->rear];
    return 1;
}


/**
 * Print the queue to stdout
 */
void printQueue(struct Queue *q) {
    int i;
    for (i = q->front; i <= q->rear; i++) {
        printf("%d\t", q->array[i]);
    }
    printf("\n");
}


/**
 * Deallocate memory
 */
void finalizeQueue(struct Queue *q) {
    free(q->array);
    q->array = NULL;
    q = NULL;
}



int connection(char *first, char *second) {
    size_t len = strlen(first);
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

/*
 * Assertions for testing:
    assert(connection("abcde", "abcde") == 1);
    assert(connection("abcde", "abcdf") == 1);
    assert(connection("abcde", "abcxx") == 0);
 */