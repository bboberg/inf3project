/*
 * client.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */

#include <string>
#include <iostream>
#include <unistd.h> //contains various constants

#include "SIMPLESOCKET.H"

using namespace std;

int main() {
	srand(time(NULL));
	TCPclient c;
	string host = "localhost";
	string msg;
	int maxX=10, maxY=10;

	//connect to host
	c.conn(host , 2022);

	bool goOn=1;
	while(goOn){ // send and receive data
		/*if((rand() % 20) < i++){
			msg = string("BYEBYE");
			goOn = 0;
		}else{
			msg = string("client wants this");
		}*/

		for(int i=1; i>=maxX; i++){
			for(int u=1; u<=maxY; u++){
				msg = string("COORD[%d, %d]", &i, &u);
				cout << "client sends:" << msg << endl;
				c.sendData(msg);
				msg = c.receive(32);
				cout << "got response:" << msg << endl;
			}
		}

		sleep(1);

	}
}

