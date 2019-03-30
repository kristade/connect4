#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>


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
    struct square* newNode = newsquare(location); // Creates a new node for the list with index 'begin' and adds it to 'begin' adjacency list
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

void makeBoard(int row, int col, int box, char grid[row][col], int gridkey[row][col]){ // Creating Connect4 board
  for(int a = 0; a < row; a++){
    for(int b = 0; b < col; b++){
      box++;
      grid[a][b] = '_'; // Initialize all boxes to '_'
      gridkey[a][b] = box; // Keep counts of boxes
    }
  }
}

void printBoard(int row, int col, char grid[row][col]){
  for(int a = 0; a < row; a++){
    for(int b = 0; b < col; b++){
      printf("%c  ", grid[a][b]);
    }
    printf("\n");
  }

  printf("\n");

  for(int a = 1; a <= col; a++){
    if(a < 9)
      printf("%d  ", a);
    else
      printf("%d ", a);
  }
  printf("\n\n");
}

void computerMove(struct Graph* graph) { // Artificial intelligence for the Player vs. Computer mode. Computer is always playing to win.
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

void playerMove1(int move, int space, int row, int col, char grid[row][col]){
  printf("Move Error\n");
  grid[space][move] = 'X';
}

void playerMove2(int move, int space, int row, int col, char grid[row][col]){
  printf("Move Error\n");
  grid[space][move] = 'O';
}

bool playerOne_winState(int row, int col, char grid[row][col]){
    for(int a = row; a >= 0; a--){
      for(int b = col; b >= 0; b--){
        if(grid[a][b] == 'X'){
          int horizontal = 0;
          int vertical = 0;
          int diagLeft = 0;
          int diagRight = 0;
          for(int c = 0; c < row; c++){
            if(grid[a-c][b] == 'X'){horizontal++;}
          }
          for(int c = 0; c < col; c++){
            if(grid[a][b-c] == 'X'){vertical++;}
          }
          for(int c = 0; c < col; c++){
            if(grid[a-c][b+c] == 'X'){diagLeft++;}
          }
          for(int c = 0; c < col; c++){
            if(grid[a-c][b-c] == 'X'){diagRight++;}
          }
          if(horizontal == 4 || vertical == 4 || diagLeft == 4 || diagRight == 4){
            return true;
          }
        }
      }
    }
    return false;
}

bool playerTwo_winState(int row, int col, char grid[row][col]){
    for(int a = row; a >= 0; a--){
      for(int b = col; b >= 0; b--){
        if(grid[a][b] == 'O'){
          int horizontal = 0;
          int vertical = 0;
          int diagLeft = 0;
          int diagRight = 0;
          for(int c = 0; c < row; c++){
            if(grid[a-c][b] == 'O'){horizontal++;}
          }
          for(int c = 0; c < col; c++){
            if(grid[a][b-c] == 'O'){vertical++;}
          }
          for(int c = 0; c < col; c++){
            if(grid[a-c][b+c] == 'O'){diagLeft++;}
          }
          for(int c = 0; c < col; c++){
            if(grid[a-c][b-c] == 'O'){diagRight++;}
          }
          if(horizontal == 4 || vertical == 4 || diagLeft == 4 || diagRight == 4){
            return true;
          }
        }
      }
    }
    return false;
}

int main() {
    printf("** Welcome to Connect4 **\n"); // Introduction
    printf("I do not own the copyrights to this game.\n\n"); // Legal rights

    printf("The object of this game is to connect 4 of your 'X's and/or 'O's so that they form a line in horizontal, vertical or diagonal direction\n");
    printf("while ascending from the bottom of the board. First player to do so is the winner.\n\n");

    printf("Let's choose your Player mode.\n"); // Prompt player for Player mode
    printf("For Player vs. Player - Enter 'P'\n");
    printf("For Player vs. Computer - Enter 'C'\n");
    printf("Please enter player mode: ");
    char player;
    scanf("%c", &player);

    while(player != 'p' && player != 'P' && player != 'c' && player != 'C'){ //Loops until player enter the correct key.
      printf("\nSorry that is not an option.\n");
      printf("Please enter player mode: ");
      scanf(" %c", &player);
    }

    if(player == 'p' || player == 'P'){printf("\nYou have chosen Player vs. Player.\n\n");}
    else{printf("\nYou have chosen Player vs. Computer.\n\n");}

    printf("Now let's choose your board size.\n"); // Prompt player for board size.
    printf("**Warning any board over a 40 x 40, runs off the screen and becomes hard to play.**\n");
    printf("**Warning any board below a 4 x 4 can not be played because no player will be able to connect four.**\n");

    char numRow[100];
    char numCol[100];

    printf("\nPlease enter number of rows: ");
    scanf("%s", numRow);
    int row = atoi(numRow);

    while(row < 4){
      printf("\nSorry that is not an option.\n");
      printf("Please enter number of rows: ");
      scanf("%s", numRow);
      row = atoi(numRow);
    }

    printf("\nPlease enter number of columns: ");
    scanf("%s", numCol);
    int col = atoi(numCol);

    while(col < 4){
      printf("\nSorry that is not an option.\n");
      printf("Please enter number of columns: ");
      scanf("%s", numCol);
      col = atoi(numCol);
    }

    bool playAgain = true; // Determines the amount of rounds the player plays
    int matches[2] = {0}; // Keeps track of how many wins each player has

    while(playAgain){
      int box = 0;
      int compacity[col];
      for(int a = 0; a < col; a++){
        compacity[a] = row-1;
      }

      char grid[row][col];
      int gridkey[row][col];
      makeBoard(row, col, box, grid, gridkey);
      box = row * col;
      struct Graph* graph = createGraph(box);
      makeConnection(graph, row, col, gridkey);
      //printBoard(row, col, grid);

      if(player == 'p' || player == 'P'){
        bool pvp = true;
        bool turn = true;
        while(pvp){
          if(turn){
            printf("\n");
            printBoard(row, col, grid);
            printf("It is Player One turn.\n");
            printf("Choose a column to place your 'X': ");
            char numMove[100];
            scanf("%s", numMove);
            int move = atoi(numMove);
            while(move == 0 || move > col){
                printf("\nSorry that is not an option.\n");
                printf("Choose a column to place your 'X': ");
                scanf("%s", numMove);
                move = atoi(numMove);
            }
            while(move < 0 && move <= col){
              if(compacity[move-1] == -1){
                printf("\nSorry, that column is full.\n");
                printf("Please choose another column: ");
                scanf("%s", numMove);
                move = atoi(numMove);
              }
              else{break;}
            }
            playerMove1(move-1, compacity[move-1], row, col, grid);
            compacity[move-1] = compacity[move - 1] - 1;
            turn = false;
          }
          else if(!turn){
            printf("\n");
            printBoard(row, col, grid);
            printf("It is Player Two turn.\n");
            printf("Choose a column to place your 'O': ");
            char numMove[100];
            scanf("%s", numMove);
            int move = atoi(numMove);
            while(move == 0 || move > col){
              printf("\nSorry that is not an option.\n");
              printf("Choose a column to place your 'X': ");
              scanf("%s", numMove);
              move = atoi(numMove);
            }
            while(move < 0 && move <= col){
              if(compacity[move-1] == -1){
                printf("\nSorry, that column is full.\n");
                printf("Please choose another column: ");
                scanf("%s", numMove);
                move = atoi(numMove);
              }
              else{break;}
            }
            playerMove2(move-1, compacity[move-1], row, col, grid);
            compacity[move-1] = compacity[move-1] - 1;
            turn = true;
          }
        }
      }
      else{
        computerMove(graph);
      }
      printf("Would you like to play again? (Y)es or (N)o: ");
      char nextMatch;
      scanf(" %c", &nextMatch);

      while(nextMatch != 'y' && nextMatch != 'Y' && nextMatch != 'n' && nextMatch != 'N'){ //Loops until player enter the correct key.
        printf("\nSorry that is not an option.\n");
        printf("Would you like to play again? (Y)es or (N)o: ");
        scanf(" %c", &nextMatch);
      }
      if(nextMatch == 'N' || nextMatch == 'n' ){
        playAgain = false;
      }
    }
    if(playAgain == false){
      printf("\nThanks for playing Connect4.\n");
      printf("Come again soon.\n");
    }


    return 0;
}
