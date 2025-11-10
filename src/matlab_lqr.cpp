#include "lqr_matlab.hpp"

#include <MatlabEngine.hpp>
#include <MatlabDataArray.hpp>
#include <memory>
#include <vector>

Eigen::MatrixXd computeLQRMatlab(const Eigen::MatrixXd& A,
                                 const Eigen::VectorXd& B,
                                 const Eigen::MatrixXd& Q,
                                 const Eigen::MatrixXd& R)
{
    const int m = 1;
    const int n = 4;

    static std::unique_ptr<matlab::engine::MATLABEngine> matlabEnginePtr = matlab::engine::startMATLAB();

    matlab::data::ArrayFactory factory;

    matlab::data::TypedArray<double> Am = factory.createArray<double>({n, n}, {
        A(0,0), A(1,0), A(2,0), A(3,0),
        A(0,1), A(1,1), A(2,1), A(3,1),
        A(0,2), A(1,2), A(2,2), A(3,2),
        A(0,3), A(1,3), A(2,3), A(3,3)
    });

    matlab::data::TypedArray<double> Bm = factory.createArray<double>({n, m}, { 
        B(0), 
        B(1), 
        B(2), 
        B(3) 
    });

    matlab::data::TypedArray<double> Qm = factory.createArray<double>({n, n}, {
        Q(0,0), Q(1,0), Q(2,0), Q(3,0),
        Q(0,1), Q(1,1), Q(2,1), Q(3,1),
        Q(0,2), Q(1,2), Q(2,2), Q(3,2),
        Q(0,3), Q(1,3), Q(2,3), Q(3,3)
    });

    matlab::data::TypedArray<double> Rm = factory.createArray<double>({m, m}, { R(0,0) });

    std::vector<matlab::data::Array> args({ Am, Bm, Qm, Rm });

    // Solve the LQR problem
    matlab::data::TypedArray<double> Km = matlabEnginePtr->feval(u"lqr", args);

    Eigen::MatrixXd K(m, n);

    // Extract the result, update the K matrix
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            K(i, j) = Km[i * n + j];
        }
    }

    return K;
}