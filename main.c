#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char grid[10][10] = {
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
};
int targets[17][2] = {
    {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1},
    {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}
};
int targets_counter = 0;
int seed = 0;
int shotsFired = 0;
int hits = 0;

//flags
int doneShooting = 0;
int doneSelecting = 0;
int doneConfirm = 0;
int choosingRow = 0;
int chosenRow = -1;
int choosingColumn = 0;
int chosenColumn = -1;

void printBoard() {
    if (choosingColumn) {
        char symbol = '|';
        for (int i = 0; i < 2; i++) {
            printf("      ");
            for (int j = 0; j < 10; j++) {
                if (j == chosenColumn || chosenColumn == -1) {
                    printf("   %c", symbol);
                } else {
                    printf("    ");
                }
            }
            symbol = 'v';
            printf("\n");
        }
    }
    printf("         1   2   3   4   5   6   7   8   9   10\n");
    for (int i = 0; i < 10; i++) {
        char output[50];
        snprintf(output, sizeof(output), "     %i | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |", (i + 1),
                 grid[i][0], grid[i][1], grid[i][2], grid[i][3], grid[i][4], grid[i][5], grid[i][6], grid[i][7],
                 grid[i][8], grid[i][9]);

        if (choosingRow) {
            if (i == chosenRow || chosenRow == -1) {
                output[0] = '-';
                output[1] = '-';
                output[2] = '>';
            }
        }


        if (i == 9) {
            for (int j = 3; j < sizeof(output); j++) {
                output[j] = output[j + 1];
            }
        }

        printf("       -----------------------------------------\n");
        printf("%s\n", output);
    }
    printf("       -----------------------------------------\n");


    // printf("       -----------------------------------------\n");
    // printf("-->  1 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |\n", grid[0][0], grid[0][1], grid[0][2], grid[0][3], grid[0][4], grid[0][5], grid[0][6], grid[0][7], grid[0][8], grid[0][9]);
    // printf("       -----------------------------------------\n");
    // printf("-->  2 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |\n", grid[1][0], grid[1][1], grid[1][2], grid[1][3], grid[1][4], grid[1][5], grid[1][6], grid[1][7], grid[1][8], grid[1][9]);
    // printf("       -----------------------------------------\n");
    // printf("-->  3 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |\n", grid[2][0], grid[2][1], grid[2][2], grid[2][3], grid[2][4], grid[2][5], grid[2][6], grid[2][7], grid[2][8], grid[2][9]);
    // printf("       -----------------------------------------\n");
    // printf("-->  4 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |\n", grid[3][0], grid[3][1], grid[3][2], grid[3][3], grid[3][4], grid[3][5], grid[3][6], grid[3][7], grid[3][8], grid[3][9]);
    // printf("       -----------------------------------------\n");
    // printf("-->  5 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |\n", grid[4][0], grid[4][1], grid[4][2], grid[4][3], grid[4][4], grid[4][5], grid[4][6], grid[4][7], grid[4][8], grid[4][9]);
    // printf("       -----------------------------------------\n");
    // printf("-->  6 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |\n", grid[5][0], grid[5][1], grid[5][2], grid[5][3], grid[5][4], grid[5][5], grid[5][6], grid[5][7], grid[5][8], grid[5][9]);
    // printf("       -----------------------------------------\n");
    // printf("-->  7 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |\n", grid[6][0], grid[6][1], grid[6][2], grid[6][3], grid[6][4], grid[6][5], grid[6][6], grid[6][7], grid[6][8], grid[6][9]);
    // printf("       -----------------------------------------\n");
    // printf("-->  8 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |\n", grid[7][0], grid[7][1], grid[7][2], grid[7][3], grid[7][4], grid[7][5], grid[7][6], grid[7][7], grid[7][8], grid[7][9]);
    // printf("       -----------------------------------------\n");
    // printf("-->  9 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |\n", grid[8][0], grid[8][1], grid[8][2], grid[8][3], grid[8][4], grid[8][5], grid[8][6], grid[8][7], grid[8][8], grid[8][9]);
    // printf("       -----------------------------------------\n");
    // printf("--> 10 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |\n", grid[9][0], grid[9][1], grid[9][2], grid[9][3], grid[9][4], grid[9][5], grid[9][6], grid[9][7], grid[9][8], grid[9][9]);
    // printf("       -----------------------------------------\n");
}

