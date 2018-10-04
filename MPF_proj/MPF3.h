#pragma once
#include<iostream>
#include<vector>
using namespace std;

class MPF3 {
public:

	MPF3();
	vector<vector<double>> calculateTransfer(double dx, double dt, double t, double coolSpeed, int steps);

private:

	double Q, R, d0;
	vector<double> c1, c2;

	double calculateIntegral(vector<double> v, int ksi);
	void printActualC(vector<double> v);

};