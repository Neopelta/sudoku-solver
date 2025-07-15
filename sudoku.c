#include "sudoku.h"

/**
 * \file sudoku.c
 * \brief Test program.
 * \author Ronan PLUTA, Raphael SIMON, Maxime MARCHIVE, Diewertje VAN DAM
 * \version 0.3
 * \date September 29, 2023
 *
 * Program for solving a sudoku grid.
 *
 */

int *tabNotes;

/**
 * \fn void initializeNotes()
 * \brief initalize the array of notes.
*/
void initializeNotes() {
    int pow2SIZE = (int)pow(2, SIZE);
    tabNotes = calloc(pow2SIZE, sizeof(int));

    for (int i = 0; i < pow2SIZE; i++) {
        int count = 0;
        int temp = i;

        while (temp > 0) {
            count += temp % 2;
            temp /= 2;
        }

        tabNotes[i] = count;
    }
}

/**
 * \fn void freeTabNotes()
 * \brief free the array of notes.
*/
void freeTabNotes(){
    free(tabNotes);
}


/**
  * \fn bool isValidMinNumber(grid sudoku)
  * \brief Checks if the minimum required numbers to complete the grid is present.
  *
  * \param [(grid) sudoku] The array representing the Sudoku grid .
  * \return True if the minimum required numbers to complete the grid is present, otherwise it returns false.
  */
bool isValidMinNumber(grid sudoku){
    short unsigned int  inCount = 0;
    for (short unsigned int  i = 0 ; i < SIZE ; i++) {
        for (short unsigned int  j = 0 ; j < SIZE ; j++) {
            if (get_value_of_case(getCell(sudoku,i,j)) != 0){
                inCount++;
            }
        }
    }
    if (SIZE == 9 && inCount < 17){
        printf("Pas assez de nombres sur la grille\n");
        return false;
    }
    /*
    Given that solving a minimal 9x9 Sudoku required the equivalent of 7.1 million hours of computation on a supercomputer over 11 calendar months,
    it is reasonable to conclude that solving a minimal 16x16 Sudoku will not be achieved in the coming decades.
    */
    return true;
}

/**
  * \fn bool check_array(grid sudoku, short unsigned int  xmin, short unsigned int  ymin, short unsigned int  xmax, short unsigned int  ymax)
  * \brief check_array : Checks if a given array is valid.
  *
  * \param [(grid) sudoku] The 2D array representing the Sudoku grid.
  * \param [(short unsigned int) xmin] The value of x of where we are starting.
  * \param [(short unsigned int) ymin] The value of y of where we are starting.
  * \param [(short unsigned int) xmax] The biggest value of x we have.
  * \param [(short unsigned int) ymax] The biggest value of y we have.
  * \return True if the array is valid, otherwise it returns false.
  */
static bool check_array(grid sudoku, short unsigned int  xmin, short unsigned int  ymin, short unsigned int  xmax, short unsigned int  ymax){
    short unsigned int  height= ymax - ymin + 1;
    short unsigned int  width= xmax - xmin + 1;
    short unsigned int  lenght= height * width;
    bool exists[lenght];
    memset(exists, false, sizeof(exists));

    for (short unsigned int x = xmin; x<= xmax; x++){
        for (short unsigned int y=ymin; y<= ymax; y++){
            if (exists[get_value_of_case(getCell(sudoku,x,y))-1]==false || get_value_of_case(getCell(sudoku,x,y))-1 != 0){
                exists[get_value_of_case(getCell(sudoku,x,y))-1]=true;

            }else {
                return false;
            }
        }
    }
    return true;
}

/**
  * \fn bool isValidRow(grid sudoku, short unsigned int ind)
  * \brief isValidRow : Checks if a given row is valid.
  *
  * \param [(grid) sudoku] The 2D array representing the Sudoku grid.
  * \param [(short unsigned int) i] The row that needs to be checked.
  * \return True if the row is valid, otherwise it returns false.
  */
bool isValidRow(grid sudoku, short unsigned int i){
    return check_array(sudoku,i,0,i,SIZE-1);
}

/**
  * \fn bool isValidCol(grid sudoku, short unsigned int i)
  * \brief Checks if a column is valid.
  *
  * \param [(grid) sudoku] The 2D array representing the Sudoku grid.
  * \param [(short unsigned int) i] The column that needs to be checked.
  * \return True if the column is valid, otherwise false.
  */
bool isValidCol(grid sudoku, short unsigned int i){
    return check_array(sudoku, 0,i,SIZE-1,i);
}

/**
  * \fn bool isValidSquare(grid sudoku, short unsigned int  x, short unsigned int  y, short unsigned int size)
  * \brief Checks if a given square is valid.
  *
  * \param [(grid) sudoku] The 2D array representing the Sudoku grid.
  * \param [(short unsigned int) x] The row on which we start
  * \param [(short unsigned int) y] The column on which we start.
  * \param [(short unsigned int) size] The size of the square.
  * \return True if the square is valid, otherwise false.
  */
