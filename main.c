/**
 * @file main.c
 * Data Structures and Algorithms Semester Project
 *
 * Problem: For given two words, on each step, changing only one letter, find
 * if you can convert the first word to second word and if you can,
 * print the path.
 *
 *
 *
 * !!!IMPORTANT!!!
 * Your file must follow this pattern: [a-z]{5}'\n'
 * Be sure that:
 *      - Your words have five letters
 *      - Letters are lowercase
 *      - Letters are belong to English alphabet
 *      - They are separated with a new line character(one word for each line)
 *      - File does not contain any other character
 *!!!IMPORTANT!!!
 *
 *
 *
 * Written and tested on Linux Mint 19 Cinnamon
 * Kernel 4.15.0-47-generic
 * gcc (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0
 * GNU Make 4.1
 * Built for x86_64-pc-linux-gnu
 *
 *
 *
 * IDE:
 * CLion 2019.1.2
 * Build #CL-191.6707.69, built on April 18, 2019
 *
 *
 *
 * stdPath = /home/mert/codes/dsa-project/kelime.txt
 *
 *
 *
 * @date 28.05.2019
 * @bug No known bugs
 * @author Mert Turkmenoglu
 */



/* Standard IO includes */
#include <stdio.h>  /* For console and file i/o */

/* Standard library includes */
#include <stdlib.h> /* For dynamic memory allocation */

/* String library includes */
#include <string.h> /* For string manipulations */

/* Error handling includes */
#include <errno.h>  /* For perror() and strerr() */

/* Assertion includes */
#include <assert.h> /* For testing purposes */



#define ACTUAL_WORD_LENGTH 5
#define MAX_WORD_LENGTH 10
#define MAX_STDIN_LENGTH 255
#define NUMBER_BASE 10



/**
 * @struct Node
 * @abstract a wrapping model for strings
 *
 * @discussion An abstraction level for expressing graph. An instance
 * of the struct holds the word, level and the parent node for given node.
 *
 * @field word is the string for holding information.
 * @field level is the distance to the relative root at given time
 * @field parent is the parent node for a specific path
 */
struct Node {
    char word[MAX_WORD_LENGTH];
    int level;
    struct Node *parent;
};



/**
 * @struct Path
 * @abstract a wrapping model for BFS graph path
 *
 * @discussion BFS finds a path between two given nodes. It needs to return
 * the path, path length and step count. This structure wraps all these information
 *
 * @field path is an array that holds the node ID's
 * @field n is the path array's length
 * @field step is the transformation step count
 */
struct Path {
    int *path;
    int n;
    int step;
};



/**
 * @struct Queue
 * @abstract a basic model for Queue data structure
 *
 * @discussion An abstract level for expressing queue. It points to
 * front element and rear element. It is implemented using linked list
 *
 * @field front is the pointer to front of the queue
 * @field rear is the pointer to rear of the queue
 */
struct Queue {
    struct QueueNode *front;
    struct QueueNode *rear;
};



/**
 * @struct QueueNode
 * @abstract a queue element
 *
 * @discussion An element of the queue. Queue is implemented using linked list
 * and a QueueNode holds the information for the value and the address of the
 * next element of the queue.
 *
 * @field value is the value wrapped
 * @field next is the pointer to next queue element
 */
struct QueueNode {
    void *value;
    struct QueueNode *next;
};



/*
 * Function prototypes
 */
struct Path *bfs(int **matrix, struct Node *wordList, int wordCount, int startingPoint, int endingPoint);

void bfsHandler(int **matrix, struct Node *wordList, int wordCount);

int createAdjacencyMatrix(FILE *fptr, int **matrix, struct Node *wordList, int lineCount);

int choiceHandler(long choice, int **matrix, struct Node *wordList, int lineCount);

int connection(const char *first, const char *second);

void connectionHandler();

int fileLineCount(FILE *fptr);

int getIndex(struct Node *wordList, const char str[MAX_WORD_LENGTH], int wordCount);

void printMatrix(int **matrix, struct Node *wordList, int rowStart, int rowEnd, int colStart, int colEnd);

void printMenu();