void rngShip(int size) {
    //rng 5 ships
    //1 two long 2 three long 1 four long 1 five long#
    int done = 0;
    while (!done) {
        srand(time(NULL) + (seed * 2));
        //printf("%i %i\n", rand() % 10, rand() % 10);
        int rng[] = {rand() % 10, rand() % 10};
        //printf("%i\n", rand() % 4);
        srand(time(NULL) + seed);
        int dir = rand() % 4;
        //printf("%i %i %i %i\n", rng[0], rng[1], dir, size);

        //2 long ship
        switch (dir) {
            //if 0 go right
            //1 go down
            //2 go left
            //3 go up
            case 0:
                if ((rng[1] + size - 1) < 9) {
                    int nope = 0;
                    int temp = rng[1];
                    for (int i = 0; i <= targets_counter && !nope; i++) {
                        //loop thru each occupied square
                        //printf("%i %i %i %i %i %i\n", rng[0], targets[i][0], temp, targets[i][1], nope, i);
                        temp = rng[1];
                        for (int j = 0; j < size; j++, temp++) {
                            //loop thru each square the new ship would take up
                            if (rng[0] == targets[i][0] && temp == targets[i][1]) {
                                nope = 1;
                            }
                            // printf("rngX:%i listX:%i rngY:%i listY:%i nope:%i i:%i\n", rng[0], targets[i][0], temp, targets[i][1], nope, i);
                            //temp++;
                        }
                    }
                    if (nope) {
                        //printf("hi");
                        seed++;
                        break; //CHECK IF THIS REBOOTS THE WHILE LOOP
                    }
                    // printf("%i %i %i %i\n", rng[0], rng[1], dir, size);
                    for (int i = 0; i < size; i++) {
                        //grid[rng[0]][rng[1]] = 'O';
                        targets[targets_counter][0] = rng[0];
                        targets[targets_counter][1] = rng[1];
                        targets_counter++;
                        rng[1]++;
                    }
                    done = !done;
                    seed++;
                }
                seed++;

                break;
            case 1:
                if ((rng[0] + size - 1) < 9) {
                    int nope = 0;
                    int temp = rng[0];
                    for (int i = 0; i <= targets_counter && !nope; i++) {
                        temp = rng[0];
                        for (int j = 0; j < size; j++, temp++) {
                            if (temp == targets[i][0] && rng[1] == targets[i][1]) {
                                nope = 1;
                            }
                            //temp++;
                            // printf("rngX:%i listX:%i rngY:%i listY:%i nope:%i i:%i\n", temp, targets[i][0], rng[1], targets[i][1], nope, i);
                        }
                    }
                    if (nope) {
                        //printf("hi");
                        seed++;
                        break; //CHECK IF THIS REBOOTS THE WHILE LOOP
                    }
                    // printf("%i %i %i %i\n", rng[0], rng[1], dir, size);
                    for (int i = 0; i < size; i++) {
                        //grid[rng[0]][rng[1]] = 'O';
                        targets[targets_counter][0] = rng[0];
                        targets[targets_counter][1] = rng[1];
                        targets_counter++;
                        rng[0]++;
                    }
                    done = !done;
                    seed++;
                }
                seed++;
                break;
            case 2:
                if ((rng[1] - size + 1) > 0) {
                    int nope = 0;
                    int temp = rng[1];
                    for (int i = 0; i <= targets_counter && !nope; i++) {
                        //printf("hi\n");
                        temp = rng[1];
                        for (int j = 0; j < size; j++, temp--) {
                            if (rng[0] == targets[i][0] && temp == targets[i][1]) {
                                nope = 1;
                            }
                            //temp--;
                            // printf("rngX:%i listX:%i rngY:%i listY:%i nope:%i i:%i\n", rng[0], targets[i][0], temp, targets[i][1], nope, i);
                        }
                    }
                    if (nope) {
                        //printf("hi");
                        seed++;
                        break; //CHECK IF THIS REBOOTS THE WHILE LOOP
                    }
                    // printf("%i %i %i %i\n", rng[0], rng[1], dir, size);
                    for (int i = 0; i < size; i++) {
                        //grid[rng[0]][rng[1]] = 'O';
                        targets[targets_counter][0] = rng[0];
                        targets[targets_counter][1] = rng[1];
                        targets_counter++;
                        rng[1]--;
                    }
                    done = !done;
                    seed++;
                }
                seed++;
                break;
            case 3:
                if ((rng[0] - size + 1) > 0) {
                    int nope = 0;
                    int temp = rng[0];
                    for (int i = 0; i <= targets_counter && !nope; i++) {
                        temp = rng[0];
                        for (int j = 0; j < size; j++, temp--) {
                            if (temp == targets[i][0] && rng[1] == targets[i][1]) {
                                nope = 1;
                            }
                            //temp--;
                            //printf("rngX:%i listX:%i rngY:%i listY:%i nope:%i i:%i\n", temp, targets[i][0], rng[1], targets[i][1], nope, i);
                        }
                    }
                    if (nope) {
                        //printf("hi");
                        seed++;
                        break; //CHECK IF THIS REBOOTS THE WHILE LOOP
                    }
                    // printf("%i %i %i %i\n", rng[0], rng[1], dir, size);
                    for (int i = 0; i < size; i++) {
                        //grid[rng[0]][rng[1]] = 'O';
                        targets[targets_counter][0] = rng[0];
                        targets[targets_counter][1] = rng[1];
                        targets_counter++;
                        rng[0]--;
                    }
                    done = !done;
                    seed++;
                }
                seed++;
                break;
        }
        //break;
    }
}

