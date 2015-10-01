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
* TODO: from instructions or from memory directly?
* Would be more efficient from instructions, but also more complex...
* needs to be able to take any length of memory, from 32B to 4GB
*/
void Processus::setChangementsMemoire(/*CHAR* ram*/) //TODO: take next instructions as param instead?
{
	eraseMemoryChanges();
	while (false) //TODO: which condition?
	{
		memoryTuple memChange;
		memChange.indice = 000; //TODO
		memChange.valeur = 111; //TODO
		MemoireModifiee.push_back(memChange);
	}
}

/*
* Returns the memory changes as a vector of (index, value) pairs from memory
*/
vector<memoryTuple> Processus::getChangementsMemoire()
{
	return MemoireModifiee;
}