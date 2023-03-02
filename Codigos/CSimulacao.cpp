#include "CSimulacao.h"

using namespace std;

CSimulacao::CSimulacao(CSimulacao& obj){
	quantSubs=obj.quantSubs;
	equacao=obj.equacao;
	T=obj.T;
	P=obj.P;
	aM=obj.aM;
	bM=obj.bM;
	aMix=obj.aMix;
	bMix=obj.bMix;
	interacao=obj.interacao;
	fracaoMolar=obj.fracaoMolar;
	x=obj.x;
	vsubs=obj.vsubs;
	z=obj.z;
	nome=obj.nome;
	fugacidade=obj.fugacidade;
	vetorx=obj.vetorx;
	vetory=obj.vetory;
}

CSimulacao::CSimulacao(int _quantSubs, int _equacao, double _T, double _P, double _aM, double _bM, double _aMix, double _bMix, double _interacao, double _fracaoMolar, vector<double> _x, vector<CSubstancia> _vsubs, vector<long double> _z, string _nome, string _legenda, vector<double> _fugacidade, vector<double> _vetorx, vector<double> _vetory){
	quantSubs=_quantSubs;
	equacao=_equacao;
	T=_T;
	P=_P;
	aM=_aM;
	bM=_bM;
	aMix=_aMix;
	bMix=_bMix;
	interacao=_interacao;
	fracaoMolar=_fracaoMolar;
	x=_x;
	vsubs=_vsubs;
	z=_z;
	nome=_nome;
	fugacidade=_fugacidade;
	vetorx=_vetorx;
	vetory=_vetory;
}

void CSimulacao::OrganizarZ(vector<long double> z){
	sort(z.begin(),z.end());
	if (z[0]<0){
		z[0]=z[1];
		z[1]=z[2];
		z.pop_back();
	}
	else{
		z[1]=z[2];
		z.pop_back();
	}
	if (z[0]<0){
		z[0]=z[1];
	}
}

void CSimulacao::CriarNomeGrafico(double T, double P, int equacao, vector<CSubstancia> vsubs){
	ostringstream convertert;
	convertert << T;
	string t=convertert.str();
	ostringstream converterp;
	converterp << P;
	string p=converterp.str();
	if (equacao==1)
		nome=vsubs[0].NomeSubs()+"_"+t+"K_"+p+"bar_PR";
	else
		nome=vsubs[0].NomeSubs()+"_"+t+"K_"+p+"bar_SRK";
}

void CSimulacao::CriarNomeGrafico(double T, double P, int equacao, vector<CSubstancia> vsubs, vector<double> x){
	ostringstream convertert;
	convertert << T;
	string t=convertert.str();
	ostringstream converterp;
	converterp << P;
	string p=converterp.str();
	ostringstream converterx0;
	converterx0 << x[0];
	string x0=converterx0.str();
	ostringstream converterx1;
	converterx1 << x[1];
	string x1=converterx1.str();
	if (equacao==1)
		nome=vsubs[0].NomeSubs()+"(fracao molar = "+x0+" )_"+vsubs[1].NomeSubs()+"(fracao molar = "+x1+" )_"+t+"K_"+p+"bar_PR";
	else
		nome=vsubs[0].NomeSubs()+"(fracao molar = "+x0+" )_"+vsubs[1].NomeSubs()+"(fracao molar = "+x1+" )_"+t+"K_"+p+"bar_SRK";
	}

