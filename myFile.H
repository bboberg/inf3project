/* 
* myFile.H
*
*/


#ifndef myFile_H_
#define myFile_H_


#include "SIMPLESOCKET.H"
#include <string>

using namespace std;

class MyTCPserver:public TCPserver{
public:
    MyTCPserver(int port, int maxDataSizeRecv) : TCPserver(port, maxDataSizeRecv){
        ;;
    }
protected:
    virtual string      myResponse(string input);
};

#endif /* myFile_H_ */