bool isValidSquare(grid sudoku, short unsigned int  x, short unsigned int  y){
    return check_array(sudoku,x,y ,x+SIZE_SQUARE-1, y+SIZE_SQUARE-1);
}

/**
  * \fn bool isvalid(grid sudoku)
  * \brief isValid : Checks if the sudoku grid is valid.
  *
  * \param [(grid) sudoku] The 2D array representing the Sudoku grid.
  * \return True if the grid is valid, otherwise it returns false.
  */
bool isValid(grid sudoku){
    int i;
    if (isValidMinNumber(sudoku)){
        for (i=0; i < SIZE; i++){
        if (!isValidRow(sudoku,i) || !isValidCol(sudoku,i))
        {
            printf("Une ligne ou colonne n'est pas valide\n");
            return false;
        }
    }

    for (short unsigned int i = 0; i < SIZE; i += SIZE_SQUARE) {
        for (short unsigned int j = 0; j < SIZE; j += SIZE_SQUARE) {
            if (!isValidSquare(sudoku, i, j)) {
                printf("Un carre n'est pas valide.\n" );
                return false;
            }
        }
    }
    }else {
        printf("Il n'y a pas assez de chiffre pour remplir le sudoku ");
        return false;
    }
    printf("La grille de sudoku est valide");
    return true;
}

/**
 * \fn bool isCompleteSudoku(grid sudoku)
 * \brief Checks if the Sudoku puzzle is complete.
 *
 * \param [(grid) sudoku] The 2D array representing the Sudoku grid.
 * \return True if the Sudoku puzzle is complete, otherwise false.
 */
bool isCompleteSudoku(grid sudoku) {
    bool ok = true;
    for (short unsigned int row = 0; row < SIZE; row++) {
        for (short unsigned int col = 0; col < SIZE; col++) {
            cases *cell = getCell(sudoku,row,col);
            if (get_value_of_case(cell) == 0) {
                ok = false;
                break;
            }
        }
    }
    return ok;
}

/**
 * \fn void FillNotes(grid sudoku)
 * \brief Initialize notes of all cases
 * \param [(grid) sudoku] The 2D array representing the Sudoku grid.
*/
void fillNotes(grid sudoku) {
    for (short unsigned int row = 0; row < SIZE; row++) {
        for (short unsigned int col = 0; col < SIZE; col++) {
            cases *cell = getCell(sudoku,row,col);
            if (get_value_of_case(cell) == 0) {
                for (int i = 1; i <= SIZE; i++) {
                    if (isNumberValid(sudoku, row, col, i)) {
                        cell->notes = setnote1(cell->notes, i);
                    }
                }
            }
        }
    }
}


/**
 * \fn int MethodeSingleton(grid sudoku)
 * \brief Apply the SingletonMethode
 * \param [(grid) sudoku] The 2D array representing the Sudoku grid.
 * \return 0 if an add has been done, otherwise 1
*/
int SingletonMethode(grid sudoku) {
    int nb = 0;
    for (short unsigned int row = 0; row < SIZE; row++) {
        for (short unsigned int col = 0; col < SIZE; col++) {
            cases *cell = getCell(sudoku,row,col);
            if (get_value_of_case(cell) == 0){
                if (nbNotes(cell->notes) == 1) {
                    int j = foundLastNumber(cell); // pas besoin de tester le cas j != -1 car nbNotes(cell) = 1
                    addNumber(cell, j);
                    updateNotesAfterFill(sudoku,row,col,j);
                    nb++;
                }
            }
        }
    }
    return nb;
}

/**
  * \fn static bool isNaiked(int k, int* values, cases* cell)
  * \brief Checks if a cell contains the naiked k-uplet
  *
  * \param [(int) k] Size of the k-uplet
  * \param [(int*) values] The array of values
  * \param [(cases*) cell] The cell tested
  * \return True if the cell contains only the notes of the k-uplet, otherwise it returns false.
  */
static bool isNaiked(int k, int* values, cases* cell) {
    bool result = true;
    int value = 1;
    while (result && value <= SIZE) {
        if(getnote(cell->notes, value)){
            int i = 0;
            bool isValues = false;
            while (!isValues && i < k){
                if (value == values[i]){
                    isValues = true;
                }
                i++;
            }
            result = isValues;
        }
        value++;
    }

    return result;
}

/**
  * \fn int nbOfNotesFromKuplet(int k, int* values, cases* cell)
  * \brief Checks the number of notes from the cell that are part of the k-uplet
  *
  * \param [(int) k] Size of the k-uplet
  * \param [(int*) values] The array of values
  * \param [(cases*) cell] The cell tested
  * \return the number of notes from a kuplet contains in the cell
  */
