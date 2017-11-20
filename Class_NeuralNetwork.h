#ifndef CLASS_NEURALNETWORK
#define CLASS_NEURALNETWORK
#include "statistic.h"
#include <string>


class Neuron;

class NeuralNetwork{
	
	
	private:
	
	int N;				//number of neuron in the network
	Neuron **neur;		//neurons in the network
	double **h; 		//element i,j represents the h of the jump that i generate in j (jump matrix)
	double **A;			// covariance matrix
	
	double **L;			// Cholesky decomposition
	bool corr;			// noise is correlated (A regulates this)
	
	
	
	public:
	
	//constructors and inizialization methods
	
	NeuralNetwork(int numNeur); // basic constructor with default param
	NeuralNetwork(int numNeur, double mu, double sigma, double theta, double C);
	
	void createJumpMatrix(double **J); // set the value h, taken by a given matrix J
	void createCovMatrix(double **C); // set the value of A, taken by a given matrix C (also set corr = true)
	
	//setters
	
	void setH(int i, int j, double val); 
	void setA(int i, int j, double val);
	void setL(int i, int j, double val);
	void cDecomposition(); // Cholesky–Banachiewicz algorithm
	
	//getters
	
	
	Neuron* 	getNeur(int i);
	double 		getH(int i, int j);
	double		getA(int i, int j);
	double		getL(int i, int j);
	bool		getCorr(); 
	
	// time evolution
	
	
	void activity(int i); 						// neuron i did a spike;
	void FPT(int NData); 						// generates NDATA data of First Passage Time
	void spikeTrain(double Tmax, bool save);	// generates a spike trains of lenght Tmax
	
	// input-ouput-related methods
	
	
	void writeSpikeTimes_FPT(string filename); // write the spike times on a file name "filename" (FPT version)
	void writeSpikeTimes_FPT();					// write the spike times on a file, will ask fot the name (FPT version)
	
	void writeSpikeTimes_ST(string filename); 	// write the spike times on a file name "filename" (Spike train version)
	void writeSpikeTimes_ST();					// write the spike times on a file, will ask fot the name (spike train version)

	void writeLog(string filename); 	//write on "filename" the Log of all neurons.
	void writeLog(); 					// write on a file the Log of all neurons, will ask for the name of the file to write
	
	void printParam(); 					//print the parameters of the network (and of each neuron in it)
	

}; // end of class NN


#endif
