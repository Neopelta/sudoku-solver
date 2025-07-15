#include "utils.h"
#include "sudoku.h"


/**
 * \fn void printNotes(grid sudoku) 
 * \brief Print all the notes of the Sudoku grid.
 * \param [(grid) sudoku] The 2D array representing the Sudoku grid.
*/ 
void printNotes(grid sudoku) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (get_value_of_case(&sudoku[i][j]) == 0){
                printf("Notes for cell (%d, %d) with %d notes: ", i+1, j+1,tabNotes[sudoku[i][j].notes]);

                for (int k = 0; k < SIZE; k++) {
                    if (getnote(sudoku[i][j].notes, k + 1)) {
                        printf("%d ", k + 1);
                    }
                }

                printf("\n");
            }
        }
    }
}

/**
 * \fn void printNotesOfRow(cases* row)
 * \brief Print all the notes of the tab cases row.
 * \param [(cases*) row] The tab of cells
*/ 
void printNotesOfRow(cases* row) {
    for (int i = 0; i < SIZE; i++) {
        if (get_value_of_case(&row[i]) == 0){
            printf("Notes for cell %d: ", i+1);

            for (int k = 0; k < SIZE; k++) {
                if (getnote(row[i].notes, k + 1)) {
                    printf("%d ", k + 1);
                }
            }

            printf("\n");
        }
    }
}

/**
 * \fn void printValNotes(grid sudoku)
 * \brief Print vlaues in the grid
 * \param [(grid)sudoku] The 2D array representing the Sudoku grid.
*/ 
void printValNotes(grid sudoku){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%2d ",get_value_of_case(&sudoku[i][j]));
        }
        printf("\n");
    }    
}

/**
 * \fn bool isNumberValid(grid sudoku, short unsigned int x, short unsigned int y, short unsigned int number)
 * \brief Checks if the number is valid in notes of case (x,y)
 * \param [(grid) sudoku] The 2D array representing the Sudoku grid.
 * \param [(short unsigned int) x] The row on which we start
 * \param [(short unsigned int) y] The column on which we start.
 * \param [(short unsigned int) number] a number in [1,SIZE] tested
 * \return True if number is valid, otherwise false.
*/
bool isNumberValid(grid sudoku, short unsigned int x, short unsigned int y, short unsigned int number) {
    bool ok = true;

    for (short unsigned int i = 0; i < SIZE; i++) {
        short unsigned int val_x = get_value_of_case(&sudoku[x][i]);
        short unsigned int val_y = get_value_of_case(&sudoku[i][y]);
        short unsigned int val_square = get_value_of_case(&sudoku[x - x % SIZE_SQUARE + i / SIZE_SQUARE][y - y % SIZE_SQUARE + i % SIZE_SQUARE]);

        if (val_x == number || val_y == number || val_square == number) {
            ok = false; // Le nombre existe d�j� dans la m�me ligne, colonne ou bloc
            break;
        }
    }

    return ok; // Le nombre est valide
}


/**
 * \fn int nbNotes(short notes)
 * \brief Count the numbers of note
 * \param [(short) notes] A note of a cell
 * \return The numbers of note 
*/
int nbNotes(short notes) {
    return tabNotes[notes];
}

/**
 * \fn int foundLastNumber(cases *cell) 
 * \brief Get the value in the note's cell in a Singleton (nbNotes(notes) = 1)
 * \param [(cases*) cell] A cases in the Sudoku grid.
 * \return The only possible value in the note
*/
int foundLastNumber(cases *cell) {
    for (int i = 1; i <= SIZE; i++) {
        if (getnote(get_notes_of_case(cell),i)){
            return i;
        }
    }
    return -1;
}


/**
 * \fn static void updateNotesAfterFill(grid sudoku, short unsigned int x, short unsigned int y, short unsigned int value) 
 * \brief Update notes of cases concerned after an add of a value in the grid
 * \param [(grid) sudoku] The 2D array representing the Sudoku grid.
 * \param [(short unsigned int) x] The row on which we start
 * \param [(short unsigned int) y] The column on which we start.
 * \param [(short unsigned int) value] a value in [1,SIZE] added 
*/
void updateNotesAfterFill(grid sudoku, short unsigned int x, short unsigned int y, short unsigned int value) {
    short unsigned int block_start_x = x - x % SIZE_SQUARE;
    short unsigned int block_start_y = y - y % SIZE_SQUARE;

    for (short unsigned int i = 0; i < SIZE; i++) {
        cases *cell_row = getCell(sudoku,x,i);
        if (i != y && get_value_of_case(cell_row) == 0 && getnote(get_notes_of_case(cell_row),value)) {
            cell_row->notes = setnote0(get_notes_of_case(cell_row), value);
        }
        cases *cell_col = getCell(sudoku,i,y);
        if (i != x && get_value_of_case(cell_col) == 0 && getnote(get_notes_of_case(cell_col),value)) {
            cell_col->notes = setnote0(get_notes_of_case(cell_col), value);
        }
        short unsigned int block_x = block_start_x + i / SIZE_SQUARE;
        short unsigned int block_y = block_start_y + i % SIZE_SQUARE;
        cases *cell_block = getCell(sudoku,block_x,block_y);
        if ((block_x != x || block_y != y) && get_value_of_case(cell_block) == 0 && getnote(get_notes_of_case(cell_block),value)) {
            cell_block->notes = setnote0(get_notes_of_case(cell_block), value);
        }
    }
}
