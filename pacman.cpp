#include <iostream>
#include <conio.h>
#include <unistd.h>
#include <windows.h>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
using namespace std;

const int SIZE_I = 21, SIZE_J = 41;
char ground[SIZE_I][SIZE_J];
int i, j, score = 0, lives = 3;
int Pac_row = 9, Pac_Col = 4;
int G1row = 11, G1col = 19;   // fist ghost
int GG2row = 16, GG2col = 29; // second ghost

void SetCursorPosition(short int x, short int y)
{
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {x, y};
    SetConsoleCursorPosition(output, pos);
}

void RandomMap()
{
    srand(time(NULL));
    for (int i = 0; i < 40; i++)
    {
        ground[(rand() % (SIZE_I - 1) / 2) * 2 + 1][(rand() % (SIZE_J - 1) / 2) * 2 + 1] = '#';
    }
}

void initializeGround()
{

    for (int i = 0; i < SIZE_I; i++)
    {
        for (int j = 0; j < SIZE_J; j++)
        {
            if (i == Pac_row && j == Pac_Col)
            {
                ground[i][j] = 'P';
            }

            else
            {
                ground[i][j] = '.';
            }

            if (j == 0 || i == 0 || i == 20 || j == 40)
            {
                ground[i][j] = '#';
            }

            if ((i == 10 && j == 0) || (i == 10 && j == 40))
            {
                ground[i][j] = ' ';
            }
        }
    }
}
void changeSit()
{

    if (Pac_row == 10 && Pac_Col == 0)
    {

        Pac_row = 10;
        Pac_Col = 40;

        ground[10][0] = ' ';
        ground[10][40] = 'P';
    }
    else if (Pac_row == 10 && Pac_Col == 40)
    {

        Pac_row = 10;
        Pac_Col = 0;

        ground[10][40] = ' ';
        ground[10][0] = 'P';
    }
}

void printGround()
{
    SetCursorPosition(0, 0);
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 41; j++)
        {
            if (i == G1row && j == G1col)
            {
                cout << 'G';
                continue;
            }

            if (i == GG2row && j == GG2col)
            {
                cout << 'K';
                continue;
            }
            if (i == Pac_row && j == Pac_Col)
            {
                cout << 'P';
                continue;
            }
            cout << ground[i][j];
        }

        cout << endl;
    }
}

bool isFilled(int i, int j)
{
    if (ground[i][j] == '#')
    {
        return true;
    }
    return false;
}

bool ghostOnghost(int i, int j)
{
    if (ground[i][j] == 'K')
    {
        return true;
    }
    return false;
}

bool ghostOnghost2(int i, int j)
{
    if (ground[i][j] == 'G')
    {
        return true;
    }
    return false;
}

void direction1()
{
    if (isFilled(G1row - 1, G1col))
    {
        srand(time(NULL));

        int r = rand() % 3;
        switch (r)
        {
        case 1:
            if ((!isFilled(G1row + 1, G1col)) && (!ghostOnghost2(GG2row + 1, GG2col)) && (!ghostOnghost(G1row + 1, G1col)))
            {
                G1row++;
            }
            break;

        case 2:
            if ((!isFilled(G1row, G1col + 1)) && (!ghostOnghost2(GG2row, GG2col + 1)) && (!ghostOnghost(G1row, G1col + 1)))
            {
                G1col++;
            }
            break;
        case 0:

            if ((!isFilled(G1row, G1col - 1)) && (!ghostOnghost2(GG2row, GG2col - 1)) && (!ghostOnghost(G1row, G1col - 1)))
            {
                G1col--;
            }
            break;
        }
    }
}

void direction2()
{
    if (isFilled(G1row + 1, G1col))
    {
        srand(time(NULL));

        int r = rand() % 3;
        switch (r)
        {
        case 1:
            if ((!isFilled(G1row - 1, G1col)) && (!ghostOnghost2(GG2row - 1, GG2col)) && (!ghostOnghost(G1row - 1, G1col)))
            {
                G1row--;
            }
            break;

        case 2:
            if ((!isFilled(G1row, G1col + 1)) && (!ghostOnghost2(GG2row, GG2col + 1)) && (!ghostOnghost(G1row, G1col + 1)))
            {
                G1col++;
            }
            break;
        case 0:

            if ((!isFilled(G1row, G1col - 1)) && (!ghostOnghost2(GG2row, GG2col - 1)) && (!ghostOnghost(G1row, G1col - 1)))
            {
                G1col--;
            }
            break;
        }
    }
}

