#pragma once
#include <string>
#include "Processus.h"
using namespace std;
/**
* Le gestionnaire de mémoire devrait permettre de prendre la mémoire des processus du CPU et la mettre sur le disque.
* Il devrait aussi pouvoir mettre à jour la mémoire sur le disque selon les modifications de mémoire de chaque processus.
* Il devrait aussi pouvoir déterminer les modifications apportées à la mémoire d'un processus selon ses instructions (et peut-être au registre?)
* TODO: quoi d'autre?
*/
class GestionnaireMemoire
{


public:
	GestionnaireMemoire();
	~GestionnaireMemoire();

	//Gets memory of new processes and put it on disk,
	//appended to the memory already written in it
	void putMemoryOnDiskFrom(string processFilename, string diskFilename, int memorySize);

	//Update the memory that has changed in the process on the disk
	void updateProcessMemoryOnDisk(string diskFilename, Processus* process);

	//Detects modifications to a process' memory and add them to the process' memory changes
	void updateProcessMemoryModifications(string processFilename, Processus process, CHAR* RAM);
};

