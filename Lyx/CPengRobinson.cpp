#include "CPengRobinson.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

//Construtores
CPengRobinson::CPengRobinson(CPengRobinson& obj){
	vsubstancia=obj.vsubstancia;
	tR=obj.tR;
	a=obj.a;
	b=obj.b;
	kappa=obj.kappa;
	alpha=obj.alpha;
	aT=obj.aT;
	aMaiusculo=obj.aMaiusculo;
	bMaiusculo=obj.bMaiusculo;
	aij=obj.aij;
	aMix=obj.aMix;
	bMix=obj.bMix;
	fugacidade=obj.fugacidade;
}
CPengRobinson::CPengRobinson(vector<CSubstancia> _vsubstancia, vector<double> _tR, vector<double> _a, vector<double> _b, vector<double> _kappa, vector<double> _alpha, double _aT, double _aMaiusculo, double _bMaiusculo, double _aij, double _interecao, double _aMix, double _bMix, vector<double> _fugacidade){
	vsubstancia=_vsubstancia;
	tR=_tR;
	a=_a;
	b=_b;
	kappa=_kappa;
	alpha=_alpha;
	aT=_aT;
	aMaiusculo=_aMaiusculo;
	bMaiusculo=_bMaiusculo;
	aij=_aij;
	aMix=_aMix;
	bMix=_bMix;
	fugacidade=_fugacidade;	
}

//Calcula parametros PR para 1 substancia
double CPengRobinson::CalcularParametros(double T, double P){
		a.push_back(0.457235 * pow(R,2) * pow(vsubstancia[0].TC(),2) / vsubstancia[0].PC());
		b.push_back(0.0777961 * R * vsubstancia[0].TC()/vsubstancia[0].PC());
		kappa.push_back(0.37464 + 1.54226 * vsubstancia[0].Omega() - 0.26992 * pow(vsubstancia[0].Omega(),2));
		tR.push_back(T/vsubstancia[0].TC());
		alpha.push_back(pow(1 + kappa[0] * (1 - sqrt(tR[0])),2));
		aT=a[0]*alpha[0];
		bT=b[0];
		aMaiusculo=aT*P/pow(R,2)/pow(T,2);
		bMaiusculo=bT*P/R/T;
		return aMaiusculo;
		return bMaiusculo;
}
//Calcula parametros PR para 2 substancias
double CPengRobinson::CalcularParametros(double T, double P, vector<double> x, double interacao){
	for(int i=0;i<2;i++){
		a.push_back(0.457235 * pow(R,2) * pow(vsubstancia[i].TC(),2) / vsubstancia[i].PC());
		b.push_back(0.0777961 * R * vsubstancia[i].TC()/vsubstancia[i].PC());
		kappa.push_back(0.37464 + 1.54226 * vsubstancia[i].Omega() - 0.26992 * pow(vsubstancia[i].Omega(),2));
		tR.push_back(T/vsubstancia[i].TC());
		alpha.push_back(a[i]*pow(1 + kappa[i] * (1 - sqrt(tR[i])),2));		
	}
	aij=(1.0 - interacao) * sqrt(a[0] * a[1]);
	aMix=alpha[0] * pow(x[0],2) + alpha[1] * pow(x[1],2) + 2.0 * x[0] * x[1] * aij;
	bMix= x[0] * b[0] + x[1] * b[1];
	aT=aMix;
	bT=bMix;
	aMaiusculo=aT*P/pow(R,2)/pow(T,2);
	bMaiusculo=bT*P/R/T;
	return aMaiusculo;
	return bMaiusculo;
	return aMix;
	return bMix;
}

void CPengRobinson::ObterDadosSubstancia(int quantSubs){
	CEquacaoEstado::ObterDadosSubstancia(quantSubs);
}

//Calcula fugacidade PR para 1 substancia
vector<double> CPengRobinson::CalcularFugacidade(vector<long double> z, double aM, double bM){
	for(int i=0;i<z.size();i++)
		fugacidade.push_back(exp(z[i] - 1 - log(z[i] - bM) - aM / sqrt(8.) / bM * log((z[i] + (1 + sqrt(2)) * bM) / (z[i] + (1. - sqrt(2.)) * bM))));
	return fugacidade;
}

//Calcula fugacidade PR para 2 substancias
vector<double> CPengRobinson::CalcularFugacidade(vector<long double> z, double aM, double bM, double bMix, double aMix, vector<double> x){
	for (int i=0;i<2;i++)
		fugacidade.push_back(exp(-log(z[i] - bM) + (z[i] - 1.0) * b[0] / bMix - aM / sqrt(8.) / bM * (2.0 / aMix * (x[0] * a[0] + x[1] * aij) - b[0] / bMix) * log((z[i] + (1.0 + sqrt(2)) * bM) / (z[i] + (1.0 - sqrt(2.)) * bM))));
	for (int i=0;i<2;i++)
		fugacidade.push_back(exp(-log(z[i] - bM) + (z[i] - 1.0) * b[1] / bMix - aM / sqrt(8.) / bM * (2.0 / aMix * (x[1] * a[1] + x[0] * aij) - b[1] / bMix) * log((z[i] + (1.0 + sqrt(2)) * bM) / (z[i] + (1.0 - sqrt(2.)) * bM))));
	return fugacidade;
}

void CPengRobinson::CalcularPropriedadesTermodinamicas(double T, double P, vector<long double> z, vector<double> fugacidade, vector<CSubstancia> vsubs){
	CEquacaoEstado::CalcularPropriedadesTermodinamicas(T,P, z, fugacidade, vsubs);
}

void CPengRobinson::CalcularPropriedadesTermodinamicas(double T, double P, vector<long double> z, vector<double> fugacidade, vector<CSubstancia> vsubs, vector<double> x){
	CEquacaoEstado::CalcularPropriedadesTermodinamicas(T, P, z, fugacidade, vsubs, x);
}

void CPengRobinson::SalvarPropriedadesTermodinamicasDisco(double T, double P, vector<long double> z, vector<double> fugacidade, vector<CSubstancia> vsubs, string nome){
	CEquacaoEstado::SalvarPropriedadesTermodinamicasDisco(T,P, z, fugacidade, vsubs, nome);
}

void CPengRobinson::SalvarPropriedadesTermodinamicasDisco(double T, double P, vector<long double> z, vector<double> fugacidade, vector<CSubstancia> vsubs, vector<double> x, string nome){
	CEquacaoEstado::SalvarPropriedadesTermodinamicasDisco(T, P, z, fugacidade, vsubs, x, nome);
}
