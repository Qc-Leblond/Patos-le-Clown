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
		if (lineCount >= 32)
		{
			disque << line + '\n';
		}
		lineCount++;
	}
	file.close();
	disque.flush();
	disque.close();
	return;
}

void GestionnaireMemoire::updateProcessMemoryOnDisk(string diskFilename, Processus process)
{
	//TODO
	return;
}

void GestionnaireMemoire::updateProcessMemoryModifications(string processFilename, Processus process)
{
	//TODO
	return;
}
