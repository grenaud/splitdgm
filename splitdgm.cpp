/*
 * splitdgm
 * Date: Dez-17-2018 
 * Author : Gabriel Renaud gabriel.reno [at sign here ] gmail.com
 *
 */

#include <iostream>
#include <fstream>

#include "utils.h"

using namespace std;

int main (int argc, char *argv[]) {

    string line;
    ifstream myFile;

   
    string infilename = string(argv[1]);
    string outfilename = string(argv[2]);

    int splits      = destringify<int>(argv[3]);
    ofstream myOFile[splits];   
    unsigned  int  bins[splits];   
    
    for(int i=0;i<splits;i++){
	cerr<<"writing to "<<(outfilename +"."+stringify(i)+".dgm")<<endl;
	myOFile[i].open( ( outfilename +"."+stringify(i)+".dgm").c_str(), ios::out);       	
    }
   
    myFile.open(infilename.c_str(), ios::in);
    unsigned int individuals;
    unsigned int lengthSites;

    
    if (myFile.is_open()){
	getline (myFile,line);
	vector<string> at = allTokens(line,' ');
	individuals =  destringify<unsigned int>( at[0] );
	lengthSites =  destringify<unsigned int>( at[1] );
	int upperbin = (lengthSites/splits)+1;
	int lowerbin = (lengthSites/splits);
	int chunks = (lengthSites%splits);
	for(int i=0;i<splits;i++){
	    if(i<chunks)
		bins[i] = upperbin;
	    else
		bins[i] = lowerbin;
	    cerr<<"file "<<(outfilename +"."+stringify(i)+".dgm") <<" will contain "<<bins[i]<<endl;
	    myOFile[i]<<individuals<<" "<<bins[i]<<endl; 
	}

	int lineNumber=1;
	while ( getline (myFile,line)){
	    cerr<<"processing line "<<(lineNumber++)<<" of "<<individuals<<endl;
	    vector<string> data = allTokens(line,'\t');
	    // for(unsigned int k=0;k<data.size();k++){
	    // 	cerr<<k<<" "<<data[k]<<endl;
	    // }
	    if(data.size() != lengthSites){
		cerr<<"ERROR: wrong number of sites "<<data.size()<<" "<<lengthSites<<endl;
		return 1;
	    }
	    
	    int          indexBin  =0;
	    string       toWrite   ="";
	    unsigned int counterRec=1;
	    
	    for(unsigned int k=0;k<lengthSites;k++){
		//cerr<<counterRec<<"bins["<<indexBin<<"] = "<<bins[indexBin]<<endl;
		if(counterRec == bins[indexBin]){
		    toWrite += data[k];
		    cerr<<"writing "<<(toWrite.length()+1)/2<<" records to "<<(outfilename +"."+stringify(indexBin)+".dgm")<<endl;

		    myOFile[indexBin]<<toWrite<<endl;
		    indexBin++;
		    counterRec=0;
		    toWrite="";
		}else{
		    toWrite += data[k]+"\t";
		}
		counterRec++;
	    }
	    //cerr<<"writingf "<<(toWrite.length()+1)/2<<" to "<<(outfilename +"."+stringify(indexBin)+".dgm")<<endl;
	    //	    myOFile[indexBin]<<toWrite<<endl;

	    cerr<<"done"<<endl;
	}
	myFile.close();
    }else{
	cerr << "Unable to open file "<<infilename<<endl;
	return 1;
    }

   
    for(int i=0;i<splits;i++){
	myOFile[i].close();
    }
   
    return 0;
}

