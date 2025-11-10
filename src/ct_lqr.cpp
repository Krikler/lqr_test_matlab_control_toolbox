#include <ct/optcon/optcon.h>

Eigen::MatrixXd computeLQRCt(const Eigen::MatrixXd& A,
                             const Eigen::VectorXd& B,
                             const Eigen::MatrixXd& Q,
                             const Eigen::MatrixXd& R)
{
	const int m = 1;
    const int n = 4;

	ct::optcon::LQR<n, m> lqrSolver;

	ct::core::StateMatrix<n> A_ct;
    ct::core::StateControlMatrix<n, m> B_ct;
    ct::core::StateMatrix<n> Q_ct;
    ct::core::ControlMatrix<m> R_ct;
    ct::core::FeedbackMatrix<n, m> K_ct;

	// Convert from Eigen dynamic (MatrixXd) to fixed-size ct matrices
	A_ct = A.cast<double>();
    Q_ct = Q.cast<double>();
    R_ct(0, 0) = R(0, 0);
    B_ct << B(0, 0), B(1, 0), B(2, 0), B(3, 0);

	const bool R_is_diagonal = true;
    const bool solve_riccati_iteratively = false;

    // Solve the LQR problem
    lqrSolver.compute(Q_ct, R_ct, A_ct, B_ct, K_ct, R_is_diagonal, solve_riccati_iteratively);

	// Extract the result, update the K matrix
	Eigen::MatrixXd K(m, n);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
        {
            K(i, j) = K_ct(i, j);
        }
	}

	return K;
}