#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <algorithm>
#include "Process.h"
#include "ProcessTable.h"
#include <ctime>
#include <vector>
using namespace std;
int rand(int n)
{
  long  num=time(0)*time(0);
  int num2=num%n +1 ; 
  return num2;
}
Process getprocess(int pid)
{ 
   vector<string> progs;
   progs.push_back("null");
   progs.push_back("bash");
   progs.push_back("php");
   progs.push_back("c++");
   progs.push_back("prog1");
   progs.push_back("prog2");
   progs.push_back("prog3");
   progs.push_back("csh");
   progs.push_back("http");
   progs.push_back("mail");
   progs.push_back("lpl");
   return Process(pid,progs[rand(10)],100+rand(1000),"ready",5+rand(100),0,0,800+rand(10000)); 
}

int main(){
   ProcessTable t=ProcessTable();
// Add daemons
   t.add(Process(t.getnextpid(),"init",-1,"ready",5+rand(100),0,0,0)); 
   t.add(Process(t.getnextpid(),"kblockd",-1,"ready",5+rand(100),0,0,0)); 
   t.add(Process(t.getnextpid(),"sendmail",-1,"ready",5+rand(100),0,0,0)); 
   t.add(Process(t.getnextpid(),"courier",-1,"ready",5+rand(100),0,0,0)); 
   t.add(Process(t.getnextpid(),"httpd",-1,"ready",5+rand(100),0,0,0)); 
   t.add(Process(t.getnextpid(),"aio",-1,"ready",5+rand(100),0,0,0)); 

   int choice=0;
   cout << "Enter selection : 1 - New Processes, 2 - Run 3 - Quit :";
   cin >> choice;
   while (choice != 3) 
     {
       if (choice==1)
         { 
            int n=0;
            cout << "Enter the number of processes to add:";
            cin >> n;
            for (int i=1; i<=n; i++)
                {
                   t.add(getprocess(t.getnextpid()));
                   
                 }
          }
        if (choice==2)
          {
             int sec=0;
             cout << "Enter the number of seconds to run :";
             cin >> sec;
             t.run(sec);
            
          }
       cout << "Enter selection : 1 - New Processes, 2 - Run 3 - Quit :";
       cin >> choice;
      }
 
  
  
   

    

    return 0;
}

