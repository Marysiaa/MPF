#pragma once
#include<vector>
using namespace std;

class MPF2 {
public:

	MPF2();
	vector<vector<double>> calculateTransfer(double dx, double dt, double t, double heatSpeed, int steps);
	vector<pair <int, double>> getPhaseVector();

private:

	double Q, R, d0;
	int phaseBoundary;
	vector<double> c1, c2;
	vector<pair <int, double>> phaseVTimeMove;

};