#ifndef ACCESS_H_INCLUDED
#define ACCESS_H_INCLUDED

#include "types.h"

/**
 * \file access.h
 * \brief Header file for Sudoku access program.
 * \author Ronan PLUTA, Raphael SIMON, Maxime MARCHIVE, Diewertje VAN DAM
 * \version 0.3
 * \date September 29, 2023
 */

 //Access Functions
short unsigned int get_value_of_case(cases *cell);

void set_value_of_case(cases *cell, short unsigned int newValue);

short unsigned int get_notes_of_case(cases *cell);

short unsigned int setnote0(short unsigned int notes, short unsigned int n);

short unsigned int setnote1(short unsigned int notes, short unsigned int n);

short unsigned int setnote(short unsigned int notes, short unsigned int n, short unsigned int x);

short unsigned int getnote0(cases *cell);

short unsigned int getnote1(cases *cell);

short unsigned int getnote(short unsigned int notes, short unsigned int n);

void addNumber(cases *cell, short unsigned int  val);

void delNumber(cases *cell);

cases* getCell(grid sudoku, short unsigned int  x, short unsigned int  y);

#endif // ACCESS_H_INCLUDED
