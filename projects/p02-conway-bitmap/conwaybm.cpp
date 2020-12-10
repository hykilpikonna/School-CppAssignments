
#include <ctime>
#include <iostream>
#include "../p02-conway2d/macros.h"
#include <chrono>
#include <algorithm>
#include <iterator>
#include "thread"
#include "ThreadPool.h"

// Standard Library
using namespace std;
using namespace std::chrono;

#define Cell uint8_t
#define Loc uint16_t

bool isBit(Long n, Long k)
{
    return (n & (1ull << k)) != 0;
}

// CELL STRUCTURE
/*
Cells are stored in 8-bit chars where the 0th bit represents
the cell state and the 1st to 4th bit represent the number
of neighbours (up to 8). The 5th to 7th bits are unused.
Refer to this diagram: http://www.jagregory.com/abrash-black-book/images/17-03.jpg
*/

// CellMap stores an array of cells with their states
class CellMap
{
public:
    CellMap();
    ~CellMap();
    bool SetCell(Loc x, Loc y) const;
    void ClearCell(Loc x, Loc y) const;
    int cellState(int x, int y) const; // WHY NOT UNSIGNED?
    int NextGen() const;
    void print() const;

    Cell* cells;
    Cell* temp_cells;
    bool* coins;
};

// Cell map dimensions
Loc w = 50;
Loc h = 50;
Loc lengthInBytes = w * h;
var maxCoins = 0;

int orderX[] = {0,0,1,1,0,1,2,2,2,0,1,2,3,3,3,3,0,1,2,3,4,4,4,4,4,0,1,2,3,4,5,5,5,5,5,5,0,1,2,3,4,5,6,6,6,6,6,6,6,0,1,2,3,4,5,6,7,7,7,7,7,7,7,7};
int orderY[] = {0,1,0,1,2,2,0,1,2,3,3,3,0,1,2,3,4,4,4,4,0,1,2,3,4,5,5,5,5,5,0,1,2,3,4,5,6,6,6,6,6,6,0,1,2,3,4,5,6,7,7,7,7,7,7,7,0,1,2,3,4,5,6,7};

//Long vStart = 56047825;
Long vStart = 325299;

void test(int mod, int step)
{
    // Init coins
    var initCoins = new bool[lengthInBytes];
    for (int i = 0; i < 50; i ++)
    {
        for (int j = 0; j < 50; j ++)
        {
            initCoins[i * w + j] = (i > 15 || j > 15) && (i % 2 == 0 && j % 2 == 0) && i != 0 && j != 0 && i != 48 && j != 48;
        }
    }

    // Create challenge board
    var board = CellMap();

    // Loop through all combinations in 8x8
    for (Long i = vStart + mod; i < 1ull << 63u; i += step)
    {
        // Init board
        memset(board.cells, 0, lengthInBytes);
        copy(initCoins, initCoins + lengthInBytes, board.coins);

        // Fill combination
        for (int b = 0; b < 63; b++)
        {
//            if (isBit(i, b)) board.SetCell(15 - orderX[b], 15 - orderY[b]);
            if (isBit(i, b))
            {
                int row = b / 8;
                int col = b % 8;
                board.SetCell(15 - col, 15 - row);
            }
        }

        // Test board
        var coins = 0;
        var coinsDidntChange = 0;
        while (true)
        {
            val get = board.NextGen();
            coins += get;

            if (get == 0) coinsDidntChange++;
            else coinsDidntChange = 0;

            if (coinsDidntChange > 15) break;
        }

        if (coins > maxCoins)
        {
            maxCoins = coins;
            cout << "New max found! " << maxCoins << " coins - " << i << endl;
        }
    }
}

int main()
{
    val size = 6;
    var pool = ThreadPool(size);

    for (int i = 0; i < size; i++)
    {
        pool.enqueue(test, i, size);
    }

    return 0;
}

CellMap::CellMap()
{
    cells = new Cell[lengthInBytes];  // cell storage
    temp_cells = new Cell[lengthInBytes]; // temp cell storage
    memset(cells, 0, lengthInBytes);  // clear all cells, to start
    coins = new bool[lengthInBytes];
}

CellMap::~CellMap()
{
    delete[] cells;
    delete[] temp_cells;
}

