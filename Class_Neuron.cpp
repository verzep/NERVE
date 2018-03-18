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

#include "Class_Neuron.h"
#include "Class_NeuralNetwork.h" 


/////////////////////////////////////////////////////////////
/////////////////				/////////////
/////////////////	NEURON FUNCTIONS 	/////////////	
////////////////				/////////////
/////////////////////////////////////////////////////////////


Neuron::Neuron( double m, double s, double t, double c, bool save=false){
	sigma = s;
	theta = t;
	mu = m;
	C = c;
	dt = 0.01;
	save_Log = save;
	sp=false;

	time = 0;
	mp= 0;
	wait = false;
	Log.push_back(0.);
}

Neuron::Neuron(NeuralNetwork* nw, int i, double m, double s, double t, double c, bool save=false){
	
	myNN = nw;
	ID = i;
	
	sigma = s;
	theta = t;
	mu = m;
	C = c;
	dt = 0.01;
	save_Log = save;
	sp=false;

	time = 0;
	mp= 0;
	wait = false;
	Log.push_back(0.);
}

/////// Setter

void Neuron::setSigma(double x){
	sigma=x;
}

void Neuron::setTheta(double x){
	theta=x;
}


void Neuron::setMu(double x){
	mu=x;
}


void Neuron::setC(double x){
	C=x;
}

void Neuron::setWait(bool x){
	wait=x;
}


void Neuron::setSave_Log(bool x){
	save_Log=x;
}

void Neuron::setSp(bool x){
	sp=x;
}
//Getters

int Neuron::getID(){
	return ID;
}

double Neuron::getTime(){
	return time;
}

double Neuron::getMp(){
	return mp;
}

double Neuron::getSigma(){
	return sigma;
}

double Neuron::getTheta(){
	return theta;
}

double Neuron::getMu(){
	return mu;
}

double Neuron::getC(){
	return C;
}


double Neuron::getDt(){
	return dt;
}

bool Neuron::getWait(){
	return wait;
}

bool Neuron::getSave_Log(){
	return save_Log;
}

bool Neuron::getSp(){
	return sp;
}

vector<double> Neuron::getLog(){
	return Log;
}

vector<double> Neuron::getSpikeTimes(){
	return spikeTimes;
}


double Neuron::getLog(int n){
	return Log[n];
}

double Neuron::getSpikeTimes(int n){
	return spikeTimes[n];
}

//Activity-related functions




void Neuron::step(double noise){
	if(!wait) mp += (-(mp/theta) + mu) * dt  + noise*sigma * sqrt(dt);
	time+= dt;
	if(save_Log)  Log.push_back(mp);
	// in this way you MUST NOT change save_Log during execution. Find a way to add the mp in time position
}

void Neuron::jump( double he){
	if(!wait) 
		{
		//cout << " JUMP ID time MP " << ID << " " << time << " " << mp << endl;
		mp += he;
		Log.back() += he;
		
		}
	//cout << "jump! "<< mp << endl;
}

void Neuron::reset(){
	mp=0;
	time=0;
	wait = false;
	sp = false;
	Log.clear();
}

void Neuron::spike(){
	//cout << " SPIKE ID time MP " << ID << " " << time << " " << mp << endl;
	spikeTimes.push_back(time);
	mp=0;
	sp = true;
	myNN->activity(ID); // myNN may not exist, this could be a problem
	if (save_Log) Log.back() = 10;	
}

//////// IO functions


void Neuron::writeLog()
	{
	
	string filename;
	ofstream myfile;
	
	cout << "Please enter a name for your file: " << endl;
    	cin >> filename;
	
	
	  myfile.open(filename + ".txt");
	  for (int t = 0; t < Log.size(); t++){
		myfile << t * dt << " " << Log[t] << endl;
		} // end for
	  myfile.close();
	}
	
void Neuron::printParam(){
	cout << 
	"Neuron: " << ID <<
	" sigma: " << sigma <<
	" theta: " << theta <<
	" mu: "	 << mu <<
	" C: " << C << endl;
	}	
	
	
	
	
	
	
	
