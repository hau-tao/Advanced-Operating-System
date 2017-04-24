#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "err.h"

using namespace std;

int main()
{   
cout << "Parent PID" << endl << getpid() << endl;
if(fork()==0)
{
    cout << "child 1" << " has pid: "<< getpid() << " My parent has pid: "<< getppid()<<endl ;
    if(fork()==0)
    {
        cout << "child 2"<<" has pid: "<< getpid() << " My parent has pid: "<< getppid()<<endl ;
        if(fork()==0)
           {
           cout << "child 3" << " has pid: "<< getpid() << " My parent has pid: "<< getppid()<<endl ;
           }
    }

}
return 0;
}    
 