#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

int main(){
	char * argv[] = {"cat", "/etc/passwd", NULL};
	pid_t pid = fork();
	if(pid ==0){
		execvp(argv[0],argv);
		exit(0);
	}
	if( pid >0){
		wait(NULL);
		exit(1);
	}
	if(pid <0){
		cout <<"error"<<endl;
		exit(0);
	}

}