int nbOfNotesFromKuplet(int k, int* values, cases* cell){
    int result = 0;

    for(int i = 0; i < k; i++){
        if(get_value_of_case(cell) == 0 && getnote(cell->notes, values[i])){
            result++;
        }
    }

    return result;
}

/**
  * \fn bool isValue(cases* zone, int value)
  * \brief Checks if the value is contained in the zone
  *
  * \param [(cases*) zone] The zone tested
  * \param [(int*) value] The value checked
  * \return if the value is found in the zone
  */
bool isValue(cases* zone, int value){
    for (int i = 0; i < SIZE; i++) {
        if (get_value_of_case(&zone[i]) == value) {
            return true;
        }
    }

    return false;
}

/**
  * \fn bool isKupletValid(cases* zone, int* values, int k)
  * \brief Checks if the k-uplet does not contains a value already marked in a cell of the zone
  *
  * \param [(cases*) zone] The zone tested
  * \param [(int*) value] The k-uplet
  * \param [(int) k] Size of the k-uplet
  * \return if it's a valid k-uplet
  */
bool isKupletValid(cases* zone, int* values, int k){
    for (int i = 0; i < k; i++){
        if (isValue(zone, values[i])){
            return false;
        }
    }

    return true;
}

/**
  * \fn int isKuplet(int k, int* values, cases* zone)
  * \brief Checks if it's a naiked or hidden k-uplet in the zone
  *
  * \param [(int) k] Size of the k-uplet
  * \param [(int*) value] The k-uplet
  * \param [(cases*) zone] The zone tested
  * \return true if the k-uplet was found in the zone, false otherwise
  */
int isKuplet(int k, int* values, cases* zone){
    if (!isKupletValid(zone, values, k)){
        return -1;
    }

    int* t = (int *)malloc(SIZE * sizeof(int));

    for(int i = 0; i < SIZE; i++){
        t[i] = 0;
    }

    for(int _k = 0; _k < k; _k++){
        int currentValue = values[_k];
        for(int i = 0; i < SIZE; i++ ){
            cases* cell = &zone[i];
            if(get_value_of_case(cell) == 0 && getnote(cell->notes, currentValue)){
                t[i] ++;
            }
        }
    }

    int nbChecks = 0;
    int nbCellNaiked = 0;
    int i = 0;
    bool forceStop = false;

    while (!forceStop && i < SIZE){
        if (k != 1 && t[i] == 1){
            forceStop = true;
        } else if(t[i] != 0){
            if(isNaiked(k, values, &zone[i])){
                nbCellNaiked++;
                nbChecks++;
            } else {
                int nbValues = nbOfNotesFromKuplet(k, values, &zone[i]);
                if (nbValues == k || nbValues > 1){
                    nbChecks++;
                }

            }
        }
        i++;
    }

    free(t);

    if (forceStop){
        return -1;
    }

    if(nbChecks == k || (nbChecks > k && nbCellNaiked == k)){
        return nbChecks;
    }

    return -1;
}

/**
  * \fn int bino(int n, int k)
  * \brief the binomial coefficient of k among n
  * \param [(int) n] the number of elements
  * \param [(int) k] the number of elements to choose
  * \return the binomial coefficient of k among n
  *
*/
int bino(int n, int k) {
    if (k > n)
        return 0;

    int res = 1;

    k = (k < n - k) ? k : n - k; // To have the minimum between k and n-k

    for (int i = 0; i < k; ++i) {
        res *= (n - i);
        res /= (i + 1);
    }

    return res;
}

/**
  * \fn void generateCombinations(int k, int *combination, int depth, int start, int **result, int *resultIndex)
  * \brief generate all combinations of k elements
  * \param [(int) k] the number of elements
  * \param [(int*) combination] the current combination
  * \param [(int) depth] the depth of the recursion
  * \param [(int) start] the index of the first element
  * \param [(int**) result] the array of combinations
  * \param [(int*) resultIndex] the index of the current combination in the array
*/
void generateCombinations(int k, int *combination, int depth, int start, int **result, int *resultIndex) {
    if (depth == k) {
        for (int i = 0; i < k; i++) {
            result[*resultIndex][i] = combination[i];
        }
        (*resultIndex)++;
        return;
    }

    for (int i = start; i <= SIZE; i++) {
        combination[depth] = i;
        generateCombinations(k, combination, depth + 1, i + 1, result, resultIndex);
    }
}

/**
  * \fn static void print_kuplet(int kuplet[], int k)
  * \brief Print the content of a k-uplet
  *
  * \param [(int*) kuplet] The k-uplet
  * \param [(int) k] Size of the k-uplet
  * \return nothing
  */
