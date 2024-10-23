#ifndef GAME_H
#define GAME_H

#define MAP_SIZE 20
#define TRAP_AMOUNT (MAP_SIZE)
#define TRAP_DAMAGE_MAX 50
#define HEAL_AMOUNT 25

#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RED "\033[31m"
#define RESET "\033[0m"

typedef enum {
    EMPTY = 0,
    WALL = 1,
    TRAP = 2,
    HEAL = 3,
    TREASURY = 4,
    ENEMY = 5,
    PLAYER = -1
} TileType;

// Funktionsprototypen
void printMapTiles(int mapTiles[MAP_SIZE][MAP_SIZE]);
void initializeMap(int mapTiles[MAP_SIZE][MAP_SIZE]);
void placeWalls(int mapTiles[MAP_SIZE][MAP_SIZE]);
void placeTraps(int mapTiles[MAP_SIZE][MAP_SIZE]);
void placeHeals(int mapTiles[MAP_SIZE][MAP_SIZE]);
void placeEnemies(int mapTiles[MAP_SIZE][MAP_SIZE]);
void placeTreasury(int mapTiles[MAP_SIZE][MAP_SIZE]);
void placePlayer(int mapTiles[MAP_SIZE][MAP_SIZE], int *playerRow, int *playerCol);
void printWelcome();
void printGameOver();
char getUserInput();
int getDamage();
int doFight(int playerHealth);

#endif