void printMatrixHandler(int **matrix, struct Node *wordList, int lineCount);

int stringCompare(const char *str1, const char *str2);

struct QueueNode *newNode(void *value);

struct Queue *createQueue();

void enqueue(struct Queue *q, void *value);

void *dequeue(struct Queue *q);

void printNeighbours(int **matrix, struct Node *wordList, int index, int wordCount);

void printNeighboursHandler(int **matrix, struct Node *wordList, int lineCount);



int main() {
    FILE *fptr = NULL;

    int **matrix = NULL;
    struct Node *wordList = NULL;

    char *charptr;
    char str[MAX_STDIN_LENGTH];
    char path[MAX_STDIN_LENGTH];

    int i;
    int result;
    int flag;
    int errnum;

    long choice;

    printf("\nEnter word file path: \n");
    printf("(Example: /home/mert/codes/dsa-project/kelime.txt)\n");
    fscanf(stdin, "%s", path);

    fptr = fopen(path, "r");

    if (fptr == NULL) {
        errnum = errno;
        fprintf(stderr, "Error No: %d\n", errno);
        perror("Unsuccessful file operation");
        fprintf(stderr, "Error file opening: %s\n", strerror(errnum));
        exit(EXIT_FAILURE);
    }

    int lineCount = fileLineCount(fptr);

    if (lineCount <= 0) {
        fclose(fptr);
        perror("File can not be read.");
        exit(EXIT_FAILURE);
    }

    matrix = (int **) malloc(lineCount * sizeof(int *));

    if (matrix == NULL) {
        errnum = errno;
        fprintf(stderr, "Error No: %d\n", errno);
        perror("Unsuccessful matrix creation");
        fprintf(stderr, "Error memory allocation: %s\n", strerror(errnum));
        fclose(fptr);
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < lineCount; i++) {
        matrix[i] = (int *) calloc((size_t) lineCount, sizeof(int));
        if (matrix[i] == NULL) {
            errnum = errno;
            fprintf(stderr, "Error No: %d\n", errno);
            perror("Unsuccessful matrix creation");
            fprintf(stderr, "Error memory allocation: %s\n", strerror(errnum));
            fclose(fptr);
            free(matrix);
            exit(EXIT_FAILURE);
        }
    }

    wordList = (struct Node *) malloc(lineCount * sizeof(struct Node));

    if (wordList == NULL) {
        errnum = errno;
        fprintf(stderr, "Error No: %d\n", errno);
        perror("Unsuccessful word list creation");
        fprintf(stderr, "Error memory allocation: %s\n", strerror(errnum));
        fclose(fptr);
        free(matrix);
        exit(EXIT_FAILURE);
    }

    result = createAdjacencyMatrix(fptr, matrix, wordList, lineCount);

    if (result == 1) {
        printf("Adjacency Matrix created successfully\n\n\n");
    } else {
        errnum = errno;
        fprintf(stderr, "Error No: %d\n", errno);
        perror("Unsuccessful adjacency matrix creation");
        fprintf(stderr, "Error memory allocation: %s\n", strerror(errnum));
        fclose(fptr);
        free(matrix);
        free(wordList);
        exit(EXIT_FAILURE);
    }

    /*
     * User interaction happens here.
     * It prints out a menu and user chooses an action.
     * A handler function will be called with necessary parameters.
     * It will ask the user for action until user chooses to exit action.
     */
    do {

        printMenu();
        printf("Enter your choice: ");
        scanf("%s", str);
        choice = strtol(str, &charptr, 10);

        flag = choiceHandler(choice, matrix, wordList, lineCount);

    } while (flag == 1);

    /*
     * Free dynamically allocated memory
     */
    for (i = 0; i < lineCount; i++) {
        int* currentIntPtr = matrix[i];
        free(currentIntPtr);
    }


    fclose(fptr);
    free(matrix);
    free(wordList);

    return 0;
}



