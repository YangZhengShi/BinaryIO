#pragma once

#include "StressFieldReader.h"
#include "StressFieldOptions.h"

class StressField
{
private:


	StressFieldOptions stressFieldOptions;
	StressFieldReader stressFieldReader;
	StressTensor* field = nullptr;

public:

	StressTensor getTensor(const float& x, const float& y, const float& z);

	void readField();

	float * getPrinciple(const float & x, const float & y, const float & z);

	void setStressFieldOptions(StressFieldOptions& SFOs)
	{
		this->stressFieldOptions = SFOs;
	}

};