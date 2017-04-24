#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>

using namespace std;

int main()
{
int i=0;
char test[i];
pid_t pid,cpid;
int* status;
int pdf[2];
char buf;
string s;

// Create a pipe pdf

if (pipe(pdf) == -1)
   {
     perror("pipe");
     exit(EXIT_FAILURE);
   }

cpid=fork();

if (cpid == 0) /* Child reads from pipe pdf[0] */
    {
      close(pdf[1]);//close write
      while(read(pdf[0],&buf,1) > 0)
         {s+=buf;
         }
       cout << s << endl;
       exit(EXIT_SUCCESS);
     }
if (cpid > 0 )/* Parent writes to pipe */
     {
       close(pdf[0]);
       s="Hau Tao";
       write(pdf[1], s.c_str(),s.size());
       close(pdf[1]);
       wait(NULL);
       exit(EXIT_SUCCESS);
      }

return 0; //return success
                                                                                }

