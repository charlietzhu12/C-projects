
/**
	@file futo.c
	@author Charles Zhu 
	This program uses a memory allocated array that can read any nxn puzzle 
	if the user wants to change the size of the array. This program solves a futoshiki puzzle using recursive
	backtracking with the solve function. 
	*/

#include <stdio.h>
#include <stdlib.h>

int solve(int puzzle[], const int constraints[], int size);
int readPuzzle(const char *name, int *(*puzzle), int *(*constraints), int *size);
void printPuzzle(const int puzzle[], const int constraints[], int size);
int isLegal(int row, int col, int num, const int puzzle[], const int constraints[], int size);

#ifndef NOMAIN   /* ignore: this is to remove the main function for testing purposes */
/**
  This is the starting point of my program.
  Accepts an input file containing the futoshiki puzzle
  and outputs a solution to that puzzle.
  @return exit status
*/
int main() {
    char filename[20];
    int (*puzzle);       /* array for puzzle numbers */
    int (*constraints);  /* array for puzzle constraints */
    int size;          /* size of puzzle */
    printf("Puzzle file: ");
    fflush(stdout);
    scanf("%20s", filename);

    if (!readPuzzle(filename, &puzzle, &constraints, &size)) {
        printf("Unable to open puzzle file: %s\n", filename);
        return 1;
    }
    printf("PUZZLE:\n");
    printPuzzle(puzzle, constraints, size);

    printf("\nSOLUTION:\n");
    if (solve(puzzle, constraints, size)) {
        printPuzzle(puzzle, constraints, size);
    }
    else {
        printf("No solution exists.\n");
    }
    return EXIT_SUCCESS;
}

#endif  /* ignore */
/** 
	memory allocation was used because the array can be changed
	this method allocates memory and reads the puzzle for the constraints
	@param Input file name
	@param puzzle Holds an array of integers
	@param constraints Holds an array of constraints
	@param size Size of puzzle
	@return succesfull exit status
	
	*/

/* function header comment goes here */
int readPuzzle(const char *name, int **puzzle, int **constraints, int *size) {
    FILE *fp;
    int a;
    if ((fp = fopen(name, "r")) == NULL){ return 1; }
    fscanf(fp, "%d\n", size);
    (*puzzle) = (int *) malloc(*size * *size * sizeof(int));
    for (a = 0; a < (*size * *size); a++) {
      (*puzzle)[a] = 0;
    }
    (*constraints) = (int *) malloc(*size * *size * sizeof(int));
    for (a = 0; a < (*size * *size); a++) {
      (*constraints)[a] = 0;
    }

    int lineLen = 2 * (*size) + 1;
    int rowNumber = 0;
    char temp[lineLen + 1];
    while(fgets(temp, lineLen + 2, fp) != NULL) {
      int i;
      if (rowNumber % 2 == 1) { rowNumber++; continue; }
      for (i = 1; i < lineLen; i += 2) {
        if (temp[i] != '-') {
          (*puzzle)[(rowNumber / 2) * (*size) + (i / 2)] = temp[i] - 48;
        }
      }
      rowNumber++;
    }

    fclose(fp);
    fp = fopen(name, "r");
    rowNumber = 0;
    fgets(temp, lineLen + 2, fp);
    while(fgets(temp, lineLen + 2, fp) != NULL) {
      int i;
      for (i = 0; i < lineLen; i++) {
        switch(temp[i]) {
          case '<':
            (*constraints)[(rowNumber / 2) * (*size) + (i / 2) - 1] += (1 << 0); /* add 2^0 = 1 */
            break;
          case '>':
            (*constraints)[(rowNumber / 2) * (*size) + (i / 2) - 1] += (1 << 1); /* add 2^1 = 2 */
            break;
          case '^':
            (*constraints)[(rowNumber / 2) * (*size) + (i / 2)] += (1 << 2); /* add 2^2 = 4 */
            break;
          case 'v':
            (*constraints)[(rowNumber / 2) * (*size) + (i / 2)] += (1 << 3); /* add 2^3 = 8 */
            break;
        }
      }
      rowNumber++;
    }
    fclose(fp);
    return 1;
}

