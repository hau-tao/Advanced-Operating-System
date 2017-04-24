#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


using namespace std;

int main()
 {
   int f1, n;
   char buf[1];
   int i = 0;
   // define the file name
   string f = "typing.txt";
   // convert to const cstring
   const char* file=f.c_str();
   f1 = open(file, O_RDONLY);
   // next we read one character at a time from the input file.
   while((n = read(f1, buf, 1)) > 0)
     {
        // output every character we read
        cout << buf[0];
     }
 close(f1); // close the file after reading
 return 0;
 }
