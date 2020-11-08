#include <iostream>
#include <fstream>
#include <array>
#include <vector>

using namespace std;

// Array to contain the board
array<array<int, 9>, 9> board;

bool isValid(int X, int Y)
{
    // The quadremts the place is in
    int quadX = X / 3;
    int quadY = Y / 3;

    // Get the current value
    int n = board[X][Y];

    // Make sure the place is not empty
    if(n == 0)
    {
        return true;
    }

    // Check the quadrent for the same value
    for(int x = 3*quadX; x < 3*(quadX+1); ++x)
    {
        for(int y = 3*quadY; y < 3*(quadY+1); y++)
        {
            if(!(X == x && Y == y) && board[x][y] == n)
            {
                return false;
            }
        }
    }

    // Check the rows for the same value
    for(int i = 0; i < 9; ++i)
    {
        if(i != X)
        {
            if(board[i][Y] == n)
            {
                return false;
            }
        }

        if(i != Y)
        {
            if(board[X][i] == n)
            {
                return false;
            }
        }
    }

    return true;
}

int main()
{
    // Get input seduko puzzle
    ifstream in;
    in.open("seduko.in");

    for(int x = 0; x < 9; ++x)
    {
        for(int y = 0; y < 9; ++y)
        {
            char nChr;
            in >> nChr;
            int n = (int)nChr-48;
            board[y][x] = n;
        }
    }

    // Until solved, or unsolvable
    while(true)
    {
        bool change = false; // Whether a change to the board was made this iteration

        // For every place
        for(int x = 0; x < 9; ++x)
        {
            for(int y = 0; y < 9; ++y)
            {
                // If the place is empty
                if(board[x][y] == 0)
                {
                    int last;
                    int n = 0;

                    // Try every number
                    for(int i = 1; i <= 9; ++i)
                    {
                        board[x][y] = i;
                        if( isValid(x, y) )
                        {
                            last = i;
                            ++n;
                        }
                    }

                    // test if one piece was found
                    if(n == 1)
                    {
                        board[x][y] = last;
                        change = true;
                    } else
                    {
                        board[x][y] = 0;
                    }
                }
            }
        }

        if(change == false)
            break;
    }

    ofstream out;
    out.open("seduko.out");

    for(int x = 0; x < 9; ++x)
    {
        for(int y = 0; y < 9; ++y)
        {
            out << board[y][x] << " ";
        }
        out << endl;
    }

}
