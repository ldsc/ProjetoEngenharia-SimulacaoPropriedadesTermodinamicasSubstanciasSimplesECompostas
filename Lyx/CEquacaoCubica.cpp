#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "CEquacaoCubica.h"
#include "CEquacaoEstado.h"

using namespace std;

//Construtores
CEquacaoCubica::CEquacaoCubica(CEquacaoCubica& obj){
	coefA=obj.coefA;
	coefB=obj.coefB;
	coefC=obj.coefC;
	zz=obj.zz;
}

CEquacaoCubica::CEquacaoCubica(long double _coefA, long double _coefB, long double _coefC, std::vector<long double> _zz){
	coefA=_coefA;
	coefB=_coefB;
	coefC=_coefC;
	zz=_zz;
}

//Organizar aM e bM em uma equacao cubica no formato PR ou SRK
void CEquacaoCubica::LerCoeficientes(int equacaoSelecionada, double aM, double bM){
	if (equacaoSelecionada==1){         //Peng-Robinson: z^3 - (1 - B) * z^2 + (A - 2*B - 3*B^2) * z - (A * B - B^2 - B^3)
		coefA=bM - 1.;
		coefB=aM - 2.*bM - 3.*pow(bM,2.);
		coefC=-(aM*bM - pow(bM,2.) - pow(bM,3.));
	}
else{                                  //Soave-Redlich-Kwong: z^3 - z^2 + (A - B - B^2) * z - (A*B)
		coefA=-1;
		coefB=aM - bM - pow(bM,2.);
		coefC=-(aM*bM);
	}
}
//Resolve equacao cubica montada pelo metodo anterior
std::vector<long double> CEquacaoCubica::ResolverEquacao(){
	long double coefD, coefE, delta;
	coefD=pow(coefA/3.,3.) - (coefA*coefB/6.) + (coefC/2.);
	coefE=(coefB/3) - pow(coefA/3,2);
	delta=pow(coefD,2.) + pow(coefE,3.);
	if (delta==0){
		zz.push_back(2.*pow(-coefD,(1./3.)) - (coefA/3.));
		zz.push_back(-pow(-coefD,(1./3.)) - (coefA/3.));
		zz.push_back(zz[1]);
	}
	else
		if (delta>0){
			long double coefF,coefG;
			long double cte=(-coefD)+sqrt(delta);
			if (cte<0)
				coefF=-pow(abs(cte),1./3.);
			else
				coefF=pow(cte,1./3.);
			cte=(-coefD)-sqrt(delta);
			if (cte<0)
				coefG=-pow(abs(cte),1./3.);
			else
				coefG=pow(cte,1./3.);
			for(int i=0;i<3;i++)
			zz.push_back(coefF + coefG - (coefA/3.));		
			}
		else{
			long double theta;
			theta=acos(-coefD/sqrt(pow(-coefE,3.)));
			zz.push_back(2.*sqrt(-coefE)*cos(theta/3.) - coefA/3.);
			zz.push_back(2.*sqrt(-coefE)*cos(theta/3. + 2.*M_PI/3.) - coefA/3.);
			zz.push_back(2.*sqrt(-coefE)*cos(theta/3. + 4.*M_PI/3.) - coefA/3.);
		}
return zz;}
