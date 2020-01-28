#include "ncurses_display.h"
#include "system.h"
#include <unistd.h>
#include <iostream>
int main() {
  System system;
  std::cout << sysconf(_SC_CLK_TCK) <<"\n\n";
  NCursesDisplay::Display(system);
  
}