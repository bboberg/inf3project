/* 
* myFile.H
*
*/


#ifndef myFile_H_
#define myFile_H_


#include "SIMPLESOCKET.H"
#include <string>

using namespace std;

class myTCPserver:public TCPserver{
protected:
    string      myResponse(string input);
};

