#ifndef SDISK_H
#define SDISK_H
#include <string>

using namespace std;

class Sdisk
{
public :
Sdisk(string Diskname, int Numberofblocks, int Blocksize);
int getblock(int blocknumber, string& buffer);
int putblock(int blocknumber, string buffer);
int getnumberofblock();
int getblocksize();
private :
string diskname;        // file name of pseudo-disk
int numberofblocks;     // number of blocks on disk
int blocksize;          // block size in bytes
};
#endif
