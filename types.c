#include "access.h"

/**
 * \file access.c
 * \brief Test program.
 * \author Ronan PLUTA, Raphael SIMON, Maxime MARCHIVE, Diewertje VAN DAM
 * \version 0.3
 * \date September 29, 2023
 *
 * Program for accessing datas of a sudoku grid.
 *
 */

//#####                                      #####
//####          UTILITY FUNCTIONS             ####
//#####                                      #####


/**
  * \fn grid allocateGrid2D()
  * \brief Creates a 2D array of size : gridSize x gridSize
  *
  * \param [(short unsigned int  ) gridSize] Size of the grid
  * \return A dynamically allocated 2D array
  */
grid allocateGrid2D(){
    grid tab = (cases**)malloc(SIZE * sizeof(cases *));
    for (short unsigned int   i = 0; i < SIZE; i++) {
        tab[i] = (cases *)malloc(SIZE * sizeof(cases));
    }
    return tab;
}

/**
  * \fn grid create_rand_tab()
  * \brief Creates a 2D array of size gridSize x gridSize with random values.
  *
  * \return A 2D grid with random values
  */
grid create_rand_tab(){
    grid tab = (cases**)malloc(SIZE * sizeof(cases *));

    // Initialisation of the random number generator
    srand(time(NULL));

    for (short unsigned int   i = 0; i < SIZE; i++) {
        tab[i] = (cases *)malloc(SIZE * sizeof(cases));
        for (short unsigned int   j = 0; j < SIZE; j++) {
            short unsigned int  randomValue = rand() % SIZE + 1;
            set_value_of_case(&tab[i][j],randomValue) ;

        }
    }
    return tab;
}

/**
  * \fn void free_grid(grid sudoku, short unsigned int  lines)
  * \brief Frees the memory allocated for a 2D array.
  *
  * \param [grid sudoku] The 2D grid that needs to be freed.
  * \param [short unsigned int  lines] The number of lines the grid has.
  */
void free_grid(grid sudoku, short unsigned int  lines){
    for (short unsigned int   i = 0; i < lines; i++) {
        free(sudoku[i]);
    }
    free(sudoku);
}

/**
  * \fn void print_grid(grid sudoku)
  * \brief Shows a 2D array of size : gridSize x gridSize
  *
  * \param [(grid) sudoku] The 2D array that needs to be shown.
  */
void print_grid(grid sudoku){
    for (short unsigned int  i = 0; i < SIZE; i++) {
        for (short unsigned int  j = 0; j < SIZE; j++) {
            printf("%2d ", get_value_of_case(&sudoku[i][j]));
        }
        printf("\n");
    }
}
