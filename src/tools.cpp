#include <iostream>
#include "tools.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

Tools::Tools() {}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) {

	// Initialize rmse vector
	VectorXd rmse(4);
	rmse << 0, 0, 0, 0;

	// Check the validity of the following inputs
	if (estimations.size() == 0 || estimations.size() != ground_truth.size()) {
		std::cout << "The inputs are not valid!\n";
		return rmse;
	}
	// Accumulate squaired residuals
	for (unsigned int i = 0; i < estimations.size(); ++i) {
		VectorXd residual = estimations[i] - ground_truth[i];

		// Coefficient-wise multiplication
		residual = residual.array() * residual.array();
		rmse += residual;
	}
	// Calculate the mean
	rmse = rmse / estimations.size();
	// Calculate the squared root
	rmse = rmse.array().sqrt();

	return rmse;
}