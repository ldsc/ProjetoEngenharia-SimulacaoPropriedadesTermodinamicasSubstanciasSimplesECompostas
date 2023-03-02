#ifndef CSoaveRedlichKwong_h
#define CSoaveRedlichKwong_h
#include "CEquacaoEstado.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>

class CSoaveRedlichKwong: public CEquacaoEstado{

public:

//Atributos
CSoaveRedlichKwong(): CEquacaoEstado() {};
CSoaveRedlichKwong(CSoaveRedlichKwong& obj);
CSoaveRedlichKwong(std::vector<CSubstancia> _vsubstancia, std::vector<double> _tR, std::vector<double> _a, std::vector<double> _b, std::vector<double> _kappa, std::vector<double> _alpha, double _aT, double _aMaiusculo, double _bMaiusculo, double _aij, double _interecao, double _aMix, double _bMix, std::vector<double> _fugacidade);
~CSoaveRedlichKwong()=default;

//Metodos Get e Set
void AMaiusculo(double _aMaiusculo){
	aMaiusculo=_aMaiusculo;}
	
double AMaiusculo(){
	return aMaiusculo;}

void BMaiusculo(double _bMaiusculo){
	bMaiusculo=_bMaiusculo;}
	
double BMaiusculo(){
	return bMaiusculo;}
	
void AMix(double _aMix){
	aMix=_aMix;}
	
double AMix(){
	return aMix;}

void BMix(double _bMix){
	bMix=_bMix;}
	
double BMix(){
	return bMix;}
	
void Fugacidade(std::vector<double> _fugacidade){
	fugacidade = _fugacidade;}
	
std::vector<double> Fugacidade(){
	return fugacidade;}
	
void Vsubstancia(std::vector<CSubstancia> _vsubstancia){
	vsubstancia = _vsubstancia;}
	
std::vector<CSubstancia> VSubstancia(){
	return vsubstancia;}

//Metodos
void ObterDadosSubstancia(int quantSubs);
double CalcularParametros(double T, double P);
double CalcularParametros(double T, double P, std::vector<double> x, double interacao);
std::vector<double> CalcularFugacidade(std::vector<long double> z, double aM, double bM);
std::vector<double> CalcularFugacidade(std::vector<long double> z, double aM, double bM, double bMix, double aMix, std::vector<double> x);
void CalcularPropriedadesTermodinamicas(double T, double P, std::vector<long double> z, std::vector<double> fugacidade, std::vector<CSubstancia> vsubs);
void CalcularPropriedadesTermodinamicas(double T, double P, std::vector<long double> z, std::vector<double> fugacidade, std::vector<CSubstancia> vsubs, std::vector<double> x);
void SalvarPropriedadesTermodinamicasDisco(double T, double P, std::vector<long double> z, std::vector<double> fugacidade, std::vector<CSubstancia> vsubs, std::string nome);
void SalvarPropriedadesTermodinamicasDisco(double T, double P, std::vector<long double> z, std::vector<double> fugacidade, std::vector<CSubstancia> vsubs, std::vector<double> x, std::string nome);
};
#endif
