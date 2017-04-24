
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <vector>
#include "Process.h"
#include "Memory.h"
#include <ctime>
#ifndef PROCESS_TABLE_H
#define PROCESS_TABLE_H
using namespace std;
class ProcessTable{
   private:
      int nextpid;   
      vector<Process> process;
      int pages_need;
      int base_address;
      Memory m;
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
       void add( Process p){ 
       	   pages_need = p.get_memorySize()/1024 +1;
           base_address = m.load(pages_need);
           cout <<"Return address at: "<< base_address << endl;
           cout << endl;
           if (base_address == -1){
           		p.set_state("m_wait");
           
           }
           if (base_address >=0){
           	   p.set_state("m_ready");
           	   p.set_base_address(base_address);
           }
           	
           process.push_back(p ); 
           cout << "My name: "<<p.get_program_name()<<" And my size: "<< p.get_memorySize() << endl;
           cout << "Memory table when adding Process has PID: "<< p.get_pid() << endl;
           m.display();
                 
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
       int rand(int n)
		{
  			long  num=time(0)*time(0);
  			int num2=num%n +1 ; 
  			return num2;
		}
       	int getioburst()
		{
 			return 500+rand(5000);
		}

		int getburst()
		{
 			return 5+rand(100);
		}
		int get_pages(){
			return pages_need;
		}


       void run(int sec){
       	 int time_quantum = 1000*sec/ get_size();
       	 cout <<"time quantum: "<< time_quantum<< endl;
       	 for (int i =0; i<get_size();++i){
       	 	if (process.at(i).get_state() == "ready"){
       	 		cout << "-----------------Before execution of run(): Process parameters:------------------"<< endl;
       	 		process.at(i).display();
       	 		cout <<"------------------Memory allocation:----------------------------------------------- " << endl;
       	 		
       	 		process.at(i).set_ttl(process.at(i).get_ttl() - time_quantum);
       	 		process.at(i).set_burst(process.at(i).getburst()- time_quantum);
       	 		if(process.at(i).getburst() <0){
       	 			process.at(i).set_state("wait");
       	 			process.at(i).set_ioburst(getioburst());
       	 			cout <<"--------------Burst time is less than 0:---------------------------------"<< endl;
       	 			process.at(i).display();
       	 		}

       	 	}
       	 	if (process.at(i).get_state() == "wait"){
       	 		
       	 		if(process.at(i).getioburst() <0){
       	 			cout <<"--------------Change from wait to ready:---------------------------------"<< endl;
       	 			process.at(i).set_state("ready");
       	 			process.at(i).set_burst(getburst());
       	 			process.at(i).display();
       	 		}

       	 	}
       	 	if (process.at(i).get_ttl()<=0){
                cout << "------------------total time is less than or equal 0:---------------------"<<endl;
                m.free(1024, 3);
       	 		cout << "the pid has terminated"<< endl;
       	 		m.display();

       	 	}
       	 }


       }
       void display_memory(){
       	for(int i =0; i< process.size(); ++i){
       		cout << "Memory table when adding Process has PID: "<<process.at(i).get_pid() << endl;
       		m.display();


       	}
       	
       }
       /* Now it is necessary to modify the ProcessTable class where a process is added and where a process is removed.
        First, when a process is added to the table, the number of pages needed by the process is computed and sent to the memory module.
         The memory module will return the starting page (base) in memory. 
         The starting page (base) and the number of pages (limit) is added to the process and the process is added to the process table.

		When a process terminates, the index of the start page and the number of pages used by the process are sent to the memory module which then frees that memory. 

       */
       
   
                     
};

#endif
