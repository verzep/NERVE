#ifndef CLASS_NEURON
#define CLASS_NEURON
#include <vector>
#include "statistic.h"

using namespace std;


class NeuralNetwork; //forward declaration

class Neuron{
	
	private:

	NeuralNetwork *myNN;
	int ID;						//number that identifies the neuron in the network (probably redundant) 

	double time; 				//time (reduntant, should be a common time for all the neurons)
	double mp;					//membrane potential


	double sigma; 				//noise intensity
	double theta; 				//membrane constant
	double mu; 					//input
	double C; 					//threshold
	 double dt;					//time interval

	bool wait;					//wait for the other neuron to spike (true when interested in FPT
	bool save_Log;				//save Logo of neural activity
	bool sp;					//if true, last timestep neuron spiked
	
	vector<double> spikeTimes;	// list of spike times (can be FPT or train)
	vector <double> Log;		//log of neural activity (element i is mp at i-th step)
	public:

	//Constructors	
	Neuron (double m, double s, double t, double c, bool save); 							// basic constructor
	Neuron (NeuralNetwork * nw, int ID, double m, double s, double t, double c, bool save); // constructor when the neuron is in a network
	// m -> mu s -> sigma, t -> theta, c -> C

	//Setters
	void setSigma(double x); 
	void setTheta(double x);
	void setMu(double x);
	void setC(double x);
	void setWait(bool x);
	void setSave_Log(bool x);
	void setSp(bool x);

	//Getters
	int 	getID();
	double 	getTime();
	double 	getMp();
	double 	getSigma();
	double 	getTheta();
	double 	getMu();
	double 	getC();
	double 	getDt();
	bool 	getWait();
	bool	getSave_Log();
	bool	getSp();
	vector<double>	getLog();
	vector<double> getSpikeTimes();
	double	getLog(int n);
	double 	getSpikeTimes(int n);
	
	
	void step(double noise); 			// single step forward in time
	void jump(double he);				// jump of the mp
	void reset();						// reset the neuron (also the log)
	void spike();						// neuron spikes and may interact with other neurons
		

	void writeLog();					// write on a file (name to be asked) the evolution of the value of the MP
	void printParam();					// print the parameters of the neurons

}; //end of class Neuron

#endif
