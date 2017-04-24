#ifndef FSYSTEM_H
#define FSTSTEM_H

#include "sdisk.h"
#include <string>
#include <vector>

using namespace std;

class Filesys: public Sdisk
{
    public :
	Filesys(string disk, int numberofblocks, int blocksize);
        int create(string file);
        int write(string file,string buffer);
        int read(string file,string& buffer);
        int remove(string file);
    private :
        vector<string> block(string buffer, int b);
	int newfile(string file);
	int rmfile(string file);
	int getfirstblock(string file);
	int addblock(string file, string buffer);
	int delblock(string file, int blocknumber);
	int readblock(string file, int blocknumber, string& buffer);
	int nextblock(string file, int blocknumber);
	int rootsize;           // maximum number of entries in ROOT
	int fatsize;            // number of blocks occupied by FAT
	int fssynch();
	bool checkblock(string file, int block);
	vector<string> filename;   // filenames in ROOT
	vector<int> firstblock; // firstblocks in ROOT
	vector<int> fat;             // FAT
};
#endif