static void print_kuplet(int kuplet[], int k) {
    printf("(");
    for (int i = 0; i < k; i++){
        printf("%d", kuplet[i]);
        if(i == k-1) {
            printf(")\n");
        } else {
            printf(", ");
        }

    }
}

/**
  * \fn bool checkContent(cases* cell, int* values, int k)
  * \brief Checks if a cell contains one of the value from the kuplet
  * \param [(cases*) cell] a cell
  * \param [(int*) values] The array of values
  * \param [int k] The size of the k-uplet
  *
*/
bool checkContent(cases* cell, int* values, int k){
    bool result = false;
    int j = 0;
    while (!result && j<k){
        if (getnote(cell-> notes, values[j])){
            result = true;
        }
        j++;
    }

    return result;
}


/**
  * \fn static bool isIncludedInTab(int* values, int k, int value)
  * \brief Checks if the value is included in the array of values
  * \param [(int*) values] The array of values
  * \param [int k] The size of the k-uplet
  * \param [(int) value] The value to check
  *
*/
static bool isIncludedInTab(int* values, int k, int value) {
    for (int i = 0; i < k; i++) {
        if (values[i] == value) {
            return true;
        }
    }

    return false;
}

/**
  * \fn static short unsigned removeOtherNotes(short unsigned notes, int* values, int k)
  * \brief Removes the other notes of the cell that are not in the k-uplet
  * \param [(short unsigned) notes] The notes of the cell
  * \param [(int*) values] The array of values
  * \param [(int) k] Size of the k-uplet
  * \return the new notes of the k-uplet
*/
static short unsigned removeOtherNotes(cases *cell, int* values, int k){
    int nb=0;
    for (int i = 1; i <= SIZE; i++){
        if (!isIncludedInTab(values, k, i)){
            if (getnote(cell->notes,i)){
                cell->notes = setnote0(cell->notes, i);
                nb=1;
            }
        }
    }
    return nb;
}

/**
  * \fn static int manageKuplet(cases* tab, int* values, int k, int nbCells)
  * \brief Manage the k-uplet
  * \param [(cases*) tab] The array of cells
  * \param [(int*) values] The array of values
  * \param [(int) k] The size of the k-uplet
  * \param [(int) nbCells] The number of cells that contains values of the k-uplet
  * \return The number of adds
*/
static int manageKuplet(cases* tab, int* values, int k, int nbCells){
    int nb=0;
    if(nbCells == k) {
        //printf("%d-uplet caché %d\n", k, nbCells);
        for (int j = 0; j < SIZE; j++){
            cases* cell = &tab[j];
            if (checkContent(cell, values, k)){
                nb+=removeOtherNotes(cell, values, k);
            }
        }
    } else {
        //printf("%d-uplet nu %d\n", k, nbCells);
        for (int i = 0; i < SIZE; i++){
            cases* cell = &tab[i];
            if (!isNaiked(k, values, cell)){
                for (int j = 0; j < k; j++){
                    if (getnote(cell->notes, values[j])){
                        cell->notes = setnote0(cell->notes, values[j]);
                        nb=1;
                    }
                }
            }
        }
    }

    return nb;
}

/**
  * \fn static int checkKuplet(cases* tab, int* values, int k)
  * \brief Checks if the k-uplet was found in the grid
  * \param [(cases*) tab] The array of cells
  * \param [(int*) values] The array of values
  * \param [(int) k] Size of the k-uplet
  * \return The number of adds
*/
static int checkKupletInGrid(grid rows, int* values, int k) {
    int nb=0;
    // Gestion des lignes
    for (int i = 0; i < SIZE; i++){
        int nbCells = isKuplet(k, values, rows[i]);
        if(nbCells != -1){
            //printNotesOfRow(rows[i]);
            nb+=manageKuplet(rows[i], values, k, nbCells);
            //printf("Found a %d-uplet on row %d \n", k, i+1);
            //printNotesOfRow(rows[i]);
        }
    }

    // Gestion des colonnes
    grid columns = allocateGrid2D();
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            columns[i][j] = rows[j][i];
        }

    }

    for (int i = 0; i < SIZE; i++){
        int nbCells = isKuplet(k, values, columns[i]);
        if(nbCells != -1){
            //printNotesOfRow(columns[i]);
            nb+=manageKuplet(columns[i], values, k, nbCells);
            //printf("Found a %d-uplet on column %d \n", k, i+1);
            //printNotesOfRow(columns[i]);
        }
    }

    // Gestion des zones
    grid sudoku = allocateGrid2D();
    for (int l = 0; l < SIZE; l++){
        for (int i = 0; i < SIZE_SQUARE; i++){
            for (int j = 0; j < SIZE_SQUARE; j++){
                sudoku[l][j + i * SIZE_SQUARE] = rows[i + (l / SIZE_SQUARE) * SIZE_SQUARE][j + (l % SIZE_SQUARE) * SIZE_SQUARE];
            }

        }
    }

    for (int i = 0; i < SIZE; i++){
        int nbCells = isKuplet(k, values, sudoku[i]);
        if(nbCells != -1){
            //printNotesOfRow(sudoku[i]);
            nb+=manageKuplet(sudoku[i], values, k, nbCells);
            //printf("Found a %d-uplet on block %d \n", k, i+1);
            //printNotesOfRow(sudoku[i]);
        }

    }
    free_grid(sudoku,SIZE);
    free_grid(columns,SIZE);
    return nb;
}

