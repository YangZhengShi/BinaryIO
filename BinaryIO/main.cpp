#include <string>
#include "..//StressFieldReader.h"
#include <iostream>

int main(int argc, char** argv)
{
	int gridSize[3] = { 51,51,101 };
	float gridDiameter[3] = { 1.0f,1.0f,1.0f };

	std::string fileName = "beam3d_100_50_50_case3_stressField.bin";
	std::string filePath = "E:\\StressField\\";

	StressFieldReader stressFieldReader = StressFieldReader(fileName, filePath);
	
	stressFieldReader.setGridDiameter(&gridDiameter[0]);
	stressFieldReader.setGridSize(&gridSize[0]);

	StressTensor * field = stressFieldReader.readField();

	for (int i = 0; i < 100; i++)
	{
		std::cout << field[i].sigma_x<<"\n";
	}

	return 0;
}