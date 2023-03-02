#ifndef CSubstancia_h
#define CSubstancia_h
#include <iostream>
#include <cmath>
#include <vector>
#include <string>

class CSubstancia{

private:

//Atributos
std::string nomeSubs; ///Nome da substancia
double tC{0}; ///Temperatura critica
double pC{0}; ///Pressao critica
double omega{0}; ///Fator acentrico
	
public:

//Construtores
CSubstancia()=default;
CSubstancia(const CSubstancia& obj);
CSubstancia(std::string _nomeSubs, double _tC, double _pC, double _omega);
~CSubstancia()=default;

//Metodos Get e Set
void NomeSubs(std::string _nomeSubs){
	nomeSubs=_nomeSubs;}
	
std::string NomeSubs(){
	return nomeSubs;}

void TC(double _tC){
	tC=_tC;}
	
double TC(){
	return tC;}
	
void PC(double _pC){
	pC=_pC;}
	
double PC(){
	return pC;}

void Omega(double _omega){
	omega=_omega;}
	
double Omega(){
	return omega;}

//Metodos
void LerDadosDisco(std::string nomeSubs);

friend class CPengRobinson;
friend class CSoaveRedlichKwong;

};
#endif
