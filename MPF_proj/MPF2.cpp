#include "MPF2.h"

MPF2::MPF2()
{
	Q = 140000;
	R = 8.3144;
	d0 = 0.000041;
	phaseBoundary = 12;
	for (int i = 0; i < 102; i++)
	{
		if (i < phaseBoundary)
		{
			c1.push_back(0.67);
			c2.push_back(0.67);
		}
		else
		{
			c1.push_back(0.02);
			c2.push_back(0.02);
		}
	}
}

vector<vector<double>> MPF2::calculateTransfer(double dx, double dt, double t, double heatSpeed, int steps)
{
	vector<vector<double>> transferC;
	vector<double> actualC;
	int ksi = phaseBoundary;
	double c_gamma_alpha, D, temp_kelvin, x;
	double temp = t;

	for (int i = 0; i < steps; i++)
	{
		actualC = c1;
		c_gamma_alpha = abs(4.8513 - 0.005776*temp);
		temp_kelvin = temp + 273;
		D = d0 * exp(-Q / (R * temp_kelvin))*1E10;
		x = (D*dt) / (dx*dx);
		temp = heatSpeed * dt + temp;
		
		for (int j = 1; j <= ksi; j++)
		{
			c2[j] = (1-2*x)*c1[j] + x*(c1[j-1]+c1[j+1]);
		}
		if (c2[ksi] >= c_gamma_alpha)
		{
			ksi++;
			c1[ksi] = 0.02;

			transferC.push_back(actualC);
		
			phaseVTimeMove.push_back(std::make_pair(i, ksi));
		}
		if (ksi > 100)
			break;

		c2[0] = c2[1];
		c1 = c2;
		c2[ksi + 1] = c2[ksi];
	}
	return transferC;
}

vector<pair <int, double>> MPF2::getPhaseVector()
{
	return phaseVTimeMove;
}