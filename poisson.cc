#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

double poisson(double mu, int k) {
  double exponent = exp(- mu);
  double factorial = tgamma(k+1);
  double x = exponent * pow(mu,k) / factorial;
  return x;
}

int main() {
  
  system("install-pkg gnuplot-nox");
  
  int N1, N, k; 
  double mu, P;
 
  vector<int> counter(11);
  ifstream fin ("datensumme.txt");
  N=234;

  for (int i=0;i<N;i++) {
    fin >> N1 ;
  
    counter[N1]+=1;
  }

  ofstream fout("hist.txt");

  for (int k = 0 ; k < counter . size () ; ++ k ) {
    //cout << k << ":" << counter [k] << std::endl;
    fout << k << " " << counter [k] << endl;
  }


  fin.close();
  fout.close();

  ifstream fin1 ("hist.txt");
  ofstream fout1 ("histpoi.txt");

  for (int i=0;i<11;i++) {
    fin1 >> k >> counter[k];
  
    P = poisson (3.11538,k);
    fout1 << k << " " << counter[k] << " " << k*P << endl;
    cout  << k << " " << counter[k] << " " << k*P << endl;
  }

  fin1.close();
  fout1.close();


}