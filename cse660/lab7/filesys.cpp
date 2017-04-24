//////////////////////////////////////////////////////////////////////////////////////////////

#include "sdisk.h"
#include "fsystem.h"
#include <string>
#include <vector>
#include <sstream>
#include <math.h>
#include <iostream>

using namespace std;

int Filesys::create(string file)
{
    return newfile(file);
}

int Filesys::write(string file,string buffer) 
{
    int bSize = getblocksize();
    vector<string> blocks=  block(buffer,bSize);
    int location =0;
   

    for(int i =0; i< blocks.size(); ++i){
       
         location =  addblock(file, buffer);
    }
    return location;
    

}

int Filesys::read(string file,string& buffer)
{
    string s;
    int location;
    int firstblock = getfirstblock(file);
    int numOfBlocks = getnumberofblock();
    for(int i = firstblock; i<= numOfBlocks; ++i){
        if(checkblock(file,i)){
            location = readblock(file,i,s);
            buffer += s;

        }
    }
    return location;

    

}

int Filesys::remove(string file)
{
    int firstBlock = getfirstblock(file);
    
    while( firstBlock>0)
    {
        int nextBlock = nextblock(file, firstBlock);
        delblock(file, firstBlock);
        firstBlock = nextBlock;
    }
    return rmfile(file);
}

Filesys::Filesys(string disk, int numberofblocks, int blocksize):Sdisk(disk, numberofblocks, blocksize) 
{
    int bSize = getblocksize();
    int numOfBlocks = getnumberofblock();
    rootsize = bSize/12;
    fatsize = numOfBlocks*6/blocksize+1;
    string check;
    getblock(0, check);
    if(check[0] != '#')
    {
	istringstream rstream1, fstream1;
	string rbuffer1, fbuffer1;
 	getblock(0, rbuffer1);
	rstream1.str(rbuffer1);
	for(int i = 0; i < rootsize; i++)
	{
	    string f;
	    int n;
	    rstream1 >> f >> n;
	    filename.push_back(f);
	    firstblock.push_back(n);
	}
	for(int i = 1; i <= fatsize; i++)
	{
	    string s;
	    getblock(i, s);
	    fbuffer1 +=s;
	}
	fstream1.str(fbuffer1);
	for(int i = 0; i < numOfBlocks; i++)
	{
	    int n = 0;
	    fstream1 >> n;
	    fat.push_back(n);
	}
    }
    else
    {
    	for(int i = 0; i < rootsize; i++)
    	{
	    filename.push_back("*****");
	    firstblock.push_back(0);
    	}
    	fat.push_back(fatsize +1);
	for(int i = 1; i <= fatsize; i++)
	    fat.push_back(i);
    	for(int i = fatsize+1; i < numOfBlocks; i++)
	    fat.push_back(i+1);
    	fat[fat.size()-1] = 0;
    	fssynch();
    }
}


vector<string> Filesys::block(string buffer, int b)
{
// blocks the buffer into a list of blocks of size b

vector<string> blocks;
int numberofblocks=0;

if (buffer.length() % b == 0) 
   { numberofblocks= buffer.length()/b;
   }
else 
   { numberofblocks= buffer.length()/b +1;
   }

string tempblock;
for (int i=0; i<numberofblocks; i++)
    { tempblock=buffer.substr(b*i,b);
      blocks.push_back(tempblock);
    }

int lastblock=blocks.size()-1;

for (int i=blocks[lastblock].length(); i<b; i++)
    { blocks[lastblock]+="#";
    }

return blocks;

}

int Filesys::newfile(string file)
{
    for(int i = 0; i < filename.size(); i++)
    {
	if(filename[i] == file)
	    return 0;
	if(filename[i] == "*****")
	{
	    filename[i] = file;
	    firstblock[i] = 0;
	    fssynch();
	    return 1;
	}
    }
}

int Filesys::rmfile(string file)
{
    for(int i = 0; i < filename.size(); i++)
    {
	if(firstblock[i] == 0)
	{
	    filename[i] = "*****";
	    return fssynch();
	}
	else
	{
	    cout << "File must be empty before removing.\n";
	    return 0;
	}
    }
}

