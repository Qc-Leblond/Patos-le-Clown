#include "GestionnaireMemoire.h"


GestionnaireMemoire::GestionnaireMemoire()
{
}


GestionnaireMemoire::~GestionnaireMemoire()
{
}

void GestionnaireMemoire::putMemoryOnDiskFrom(string processFilename, string diskFilename, int size)
{
	ifstream file;
	ofstream disque;
	file.open(processFilename, ios::in); //ios::in -> read only
	disque.open(diskFilename, ios::app); //ios::app -> append to file instead of overwriting

	int lineCount = 0;
	for (int j = 0; j < size * 2; j++)
	{
		string line;
		file >> line;
		//skip the first 32 lines (the instructions)
		if (j >= 32)
		{
			disque << line + '\n';
		}
	}
	file.close();
	disque.flush();
	disque.close();
	return;
}

void GestionnaireMemoire::updateProcessMemoryOnDisk(string diskFilename, Processus* process)
{
	vector<memoryTuple> memChanges = process->getChangementsMemoire();
	for (int i = 0; i < memChanges.size(); i++)
	{

	}
	return;
}

void GestionnaireMemoire::updateProcessMemoryModifications(string processFilename, Processus process, CHAR* RAM)
{
	ifstream file;
	file.open(processFilename, ios::in);

	int lineCount = 0;
	for (int j = 0; j < 64; j++)
	{
		CHAR line;
		file >> line;
		//skip the first 32 lines (the instructions)
		if (j >= 32)
		{
			if (line != RAM[j])
			{
				//add a memory change to the process
				process.setChangementMemoire(j, RAM[j]);
			}
		}
	}
	file.close();




	return;
}
