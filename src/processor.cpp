#include <string>
#include <iostream>
#include "processor.h"
#include "linux_parser.h"

using std::string;
using std::to_string;

// Return the aggregate CPU utilization
// Processor utilization seems very stable since no interval is used.
// interval used was considered a bonus for this project
float Processor::Utilization() { 
  string line, key, user, nice, sys, idle, iowait, irq, softirq, steal;
  int nonIdleT, idleT;
  float cpuUtil;
  std::ifstream filestream("/proc/stat");
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> user >> nice >> sys >> idle >> iowait>> irq >> softirq >> steal) {
        if (key == "cpu") {
          nonIdleT = stoi(user) +stoi(nice) + stoi(sys) +stoi(irq) +stoi(softirq) + stoi(steal);
          idleT = stoi(idle) + stoi(iowait);
          break;
        }
      }
    }
  }
  cpuUtil = float(nonIdleT)/ float(nonIdleT + idleT);
return cpuUtil;
}