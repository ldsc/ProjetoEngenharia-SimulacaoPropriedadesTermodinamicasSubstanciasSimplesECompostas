#include <iostream>
#include <sstream>
#include <locale.h>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include "CSubstancia.h"

using namespace std;

//Construtores
CSubstancia::CSubstancia(const CSubstancia& obj){
	nomeSubs=obj.nomeSubs;
	tC=obj.tC;
	pC=obj.pC;
	omega=obj.omega;
}

CSubstancia::CSubstancia(string _nomeSubs, double _tC, double _pC, double _omega){
	nomeSubs=_nomeSubs;
	tC=_tC;
	pC=_pC;
	omega=_omega;
}

//Le o arquivo em disco e salva as propriedades da substancia
void CSubstancia::LerDadosDisco(string nomeSubs){	
	NomeSubs(nomeSubs);
	ifstream fin;
	string lixo=" ";
	fin.open("Substancias.txt");
        if(!fin) exit(0);
	while( lixo != nomeSubs and !fin.eof()){
		fin >> lixo;
	}
	fin >> tC;
	fin >> pC;
	fin >> omega;
	fin.close();
}
