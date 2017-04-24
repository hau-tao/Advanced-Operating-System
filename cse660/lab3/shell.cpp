#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <sys/wait.h>

using namespace std;

vector<string> parse(string x)
{
 // This function parses the command line input into parts
  vector<string> s;
  istringstream instream;
  x=x+" "+"@"+" ";
  instream.str(x);
  string part;
  instream >> part;
  //cout << part;
  while ( part != "@")
    {
      s.push_back(part);
      instream >> part;
    }
  return s;
}

vector<char *> strconv(vector<string> s)

// This converts a vector of C++ string to C string
{
vector<char *> argv(s.size());    

for (int i = 0; i<s.size(); i++)
{
      argv[i] = &s[i][0];
}

return argv;
}

int main ()
{
  string x;
  vector<string> s;
  istringstream instream;
// the next part reads in a command
  cout << "$$";
  getline(cin,x);
  s=parse(x);
 

 //execvp(argv[0], argv.data());
   
  while (s[0] != "exit")
    {
     // first convert from C++ strings to C strings
       vector<char *> argv(s.size());
       argv=strconv(s);

     // 1. fork
       pid_t cpid = fork();
     // 2. child runs execvp and exits
     //     use execvp(argv[0], argv.data())
       if(cpid ==0){
            execvp(argv[0], argv.data());
           
           

       }
     // 3. parent waits for child
     //    now parent reads in next command
       if(cpid > 0){
        wait(NULL);
        cout << "$$";
        getline(cin,x);
        s=parse(x);

     }
   }
}
