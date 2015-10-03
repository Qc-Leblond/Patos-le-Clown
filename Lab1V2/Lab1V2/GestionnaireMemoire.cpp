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

void GestionnaireMemoire::updateProcessMemoryOnDisk(string diskFilename, Processus* process, int processID)
{
	//read disk to vector
	fstream disque;
	disque.open(diskFilename, ios::in);
	vector<CHAR> diskContent;
	int processPosition = processID * 32;
	while (!disque.eof())
	{
		CHAR line;
		disque >> line;
		diskContent.push_back(line);
	}

	//make modifications
	vector<memoryTuple> memChanges = process->getChangementsMemoire();
	for (int i = 0; i < memChanges.size(); i++)
	{
		diskContent[memChanges[i].indice + processPosition] = memChanges[i].valeur;
	}

	//write to disk from vector
	int indice = 0;
	while (!disque.eof())
	{
		disque << diskContent[indice];
		indice++;
	}
	disque.close();
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
