#include "ncurses_display.h"
#include "system.h"
#include "linux_parser.h"

int main() {
  System system;
  //LinuxParser::Kernel();
  //LinuxParser::MemoryUtilization();
  NCursesDisplay::Display(system);
  
}