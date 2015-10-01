#include <cstdlib>
#include <iostream>
#include <fstream>
#include "Ordonnanceur.h"
using namespace std;


#define CHAR unsigned char
const int TAILLE = 32;


class CProcesseur
{
	CHAR*			RAM;
	CHAR			Registre;
	CHAR			PC;				// Program Counter
	CHAR			State;

public :
	CProcesseur()
	{
		RAM = new CHAR[TAILLE*2];

		Registre	= 0;
		PC			= 0;
		State		= 'E';
	}

	~CProcesseur()						{ delete RAM;			}	

	CHAR	retPC()						{ return PC;			}
	CHAR	retRegistre()				{ return Registre;		}
	CHAR	retState()					{ return State;			}
	void setPC(CHAR pc)					{ PC = pc;				}
	void setRegistre(CHAR registre)		{ Registre = registre;	}
	void setState(CHAR state)			{ State = state;		}
	void setRAM(CHAR indice, CHAR val)	{ RAM[indice] = val;	}


	void run()
	{
		if (State != 'E') return;		// Pas exécutable

		char no				= (RAM[PC] & 224) >> 5;
		CHAR data			= (RAM[PC] & 31);
		char adresseData	= (RAM[PC] & 31) + 32;
	
		switch (no)
		{
		case 0	: // CPY  valeur	: Copie valeur dans le registre.
				Registre = data;
				PC++;
				break;
		case 1	: // RED [adresse]	: Copie le contenu d'adresse dans le registre.
				Registre = RAM[adresseData];
				PC++;
				break;
		case 2	: // WRT [adresse]	: Copie le registre dans adresse.
				RAM[adresseData] = Registre;
				PC++;
				break;
		case 3	: // ADD [adresse]	: Additionne la valeur dans adresse au registre.
				Registre += RAM[adresseData];
				PC++;
				break;
		case 4	: // SUB  adresse	: Soustrait la valeur dans adresse au registre.
				Registre -= RAM[adresseData];
				PC++;
				break;
		case 5	: // JMP  adresse	: Effectue un saut à l'adresse dans le registre et copie data dans le registre.
				PC = Registre;
				Registre = data;
				break;
		case 6	: // JEQ  adresse	: Effectue un saut (jump) à adresse si la valeur du registre est égale à 0.
				if (Registre == 0)	PC = data;
				else				PC++;
				break;
		case 7	: //INT valeur	Effectue l'interruption data.
				if (data == 0)		// écrire à l'écran
				{
					CHAR adresseData = (Registre & 31) + 32;
					cout << (RAM[adresseData] != 0 ? (char)(';' + RAM[adresseData]) : ' ');
				}
				if(data==1)			// fin d'une exécution
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
			for (int x = 0; x < TAILLE*2 / 4; x++)
				cout << "-" << (x % 10) << "-- ";
		}
		for (int x = 0; x < TAILLE; x++)
		{
			if (x % 4 == 0 && x != 0) cout << " ";
			cout << RAM[x] % 10 ;
		}

		for (int x = TAILLE; x < 2*TAILLE ; x++)
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


int main(/* int nbr, char ** fileName*/)
{
	Ordonnanceur* ordonnanceur = new Ordonnanceur();
	/*if (nbr < 2)
	{
		cout << "ExecPatOS.exe [nomDufichier.txt]" << endl;
		exit(-1);
	}
	
	loadProgram(fileName[1]);

	CPU.setPC(0);
	CPU.setRegistre(0);

	while (CPU.retState() == 'E')
		CPU.run();

	cout << "fin normal" << endl;*/

	return 0;
}

void loadProgram(char* fileName)
{
	ifstream file(fileName);

	int indice = 0;
	while (!file.eof())
	{
		int tamp = 0;
		file >> tamp;
		CPU.setRAM(indice, (CHAR)tamp);
		indice ++;		
	}
	file.close();
}