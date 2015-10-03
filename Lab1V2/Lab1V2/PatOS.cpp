#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include "Processus.h"
#include "Ordonnanceur.h"
#include "GestionnaireMemoire.h"
using namespace std;


#define CHAR unsigned char
const int TAILLE = 32;

class CProcesseur
{
	CHAR*			RAM;
	CHAR			Registre;
	CHAR			PC;				// Program Counter
	CHAR			State;

public:
	CProcesseur()
	{
		RAM = new CHAR[TAILLE * 2];

		Registre = 0;
		PC = 0;
		State = 'E';
	}

	~CProcesseur()						{ delete RAM; }

	CHAR	retPC()						{ return PC; }
	CHAR	retRegistre()				{ return Registre; }
	CHAR	retState()					{ return State; }
	CHAR*	retRAM()					{ return RAM;  }
	void setPC(CHAR pc)					{ PC = pc; }
	void setRegistre(CHAR registre)		{ Registre = registre; }
	void setState(CHAR state)			{ State = state; }
	void setRAM(CHAR indice, CHAR val)	{ RAM[indice] = val; }


	void run()
	{
		if (State != 'E') return;		// Pas exécutable

		char no = (RAM[PC] & 224) >> 5;
		CHAR data = (RAM[PC] & 31);
		char adresseData = (RAM[PC] & 31) + 32;

		switch (no)
		{
		case 0: // CPY  valeur	: Copie valeur dans le registre.
			Registre = data;
			PC++;
			break;
		case 1: // RED [adresse]	: Copie le contenu d'adresse dans le registre.
			Registre = RAM[adresseData];
			PC++;
			break;
		case 2: // WRT [adresse]	: Copie le registre dans adresse.
			RAM[adresseData] = Registre;
			PC++;
			break;
		case 3: // ADD [adresse]	: Additionne la valeur dans adresse au registre.
			Registre += RAM[adresseData];
			PC++;
			break;
		case 4: // SUB  adresse	: Soustrait la valeur dans adresse au registre.
			Registre -= RAM[adresseData];
			PC++;
			break;
		case 5: // JMP  adresse	: Effectue un saut à l'adresse dans le registre et copie data dans le registre.
			PC = Registre;
			Registre = data;
			break;
		case 6: // JEQ  adresse	: Effectue un saut (jump) à adresse si la valeur du registre est égale à 0.
			if (Registre == 0)	PC = data;
			else				PC++;
			break;
		case 7: //INT valeur	Effectue l'interruption data.
			if (data == 0)		// écrire à l'écran
			{
				CHAR adresseData = (Registre & 31) + 32;
				cout << (RAM[adresseData] != 0 ? (char)(';' + RAM[adresseData]) : ' ');
			}
			if (data == 1)			// fin d'une exécution
				State = 'D';
			PC++;
			break;
		}
	}

	void afficherRAM(bool entete = true)
	{
		if (entete)
		{
			cout << endl;
			for (int x = 0; x < TAILLE * 2 / 4; x++)
				cout << "-" << (x % 10) << "-- ";
		}
		for (int x = 0; x < TAILLE; x++)
		{
			if (x % 4 == 0 && x != 0) cout << " ";
			cout << RAM[x] % 10;
		}

		for (int x = TAILLE; x < 2 * TAILLE; x++)
		{
			if (x % 4 == 0 && x != TAILLE) cout << " ";
			cout << (RAM[x] != 0 ? (char)(';' + RAM[x]) : '_');
		}
		cout << endl;
	}
};


// Prototype des fonctions
void loadProgram(char* fileName, string diskName);
bool CheckIfAllProcessusCompleted();


CProcesseur CPU;
vector<Processus*> processus;

int main(int nbr, char ** fileName)
{
	Ordonnanceur* ordonnanceur = new Ordonnanceur();
	GestionnaireMemoire *gestionnaireMemoire = new GestionnaireMemoire();

	string diskFilename = "memoire.txt";

	//missing filename arguments
	if (nbr < 2)
	{
		cout << "ExecPatOS.exe [nomDufichier.txt]" << endl;
		exit(-1);
	}

	//filename[0] if the executable path,
	//filename[1+] are the filenames passed as parameters
	//The number of parameters is not fixed
	//fills the processus vector collection with the active processes
	//fills the "disque" file with the memory of every process
	for (int i = 1; i < nbr; i++)
	{
		//set new processus object
		Processus *p = new Processus();
		p->setRegistre(0);
		p->setPriorite(1);
		p->setState('E');
		p->setPC(0);
		processus.push_back(p);

		//get memory from process and put it on "disk" (a text file)
		gestionnaireMemoire->putMemoryOnDiskFrom(fileName[i], diskFilename, TAILLE);
	}

	while (!CheckIfAllProcessusCompleted()) 
	{
		int processusID = ordonnanceur->ChooseProcessus(processus);
		loadProgram(fileName[processusID+1], diskFilename);
		CPU.setPC(processus[processusID]->getPC());
		CPU.setRegistre(processus[processusID]->getRegistre());

		for (int i = 0; i < 2; i++)
		{
			if (CPU.retState() == 'E')
			{
				CPU.run();
			}
		}
		//update the process' memory
		gestionnaireMemoire->updateProcessMemoryOnDisk(diskFilename, processus[processusID]);

		processus[processusID]->setPC(CPU.retPC());
		processus[processusID]->setRegistre(CPU.retRegistre());
	}

	cout << "fin normal" << endl;

	return 0;
}


void loadProgram(char* fileName, string diskName, int processusID)
{
	ifstream file(fileName);

	//Load the processus instruction
	for (int i = 0; i < 32; i++)
	{
		int tamp = 0;
		file >> tamp;
		CPU.setRAM(i, (CHAR)tamp);
	}

	file.close();

	ifstream disk(diskName);

	bool loaded = false;
	int index = 0;
	//Load memory from disk
	while (!loaded) {
		//Get to the right part of the memory
		int tamp = 0;
		index++;
		disk >> tamp;

		//When to the right part load memory to RAM
		if (index == 32 * processusID)
		{
			for (int i = 0; i < 32; i++)
			{
				disk >> tamp;
				CPU.setRAM(i + 32, (CHAR)tamp);
			}

			loaded = true;
		}
	}

	disk.close();
}

bool CheckIfAllProcessusCompleted()
{
	for (int i = 0; i < processus.size(); i++)
		if (processus.at(i)->GetState() == 'E') return false;

	return true;
} 
