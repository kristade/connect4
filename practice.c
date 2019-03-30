#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

struct square { // Square and/or node is the representation of where a location on the board is.
    int location; // Location of that square.
    struct square* next; // Direction to the next square.
};

struct squareList { //A list of the square that are connected to each other.
    struct square *head;
};

struct Graph { // A graph of the square, and connected to them, are the adjacency list of the other squares they are connected to.
    int numSquare; // The number of squares.
    struct squareList* array; // List of the connected squares.
};

struct square* newsquare(int location) { // Create a square.
    struct square* newNode = (struct square*) malloc(sizeof(struct square)); // Allocating space for the new square.
    newNode->location = location; // Location of the square.
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int numSquare) { // Creating an adjacency list for the squares.
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph)); // Allocating space for the new graph.
    numSquare = numSquare + 1;
    graph->numSquare = numSquare; // Size of the graph, the same as the number of squares.
    graph->array = (struct squareList*) malloc(numSquare * sizeof(struct squareList)); // Creating space for a list within the graph.
    for (int i = 1; i < numSquare; ++i)
        graph->array[i].head = NULL;
    return graph;
}

void connect(struct Graph* graph, int begin, int location) { //Connects appriopriate squares with each other.
    struct square* newNode = newsquare(location); // Connects a square with the beginning square, and if a square is already there, it justs adds it to the list.
    newNode->next = graph->array[begin].head;
    graph->array[begin].head = newNode;
}

void makeConnection(struct Graph* graph, int row, int col, int gridkey[row][col]){
  for(int a = 0; a < row; a++){
    for(int b = 0; b < col; b++){
      for(int c = 0; c < row; c++){
        for(int d = 0; d < col; d++){
          if(abs(a - c) == 1 && abs(b - d) == 1){connect(graph, gridkey[a][b], gridkey[c][d]);}
          if(abs(a - c) == 0 && abs(b - d) == 1){connect(graph, gridkey[a][b], gridkey[c][d]);}
          if(abs(a - c) == 1 && abs(b - d) == 0){connect(graph, gridkey[a][b], gridkey[c][d]);}
        }
      }
    }
  }
}

void printGraph(struct Graph* graph) { // Artificial intelligence for the Player vs. Computer mode. Computer is always playing to win.
    int numSquare;
    for (numSquare = 1; numSquare < graph->numSquare; ++numSquare) {
        struct square* pCrawl = graph->array[numSquare].head;
        printf("\n Adjacency list of numSquarevertex %d\n head ", numSquare);
        while (pCrawl)
        {
            printf("-> %d", pCrawl->location);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

int main() {
    printf("** Welcome to Connect4 **\n"); // Introduction
    printf("I do not own the copyrights to this game.\n\n"); // Legal rights

    printf("Let's choose your Player mode.\n"); // Prompt player for Player mode
    printf("For Player vs. Player - Enter 'P'\n");
    printf("For Player vs. Computer - Enter 'C'\n");
    printf("Please enter player mode: ");
    char player;
    scanf("%c", &player);
    while(player != 'p' && player != 'P' && player != 'c' && player != 'C'){
      printf("\nSorry that is not an option.\n");
      printf("Please enter player mode: ");
      scanf(" %c", &player);
    }
    if(player == 'p' || player == 'P'){printf("\nYou have chosen Player vs. Player.\n");}
    else{printf("\nYou have chosen Player vs. Computer.\n");}

    int row = 3;
    int col = 3;
    int box = 0;
    char grid[row][col];
    int gridkey[row][col];
    for(int a = 0; a < row; a++){
      for(int b = 0; b < col; b++){
        box++;
        grid[a][b] = '_';
        gridkey[a][b] = box;
      }
    }
    for(int a = 0; a < row; a++){
      for(int b = 0; b < col; b++){
        printf("%c ", grid[a][b]);
      }
      printf("\n");
    }
    for(int a = 0; a < row; a++){
      for(int b = 0; b < col; b++){
        printf("%d ", gridkey[a][b]);
      }
      printf("\n");
    }
    struct Graph* graph = createGraph(box);
    makeConnection(graph, row, col, gridkey);
    printGraph(graph);

    return 0;
}
