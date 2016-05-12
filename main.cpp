#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <algorithm>
#include "Process.h"
#include "ProcessTable.h"
using namespace std;
int main(){
   ProcessTable PT ;
   Process p1 = Process(PT.getnextpid(), "process_1", 30, "run" , 5, 2, 3000, 1);
   
   // add p1 to PT
   PT.add(p1);
   // create p2
   Process p2 = Process(PT.getnextpid(), "process_2", 30, "run" , 5, 2, 3000, 1);
   // addd p2 to PT
   PT.add(p2);
   cout <<"The size of table: "<< PT.get_size()<< endl; // should be 2
  
   

 /*   Process p1= Process( 1005, "process_1", 30, "run" , 5, 2, 3000, 1); */
   
    cout <<"My pid_1: "<< p1.get_pid()<<endl;
    cout << "My name: "<<p1.get_program_name()<< endl;
    cout << "My ttl: "<<p1.get_ttl()<<endl;
    cout << "My_state: "<<p1.get_state()<<endl;
    cout << "My burst time: "<<p1.get_burst()<<endl;
    cout << "My io burst time: "<<p1.get_ioburst()<<endl;
    cout << "My memory address: "<< p1.get_memoryAddress()<<endl;
    cout << "My memory size: "<<p1.get_memorySize()<< endl; 
    // remove process p1 from table
    PT.remove(p1);
    // remove process p1 from table
    PT.remove(p2);
    
    cout <<"The size of table: "<< PT.get_size()<< endl; // shoule be 0
    

    return 0;
}

