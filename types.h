#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <math.h>

/**
 * \file types.h
 * \brief Header file for Sudoku types program and other secondary functions.
 * \author Ronan PLUTA, Raphael SIMON, Maxime MARCHIVE, Diewertje VAN DAM
 * \version 0.3
 * \date September 29, 2023
 */

#define SIZE 9  // <<----  Replace this value with the size of the array (9, 16, or 25)
#define SIZE_SQUARE 3

// Structure to represent a Sudoku cell
typedef struct {
    short unsigned int value; // Value of the cell
    short unsigned int notes; // Notes for the cell
} cases;

// Type alias for a 2D grid of Sudoku cells
typedef cases** grid;

//Utility Functions
grid allocateGrid2D();

void free_grid(grid sudoku, short unsigned int lines);

void print_grid(grid sudoku);

#endif // TYPES_H_INCLUDED
