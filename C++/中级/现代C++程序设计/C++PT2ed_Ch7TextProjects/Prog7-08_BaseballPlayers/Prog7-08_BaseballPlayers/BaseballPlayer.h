//File: BaseballPlayer.h

#ifndef _BBP_H
#define _BBP_H

#include <string> 
using namespace std;

class BaseballPlayer
{
	private:
		string name;
		int homers, RBI;

	public:
		BaseballPlayer();
		BaseballPlayer(string n, int h, int rbi);

		void setName(string n){name = n;}
		void setHomers(int num){homers = num;}
		void setRBIs(int rbi){RBI = rbi;}
		void WritePlayerStats();

		string GetName(){ return name; }

		//The > operator "bigger" if homers is larger
		//If same number of homers, greater RBIs is larger
		bool operator > (BaseballPlayer bbp);
		bool operator < (BaseballPlayer bbp);

		//The ! operator increments the number of homers.
		void operator !();
};

#endif
