#include "Ordonnanceur.h"
#include <iostream>
using namespace std;


Ordonnanceur::Ordonnanceur(vector<int> idProcessus)
{
	for (int i = 0; i < idProcessus.size(); i++) 
	{
		processusList.push_back(ProcessusTicket(idProcessus.back(), 1));
		idProcessus.pop_back();
	}
}

//For Debugging purpose
Ordonnanceur::Ordonnanceur()
{
	for (int i = 0; i < 3; i++) 
	{
		processusList.push_back(ProcessusTicket(i, 1));
	}

	for (int i = 0; i < 50; i++)
	{
		cout << "Processus " << ChooseProcessus() << endl;
	}
	while (true);
}

/// <return> the ID of the chosen processus <return>
int Ordonnanceur::ChooseProcessus()
{
	vector<int> lotery;

	//Create the lotery
	for (int i = 0; i < processusList.size(); i++)
	{
		///TODO if processus not blocked
		for (int j = 0; j < processusList.at(i).ticketNumber; j++)
		{
			lotery.push_back(processusList.at(i).id);
		}
	}
	//Randomly Choose a processus
	int resultID = lotery.at(rand() % lotery.size());

	//Change Priority
	for (int i = 0; i < processusList.size(); i++)
	{
		//Add to the priority if the random does not choose him (to give the processus more chances on next pass)
		if (processusList.at(i).id != resultID)
		{
			processusList.at(i).ticketNumber++;
		}
		//Reset priority if chosen
		else
		{
			processusList.at(i).ticketNumber = 1;
		}
	}

	return resultID;
}