#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include "access.h"

void printNotes(grid sudoku);

void printNotesOfRow(cases* row);

void printValNotes();

bool isNumberValid(grid sudoku, short unsigned int x, short unsigned int y, short unsigned int number);

int nbNotes(short notes);

void printValNotes(grid sudoku);

int foundLastNumber(cases *cell);

void updateNotesAfterFill(grid sudoku, short unsigned int x, short unsigned int y, short unsigned int value);

#endif