/**
 * @function bfs
 * @brief Breadth First Search algorithm implementation
 *
 * @discussion
 * <p>This function traverses on the given graph and tries to find
 * if there is a transformation between given two word.
 *
 * @warning
 * <p><strong>Note that this implementation is <i>not</i> generic</strong>
 * It is a specialized BFS implementation for disclosed purposes.
 *
 * <p>With given words, function starts to enqueueing nodes to queue. As long as
 * queue is not empty, it dequeues and adds unvisited neighbour nodes to queue.
 * If it comes across the searching word, it will return a success value. If it
 * never happens and queue becomes empty, it will return a failure value.
 *
 * @author Mert Turkmenoglu
 * @see {@code struct Node}
 * @see {@code struct Queue}
 *
 * @param matrix is the adjacency matrix
 * @param wordList is the array holds words
 * @param wordCount is the number of words read from file
 * @param startingPoint is the starting node index
 * @param endingPoint is the ending node index
 * @return transformation path or NULL
 */
struct Path *bfs(int **matrix, struct Node *wordList, int wordCount, int startingPoint, int endingPoint) {
    if (matrix == NULL || wordList == NULL) {
        perror("\nbfs: NULL argument\n");
        return NULL;
    }

    int i;

    /*
     * Assign initial level and parent values for every word.
     */
    for (i = 0; i < wordCount; i++) {
        wordList[i].level = 0;
        wordList[i].parent = NULL;
    }

    struct Queue *q = createQueue();

    /*
     * Start by enqueueing the starting node
     */
    enqueue(q, (void*) &wordList[startingPoint]);

    /*
     * Allocate an array for holding marking information.
     * Calloc will assign first values as 0.
     */
    int *visited = (int *) calloc((size_t) wordCount, sizeof(int));

    if (visited == NULL) {
        perror("Unsuccessful array creation");
        fprintf(stderr, "Error memory allocation: %s\n", strerror(errno));
        free(q);
        exit(EXIT_FAILURE);
    }

    /*
     * Mark starting point as visited
     */
    visited[startingPoint] = 1;

    /*
     * While queue is not empty, traverse the graph
     */
    while (q->front != NULL) {
        /*
         * Get the first node
         */
        struct QueueNode *dequed = dequeue(q);
        struct Node *v = dequed->value;

        int result = stringCompare(wordList[endingPoint].word, v->word);

        /* Is it the searched one? */
        if (result == 1) {
            struct Path *path = (struct Path*) malloc(sizeof(struct Path));

            path->path = (int*) malloc((v->level + 1) * sizeof(int));
            path->n = v->level + 1;
            path->step = v->level;
            int j = v->level;

            while(v != NULL) {
                path->path[j--] = getIndex(wordList, v->word, wordCount);
                v = v->parent;
            }

            free(dequed);
            free(v);
            free(q);
            free(visited);

            return path;
        }

        /**
         * I do not understand why we have to print out which nodes we are looking.
         * It breaks the understanding of a function. A function should do only one thing.
         * BFS finds a path between two given nodes and returns the path.
         * It should not print out what nodes we are looking. Furthermore, these outputs could
         * change because of the implementation dependency. I do not think this requirement
         * is necessary. I think this should be removed. So I added a to-do comment.
         */
        // TODO: Remove printf() call for given reasons
        printf("\nCurrent Node: %s\n", v->word);
        int index = getIndex(wordList, v->word, wordCount);

        for (i = 0; i < wordCount; i++) {
            /*
             * Is it a neighbour? Is it visited? If it is a neighbour and
             * not visited, mark it as visited, assign the level and parent
             * values then enqueue it.
             */
            if (matrix[index][i] == 1 && visited[i] != 1) {
                visited[i] = 1;
                wordList[i].level = v->level + 1;
                wordList[i].parent = v;
                enqueue(q, (void*) &wordList[i]);
            }
        }
        free(dequed);
    }

    free(q);
    free(visited);

    /*
     * If queue becomes empty, there is no transformation between given words.
     * Return failure value
     */
    return NULL;
}



