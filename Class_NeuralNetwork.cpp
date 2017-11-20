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

#include "Class_NeuralNetwork.h" 
#include "Class_Neuron.h"

using namespace std;

/////////////////////////////////////////////////////////////
/////////////////				/////////////
/////////////////	NN FUNCTIONS 		/////////////	
////////////////				/////////////
/////////////////////////////////////////////////////////////



NeuralNetwork::NeuralNetwork(int numNeur){
	N = numNeur;
	neur = new Neuron *[N];
	corr = false;
		
	h = new  double *[N];  // create the jump matrix, with all zeros
	for(int i =0; i < N; i++){
		h[i] = new double[N];
		for(int j =0; j < N; ++j) h[i][j] =0;}
		
	A = new  double *[N]; //create the correlation matrix, with all zeros
	for(int i =0; i < N; i++){
		A[i] = new double[N];
		for(int j =0; j < N; ++j) 
			 A[i][j] =0;
			}
			
	L = new  double *[N]; // create the Cholesky decomposition matrix, with all zeros
	for(int i =0; i < N; i++){
		L[i] = new double[N];
		for(int j =0; j < N; ++j) L[i][j] =0;}
			
	for (int i=0; i<N; i++) // creates all neuron, with the same paramters
		{
		neur[i] = new Neuron( this, i ,1.2, sqrt(0.3), 10, 10, false); 
		}
	
	} //end costructor
	
NeuralNetwork::NeuralNetwork(int numNeur, double mu, double sigma, double theta, double C){
	N = numNeur;
	neur = new Neuron *[N];
	corr = false;
		
	h = new  double *[N];  // create the jump matrix, with all zeros
	for(int i =0; i < N; i++){
		h[i] = new double[N];
		for(int j =0; j < N; ++j) h[i][j] =0;}
		
	A = new  double *[N]; //create the correlation matrix, with all zeros
	for(int i =0; i < N; i++){
		A[i] = new double[N];
		for(int j =0; j < N; ++j) 
				A[i][j] =0;
			}
			
	L = new  double *[N]; // create the Cholesky decomposition matrix
	for(int i =0; i < N; i++){
		L[i] = new double[N];
		for(int j =0; j < N; ++j) L[i][j] =0;}
			
	for (int i=0; i<N; i++) // create all neuron, with the same paramters
		{
		neur[i] = new Neuron( this, i , mu, sigma, theta, C, false); 
		}
	
	} //end costructor

void NeuralNetwork::createJumpMatrix(double **J)
	{
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			setH(i,j,J[i][j]);
			}
		}
	}
	
void NeuralNetwork::createCovMatrix(double **J)
	{
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			setA(i,j,J[i][j]);
			}
		}
	corr=true;
	cDecomposition();
	}	
	
	//-------------------------------------------
	// setters
	// ------------------------------------------
	
void NeuralNetwork::setH(int i, int j, double val)
	{
	h[i][j]= val;
	}
	
void NeuralNetwork::setA(int i, int j, double val)
	{
	A[i][j]= val;
	}

void NeuralNetwork::setL(int i, int j, double val)
	{
	L[i][j]= val;
	}
	
	
	
void NeuralNetwork::cDecomposition()
	{
	for (int i = 0; i < N; i++)
		{for(int j=0; j<= i; j++)
			{if (i==j)
				{double S=0;
				
				for(int k=0; k<j; k++) S += L[j][k]*L[j][k];
					
				L[j][j] = sqrt (A[j][j] - S);
				//cout << i << " " << j << " " << S << " "<< L[j][j] <<endl;
				}
			else{
				double S=0;
			
				for(int k=0; k<j; k++) S += L[i][k]*L[j][k];
			
				L[i][j] = (A[i][j] - S) / L[j][j];
				//cout << i << " " << j << " " << S <<  " " << L[i][j]<< endl;	
			}
			
			
			}//end for j
	}//end for i
	
	
	}
	
	
	//------------------------------------------------
	// Getters
	//-----------------------------------------------	
	
	
Neuron* NeuralNetwork::getNeur(int i){
	return neur[i];
	}
	
double NeuralNetwork::getH(int i, int j){
	return h[i][j];
	}
	
double NeuralNetwork::getA(int i, int j){
	return A[i][j];
	}
	
