/*
Noah Miller 9-2-19
This code is a C++ recreation of my original Secret Santa code, originally written in Python
Standalone class that simulates drawing names inputted by user out of a hat
Guarantees that people will not pick themself
Saves txt file of the pairs through a numerical pairing system for extra security
Gives the user the option to see the pairs through through the number system, by name, or not at all
Feel free to keep and use this code whenever you would like
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

//function declarations
void startShuffle();
void viewmenu(int[][2], int);
void printNames(int[][2], int);
void printNumbers(int[][2], int);
string toFile(int[][2], int);
void intro();
void ascii();


//global variables
vector<int> drawFrom; //holds values to pull from
string* nameList; //holds names to compare to number values

int main()
{
	intro();

	startShuffle();

	return 0;
}


void startShuffle()
{
	int numPeople, playerNum;
	string tempName;

	//get number of people in game
	cout << "How many people should be shuffled? ";
	cin >> numPeople;
	
	//setup lists to hold names
	nameList = new string[numPeople];
	auto namePairs = new int[numPeople][2]; //holds pairs in numerical system

	//get names and numbers
	cout << "Enter the first name: ";
	cin >> tempName;
	nameList[0] = tempName;
	namePairs[0][0] = 0;
	drawFrom.push_back(0);
	for (int x = 1; x < numPeople - 1; x++)
	{
		cout << "Enter the next name: ";
		cin >> tempName;
		nameList[x] = tempName;
		namePairs[x][0] = x;
		drawFrom.push_back(x);
	}
	cout << "Enter the last name: ";
	cin >> tempName;
	nameList[numPeople-1] = tempName;
	namePairs[numPeople-1][0] = numPeople - 1;
	drawFrom.push_back(numPeople - 1);

	srand(time(NULL));

	for (int y = 0; y < numPeople; y++)
	{
		playerNum = rand() % drawFrom.size();


		if (namePairs[y][0] != drawFrom[playerNum])
		{
			namePairs[y][1] = drawFrom[playerNum];
			drawFrom.erase(drawFrom.begin() + playerNum);
		}
		else
			y--;
	}

	cout << "\n\n\nThe program has now successfully shuffled the names and created pairs.";

	//menu for the user to view pairs
	viewmenu(namePairs, numPeople);
}

void intro()
{
	do
	{
		cout << " ---------------------------------------------------"
			<< "\n   Hello, and welcome to the Secret Santa code"
			<< "\n    This was originally created for my family"
			<< "\n      in Python v3, and is converted to C++."
			<< "\n     The code receives input from the user to"
			<< "\n  get a list of the people who wish to participate."
			<< "\n    It then acts as if they are drawing names."
			<< "\n  The user is then given options to view the pairs"
			<< "\n      and save them to a file for the future"
			<< "\n           or for a third party to use."
			<< "\n ---------------------------------------------------"
			<< "\n\n Press [Enter] to continue...";
	} while (cin.get() != '\n');
}

void viewmenu(int namePairs[][2], int numPeople)
{
	int input = 0;
	bool exit = false;
	do
	{
		cout << "\nYou may now choose what to do with the program. Will you:" <<
		"\n     [1] View the pairs of people using their inputted names" <<
		"\n     [2] View the pairs of people using their numerical code" <<
		"\n     [3] Save the pairs of people to a file with their numerical codes and its key" <<
		"\n     [4] Clear the terminal screen" << 
		"\n     [5] Exit (Waring: If you did not choose to save the pairs to a file,\n              the program will not store who is getting a gift for whom)\n";
		cin >> input;
		cout << "\n\n";

		switch (input)
		{
		case 1: printNames(namePairs, numPeople);
			break;
		case 2: printNumbers(namePairs, numPeople);
			break;
		case 3: toFile(namePairs, numPeople);
			break;
		case 4: system("CLS");
			break;
		case 5: cout << "Exiting Program" << endl;
			exit = true;
			break;
		case 25:ascii();
			break;
		default: cout << "Incorrect input. Please try again.\n";
			break;
		}
	} while (exit == false);
}


void printNames(int namePairs[][2], int numPeople)
{
	cout << "______ is getting a gift for ______\n";
	for (int z = 0; z < numPeople; z++)
	{
		cout << nameList[namePairs[z][0]] << " " << nameList[namePairs[z][1]] << endl;
	}
}

void printNumbers(int namePairs[][2], int numPeople)
{
	cout << "______ is getting a gift for ______\n";
	for (int z = 0; z < numPeople; z++)
	{
		cout << namePairs[z][0] << " " << namePairs[z][1] << endl;
	}
}


string toFile(int namePairs[][2], int numPeople)
{
	string success = "";
	string nameKey = "Names and their corresponding numerical key:\n";
	ofstream myfile;

	myfile.open("SantaList.txt");

	if (myfile.is_open())
	{
		for (int x = 0; x < numPeople; x++)
		{
			nameKey += nameList[x] + ": " + to_string(x) + " | ";
		}
		myfile << nameKey << endl << "______ is getting a gift for ______\n";

		for (int y = 0; y < numPeople; y++)
		{
			myfile << namePairs[y][0] << " " << namePairs[y][1] << endl;
		}
		myfile.close();
		success = "Successfully able to open and write pairing into SantaList.txt";
	}
	else
		success = "Unable to open file. Please try again.";


	return success;
}


void ascii()
{
	cout << R"(
                     _,.._                         __
                   ,'     '.                      /  `.
                  /        ,\                     |    \
  MERRY CHRISTMAS |;       ;;''-------.._         ;     \
     from the     \;;     ,;' _.-'       `.     .-.\     ;
       _  _ ___    ';;,,-''``''-._         \    '  \\    |
  |\ |/ \|_) | |_|     /          `'-._     |    \  '    ;
  | \|\_/| \ | | |     |               `.   |.-.  \     ;  _
    _  _     _         \_;,.._           ',/ |  |  |   /,'` `\
   |_)/ \|  |_      _,,_/` / .'-.          `,\  \  ;  ,'      |
   |  \_/|_ |_   ,-'  ,--'` |   o`-.        ;;|  `-' ;  .-    |
               ;`    /      '.__  O `'.     _/       | /`    /
              /      |_,--._,'  `.   | `.;/'  `'-. _ ;.-._,.'
              /    _,'      |    |'-'  / |   .--.,' '\o  )_
            .-;   `-..._     `-.-'     | \      _| O .'-'` `.
          /`  |         '-'7     \  |  |  |'--'` /'-'.--.    `.
        .| | <;            \      :-\  |  | ___ /    '._'     ;
       / '-\__)\            '.    ;__,/   ;`   | .-.          |
    ,.--.,  /   `.            \  /        |'--.\  |           /'-.
   /'     `;`     `,           '/        /'--.  `-`.         / _  \
   \,,-.   ;.       '-.._              ,'     `;    `-.___.-'`/'   |
   /    `-,'.'.     /     `'-.__   _,-'    .--'/             |     /
  /    ,  \  '.` f\/     /      `''`     /`   /              `.__.'\
 |     ;  |.   `/ .`'-._;             __.L   ;                  \  ;
 \    ,'`-' `._/ / `'-. |._____....--'_,-7\ /                   |   \
  `''` |;,     `-.`'-.| |__.....--'''`_,'`|;                    \_|  |
        \;,       `'-.__|__.,,__,,.."'`   ;|                      ;`-'
         `:_             `'`              / \                     /
            `._                    ,.__.-'   `._             mx .'
           .-,|`-...________.,---'`|_           `-....____..--'`
  ._       |   `.     ,-|     _,,,-' `.             \   |  /
    '-..   .-._, `''"/   `---''       |              `. | ;        _
        _,'   \;`-._ \_      _,-'`-.-'               _| | |_   .--'
     .'`           `'"`|"`"`-;/     `' -. -..__   ,-' ` |   `'. _
..--'\_       _,-'\___'    ,             |     ' / ,'  ,'.  `._) '-..
      ' `"'''`         '---'`-..._____.-'        '-'--'   `'-'


)" << endl;
}