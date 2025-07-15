#ifndef SUDOKU_H_INCLUDED
#define SUDOKU_H_INCLUDED

#include "utils.h"

/**
 * \file sudoku.h
 * \brief Header file for Sudoku solving program.
 * \author Ronan PLUTA, Raphael SIMON, Maxime MARCHIVE, Diewertje VAN DAM
 * \version 0.3
 * \date September 29, 2023
 */
// Verification functions
extern int* tabNotes; // To have allPossibilities of a note in a cell
void initializeNotes();

void freeTabNotes();

bool isValidMinNumber(grid sudoku);

bool isValidRow(grid sudoku, short unsigned int i);

bool isValidCol(grid sudoku, short unsigned int i);

bool isValidSquare(grid sudoku, short unsigned int x, short unsigned int y);

bool isValid(grid sudoku);

bool isCompleteSudoku(grid sudoku);

void fillNotes(grid sudoku);

int SingletonMethode(grid sudoku);

int findKuplet(grid sudoku, int k);

int boxKReduction(grid sudoku,int k);

int xWing(grid sudoku);

void backtracking(grid sudoku);

#endif // SUDOKU_H_INCLUDED
