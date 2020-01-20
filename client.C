/*
 * client.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */

#include <string>
#include <iostream>
#include <sstream>
#include <unistd.h> //contains various constants
#include <time.h>



#include "SIMPLESOCKET.H"
#include "TASK3.H"

using namespace std;

int ShootALL(TCPclient *ptrC);

int main() {
	srand(time(NULL));
	TCPclient c;
	string host = "localhost";
	int shtNmb;


	//connect to host
	c.conn(host , 2022);

	cout << "Implementierung der simplen Reihe für Reihe Strategie:" << endl;

	shtNmb = ShootALL(&c);
	cout << shtNmb << endl;

}

int ShootALL(TCPclient *ptrC){

	stringstream *sstm = NULL;
	string msg;
	int r, count=0;

	ptrC-> sendData(string("NEWGAME")); //start new Game
	msg = ptrC->receive(32);			//response

	for(int x=1; x<=10; x++){
		
		for(int y=1; y<=10; y++){
			if(sstm!=NULL){
				delete sstm;
			}

			sstm = new stringstream();
			*sstm << "COORD["<<x<<","<<y<<"]";
			ptrC->sendData(sstm->str());
			msg = ptrC -> receive(32);

			if(0 == scanf(msg.c_str(), "RES[%d]", &r)){
				count++;
			}

			else{
				cout << "Unknown: " << msg << endl;
			}

			if(r == TASK3::GAME_OVER){
				break;
			};
		}
		if(r == TASK3::GAME_OVER){
			break;
		};
	}
	return count;
}
