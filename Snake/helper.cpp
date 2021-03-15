#include "helper.h"

void clearscreen()
{
    COORD coord;
    coord.X = 0;
    coord.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

helper::helper() {
    map = new char[2700];
    mapSize = 2700;
    L = 0;
    R = 1;
    D = 0;
    U = 0;
    A = 0;
    tail = 1; //Actually it will not have a tail until it eats first apple
    x = 100; //Position of snake at the beggining
    y = 0;
}

helper::~helper() {
    delete[] map;
}

void helper::Pineapple() {
    map[z] = ' ';
    if (Dollars % 8 != 0 || Dollars == 0)
        //Bonus apple - every 8 normal apples eaten ,so we need to check - generate an apple or a bonus apple
    {
        while (map[z] != ' ' && z % 100 != 0 && (z - (z / 100)) % 99 != 0);
        //Keep generating new coordinates of pineapple until that place is empty
        {
            z = rand() % mapSize + 1;
        }

        map[z] = char(3);
        //(z(z/50)) % 49 != 0 that means ,if z isn't 49+50n (49,99,149,199...)
    } //Logic ftw ,yeh?:D

    else //BONUS APPLE
    {
        while (map[z] != ' ' && z % 100 != 0 && (z - (z / 100)) % 99 != 0);
        //Keep generating new coordinates of pineapple until that place is empty
        {
            z = rand() % mapSize + 1;
        }
        map[z] = char(5);
    }
}

void helper::Start()
{
    // populate array
    for (int p = 0; p < mapSize; p++)
    {
        map[p] = ' ';
    }

    // plot snake head
    map[x] = char(153);
    Pineapple();
    Graphics();
}

void helper::KeyEntry() {
    if (_kbhit()) {
        char key = _getch();
        switch (key)
        {
        case 'd':
            //cases below,nothing special ,you should understand that easily
            //,but let me give a simple explanation of first case:
        {
            if (L == 0) //So if a player has clicked 'd' ,then.1:We check if snake is not
            //going left,because how can she turn right,if she's going left?Teleporting?..
            {
                L = 0, U = 0, D = 0, //Left = false UP = false Down = false
                    R = 1; //Right = true !
            }
            break; //We break it,end of the case.Identic with other cases..
        }

        case 'w':
        {
            if (D == 0)
            {
                L = 0, D = 0, R = 0,
                    U = 1;
            }
            break;
        }

        case 'a':
        {
            if (R == 0)
            {
                D = 0, U = 0, R = 0,
                    L = 1;
            }
            break;
        }

        case 's':
        {
            if (U == 0)
            {
                L = 0, U = 0, R = 0,
                    D = 1;
            }
            break;
        }

        }
    }
}

void helper::Graphics()
{
    std::cout << "\n";
    for (int u = 0; u < 100; u++) //Top border
    {
        std::cout << char(219);
    }

    std::cout << std::endl;

    for (int i = 0; i < mapSize; i++) //DRAWING BOARD!~
    {
        if (i % 100 == 0 && i != 0)
        {
            std::cout << std::endl; // Safe play area
        }
        if (i % 100 == 0 || (i - (i / 100)) % 99 == 0) // left and right borders
        {
            map[i] = char(178);
            std::cout << map[i];
        }
        else if (map[i] != char(153) && map[i] != map[z])
        {
            std::cout << map[i];
        }
        else if (i == z)
        {
            std::cout << map[i];
        }
        else
        {
            std::cout << map[i];
        }

    }

    std::cout << std::endl;
    for (int u = 0; u < 100; u++) //Bottom border
    {
        std::cout << char(219);
    }

    if (U == 1 || D == 1)
    { //WITHOUT IT ,GOING UP/DOWN IS MUCH FASTER THAN < >
        Sleep(20);
    }
    if (map[z] == char(5)) //If apple is bonus ,then start decreasing time to get it!
    {
        time--;
        if (time == 0) //If you were too slow ,you lose a dollar and a new apple is generated
        {
            Dollars++;
            time = 40;
            Pineapple();
        }
    }

    clearscreen();
    GameLogic();
}

void helper::GameLogic()
{
    past.insert(past.begin(), x); //Inserting past x position to vector
    KeyEntry();
    if (R == 1) //If snake is going right
    {
        x++;
        Sleep(19);
    }
    else if (L == 1) //If snake is going left
    {
        x--;
        Sleep(19);
    }
    else if (U == 1) //If snake is going up
    {
        x -= 100;
    }
    else //If snake is going down(only case left)
    {
        x += 100;
    }

    if (map[x] == char(219) || x % 100 == 0 || x > mapSize || x < 0 || (x - (x / 100)) % 99 == 0)  //If it hits herself or border...
    {
        GameOver();
        return;
    }

    if (map[x] == char(153))
        //If it eats an pineapple also A becomes true,that means the
        //very end of the snake(tail) will not be deleted ( line 276 ) for 1 frame
    {
        A = true;
        tail++; //It eats a big apple ,so snake becomes heavier
   
        Dollars++; //Apple had some dollars in it,congrulations!
    }

    else if (map[x] == char(5)) //Same,but maybe it has just eaten bonus apple?
    {
        A = true;
        tail++;
      
        Bonus += time;
    }

    map[x] = char(153);
    //When it touches apple - head becomes an apple,so we need to change it.
    if (A == false) //If snake has just eaten an apple
    {
        y = past[past.size() - tail]; //D E L E T I N G past tail from the map!
        map[y] = ' ';
    }

    A = false; //So the next time line 270 will work again,if apple is no eaten ///
    if (tail != 1)
    {
        for (int u = past.size() - 2; u > 0; u--)
        {
            past[u + 1] = past[u];
        } //Try your best to understand what's happening here,
        //let's say this is an exercise for you from Foxefde
        past.erase(past.end() - tail);
    }
    else
    {
        past.erase(past.begin()); //I could do it without erases,
    } //
    Graphics();
}

int helper::GameOver()
{
    Sleep(1500);
    system("cls");
    std::cout << std::endl << "Oops...You earned " << Dollars + Bonus << " Dollars...";
    //Better luck next time.
    Sleep(1800);
    return 0;
}