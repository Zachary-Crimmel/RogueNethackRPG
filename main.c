/*
Author: Zachary Crimmel
Start Date: Dec 5, 2022
Last Updated: January 17, 2023

From the Rogue/Nethack RPG tutorial by badcodinghabits on YouTube
*/

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

typedef struct Position{
    int x;
    int y;
}Position;

typedef struct Room{
    Position position;
    int width;
    int height;

    Position ** doors;
}Room;

typedef struct Player
{
    Position position;
    int health;
} Player;

int screenSetUp();
Room ** mapSetUp();
Player *playerSetUp();
int handleInput(int input, Player *user);
int playerMove(int y, int x, Player * user);
int checkPosition(int y, int x, Player * user);
int drawRoom(Room * room);

/*Room functions*/

Room * createRoom(int x, int y, int height, int width);

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

Room ** mapSetUp()
{
    Room ** rooms;
    rooms = malloc(sizeof(Room)*6);

    rooms[0] = createRoom(13, 13, 6, 8);
    drawRoom(rooms[0]);

    rooms[1] = createRoom(40, 2, 6, 8);
    drawRoom(rooms[1]);

    rooms[2] = createRoom(40, 10, 6, 12);
    drawRoom(rooms[2]);

    return rooms;
}

int screenSetUp()
{
    initscr();

    // Makes sure that user input doesn't show up on the screen
    noecho();

    refresh();

    return 1;
}

Player *playerSetUp()
{
    Player *newPlayer;
    newPlayer = malloc(sizeof(Player));

    newPlayer->position.x = 14;
    newPlayer->position.y = 14;
    newPlayer->health = 20;

    playerMove(newPlayer->position.y, newPlayer->position.x, newPlayer);

    return newPlayer;
}

int handleInput(int input, Player * user)
{
    int newY;
    int newX;
    switch (input)
    {

    //Move up
    case 'w':
    case 'W':
        newY = user->position.y -1;
        newX = user->position.x;
        break;

    //Move down
    case 's':
    case 'S':
        newY = user->position.y +1;
        newX = user->position.x;
        break;

    //Move left
    case 'a':
    case 'A':
        newY = user->position.y;
        newX = user->position.x-1;
        break;

    //Move right
    case 'd':
    case 'D':
        newY = user->position.y;
        newX = user->position.x+1;
        break;

    default:
        break;
    }
    checkPosition(newY, newX, user);

}

// Check what is at next position
int checkPosition(int newY, int newX, Player * user){
    int space;
    switch (mvinch(newY, newX)){
        case '.':
            playerMove(newY, newX, user);
            break;
        default:
            move(user->position.y, user->position.x);
            break;
    }
}

int playerMove(int y, int x, Player * user){
    mvprintw(user->position.y, user->position.x, ".");

    user->position.x = x;
    user->position.y = y;

    mvprintw(user->position.y, user->position.x, "@");
    move(user->position.y, user->position.x);
}

Room * createRoom(int x, int y, int height, int width){
    Room * newRoom;
    newRoom = malloc(sizeof(Room));

    newRoom->position.x = x;
    newRoom->position.y = y;
    newRoom->height = height;
    newRoom->width = width;

    srand(time(NULL));

    newRoom->doors = malloc(sizeof(Position) * 4);

    /* Top doors*/
    newRoom->doors[0] = malloc(sizeof(Position));
    newRoom->doors[0]->x = rand() % width + newRoom->position.x;
    newRoom->doors[0]->y = newRoom->position.y;

    /* Bottom doors */
    newRoom->doors[1] = malloc(sizeof(Position));
    newRoom->doors[1]->x = rand() % (width - 2) + (newRoom->position.x + 1);
    newRoom->doors[1]->y = newRoom->position.y + newRoom->height - 1;

    /* Left doors */
    newRoom->doors[2] = malloc(sizeof(Position));
    newRoom->doors[2]->y = rand() % height + newRoom->position.y;
    newRoom->doors[2]->x = newRoom->position.x;

    /* Right doors */
    newRoom->doors[3] = malloc(sizeof(Position));
    newRoom->doors[3]->y = rand() % height + newRoom->position.y;
    newRoom->doors[3]->x = newRoom->position.x;

    return newRoom;
}

int drawRoom(Room * room){
    int x;
    int y;

    /*Draw top and bottom*/
    for(x = room->position.x; x < room->position.x+room->width;x++){
        mvprintw(room->position.y, x, "-"); /* Top */
        mvprintw(room->position.y + room->height - 1, x, "-"); /* Bottom */
    }

    /* Draw floors and side walls */
    for(y = room->position.y + 1; y < room->position.y + room->height - 1; y++){
        /* Draw side walls */
        mvprintw(y, room->position.x, "|");
        mvprintw(y, room->position.x + room->width - 1, "|");
        for(x = room->position.x + 1; x < room->position.x + room->width - 1; x++){
            mvprintw(y, x, ".");
        }
    }

    /* Draw doors */
    mvprintw(room->doors[0]->y, room->doors[0]->x, "+");
    mvprintw(room->doors[1]->y, room->doors[1]->x, "+");
    mvprintw(room->doors[2]->y, room->doors[2]->x, "+");
    mvprintw(room->doors[3]->y, room->doors[3]->x, "+");

    return 1;
}