int Filesys::getfirstblock(string file)
{
    for(int i = 0; i < filename.size(); i++)
    {
	if(filename[i] == file)
	    return firstblock[i];
    }
    return -1;
}

int Filesys::addblock(string file, string buffer)
{
    int firstb = getfirstblock(file);
    if(firstb < 0)
    {
	cout << "Error: file " << file << "cannot be found!\n";
	return -1;
    }
    int allocate = fat[0];
    if(allocate == 0)
    {
	cout << "No space on device.\n";
	return -1;
    }
    fat[0] = fat[allocate];
    fat[allocate] = 0;
    if(firstb == 0)
    {
	for(int i = 0; i < filename.size(); i++)
	{
	    if(filename[i] == file)
		firstblock[i] = allocate;
	}
    }
    else
    {
	int block = firstb;
	while(fat[block] != 0)
	    block = fat[block];
	fat[block] = allocate;
    }
    putblock(allocate, buffer);
    fssynch();
    return allocate;
}

int Filesys::delblock(string file, int blocknumber)
{
    if(blocknumber <= 0)
    {
	cout << "Cannot delete! " << file << " is empty!" << endl;
	return 0;
    }
    if(!checkblock(file, blocknumber))
    {
	cout << "Cannot delete block " << blocknumber << endl;
	return 0;
    }

    if(getfirstblock(file) == blocknumber)
    {
	for(int i = 0; i < filename.size(); i++)
	{
	    if(filename[i] == file)
	    {
		firstblock[i] = fat[blocknumber];
		cout << "Deleting block!\n";
	    }
	}
    }
    else
    {
	int fblock = getfirstblock(file);
	while(fat[fblock] != blocknumber)
	    fblock = fat[fblock];
	fat[fblock] = fat[blocknumber];
    }
    fat[blocknumber] = fat[0];
    fat[0] = blocknumber;
    fssynch();
    return 1;
}

int Filesys::readblock(string file, int blocknumber, string& buffer)
{
    if(!checkblock(file, blocknumber))
    {
	cout << blocknumber << " does not exist in " << file << endl;
	return 0;
    }
    int firstb = getfirstblock(file);
    if(firstb < 0)
    {
	cout << "File " << file << " does not exist!\n";
	return 0;
    }
    else if(firstb == 0)
    {
	cout << "File " << file << " is empty!\n";
	return 0;
    }
    int nblock = firstb;
    while(nblock != blocknumber && nblock != 0)
	nblock = fat[nblock];
    if(nblock == blocknumber)
    {
    getblock(blocknumber, buffer);
    return 1;
    }
    if(nblock == 0)
    {
    cout << "Block " << blocknumber << " is not in file " << file << endl;
	return 0;
    }
}


int Filesys::nextblock(string file, int blocknumber)
{
    int nblock = getfirstblock(file);
    if(nblock < 0)
	return -1;
    while(nblock != blocknumber && nblock != 0)
	nblock = fat[nblock];
    return fat[nblock];
}

int Filesys::fssynch()
{
    ostringstream rstream;
    ostringstream fstream;
    for(int i = 0; i < rootsize; i++)
	rstream << filename[i] << " " << firstblock[i] << " ";
    for(int i = 0; i < fat.size(); i++)
    	fstream << fat[i] << " ";
    string rbuffer = rstream.str();
    string fbuffer = fstream.str();
    vector<string> rVec, fVec;
    rVec = block(rbuffer, getblocksize());
    fVec = block(fbuffer, getblocksize());
    putblock(0, rVec[0]);
    for(int i = 1; i <= fVec.size(); i++)
	putblock(i, fVec[i-1]);
	return 0;
}



bool Filesys::checkblock(string file, int block)
{
    int fblock = getfirstblock(file);
    if(fblock < 0)
	return false;
    else if(fblock == block)
	return true;
    int nblock = fblock;
    while(fat[nblock] !=0 && fat[nblock] != block)
	nblock = fat[nblock];
    if(fat[nblock] == block)
	return true;
    if(nblock == 0) 
	return false;

}
