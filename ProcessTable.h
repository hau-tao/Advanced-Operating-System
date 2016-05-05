
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <vector>
#include "Process.h"
#ifndef PROCESS_TABLE_H
#define PROCESS_TABLE_H
using namespace std;
class ProcessTable{
   private:
      int nextpid;   
      vector<Process> process;
      int size; // number of process in table 
  public:
       // default constructor to initialize the first value pid
       ProcessTable ()
      {
           nextpid = 1001;
           size = process.size();
           
      }   
       // mutator functions
       //The class needs two mutators to add and remove processes from the vector
       void add_process(Process p){ 
           process.push_back(p);
           ++nextpid;
           ++size;
       } // every time adding a process into table, increase pid by 1
       void remove_process(Process p)
       {   //int pos = find(process.begin(), process.end(), p) - process.begin();
           process.erase(process.begin() + (p.get_pid()%1000)-1); 
           --size;
       }
       // send pid to its process
       int get_pid(){
         return nextpid;

       }
       int get_size(){
          return size;
       }
   
                     
};

#endif
