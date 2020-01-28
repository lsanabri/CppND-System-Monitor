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
  int nonIdleT, idleT;
  float cpuUtil;
  std::vector<string> cpuInfo = LinuxParser::CpuUtilization();
  // CpuInfo vector has the follwing data
  // {'cpu', user, nice, sys, idle, iowait, irq, softirq, steal}
  nonIdleT = stoi(cpuInfo[1]) +stoi(cpuInfo[2]) + stoi(cpuInfo[3]) +stoi(cpuInfo[6])+stoi(cpuInfo[7]) + stoi(cpuInfo[8]);
  idleT = stoi(cpuInfo[4]) +stoi(cpuInfo[5]);
  cpuUtil = float(nonIdleT)/ float(nonIdleT + idleT);
  return cpuUtil;
}