void direction3()
{
    if (isFilled(G1row, G1col + 1))
    {
        srand(time(NULL));

        int r = rand() % 3;
        switch (r)
        {
        case 1:
            if ((!isFilled(G1row + 1, G1col)) && (!ghostOnghost2(GG2row + 1, GG2col)) && (!ghostOnghost(G1row + 1, G1col)))
            {
                G1row++;
            }
            break;

        case 2:
            if ((!isFilled(G1row - 1, G1col)) && (!ghostOnghost2(GG2row - 1, GG2col)) && (!ghostOnghost(G1row - 1, G1col)))
            {
                G1row--;
            }
            break;
        case 0:

            if ((!isFilled(G1row, G1col - 1)) && (!ghostOnghost2(GG2row, GG2col - 1)) && (!ghostOnghost(G1row, G1col - 1)))
            {
                G1col--;
            }
            break;
        }
    }
}

void direction4()
{
    if (isFilled(G1row, G1col - 1))
    {
        srand(time(NULL));

        int r = rand() % 3;
        switch (r)
        {
        case 1:
            if ((!isFilled(G1row + 1, G1col)) && (!ghostOnghost2(GG2row + 1, GG2col)) && (!ghostOnghost(G1row + 1, G1col)))
            {
                G1row++;
            }
            break;

        case 2:
            if ((!isFilled(G1row - 1, G1col)) && (!ghostOnghost2(GG2row - 1, GG2col)) && (!ghostOnghost(G1row - 1, G1col)))
            {
                G1row--;
            }
            break;
        case 0:

            if ((!isFilled(G1row, G1col + 1)) && (!ghostOnghost2(GG2row, GG2col + 1)) && (!ghostOnghost(G1row, G1col + 1)))
            {
                G1col++;
            }
            break;
        }
    }
}

void GhostRun()
{

    // The ghost is on the bottom right
    if (G1row - Pac_row > 0 && G1col - Pac_Col > 0)
    {

        srand(time(NULL));

        int r = rand() % 2;
        switch (r)
        {
        case 1:

            if ((!isFilled(G1row - 1, G1col)) && (!ghostOnghost(G1row - 1, G1col)))
            {
                G1row--;
            }
            else
                direction1();
            break;

        default:
            if (!isFilled(G1row, G1col - 1) && (!ghostOnghost(G1row, G1col - 1)))
            {
                G1col--;
            }
            else
                direction4();
            break;
        }
    }
    // the ghost is on the top right
    else if (G1row - Pac_row < 0 && G1col - Pac_Col > 0)
    {
        srand(time(NULL));
        int r = rand() % 2;
        switch (r)
        {
        case 1:
            if ((!isFilled(G1row + 1, G1col)) && (!ghostOnghost(G1row + 1, G1col)))
            {
                G1row++;
            }
            else
                direction2();
            break;

        case 0:
            if ((!isFilled(G1row, G1col - 1)) && (!ghostOnghost(G1row, G1col - 1)))
            {
                G1col--;
            }
            else
                direction4();
            break;
        }
    }

    // The ghost is on the top left
    else if (G1row - Pac_row < 0 && G1col - Pac_Col < 0)
    {
        srand(time(NULL));
        int r = rand() % 2;
        switch (r)
        {
        case 1:
            if ((!isFilled(G1row + 1, G1col)) && (!ghostOnghost(G1row + 1, G1col)))
            {
                G1row++;
            }
            else
                direction2();
            break;

        case 0:
            if ((!isFilled(G1row, G1col + 1)) && (!ghostOnghost(G1row, G1col + 1)))
            {
                G1col++;
            }
            else
                direction3();
            break;
        }
    }

    // The ghost is on the bottom left
    else if (G1row - Pac_row > 0 && G1col - Pac_Col < 0)
    {
        srand(time(NULL));
        int r = rand() % 2;
        switch (r)
        {
        case 1:
            if ((!isFilled(G1row - 1, G1col)) && (!ghostOnghost(G1row - 1, G1col)))
            {
                G1row--;
            }
            else
                direction1();

            break;

        case 0:
            if ((!isFilled(G1row, G1col + 1)) && (!ghostOnghost(G1row - 1, G1col)))
            {
                G1col++;
            }
            else
                direction3();
            break;
        }
    }
    // The ghost is on the right
    else if (G1row == Pac_row && G1col > Pac_Col)
    {
        if ((!isFilled(G1row, G1col - 1)) && (!ghostOnghost(G1row, G1col - 1)))
        {
            G1col--;
        }
        else
            direction4();
    }
    // The ghost is on the left
    else if (G1row == Pac_row && G1col < Pac_Col)
    {
        if ((!isFilled(G1row, G1col + 1)) && (!ghostOnghost(G1row, G1col + 1)))
        {
            G1col++;
        }
        else
            direction3();
    }
    // The ghost is down
    else if (G1col == Pac_Col && G1row > Pac_row)
    {
        if ((!isFilled(G1row - 1, G1col)) && (!ghostOnghost(G1row - 1, G1col)))
        {
            G1row--;
        }
        else
            direction1();
    }
    // The ghost is above
    else if (G1col == Pac_Col && G1row < Pac_row)
    {
        if (!isFilled(G1row + 1, G1col))
        {
            G1row++;
        }
        else
            direction2();
    }
}

