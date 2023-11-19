#ifndef TEXTINVADERS_TEXTINVADERS_H
#define TEXTINVADERS_TEXTINVADERS_H

#include <vector>

const char* PLAYER_SPRITE[] = {" =A= ", "====="};

const char PLAYER_MISSLE_SPRITE = '|';

const char * SHIELD_SPRITE[] = {"/IIIII\\", "IIIIIII", "I/   \\I"};

enum{
    SHIELD_SPRITE_HEIGHT = 3,
    SHIELD_SPRITE_WIDTH = 7,
    NUM_ALIEN_ROWS = 5,
    NUM_ALIEN_COLUMNS = 11,
    MAX_NUMBER_OF_ALIEN_BOMBS = 3,
    MAX_NUMBER_OF_LIVES = 3,
    PLAYER_SPRITE_WIDTH = 5,
    PLAYER_SPRITE_HEIGHT = 2,
    NOT_IN_PLAY = -1,
    PLAYER_MOVEMENT_AMOUNT = 2,
    PLAYER_MISSLE_SPEED = 1,
    FPS = 20,
    NUM_SHIELDS = 4,

};

enum GameState {
    GS_INTRO = 0,
    GS_HIGH_SCORES,
    GS_PLAY,
    GS_PLAYER_DEAD,
    GS_WAIT,
    GS_GAME_OVER,
};

enum AlienState
{
    AS_ALIVE = 0,
    AS_DEAD,
    AS_EXPLODING
};

struct Position
{
    int x;
    int y;
};

struct Size
{
    int width;
    int height;
};

struct Player
{
    Position position;
    Position missile;
    Size spriteSize;
    int animation;
    int lives; //max 3
    int score;
};

struct Shield
{
    Position position;
    char * sprite[SHIELD_SPRITE_HEIGHT];
};

struct AlienBomb
{
    Position position;
    int animation;
};

struct AlienSwarm
{
    Position position;
    AlienState aliens[NUM_ALIEN_ROWS][NUM_ALIEN_COLUMNS];
    AlienBomb bombs[MAX_NUMBER_OF_ALIEN_BOMBS];
    Size spriteSize;
    int animation;
    int direction; // >0 = right, <0 = left
    int numberOfBombsInPlay;
    int movementTimer; // how fast the aliens move
    int explosionTimer; // how long the explosion lasts
    int numAliensLeft; // when this reaches 0, the player wins and go to next level
    int line; // the lowest line of aliens, if 0 then alien win
};

struct AlienUFO
{
    Position position;
    Size size;
    int points;
};

struct Score
{
    int score;
    std::string name;
};

struct HighScoreTable
{
    std::vector<Score> scores;
};

struct Game
{
    Size windowSize;
    GameState currentState;
    int level;

};



#endif //TEXTINVADERS_TEXTINVADERS_H
