#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

//Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string line, key, value;
  float memTotal, memFree;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal:") {
          memTotal = stoi(value);
        }
        if (key == "MemFree:"){
            memFree = stoi(value);
        }
      }
    }
  }
  return  (memTotal - memFree)/memTotal;
}

// Read and return the system uptime
long LinuxParser::UpTime() { 
  string upTime, idleTime;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> upTime >> idleTime ;
  }
  return  stol(upTime);
}

// Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  string line, value;
  vector<string> cpuUtil;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    // CPU utilization information is in the first line of the system file
    // and the only file of the process stat file
    std::getline(filestream, line);
    std::istringstream linestream(line);
    while (linestream >> value) {
       cpuUtil.push_back(value); 
    }
  }
  return cpuUtil;
}

// Read and return process CPU utilization
vector<string> LinuxParser::ProcessCpuUtilization(int pid){
  string line, value;
  vector<string> cpuUtil;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    while (linestream >> value) {
       cpuUtil.push_back(value); 
    }
  }
  return cpuUtil;
}

// Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string line, key, value;
  int processes;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          processes = stoi(value);
        }
      }
    }
  }
  return processes;
}

// Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string line, key, value;
  int processes;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          processes = stoi(value);
        }
      }
    }
  }
  return processes;
}

// Read and return the command associated with a process
string LinuxParser::Command(int pid) { 
  string line;
  std::ifstream stream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
  }
  return line; 
}

// Read and return the memory used by a process
string LinuxParser::Ram(int pid) { 
  string key, value, mem, line;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream stream(line);
      while (stream >> key >> value) {
        if (key == "VmSize:") {
          mem = value;
          break;
        }
      }
    }
  }
  return mem; 
}

// Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) {
  string key, value, uid, line;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream stream(line);
      while (stream >> key >> value) {
        if (key == "Uid:") {
          uid = value;
          break;
        }
      }
    }
  }
  return uid; 
}

// Return User name associated with a process
string LinuxParser::User(int uid) { 
  string key, value, user, line, x ;
  x =  "x";
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream stream(line);
      while (stream >> value >> x >> key) {  
          if (key == to_string(uid)) {
            user = value;
            break;
          }
      }
    }
  }
  return user;
}

// Read and return the uptime of a process
long LinuxParser::UpTime(int pid) { 
  int counter = 0;
  string line, startTime;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    // Start time is 22th object in the line
    // http://man7.org/linux/man-pages/man5/proc.5.html
    while (counter < 22) {
      linestream >> startTime;
      counter ++;
    }                  
  }
  return std::stol(startTime);
}
 
 /* Not used functions */
// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }