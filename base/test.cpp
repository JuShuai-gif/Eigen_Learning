#include <iostream>
#include <Eigen/Core>

int main(){
    Eigen::Vector3d init_std_pos;
    init_std_pos << 1,2,3;
    // Vector3d不支持 * 运算符
    // std::cout << "vector product: \n" << init_std_pos * init_std_pos << std::endl;

    std::cout << "vector product: \n" << init_std_pos.cwiseProduct(init_std_pos) << std::endl;


    Eigen::Array3d init_std_pos_array;
    init_std_pos_array << 1,2,3;
    std::cout << "array product: \n" << init_std_pos_array * init_std_pos_array << std::endl;
    
    Eigen::Vector3d squared_pos = init_std_pos.cwiseProduct(init_std_pos);
    std::cout << "squared_pos: \n" << squared_pos << std::endl;

    Eigen::Matrix3d diag_mat = squared_pos.asDiagonal();

    std::cout << "diag_mat: \n" << diag_mat << std::endl;

    return 0;
}



