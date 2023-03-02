#ifndef CEquacaoCubica_h
#define CEquacaoCubica_h
#include "CEquacaoEstado.h"
#include "CPengRobinson.h"
#include "CSoaveRedlichKwong.h"
#include <iostream>
#include <cmath>
#include <vector>

class CEquacaoCubica {

private:

long double coefA{0}; ///Coeficiente A
long double coefB{0}; ///Coeficiente B
long double coefC{0}; ///Coeficiente C
std::vector<long double> zz; /// Fator de compressibilidade

public:

//Construtores e Destrutor
CEquacaoCubica() = default;
CEquacaoCubica(CEquacaoCubica& obj);
CEquacaoCubica(long double _coefA, long double _coefB, long double _coefC, std::vector<long double> _zz);
~CEquacaoCubica() = default;

//Métodos Get e Set
void CoefA(long double _coefA){
	coefA=_coefA;}
	
long double CoefA(){
	return coefA;}

void CoefB(long double _coefB){
	coefB = _coefB;}
	
long double CoefB(){
	return coefB;}

void CoefC(long double _coefC){
	coefC = _coefC;}
	
long double CoefC(){
	return coefC;}

void Zz(std::vector<long double> _zz){
	zz = _zz;}
	
std::vector<long double> Zz(){
	return zz;}
	
//Métodos
void LerCoeficientes(int equacaoSelecionada, double aM, double bM);
std::vector<long double> ResolverEquacao();

};

#endif
