#include "Processus.h"

/**
* Erases the previous memory changes from vector
*/
void Processus::eraseMemoryChanges()
{
	MemoireModifiee.erase(MemoireModifiee.begin(), MemoireModifiee.begin() + MemoireModifiee.size());
}

/**
* Retrieves the memory changes before/after next/last swap
*/
void Processus::setChangementMemoire(int _indice, CHAR _valeur)
{
	eraseMemoryChanges();
	memoryTuple memChange;
	memChange.indice = _indice;
	memChange.valeur = _valeur; 
	MemoireModifiee.push_back(memChange);
}

/*
* Returns the memory changes as a vector of (index, value) pairs from memory
*/
vector<memoryTuple> Processus::getChangementsMemoire()
{
	return MemoireModifiee;
}