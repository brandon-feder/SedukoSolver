#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <utility>

using namespace std;

// Array to contain the board
array<array<int, 9>, 9> boardStart;

bool isValid(array<array<int, 9>, 9> board, int X, int Y)
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

std::pair<array<array<int, 9>, 9>, bool>
solve(array<array<int, 9>, 9> board, int x, int y)
{

    int nextX = x;
    int nextY = y;

    if(nextX == 8)
    {
        nextX = 0;
        nextY += 1;
    } else
    {
        nextX += 1;
    }

    if(x*y > 64)
    {
        return std::pair<array<array<int, 9>, 9>, bool>(board, true);
    } else if(board[x][y] == 0)
    {
        for(int i = 1; i <= 9; ++i)
        {
            board[x][y] = i;
            if( isValid(board, x, y) )
            {
                std::pair<array<array<int, 9>, 9>, bool> res = solve(board, nextX, nextY);
                if(res.second == true)
                {
                    return res;
                }
            }

        }

        return std::pair<array<array<int, 9>, 9>, bool>(board, false);
    } else
    {
        return solve(board, nextX, nextY);
    }

    std::cout << "Can't be solved" << std::endl;
    std::exit(1);
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
            boardStart[y][x] = n;
        }
    }

    array<array<int, 9>, 9> boardEnd = solve(boardStart, 0, 0).first;

    ofstream out;
    out.open("seduko.out");

    for(int x = 0; x < 9; ++x)
    {
        for(int y = 0; y < 9; ++y)
        {
            out << boardEnd[y][x] << " ";
        }
        out << endl;
    }

}
