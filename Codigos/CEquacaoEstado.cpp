#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <iomanip>
#include <locale>
#include <sstream>
#include "CEquacaoEstado.h"
#include <algorithm>

using namespace std;

//Construtores
CEquacaoEstado::CEquacaoEstado(CEquacaoEstado& obj){
	vsubstancia=obj.vsubstancia;
	tR=obj.tR;
	a=obj.a;
	b=obj.b;
	kappa=obj.kappa;
	alpha=obj.alpha;
	aT=obj.aT;
	bT=obj.bT;
	aMaiusculo=obj.aMaiusculo;
	bMaiusculo=obj.bMaiusculo;
	aij=obj.aij;
	aMix=obj.aMix;
	bMix=obj.bMix;	
	z=obj.z;
	fugacidade=obj.fugacidade;
	R=8.314e-5;
}

CEquacaoEstado::CEquacaoEstado(double R, vector<CSubstancia> _vsubstancia, vector<double> _tR, vector<double> _a, vector<double> _b, vector<double> _kappa, vector<double> _alpha, double _aT, double _bT, double _aMaiusculo, double _bMaiusculo, double _aij, double _interecao, double _aMix, double _bMix, vector<long double> _z, vector<double> _fugacidade){
	vsubstancia=_vsubstancia;
	tR=_tR;
	a=_a;
	b=_b;
	kappa=_kappa;
	alpha=_alpha;
	aT=_aT;
	bT=_bT;
	aMaiusculo=_aMaiusculo;
	bMaiusculo=_bMaiusculo;
	aij=_aij;
	aMix=_aMix;
	bMix=_bMix;
	z=_z;
	fugacidade=_fugacidade;
	R=8.314e-5;
}

//Obter os dados da substancia selecionada pelo usuario e armazenar no vetor vsubstancia
void CEquacaoEstado::ObterDadosSubstancia(int quantSubs){
	CSubstancia subs;
	string nomeSubs;
	cout << "\nAs substancias possiveis sao: \nmetano \netano \npropano \nisobutano \nnbutano \nisopentano \nnpentano \nnhexano \nnheptano \nnoctano \nndecano \nndodecano \nco2 \nnitrogenio \nh2s \nh2o \n\n";
	for (int i=0;i<quantSubs;i++){
		cout << "\nQual a substancia " << i+1 << " ?" << endl;		
		getline (cin, nomeSubs);
		subs.LerDadosDisco(nomeSubs);
		vsubstancia.push_back(subs);
		}
}

//Calcula Propriedades termodinamicas para 1 substancia
void CEquacaoEstado::CalcularPropriedadesTermodinamicas(double T, double P, vector<long double> z, std::vector<double> fugacidade, std::vector<CSubstancia> vsubs){
	vector<double> densidade;
	for (int i=0;i<2;i++)
		densidade.push_back(P/(R*T*z[i]));
	cout << "Molecula: "<< vsubs[0].NomeSubs()<<endl;
	cout << "Temperatura Critica: "<< vsubs[0].TC()<< " K"<<endl;
	cout << "Pressao Critica: "<<vsubs[0].PC()<< " bar"<<endl;
	cout << "Fator acentrico: "<<vsubs[0].Omega()<<endl;
	if (z[0]==z[1]){
		cout << "So existe uma fase."<<endl;
		cout << "Fator de compressibilidade: "<<z[0]<<endl;
		cout << "Coeficiente de fugacidade: "<< fugacidade[0]<<endl;
		cout << "Fugacidade em "<< P << " bar: " << fugacidade[0]*P << " bar"<<endl;
		cout << "Densidade: " << densidade[0]<< " mol/m^3"<<endl;
		cout << "Volume especifico: " << 1./densidade[0]<< " m^3/mol"<<endl;
		cout << "Volume molar: " << 1000./densidade[0]<< " L/mol"<<endl;
	}
	else{
		cout << "As fases liquido e vapor coexistem."<<endl;
		cout << "Fator de compressibilidade (liquido): "<<z[0]<<endl;
		cout << "Fator de compressibilidade (vapor): "<<z[1]<<endl;
		cout << "Coeficiente de fugacidade (liquido): "<< fugacidade[0]<<endl;
		cout << "Coeficiente de fugacidade (vapor): "<< fugacidade[1]<<endl;
		cout << "Fugacidade em "<< P << " bar (liquido): " << fugacidade[0]*P<< " bar"<<endl;
		cout << "Fugacidade em "<< P << " bar (vapor): " << fugacidade[1]*P<< " bar"<<endl;
		cout << "Densidade (liquido): " << densidade[0]<< " mol/m^3"<<endl;
		cout << "Densidade (vapor): " << densidade[1]<< " mol/m^3"<<endl;
		cout << "Volume especifico (liquido): " << 1./densidade[0]<< " m^3/mol"<<endl;
		cout << "Volume especifico (vapor): " << 1./densidade[1]<< " m^3/mol"<<endl;
		cout << "Volume molar (liquido): " << 1000./densidade[0]<< " L/mol"<<endl;
		cout << "Volume molar (vapor): " << 1000./densidade[1]<< " L/mol"<<endl;
	}
}