void Ghost2Run()
{

    // The ghost is on the bottom right
    if (GG2row - Pac_row > 0 && GG2col - Pac_Col > 0)
    {

        srand(time(NULL));

        int r = rand() % 2;
        switch (r)
        {
        case 1:

            if ((!isFilled(GG2row - 1, GG2col)) && (!ghostOnghost2(GG2row - 1, GG2col)))
            {
                GG2row--;
            }
            break;

        default:
            if ((!isFilled(GG2row, GG2col - 1)) && (!ghostOnghost2(GG2row, GG2col - 1)))
            {
                GG2col--;

                break;
            }
        }
    }
    // The ghost is on the top right
    else if (GG2row - Pac_row < 0 && GG2col - Pac_Col > 0)
    {
        srand(time(NULL));
        int r = rand() % 2;
        switch (r)
        {
        case 1:
            if ((!isFilled(GG2row + 1, GG2col)) && (!ghostOnghost2(GG2row + 1, GG2col)))
            {
                GG2row++;
            }
            break;

        case 0:
            if ((!isFilled(GG2row, GG2col - 1)) && (!ghostOnghost2(GG2row, GG2col - 1)))
            {
                GG2col--;
            }
            break;
        }
    }
    // The ghost is on the top left

    else if (GG2row - Pac_row < 0 && GG2col - Pac_Col < 0)
    {
        srand(time(NULL));
        int r = rand() % 2;
        switch (r)
        {
        case 1:
            if ((!isFilled(GG2row + 1, GG2col)) && (!ghostOnghost2(GG2row + 1, GG2col)))
            {
                GG2row++;
            }
            break;

        case 0:
            if ((!isFilled(GG2row, GG2col + 1)) && (!ghostOnghost2(GG2row, GG2col + 1)))
            {
                GG2col++;
            }
            break;
        }
    }
    // The ghost is on the bottom left

    else if (GG2row - Pac_row > 0 && GG2col - Pac_Col < 0)
    {
        srand(time(NULL));
        int r = rand() % 2;
        switch (r)
        {
        case 1:
            if ((!isFilled(GG2row - 1, GG2col)) && (!ghostOnghost2(GG2row - 1, GG2col)))
            {
                GG2row--;
            }
            break;

        case 0:
            if ((!isFilled(GG2row, GG2col + 1)) && (!ghostOnghost2(GG2row, GG2col + 1)))
            {
                GG2col++;
            }
            break;
        }
    }
    // The ghost is on the right

    else if (GG2row == Pac_row && GG2col > Pac_Col)
    {
        if ((!isFilled(GG2row, GG2col - 1)) && (!ghostOnghost2(GG2row, GG2col - 1)))
        {
            GG2col--;
        }
        else
            direction4();
    }

    // The ghost is on the left
    else if (GG2row == Pac_row && GG2col < Pac_Col)
    {
        if ((!isFilled(GG2row, GG2col + 1)) && (!ghostOnghost2(GG2row, GG2col + 1)))
        {
            GG2col++;
        }
    }

    // The ghost is down
    else if (GG2col == Pac_Col && GG2row > Pac_row)
    {
        if ((!isFilled(GG2row - 1, GG2col)) && (!ghostOnghost2(GG2row - 1, GG2col)))
        {
            GG2row--;
        }
    }
    // The ghost is above
    else if (GG2col == Pac_Col && GG2row < Pac_row)
    {
        if ((!isFilled(GG2row + 1, GG2col)) && (!ghostOnghost2(GG2row + 1, GG2col)))
        {
            GG2row++;
        }
    }
}

