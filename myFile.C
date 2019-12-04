/* 
* myFile.C
*
*/

#include "myFile.H"
#include "TASK3.H"
#include <iostream>
#include <sstream>

using namespace std;

string MyTCPserver::myResponse(string input){
	std::stringstream ss;
	int x,y;
	TASK3::ShootResult result;

	if(input.compare(0,6,"COORD[") ==0 ){
		if(2!=sscanf(input.c_str(), "COORD[%d,%d]", &x,&y) ){
			return string("ERR[-1]");
		}

		if( (x<1) || (y<1) || (x>10) || (y>10) ){
			return string("ERR[-2]");
		}

		result = (TASK3::ShootResult) (rand() % 6);
		ss << "RES[" << result << "]";
		return ss.str();
	};

	if(input.compare(0,7,"NEWGAME") == 0 ){
		return string("OK");
	};

	return string("NOT PROCESSABLE COMMAND");
}

/*namespace myFile{

void myTask(){

}*/