#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <unsupported/Eigen/MatrixFunctions> // For matrix exponential

int main()
{
    // 定义旋转矩阵
    Eigen::Matrix3d rotation_matrix;
    double angle = M_PI / 4; // 45度
    rotation_matrix =
        Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitZ()).toRotationMatrix();

    // 输出旋转矩阵
    std::cout << "Rotation matrix:\n" << rotation_matrix << std::endl;

    // 从旋转矩阵计算欧拉角
    Eigen::Vector3d euler_angles =
        rotation_matrix.eulerAngles(2, 1, 0); // ZYX顺序
    std::cout << "Euler angles (ZYX):\n"
              << euler_angles.transpose() << std::endl;

    Eigen::Matrix3d rotation_matrix1;
    rotation_matrix1 =
        Eigen::AngleAxisd(euler_angles[0], Eigen::Vector3d::UnitZ()) *
        Eigen::AngleAxisd(euler_angles[1], Eigen::Vector3d::UnitY()) *
        Eigen::AngleAxisd(euler_angles[2], Eigen::Vector3d::UnitX());

    // 输出旋转矩阵
    std::cout << "Rotation matrix from Euler angles (ZYX):\n"
              << rotation_matrix1 << std::endl;

    // 从旋转矩阵计算四元数
    Eigen::Quaterniond quaternion(rotation_matrix);
    std::cout << "Quaternion:\n"
              << quaternion.coeffs().transpose() << std::endl;

    // 定义轴角表示
    Eigen::AngleAxisd angle_axis(angle, Eigen::Vector3d::UnitZ());
    std::cout << "Angle-Axis:\n";
    std::cout << "Angle: " << angle_axis.angle() << "\n";
    std::cout << "Axis: " << angle_axis.axis().transpose() << "\n";

    // 从四元数计算旋转矩阵
    Eigen::Matrix3d quat_to_rot = quaternion.toRotationMatrix();
    std::cout << "Rotation matrix from quaternion:\n"
              << quat_to_rot << std::endl;

    // 使用李群表示 (SO(3))
    Eigen::Vector3d rotation_vector =
        angle * Eigen::Vector3d::UnitZ(); // 旋转向量
    Eigen::Matrix3d skew_symmetric;
    skew_symmetric << 0, -rotation_vector.z(), rotation_vector.y(),
        rotation_vector.z(), 0, -rotation_vector.x(), -rotation_vector.y(),
        rotation_vector.x(), 0;

    // 计算李代数到李群的映射 (matrix exponential)
    Eigen::Matrix3d so3_to_SO3 = skew_symmetric.exp();
    std::cout << "SO(3) from rotation vector:\n" << so3_to_SO3 << std::endl;

    // 从SO(3)计算旋转向量（李代数）
    Eigen::AngleAxisd recovered_angle_axis(so3_to_SO3);
    Eigen::Vector3d recovered_rotation_vector =
        recovered_angle_axis.angle() * recovered_angle_axis.axis();
    std::cout << "Recovered rotation vector:\n"
              << recovered_rotation_vector.transpose() << std::endl;

    return 0;
}
