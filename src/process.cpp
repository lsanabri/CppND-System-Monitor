#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

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

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return 0; }

// Return the command that generated this process
string Process::Command() { 
    return LinuxParser::Command(this->pid_ );
}

// Return this process's memory utilization
string Process::Ram() { 
    return LinuxParser::Ram(this->pid_ );
}

// Return the user (name) that generated this process
string Process::User() { 
    string user =  LinuxParser::User(this->uid_);
    return user;
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return 0; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }