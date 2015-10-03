#include "Ordonnanceur.h"
#include "Processus.h"
#include <iostream>
using namespace std;


Ordonnanceur::Ordonnanceur()
{
	
}

/// <return> the ID of the chosen processus <return>
int Ordonnanceur::ChooseProcessus(vector<Processus*> processus)
{
	vector<int> lotery;

	//Create the lotery
	for (int i = 0; i < processus.size(); i++)
	{
		///TODO if processus not blocked
		for (int j = 0; j < processus.at(i)->GetPriorite(); j++)
		{
			lotery.push_back(i);
		}
	}
	//Randomly Choose a processus
	int resultID = lotery.at(rand() % lotery.size());

	//Change Priority
	for (int i = 0; i < processus.size(); i++)
	{
		//Add to the priority if the random does not choose him (to give the processus more chances on next pass)
		if (i != resultID)
		{
			processus.at(i)->AddToPriorite(1);
		}
		//Reset priority if chosen
		else
		{
			processus.at(i)->setPriorite(1);
		}
	}

	return resultID;
}