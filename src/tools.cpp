#include <iostream>
#include "tools.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

Tools::Tools() {}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) {
    
    // RMSE to calculate performance of Kalman filter against ground truth
    // create and intitalise rmse vector
    VectorXd rmse(4);
    rmse << 0,0,0,0;
    
    // check: input estimation is not zero
    // check: estimation vector and ground truth vector are equal in size
    if(estimations.size() != ground_truth.size() || estimations.size() == 0) {
        cout << "Invalid estimation or ground truth data" << endl;
        return rmse;
    }
    
    // accumulate squared residuals
    for(unsigned int i=0; i < estimations.size(); ++i) {
        
        // temporary vector to get difference between est and gt
        VectorXd residual = estimations[i] - ground_truth[i];
        
        // coefficient-wise multiplication
        residual = residual.array()*residual.array();
        rmse += residual;
        
    }
    
    // calculate the mean
    rmse = rmse/estimations.size();
    
    // calculate sqaure root
    rmse = rmse.array().sqrt();
    
    // return result
    return rmse;
}
