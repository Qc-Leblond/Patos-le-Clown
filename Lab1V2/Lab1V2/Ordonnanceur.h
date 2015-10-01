#pragma once
#include <vector>
using namespace std;

struct ProcessusTicket
{
	int id;
	int ticketNumber;

	ProcessusTicket(int _id, int _ticketNumber)
	{
		id = _id;
		ticketNumber = _ticketNumber;
	}
};

class Ordonnanceur
{
	vector<ProcessusTicket> processusList;

public:
	Ordonnanceur(vector<int>);
	Ordonnanceur();
	~Ordonnanceur(void);
	int ChooseProcessus(void);
};

