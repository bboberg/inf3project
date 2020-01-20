/* 
* myFile.H
*
*/


#ifndef myFile_H_
#define myFile_H_


#include "SIMPLESOCKET.H"
#include "TASK3.H"
#include <string>
#include <cstdlib>

using namespace std;

class MyTCPserver:public TCPserver{
public:
    MyTCPserver(int port, int maxDataSizeRecv) : TCPserver(port, maxDataSizeRecv){
        srand(time(nullptr));
        w_ = new TASK3::World();
        //w_-> printBoard();
    }
protected:
    virtual string      myResponse(string input);
    TASK3::World *w_;
};

#endif /* myFile_H_ */