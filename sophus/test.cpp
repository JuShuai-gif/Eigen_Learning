#include <iostream>
#include <cmath>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include "sophus/se3.hpp"
#include "sophus/so3.hpp"

using namespace Eigen;
using namespace std;

int main()
{
    Vector3d v_axis = AngleAxisd(M_PI / 2, Vector3d(0, 0, 1)).axis();
    double v_angle = AngleAxisd(M_PI / 2, Vector3d(0, 0, 1)).angle();
    Matrix3d v_v = AngleAxisd(M_PI / 2, Vector3d(0, 0, 1)).matrix();
    Matrix3d v_mat = AngleAxisd(M_PI / 2, Vector3d(0, 0, 1)).toRotationMatrix();

    std::cout << "旋转轴：" << v_axis << std::endl;
    std::cout << "旋转角：" << v_angle << std::endl;
    std::cout << "旋转轴：" << v_v << std::endl;
    std::cout << "旋转矩阵：" << v_mat << std::endl;

    Vector3d t(1, 0, 0); // 沿x轴平移1
    typedef Eigen::Matrix<double, 6, 1> Vector6d;
    std::cout << "R: \n" << v_mat << std::endl;
    std::cout << "t: \n" << t << std::endl;
    Sophus::SE3d SE3_Rt(v_mat, t); // 从R，t构造SE(3)

    std::cout << "旋转矩阵：\n" << SE3_Rt.so3().matrix() << std::endl;
    std::cout << "位移向量：\n" << SE3_Rt.translation() << std::endl;
    Eigen::AngleAxisd rotation_vector(SE3_Rt.so3().matrix());
    // 输出旋转向量
    std::cout << "Rotation Vector (Axis, Angle):\n"
              << "Axis: " << rotation_vector.axis().transpose()
              << "\nAngle: " << rotation_vector.angle() << std::endl;

    


    return 0;
}
