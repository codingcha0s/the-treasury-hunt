#include "game.h"
#include <stdio.h>
#include <stdlib.h>

void printMapTiles(int mapTiles[MAP_SIZE][MAP_SIZE]) {
    for (int x = 0; x < MAP_SIZE; x++) {
        for (int y = 0; y < MAP_SIZE; y++) {
            switch (mapTiles[x][y]) {
                case EMPTY: printf("-\t"); break;  // Empty
                case WALL: printf("[W]\t"); break;  // Wall
                case TRAP: printf(YELLOW "[?]\t" RESET); break;  // Trap
                case HEAL: printf(RED "[+]\t" RESET); break;  // Heal
                case TREASURY: printf(YELLOW "[?]\t" RESET); break;  // Treasury
                case PLAYER: printf( GREEN "(^u^)\t" RESET); break;  // Player
                case ENEMY: printf("-\t"); break;  // Enemy
                default: printf("%i\t", mapTiles[x][y]); break; // Unknown
            }
        }
        printf("\n");
    }
}

void initializeMap(int mapTiles[MAP_SIZE][MAP_SIZE]) {
    for (int x = 0; x < MAP_SIZE; x++) {
        for (int y = 0; y < MAP_SIZE; y++) {
            mapTiles[x][y] = EMPTY;  // Fill the map with empty tiles
        }
    }
}

void placeWalls(int mapTiles[MAP_SIZE][MAP_SIZE]) {
    for (int x = 0; x < MAP_SIZE; x++) {
        int wallsThisRowMax = rand() % 3 + 1; // Random number of walls per row (1 to 3)
        int wallsThisRow = 0;

        while (wallsThisRow < wallsThisRowMax) {
            int randomPosition = rand() % MAP_SIZE;  // Random position in the row
            if (mapTiles[x][randomPosition] == EMPTY) { // Only place a wall if it's empty
                mapTiles[x][randomPosition] = WALL;
                wallsThisRow++;
            }
        }
    }
}

void placeTraps(int mapTiles[MAP_SIZE][MAP_SIZE]) {
    int trapsThisGame = 0;
    while (trapsThisGame < TRAP_AMOUNT) {
        int randomRow = rand() % MAP_SIZE;
        int randomCol = rand() % MAP_SIZE;
        if (mapTiles[randomRow][randomCol] == EMPTY) {
            mapTiles[randomRow][randomCol] = TRAP;
            trapsThisGame++;
        }
    }
}

void placeHeals(int mapTiles[MAP_SIZE][MAP_SIZE]) {
    int healsThisGame = 0;
    while (healsThisGame < MAP_SIZE / 2) {  // Fewer heals than traps
        int randomRow = rand() % MAP_SIZE;
        int randomCol = rand() % MAP_SIZE;
        if (mapTiles[randomRow][randomCol] == EMPTY) {
            mapTiles[randomRow][randomCol] = HEAL;
            healsThisGame++;
        }
    }
}

void placeEnemies(int mapTiles[MAP_SIZE][MAP_SIZE]) {
    int enemiesThisGame = 0;
    while (enemiesThisGame < MAP_SIZE / 2) {  // Fewer enemies than traps
        int randomRow = rand() % MAP_SIZE;
        int randomCol = rand() % MAP_SIZE;
        if (mapTiles[randomRow][randomCol] == EMPTY) {
            mapTiles[randomRow][randomCol] = ENEMY;
            enemiesThisGame++;
        }
    }
}

void placeTreasury(int mapTiles[MAP_SIZE][MAP_SIZE]) {
    int randRow, randCol;
    do {
        randRow = rand() % MAP_SIZE;
        randCol = rand() % MAP_SIZE;
    } while (mapTiles[randRow][randCol] != EMPTY);  // Find an empty spot
    mapTiles[randRow][randCol] = TREASURY;  // Set treasury position
}

void placePlayer(int mapTiles[MAP_SIZE][MAP_SIZE], int *playerRow, int *playerCol) {
    do {
        *playerRow = rand() % MAP_SIZE;
        *playerCol = rand() % MAP_SIZE;
    } while (mapTiles[*playerRow][*playerCol] != EMPTY);  // Find an empty spot
    mapTiles[*playerRow][*playerCol] = PLAYER;  // Set player position
}

void printWelcome() {
    printf("Welcome to <The Treasury Hunt>\n\n");
    printf("How to Play:\n");
    printf("\tNavigate through the map using WASD and find the hidden treasury without dying :P\n");
    printf("\n");
    printf("Legend:\n");
    printf("\t" GREEN "(^u^)" RESET " => Your character, move it along the map\n");
    printf("\t[W] => Walls, you cant move trough them\n");
    printf("\t" RED "[+]" RESET " => Heals, giving you +25 Health\n");
    printf("\t" YELLOW "[?]" RESET " => Trap or Treasury\n");
    printf("\t- => The Path; remember where you moved along to avoid enemies\n");
    printf("\n\n");
    system("pause");
    system("clear");
}

void printGameOver() {
    printf(
    "  ######      ###    ##     ## ########     #######  ##     ## ######## ########  \n"
    " ##    ##    ## ##   ###   ### ##          ##     ## ##     ## ##       ##     ## \n"
    " ##         ##   ##  #### #### ##          ##     ## ##     ## ##       ##     ## \n"
    " ##   #### ##     ## ## ### ## ######      ##     ## ##     ## ######   ########  \n"
    " ##    ##  ######### ##     ## ##          ##     ##  ##   ##  ##       ##   ##   \n"
    " ##    ##  ##     ## ##     ## ##          ##     ##   ## ##   ##       ##    ##  \n"
    "  ######   ##     ## ##     ## ########     #######     ###    ######## ##     ## \n"
    );
}

char getUserInput() {
    char input;
    printf("\nMovement:\tW = UP, A = LEFT, S = DOWN, D = RIGHT, Q = QUIT\nYour Choice: \t");
    scanf(" %c", &input);
    return input;
}

int getDamage() {
    return rand() % TRAP_DAMAGE_MAX;
}

int doFight(int playerHealth) {
    int round = 1;
    int accumulatedDamage = 0;
    int enemyHealth = 50;

    printf("Oh no! An enemy (%i Health) appeared, you're starting a fight!\n\n", enemyHealth);

    while (playerHealth > 0 && enemyHealth >= 0) {
        int roundPlayerDamage = rand() % 50; // Damage taken by Enemy
        int roundEnemyDamage = rand() % 25; // Damage taken by Player

        printf("Round %d:\n", round);
        printf("You attack, the enemy takes %i (%i => %i) damage!\n", roundPlayerDamage, enemyHealth, enemyHealth-roundPlayerDamage);
        enemyHealth-=roundPlayerDamage;
        if (enemyHealth > 0) {
            printf("The enemy attacks, you take %i (%i => %i) damage!\n", roundEnemyDamage, playerHealth, playerHealth-roundEnemyDamage);
            accumulatedDamage += roundEnemyDamage;
            playerHealth -= roundEnemyDamage;
        }
        round++;
    }
    return accumulatedDamage;
}

