#include <iostream>
#include <Eigen/Dense>

int main() {
    // 创建一个3x3的矩阵
    Eigen::MatrixXd matrix(3, 3);
    matrix << 1, 2, 3,
              4, 5, 6,
              7, 8, 9;

    std::cout << "Original Matrix:\n" << matrix << "\n\n";

    // 进行SVD分解
    Eigen::JacobiSVD<Eigen::MatrixXd> svd(matrix, Eigen::ComputeThinU | Eigen::ComputeThinV);

    // 获取U、S和V矩阵
    Eigen::MatrixXd U = svd.matrixU();
    Eigen::MatrixXd S = svd.singularValues().asDiagonal();
    Eigen::MatrixXd V = svd.matrixV();

    if (U.determinant() * V.determinant() < 0)
    {
        for (int x = 0; x < 3; ++x)
            V(x,2) *= -1;
        
    }
    

    std::cout << "U Matrix:\n" << U << "\n\n";
    std::cout << "S Matrix (Diagonal):\n" << S << "\n\n";
    std::cout << "V Matrix:\n" << V << "\n\n";

    // 重建原始矩阵
    Eigen::MatrixXd reconstructed_matrix = U * S * V.transpose();

    std::cout << "Reconstructed Matrix:\n" << reconstructed_matrix << "\n\n";

    return 0;
}
