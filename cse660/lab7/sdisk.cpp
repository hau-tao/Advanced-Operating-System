//////////////////////////////////////////////////////////////////////////////////////////////
#include "sdisk.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

Sdisk::Sdisk(string Diskname, int Numberofblocks, int Blocksize)
{
    this->diskname = Diskname;
    this->numberofblocks = Numberofblocks;
    this->blocksize = Blocksize;
    bool isGood;
    ifstream checkDisk(diskname.c_str());
    char c = checkDisk.peek();
    if(checkDisk.good())
    {
	checkDisk.seekg(0, ios::end);
	int i = checkDisk.tellg();
	if(i == (numberofblocks*blocksize))
    	    isGood = true;
	else
	    isGood = false;
    }	
    else 
	isGood = false;
    checkDisk.close();
    if(!isGood)
    {
    	ofstream Disk;
	cout << "Overwriting " << diskname << endl;
    	Disk.open(diskname.c_str(), ios::trunc);
    	for(int i = 0; i < (numberofblocks*blocksize); i++)//if file is empty fill with blank blocks
    	{
	    Disk <<'#';
    	}
    	Disk.close();
    }
}

int Sdisk::getblock(int blocknumber, string& buffer) 
{
    if(blocknumber >= numberofblocks || blocknumber < 0)
    {
	cout << "Error: block number " << blocknumber << " does not exist!" << endl;
	return 0;
    }
    char c[blocksize];
    ifstream rDisk;
    rDisk.open(diskname.c_str());
    rDisk.seekg((blocknumber)*(blocksize));
    rDisk.get(c, blocksize+1);
    string temp(c);
    buffer = temp;
    rDisk.close();
    return 1;
    
}

int Sdisk::putblock(int blocknumber, string buffer)
{
    
    if(blocknumber >= numberofblocks || blocknumber < 0)
    {
	cout << "Error: block number " << blocknumber << " does not exist!" << endl;
	return 0;
    }
    if(buffer.length() != blocksize)
    {
	cout << "Error: All blocks must be " << blocksize << " characters long." << endl;
	return 0;
    }
    fstream wDisk;
    wDisk.open(diskname.c_str(), ios::in|ios::out);
    int offset = (blocknumber)*(blocksize);
    wDisk.seekp(offset);
    for(int i = 0; i < blocksize; i++)
	wDisk.put(buffer[i]);
    wDisk.close();
    return 1;
}

int Sdisk::getnumberofblock()
{
    return numberofblocks;
}

int Sdisk::getblocksize()
{
    return blocksize;
}
