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
#include <algorithm>  

#include "statistic.h"

using namespace std;

double eCDF(double x, vector<double> O)
{	double C = 0;
	double n = O.size();
	
	//cout << "x vale " << x << endl;
	while(O[C] <= x and C<n){
		//cout << O[C] << " ";
		C++;
		}
	//cout << endl;
	//cout <<C << " " << C / n << endl;
	return ( C / n );
}

vector<double> dist(vector<double> V1){
	vector<double> O1(V1);
	sort  ( O1.begin(), O1.end() );
	
	
	
	vector<double> U1;
	
	for (int i=0; i<O1.size(); i++)	U1.push_back( eCDF(V1[i], O1) );
	
	return U1;
}

vector<double> readData(string filename){
	//cout << "AAAAAAA" << endl;
	vector <double> V1;
	ifstream infile(filename);
	double a;
	while (infile >> a)
	 { 
	 V1.push_back(a);
	 }
	 return V1;
}




vector<double> ISI_fwd(vector<double> U1, int m, int nData, int start){
	vector<double> R;
	if ( start + nData + m + 1 > U1.size() ) {
		cout << "OUT OF RANGE " << endl;
		return R;}
	
	for(int i = start; i < start+nData; i++)
		{
		//cout << U1[i] << " " << U1[i + 1 + m] << endl;
		R.push_back(U1[i + 1 + m] - U1[i]);
		}
			
	return R;
}


vector<double> ISI_Rel_fwd(vector<double> U1, vector<double> U2, int m, int nData, int start){
	vector<double> R;
	int j =0;									//j runs on U2
	for(int i = start; i < start+nData; i++) 	//i runs on U1
		{						
		while(U2[j] <= U1[i])
			{
			j++;
			}
		R.push_back( U2[j+m] - U1[i] );
		}
	return R;
}

vector<double> ISI_bwd(vector<double> U1, int m, int nData, int start){
	vector<double> R;
	if ( start + nData + m > U1.size() ) {
		cout << "OUT OF RANGE " << endl;
		return R;}
	
	for(int i = start; i < start+nData; i++)
		{
		//cout << U1[i] << " " << U1[i - 1 - m] << endl;
		R.push_back(U1[i] - U1[i - 1 - m]);
		}
			
	return R;
}
	
	
vector<double> ISI_Rel_bwd(vector<double> U1, vector<double> U2, int m, int nData, int start){
	vector<double> R;
	int j =0;									//j runs on U2
	for(int i = start; i < start+nData; i++) 	//i runs on U1
		{						
		while(U2[j+1] < U1[i])
			{
			j++;
			}
		//cout << U1[i] << " " << U2[j - m] << endl;
		R.push_back(U1[i] - U2[j-m]);
		}
	return R;
}







void writeVec2D(vector<double> U1, vector<double> U2){
	string filename;
	ofstream myfile;
	
	cout << "Please enter the name of the file for the vec (.txt will be added): " << endl;
    cin >> filename;
    myfile.open(filename + ".txt");
    
    for(int i= 0; i < U1.size(); i++){
    	myfile << U1[i] << " " << U2[i] << endl;
    }
    
    myfile.close();	
}


void writeVec2D(vector<double> U1, vector<double> U2, string filename){
	ofstream myfile;
    myfile.open(filename);
   	myfile << setprecision(4);
	myfile << fixed;
    
    for(int i= 0; i < U1.size(); i++){
    	myfile << U1[i] << " " << U2[i] << endl;
   	 }
    
    myfile.close();	
}


void writeVec3D(vector<double> U1, vector<double> U2, vector<double> U3, string filename){
	ofstream myfile;
    myfile.open(filename);
   	myfile << setprecision(4);
	myfile << fixed;
    
    for(int i= 0; i < U1.size(); i++){
    	myfile << U1[i] << " " << U2[i] << " " << U3[i] << endl;
   	 }
    
    myfile.close();	
}