void initialize() {
    // for (int i = 0; i < 10; i++) {
    //     for (int j = 0; j < 10; j++) {
    //         grid[i][j] = ' ';
    //     }
    // }

    rngShip(2);
    rngShip(3);
    //sleep(1);
    rngShip(3);
    rngShip(4);
    rngShip(5);
}

int main(void) {
    printf("loading...\n");
    initialize();
    printf(
        "Welcome to battleships!\nIn this game you select a square to shoot\nto see if there is a ship hiding there.\nTry and sink all 5 ships with the lowest shots possible!\n");

    // for (int i = 0; i < 17; i++) {
    //     printf("%i %i\n", targets[i][0], targets[i][1]);
    //     grid[targets[i][0]][targets[i][1]] = 'O';
    // }
    //printf("%i\n", targets_counter);
    int gameOver = 0;
    while (!gameOver) {
        printBoard();
        char input[3] = "-1";
        printf("Misses: X\tHits: O\nShots fired: %i\nPlease select from the following:\n1. shoot\n2. forfeit\n",
               shotsFired);
        fflush(stdin);
        fgets(input, sizeof(input), stdin);
        //printf("%s, %i\n", input, input == "1");
        //printf("%i\n", input);
        //printf("%i\n", input);
        if (strcmp(input, "1\n") == 0) {
            // switch (input) {
            //     case "1"://shoot

            fflush(stdin);
            doneShooting = 0;
            while (!doneShooting) {
                doneConfirm = 0;
                while (!doneSelecting) {
                    choosingRow = 1;
                    chosenRow = -1;
                    printBoard();
                    printf("Please select the row number to shoot:\n");
                    fflush(stdin);
                    fgets(input, sizeof(input), stdin);
                    if (strcmp(input, "1\n") == 0 || strcmp(input, "2\n") == 0 || strcmp(input, "3\n") == 0 ||
                        strcmp(input, "4\n") == 0 || strcmp(input, "5\n") == 0 || strcmp(input, "6\n") == 0 ||
                        strcmp(input, "7\n") == 0 || strcmp(input, "8\n") == 0 || strcmp(input, "9\n") == 0 || strcmp(
                            input, "10") == 0) {
                        // switch (input) {
                        //     case "1":
                        //     case "2":
                        //     case "3":
                        //     case "4":
                        //     case "5":
                        //     case "6":
                        //     case "7":
                        //     case "8":
                        //     case "9":
                        //     case "10":
                        chosenRow = atoi(input) - 1;
                        doneSelecting = 1;
                    } else {
                        //printf("%i\n", chosenRow);
                        // break;

                        // default:
                        printf("Please select a valid row number!\n");
                        // break;
                    }
                }
                fflush(stdin);


                doneSelecting = 0;
                while (!doneSelecting) {
                    choosingColumn = 1;
                    chosenColumn = -1;
                    printBoard();
                    printf("Please select the column number to shoot:\n");
                    fflush(stdin);
                    fgets(input, sizeof(input), stdin);
                    //input = fgetc(stdin) - 48;
                    if (strcmp(input, "1\n") == 0 || strcmp(input, "2\n") == 0 || strcmp(input, "3\n") == 0 ||
                        strcmp(input, "4\n") == 0 || strcmp(input, "5\n") == 0 || strcmp(input, "6\n") == 0 ||
                        strcmp(input, "7\n") == 0 || strcmp(input, "8\n") == 0 || strcmp(input, "9\n") == 0 || strcmp(
                            input, "10") == 0) {
                        // switch (input) {
                        //     case "1":
                        //     case "2":
                        //     case "3":
                        //     case "4":
                        //     case "5":
                        //     case "6":
                        //     case "7":
                        //     case "8":
                        //     case "9":
                        //     case "10":

                        chosenColumn = atoi(input) - 1;
                        //printf("%i", doneConfirm);
                        doneSelecting = 1;
                    } else {
                        //printf("%i\n", chosenRow);
                        // break;

                        // default:
                        printf("Please select a valid column number!\n");
                        // break;
                    }
                }
                fflush(stdin);


                //printf("%i %i\n", choosingColumn, chosenColumn);

                while (!doneConfirm) {
                    //printf("hi");
                    printBoard();
                    printf("You sure you want to shoot there?(Y/N)\n");
                    fflush(stdin);
                    input[0] = fgetc(stdin);
                    switch (input[0]) {
                        case 'y':
                        case 'Y':
                            //printf("yes");
                            for (int i = 0; i < 17; i++) {
                                if (targets[i][0] == chosenRow && targets[i][1] == chosenColumn) {
                                    grid[chosenRow][chosenColumn] = 'O';
                                    hits++;
                                    shotsFired++;
                                    break;
                                } else {
                                    grid[chosenRow][chosenColumn] = 'X';
                                }
                            }
                            doneConfirm = 1;
                            doneShooting = 1;
                            shotsFired++;
                            break;
                        case 'N':
                        case 'n':
                            //printf("no");
                            doneConfirm = 1;
                            doneShooting = 0;
                            doneSelecting = 0;
                            choosingRow = 0;
                            chosenRow = -1;
                            choosingColumn = 0;
                            chosenColumn = -1;
                            break;
                        default:
                            //printf("lol");
                            printf("invalid input!\n");
                    }
                    fflush(stdin);
                }
                printf("\n");
            }

            doneShooting = 0;
            doneSelecting = 0;
            doneConfirm = 0;
            choosingRow = 0;
            chosenRow = -1;
            choosingColumn = 0;
            chosenColumn = -1;
            if (hits == 17) {
                printBoard();
                printf("You win!\n");
                gameOver = 1;
            }
        } else if (strcmp(input, "2\n") == 0) {
            // break;
            // case 2://forfeit
            for (int i = 0; i < 17; i++) {
                if (grid[targets[i][0]][targets[i][1]] != 'O') {
                    grid[targets[i][0]][targets[i][1]] = 'i';
                }
            }
            printBoard();
            printf("you lost!");
            //show end board with ship locations here
            gameOver = 1;
        } else {
            printf("invalid input!\n");
        }
        // break;
    }

    return 0;
}
