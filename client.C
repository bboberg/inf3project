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

int shootALL(TCPclient *ptrC);
int Shootrand(TCPclient *ptrC);
int shootAdvanced(TCPclient *ptrC);
int oneShoot(TCPclient *ptrC, int x, int y);
float mittelwertshootAdvanced(TCPclient *c, int n);

int main() {
	srand(time(NULL));
	TCPclient c;
	string host = "localhost";
	float shtNmb;


	//connect to host
	c.conn(host , 2022);

	cout << endl << "Implementierung der simplen Reihe für Reihe Strategie:" << endl;

	for(int i=1;i<=10;i++){							//Change number of process
		shtNmb = shootALL(&c);
		cout << i << ".: " << shtNmb << endl;
	}

	cout << endl << "Implementierung der Zufallsbeschuss-Strategie:" << endl;

	for(int i=1;i<=10;i++){							//Change number of process
		shtNmb = Shootrand(&c);
		cout << i << ".: " << shtNmb << endl;
	}	

	cout << endl << "Implementierung der alle-zwei-Felder-Strategie:" << endl;

	shtNmb = mittelwertshootAdvanced(&c,10);		//Change number of process
	cout << "MEAN: " << shtNmb << endl;

}
float mittelwertshootAdvanced(TCPclient *c, int n)
{
	float shtNmb=0;
	int r;
	int min=100;
	int max=0;
	for(int i=1;i<=n;i++)
	{
		r = shootAdvanced(c);
		if(r<min)
		{
			min=r;
		}
		if(r>max)
		{
			max=r;
		}
		shtNmb = shtNmb + r;
		cout << i << ".: " << r << endl;
	}
	shtNmb=(float)shtNmb/n;
	cout << endl << "Minimum: "<<min<<"  Maximum: "<<max<<endl;
	return shtNmb;
}

int oneShoot(TCPclient *ptrC, int x, int y){
	int r; 
	string msg;
	stringstream *sstm = new stringstream();
	*sstm << "COORD["<<x<<","<<y<<"]";
	ptrC->sendData(sstm->str());
	msg = ptrC -> receive(32);

	sscanf(msg.c_str(), "RES[%d]", &r);
	return r;
}

int shootALL(TCPclient *ptrC){

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

				r = oneShoot(ptrC, x,y);
				count++;

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

int shootAdvanced(TCPclient *ptrC){

	stringstream *sstm = NULL;
	string msg;
	int r, count=0, startY;

	r = 0;
	ptrC-> sendData(string("NEWGAME")); //start new Game
	msg = ptrC->receive(32);			//response

	for(int x=1; x<=10; x++){
		if( (x%2) == 1){
			startY = 1;
		}else{
			startY = 2;
		}

		for(int y=startY; y<=10; y=y+2){
			if(sstm!=NULL){
					delete sstm;
			}

			if(r == TASK3::GAME_OVER){
				break;
			}

			r = oneShoot(ptrC, x,y);
			count++;

			if(r==1){//beschiesse umgebung
				if(x!=10){
					r = oneShoot(ptrC, x+1,y);
					count++;
					if(r == TASK3::SHIP_DESTROYED){
						continue;
					};
				};
				if(x!=1){
					r = oneShoot(ptrC, x-1,y);
					count++;
					if(r == TASK3::SHIP_DESTROYED){
						continue;
					};
				};
				if(y!=10){	
					r = oneShoot(ptrC, x,y+1);
					count++;
					if(r == TASK3::SHIP_DESTROYED){
						continue;
					};
				};
				if(y!=1){
					r = oneShoot(ptrC, x,y-1);
					count++;
					if(r == TASK3::SHIP_DESTROYED){
						continue;
					};
				};
			};
		}
		if(r == TASK3::GAME_OVER){
			break;
		}
	};
	
	return count;
}

