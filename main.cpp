#include "memory.h"

#include <thread>

#include <iostream>

#include <string>

#include <vector>

using namespace std;

namespace offsets {
  constexpr auto timesClicked = 0x1C;
  constexpr auto bombCount = 0x8;
  constexpr auto rowSize = 0x10;
  constexpr auto columnSize = 0xC;
  constexpr auto isTimerRunning = 0x126;
  constexpr auto timer = 0x20;
}

int main() {
  const auto mem = Memory("Minesweeper.exe");

  std::cout << "minesweeper found!" << std::endl;

  const auto client = mem.GetModuleAddress("Minesweeper.exe");

  auto base = mem.Read < std::int64_t > (mem.Read < std::int64_t > (client + 0xAAA38) + 0x18);

  auto y = mem.Read < std::int32_t > (base + offsets::columnSize);
  auto x = mem.Read < std::int32_t > (base + offsets::rowSize);

  cout << "x: " << x << endl;

  cout << "y: " << y << endl;

  // Minesweeper.exe + 0xAAA38] + 0x18] + 0x58] + 0x10] + 0x8* column] + 0x10] + row
  auto field = mem.Read < std::int64_t > (mem.Read < std::int64_t > (base + 0x58) + 0x10);

  cout << "field: " << field << endl;

  char grid[9][9];

  // Initialize the grid with empty cells (' ')
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
      grid[i][j] = ' ';
    }
  }

  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
      auto mines = mem.Read < char > (mem.Read < std::int64_t > (mem.Read < std::int64_t > (field + 0x8 * i) + 0x10) + j);

      //if((int)(mines) == 1) cout <<  j << i << ": " << int(mines) << endl;
      if ((int)(mines) == 1) grid[j][i] = 'X';

    }
    cout << "" << endl;

  }

  cout << "   ";
  for (int j = 0; j < y; j++) {
    cout << " " << j << " ";
  }
  cout << endl;

  for (int i = 0; i < x; i++) {
    cout << " " << i << " ";
    for (int j = 0; j < y; j++) {
      cout << "[" << grid[i][j] << "]";
    }
    cout << endl;
  }

  cout << "" << endl;

  auto clicked = mem.Read < std::int32_t > (base + offsets::timesClicked);

  cout << "clicked: " << clicked << endl;

  auto bomb = mem.Read < std::int32_t > (base + offsets::bombCount);

  cout << "bomb: " << bomb << endl;

  auto time = mem.Read < float > (base + offsets::timer);

  cout << "time: " << time << endl;

}
