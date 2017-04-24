
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <vector>
#include "Process.h"
#include <ctime>
#ifndef MEMORY_H
#define MEMORY_H
using namespace std;
class Memory{
	private:
		vector<int> pages;
		
    public:
    	Memory():pages(50,0){}
    	
    	// mutator
    	int load(int limit){
    		for(int i =0; i< pages.size();++i){
    			for(int j = i; j < i+limit ;++j){
    				if(pages.at(i)== 0 && pages.at(i)==pages.at(j)){
    					pages.at(j)= 1;
    					limit--;
    					if(limit==0)
    						return i*1024;
    					

    				}
    				
    					
    			}

    		}
    		return -1;

    	}
    	void free(int base, int limit){
    		for(int i = base/1024; i< base/1024+limit; ++i)
    			pages.at(i) = 0;

    	}
    	
    	void display(){
    		for (int i =0 ; i< pages.size(); ++i){
    			if (pages.at(i)==0)
    				cout << "Free space at index: " <<i<<" value: "<< pages.at(i)<< endl;
    		    else
    		    	cout << "Used space at index: " <<i<<" value:  "<< pages.at(i)<<endl;
    		}
    	}


};
#endif