static int countNonZeroNotes(grid sudoku) {
    int count = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            count += tabNotes[get_notes_of_case(getCell(sudoku,i,j))];
        }
    }
    return count;
}
/**
  * \fn static int findKuplet(grid sudoku, int k)
  * \brief Finds all k-uplets in the sudoku grid
  * \param [(grid) sudoku] The sudoku
  * \param [(int) k] Size of the k-uplets
  * \return The numbers of adds
*/
int findKuplet(grid sudoku, int k){
    int nb=0;
    int before = countNonZeroNotes(sudoku);
    int combination[k];
    int totalCombinations = bino(SIZE, k);

    int **result = (int **)malloc(totalCombinations * sizeof(int *));
    for (int i = 0; i < totalCombinations; i++) {
        result[i] = (int *)malloc(k * sizeof(int));
    }

    int resultIndex = 0;
    generateCombinations(k, combination, 0,1, result, &resultIndex);

    for (int i = 0; i < totalCombinations; i++) {
        //printf("Testing kuplet : ");
        //print_kuplet(result[i], k);
        nb+=checkKupletInGrid(sudoku, result[i], k);
    }

    for (int i = 0; i < totalCombinations; i++) {
        free(result[i]);
    }
    free(result);
    int after = countNonZeroNotes(sudoku);
    //printf("nb = %d k = %d\n",before-after,k);
    return before-after;
}

static bool isDifferent(int ind, int start_block_y, int size) {
    if (size == 0) {
        return false; 
    }

    if (ind != start_block_y + size) {
        return true;
    }

    return isDifferent(ind, start_block_y, size - 1);
}

void boxKReduction_line(grid sudoku, int num, int block_x, int block_y,int k) {
    int start_block_x= block_x*SIZE_SQUARE;
    int start_block_y= block_y*SIZE_SQUARE;

    for (int i = start_block_x; i < (start_block_x+ SIZE_SQUARE); i++) { //La ligne du carré
        int k_line = 0;
        bool pointe = true;
        bool box = true;
        for (int j = start_block_y;  j < (start_block_y+SIZE_SQUARE); j++) { //La colonne du carré
        
            cases *cell_line = getCell(sudoku, i, j);

            if (getnote(cell_line->notes, num)) {
                k_line++;
            }

            if (k_line >= k) {
                for (int ind = 0; ind < SIZE; ind++) {
                    if (ind != start_block_y && ind != start_block_y + 1 && ind != start_block_y + 2) { //pour ne pas prendre en compte les valeurs ou il y a peut etre la box isDifferent(ind,block_x)
                        cases *cellInLine = getCell(sudoku, i, ind);
                        if (getnote(cellInLine->notes, num)) {
                            box = false;
                        }
                    }

                    if (start_block_x + ind % SIZE_SQUARE != i) { //pour ne pas prendre en compte les x de la ligne ou il y a peut etre le poitant
                        cases *cellInBox = getCell(sudoku, block_x*SIZE_SQUARE + ind % SIZE_SQUARE,block_y*SIZE_SQUARE + ind / SIZE_SQUARE);
                        if (getnote(cellInBox->notes, num)) {
                            pointe = false;
                        }
                    }
                }
                if (pointe && !box) {
                    for (int ind = 0; ind < SIZE; ind++) {
                        if (!isDifferent(ind,start_block_y,SIZE_SQUARE)) { //pour ne pas prendre en compte les x de la ligne ou il y a peut etre le poitant (block_x + ind % SIZE_SQUARE !=i   isDifferent(ind,block_x)
                            cases *cellInLine = getCell(sudoku, i,ind);
                            if (getnote(cellInLine->notes, num)) {
                                cellInLine->notes=setnote0(cellInLine->notes,num);
                            }
                        }
                    }
                    //printf("Pointe dans line\n");

                }
                if (box && !pointe) {
                    for (int ind = 0; ind < SIZE; ind++) {
                        if ( block_x*SIZE_SQUARE + ind % SIZE_SQUARE !=i) { //pour ne pas prendre en compte les x de la ligne ou il y a peut etre le poitant of block_y+ind/SIZE_SQUARE)
                            cases *cellInLine = getCell(sudoku, block_x*SIZE_SQUARE + ind % SIZE_SQUARE,block_y*SIZE_SQUARE+ind/SIZE_SQUARE);
                            if (getnote(cellInLine->notes, num)) {
                                cellInLine->notes=setnote0(cellInLine->notes,num);
                            }
                        }
                    }
                    //printf("Box dans line\n");
                }
            }
        }
    }
}