double NeuralNetwork::getL(int i, int j){
	return L[i][j];
	}
	
bool NeuralNetwork::getCorr(){
	return corr;
	}
	

	
	//------------------------------------------------
	// Time evolution
	//-----------------------------------------------	
	
	
	
	
void NeuralNetwork::activity(int i){
	//cout << "act " << endl;
	for (int j=0; j<N; j++)
		{
		if( ! neur[j]->getSp() ){
			//cout << "activity "<< i << endl;
			if(h[i][j] != 0) neur[j]-> jump(h[i][j]);
			if(neur[j]->getMp() >= neur[j]->getC() ) neur[j]->spike();
			}//end if
		}
}



void NeuralNetwork::FPT(int NData){

	srand(time(NULL));
	mt19937 gen{static_cast<long unsigned int>(time(0))};
	normal_distribution<double> d(0,1);

	double* noise;
	noise = new double [N];	
	double* corrNoise;
	corrNoise = new double [N];	
	
	//cout<<"istanzio S"<<endl;
	
	for (int n=0; n<NData; n++)
	{	
		//cout << N1->time<< " " << N1->mp << " " << N2->mp << endl;
		int count = 0;
		//cout << n << endl;
			while(true)
				{
				
				
				
				//each neuron does a timestep
				if(corr) { //if corr is true, generate correlated noise using L
				
					for (int i=0; i<N; i++){noise[i]=d(gen);}
					for (int i=0; i<N; i++){
						corrNoise[i]=0;
						for (int j=0; j<N; j++){
							corrNoise[i] += L[i][j]*noise[j];	
							}
						}
					for (int i=0; i<N; i++) neur[i]->step(corrNoise[i] );
					}
							//else, simply do a step with random noise	
				else {for (int i=0; i<N; i++) neur[i]->step( d(gen));} 
				
				//then check if some neuron went over the threshold and let them spike
				for (int i=0; i<N; i++){
					if (neur[i]->getMp() >= neur[i]->getC() and neur[i]->getWait() == false)
						{
						neur[i]->spike();
						}
					}//end for
					
				//check if someone did a spike
				for (int i=0; i<N; i++){
					if (neur[i]->getSp() == true and neur[i]->getWait() == false ) 
						{//activity(i); //communicate to the network the activity of i
						 //in FPT neurons just wait after the spike
						//cout << "neur " << i << "sp =" << neur[i]->getSp() <<" and wait =" << neur[i]->getWait()<< endl;
						neur[i]->setWait(true);
						count++;
							}	
						}
			
				if (count==N)
					{
				
					if (n%100 == 0)cout<< n << endl;
					for (int i=0; i<N; i++) {
							neur[i]->reset();}				
					break;
					}
				
			
			
				} //end while
			
		//cout << "AAAAAAAAAAAA"<<endl;
			
		} //end for
		
		//for (int i=0; i<N; i++)
		//{
		//	for (auto k: S[i]) {std::cout << k << ' ';}
		//  	cout << endl;
		//  	}
		  	
		
		
			

} // end FPT

void NeuralNetwork::spikeTrain(double Tmax, bool save= false){
	
	srand(time(NULL));
	default_random_engine gen{static_cast<long unsigned int>(time(0))};
	normal_distribution<double> d(0,1);
	
	
	if (save){
		for(int i=0; i<N; i++)
			{neur[i]->setSave_Log(true);}
	}
	
	
	double* noise;
	noise = new double [N];	
	double* corrNoise;
	corrNoise = new double [N];	
	
	
	int counter = 0;
	while(neur[0]->getTime() < Tmax){
		if (counter++ % 1000 ==0) cout << counter -1 << endl;
		
		//each neuron does a timestep
		if(corr) { //if corr is true, generate a correlated noise using L
					for (int i=0; i<N; i++){noise[i]=d(gen);}
					for (int i=0; i<N; i++){
						corrNoise[i]=0;
						for (int j=0; j<N; j++){
							corrNoise[i] += L[i][j]*noise[j];	
							}
						}
					for (int i=0; i<N; i++) neur[i]->step(corrNoise[i]);
					}
				//else just use random noise
		else {for (int i=0; i<N; i++) neur[i]->step(d(gen));} 
		
		
		//check if someone went over the threshold
		for (int i=0; i<N; i++){
			if (neur[i]->getMp() >= neur[i]->getC() and neur[i]->getSp() == false )
				{ 
				neur[i]->spike();
				}//endif
			}//end for
		
		//reset every Sp
		for (int i=0; i<N; i++)
			{ 
			neur[i]->setSp(false);			
			}
		//check if someone did a spike
		//for (int i=0; i<N; i++){
		//	if (neur[i]->getSp() == true)
		//		{activity(i); }
		//	}//end for
		
		
		}//end while
		
	
		
	
	} //end spikeTRain
	
	
