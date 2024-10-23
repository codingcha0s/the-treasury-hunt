#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define MAP_SIZE 20
#define TRAP_AMOUNT (MAP_SIZE) // more traps as the map size increases
#define TRAP_DAMAGE_MAX 50
#define HEAL_AMOUNT 25
// asd
typedef enum {
    EMPTY = 0,
    WALL = 1,
    TRAP = 2,
    HEAL = 3,
    TREASURY = 4,
    ENEMY = 5,
    PLAYER = -1
} TileType;

void printWelcome() {
    printf("Welcome to <The Treasury Hunt>\n\n");
    printf("How to Play:\n");
    printf("\tNavigate through the map using WASD and find the hidden treasury without dying :P\n");
    printf("\n");
    printf("Legend:\n");
    printf("\t[W] => Walls, you cant move trough them\n");
    printf("\t[+] => Heals, giving you +25 Health\n");
    printf("\t[?] => Trap or Treasury\n");
    printf("\t- => The Path; remember where you moved along to avoid enemies\n");
    printf("\n\n");
    system("pause");
    system("clear");
}
void printMapTiles(int mapTiles[MAP_SIZE][MAP_SIZE]) {
    for (int x = 0; x < MAP_SIZE; x++) {
        for (int y = 0; y < MAP_SIZE; y++) {
            switch (mapTiles[x][y]) {
                case EMPTY: printf("-\t"); break;  // Empty
                case WALL: printf("[W]\t"); break;  // Wall
                case TRAP: printf("[?]\t"); break;  // Trap
                case HEAL: printf("[+]\t"); break;  // Heal
                case TREASURY: printf("[?]\t"); break;  // Treasury
                case PLAYER: printf("(^u^)\t"); break;  // Player
                case ENEMY: printf("<E>\t"); break;  // Enemy
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
int dofight(int playerHealth) {
    int round = 1;
    int accumulatedDamage = 0;
    int enemyHealth = 50;

    printf("Oh no! An enemy (%i Health) appeared, you're starting a fight!\n\n", enemyHealth);

    while (playerHealth > 0 && enemyHealth >= 0) {
        int roundPlayerDamage = rand() % 50; // Damage taken by Enemy
        int roundEnemyDamage = rand() % 25; // Damage taken by Player
        accumulatedDamage+= roundEnemyDamage;

        printf("Round %d:\n", round);
        printf("You attack, the enemy takes %i (%i => %i) damage!\n", roundPlayerDamage, enemyHealth, enemyHealth-roundPlayerDamage);
        enemyHealth-=roundPlayerDamage;
        if (enemyHealth > 0) {
            printf("The enemy attacks, you take %i (%i => %i) damage!\n", roundEnemyDamage, playerHealth, playerHealth-roundEnemyDamage);
            playerHealth-=roundEnemyDamage;
        }
        round++;
    }
    return accumulatedDamage;
}

int main(void) {
    srand(time(NULL)); // init randomization
    printWelcome();

    int playerHealth = 100;
    int mapTiles[MAP_SIZE][MAP_SIZE];
    initializeMap(mapTiles);
    placeWalls(mapTiles);
    placeTraps(mapTiles);
    placeHeals(mapTiles);
    placeTreasury(mapTiles);
    placeEnemies(mapTiles);

    int playerRow, playerCol;
    placePlayer(mapTiles, &playerRow, &playerCol);

    char input;
    int gameRunning = 1;
    while (gameRunning) {
        system("cls");  // clear screen
        printMapTiles(mapTiles);

        printf("_____________________________________________________________________________\n");
        printf("Health:\t\t%i", playerHealth);
        input = getUserInput();

        // Calculate new position based on input
        int newRow = playerRow;
        int newCol = playerCol;
        if (input == 'w' || input == 'W') newRow--;  // Move up
        if (input == 's' || input == 'S') newRow++;  // Move down
        if (input == 'a' || input == 'A') newCol--;  // Move left
        if (input == 'd' || input == 'D') newCol++;  // Move right
        if (input == 'q' || input == 'Q') gameRunning = 0;  // Quit game

        // Check if new position is within bounds and not a wall
        if (newRow >= 0 && newRow < MAP_SIZE && newCol >= 0 && newCol < MAP_SIZE) {
            if (mapTiles[newRow][newCol] != WALL) {  // Not a wall
                // Handle special tiles
                if (mapTiles[newRow][newCol] == TRAP) {
                    int trapDamage = getDamage();
                    playerHealth -= trapDamage;
                    printf("You stepped on a trap! You've received %i damage, remaining health: %i\n", trapDamage, playerHealth);
                    if (playerHealth <= 0) {
                        // system("cls");
                        printGameOver();
                        printf("You have been defeated.\n\n");
                        gameRunning = 0;
                    }
                    system("pause");
                } else if (mapTiles[newRow][newCol] == HEAL) {
                    playerHealth += HEAL_AMOUNT;
                    if (playerHealth > 100) playerHealth = 100;  // Cap health at 100
                    printf("You found a healing spot! +%i health, remaining health: %i\n", HEAL_AMOUNT, playerHealth);
                    system("pause");
                } else if (mapTiles[newRow][newCol] == TREASURY) {
                    printf("You found the treasury, you've won!\n");
                    system("pause");
                    gameRunning = 0;
                } else if (mapTiles[newRow][newCol] == ENEMY) {
                    int damageFromEnemy = dofight(playerHealth);
                    playerHealth-= damageFromEnemy;
                    if (playerHealth <= 0) {
                        // system("cls");
                        printGameOver();
                        printf("You have been defeated.\n\n");
                        gameRunning = 0;
                    } else {
                        printf("Congratulation, you've defeated the enemy!\n");
                    }
                    system("pause");
                }

                // Move player to the new position
                mapTiles[playerRow][playerCol] = EMPTY;  // Clear old position
                mapTiles[newRow][newCol] = PLAYER;        // Set new position
                playerRow = newRow;
                playerCol = newCol;
            } else {
                printf("You hit a wall! Try another direction.\n");
                system("pause");
            }
        } else {
            printf("Out of bounds! Try another direction.\n");
            system("pause");
        }
    }

    return 0;
}