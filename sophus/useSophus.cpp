#include <iostream>
#include <cmath>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include "sophus/se3.hpp"
#include "sophus/so3.hpp"

using namespace std;
using namespace Eigen;

int main(int argc,char **argv)
{

    // 定义double绕z轴旋转90度的矩阵
    Matrix3d R = AngleAxisd(M_PI/2,Vector3d(0,0,1)).toRotationMatrix();
    std::cout << R << std::endl;
    
    // 转换为四元数
    Quaterniond q(R);
    Sophus::SO3d SO3_R(R);  // 旋转矩阵直接转为李群
    Sophus::SO3d SO3_q(q);  // 四元数直接构造李群
    std::cout << "旋转矩阵转换为李群：\n" << SO3_R.matrix() << std::endl;
    std::cout << "四元数构造李群：\n" << SO3_q.matrix() << std::endl;
    // 这时你会发现SO3_R和R的输出不一样，因为他们内部的表达机制不一样，但是此时他们的作用是一样都是表示同一种旋转
    // 下面是验证
    Vector3d v{1,5.3,2.4};
    Vector3d R_v = R * v;
    Vector3d SO3_R_v = SO3_R * v;
    // 旋转之后得到的点是一样的
    std::cout << "R_v:\n" << R_v << std::endl;
    std::cout << "SO3_R_v:\n" << SO3_R_v << std::endl;

    // 使用对数映射得到它的李代数（log也包括上三角操作）
    Vector3d so3 = SO3_R.log();
    std::cout << "Lie代数（对数） so3:\n" << so3.transpose() << std::endl;

    // 使用hat将Lie代数映射回反对称矩阵
    Matrix3d so3_hat = Sophus::SO3d::hat(so3.transpose());
    std::cout << "hat(so3):\n" << so3_hat << std::endl;

    // 使用exp将反对称矩阵映射回Lie群
    /*
    这里其实应该会有疑惑的？因为李代数到R是要先取下三角，然后取指数，然后得到R，为什么直接exp(李代数)就可以了
    那时因为exp内部已经包含了取下三角
    */
    Sophus::SO3d SO3_exp = Sophus::SO3d::exp(so3);
    std::cout << "exp(hat(so3)).matrix():\n" << SO3_exp.matrix() << std::endl;

    // hat 为向量到反对称矩阵
    std::cout << "fai的下三角取指数得到的R=\n" << Sophus::SO3d::hat(so3) << std::endl;
    // 相对的，vee为反对称矩阵到向量
    std::cout << "so3 hat vee=" << Sophus::SO3d::vee(Sophus::SO3d::hat(so3)).transpose() << std::endl;
    
    /*****************  增量扰动模型的更新   *********************/
    Vector3d update_so3(1e-4,0,0);//假设更新量为这么多
    Sophus::SO3d SO3_updated = Sophus::SO3d::exp(update_so3) * SO3_R;
    std::cout << "SO3 updated = \n" << SO3_updated.matrix() << std::endl;


    /********************  SE(3)  ******************/
    Vector3d t(1,0,0);//沿x轴平移1
    Sophus::SE3d SE3_Rt(R,t); // 从R，t构造SE(3)
    Sophus::SE3d SE3_qt(q,t); // 从q，t构造SE(3)
    std::cout << "SE3 from R,t = \n" << SE3_Rt.matrix() << std::endl;
    std::cout << "SE3 from q,t = \n" << SE3_qt.matrix() << std::endl;

    // 李代数se3是一个六维向量
    typedef Eigen::Matrix<double,6,1> Vector6d;
    Vector6d se3 = SE3_Rt.log();
    std::cout << "se = " << se3.transpose() << std::endl;
    // se3的平移在前，旋转在后
    std::cout << "se3 hat = \n" << Sophus::SE3d::hat(se3) << endl;
    std::cout << "se3 hat vee = " << Sophus::SE3d::vee(Sophus::SE3d::hat(se3)).transpose() << endl;

    Vector6d update_se3;//更新量
    update_se3.setZero();
    update_se3(0,0) = 1e-4;
    Sophus::SE3d SE3_updated = Sophus::SE3d::exp(update_se3) * SE3_Rt;
    std::cout << "SE3 updated = " << std::endl << SE3_updated.matrix() << std::endl;

    std::cout << "R: \n" << R << std::endl;
    std::cout << "t: \n" << t << std::endl;



    return 0;
}


