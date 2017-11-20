using namespace std;
#include <vector>
#include <string>

double eCDF(double x, vector <double> O); // compute the empirical CDF of point x given the data O


vector<double> dist(vector<double> V); // return a vector of the value of the eCDF in each point

vector<double> readData(string filename); //read the data for a file with a single data




vector<double> ISI_fwd(vector<double> U1, int m, int nData, int start);
vector<double> ISI_Rel_fwd(vector<double> U1, vector<double> U2, int m, int nData, int start);

vector<double> ISI_bwd(vector<double> U1, int m, int nData, int start);
vector<double> ISI_Rel_bwd(vector<double> U1, vector<double> U2, int m, int nData, int start);

void writeVec2D(vector<double> U1, vector<double> U2);
void writeVec2D(vector<double> U1, vector<double> U2, string filename);

void writeVec3D(vector<double> U1, vector<double> U2, vector<double> U3, string filename);

void ISI_full_2D( vector<double> U1, vector<double> U2, string filename);
void ISI_full_3D( vector<double> U1, vector<double> U2, vector<double> U3, string filename);
