#pragma once

#include <Eigen/Dense>

Eigen::MatrixXd computeLQRMatlab(const Eigen::MatrixXd& A,
                                 const Eigen::VectorXd& B,
                                 const Eigen::MatrixXd& Q,
                                 const Eigen::MatrixXd& R);