void  boxKReduction_col(grid sudoku, int num, int block_x, int block_y,int k) {
    int start_block_x= block_x*SIZE_SQUARE;
    int start_block_y= block_y*SIZE_SQUARE;

    for (int j = start_block_y;  j < (start_block_y+SIZE_SQUARE); j++)  { //La colonne du carré
        int k_col=0;
        bool pointe = true;
        bool box = true;

        for (int i = start_block_x; i < (start_block_x+ SIZE_SQUARE); i++){ //La ligne du carré

            cases *cell_col = getCell(sudoku, i, j);
            if (getnote(cell_col->notes, num)) {
                k_col++;
            }
            if (k_col>= k) {
                for (int ind = 0; ind < SIZE; ind++) {
                    if (isDifferent(ind,block_x,SIZE_SQUARE)) { //pour ne pas prendre en compte les valeurs ou il y a peut etre la box
                        cases *cellInLine = getCell(sudoku, ind, j);
                        if (getnote(cellInLine->notes, num)) {
                            box = false;
                        }

                    }

                    if (start_block_y + ind / SIZE_SQUARE !=j) { //pour ne pas prendre en compte les x de la ligne ou il y a peut etre le poitant
                        cases *cellInBox = getCell(sudoku, block_x * SIZE_SQUARE + ind % SIZE_SQUARE,block_y * SIZE_SQUARE + ind / SIZE_SQUARE);
                        if (getnote(cellInBox->notes, num)) {
                            pointe = false;
                        }
                    }
                }
            
                if (pointe && k_col>=k && !box) {
                    for (int ind = 0; ind < SIZE; ind++) {
                        if ( ind!= block_x*SIZE_SQUARE && ind != block_x*SIZE_SQUARE+1 && ind !=block_x*SIZE_SQUARE+2) { //pour ne pas prendre en compte les x de la ligne ou il y a peut etre le poitant (block_x + ind % SIZE_SQUARE !=i
                            cases *cellInCol = getCell(sudoku, ind,j);
                            if (getnote(cellInCol->notes, num)) {
                                cellInCol->notes= setnote0(cellInCol->notes,num);
                            }
                        }
                    }
                    //printf("Pointe dans colonnea pour num: %d, pos_X: %d, pos_Y: %d\n",num,i,j);

                }
                if (box && k_col>=2 && !pointe) {
                    for (int ind = 0; ind < SIZE; ind++) {
                        if ( block_y*SIZE_SQUARE+(ind/SIZE_SQUARE) !=j) { //pour ne pas prendre en compte les x de la ligne ou il y a peut etre le poitant (block_x + ind % SIZE_SQUARE !=i
                            cases *cellInCol = getCell(sudoku, block_x*SIZE_SQUARE + ind % SIZE_SQUARE,block_y*SIZE_SQUARE+ind/SIZE_SQUARE);
                            if (getnote(cellInCol->notes, num)) {
                                cellInCol->notes=setnote0(cellInCol->notes,num);
                            }
                        }
                    }
                    //printf("box dans colonne pour num: %d, pos_X: %d, pos_Y: %d \n",num,i,j);
                }
            }
        }
    }
}

int boxKReduction(grid sudoku,int k) {
    int before = countNonZeroNotes(sudoku);

    for (int num = 1; num <= SIZE; num++) {
        for (int block_x = 0; block_x < SIZE_SQUARE; block_x++) {
            for (int block_y = 0; block_y < SIZE_SQUARE; block_y++) {
                boxKReduction_col(sudoku,num,block_x, block_y,k);
                boxKReduction_line(sudoku,num,block_x, block_y,k);
            }
        }
    }

    int after = countNonZeroNotes(sudoku);
    return after - before;
}

