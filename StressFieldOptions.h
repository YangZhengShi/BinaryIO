#pragma once

#include <string>

struct StressFieldOptions
{
	std::string fileName = "beam3d_100_50_50_case3_stressField.bin";
	std::string filePath = "E:\\StressField\\";

	size_t gridSize[3] = { 51ull,51ull,101ull };
	float gridDiameter[3] = { 1.0f,1.0f,1.0f };


};