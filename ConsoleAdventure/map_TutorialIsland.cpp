#include "map_TutorialIsland.h"
#include "checkNextBlock.h"
#include "inputHandler.h"
#include "windows.h"
#include <tuple>

void map_TutorialIsland::moveCursor(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}

void map_TutorialIsland::hideCursor()
{
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = false;
   SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

std::tuple<std::string, int, std::vector<std::string>, int, int> map_TutorialIsland::loadMap(int health, std::vector<std::string> inventory, int posX, int posY)
{
    checkNextBlock checkBlock;
    inputHandler userPos;

    hideCursor();

    playerX = userPos.returnX(map, sizeX, sizeY);
    playerY = userPos.returnY(map, sizeX, sizeY);

    map[playerY][playerX] = ' ';    //sets the player on the map upon given coords, clarified from previous map
    map[posY][posX] = '@';
    status = "*You see a house... You might be able to go inside*";

    system("cls");
    Sleep(125);

    while(running)
    {
        playerX = userPos.returnX(map, sizeX, sizeY);   //get players coordinates
        playerY = userPos.returnY(map, sizeX, sizeY);

        if(GetAsyncKeyState(0x49))  //if key I is pressed
        {

        }

        if(GetAsyncKeyState(VK_RIGHT) && !GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_UP) && !GetAsyncKeyState(VK_DOWN))
        {
            if(checkBlock.checkNext(map[playerY][playerX+1]) == true)
            {
                map[playerY][playerX] = ' ';
                map[playerY][playerX+1] = '@';

                Sleep(gameSpeed);
            }
            else
            {
                if(playerX == houseX+1 && playerY == houseY)
                {
                    posX = 1;
                    posY = 3;
                    mapToLoad = "map_TutHouse";
                    return std::make_tuple(mapToLoad, health, inventory, posX, posY);
                }
            }
        }

        if(GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_RIGHT) && !GetAsyncKeyState(VK_UP) && !GetAsyncKeyState(VK_DOWN))
        {
            if(checkBlock.checkNext(map[playerY][playerX-1]) == true)
            {
                map[playerY][playerX] = ' ';
                map[playerY][playerX-1] = '@';
                Sleep(gameSpeed);
            }
            else
            {
                if(playerX == houseX-1 && playerY == houseY)
                {
                    posX = 1;
                    posY = 3;
                   mapToLoad = "map_TutHouse";
                   return std::make_tuple(mapToLoad, health, inventory, posX, posY);
                }
            }
        }

        if(GetAsyncKeyState(VK_UP) && !GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_RIGHT) && !GetAsyncKeyState(VK_DOWN))
        {
            if(checkBlock.checkNext(map[playerY-1][playerX]) == true)
            {
                map[playerY][playerX] = ' ';
                map[playerY-1][playerX] = '@';
                Sleep(gameSpeed);
            }
            else
            {
                if(playerX == houseX && playerY-1== houseY)
                {
                    posX = 1;
                    posY = 3;
                    mapToLoad = "map_TutHouse";
                    return std::make_tuple(mapToLoad, health, inventory, posX, posY);
                }
            }
        }

        if(GetAsyncKeyState(VK_DOWN) && !GetAsyncKeyState(VK_RIGHT) && !GetAsyncKeyState(VK_UP) && !GetAsyncKeyState(VK_LEFT))
        {
            if(checkBlock.checkNext(map[playerY+1][playerX]) == true)
            {
                map[playerY][playerX] = ' ';
                map[playerY+1][playerX] = '@';
                Sleep(gameSpeed);
            }
            else
            {
                if(playerX == houseX && playerY+1 == houseY)
                {
                    posX = 1;
                    posY = 3;
                    mapToLoad = "map_TutHouse";
                    return std::make_tuple(mapToLoad, health, inventory, posX, posY);
                }
            }
        }

        for(int x = 0; x < sizeX; x++)
        {
            for(int y = 0; y < sizeY; y++)
            {
                moveCursor(x, y);
                std::cout << map[y][x];
                std::cout<<std::endl;
            }
        }
        std::cout<<std::endl;
        std::cout << status << std::endl;
        std::cout<<std::endl;
        std::cout << "health: " << health << std::endl;
    }
}
