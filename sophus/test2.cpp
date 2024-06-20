#include <iostream>
#include <Eigen/Dense>
#include <unsupported/Eigen/MatrixFunctions>

int main(int argc, char* argv[]) {
    // 定义旋转向量 omega
    Eigen::Vector3d omega(1, 2, 3);
    
    // 计算旋转角度 theta 和旋转轴 n_w
    double theta = omega.norm();
    Eigen::Vector3d n_w = omega / theta;
    
    // 定义 n_w 的反对称矩阵 n_w_skew
    Eigen::Matrix3d n_w_skew;
    n_w_skew << 0, -n_w(2), n_w(1),
                n_w(2), 0, -n_w(0),
                -n_w(1), n_w(0), 0;

    // 使用罗德里格斯公式计算旋转矩阵 R_w
    Eigen::Matrix3d R_w = Eigen::Matrix3d::Identity()
                        + sin(theta) * n_w_skew
                        + (1 - cos(theta)) * n_w_skew * n_w_skew;

    std::cout << "cos(theta) " << cos(theta) << std::endl;
    std::cout << "n_w.transpose() " << n_w.transpose() << std::endl;

    Eigen::Matrix3d R_w_ = cos(theta) * Eigen::Matrix3d::Identity() 
                            + (1 - cos(theta)) * n_w * n_w.transpose() + sin(theta) * n_w_skew;

    // 使用指数映射计算旋转矩阵 R_w_exp
    Eigen::Matrix3d R_w_exp = (theta * n_w_skew).exp();

    // 输出结果
    std::cout  << "R_w_exp: \n" << R_w_exp << "\n";
    std::cout << "R_w \n" << R_w;

    return 0;
}
