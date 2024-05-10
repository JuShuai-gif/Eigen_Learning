#include <iostream>
#include <eigen3/Eigen/Core>

int main()
{
    Eigen::Vector3d v{1.2,2.3,5.9};
    // 一范数
    double vec_norm1 = v.lpNorm<1>();
    std::cout << "Vec One Norm: " << vec_norm1 << std::endl;
    // 二范数
    double vec_norm2 = v.norm();
    std::cout << "Vec Two Norm: " << vec_norm2 << std::endl;
    // 无穷范数
    double vec_normInf = v.lpNorm<Eigen::Infinity>();
    std::cout << "Vec Infinity-norm: " << vec_normInf << std::endl;

    Eigen::MatrixXd A(3,3);
    A << 1,2,3,
        4,5,6,
        7,8,9;
    
    /*关于矩阵一范数，下面这种我觉得它是按照向量求解的*/
    double mat_norm1 = A.lpNorm<1>();
    // 这个求解矩阵一范数才对
    double matrix1Norm = A.colwise().lpNorm<1>().maxCoeff();
    std::cout << "Mat One Norm: " << matrix1Norm << std::endl;
    // 矩阵二范数
    double mat_norm2 = A.norm();
    std::cout << "Mat Two Norm: " << mat_norm2 << std::endl;
    // 矩阵无穷范数
    double mat_normInf = A.lpNorm<Eigen::Infinity>();
    std::cout << "Mat Inf Norm: " << mat_normInf << std::endl;
    return 0;
}