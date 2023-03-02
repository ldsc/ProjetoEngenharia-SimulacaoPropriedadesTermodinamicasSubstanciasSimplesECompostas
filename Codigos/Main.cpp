#include "CSubstancia.h"
#include "CEquacaoCubica.h"
#include "CEquacaoEstado.h"
#include "CPengRobinson.h"
#include "CSoaveRedlichKwong.h"
#include "CGnuplot.h"
#include "CSimulacao.h"
#include <cmath>
#include <locale.h>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

int main(){	
CSimulacao sim;
sim.Simular();
system("pause");
return 0;
}