bool CellMap::SetCell(Loc x, Loc y) const
{
    var loc = (y * w) + x;
    Cell *cell_ptr = cells + loc;

    *(cell_ptr) |= 0x01u; // Set first bit to 1

    // Change successive bits for neighbour counts
    if (x != 0)
    {
        *(cell_ptr - 1) += 0x02;
        if (y != 0) *(cell_ptr - w - 1) += 0x02;
        if (y != h - 1) *(cell_ptr + w - 1) += 0x02;
    }
    if (x != w - 1)
    {
        if (y != 0) *(cell_ptr - w + 1) += 0x02;
        *(cell_ptr + 1) += 0x02;
        if (y != h - 1) *(cell_ptr + w + 1) += 0x02;
    }
    if (y != 0) *(cell_ptr - w) += 0x02;
    if (y != h - 1) *(cell_ptr + w) += 0x02;

    if (coins[loc])
    {
        coins[loc] = false;
        return true;
    }
    return false;
}

void CellMap::ClearCell(Loc x, Loc y) const
{
    Cell *cell_ptr = cells + (y * w) + x;

    *(cell_ptr) &= ~0x01u; // Set first bit to 0

    if (x != 0)
    {
        *(cell_ptr - 1) -= 0x02;
        if (y != 0) *(cell_ptr - w - 1) -= 0x02;
        if (y != h - 1) *(cell_ptr + w - 1) -= 0x02;
    }
    if (x != w - 1)
    {
        if (y != 0) *(cell_ptr - w + 1) -= 0x02;
        *(cell_ptr + 1) -= 0x02;
        if (y != h - 1) *(cell_ptr + w + 1) -= 0x02;
    }
    if (y != 0) *(cell_ptr - w) -= 0x02;
    if (y != h - 1) *(cell_ptr + w) -= 0x02;
}

int CellMap::cellState(int x, int y) const
{
    Cell *cell_ptr = cells + (y * w) + x;

    // Return first bit (LSB: cell state stored here)
    return *cell_ptr & 0x01u;
}

int CellMap::NextGen() const
{
    var numCoins = 0;
    Loc x, y, count;
    Cell *cell_ptr;

    // Copy to temp map to keep an unaltered version
    memcpy(temp_cells, cells, lengthInBytes);

    // Process all cells in the current cell map
    cell_ptr = temp_cells;
    for (y = 0; y < h; y++)
    {
        x = 0;
        do
        {
            // Zero bytes are off and have no neighbours so skip them...
            while (*cell_ptr == 0)
            {
                cell_ptr++; // Advance to the next cell
                // If all cells in row are off with no neighbours go to next row
                if (++x >= w) goto RowDone;
            }

            // Remaining cells are either on or have neighbours
            count = *cell_ptr >> 1u; // # of neighboring on-cells
            if (*cell_ptr & 0x01u)
            {
                // On cell must turn off if not 2 or 3 neighbours
                if ((count != 2) && (count != 3))
                {
                    ClearCell(x, y);
                }
            }
            else
            {
                // Off cell must turn on if 3 neighbours
                if (count == 3)
                {
                    numCoins += SetCell(x, y);
                }
            }

            // Advance to the next cell byte
            cell_ptr++;

        }
        while (++x < w);
        RowDone:;
    }
    return numCoins;
}

String repeat(const String &str, Int times)
{
    String s;
    for (var i = 0; i < times; i++) s += str;
    return s;
}

void CellMap::print() const
{
    String result = "\033[2J\033[H\n";

    // Output border row
    result += borderColor + repeat("  ", w + 1) + reset + "\n";

    // Loop through all elements
    for (Int y = 0; y < h; y++)
    {
        result += borderColor;
        result += " ";
        bool lastIsDead = true; // Used for coloring
        for (Int x = 0; x < w; x++)
        {
            // Alive
            if (cellState(x, y) == 1)
            {
                if (x == 0 || lastIsDead)
                {
                    lastIsDead = false;
                    result += lightColor;
                }
            }

            // Dead
            else
            {
                if (x == 0 || !lastIsDead)
                {
                    lastIsDead = true;
                    result += darkColor;
                }
            }

            // Output spaces or coins
            result += coins[(y * w) + x] ? "()" : "  ";
        }

        // Reset color for the end
        result += borderColor + String(" ") + reset + "\n";
    }

    // Output border row
    result += borderColor + repeat("  ", w + 1) + reset + "\n";

    cout << result;
}