/**
 * @function bfsHandler
 *
 * Breadth First Search Handler
 *
 * @brief This function takes necessary inputs from user
 * and handles bfs function calls.
 *
 * @discussion
 * <p>Call for this function comes after user choosing the transformation action.
 * After the call, function will ask two string input for user and reads it from
 * stdin. Then it will call the {@link getIndex} and assign the index values of
 * strings. Then it will call {@link bfs} and wait for the return value. After bfs
 * call, it will print the outcome of the function.
 *
 * @author Mert Turkmenoglu
 * @see {@code struct Node}
 * @see {@code struct Queue}
 *
 * @param matrix is the adjacency matrix
 * @param wordList is the array holds words
 * @param wordCount is the number of words read from file
 */
void bfsHandler(int **matrix, struct Node *wordList, int wordCount) {
    if (matrix == NULL || wordList == NULL) {
        perror("\nbfsHandler: NULL argument\n");
        return;
    }

    int i;
    char first[MAX_WORD_LENGTH];
    char second[MAX_WORD_LENGTH];
    struct Path *result;

    /*
     * Read starting and ending strings from user.
     */
    printf("\nEnter your first word: ");
    scanf("%s", first);

    printf("\nEnter your second word: ");
    scanf("%s", second);

    /*
     * Get the indices of the words.
     */
    int start = getIndex(wordList, first, wordCount);
    int end = getIndex(wordList, second, wordCount);

    if (start == -1 || end == -1) {
        perror("\nYou entered invalid words. Please enter words from the file.\n");
        return;
    }

    /*
     * Get the result and print it.
     */
    result = bfs(matrix, wordList, wordCount, start, end);

    if (result != NULL) {
        printf("There is a transformation between %s and %s: %d steps\n", first, second, result->step);

        for(i = 0; i < result->n; i++) {
            printf("%s\n", wordList[result->path[i]].word);
        }

        free(result->path);
        free(result);
    } else {
        printf("There is no transformation between %s and %s\n", first, second);
    }

    printf("----------------------\n\n");
}



/**
 * @function createAdjacencyMatrix
 *
 * @brief Create Adjacency Matrix from graph
 *
 * @discussion
 * <p>This function reads lines a.k.a words from the given file and wraps them in a
 * structure. Then assigns them to given wordList array. After that, it browses
 * the matrix and assigns 1 or 0 to given point. 1 means that relative row
 * and column words can transform into each other with just step a.k.a they are
 * neighbours in the graph. 0 means, you cannot traverse the graph from given node
 * to the other node without visiting at least one other node. In other words, they
 * are not neighbours. Graph does not contain any self return links. So elements of
 * the main diagonal of the matrix are always zero. Otherwise, other operations may
 * be performed unnecessarily.
 *
 * <p>Call for this function comes after user choosing the transformation action.
 * After the call, function will ask two string input for user and reads it from
 * stdin. Then it will call the {@link getIndex} and assign the index values of
 * strings. Then it will call {@link bfs} and wait for the return value. After bfs
 * call, it will print the outcome of the function.
 *
 * <p>{@code FILE* fptr}, {@code int **matrix} and {@code struct Node *wordList} are
 * must be initialized. They cannot be NULL. So before this function call, file stream
 * must be opened, lines in the file must be counted, appropriate size of matrix and
 * wordList must be allocated on the memory.
 *
 * <p>With given FILE pointer, function starts to read lines from the file. File
 * must be in the correct format. There must be one and only one word on the each
 * line. It creates an abstraction form for the word and holds the structure in an
 * array. It reads the file until the end. Then for all possibilities of
 * word pairs, it browses the matrix and find if they are neighbours.
 * If they are, marks them as one, otherwise zero. On successful operations,
 * function should return 1.
 *
 * @author Mert Turkmenoglu
 *
 * @see {@code struct Node}
 *
 * @param fptr is the not NULL file pointer to the word list file stream
 * @param matrix is the allocated adjacency matrix pointer(not NULL)
 * @param wordList is the allocated array of struct Node's(not NULL)
 * @param lineCount is word/line count of the word file
 * @return successful or not
 */
