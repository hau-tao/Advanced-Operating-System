#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "err.h"

using namespace std;
int main ()
{
 pid_t pid;
 int i;

cout << "My process id = " << getpid() << endl;

 for (i = 1; i <= 4; i++)
  pid = fork();
  if (pid==-1)
    {
    cout <<"Error in fork" << endl;
    }

  if (pid==0)
    {
    cout << "Child process: Value returned by fork() = " << pid << endl;
    return 0;
    }

  if (pid>0)
    {
    cout << "Parent process. Value returned by fork() = " << pid << endl;
     }
 return 0;
 }