/* function header comment goes here */
void printPuzzle(const int *puzzle, const int *constraints, int size) {
    int numRows = 4;
    int numColumns = 2 * size + 1;

    int i;
    for (i = 0; i < numRows; i++) {
        /* Special case: last row */
        int j;
        if (i == numRows - 1) {
          int j;
          for (j = 0; j < numColumns; j++) {
            if (j == 0 || j == numColumns - 1) {
              printf("|");
              continue;
            }
            if (j % 2 == 1) {
              /* Puzzle space */
              if (puzzle[i * size + (j / 2)] == 0) {
                printf("-");
              } else {
                printf("%d", puzzle[i * size + (j / 2)]);
              }
            } else {
              /* Constraint space: consider all possible numbers */
              switch(constraints[i * size + (j/2) - 1]) {
                case 0:
                  printf(" ");
                  break;
                case 1:
                  printf("<");
                  break;
                case 2:
                  printf(">");
                  break;
              }
            }
          }
          putchar('\n');
          break;
        }
        /* puzzle and alligator row */
        for (j = 0; j < numColumns; j++) {
          if (j == 0 || j == numColumns - 1) {
            printf("|");
            continue;
          }
          if (j % 2 == 1) {
            /* puzzle space */
            if (puzzle[i * size + (j / 2)] == 0) {
              printf("-");
            } else {
              printf("%d", puzzle[i * size + (j / 2)]);
            }
          } else {
            /* constraint space: consider all possible numbers */
            switch(constraints[i * size + (j/2) - 1]) {
              case 0:
                printf(" ");
                break;
              case 1:
                printf("<");
                break;
              case 2:
                printf(">");
                break;
              case 5:
                printf("<");
                break;
              case 6:
                printf(">");
                break;
              case 9:
                printf("<");
                break;
              case 10:
                printf(">");
                break;
              default:
                printf(" ");
                break;
            }
          }
        }
        putchar('\n');
        /* v ^ row */
        for (j = 0; j < numColumns; j++) {
          if (j == 0 || j == numColumns - 1) {
            printf("|");
            continue;
          }
          if (j % 2 == 0) {
            printf(" ");
            continue;
          }
          switch(constraints[i * size + (j/2)]) {
              case 0:
                printf(" ");
                break;
              case 4:
                printf("^");
                break;
              case 5:
                printf("^");
                break;
              case 6:
                printf("^");
                break;
              case 8:
                printf("v");
                break;
              case 9:
                printf("v");
                break;
              case 10:
                printf("v");
                break;
          }
        }
        putchar('\n');
    }
    return;
}

/* function header comment goes here */
int solve(int *puzzle, const int *constraints, int size) {
    int i;
    int row = 0;
    int col = 0;
    for (i = 0; i < size * size; i++) {
      if (puzzle[i] == 0) {
        break;
      }
    }
    /* now we have index i, with that we can find row and col */
    col = i % size;
    row = (i - col) / size;
    if (row == size) { return 1; }
    for (i = 1; i <= size; i++) {
      if (isLegal(row, col, i, puzzle, constraints, size)) {
        puzzle[row * size + col] = i;
        if (solve(puzzle, constraints, size)) {
          return 1;
        } else {
          puzzle[row * size + col] = 0;
        }
      }
    }
    return 0;
}

/*function header comment goes here */
int isLegal(int row, int col, int num, const int *puzzle, const int *constraints, int size) {
    /* check every other column in the current row */
    int i;
    int currentIndex = row * size + col;
    for (i = row * size; i < row * size + size; i++) {
      if (puzzle[i] == num) {
        return 0;
      }
    }
    /* check every other row in the current column */
    for (i = 0; i < size; i++) {
      if (puzzle[i * size + col] == num) {
        return 0;
      }
    }
    /* now check for constraints */
    switch(constraints[currentIndex]) {
      case 1:
        if (puzzle[currentIndex + 1] == 0) { return 1; }
        return num < puzzle[currentIndex + 1];
      case 2:
        return num > puzzle[currentIndex + 1];
      case 4:
        if (puzzle[(row + 1) * size + col] == 0) { return 1; }
        return num < puzzle[(row + 1) * size + col];
      case 5:
        if (num < puzzle[currentIndex + 1] && num < puzzle[(row + 1) * size + col]) {
          return 1;
        }
        if (puzzle[currentIndex + 1] == 0 || puzzle[(row + 1) * size + col] == 0) {
          return 1;
        }
        return 0;
      case 6:
        if (num > puzzle[currentIndex + 1] && num < puzzle[(row + 1) * size + col]) {
          return 1;
        }
        if (puzzle[(row + 1) * size + col] == 0) { return 1; }
        return 0;
      case 8:
        return num > puzzle[(row + 1) * size + col];
      case 9:
        if (num < puzzle[currentIndex + 1] && num > puzzle[(row + 1) * size + col]) {
          return 1;
        }
        if (puzzle[currentIndex + 1] == 0) { return 1; }
        return 0;
      case 10:
        if (num > puzzle[currentIndex + 1] && num > puzzle[(row + 1) * size + col]) {
          return 1;
        }
        return 0;
    }
    return 1;
}

