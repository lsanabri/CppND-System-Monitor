#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <math.h>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// Return this process's ID
int Process::Pid() {  
    return this->pid_; 
}

// Return this process's UID
int Process::GetUid() const {  
    return this->uid_; 
}

// Set this process's UID
void Process::SetUid() {  
    this->uid_ = stoi(LinuxParser::Uid(this->pid_)); 
}

// Return this process's CPU utilization
float Process::CpuUtilization() { 
    vector<string> cpuInfo = LinuxParser::ProcessCpuUtilization(this->pid_);
    /* The vector holds the following information
     vector[13] = utime
     vector[14] = stime
     vector[15] = cutime
     vector[16] = cstime
     vector[22] = starttime
     */
    int totalTime =  std::stoi(cpuInfo[13])+ std::stoi(cpuInfo[14])+std::stoi(cpuInfo[15])+ std::stoi(cpuInfo[16]);
    float seconds = LinuxParser::UpTime() - std::stoi(cpuInfo[21])/float(sysconf(_SC_CLK_TCK));
    return totalTime/float(sysconf(_SC_CLK_TCK))/seconds;
}

// Return the command that generated this process
string Process::Command() { 
    return LinuxParser::Command(this->pid_ );
}

// Set this process's memory attribute from process file
void Process::RamSet() { 
    long mem = stol(LinuxParser::Ram(this->pid_ ));
    // Convert from Kb to Mb
    mem = mem / 1024;
    // Store Memory consumption 
    this->memory_= mem;
}

// Return this process's memory utilization
string Process::RamGet() const { 
    return to_string(this->memory_);
}

// Return the user (name) that generated this process
string Process::User() { 
    string user =  LinuxParser::User(this->uid_);
    return user;
}

// Return the age of this process (in seconds)
long int Process::UpTime() { 
    long startTime = LinuxParser::UpTime(this->pid_);
    // One of the operands needs to cast to get more presition,
    // then we round up... if not we end up truncating the value.
    startTime = round(startTime/float(sysconf(_SC_CLK_TCK)));
    return startTime;
}

// Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const { 
    return (this->memory_ > a.memory_);
}