//////// -----------------------------------------------------------	
//////// IO functions
//////// -----------------------------------------------------------

void NeuralNetwork::writeLog()
	{
	string filename;
	ofstream myfile;
	
	cout << "Please enter a name for your file (.txt will be added): " << endl;
    	cin >> filename;
	
	  myfile.open(filename + ".txt");
	  //cout << neur[0]->getLog().size() << endl;
	  double delta = neur[0]->getDt();
	  for (int t = 0; t < neur[0]->getLog().size(); t++){
	  		//cout << t << endl;
	  		myfile << t * delta << " ";
			for (int i=0; i<N; i++){
				myfile << neur[i]->getLog(t)<< " ";
				} // end for
			myfile << endl;	
			}	
	  myfile.close();
	
	}
	
	
void NeuralNetwork::writeSpikeTimes_FPT(string filename)
		{
		ofstream myfile;	
		
		myfile.open (filename + "_TOT.txt"); //write all the data in a single file
		for (int k = 0; k < neur[0]->getSpikeTimes().size(); k++){
			for (int i=0; i<N; i++){
			
				myfile << neur[i]->getSpikeTimes(k) << " "; //line represents time (k index) while column neurons(i index)
					}//end for
			myfile << endl;
			} // end for
		myfile.close();
		  
		ofstream outFile; // write a file for each single data
		for (int i=0; i < N; i++)
			{
			outFile.open(filename + "_N" +  to_string(i) + ".txt");
			for (int k = 0; k < neur[0]->getSpikeTimes().size(); k++) { outFile << neur[i]->getSpikeTimes(k) << endl;}
			outFile.close();
			}
		
		/// old part to write copulas (now uses r)
		/*vector<double> *U;
		U = new vector<double>[N]; 
		
		for (int i=0; i < N; i++) // write a file for each single eCDF
			{
			U[i] = dist(neur[i]->getSpikeTimes());
			string NOF = output_filename + "_COP_N" +  to_string(i) + ".txt";
			outFile.open(filename.c_str());
			for (int k = 0; k < NData; k++) { outFile << U[i][k]<< endl;}
			outFile.close();
			}
		
		myfile.open (output_filename + "_COP_TOT.txt"); //write all the eCDF data in a single file
		for (int k = 0; k < NData; k++){
			for (int i=0; i<N; i++){
			
				myfile << U[i][k] << " "; //line represents time (k index) while column neurons(i index)
					}//end for
			myfile << endl;
			} // end for
		myfile.close();*/
		
		//writes a resume
		ofstream Rfile;
		Rfile.open (filename+ "_resume.txt");
		Rfile << "This NeuralNetwork has " << N << " Neurons \n";
		Rfile << "Jump matrix (h): \n";
	
		Rfile << setprecision(3);
		Rfile << fixed;
		for (int i = 0; i<N; i++){
			for (int j = 0; j < N; j++){
				Rfile << h[i][j]<< " ";
				}
			Rfile << endl;
			}
	
		if(corr)
			{
			Rfile << "Correlation matrix (A): \n"; 		
			for (int i = 0; i<N; i++){
				for (int j = 0; j < N; j++){
					Rfile << A[i][j]<< " ";
					} 
				Rfile << endl;
				}
			Rfile << "L: \n"; 
			for (int i = 0; i<N; i++){
				for (int j = 0; j < N; j++){
					Rfile << L[i][j]<< " ";
					}
				Rfile << endl;
				}
			} // end if
			
		for (int i = 0; i<N; i++)
			{
			Rfile << 
		"Neuron: " << neur[i]->getID() <<
		" sigma: " << neur[i]->getSigma() <<
		" theta: " << neur[i]->getTheta() <<
		" mu: "	 << neur[i]->getMu() <<
		" C: " << neur[i]->getC() << endl;
			}
		Rfile.close();	
			
	
}
	
	
	
	

