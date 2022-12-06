/*
Author: Zachary Crimmel
Start Date: Dec 5, 2022
Last Updated: Dec6, 2022

From the Rogue/Nethack RPG tutorial by badcodinghabits on YouTube
*/

#include <ncurses.h>
#include <stdlib.h>

typedef struct Room{
    int xPosition;
    int yPosition;
    int width;
    int height;
    // Monster ** monsters;
    // Item ** items;


}Room;

typedef struct Player
{
    int xposition;
    int yposition;
    int health;
    // Room * room;
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

    // mvprintw(13, 13, "--------");
    // mvprintw(14, 13, "|......|");
    // mvprintw(15, 13, "|......|");
    // mvprintw(16, 13, "|......|");
    // mvprintw(17, 13, "|......|");
    // mvprintw(18, 13, "--------");

    rooms[0] = createRoom(13, 13, 6, 8);
    drawRoom(rooms[0]);

    // mvprintw(2, 40, "--------");
    // mvprintw(3, 40, "|......|");
    // mvprintw(4, 40, "|......|");
    // mvprintw(5, 40, "|......|");
    // mvprintw(6, 40, "|......|");
    // mvprintw(7, 40, "--------");

    rooms[1] = createRoom(40, 2, 6, 8);
    drawRoom(rooms[1]);

    // mvprintw(10, 40, "------------");
    // mvprintw(11, 40, "|..........|");
    // mvprintw(12, 40, "|..........|");
    // mvprintw(13, 40, "|..........|");
    // mvprintw(14, 40, "|..........|");
    // mvprintw(15, 40, "------------");

    rooms[2] = createRoom(40, 10, 6, 12);
    drawRoom(rooms[2]);

    return rooms;
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
    int newY;
    int newX;
    switch (input)
    {

    //Move up
    case 'w':
    case 'W':
        newY = user->yposition -1;
        newX = user->xposition;
        break;

    //Move down
    case 's':
    case 'S':
        newY = user->yposition +1;
        newX = user->xposition;
        break;

    //Move left
    case 'a':
    case 'A':
        newY = user->yposition;
        newX = user->xposition-1;
        break;

    //Move right
    case 'd':
    case 'D':
        newY = user->yposition;
        newX = user->xposition+1;
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
            move(user->yposition, user->xposition);
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

Room * createRoom(int x, int y, int height, int width){
    Room * newRoom;
    newRoom = malloc(sizeof(Room));

    newRoom->xPosition = x;
    newRoom->yPosition = y;
    newRoom->height = height;
    newRoom->width = width;

    return newRoom;
}

int drawRoom(Room * room){
    int x;
    int y;

    /*Draw top and bottom*/
    for(x = room->xPosition; x < room->xPosition+room->width;x++){
        mvprintw(room->yPosition, x, "-"); /* Top */
        mvprintw(room->yPosition + room->height - 1, x, "-"); /* Bottom */
    }

    /* Draw floors and side walls */
    for(y = room->yPosition + 1; y < room->yPosition + room->height - 1; y++){
        /* Draw side walls */
        mvprintw(y, room->xPosition, "|");
        mvprintw(y, room->xPosition + room->width - 1, "|");
        for(x = room->xPosition + 1; x < room->xPosition + room->width - 1; x++){
            mvprintw(y, x, ".");
        }
    }

    return 1;
}