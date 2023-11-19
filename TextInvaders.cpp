
#include <iostream>
#include "TextInvaders.h"
#include "CursesUtils.h"
#include <ctime>
#include <cmath>
#include <cstring>

using namespace std;

void InitGame(Game &game);
void InitPlayer(const Game &game, Player &player);
void ResetPlayer(const Game &game, Player &player);
void ResetMissile(Player &player);
int HandleInput(const Game &game, Player &player);
void UpdateGame(const Game &game, Player &player);
void DrawGame(const Game &game, const Player &player, Shield shields[], int numberOfShields);
void MovePlayer(const Game& game, Player& player, int dx);
void PlayerShoot(Player& player);
void DrawPlayer(const Player& player, const char* sprite[]);
void UpdateMissile(Player& player);
void InitShields(const Game& game, Shield shields[], int numberOfShields);
void CleanUpShields(Shield shields[], int numberOfShields);
void DrawShields(const Shield shields[], int numberOfShields);

int main()
{

    Game game;
    Player player;
    Shield shields[NUM_SHIELDS];

    InitializeCurses(true);

    InitGame(game);
    InitPlayer(game, player);
    InitShields(game, shields, NUM_SHIELDS);

    bool quit = false;
    int input;

    clock_t lastTime = clock();

    while (!quit)
    {
        input = HandleInput(game, player);
        if (input != 'q')
        {

            clock_t currentTime = clock();

            clock_t dt = currentTime - lastTime;

            if(dt > CLOCKS_PER_SEC/FPS)
            {
                lastTime = currentTime;
                UpdateGame(game, player);
                ClearScreen();
                DrawGame(game, player, shields, NUM_SHIELDS);
                RefreshScreen();
            }
        }
        else
        {
            quit = true;
        }
    }

    CleanUpShields(shields, NUM_SHIELDS);
    ShutdownCurses();

    return 0;
}

void InitGame(Game &game)
{
    game.windowSize.width = ScreenWidth();
    game.windowSize.height = ScreenHeight();
    game.level = 1;
    game.currentState = GS_PLAY;
}

void InitPlayer(const Game &game, Player &player)
{
    player.lives = MAX_NUMBER_OF_LIVES;
    player.spriteSize.height = PLAYER_SPRITE_HEIGHT;
    player.spriteSize.width = PLAYER_SPRITE_WIDTH;
    ResetPlayer(game, player);
}

void ResetPlayer(const Game &game, Player &player)
{
    player.position.x = game.windowSize.width / 2 - player.spriteSize.width / 2;
    player.position.y = game.windowSize.height - player.spriteSize.height - 1;
    player.animation = 0;
    ResetMissile(player);
}

void ResetMissile(Player &player)
{
    player.missile.x = NOT_IN_PLAY;
    player.missile.y = NOT_IN_PLAY;
}

int HandleInput(const Game &game, Player &player)
{
    int input = GetChar();
    switch (input)
    {
    case 'q':
        return input;
    case AK_LEFT:
        MovePlayer(game, player, -PLAYER_MOVEMENT_AMOUNT);
        break;
    case AK_RIGHT:
        MovePlayer(game, player, PLAYER_MOVEMENT_AMOUNT);
        break;
    case ' ':
        PlayerShoot(player);
    }
    return input;
}

void UpdateGame(const Game &game, Player &player)
{
    UpdateMissile(player);
}

void DrawGame(const Game &game, const Player &player, Shield shields[], int numberOfShields)
{
    DrawPlayer(player, PLAYER_SPRITE);
    DrawShields(shields, numberOfShields);
}

void MovePlayer(const Game& game, Player& player, int dx)
{
    if(player.position.x + dx >= 0 && player.position.x + player.spriteSize.width + dx < game.windowSize.width)
    {
        player.position.x += dx;
    };
}

void PlayerShoot(Player& player)
{
    if(player.missile.x == NOT_IN_PLAY)
    {
        player.missile.x = player.position.x + player.spriteSize.width / 2;
        player.missile.y = player.position.y - 1;
    }
}

void DrawPlayer(const Player& player, const char* sprite[])
{
    DrawSprite(player.position.x, player.position.y, sprite, player.spriteSize.height);
    DrawCharacter(player.missile.x, player.missile.y, PLAYER_MISSLE_SPRITE);

    if(player.missile.x != NOT_IN_PLAY)
    {
        DrawCharacter(player.missile.x, player.missile.y, PLAYER_MISSLE_SPRITE);
    }
}

void UpdateMissile(Player& player)
{
    if(player.missile.y != NOT_IN_PLAY)
    {
        player.missile.y -= PLAYER_MISSLE_SPEED;
        if(player.missile.y < 0)
        {
            ResetMissile(player);
        }
    }
}

void InitShields(const Game& game, Shield shields[], int numberOfShields)
{
    int firstPaddding = ceil(float(game.windowSize.width - numberOfShields * SHIELD_SPRITE_WIDTH)/float(numberOfShields+1));
    int xPadding = floor(float(game.windowSize.width - numberOfShields * SHIELD_SPRITE_WIDTH)/float(numberOfShields+1));

    for(int i = 0; i < numberOfShields; i++)
    {
        Shield& shield = shields[i];
        shield.position.x = firstPaddding + i * (SHIELD_SPRITE_WIDTH + xPadding);
        shield.position.y = game.windowSize.height - PLAYER_SPRITE_HEIGHT - 1 - SHIELD_SPRITE_HEIGHT - 2;

        for(int row = 0; row < SHIELD_SPRITE_HEIGHT; row++)
        {
            shield.sprite[row] = new char[SHIELD_SPRITE_WIDTH + 1];
            strcpy(shield.sprite[row], SHIELD_SPRITE[row]);
        }   
    }
}

void CleanUpShields(Shield shields[], int numberOfShields)
{
    for(int i = 0; i < numberOfShields; i++)
    {
        Shield& shield = shields[i];
        for(int row = 0; row < SHIELD_SPRITE_HEIGHT; row++)
        {
            delete[] shield.sprite[row];
        }
    }
}

void DrawShields(const Shield shields[], int numberOfShields)
{
    for(int i = 0; i < numberOfShields; i++)
    {
        const Shield& shield = shields[i];
        DrawSprite(shield.position.x, shield.position.y, (const char**)shield.sprite, SHIELD_SPRITE_HEIGHT);
    }
}