#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main()
{
 pid_t pid;
 int* status;

 pid = fork();

  if (pid > 0)
   {
      cout << "Parent :child executing" <<endl;
      pid_t cpid=wait(status);
      cout << " Parent : child process" << cpid << " finished" << endl;
    }
   if (pid == 0)
    {
       for (int i=0; i<10000; i++)
       {
         
       }
       cout << "Child :child exiting" << endl;
       exit(0);

     }
   if (pid <= 0)
     {
        cout << "fork failed" << endl;
      }
 return 0; //return success
                                                                                }
