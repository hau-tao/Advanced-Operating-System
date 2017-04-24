#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <string>

using namespace std;

int main ()
{
    int fd1;
    string buf;
    fd1 = open("write.txt",O_WRONLY|O_CREAT, 0600); // rw only for owner
    if (fd1 == -1) {
        cout << "Open Failed";
        return EXIT_FAILURE;
    }

    /* Enter the data to be written into the file */
    buf="Hello World";

    // write the string - note we use c_str() to convert to a C String
    write(fd1, buf.c_str(), buf.size());

    close(fd1);

    return 0;
}