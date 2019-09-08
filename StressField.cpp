#include "StressField.h"
#include "linearIndex.h"
#include "HelperSymmetricMatrix.h"
#include <boost/qvm/mat_operations.hpp>
#include <boost/numeric/ublas/matrix.hpp>
void StressField::readField()
{
	this->stressFieldReader.setFileName(this->stressFieldOptions.fileName);
	this->stressFieldReader.setFilePath(this->stressFieldOptions.filePath);
	this->field = this->stressFieldReader.readField
	(
		this->stressFieldOptions.gridSize[0] *
		this->stressFieldOptions.gridSize[1] *
		this->stressFieldOptions.gridSize[2] *
		sizeof(StressTensor)
	);

}



StressTensor StressField::getTensor(const float & x, const float & y, const float & z)
{
	StressTensor stressTensor = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

	size_t x0 = size_t(x);
	size_t y0 = size_t(y);
	size_t z0 = size_t(z);

	size_t x1 = x0;
	size_t y1 = y0;
	size_t z1 = z0;

	

	// In this way the boundries won't be a problem
	if (x0 != x)
		x1 += 1;

	if (y0 != y)
		y1 += 1;

	if (z0 != z)
		z1 += 1;
		
	float delta_x = x - x0;
	float delta_y = y - y0;
	float delta_z = z - z0;

	size_t3 edges[8] =
	{
		{x0,y0,z0},		//(0,0,0)	-> edges[0]
		{x1,y0,z0},		//(1,0,0)	-> edges[1]
		{x0,y1,z0},		//(0,1,0)	-> edges[2]
		{x0,y0,z1},		//(0,0,1)	-> edges[3]
		{x1,y0,z1},		//(1,0,1)	-> edges[4]
		{x0,y1,z1},		//(0,1,1)	-> edges[5]
		{x1,y1,z0},		//(1,1,0)	-> edges[6]
		{x1,y1,z1}		//(1,1,1)	-> edges[7]
	
	};

	size_t4 dim = 
	{ 
		this->stressFieldOptions.gridSize[0],
		this->stressFieldOptions.gridSize[1],
		this->stressFieldOptions.gridSize[2],
		6 // The Stress Tensor can be represented by 6 element as it is symmetric
	};
	
	size_t zz = linearIndex(edges[0], dim);

	StressTensor mm = this->field[zz];
	
	
	stressTensor =
		this->field[linearIndex(edges[0], dim)] * (1 - delta_x) * (1 - delta_y) * (1 - delta_z) +
		this->field[linearIndex(edges[1], dim)] * delta_x * (1 - delta_y) * (1 - delta_z) +
		this->field[linearIndex(edges[2], dim)] * (1 - delta_x) * delta_y * (1 - delta_z) +
		this->field[linearIndex(edges[3], dim)] * (1 - delta_x) * (1 - delta_y) * delta_z +
		this->field[linearIndex(edges[4], dim)] * delta_x * (1 - delta_y) * delta_z +
		this->field[linearIndex(edges[5], dim)] * (1 - delta_x) * delta_y* delta_z +
		this->field[linearIndex(edges[6], dim)] * delta_x * delta_y * (1 - delta_z) +
		this->field[linearIndex(edges[7], dim)] * delta_x * delta_y * delta_z;

	return stressTensor;
}


double * StressField::getEigenvalues(const float& x, const float& y, const float& z)
{
	StressTensor stressTensor = this->getTensor(x, y, z);

	static double eigen[3] = { 0.0f,0.0f,0.0f };


	//https://en.wikipedia.org/wiki/Eigenvalue_algorithm
	//Given a real symmetric 3x3 matrix A, compute the eigenvalues
	// Note that acosand cos operate on angles in radians

	double p1 = pow(stressTensor.tau_xy, 2.0) + pow(stressTensor.tau_zx, 2.0) + pow(stressTensor.tau_zy, 2.0);
	if (p1 == 0)// A is diagonal.
	{
		eigen[0] = stressTensor.sigma_x;
		eigen[1] = stressTensor.sigma_y;
		eigen[2] = stressTensor.sigma_z;
	}
	else
	{
		double trace = stressTensor.sigma_x + stressTensor.sigma_y + stressTensor.sigma_z;
		double q = trace / 3.0;
		double p2 =
			pow((stressTensor.sigma_x - q), 2.0) +
			pow((stressTensor.sigma_y - q), 2.0) +
			pow((stressTensor.sigma_z - q), 2.0) +
			2.0 * p1;

		double p = sqrt(p2 / 6.0);
		StressTensor B = (1 / p) * (stressTensor - q * IDENTITY);
		double r = determinant(B) / 2.0;
		double phi = 0.0f;

		if (r <= -1)
		{
			phi = PI / 3.0;
		}
		else if(r >= 1)
		{
			phi = 0.0f;
		}
		else
		{
			phi = acos(r) / 3;

		}

		// the eigenvalues satisfy eig3 <= eig2 <= eig1

		eigen[0] = (q + 2.0f * p * cos(phi));
		eigen[1] = (q + 2.0f * p * cos(phi + (2.0f * PI / 3.0f)));
		eigen[2] = (3.0f * q - eigen[1] - eigen[2]);

	}

	return eigen;
}


double* StressField::getEigenvectors(const float& x, const float& y, const float& z)
{
	StressTensor stressTensor = this->getTensor(x, y, z);
	boost::numeric::ublas::matrix<double> b_stressTensor(3, 3);

	b_stressTensor(0, 0) = stressTensor.sigma_x;
	b_stressTensor(1, 1) = stressTensor.sigma_y;
	b_stressTensor(2, 2) = stressTensor.sigma_z;

	b_stressTensor(0, 1) = stressTensor.tau_xy;
	b_stressTensor(1, 0) = stressTensor.tau_xy;

	b_stressTensor(0, 2) = stressTensor.tau_zx;
	b_stressTensor(2, 0) = stressTensor.tau_zx;


	b_stressTensor(1, 2) = stressTensor.tau_zy;
	b_stressTensor(2, 1) = stressTensor.tau_zy;



	boost::qvm::inverse(b_stressTensor);
}
