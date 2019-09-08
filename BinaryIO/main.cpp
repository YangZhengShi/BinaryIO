#include <string>
#include "..//StressFieldReader.h"
#include <iostream>
#include "..///StressField.h"
#include <boost/math/tools/roots.hpp>


int main(int argc, char** argv)
{
	int gridSize[3] = { 51,51,101 };
	float gridDiameter[3] = { 1.0f,1.0f,1.0f };

	StressField stressField;
	StressFieldOptions SFOs;

	stressField.setStressFieldOptions(SFOs);
	stressField.readField();

	

	for (int i = 4; i < 50; i++)
	{
		std::cout << stressField.getEigenvalues(i, 0, 0)[0] << "\n";
		std::cout << stressField.getEigenvalues(i, 0, 0)[1] << "\n";
		std::cout << stressField.getEigenvalues(i, 0, 0)[2] << "\n";
		std::cout <<"\n";
	}


	return 0;
}