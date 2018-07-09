#include <iostream>
#include <cmath>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip> 

#include <iostream>     // std::cout
#include <algorithm>    // std::sort
#include <vector>       // std::vector

#include "Class_Neuron.h"
#include "Class_NeuralNetwork.h"
#include "statistic.h"

using namespace std;
double** getMatrix(int N);


int main(){
	int N;
	double mu, sigma, theta, C;
	string esp;
	
	
	cout << "insert N (number of neurons)" << endl;
	cin >> N;
	
	cout << "insert mu (drift)" << endl;
	cin >> mu;
	
	cout << "insert sigma (noise intensity)" << endl;
	cin >> sigma;
	
	cout << "insert theta (membrane time)" << endl;
	cin >> theta;
	
	cout << "insert C (threshold)" << endl;
	cin >> C;
	
	NeuralNetwork NN1(N, mu, sigma, theta, C ); // N , mu, sigma ,theta, C (threshold)
	
	// Uncomment next line if you want a neuron to have a different mu
	//NN1.getNeur(1)->setMu(2);
	

	//JUMP MODEL
	
	cout << "insert the jump matrix " << endl;
	NN1.createJumpMatrix(getMatrix(N));
	
	
	// COVARIANCE MODEL
	
	//cout << "insert the covariance matrix " << endl;
	//NN1.createCovMatrix(getMatrix(N));
	
	
	
	
	cout << "Name of the experiment" << endl;
	cin >> esp;
	//NN1.printParam();
	
	
	
	
	//--------------------  FPT
	
	NN1.FPT(10000);
	NN1.writeSpikeTimes_FPT();
	
	
	//--------------------- SPIKE TRAIN
	
	//NN1.spikeTrain(250000, false);
	//NN1.writeSpikeTimes_ST(esp);
	//Il copia e incolla e' la fonte di ogni nequizia
	//ISI_full_3D(NN1.getNeur(0)->getSpikeTimes() , NN1.getNeur(1)->getSpikeTimes(), NN1.getNeur(2)->getSpikeTimes() , esp);	
	
	
	//cout << NN1.getNeur(0) ->getLog().size() << endl;
	//cout << NN1.getNeur(1) ->getLog().size() << endl;
	


	NN1.printParam();
	
	
	//NN1.writeLog();
	
	
	
	
	
	
	
	
	
}// end main



double** getMatrix(int N){

	double **K = new double *[N];
		for(int i =0; i < N; i++){
			K[i] = new double[N];
			for(int j =0; j < N; ++j){ 
				cout << "Insert element " << i+1 <<"," << j+1 << endl;
				cin >> K[i][j]; 
				
					}
			}
		return K;
	
}