//Calcula Propriedades termodinamicas para 2 substancias
void CEquacaoEstado::CalcularPropriedadesTermodinamicas(double T, double P, vector<long double> z, std::vector<double> fugacidade, std::vector<CSubstancia> vsubs, std::vector<double> x){
	vector<double> densidade;
	for (int i=0;i<2;i++)
		densidade.push_back(P/(R*T*z[i]));
	if (z[0]==z[1]){
		cout << "So existe uma fase."<<endl;
		cout << "Densidade: " << densidade[0]<< " mol/m^3"<<endl;
		cout << "Volume especifico: " << 1./densidade[0]<< " m^3/mol"<<endl;
		cout << "Volume molar: " << 1000./densidade[0]<< " L/mol"<<endl;
		cout << "Fator de compressibilidade: "<<z[0]<<endl;
		cout << "Componente A: "<< vsubs[0].NomeSubs()<<endl;
		cout << "Coeficiente de fugacidade: "<< fugacidade[0]<<endl;
		cout << "Fugacidade em "<< P << " bar: " << fugacidade[0]*P*x[0]<< " bar"<<endl;
		cout << "Componente B: "<< vsubs[1].NomeSubs()<<endl;
		cout << "Coeficiente de fugacidade: "<< fugacidade[1]<<endl;
		cout << "Fugacidade em "<< P << " bar: " << fugacidade[1]*P*x[1]<< " bar"<<endl;
	}
	else{
		cout << "As fases liquido e vapor coexistem."<<endl;
		cout << "Densidade (liquido): " << densidade[0]<< " mol/m^3"<<endl;
		cout << "Densidade (vapor): " << densidade[1]<< " mol/m^3"<<endl;
		cout << "Volume especifico (liquido): " << 1./densidade[0]<< " m^3/mol"<<endl;
		cout << "Volume especifico (vapor): " << 1./densidade[1]<< " m^3/mol"<<endl;
		cout << "Volume molar (liquido): " << 1000./densidade[0]<< " L/mol"<<endl;
		cout << "Volume molar (vapor): " << 1000./densidade[1]<< " L/mol"<<endl;
		cout << "Fator de compressibilidade (liquido): "<<z[0]<<endl;
		cout << "Fator de compressibilidade (vapor): "<<z[1]<<endl;
		cout << "Componente A: "<< vsubs[0].NomeSubs()<<endl;
		cout << "Coeficiente de fugacidade (liquido): "<< fugacidade[0]<<endl;
		cout << "Fugacidade em "<< P << " bar (liquido): " << fugacidade[0]*P*x[0]<< " bar"<<endl;
		cout << "Coeficiente de fugacidade (vapor): "<< fugacidade[1]<<endl;
		cout << "Fugacidade em "<< P << " bar (vapor): " << fugacidade[1]*P*x[0]<< " bar"<<endl;
		cout << "Componente B: "<< vsubs[1].NomeSubs()<<endl;
		cout << "Coeficiente de fugacidade (liquido): "<< fugacidade[2]<<endl;
		cout << "Fugacidade em "<< P << " bar (liquido): " << fugacidade[2]*P*x[1]<< " bar"<<endl;
		cout << "Coeficiente de fugacidade (vapor): "<< fugacidade[3]<<endl;
		cout << "Fugacidade em "<< P << " bar (vapor): " << fugacidade[3]*P*x[1]<< " bar"<<endl;
	}	
}

//Salvar em disco propriedades termodinamicas para 1 substancia
void CEquacaoEstado::SalvarPropriedadesTermodinamicasDisco(double T, double P, vector<long double> z, std::vector<double> fugacidade, std::vector<CSubstancia> vsubs, std::string nome){
	vector<double> densidade;
	for (int i=0;i<2;i++)
		densidade.push_back(P/(R*T*z[i]));
	nome=nome+".txt";
	ofstream fout;
	fout.open(nome.c_str());
	fout << "Simulacao de " << nome << endl;
	fout << "Molecula: "<< vsubs[0].NomeSubs()<<endl;
	fout << "Temperatura Critica: "<< vsubs[0].TC()<< " K"<<endl;
	fout << "Pressao Critica: "<<vsubs[0].PC()<< " bar"<<endl;
	fout << "Fator acentrico: "<<vsubs[0].Omega()<<endl;
	if (z[0]==z[1]){
		fout << "So existe uma fase."<<endl;
		fout << "Fator de compressibilidade: "<<z[0]<<endl;
		fout << "Coeficiente de fugacidade: "<< fugacidade[0]<<endl;
		fout << "Fugacidade em "<< P << " bar: " << fugacidade[0]*P << " bar"<<endl;
		fout << "Densidade: " << densidade[0]<< " mol/m^3"<<endl;
		fout << "Volume especifico: " << 1./densidade[0]<< " m^3/mol"<<endl;
		fout << "Volume molar: " << 1000./densidade[0]<< " L/mol"<<endl;
	}
	else{
		fout << "As fases liquido e vapor coexistem."<<endl;
		fout << "Fator de compressibilidade (liquido): "<<z[0]<<endl;
		fout << "Fator de compressibilidade (vapor): "<<z[1]<<endl;
		fout << "Coeficiente de fugacidade (liquido): "<< fugacidade[0]<<endl;
		fout << "Coeficiente de fugacidade (vapor): "<< fugacidade[1]<<endl;
		fout << "Fugacidade em "<< P << " bar (liquido): " << fugacidade[0]*P<< " bar"<<endl;
		fout << "Fugacidade em "<< P << " bar (vapor): " << fugacidade[1]*P<< " bar"<<endl;
		fout << "Densidade (liquido): " << densidade[0]<< " mol/m^3"<<endl;
		fout << "Densidade (vapor): " << densidade[1]<< " mol/m^3"<<endl;
		fout << "Volume especifico (liquido): " << 1./densidade[0]<< " m^3/mol"<<endl;
		fout << "Volume especifico (vapor): " << 1./densidade[1]<< " m^3/mol"<<endl;
		fout << "Volume molar (liquido): " << 1000./densidade[0]<< " L/mol"<<endl;
		fout << "Volume molar (vapor): " << 1000./densidade[1]<< " L/mol"<<endl;
	}
	fout.close();
}

