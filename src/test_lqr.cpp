#include "lqr_matlab.hpp"
#include "lqr_ct.hpp"

#include <Eigen/Dense>
#include <iostream>
#include <iomanip>

int test_loop(int n)
{
    int errors = 0;
    for (int i = 0; i < n; i++)
    {
        Eigen::MatrixXd A = Eigen::MatrixXd::Random(4,4);
        Eigen::MatrixXd B = Eigen::MatrixXd::Random(4,1);
        Eigen::MatrixXd Q = Eigen::MatrixXd::Identity(4,4);
        Eigen::MatrixXd R(1,1); R(0,0) = 1.0;

        auto K_matlab = computeLQRMatlab(A, B, Q, R);
        auto K_ct     = computeLQRCt(A, B, Q, R);

        Eigen::MatrixXd diff = K_matlab - K_ct;
        double error = diff.norm();

        if (error > 0.001)
        {
            errors++;
        }
    }
    return errors;
}

int main()
{
    Eigen::MatrixXd A = Eigen::MatrixXd::Random(4,4);
    Eigen::MatrixXd B = Eigen::MatrixXd::Random(4,1);
    Eigen::MatrixXd Q = Eigen::MatrixXd::Identity(4,4);
    Eigen::MatrixXd R(1,1); R(0,0) = 1.0;

    auto K_matlab = computeLQRMatlab(A, B, Q, R);
    auto K_ct     = computeLQRCt(A, B, Q, R);

    std::cout << "A = " << A << std::endl;
    std::cout << "B = " << B << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "K_matlab = " << K_matlab << std::endl;
    std::cout << "K_ct     = " << K_ct << std::endl;

    std::cout << "Errors: " << test_loop(10000) << std::endl;

    return 0;
}
