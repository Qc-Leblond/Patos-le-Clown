#include <cstdlib>
#include <iostream>
#include <fstream>

#include "Processus.h"
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
	void setPC(CHAR pc)					{ PC = pc; }
	void setRegistre(CHAR registre)		{ Registre = registre; }
	void setState(CHAR state)			{ State = state; }
	void setRAM(CHAR indice, CHAR val)	{ RAM[indice] = val; }


	void run()
	{
		if (State != 'E') return;		// Pas ex�cutable

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
		case 5: // JMP  adresse	: Effectue un saut � l'adresse dans le registre et copie data dans le registre.
			PC = Registre;
			Registre = data;
			break;
		case 6: // JEQ  adresse	: Effectue un saut (jump) � adresse si la valeur du registre est �gale � 0.
			if (Registre == 0)	PC = data;
			else				PC++;
			break;
		case 7: //INT valeur	Effectue l'interruption data.
			if (data == 0)		// �crire � l'�cran
			{
				CHAR adresseData = (Registre & 31) + 32;
				cout << (RAM[adresseData] != 0 ? (char)(';' + RAM[adresseData]) : ' ');
			}
			if (data == 1)			// fin d'une ex�cution
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
void loadProgram(char* fileName);


CProcesseur CPU;
vector<Processus> processus;

int main(int nbr, char ** fileName)
{
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
	for (int i = 1; i < nbr; i++)
	{
		Processus p = new Processus(); //TODO: why?
		p.setRegistre(0);
		p.setPriorite(1);
		P.setState("ready"); //TODO: ???
		p.setPC(0);
		processus.push_back(p);
	}

	loadProgram(fileName[1]);

	CPU.setPC(0);
	CPU.setRegistre(0);

	while (CPU.retState() == 'E')
		CPU.run();

	cout << "fin normal" << endl;

	return 0;
}

//loadProgram should create a processus object 
//and put it in some collection
void loadProgram(char* fileName)
{
	ifstream file(fileName);

	int indice = 0;
	while (!file.eof())
	{
		int tamp = 0;
		file >> tamp;
		CPU.setRAM(indice, (CHAR)tamp);
		indice++;
	}
	file.close();
}


//TODO: fichier avec la m�moire de tous les processus au complet, avec acces � la m�moire
//�a agirait comme le disque dur, et la RAM est celle de l'objet CPU