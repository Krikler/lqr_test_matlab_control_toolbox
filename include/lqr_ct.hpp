#pragma once

#include <Eigen/Dense>

Eigen::MatrixXd computeLQRCt(const Eigen::MatrixXd& A,
                             const Eigen::VectorXd& B,
                             const Eigen::MatrixXd& Q,
                             const Eigen::MatrixXd& R);
