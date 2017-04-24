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

pid = fork();
if(pid ==-1)
	cout <<"eoor" << endl;
if(pid>0)
	wait(NULL);
if(pid ==0){
	fork();
cout << "process "<< getpid() << endl ;
	wait(NULL);
	return 0;
}

cout << "process "<< getpid() << endl ;
return 0; //return success
                                                                                }
