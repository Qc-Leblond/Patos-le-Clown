#pragma once
#include <string>
#include "Processus.h"
using namespace std;
/**
* Le gestionnaire de m�moire devrait permettre de prendre la m�moire des processus du CPU et la mettre sur le disque.
* Il devrait aussi pouvoir mettre � jour la m�moire sur le disque selon les modifications de m�moire de chaque processus.
* Il devrait aussi pouvoir d�terminer les modifications apport�es � la m�moire d'un processus selon ses instructions (et peut-�tre au registre?)
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
	void updateProcessMemoryOnDisk(string diskFilename, Processus* process, int processID);

	//Detects modifications to a process' memory and add them to the process' memory changes
	void updateProcessMemoryModifications(string processFilename, Processus* process, CHAR* RAM);
};

