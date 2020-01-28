#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
 * Basic class for Process representation
 * It contains relevant attributes as shown below
 */
class Process {
 public:
  Process(int pid): pid_(pid){};
  int Pid();                               // See src/process.cpp
  void SetUid();
  int GetUid() const;
  std::string User();                      // See src/process.cpp
  std::string Command();                   // See src/process.cpp
  float CpuUtilization();                  // See src/process.cpp
  void RamSet();                           // See src/process.cpp
  std::string RamGet() const;              // See src/process.cpp
  long int UpTime();                       // See src/process.cpp
  bool operator<(Process const& a) const;  // See src/process.cpp

 private:
    int pid_;
    int uid_;
    long memory_;
};

#endif