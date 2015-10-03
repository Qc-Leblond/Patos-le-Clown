#pragma once
#include <vector>
#include "Processus.h"
using namespace std;

class Ordonnanceur
{
public:
	Ordonnanceur();
	~Ordonnanceur(void);
	int ChooseProcessus(vector<Processus*>);
};

