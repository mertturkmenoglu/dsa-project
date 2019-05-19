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
#include <assert.h>

#define MAX_WORD_LENGTH 10

int createAdjacencyMatrix(FILE *fptr);

int main() {

    // Open word file
    // TODO: Update file path.
    FILE *fptr = fopen("/home/mert/codes/dsa-project/kelime.txt", "r");
    assert(fptr);

    int result = createAdjacencyMatrix(fptr);
    assert(result == 1);

    // Close word file
    fclose(fptr);
    return 0;
}


int createAdjacencyMatrix(FILE *fptr) {
    char tmp[MAX_WORD_LENGTH];

    // Read line by line and parse the string
    while (fgets(tmp, MAX_WORD_LENGTH - 1, fptr) != NULL) {
        // TODO: Update this part
        printf("%s\n", tmp);
    }

    // TODO: Implement function
    return 0;
}