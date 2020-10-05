// Knight's Tour Problem
// Data Structure Project 1 by 2016-12161 Taewon Lee
// The file contains 2 classes: simpleKnight & complexKnight since it should have 2 chessboards
// Algorithm is following the description from the book
// input the i, j separately
#include <iostream>
using namespace std;

//simple_solve is the main function
class simpleKnight
{
public:
    int chessboard[8][8] = {0}; //step (a) - initialize chessboard
    int ktmov1[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
    int ktmov2[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    bool isPassed = true;        //if npos goes 0, isPassed comes false
    bool nextable(int x, int y); //check the square is valid
    int howmany_nextable(int x, int y);
    void simple_solve(int x, int y)
    {
        chessboard[x][y] = 1; //step (b) - set starting position
        int m = 1;
        for (int m = 2; m <= 64; m++) //step (c) - Loop
                                      //step (d) - Form set of possible next squares
        {
            int min, minval = 9;
            int nexti[8], nextj[8], exits[8]; //saving next position
            int l, npos = 0;
            for (int k = 0; k < 8; k++)
            {
                if (nextable(x + ktmov1[k], y + ktmov2[k]))
                {
                    nexti[npos] = x + ktmov1[k];
                    nextj[npos] = y + ktmov2[k];
                    npos++;
                }
            }
            //step (e) - Test special cases
            if (npos == 0) //special case npos = 0
            {
                isPassed = false;
                break;
            }
            for (int l = 0; l < npos; l++)
            {
                exits[l] = howmany_nextable(nexti[l], nextj[l]); //checking fewest next valid position
                if (minval > exits[l])
                {
                    minval = exits[l];
                    min = l;
                }
            }
            //step (g) - Move Knight
            x = nexti[min];
            y = nextj[min];
            chessboard[x][y] = m;
        }
    };
    simpleKnight(int x, int y) //constructor
    {
        simple_solve(x, y);
    };
    void printKnight() //printing the chessboard
    {
        cout << "Simple Solution: ";
        if (isPassed)
            cout << "Success" << endl;
        else
            cout << "Failure" << endl;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                cout.width(2);
                cout << chessboard[i][j] << " ";
            }
            cout << endl;
        }
    }
};
//complexKnight is totally same as simpleKnight except breaking even
//Not saving next_next position, because we only needs the sum of legal moves
class complexKnight
{
public:
    int chessboard[8][8] = {0};
    int ktmov1[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
    int ktmov2[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    bool isPassed = true;
    bool nextable(int x, int y);
    int howmany_nextable(int x, int y);
    void complex_solve(int x, int y)
    {
        chessboard[x][y] = 1;
        int m = 1;
        for (int m = 2; m <= 64; m++)
        {
            int minval = 9;
            int nexti[8], nextj[8], exits[8];
            int l = 0, npos = 0, howmany_min = 0;
            int mins[8]; //list of the fewest legal moves
            int minvaluesforsum = 0;
            int next_minval = 100;
            int minwhere = 0;
            for (int k = 0; k < 8; k++)
            {
                if (nextable(x + ktmov1[k], y + ktmov2[k]))
                {
                    nexti[npos] = x + ktmov1[k];
                    nextj[npos] = y + ktmov2[k];
                    npos++;
                }
            }
            if (npos == 0)
            {
                isPassed = false;
                break;
            }
            for (int l = 0; l < npos; l++)
            {
                exits[l] = howmany_nextable(nexti[l], nextj[l]);
                if (minval > exits[l])
                {
                    minval = exits[l];
                    mins[0] = l;
                    howmany_min = 1;
                }
                else if (minval == exits[l])
                {
                    mins[howmany_min] = l;
                    howmany_min++;
                }
            }
            //checking the sum of next next legal moves if we have same legal moves
            for (int k = 0; k < howmany_min; k++)
            {
                for (int t = 0; t < 8; t++)
                {
                    if (nextable(nexti[mins[k]] + ktmov1[t], nextj[mins[k]] + ktmov2[t]))
                        minvaluesforsum = minvaluesforsum + howmany_nextable(nexti[mins[k]] + ktmov1[t], nextj[mins[k]] + ktmov2[t]);
                }
                if (minvaluesforsum < next_minval)
                {
                    minwhere = k;
                    next_minval = minvaluesforsum;
                }
                minvaluesforsum = 0;
            }
            x = nexti[mins[minwhere]];
            y = nextj[mins[minwhere]];
            chessboard[x][y] = m;
        }
    };
    complexKnight(int x, int y)
    {
        complex_solve(x, y);
    };
    void printKnight()
    {
        cout << "Complex Solution: ";
        if (isPassed)
            cout << "Success" << endl;
        else
            cout << "Failure" << endl;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                cout.width(2);
                cout << chessboard[i][j] << " ";
            }
            cout << endl;
        }
    }
};
int main()
{
    int x, y; // x, y for starting position
    cout << "input x, y" << endl;
    cin >> x >> y; //input
    simpleKnight simpleknight(x, y);
    complexKnight complexknight(x, y);
    simpleknight.printKnight();
    cout << endl;
    complexknight.printKnight();
    return 0;
}

bool simpleKnight::nextable(int x, int y)
{
    if (chessboard[x][y] == 0 && x > -1 && y > -1 && x < 8 && y < 8)
        return true;
    else
        return false;
}
int simpleKnight::howmany_nextable(int x, int y)
{ // in range, never been -> true
    int ans = 0;
    for (int i = 0; i < 8; i++)
    {
        if (nextable(x + ktmov1[i], y + ktmov2[i]))
            ans++;
    }
    return ans;
}
bool complexKnight::nextable(int x, int y)
{
    if (chessboard[x][y] == 0 && x > -1 && y > -1 && x < 8 && y < 8)
        return true;
    else
        return false;
}
int complexKnight::howmany_nextable(int x, int y)
{ // in range, never been -> true
    int ans = 0;
    for (int i = 0; i < 8; i++)
    {
        if (nextable(x + ktmov1[i], y + ktmov2[i]))
            ans++;
    }
    return ans;
}
