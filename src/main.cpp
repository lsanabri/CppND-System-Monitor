#include "ncurses_display.h"
#include "system.h"
#include <unistd.h>
#include <iostream>
int main() {
  System system;
  NCursesDisplay::Display(system); 
}