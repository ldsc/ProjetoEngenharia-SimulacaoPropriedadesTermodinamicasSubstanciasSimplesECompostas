#ifndef CEquacaoEstado_h
#define CEquacaoEstado_h
#include "CSubstancia.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>

class CEquacaoEstado{
	
protected:
//Atributos
double R{8.314e-5}; ///Constante dos gases
std::vector<CSubstancia> vsubstancia; ///Vetor de substancia	
std::vector<double> tR; ///Temperatura Critica
std::vector<double> a; ///a
std::vector<double> b; ///b
std::vector<double> kappa; ///kappa
std::vector<double> alpha; ///alpha
double aT{0}; ///aT
double bT{0}; ///bT
double aMaiusculo{0}; ///aMaiusculo
double bMaiusculo{0}; ///bMaiusculo
double aij{0}; ///aij
double aMix{0}; ///aMix
double bMix{0}; ///bMix
std::vector<long double> z; ///Fator de compressibilidade
std::vector<double> fugacidade; ///Fugacidade

public:

//Construtores e Destrutor
CEquacaoEstado()=default;
CEquacaoEstado(CEquacaoEstado& obj);
CEquacaoEstado(double R, std::vector<CSubstancia> _vsubstancia, std::vector<double> _tR, std::vector<double> _a, std::vector<double> _b, std::vector<double> _kappa, std::vector<double> _alpha, double _aT, double _bT, double _aMaiusculo, double _bMaiusculo, double _aij, double _interecao, double _aMix, double _bMix, std::vector<long double> _z, std::vector<double> _fugacidade);
~CEquacaoEstado()=default;

//Métodos Get e Set
void AMaiusculo(double _aMaiusculo){
	aMaiusculo=_aMaiusculo;}
	
double AMaiusculo(){
	return aMaiusculo;}

void BMaiusculo(double _bMaiusculo){
	bMaiusculo=_bMaiusculo;}
	
double BMaiusculo(){
	return bMaiusculo;}
	
void Z(std::vector<long double> _z){
	z = _z;}
	
std::vector<long double> Z(){
	return z;}

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
	
//Métodos
void ObterDadosSubstancia(int quantSubs);
virtual double CalcularParametros(double T, double P)=0;
virtual double CalcularParametros(double T, double P, std::vector<double> x, double interacao)=0;
virtual std::vector<double> CalcularFugacidade(std::vector<long double> z, double aM, double bM)=0;
virtual std::vector<double> CalcularFugacidade(std::vector<long double> z, double aM, double bM, double bMix, double aMix, std::vector<double> x)=0;
void CalcularPropriedadesTermodinamicas(double T, double P, std::vector<long double> z, std::vector<double> fugacidade, std::vector<CSubstancia> vsubs);
void CalcularPropriedadesTermodinamicas(double T, double P, std::vector<long double> z, std::vector<double> fugacidade, std::vector<CSubstancia> vsubs, std::vector<double> x);
void SalvarPropriedadesTermodinamicasDisco(double T, double P, std::vector<long double> z, std::vector<double> fugacidade, std::vector<CSubstancia> vsubs, std::string nome);
void SalvarPropriedadesTermodinamicasDisco(double T, double P, std::vector<long double> z, std::vector<double> fugacidade, std::vector<CSubstancia> vsubs, std::vector<double> x, std::string nome);
};
#endif