//Salvar em disco Propriedades termodinamicas para 2 substancias
void CEquacaoEstado::SalvarPropriedadesTermodinamicasDisco(double T, double P, vector<long double> z, std::vector<double> fugacidade, std::vector<CSubstancia> vsubs, std::vector<double> x, std::string nome){
	vector<double> densidade;
	for (int i=0;i<2;i++)
		densidade.push_back(P/(R*T*z[i]));
	nome=nome+".txt";
	ofstream fout;
	fout.open(nome.c_str());
	fout << "Simulacao de " << nome<< endl;
	if (z[0]==z[1]){
		fout << "So existe uma fase."<<endl;
		fout << "Densidade: " << densidade[0]<< " mol/m^3"<<endl;
		fout << "Volume especifico: " << 1./densidade[0]<< " m^3/mol"<<endl;
		fout << "Volume molar: " << 1000./densidade[0]<< " L/mol"<<endl;
		fout << "Fator de compressibilidade: "<<z[0]<<endl;
		fout << "Componente A: "<< vsubs[0].NomeSubs()<<endl;
		fout << "Coeficiente de fugacidade: "<< fugacidade[0]<<endl;
		fout << "Fugacidde em "<< P << " bar: " << fugacidade[0]*P*x[0]<< " bar"<<endl;
		fout << "Componente B: "<< vsubs[1].NomeSubs()<<endl;
		fout << "Coeficiente de fugacidade: "<< fugacidade[1]<<endl;
		fout << "Fugacidade em "<< P << " bar: " << fugacidade[1]*P*x[1]<< " bar"<<endl;
	}
	else{
		fout << "As fases liquido e vapor coexistem."<<endl;
		fout << "Densidade (liquido): " << densidade[0]<< " mol/m^3"<<endl;
		fout << "Densidade (vapor): " << densidade[1]<< " mol/m^3"<<endl;
		fout << "Volume especifico (liquido): " << 1./densidade[0]<< " m^3/mol"<<endl;
		fout << "Volume especifico (vapor): " << 1./densidade[1]<< " m^3/mol"<<endl;
		fout << "Volume molar (liquido): " << 1000./densidade[0]<< " L/mol"<<endl;
		fout << "Volume molar (vapor): " << 1000./densidade[1]<< " L/mol"<<endl;
		fout << "Fator de compressibilidade (liquido): "<<z[0]<<endl;
		fout << "Fator de compressibilidade (vapor): "<<z[1]<<endl;
		fout << "Componente A: "<< vsubs[0].NomeSubs()<<endl;
		fout << "Coeficiente de fugacidade (liquido): "<< fugacidade[0]<<endl;
		fout << "Fugacidade em "<< P << " bar (liquido): " << fugacidade[0]*P*x[0]<< " bar"<<endl;
		fout << "Coeficiente de fugacidade (vapor): "<< fugacidade[1]<<endl;
		fout << "Fugacidade em "<< P << " bar (vapor): " << fugacidade[1]*P*x[0]<< " bar"<<endl;
		fout << "Componente B: "<< vsubs[1].NomeSubs()<<endl;
		fout << "Coeficiente de fugacidade (liquido): "<< fugacidade[2]<<endl;
		fout << "Fugacidde em "<< P << " bar (liquido): " << fugacidade[2]*P*x[1]<< " bar"<<endl;
		fout << "Coeficiente de fugacidade (vapor): "<< fugacidade[3]<<endl;
		fout << "Fugacidade em "<< P << " bar (vapor): " << fugacidade[3]*P*x[1]<< " bar"<<endl;
	}
	fout.close();	
}