void ISI_full_2D( vector<double> U1, vector<double> U2, string filename)
	{
	// 01 fwd
	cout << "Creo" << endl;
	vector<double> A1 = ISI_fwd(U1, 0, 10000,50);
	vector<double> B1 = ISI_Rel_fwd(U1, U2, 0, 10000, 50);
	
	
	writeVec2D(A1, B1 , filename + "_01_FWD.txt");



	// 01  bwd
	cout << "Creo" << endl;
	vector<double> A2 = ISI_bwd(U1, 0, 10000,50);
	vector<double> B2 = ISI_Rel_bwd(U1, U2, 0, 10000, 50);

	writeVec2D(A2, B2 , filename + "_01_BWD.txt");

	

	// 1 0 fwd
	cout << "Creo" << endl;
	vector<double> A3 = ISI_fwd(U2, 0, 10000,50);
	vector<double> B3 = ISI_Rel_fwd(U2, U1, 0, 10000, 50);

	writeVec2D(A3, B3 , filename + "_10_FWD.txt");

	
	// 1 0 bwd
	cout << "Creo" << endl;
	vector<double> A4 = ISI_bwd(U2, 0, 10000,50);
	vector<double> B4 = ISI_Rel_bwd(U2, U1, 0, 10000, 50);

	writeVec2D(A4, B4 , filename + "_10_BWD.txt");

	}
	
	
	
	void ISI_full_3D( vector<double> U1, vector<double> U2, vector<double> U3, string filename)
	{
	// 0  fwd
	cout << "Creo" << endl;
	vector<double> A1 = ISI_fwd(U1, 0, 10000,50);
	vector<double> B1 = ISI_Rel_fwd(U1, U2, 0, 10000, 50);
	vector<double> C1 = ISI_Rel_fwd(U1, U3, 0, 10000, 50);
	
	writeVec3D(A1, B1, C1 , filename + "_012_FWD.txt");



	// 0 bwd
	cout << "Creo" << endl;
	vector<double> A2 = ISI_bwd(U1, 0, 10000,50);
	vector<double> B2 = ISI_Rel_bwd(U1, U2, 0, 10000, 50);
	vector<double> C2 = ISI_Rel_bwd(U1, U3, 0, 10000, 50);

	writeVec3D(A2, B2, C2 , filename + "_012_BWD.txt");
	
	
	// 1 fwd
	cout << "Creo" << endl;
	vector<double> A3 = ISI_fwd(U2, 0, 10000,50);
	vector<double> B3 = ISI_Rel_fwd(U2, U1, 0, 10000, 50);
	vector<double> C3 = ISI_Rel_fwd(U2, U3, 0, 10000, 50);
	
	writeVec3D(A3, B3, C3 , filename + "_102_FWD.txt");



	// 1 bwd
	cout << "Creo" << endl;
	vector<double> A4 = ISI_bwd(U2, 0, 10000,50);
	vector<double> B4 = ISI_Rel_bwd(U2, U1, 0, 10000, 50);
	vector<double> C4 = ISI_Rel_bwd(U2, U3, 0, 10000, 50);

	writeVec3D(A4, B4, C4 , filename + "_102_BWD.txt");
	

	// 2  fwd
	cout << "Creo" << endl;
	vector<double> A5 = ISI_fwd(U3, 0, 10000,50);
	vector<double> B5 = ISI_Rel_fwd(U3, U1, 0, 10000, 50);
	vector<double> C5 = ISI_Rel_fwd(U3, U2, 0, 10000, 50);
	
	writeVec3D(A5, B5, C5 , filename + "_201_FWD.txt");



	// 2 bwd
	cout << "Creo" << endl;
	vector<double> A6 = ISI_bwd(U3, 0, 10000,50);
	vector<double> B6 = ISI_Rel_bwd(U3, U1, 0, 10000, 50);
	vector<double> C6 = ISI_Rel_bwd(U3, U2, 0, 10000, 50);

	writeVec3D(A6, B6, C6 , filename + "_201_BWD.txt");
	

	}




