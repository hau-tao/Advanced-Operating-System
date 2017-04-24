#include "fsystem.h"
#include "sdisk.h"
#include <string>
#include <vector>
#include <sstream>
#include <math.h>
#include <iostream>
using namespace std;
int main(){
	string buffer = "---------------Hello CSUSB. This is lab 7. This is end of file-----------------";
	Filesys f1("file1",50,buffer.length());//create file1 with 30 blocks and 
	
	f1.create("test.txt");
	f1.write ("test.txt", buffer); //write from buffer to file
	f1.write ("test.txt", buffer);
	f1.write ("test.txt", buffer);
	f1.write ("test.txt", buffer);

	string buffer1 ;                         
	f1.read("test.txt", buffer1); //read from file into buffer
	cout <<"Reading content:\n"<< buffer1 << endl;
	f1.remove("test.txt");
	

	return 0;
}