int xWing(grid sudoku){
    int before = countNonZeroNotes(sudoku);
    int tabx[2];
    int taby[2];
    for (int i = 0; i < SIZE; i++){
        for(int x = 0; x<SIZE; x++){
            int k = 0;
            int r = 0;
            for(int j = 0; j<SIZE; j++){
                cases *cellX = getCell(sudoku,i,j);
                cases *cellY = getCell(sudoku,j,i);
                if(getnote(cellX->notes,x)){
                    k++;
                    if(k == 1){
                        tabx[0] = j;
                        //printf("(x-wing) trouver 1er : %d en (%d, %d)\n",x,i,tabx[0]);
                    }else{
                        if(k == 2){
                        tabx[1] = j;
                        //printf("(X-wing) trouver 2eme : %d en (%d, %d)\n",x,i,tabx[1]);
                        }
                    }
                }
                if(getnote(cellY->notes,x)){
                    r++;
                    if(r == 1){
                        taby[0] = j;
                        //printf("(Y-wing) trouver 1er : %d en (%d, %d)\n",x,i,taby[0]);
                    }else{
                        if(r == 2){
                        taby[1] = j;
                        //printf("(Y-wing) trouver 2eme : %d en (%d, %d)\n",x,i,taby[1]);
                        }
                    }
                }
            }
            if(k == 2){
                cases *cellx1 = getCell(sudoku,i,tabx[0]);
                cases *cellx2 = getCell(sudoku,i,tabx[1]);
                int l = i+1;
                bool continu = true;
                while((l<SIZE) && continu){
                    int m = 0;
                    for(int c = 0; c<SIZE; c++){
                        cases *cell = getCell(sudoku,l,c);
                        if(getnote(cell->notes,x)){
                            m++;
                        }
                    }
                    if(m == 2){
                        cases *cell1 = getCell(sudoku,l,tabx[0]);
                        cases *cell2 = getCell(sudoku,l,tabx[1]);
                        if(getnote(cell1->notes,x) && getnote(cell2->notes,x)){
                            //printf("(X-wing) correspondance ligne %d en pos %d et %d   ===============\n",l,tabx[0], tabx[1]);
                            for(int line = 0; line<SIZE; line++){
                                    cases *check_cell1 = getCell(sudoku,line,tabx[0]);
                                    cases *check_cell2 = getCell(sudoku,line,tabx[1]);
                                if(check_cell1!=cell1 && check_cell1!=cellx1 && getnote(check_cell1->notes,x)){
                                    check_cell1->notes = setnote0(check_cell1->notes,x);
                                }
                                if(check_cell2!=cell2 && check_cell2!=cellx2 && getnote(check_cell2->notes,x)){
                                    check_cell2->notes = setnote0(check_cell2->notes,x);
                                }
                            }
                        }
                        continu = false;
                    }
                    l++;
                }
            }
            if(r == 2){
                cases *celly1 = getCell(sudoku,tabx[0],i);
                cases *celly2 = getCell(sudoku,tabx[1],i);
                int l = i+1;
                bool continu = true;
                while((l<SIZE) && continu){
                    int m = 0;
                    for(int c = 0; c<SIZE; c++){
                        cases *cell = getCell(sudoku,c,l);
                        if(getnote(cell->notes,x)){
                            m++;
                        }
                    }
                    if(m==2){
                        cases *cell1 = getCell(sudoku,taby[0],l);
                        cases *cell2 = getCell(sudoku,taby[1],l);
                        if(getnote(cell1->notes,x) && getnote(cell2->notes,x)){
                            //printf("(Y-wing) correspondance ligne %d en pos %d et %d   ===============\n",l,taby[0], taby[1]);
                            for(int col = 0; col<SIZE; col++){
                                    cases *check_cell1 = getCell(sudoku,taby[0],col);
                                    cases *check_cell2 = getCell(sudoku,taby[1],col);
                                if(check_cell1!=cell1 && check_cell1!=celly1 && getnote(check_cell1->notes,x)){
                                    check_cell1->notes = setnote0(check_cell1->notes,x);
                                }
                                if(check_cell2!=cell2 && check_cell2!=celly2 && getnote(check_cell2->notes,x)){
                                    check_cell2->notes = setnote0(check_cell2->notes,x);
                                }
                            }
                        }
                        continu = false;
                    }
                    l++;
                }
            }
        }
    }
    int after = countNonZeroNotes(sudoku);
    return before-after;
}

bool isSafe(grid sudoku, int x, int y, int value) {
    short unsigned int block_start_x = x - x % SIZE_SQUARE;
    short unsigned int block_start_y = y - y % SIZE_SQUARE;

    for (short unsigned int i = 0; i < SIZE; i++) {
        cases *cell_row = getCell(sudoku,x,i);
        if (i != y && get_value_of_case(cell_row) == value) {
            return false;
        }
        cases *cell_col = getCell(sudoku,i,y);
        if (i != x && get_value_of_case(cell_col) == value) {
            return false;
        }
        short unsigned int block_x = block_start_x + i / SIZE_SQUARE;
        short unsigned int block_y = block_start_y + i % SIZE_SQUARE;
        cases *cell_block = getCell(sudoku,block_x,block_y);
        if ((block_x != x || block_y != y) && get_value_of_case(cell_block) == value) {
            return false;
        }
    }
}

bool findEmptyCell(grid sudoku, int* row, int* col) {
    for (*row = 0; *row < SIZE; (*row)++) {
        for (*col = 0; *col < SIZE; (*col)++) {
            if (get_value_of_case(getCell(sudoku, *row, *col)) == 0)
                return true;
        }
    }
    return false;
}