void NeuralNetwork::writeSpikeTimes_FPT(){
	string myfilename;
	cout << "Name of the file for FPT?\n";
	cin >> myfilename;
	NeuralNetwork::writeSpikeTimes_FPT(myfilename);
	}
	

void NeuralNetwork::writeSpikeTimes_ST(string filename){
	
	ofstream outFile;	
	for (int i=0; i < N; i++)
		{
		outFile << setprecision(3);
		outFile << fixed;
		outFile.open(filename + "_N" +  to_string(i) + ".txt");
			for (int k = 0; k < neur[i]->getSpikeTimes().size(); k++) { outFile << neur[i]->getSpikeTimes(k) << endl;}
		outFile.close();}

	/*
	ofstream outFile;
	string filename;	
	for (int i=0; i < N; i++)
	{
	string filename = "Train_N" + to_string(i) + ".txt";
	
	outFile.open(filename.c_str());
	for (int k = 0; k < S[i].size(); k++) { outFile << S[i][k] << endl;}
	outFile.close();
	
	}*/
	
	//writes a resume
	ofstream Rfile;
	Rfile.open (filename + "_resume.txt");
	Rfile << "This NeuralNetwork has " << N << " Neurons \n";
	Rfile << "Jump matrix (h): \n";

	Rfile << setprecision(3);
	Rfile << fixed;
	for (int i = 0; i<N; i++){
		for (int j = 0; j < N; j++){
			Rfile << h[i][j]<< " ";
			}
		Rfile << endl;
		}

	if(corr)
		{
		Rfile << "Correlation matrix (A): \n"; 		
		for (int i = 0; i<N; i++){
			for (int j = 0; j < N; j++){
				Rfile << A[i][j]<< " ";
				} 
			Rfile << endl;
			}
		Rfile << "L: \n"; 
		for (int i = 0; i<N; i++){
			for (int j = 0; j < N; j++){
				Rfile << L[i][j]<< " ";
				}
			Rfile << endl;
			}
		} // end if
		
	for (int i = 0; i<N; i++)
		{
		Rfile << 
	"Neuron: " << neur[i]->getID() <<
	" sigma: " << neur[i]->getSigma() <<
	" theta: " << neur[i]->getTheta() <<
	" mu: "	 << neur[i]->getMu() <<
	" C: " << neur[i]->getC() << endl;
		}
	Rfile.close();	
		
}
	
void NeuralNetwork::writeSpikeTimes_ST(){
	string myfilename;
	cout << "Name of the file for spike train?\n";
	cin >> myfilename;
	NeuralNetwork::writeSpikeTimes_ST(myfilename);
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

void NeuralNetwork::writeLog(string filename)
	{
		ofstream myfile;
	  	myfile.open(filename);
	  	for (int t = 0; t < neur[0]->getLog().size(); t++){
	  		myfile << t * neur[0]->getDt() << " ";
			for (int i=0; i<N; i++){
				myfile << neur[i]->getLog(t)<< " ";
				} // end for
			myfile << endl;	
			}	
		myfile.close();
	
	}

void NeuralNetwork::printParam(){
	cout << "This NeuralNetwork has " << N << " Neurons \n";
	cout << "Jump matrix (h): \n";
	
	cout << setprecision(3);
	cout << fixed;
	for (int i = 0; i<N; i++){
		for (int j = 0; j < N; j++){
			cout << h[i][j]<< " ";
			}
		cout << endl;
		}
	
	if(corr)
		{
		cout << "Correlation matrix (A): \n"; 		
		for (int i = 0; i<N; i++){
			for (int j = 0; j < N; j++){
				cout << A[i][j]<< " ";
				} 
			cout << endl;
			}
		cout << "L: \n"; 
		for (int i = 0; i<N; i++){
			for (int j = 0; j < N; j++){
				cout << L[i][j]<< " ";
				}
			cout << endl;
			}
		} // end if
	
	for (int i = 0; i<N; i++){
		neur[i]->printParam();
		}
} //end print param