int createAdjacencyMatrix(FILE *fptr, int **matrix, struct Node *wordList, int lineCount) {
    if (fptr == NULL || matrix == NULL || wordList == NULL) {
        perror("\ncreateAdjacencyMatrix: NULL argument");
        return 0;
    }

    char tmp[MAX_WORD_LENGTH];
    int i = 0;
    int j = 0;

    /*
     * Read until you reach the end of the file
     */
    while (fgets(tmp, MAX_WORD_LENGTH - 1, fptr) != NULL) {
        /*
         * Create an abstraction structure and assign the string
         * to the field. Then add it to the wordList array.
         */
        struct Node *structNode = malloc(sizeof(struct Node));
        strcpy(structNode->word, tmp);
        structNode->level = 0;
        wordList[i++] = *structNode;
        free(structNode);
    }

    /*g
     * Browse the matrix and assign the connection value
     */
    for (i = 0; i < lineCount; i++) {
        for (j = 0; j < lineCount; j++) {
            /*
             * If it is a main diagonal element, mark it as zero because
             * there is no self-return links in the graph.
             */
            matrix[i][j] = (i == j) ? 0 : connection(wordList[i].word, wordList[j].word);
            matrix[j][i] = matrix[i][j];
        }
    }

    /* Return a success value */
    return 1;
}



int checkNeighbours(int **matrix, int firstIndex, int secondIndex) {
    if (matrix == NULL) {
        perror("\ncheckNeighbours: NULL argument\n");
        return 0;
    }

    return (matrix[firstIndex][secondIndex]);
}




void checkNeighboursHandler(int **matrix, struct Node *wordList, int lineCount) {
    char first[MAX_WORD_LENGTH];
    char second[MAX_WORD_LENGTH];
    int result;

    printf("\nEnter your first word: ");
    fscanf(stdin, "%s", first);

    printf("\nEnter your second word: ");
    fscanf(stdin, "%s", second);

    if (strlen(first) == 0 || strlen(second) == 0) {
        perror("\ncheckNeighboursHandler: Empty String\n");
        return;
    }

    int firstIndex = getIndex(wordList, first, lineCount);
    int secondIndex = getIndex(wordList, second, lineCount);

    if (firstIndex == -1 || secondIndex == -1) {
        perror("\nYou entered invalid words. Please enter words from the file.\n");
        return;
    }

    result = checkNeighbours(matrix, firstIndex, secondIndex);

    if (result == 1) {
        printf("%s and %s are neighbours\n\n", first, second);
    } else {
        printf("%s and %s are not neighbours\n\n", first, second);
    }
}



/**
 * @function choiceHandler
 *
 * @brief this function handles user actions
 *
 * @discussion
 * <p>This function takes user input and makes necessary function call
 * If user chose a valid action, relevant function will be called from this
 * point of the code flow. If user enters(chooses) an invalid value, it will
 * print an error message to stderr stream. {@code perror()}
 *
 * <p>Return of the function will be assigned to a flag value used for input
 * loop. If user chooses to exit action(case 0), function will return exit value
 * to previous code flow point. Otherwise, it will return a continue value and
 * user interaction loop will continue.
 *
 * @author Mert Turkmenoglu
 *
 * @see {@code struct Node}
 *
 * @param choice is the user action decision
 * @param matrix is the adjacency matrix that represents the graph connection
 * @param wordList is the array of Nodes that holds words of the graph
 * @param lineCount is the number of line in the word file
 * @return action continue / action exit value
 */
int choiceHandler(long choice, int **matrix, struct Node *wordList, int lineCount) {
    if (matrix == NULL || wordList == NULL) {
        perror("\nchoiceHandler: NULL argument\n");
        return 1;
    }

    switch (choice) {
        case 1:
            printMatrixHandler(matrix, wordList, lineCount);
            break;
        case 2:
            checkNeighboursHandler(matrix, wordList, lineCount);
            break;
        case 3:
            connectionHandler();
            break;
        case 4:
            bfsHandler(matrix, wordList, lineCount);
            break;
        case 5:
            printNeighboursHandler(matrix, wordList, lineCount);
            break;
        case 0:
            break;
        default:
            perror("Invalid input\n");
    }

    return (choice == 0) ? 0 : 1;
}



