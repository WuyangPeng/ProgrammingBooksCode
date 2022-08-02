//This program uses a queue to hold numbers
//input by the user. The ServeQueue function
//removes the numbers from the queue and displays
//them to the screen.

#include <iostream>
#include <queue>		//for queue object
#include <string>

using namespace std;

//function declarations
void FillPlayList(queue<string> &rPeaPod);
void PlaySongs(queue<string> &rPeaPod);

int main()
{
	cout << "Welcome to the C++ Song Organizer ";
	queue<string> PeaPod;

	FillPlayList(PeaPod);
	PlaySongs(PeaPod);

	cout << "Thanks for listening! " << endl;

	return 0;
}

void FillPlayList(queue<string> &rPeaPod)
{
	cout << "\nPlease enter desired song titles"
			<< " for your PeaPod. "
			<< "\nEnter \"done\" when finished." << endl;
	
	string title = "not done";
	while(title != "done")
	{
		cout << "Title:  ";
		getline(cin,title);

		//push the title onto the queue
		if(title != "done") rPeaPod.push(title);
	}

	cout << "You have entered " << rPeaPod.size() 
		<< " titles for your listening pleasure. " << endl;
}

void PlaySongs(queue<string> &rPeaPod)
{
	cout << "\nNow playing .... \n";

	int totalSongs = rPeaPod.size();
	for(int i = 0; i < totalSongs; ++i)
	{
		//play the song at the front of the line
		cout << rPeaPod.front() << endl;

		//now pop it out of the line
		rPeaPod.pop();
	}
}

