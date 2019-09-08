#pragma once

#include "StressTensor.h"
#include <math.h>

float determinant(const StressTensor& tensor)
{

	float det = tensor.sigma_x * (tensor.sigma_y * tensor.sigma_z - static_cast<float>(pow(tensor.tau_zy, 2.0)));
	det += tensor.tau_xy * (tensor.tau_zx * tensor.tau_zy - tensor.tau_xy * tensor.sigma_z);
	det += tensor.tau_zx * (tensor.tau_xy * tensor.tau_zy - tensor.sigma_y * tensor.tau_zx);

	return det;
}