bool solveSudoku(grid sudoku) {
    int row, col;

    if (!findEmptyCell(sudoku, &row, &col))
        return true; 


    for (int num = 1; num <= SIZE; num++) {
        if (isSafe(sudoku, row, col, num)) {
            set_value_of_case(getCell(sudoku, row, col), num);

            if (solveSudoku(sudoku))
                return true; 

            set_value_of_case(getCell(sudoku, row, col), 0);
        }
    }
    return false;
}

void backtracking(grid sudoku){
    solveSudoku(sudoku);
}

int x_wing(grid sudoku, bool isForLine){
    int before = countNonZeroNotes(sudoku);
    int tab[2];
    if(isForLine){
        //printf("Starting X-Wing\n");
        for (int i = 0; i < SIZE; i++){
            for(int x = 0; x<SIZE; x++){
                int k = 0;
                for(int j = 0; j<SIZE; j++){
                    cases *cellX = getCell(sudoku,i,j);
                    if(getnote(cellX->notes,x)){
                        k++;
                        if(k == 1){
                            tab[0] = j;
                        }else{
                            if(k == 2){
                                tab[1] = j;
                            }
                        }
                    }
                }
                if(k == 2){
                    cases *cellx1 = getCell(sudoku,i,tab[0]);
                    cases *cellx2 = getCell(sudoku,i,tab[1]);
                    int l = i+1;
                    bool continu = true;
                    while((l<SIZE) && continu){
                        int m = 0;
                        for(int c = 0; c<SIZE; c++){
                            cases *cell = getCell(sudoku,l,c);
                            if(getnote(cell->notes,x)){
                                m++;
                            }
                        }
                        if(m == 2){
                            cases *cell1 = getCell(sudoku,l,tab[0]);
                            cases *cell2 = getCell(sudoku,l,tab[1]);
                            if(getnote(cell1->notes,x) && getnote(cell2->notes,x)){
                                //printf("(x-wing) line matching %d pos %d and %d\n",l,tab[0], tab[1]);
                                for(int line = 0; line<SIZE; line++){
                                        cases *check_cell1 = getCell(sudoku,line,tab[0]);
                                        cases *check_cell2 = getCell(sudoku,line,tab[1]);
                                    if(check_cell1!=cell1 && check_cell1!=cellx1 && getnote(check_cell1->notes,x)){
                                        check_cell1->notes = setnote0(check_cell1->notes,x);
                                    }
                                    if(check_cell2!=cell2 && check_cell2!=cellx2 && getnote(check_cell2->notes,x)){
                                        check_cell2->notes = setnote0(check_cell2->notes,x);
                                    }
                                }
                            }
                            continu = false;
                        }
                        l++;
                    }
                }
            }
        }
    }else{
        //printf("Starting Y-Wing\n");
        for (int i = 0; i < SIZE; i++){
            for(int x = 0; x<SIZE; x++){
                int k = 0;
                for(int j = 0; j<SIZE; j++){
                    cases *cellX = getCell(sudoku,j,i);
                    if(getnote(cellX->notes,x)){
                        k++;
                        if(k == 1){
                            tab[0] = j;
                        }else{
                            if(k == 2){
                                tab[1] = j;
                            }
                        }
                    }
                }
                if(k == 2){
                    cases *celly1 = getCell(sudoku,tab[0],i);
                    cases *celly2 = getCell(sudoku,tab[1],i);
                    int l = i+1;
                    bool continu = true;
                    while((l<SIZE) && continu){
                        int m = 0;
                        for(int c = 0; c<SIZE; c++){
                            cases *cell = getCell(sudoku,c,l);
                            if(getnote(cell->notes,x)){
                                m++;
                            }
                        }
                        if(m == 2){
                            cases *cell1 = getCell(sudoku,tab[0],l);
                            cases *cell2 = getCell(sudoku,tab[1],l);
                            if(getnote(cell1->notes,x) && getnote(cell2->notes,x)){
                                //printf("(y-wing) column matching %d pos %d and %d\n",l,tab[0], tab[1]);
                                for(int line = 0; line<SIZE; line++){
                                        cases *check_cell1 = getCell(sudoku,tab[0],line);
                                        cases *check_cell2 = getCell(sudoku,tab[1],line);
                                    if(check_cell1!=cell1 && check_cell1!=celly1 && getnote(check_cell1->notes,x)){
                                        check_cell1->notes = setnote0(check_cell1->notes,x);
                                    }
                                    if(check_cell2!=cell2 && check_cell2!=celly2 && getnote(check_cell2->notes,x)){
                                        check_cell2->notes = setnote0(check_cell2->notes,x);
                                    }
                                }
                            }
                            continu = false;
                        }
                        l++;
                    }
                }
            }
        }
    }
    int after = countNonZeroNotes(sudoku);
    return before-after;
}
