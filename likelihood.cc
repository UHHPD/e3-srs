#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>

using namespace std;
int N = 234;

double poisson(double mu, int k) {
  double exponent = exp(- mu);
  double factorial = tgamma(k+1);
  double x = exponent * pow(mu,k) / factorial;
  return x;
}

double prob(vector<int> daten, double mu) {
  double product = 1;
  for (int i=0;i<N;i++) {
    double exponent = exp(- mu);
    double factorial = double (tgamma(daten[i]+1));
      if (daten[i]==0)
        factorial = 1;

    double x = (pow(mu,daten[i])*exponent) / factorial;
    product *= x;
  }
return product;
}

int main() {
  

int k, ndof; 
  double L, L_mean, deltaL, min, min_mu, nl, Nll, interval[50], Pp, Pp1, Lambda, LR, z;

  ifstream fin ("datensumme.txt");

  vector<int> daten;

  for (int i=0;i<N;i++) {
    fin >> k ;
    daten.push_back(k);
  }

  
  L_mean = prob(daten,3.11538);
  cout  << L_mean << endl;

  ofstream fout("likelihood.txt");
  ofstream fout1("nll.txt");
  ofstream fout2("deltanll.txt");
  ofstream fout3("random check.txt");
  
  for (double i=0; i<=6.0; i+=(0.1)) {
    L = prob(daten,i);
    nl = -2*log(L);
    Nll = ((-2*log(L)) - (-2*log(L_mean)));

    fout  << i << "   " <<  L   << endl;
    fout1 << i << "   " <<  nl  << endl;
    fout2 << i << "   " <<  Nll << endl;

  }
  
  for (double i=0; i<=6.0; i+=(0.1)) {
    L = prob(daten,i);
    nl = -2*log(L);
    Nll = ((-2*log(L)) - (-2*log(L_mean)));


    if (i==0) {
      min = Nll;
    }
    if (Nll < min) {
      min = Nll;
      min_mu = i;
    }

  }
  int j=0;
  for (double i=0; i<=6.0; i+=(0.01)) {
    L = prob(daten,i);
    nl = -2*log(L);
    Nll = ((-2*log(L)) - (-2*log(L_mean)));

    if ((-2*log((L)/((prob(daten,min_mu)))))<1) {
      fout3 << i << "  " << nl << endl;
      interval[j] = i;
      j++;
    }
  }

  fin.close();
  fout.close();

  cout << min_mu << "  " << min << endl;
  cout << "Interval for uncertainty on µ = " << interval[0] << " to " << interval[j-1] << endl;
  cout << "Uncertainty on the estimated µ = " << interval[j-1] - interval[0] << endl;
  cout << "Uncertainty on sample mean = " << 2.88462/(sqrt(234)) << endl;
  
  double product =1;
  double product1 =1;
  for (int i=0;i<N;i++) {
    Pp = poisson(3.11538,daten[i]);
    Pp1 = poisson(daten[i],daten[i]);
    product *= Pp;
    product1 *= Pp1;
  }
  
  Lambda = product/product1;
  LR = -2*log(Lambda);
  cout << LR << endl ;
  
  ndof = 233;
  z = (LR-ndof)/(sqrt(2*ndof));
  cout << "Relative deviation of our likelihood ratio from the mean = "<< z <<endl;

  fout1.close();
  fout2.close();
  fout3.close();

  //system("install-pkg gnuplot-nox");
  system("gnuplot-nox");
  
}