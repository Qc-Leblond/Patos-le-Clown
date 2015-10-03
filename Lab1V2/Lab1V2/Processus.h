#pragma once
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#define CHAR unsigned char

// (index, value) pair from 
// detected memory changes
struct memoryTuple
{
	int indice;
	int valeur;
};

/*
* Class containing information about the active processes
*/
class Processus
{

	vector<memoryTuple> MemoireModifiee;
	int 				Priorite;
	CHAR				Registre;
	CHAR				PC;				// Compteur ordinal
	CHAR				State;

public:

	Processus() {}
	~Processus() {} //may cause error

	void setRegistre(CHAR reg) { Registre = reg; }
	void setPC(CHAR pc) { PC = pc; }
	void setState(CHAR state) { State = state; }
	void setPriorite(int priorite) { Priorite = priorite; }
	void AddToPriorite(int var) { Priorite += var;}

	int GetPriorite() {return Priorite;}
	CHAR GetState() {return State;}
	CHAR getRegistre() {return Registre;}
	CHAR getPC() {return PC;}

	void eraseMemoryChanges();

	void setChangementsMemoire(/*CHAR* ram*/);

	vector<memoryTuple> getChangementsMemoire();

};