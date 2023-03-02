#ifndef CSimulacao_h
#define CSimulacao_h
#include "CSubstancia.h"
#include "CEquacaoCubica.h"
#include "CEquacaoEstado.h"
#include "CPengRobinson.h"
#include "CSoaveRedlichKwong.h"
#include "CGnuplot.h"
#include <cmath>
#include <locale.h>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

class CSimulacao{
	
private:
	
int quantSubs{0}; ///Quantidade de substancias
int equacao{0}; ///Equacao selecionada
double T{0}; ///Temperatura selecionada
double P{0}; ///Pressao selecionada
double aM{0}; ///aM
double bM{0}; ///bM
double aMix{0}; ///aMix
double bMix{0}; ///bMix
double interacao{0}; ///Interacao
double fracaoMolar{0};
std::vector<double>x; ///Fracao molar
std::vector<CSubstancia>vsubs; ///Vetor de substancia
std::vector<long double> z; ///Fator de compressibilidade
std::string nome; ///Nome da substancia
std::string legenda; ///Nome da legenda
std::vector<double> fugacidade; ///Fugacidade
std::vector<double> vetorx; ///Eixo x
std::vector<double> vetory; ///Eixo y

public:
	
CSimulacao()=default;
CSimulacao(CSimulacao& obj);
CSimulacao(int _quantSubs, int _equacao, double _T, double _P, double _aM, double _bM, double _aMix, double _bMix, double _interacao, double _fracaoMolar, std::vector<double> _x, std::vector<CSubstancia> _vsubs, std::vector<long double> _z, std::string _nome, std::string _legenda, std::vector<double> _fugacidade, std::vector<double> _vetorx, std::vector<double> _vetory);
~CSimulacao()=default;

void Simular();
void OrganizarZ(std::vector<long double> z);
void CriarNomeGrafico(double T, double P, int equacao, std::vector<CSubstancia> vsubs);
void CriarNomeGrafico(double T, double P, int equacao, std::vector<CSubstancia> vsubs, std::vector<double> x);

};
#endif
