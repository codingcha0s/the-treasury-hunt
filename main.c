#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "game.h"

int main(void) {
    srand(time(NULL)); // init randomization
    printWelcome();

    time_t start_time = time(NULL);
    int movements = 0;
    int points = 0;

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
        printf("Health:\t%i\t\tPoints:\t%i", playerHealth, points);
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
                    points+= 10;
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
                    points+= 5;
                    playerHealth += HEAL_AMOUNT;
                    if (playerHealth > 100) playerHealth = 100;  // Cap health at 100
                    printf("You found a healing spot! +%i health, remaining health: %i\n", HEAL_AMOUNT, playerHealth);
                    system("pause");
                } else if (mapTiles[newRow][newCol] == TREASURY) {
                    time_t stop_time = time(NULL);
                    points+= 25;
                    printf("You found the treasury, you've won! (Points: %i)\n", points);
                    system("pause");
                    gameRunning = 0;
                } else if (mapTiles[newRow][newCol] == ENEMY) {
                    int damageFromEnemy = doFight(playerHealth);
                    playerHealth-= damageFromEnemy;
                    if (playerHealth <= 0) {
                        // system("cls");
                        printGameOver();
                        printf("You have been defeated.\n\n");
                        gameRunning = 0;
                    } else {
                        points+= 20;
                        printf("Congratulation, you've defeated the enemy!\n");
                    }
                    system("pause");
                }

                // Move player to the new position
                mapTiles[playerRow][playerCol] = EMPTY;  // Clear old position
                mapTiles[newRow][newCol] = PLAYER;        // Set new position
                playerRow = newRow;
                playerCol = newCol;
                movements++;
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