void CSimulacao::Simular(){
cout << "A simulacao sera feita para 1 ou 2 substancias?"<<endl;
cin >> quantSubs; cin.get();
while (quantSubs!=1 && quantSubs!=2){
	cerr << "\n-->ERRO: Quantidade invalida(" << quantSubs << ") .\n";
	cout << "\nA simulacao sera feita para 1 ou 2 substancias?"<<endl;
	cin >> quantSubs; cin.get();
} 
cout << "\nQual equacao deseja utilizar? (1 para Peng-Robinson ou 2 para Soave-Redlich-Kwong)" << endl;
cin >>equacao; cin.get();
while (equacao!=1 && equacao!=2){
	cerr << "\n-->ERRO: Equacao invalida(" << equacao << ") .\n";
	cout << "\nQual equacao deseja utilizar? (1 para Peng-Robinson ou 2 para Soave-Redlich-Kwong)" << endl;
	cin >>equacao; cin.get();
}
cout << "\nQual a temperatura da simulacao?" << endl;
cin >> T; cin.get();
while (T<0){
	cerr << "\n-->ERRO: Temperatura absoluta nao pode ter valor " << T <<" .\n";
	cout << "\nQual a temperatura da simulacao?" << endl;
	cin >> T; cin.get();
}
cout << "\nQual a pressao da simulacao?" << endl;
cin >> P; cin.get();
while (P<0){
	cerr << "\n-->ERRO: Pressao nao pode ter valor " << P << ".\n";
	cout << "\nQual a pressao da simulacao?" << endl;
	cin >> P; cin.get();
}

//Criando objetos
CEquacaoCubica cub;
CPengRobinson pr;
CSoaveRedlichKwong srk;

//Calculando parametros PR ou SRK
if (equacao==1){
	pr.ObterDadosSubstancia(quantSubs);
	vsubs=pr.VSubstancia();
	if(quantSubs==2){
		cout << "\nQual a interacao entre as duas substancias?"<<endl;
		cin >> interacao; cin.get();
		cout << "\nQual a fracao molar da primeira substancia?"<< endl;
		cin >> fracaoMolar; cin.get();
		while (fracaoMolar<=0 || fracaoMolar>=1){
			cerr << "\n-->ERRO: Fracao molar deve ser um numero entre 0 e 1.\n";
			cout << "\nQual a fracao molar da primeira substancia?"<< endl;
			cin >> fracaoMolar; cin.get();
		}
		x.push_back(fracaoMolar);
		x.push_back(1-x[0]);
		pr.CalcularParametros(T,P, x, interacao);
		aMix=pr.AMix();
		bMix=pr.BMix();
	}
	else{
		pr.CalcularParametros(T, P);
	}
	aM=pr.AMaiusculo();
	bM=pr.BMaiusculo();
}
else{
	srk.ObterDadosSubstancia(quantSubs);
	vsubs=srk.VSubstancia();
	if(quantSubs==2){
		double interacao, fracaoMolar;
		cout << "\nQual a interacao entre as duas substancias?"<<endl;
		cin >> interacao; cin.get();
		cout << "\nQual a fracao molar da primeira substancia?"<< endl;
		cin >> fracaoMolar; cin.get();
		while (fracaoMolar<=0 || fracaoMolar>=1){
			cerr << "\n-->ERRO: Fracao molar deve ser um numero entre 0 e 1.\n";
			cout << "\nQual a fracao molar da primeira substancia?"<< endl;
			cin >> fracaoMolar; cin.get();
		}
		x.push_back(fracaoMolar);
		x.push_back(1-x[0]);
		srk.CalcularParametros(T,P, x, interacao);
		aMix=srk.AMix();
		bMix=srk.BMix();
	}
	else{
		srk.CalcularParametros(T, P);
	}
	aM=srk.AMaiusculo();
	bM=srk.BMaiusculo();
}
cub.LerCoeficientes(equacao, aM, bM);
cub.ResolverEquacao();
z=cub.Zz();

///Organizando vetor Z
CSimulacao::OrganizarZ(z);

//Criando nome para arquivo de disco e para grafico
if (quantSubs==1)
	CSimulacao::CriarNomeGrafico(T, P, equacao, vsubs);
else
	CSimulacao::CriarNomeGrafico(T, P, equacao, vsubs, x);

//Propriedades Termodinamicas PR ou SRK: Calcular, mostrar na tela e salvar em disco
cout << "\n\nPropriedades Termodinamicas na temperatura "<<T<< " K e "<<P<< " bar:\n\n";
if (quantSubs==1)
	if (equacao==1){
		pr.CalcularFugacidade(z, aM, bM);
		fugacidade=pr.Fugacidade();
		pr.CalcularPropriedadesTermodinamicas(T, P, z, fugacidade, vsubs);
		pr.SalvarPropriedadesTermodinamicasDisco(T, P, z, fugacidade, vsubs, nome);

	}
	else{
		srk.CalcularFugacidade(z, aM, bM);
		fugacidade=srk.Fugacidade();
		srk.CalcularPropriedadesTermodinamicas(T, P, z, fugacidade, vsubs);	
		srk.SalvarPropriedadesTermodinamicasDisco(T, P, z, fugacidade, vsubs, nome);
	}
else
	if(equacao==1){
		pr.CalcularFugacidade(z, aM, bM, bMix, aMix, x);
		fugacidade=pr.Fugacidade();
		pr.CalcularPropriedadesTermodinamicas(T, P, z, fugacidade, vsubs, x);
		pr.SalvarPropriedadesTermodinamicasDisco(T, P, z, fugacidade, vsubs, x, nome);
	}
	else{
		srk.CalcularFugacidade(z, aM, bM, bMix, aMix, x);
		fugacidade=srk.Fugacidade();
		srk.CalcularPropriedadesTermodinamicas(T, P, z, fugacidade, vsubs, x);
		srk.SalvarPropriedadesTermodinamicasDisco(T, P, z, fugacidade, vsubs, x, nome);	
	}
	
//Plotar Grafico PR ou SRK
if (equacao==1)
	for (double i=0;i<=1.5;i=i+.01){
		vetorx.push_back(i);
		vetory.push_back(i*i*i+(bM - 1.)*i*i+(aM - 2.*bM - 3.*pow(bM,2.))*i-(aM*bM - pow(bM,2.) - pow(bM,3.)));
	}
else
	for (double i=0;i<=1.5;i=i+.01){
		vetorx.push_back(i);
		vetory.push_back(i*i*i-i*i+(aM-bM-pow(bM,2))*i-(aM*bM));
	}

//Criando legenda para o grafico
ostringstream converterz0;
converterz0 << z[0];
string z0=converterz0.str();
if(z[0]==z[1]){
	legenda="Z = "+z0;
}
else{
	ostringstream converterz1;
	converterz1 << z[1];
	string z1=converterz1.str();
	legenda="Z(liquido) = "+z0+" // Z (vapor) = "+z1;
}

//Criando grafico
CGnuplot grafico;
grafico.Style("lines");
grafico.set_xlabel("Z");
if (equacao==1)
	grafico.set_ylabel("PR(Z)");
else
	grafico.set_ylabel("SRK(Z)");	
grafico.Title("Gráfico de Z");
grafico.PlotVector(vetorx, vetory, legenda); // aparece na tela
string salvar="set out \""+nome+".png\"\n" ;
grafico << salvar; // setar nome arquivo
grafico << "set term png\n" ; // setar tipo do arquivo
grafico.Replot();               // replotar; salva no disco.
cin.get();cin.get();
}
