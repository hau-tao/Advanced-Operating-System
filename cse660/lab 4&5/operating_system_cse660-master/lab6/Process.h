
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <ctime>
#include <vector>
#ifndef PROCESS_H
#define PROCESS_H
using namespace std;
class Process{
   private:
       int pid;  // get pid
       string programName; // name of the program
       int ttl; // total CPU time
       string state;// run, wait,ready
       int burst; // CPU burst
       int ioburst; // wait time state
       int memoryAddress;// mem address
       int memorySize;// mem size
  public:
       // constructor
       Process ( int pid, string programName, int ttl, string state, int burst, int ioburst, int memoryAddress, int memorySize)
       {
             this->pid = pid;
             this->programName = programName;
             this->ttl = ttl;
             this->state =  state;
             this->burst = burst;
             this->ioburst =  ioburst;
             this->memoryAddress = memoryAddress;
             this->memorySize = memorySize;

       }
       // radom function
       int rand(int n)
      {
            long  num=time(0)*time(0);
            int num2=num%n +1 ; 
            return num2;
      }
       // accessor functions
       int get_pid(){return pid;}
       string get_program_name(){ return programName;}
       int get_ttl(){return ttl;}
       string get_state(){return state;}
       int getburst(){return burst;}
       int getioburst(){return ioburst;}
       int get_memoryAddress(){return memoryAddress;}
       int get_memorySize(){return memorySize;}
       // mutator functions
       int set_ttl(int CPU_time){ return ttl = CPU_time;}
       string set_state(string state_name){return  state = state_name;}
       int set_burst(int burst_time){ return burst = burst_time;}
       int set_ioburst(int ioburst_time){return ioburst = ioburst_time;}
       int set_base_address(int base){ return memoryAddress = base;}

       // display data
       void display(){       
            cout <<"My pid: "<< get_pid()<<endl;
            cout << "My name: "<<get_program_name()<< endl;
            cout << "My ttl: "<<get_ttl()<<endl;
            cout << "My_state: "<<get_state()<<endl;
            cout << "My burst time: "<<getburst()<<endl;
            cout << "My io burst time: "<<getioburst()<<endl;
            cout << "My memory address: "<< get_memoryAddress()<<endl;
            cout << "My memory size: "<<get_memorySize()<< endl; 
      
       }
                     
};

#endif
