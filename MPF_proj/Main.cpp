#include<iostream>
#include "MPF2.h"
#include "MPF3.h"
#include "FileSaver.h"
using std::cout;
using std::endl;

int main()
{
	/*
	PROJEKT 3
	//temp: 780, 800
	// przy chlodzeniu: 800
	//predkosc chlodzenia: 0.1
	*/
	double dx = 0.1, dt = 0.001, temp = 800, coolSpeed = 0.1;
	int steps = 100000;

	MPF3 mpf;
	vector <vector<double>> transferC = mpf.calculateTransfer(dx, dt, temp, coolSpeed, steps);

	std::string transfer = "transferC_" + std::to_string(temp) + "_" + std::to_string(coolSpeed) + ".txt";
	FileSaver fileSaver;
	fileSaver.saveToFile(transferC, transfer);

	system("pause");

	/* 
	PROJEKT 2
	//temp:	780, 800, 820
	//przy nagrzewaniu : 727	->kryterium stabilnosci Neumanna
	//predkosci nagrzewania : 0.5, 2, 3

	double dx = 0.1, dt = 0.001, temp = 727, heatSpeed = 3;
	int steps = 100000;

	MPF2 mpf;
	vector <vector<double>> transferC = mpf.calculateTransfer(dx, dt, temp, heatSpeed, steps);

	std::string transfer = "transferC_" + std::to_string(temp) + "_" + std::to_string(heatSpeed) + ".txt";
	std::string phase = "phase_" + std::to_string(temp) + "_" + std::to_string(heatSpeed) + ".txt";
	FileSaver fileSaver;
	fileSaver.saveToFile(transferC, transfer);
	fileSaver.saveToFile(mpf.getPhaseVector(), phase);

	*/

}