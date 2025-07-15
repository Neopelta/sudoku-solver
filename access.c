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
//####          ACCESS FUNCTIONS             ####
//#####                                      #####

/**
  * \fn short unsigned int *get_value_of_case(cases *cell)
  * \brief Returns a pointer to the value that is in the cell.
  *
  * \param [(cases) cell] The cell of which we want the value.
  * \return A pointer to the value that is in the cell.
  */
short unsigned int get_value_of_case(cases *cell){
    return cell->value;
}

/**
  * \fn void set_value_of_case(cases *cell, short unsigned int newValue)
  * \brief Changes the value of the case.
  *
  * \param [(cases) cell] The cell of which we want to change the value.
  * \param [(short unsigned int) newValue] The new value of the case.
  */
void set_value_of_case(cases *cell, short unsigned int newValue) {
    cell->value = newValue;
}

/**
  * \fn short unsigned int get_notes_of_case(cases *cell)
  * \brief Returns the array of the notes of a cell.
  *
  * \param [(cases) cell] The cell of which we want the notes.
  * \return A pointer to the array of the notes of the cell.
  */
short unsigned int get_notes_of_case(cases *cell){
    return cell->notes;
}

/**
  * \fn short unsigned int setnote0(short unsigned int notes, short unsigned int  n)
  * \brief set a note of a case to 0.
  *
  * \param [(short unsigned int) notes] Notes of a case.
  * \param [(short unsigned int) n] Index of the note we want to set to 0.
  * \return same short unsigned int but with a 0 at the index location.
  */
short unsigned int setnote0(short unsigned int notes, short unsigned int  n){
    return notes & ~(1<<(n-1));
}

/**
  * \fn short unsigned int setnote1(short unsigned int notes, short unsigned int  n)
  * \brief set a note of a case to 1.
  *
  * \param [(short unsigned int) notes] Notes of a case.
  * \param [(short unsigned int) n] Index of the note we want to set to 1.
  * \return same short unsigned int but with a 1 at the index location.
  */
short unsigned int setnote1(short unsigned int notes, short unsigned int  n){
    return notes | 1<<(n-1);
}

/**
  * \fn short unsigned int setnote(short unsigned int notes, short unsigned int  n, short unsigned int  x)
  * \brief use setnote1 or setnote0 to set a note of a case to 1 or 0.
  *
  * \param [(short unsigned int) notes] Notes of a case.
  * \param [(short unsigned int) n] number (0 or 1) use to chose setnote (with 0) or setnote1 (with1).
  * \param [(short unsigned int) x] Index of the note we want to set to 0 or 1.
  * \return same short unsigned int but with a 0 or 1 at the index location (noted x).
  */
short unsigned int setnote(short unsigned int notes, short unsigned int  n, short unsigned int  x){
    if (x==0){
        return setnote0(notes,n);
    }else{
         return setnote1(notes,n);
    }
}

/**
  * \fn short unsigned int getnote0(short unsigned int notes)
  * \brief getnote0 : get all the note of the case equal to 0.
  *
  * \param [(short unsigned int) notes] Notes of a case.
  * \return a short unsigned int with 1 for each index equal to 0.
  */
short unsigned int getnote0(cases *cell){
    return ((cell->notes & (1<<(SIZE-1))) != 0);
}

/**
  * \fn short unsigned int getnote1(short unsigned int notes)
  * \brief get all the notes of the case equal to 1.
  *
  * \param [(short unsigned int) notes] Notes of a case.
  * \return a short unsigned int with 1 for each index equal to 1.
  */
short unsigned int getnote1(cases *cell){
    return ((cell->notes & (1<<(SIZE-2))) != 0);
}

/**
  * \fn short unsigned int getnote(short unsigned int notes, short unsigned int  n)
  * \brief get the note of the case.
  *
  * \param [(short unsigned int) notes] Notes of a case.
  * \param [(short unsigned int) n] Index of the note we want to get.
  * \return a short unsigned int equal to 1 if the index equal to 1 and 0 if the index equal to 0.
  */
short unsigned int getnote(short unsigned int notes, short unsigned int  n){
    return notes & 1<<(n-1);
}

/**
  * \fn void addNumber(grid sudoku, short unsigned int  x, short unsigned int  y, short unsigned int  val)
  * \brief Allows us to add a number at the desired location.
  * \param [(grid) sudoku] The 2D array representing the grid.
  * \param [(short unsigned int) x] The x coordinate of the location.
  * \param [(short unsigned int) y] The y coordinate of the location
  * \param [(short unsigned int) val] The value that needs to be added.
  */
void addNumber(cases *cell, short unsigned int  val){
    set_value_of_case(cell,val);
    cell->notes = 0;
}

/**
  * \fn void delNumber(grid sudoku, short unsigned int  x, short unsigned int  y)
  * \brief Allows us to delete a number at the desired location.
  *
  * \param [(grid) sudoku] The 2D array representing the grid.
  * \param [(short unsigned int) x] The x coordinate of the location.
  * \param [(short unsigned int) y] The y coordinate of the location
  */
void delNumber(cases *cell){
    set_value_of_case(cell,0);
}

/**
  * \fn cases* getCell(grid sudoku, short unsigned int  x, short unsigned int  y)
  * \brief get the cell (x,y) in the grid
  *
  * \param [(grid) sudoku]  the 2D array representing the grid.
  * \param [(short unsigned int) x]  Row x.
  * \param [(short unsigned int) y] Col y.
  * \return the cell (x,y) in the grid.
  */
cases* getCell(grid sudoku, short unsigned int  x, short unsigned int  y){
  return &sudoku[x][y];
}

//#####                                      #####
//####        VERIFICATION FUNCTIONS          ####
//#####                                      #####
