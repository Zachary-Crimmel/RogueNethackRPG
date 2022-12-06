#include <ncurses.h>
#include <stdlib.h>

typedef struct Player
{
    int xposition;
    int yposition;
    int health;
} Player;

int screenSetUp();
int mapSetUp();
Player *playerSetUp();
int handleInput(int input, Player *user);
int playerMove(int y, int x, Player * user);

int main()
{
    Player *user;
    int ch;
    screenSetUp();

    mapSetUp();

    user = playerSetUp();

    // Main game loop
    while ((ch = getch()) != 'q')
    {
        handleInput(ch, user);
    }

    endwin();

    return 0;
}

int mapSetUp()
{
    mvprintw(13, 13, "--------");
    mvprintw(14, 13, "|......|");
    mvprintw(15, 13, "|......|");
    mvprintw(16, 13, "|......|");
    mvprintw(17, 13, "|......|");
    mvprintw(18, 13, "--------");

    mvprintw(2, 40, "--------");
    mvprintw(3, 40, "|......|");
    mvprintw(4, 40, "|......|");
    mvprintw(5, 40, "|......|");
    mvprintw(6, 40, "|......|");
    mvprintw(7, 40, "--------");

    mvprintw(10, 40, "------------");
    mvprintw(11, 40, "|..........|");
    mvprintw(12, 40, "|..........|");
    mvprintw(13, 40, "|..........|");
    mvprintw(14, 40, "|..........|");
    mvprintw(15, 40, "------------");
}

int screenSetUp()
{
    initscr();
    printw("Hello World!");

    // Makes sure that user input doesn't show up on the screen
    noecho();

    refresh();

    return 1;
}

Player *playerSetUp()
{
    Player *newPlayer;
    newPlayer = malloc(sizeof(Player));

    newPlayer->xposition = 14;
    newPlayer->yposition = 14;
    newPlayer->health = 20;

    playerMove(newPlayer->yposition, newPlayer->xposition, newPlayer);

    return newPlayer;
}

int handleInput(int input, Player * user)
{
    switch (input)
    {

    //Move up
    case 'w':
    case 'W':
        playerMove(user->yposition-1, user->xposition, user);
        break;

    //Move down
    case 's':
    case 'S':
        playerMove(user->yposition+1, user->xposition, user);
        break;

    //Move left
    case 'a':
    case 'A':
        playerMove(user->yposition, user->xposition-1, user);
        break;

    //Move right
    case 'd':
    case 'D':
        playerMove(user->yposition, user->xposition+1, user);
        break;

    default:
        break;
    }
}

int playerMove(int y, int x, Player * user){
    mvprintw(user->yposition, user->xposition, ".");

    user->xposition = x;
    user->yposition = y;

    mvprintw(user->yposition, user->xposition, "@");
    move(user->yposition, user->xposition);
}