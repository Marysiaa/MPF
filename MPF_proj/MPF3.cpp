#include "MPF3.h"

MPF3::MPF3()
{
	Q = 140000;
	R = 8.3144;
	d0 = 0.000041;
	for (int i = 0; i < 102; i++)
	{
			c1.push_back(0.1);
			c2.push_back(0.1);
	}
}

vector<vector<double>> MPF3::calculateTransfer(double dx, double dt, double t, double coolSpeed, int steps)
{
	vector<vector<double>> transferC;
	vector<double> actualC;
	int ksi = 0;
	double c_gamma_alpha, D, temp_kelvin, x;
	double temp = t;

	double c_integral = 0, dc = 0;	// dc - roznica pol
	double first_integral = calculateIntegral(c1, ksi + 1);

	double c0 = 0.1; // %C - zawartość węgla w austenicie
	double ca = 0.02;

	transferC.push_back(c2);

	for (int i = 0; i < steps; i++)
	{
		// dostarczenie węgla
		c_gamma_alpha = -(temp-845)/210;
		c1[ksi] = c_gamma_alpha;
		c2[ksi] = 0.02;

		// obliczenie różnicy pól
		c_integral = calculateIntegral(c1, ksi+1);
		dc = c_integral - first_integral;

		// oblicznie paranetrów dla aktualnej temperatury 
		temp_kelvin = temp + 273;
		D = d0 * exp(-Q / (R * temp_kelvin))*1E10;
		x = (D*dt) / (dx*dx);

		// obliczenie wartości do c2 na podstawie c1
		for (int j = ksi+1; j < c2.size()-1; j++)
		{
			c2[j] = (1 - 2 * x)*c1[j] + x * (c1[j - 1] + c1[j + 1]);
		}

		// bilans masy - przesunięcide ksi, gdy będzie odpowiednia ilość węgla
		if (dc >= (c0 - ca) * dx)
		{
			ksi++;
			transferC.push_back(c2);
		}

		// przepisanie ostatniego elementu (pomocniczego do obliczeń)
		c2[c2.size() - 1] = c2[c2.size() - 2];
		// przepisanie aktualnych danych (wyliczonych do c2 na podstawie c1)
		c1 = c2;
		
		// zmiana temperatury
		temp = temp - coolSpeed * dt;

		if (ksi >= 100 || temp <= 727)
			break;
	}
	return transferC;
}

double MPF3::calculateIntegral(vector<double> v, int start)
{
	double integral = 0.0;
	for (int i = start; i < v.size()-1; ++i)
	{
		integral += 0.5 * (v[i-1] + v[i]);
	}
	return integral;
}

void MPF3::printActualC(vector<double> vec)
{
	for (auto v : vec) {
		std::cout << v << "\t";
	}
	std::cout << std::endl;

}
