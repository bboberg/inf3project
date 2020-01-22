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

int Shootrand(TCPclient *ptrC);


int main() {
	srand(time(NULL));
	TCPclient c;
	string host = "localhost";
	int shtNmb;


	//connect to host
	c.conn(host , 2022);

	cout << endl << "Reihe für Reihe Strategie (100 Durchläufe); Anzahl der Schüsse pro Durchlauf:" << endl;

	for(int i=0; i<100; i++){
		shtNmb = ShootALL(&c);
		cout << shtNmb << endl;
	}
	cout << endl;

	cout << endl << "Zufallsstrategie (100 Durchläufe); Anzahl der Schüsse pro Durchlauf:" << endl;

	for(int i=0; i<100; i++){
		shtNmb = Shootrand(&c);
		cout << shtNmb << endl;
	}
	cout << endl;
	
}

int ShootALL(TCPclient *ptrC){

	srand(time(NULL));
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
			sscanf(msg.c_str(), "RES[%d]", &r);

			if(r == 0){
				count++;
			}

			else if(r == 1){
				count++;
			}

			else if(r == 2){
				count++;
			}

			else if(r == 4){
				break;
			}

			else{
				cout << "Unknown: " << msg << endl;
			};
		}
		if(r == TASK3::GAME_OVER){
			break;
		};
	}
	return count;
}


int Shootrand(TCPclient *ptrC){

	srand(time(NULL));
	stringstream *sstm = NULL;
	string msg;
	int r, count=0;

	ptrC-> sendData(string("NEWGAME")); //start new Game
	msg = ptrC->receive(32);			//response

	while(msg.compare(0,5, "RES[4") != 0){
		if(sstm!=NULL){
				delete sstm;
			}

		int x = (rand() % 10)+1;
		int y = (rand() % 10)+1;

		sstm = new stringstream();
		*sstm << "COORD["<<x<<","<<y<<"]";
		ptrC->sendData(sstm->str());
		msg = ptrC -> receive(32);
		sscanf(msg.c_str(), "RES[%d]", &r);

		if(r <= 2){
			count++;
		}

		else if(r == 4){
			break;
		}

		else{
			cout << "Unknown: " << msg << endl;
		};
	}
	return count;
}

