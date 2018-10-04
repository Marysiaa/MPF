#pragma once
#include<string>
#include <fstream>

class FileSaver
{
public:

	template<typename T>
	void saveToFile(vector<vector<T>> vec, std::string filename);

	template<typename T>
	void saveToFile(vector<T> vec, std::string filename);

	template<typename T>
	void saveToFile(vector<pair <int, double>> vec, std::string filename);
};

template<typename T>
void FileSaver::saveToFile(vector<vector<T>> vec, std::string filename)
{
	vector< vector<double> >::iterator row;
	vector<double>::iterator col;

	ofstream myfile;
	myfile.open(filename);

	for (auto& row : vec) {
		for (auto& col : row) {
			myfile << col << "\t";
		}
		myfile << endl;
	}

	myfile.close();
}

template<typename T>
void FileSaver::saveToFile(vector<T> vec, std::string filename)
{
	ofstream myfile;
	myfile.open(filename);

	for (auto& row : vec) {
		myfile << row.first << "\t" << row.second << endl;
	}

	myfile.close();
}

template<typename T>
void FileSaver::saveToFile(vector<pair <int, double>> vec, std::string filename)
{
	ofstream myfile;
	myfile.open(filename);
	myfile.precision(4);
	for (auto& row : vec) {
		myfile << row << endl;
	}

	myfile.close();
}