/**
 * @function connection
 *
 * @brief finds if there is a connection between two nodes
 *
 * @discussion
 * <p>This function takes two string argument and it will compare every
 * character of them. If they are not different, they represents the
 * same node{@see @code struct Node}. If they are different with only
 * one character, it means that they are neighbours on the graph. If
 * they are different with more than one character, they may be connected
 * but they cannot transform into each other with only one step. So they
 * are not neighbours, in other words, they are not connected.
 *
 * @warning
 * <p>Connection word is used for "being neighbour" in the program context.
 * In real use, if there is a path between two node, they may be considered
 * as connected but in this context, there cannot be any other node in the
 * path.
 *
 * @author Mert Turkmenoglu
 *
 * @param first is the first string value
 * @param second is the second string value
 * @return 1 if they are neighbours otherwise 0
 */
int connection(const char *first, const char *second) {
    if (first == NULL || second == NULL) {
        perror("\nconnection: NULL argument\n");
        return 0;
    }

    size_t len = ACTUAL_WORD_LENGTH;
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



/**
 * @function connectionHandler
 *
 * @brief This function handles connection actions
 *
 * @discussion
 * <p>This function reads two string from user and then calls
 * {@function connection}. Return value of the function
 * indicates connection status: True or False. Depending on the
 * return value, function prints relevant information to the stdout.
 *
 * @see @function connection
 *
 * @bug No known bugs
 * @author Mert Turkmenoglu
 */
void connectionHandler() {
    char first[MAX_WORD_LENGTH];
    char second[MAX_WORD_LENGTH];
    int result;

    printf("\nEnter your first word: ");
    fscanf(stdin, "%s", first);

    printf("\nEnter your second word: ");
    fscanf(stdin, "%s", second);

    if (strlen(first) == 0 || strlen(second) == 0) {
        perror("\nconnectionHandler: Empty String\n");
        return;
    }

    result = connection(first, second);

    if (result == 1) {
        printf("Same or one letter difference\n\n");
    } else {
        printf("More than one letter is different\n\n");
    }
}



/**
 * @function fileLineCount
 *
 * @brief This function returns line number of the given file stream
 *
 * @discussion
 * <p>This function takes a file pointer and validates that it is not NULL.
 * After that, it counts new line characters until it reaches EOF. When counting
 * is completed, it sets the file position to the beginning.
 *
 * @author Mert Turkmenoglu
 * @bug No known bugs
 *
 * @param fptr is the not NULL file pointer
 * @return number of lines in the file
 */
int fileLineCount(FILE *fptr) {
    /* Validate pointer is not NULL */
    if (fptr == NULL) {
        perror("\nfileLineCount: NULL argument\n");
        return -1;
    }

    int counter = 0;
    int tmp;

    /* While it is not EOF, count new line characters */
    while (!feof(fptr)) {
        tmp = fgetc(fptr);
        if (tmp == '\n')
            counter++;
    }

    /* Set current file position to beginning */
    rewind(fptr);

    return counter + 1;
}



/**
 * @function getIndex
 *
 * @brief it returns the wordList index of the given string
 *
 * @discussion
 * <p>This function takes an array of Node's and searches the given string in
 * the array. If it cannot find it, returns -1 as unsuccessful operation indicator.
 *
 * @see {@code struct Node}
 *
 * @author Mert Turkmenoglu
 *
 * @param wordList is the array of Node elements
 * @param str is the searching element
 * @param wordCount is the number of elements in the wordList
 * @return index of the string in the wordList or -1
 */
int getIndex(struct Node *wordList, const char str[MAX_WORD_LENGTH], int wordCount) {
    if (wordList == NULL || str == NULL) {
        perror("\ngetIndex: NULL argument\n");
        return -1;
    }

    int i = 0;

    while (i < wordCount) {
        int result = stringCompare(wordList[i].word, str);

        /* Word is found */
        if (result == 1)
            return i;

        i++;
    }

    /* Word is not in the array */
    return -1;
}



/**
 * @function printMatrix
 *
 * @brief Prints matrix to stdout
 *
 * @discussion
 * <p>Function takes an integer matrix and prints its first n row x column
 * formatted to stdout.
 * Then prints n words of the wordList.
 * @see {@code struct Node}
 *
 * @author Mert Turkmenoglu
 * @bug No known bugs
 *
 * @param matrix is the adjacency matrix
 * @param wordList is the array of words
 * @param n is the number of lines will be printed
 */
void printMatrix(int **matrix, struct Node *wordList, int rowStart, int rowEnd, int colStart, int colEnd) {
    if (matrix == NULL || wordList == NULL) {
        perror("\nprintMatrix: NULL argument\n");
        return;
    }

    int i, j;

    printf("\t\t");
    for (i = colStart; i < colEnd; i++) {
        printf(".%d\t", (i + 1) % 10);
    }

    printf("\n");
    for (i = 0; i < 9 * (colEnd-colStart); i++) {
        printf("-");
    }
    printf("\n");

    for (i = rowStart; i < rowEnd; i++) {
        printf("%d|\t\t", i + 1);
        for (j = colStart; j < colEnd; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}



/**
 * @function printMatrixHandler
 *
 * @brief Handles how a matrix should print out
 *
 * @discussion
 * <p>Function takes an integer matrix and prints its first n row x column
 * formatted to stdout.
 * Then prints n words of the wordList.
 * @see {@code struct Node}
 *
 * @author Mert Turkmenoglu
 * @bug No known bugs
 *
 * @param matrix is the adjacency matrix
 * @param wordList is the array of words
 * @param lineCount is the number of words in the list
 */
void printMatrixHandler(int **matrix, struct Node *wordList, int lineCount) {
    int i;

    if (matrix == NULL || wordList == NULL) {
        perror("\nprintMatrixHandler: NULL argument\n");
        return;
    }

    char *charptr;
    char str[MAX_STDIN_LENGTH];
    int rowStart;
    int rowEnd;
    int colStart;
    int colEnd;

    printf("\nPlease make sure that entered number of elements can be displayed on your terminal");
    printf("\nUser has to be sure about his / her terminal's display capacity");

    do {
        printf("\nStarting row index: \n");
        scanf("%s", str);
        rowStart = strtol(str, &charptr, NUMBER_BASE);
    } while ((rowStart <= 0) || (rowStart > lineCount));

    do {
        printf("\nEnding row index: \n");
        scanf("%s", str);
        rowEnd = strtol(str, &charptr, NUMBER_BASE);
    } while ((rowEnd <= 0) || (rowEnd > lineCount));

    do {
        printf("\nStarting column index: \n");
        scanf("%s", str);
        colStart = strtol(str, &charptr, NUMBER_BASE);
    } while ((colStart <= 0) || (colStart > lineCount));

    do {
        printf("\nEnding column index: \n");
        scanf("%s", str);
        colEnd = strtol(str, &charptr, NUMBER_BASE);
    } while ((colEnd <= 0) || (colEnd > lineCount));

    printMatrix(matrix, wordList, rowStart, rowEnd, colStart, colEnd);

    for (i = rowStart; i < rowEnd; i++) {
        printf("%d-%s", i + 1, wordList[i].word);
    }
}



void printMenu() {
    printf("---------------------------------------------------------------\n");
    printf("1- Print Adjacency Matrix (First n element of connection matrix)\n");
    printf("2- areTheyNeighbours (Give two words from matrix)\n");
    printf("3- isDifferentOneLetter (Give any two words)\n");
    printf("4- isTransformable (Is there any path between given two words)\n");
    printf("5- printNeighbours (Print all 1-step transformations)\n");
    printf("0- Exit\n");
    printf("---------------------------------------------------------------\n");
}



/**
 * @function printNeighbours
 *
 * @brief prints all neighbours of a node
 *
 * @discussion
 * <p>This function takes an index and prints all neighbours of
 * that index.
 *
 * @see @see {@code struct Node}
 *
 * @author Mert Turkmenoglu
 *
 * @param matrix is the adjacency matrix
 * @param wordList is the array of words
 * @param index index number of the word
 * @param length of wordList array
 */
void printNeighbours(int **matrix, struct Node *wordList, int index, int wordCount) {
    int i;

    for (i = 0; i < wordCount; i++) {
        if (matrix[index][i] == 1) {
            printf("%s\n", wordList[i].word);
        }
    }
}



/**
 * @function printNeighboursHandler
 *
 * @brief Handles how neighbours of a node will be printed
 *
 * @discussion
 * <p>Function takes adjacency matrix of a graph, list of the nodes and
 * total node count. Then takes input from user, finds the index number
 * of the word then calls @see printNeighbours
 *
 * @author Mert Turkmenoglu
 *
 * @param matrix is the adjacency matrix
 * @param wordList is the array of words
 * @param lineCount is the length of wordList array
 * @return
 */
void printNeighboursHandler(int **matrix, struct Node *wordList, int lineCount) {
    char str[MAX_WORD_LENGTH];

    printf("\nEnter your word: ");
    scanf("%s", str);

    int index = getIndex(wordList, str, lineCount);

    if (index == -1) {
        errno = 1;
        perror("You entered invalid word. Please enter a word from file.");
        return;
    }

    printNeighbours(matrix, wordList, index, lineCount);
}



/**
 * @function stringCompare
 *
 * @brief compares two given strings
 *
 * @discussion
 * <p>Function takes two constant char pointer two strings.
 * Then compares first {@see ACTUAL_WORD_LENGTH} characters.
 * If they are equal, it returns true, else false.
 *
 * @author Mert Turkmenoglu
 *
 * @param str1 is the first string
 * @param str2 is the second string
 * @return if they are equal or not
 */
int stringCompare(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        perror("\nstringCompare: NULL argument");
        return 0;
    }
    int i = 0;

    while ((i < ACTUAL_WORD_LENGTH) && (str1[i] == str2[i]))
        i++;

    return (i == ACTUAL_WORD_LENGTH) ? 1 : 0;
}



/**
 * @function createQueue
 *
 * @brief creates a struct Queue instance
 *
 * @discussion
 * <p>Function allocates memory for a queue instance then
 * assigns front and rear pointers to NULL.
 *
 * @see {@code struct Queue}
 * @see {@code struct QueueNode}
 *
 * @author Mert Turkmenoglu
 *
 * @return pointer to queue instance
 */
struct Queue *createQueue() {
    struct Queue *q = (struct Queue*) malloc(sizeof(struct Queue));

    q->front = NULL;
    q->rear = NULL;

    return q;
}



/**
 * @function dequeue
 *
 * @brief deques element
 *
 * @discussion
 * <p> Function removes the first element of the queue
 * and returns the element. If it is empty, returns NULL.
 *
 * @see {@code struct Queue}
 * @see {@code struct QueueNode}
 *
 * @author Mert Turkmenoglu
 *
 * @param q is the queue instance to operate on
 * @return the first element of the queue
 */
void *dequeue(struct Queue *q) {
    if (q->front == NULL)
        return NULL;

    void *temp = q->front;
    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    return temp;
}



/**
 * @function enqueue
 *
 * @brief Adds new element to queue
 *
 * @discussion
 * <p>Function adds a new element to end of the queue.
 *
 * @see {@code struct Queue}
 * @see {@code struct QueueNode}
 *
 * @author Mert Turkmenoglu
 *
 * @param q is the queue instance to operate on
 * @param value is the new element to add queue
 */
void enqueue(struct Queue *q, void *value) {
    struct QueueNode *temp = newNode(value);

    if (q->rear == NULL) {
        q->front = temp;
        q->rear = temp;
        return;
    }

    q->rear->next = temp;
    q->rear = temp;
}



/**
 * @function newNode
 *
 * @brief creates a new node for queue
 *
 * @discussion
 * <p>Function wraps a Graph Node value with
 * necessary queue values and returns a pointer to it.
 *
 * @see {@code struct Node}
 * @see {@code struct Queue}
 * @see {@code struct QueueNode}
 *
 * @author Mert Turkmenoglu
 *
 * @param value is the Graph's node
 * @return a pointer to wrapped instance
 */
struct QueueNode *newNode(void *value) {
    struct QueueNode *temp = (struct QueueNode *) malloc(sizeof(struct QueueNode));

    temp->value = value;
    temp->next = NULL;

    return temp;
}