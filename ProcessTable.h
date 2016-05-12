
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
       void add(Process &p){ 
           process.push_back(p );
           ++nextpid;
           ++size;
       } // every time adding a process into table, increase pid by 1
       void remove( Process &p)
       {   
           vector<Process>:: iterator it = process.begin();
           while(it!= process.end()){
               if(p.get_pid()==  (*it).get_pid()){
                   it = process.erase(it);
                   --size;
                }
               else{
                    ++it;

               }
           }

       }
       // send pid to its process
       int getnextpid(){
         return nextpid;

       }
       int get_size(){
          return size;
       }
   
                     
};

#endif