void move(char key)
{

    switch (key)
    {

    case 'w':
        if (isFilled(Pac_row - 1, Pac_Col) != true)
        {

            Pac_row--;
            if (Pac_row > 0)
            {
                if (ground[Pac_row][Pac_Col] == '.')
                {
                    score += 10;
                }
                ground[Pac_row + 1][Pac_Col] = ' ';
            }
        }

        break;

    case 's':
        if (isFilled(Pac_row + 1, Pac_Col) != true)
        {
            Pac_row++;

            if (Pac_row > 0)
            {

                if (ground[Pac_row][Pac_Col] == '.')
                {
                    score += 10;
                }
                ground[Pac_row - 1][Pac_Col] = ' ';
            }
        }
        break;

    case 'd':
        if (isFilled(Pac_row, Pac_Col + 1) != true)
        {
            Pac_Col++;

            if (Pac_Col > 0)
            {
                if (ground[Pac_row][Pac_Col] == '.')
                {
                    score += 10;
                }

                ground[Pac_row][Pac_Col - 1] = ' ';
            }
        }
        break;

    case 'a':
        if (isFilled(Pac_row, Pac_Col - 1) != true)
        {
            Pac_Col--;

            if (Pac_Col >= 0)
            {
                if (ground[Pac_row][Pac_Col] == '.')
                {
                    score += 10;
                }

                ground[Pac_row][Pac_Col + 1] = ' ';
            }
        }
        break;
    }
}

bool loseTime()
{
    if ((Pac_row == G1row && Pac_Col == G1col) || ( Pac_row==GG2row && Pac_Col == GG2col ))
    {
        lives--;
        Pac_row = 9, Pac_Col = 4;
        G1row = 11, G1col = 19;
        GG2row = 16, GG2col = 29;
        if (lives == 0)
        {
            cout << "lives: " << lives;
            cout << endl;
            return true;
        }
    }
    return false;
}

bool winTime()
{
    int checkpoint = 0;
    for (i = 0; i < SIZE_I; i++)
    {
        for (j = 0; j < SIZE_J; j++)
        {
            if (ground[i][j] == '.')
            {
                checkpoint++;
            }
        }
    }
    if (checkpoint == 0)
    {
        return true;
    }

    return false;
}

int main()
{
    system("cls");
    initializeGround();
    RandomMap();
    char key;

    while (true)
    {
        changeSit();

        printGround();

        GhostRun();
        if (loseTime())
        {
            cout << "Game over!" << endl
                 << "Your score is : " << score;

            break;
        }
        Ghost2Run();
        if (loseTime())
        {
            cout << "Game over!" << endl
                 << "Your score is : " << score;

            break;
        }
        cout << "lives: " << lives;
        cout << "\t\t\tScore:" << score;
        cout << endl;

        if (kbhit())
        {
            key = getch();
        }
        usleep(0.2 * 1000000);

        move(key);
        if (loseTime())
        {
            cout << "Game over!" << endl
                 << "Your score is : " << score;

            break;
        }
        if (winTime())
        {
            cout << "You win !!" << endl
                 << score;
            break;
        }
    }
    getch();
}
