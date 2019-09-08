#include <string>
#include "..//StressFieldReader.h"
#include <iostream>
#include "..///StressField.h"
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
		std::cout << stressField.getTensor(i,0,0).sigma_x<<"\n";
	}


	return 0;
}