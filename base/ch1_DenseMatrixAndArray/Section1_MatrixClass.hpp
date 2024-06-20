#pragma once
#include "HeaderFile.h"

namespace CH1 {
namespace Section1_MatrixClass {
// Eigen中的Matrix和Vector其实都是Matrix<>模版类实现的，向量是特殊的矩阵，行向量是一行多列，列向量是一列多行

// Matrix<>模板类定义：
// template<typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows,
// int _MaxCols> class Matrix
//    : public PlainObjectBase<Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows,
//    _MaxCols> >

//```固定大小的向量提供了初始化操作
//               Vector2d a(5.0, 6.0);
//               Vector3d b(5.0, 6.0, 7.0);
//               Vector4d c(5.0, 6.0, 7.0, 8.0);

// Row 行  col列
// Eigen不支持初始化列表方式初始化   Matrix<int,2,2> m{2,3,2,1};
// 那为什么 Matrix<int,1,2> m{2,3}; 可以，因为这时候，可以将 m 看做一个向量

// 获取元素：
// 所有元素：m(index)的方式可以获取数据，但是和存储方式有关，
// eigen默认采用column-major storage order, but this can be changed to
// row-major, 注意，存储顺序与逗号初始化是无关系的
// []运算符只能获取**向量元素**，因为C++[]只支持一个参数；

// Eigen 中默认的是列主序的

// Eigen定义一些变量的方式
void CoefficientAccessors()
{
    LOG();

    // 默认的构造函数不执行任何空间分配，也不初始化矩阵的元素
    // a是一个3*3的矩阵，分配了float[9]的空间，但未初始化内部元素
    Matrix3f a;
    // b是一个动态大小的矩阵，定义是未分配空间(0*0)
    MatrixXf b;

    // 指定大小的矩阵，只是分配相应大小的空间，未初始化元素
    MatrixXf aa(10, 15);
    // aa是一个10*15的动态大小的矩阵，分配了空间但未初始化元素
    VectorXf bb(30);
    // bb是一个30大小的向量，同样分配空间未初始化元素

    // 为了对固定大小和动态大小的矩阵提供统一的API，对指定大小的Matrix传递sizes也是合法的
    Matrix3f aaa(3, 3);
    // Matrix3f aaa(3,4); //
    // 对于已经固定大小的矩阵，尽管可以给它赋值改变大小，但是这是违法的

    // 模版初始化
    Matrix<int, 1, 2> m{2, 3};
    std::cout << m << std::endl;

    Matrix<double, 2, 2> m_2_2;
    // 等同于 MatrixXd m_2_2(2,2);
    m_2_2 << 1, 2, 3, 4;
    m_2_2(0, 0) = 5;
    m_2_2(0, 1) = 6;
    m_2_2(1, 0) = 7;
    m_2_2(1, 1) = m_2_2(0, 0) + m_2_2(0, 1);
    std::cout << m_2_2 << std::endl;

    // 从下面可以得出是列主序的
    std::cout << "m_2_2(1)  " << m_2_2(1) << std::endl;
    std::cout << "m_2_2(2)  " << m_2_2(2) << std::endl;

    // 使用事先定义好的别名定义和初始化
    // Rows 行        Cols列
    // 列向量
    // typedef Matrix<float, 3, 1> Vector3f;
    // 行向量
    // typedef Matrix<int, 1, 2> RowVector2i;

    Vector2d v_2(1, 2);
    Vector3d v_3(1, 2, 3);
    Vector4d v_4(1, 2, 3, 4);
    // 上面这种定义类似于 Vector<double,4> v_v;
    // 如果没有赋值就使用的话，会造成随机值错误，另外
    // 如果定义四维向量，那么四个维度都要赋值

    // 为什么输出都是列向量，因为线性代数是列向量，也为了和其它库匹配
    std::cout << v_2 << std::endl;
    std::cout << v_3 << std::endl;
    std::cout << v_4 << std::endl;

    Vector<double, 4> v_v(111, 2, 3, 4);
    std::cout << v_v << std::endl;

    // 行向量
    RowVectorXd vec1(3);
    vec1 << 1, 2, 3;
    std::cout << "vec1 = " << vec1 << std::endl;

    RowVectorXd vec2(4);
    vec2 << 1, 4, 9, 16;
    std::cout << "vec2 = " << vec2 << std::endl;

    RowVectorXd joined(7);
    joined << vec1, vec2;
    std::cout << "joined = " << joined << std::endl;

    // 不定长的向量不能使用初始化列表，下面这个是错误的
    // RowVectorXd vec11{1,5,9};// 错误
    // std::cout << "vec11 = " << vec11 << std::endl;
}

void CommaInitialization()
{
    // 单行向量
    Matrix<int, 1, 2> m{2, 3};
    std::cout << m << std::endl;

    // 2*2矩阵
    Matrix<double, 2, 2> m_2_2;
    // 等同于 MatrixXd m_2_2(2,2);
    m_2_2 << 1, 2, 3, 4;

    MatrixXf matA(2, 2);
    matA << 1, 2, 3, 4;
    MatrixXf matB(4, 4);
    matB << matA, matA / 100, matA / 10, matA;
    matB << 255, 255, 255, 3000, 255, 255, 255, 3000, 255, 255, 255, 3000, 255,
        255, 255, 3000;
    // 从输出结果可以看出，使用 << 进行赋值时，是行排序进行赋值
    std::cout << matB << std::endl;

    // 默认情况
    Matrix<int, 3, 4, ColMajor> Adefaultmajor;
    Adefaultmajor << 8, 2, 2, 9, 9, 1, 4, 4, 3, 5, 4, 5;

    cout << "默认情况:" << endl;
    cout << Adefaultmajor << endl << endl;
    // https://blog.csdn.net/juluwangriyue/article/details/122274335
    // 默认列主序
    cout << "In memory (column-major):" << endl;
    for (int i = 0; i < Adefaultmajor.size(); i++)
        cout << *(Adefaultmajor.data() + i) << "  ";
    cout << endl << endl;

    // 列主序
    Matrix<int, 3, 4, ColMajor> Acolmajor;
    Acolmajor << 8, 2, 2, 9, 9, 1, 4, 4, 3, 5, 4, 5;
    cout << "The matrix A:" << endl;
    cout << Acolmajor << endl << endl;

    cout << "In memory (column-major):" << endl;
    for (int i = 0; i < Acolmajor.size(); i++)
        cout << *(Acolmajor.data() + i) << "  ";
    cout << endl << endl;

    // 指定行主序存储
    Matrix<int, 3, 4, RowMajor> Arowmajor = Acolmajor;
    cout << "In memory (row-major):" << endl;
    for (int i = 0; i < Arowmajor.size(); i++)
        cout << *(Arowmajor.data() + i) << "  ";
    cout << endl;

    // 下面有一点是比较困惑的
    // 在使用这种方式存数据时，是按照行的方式进行存储的 A << 1, 2, 3, 4, 5, 6,
    // 7, 8, 9; 但实际在内存中是以列的顺序存储的
    double arr[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    MatrixXd A(3, 3);
    A << 1, 2, 3, 4, 5, 6, 7, 8, 9;
    // A.transpose();
    cout << "In memory (row-major): \n" << A << endl;
    for (int i = 0; i < A.size(); i++) cout << *(A.data() + i) << "  ";
    cout << endl;

    // 转置之后，看起来就和arr数组一样了
    MatrixXd B = A.transpose();
    cout << "\nIn memory (row-major transpose): \n" << B << endl;
    for (int i = 0; i < B.size(); i++) cout << *(B.data() + i) << "  ";
    cout << endl;
}

void Resizing()
{
    LOG();
    // 矩阵的当前大小可以通过rows()，cols()和size()获取。
    // 这些方法分别返回行数，列数和系数数。调整动态大小矩阵的大小是通过resize()方法完成的。
    // 如果实际矩阵大小不变，则resize()方法为空操作。
    // 否则具有破坏性：系数的值可能会更改。如果你想调整大小()，它不改变系数，使用conservativeResize()

    // Eigen不只限于已知大小（编译阶段）的矩阵，有些矩阵的尺寸是运行时确定的，于是引入了一个特殊的标识符：Dynamic
    typedef Matrix<double, Dynamic, Dynamic> MatrixXd;
    typedef Matrix<int, Dynamic, 1> VectorXi;
    Matrix<float, 3, Dynamic> Matrix3;
    Matrix3.resize(3, 3);
    Matrix3 << 1, 2, 3, 4, 5, 6, 7, 8, 9;
    // 打印 Matrix3
    std::cout << "Matrix3:\n" << Matrix3 << std::endl;

    MatrixXd m(2, 5);
    m.resize(4, 3);
    std::cout << "The matrix m is of size " << m.rows() << "x" << m.cols()
              << std::endl;
    std::cout << "It has " << m.size() << " coefficients" << std::endl;

    VectorXd v(2);
    v.resize(5);
    std::cout << "The vector v is of size " << v.size() << std::endl;
    std::cout << "As a matrix, v is of size " << v.rows() << "x" << v.cols()
              << std::endl;
    {
        //为了实现API统一性，所有这些方法仍可用于固定大小的矩阵。当然，您实际上不能调整固定大小的矩阵的大小。尝试将固定大小更改为实际不同的值将触发断言失败。
        //但是以下代码是合法的：
        Matrix4d m;
        m.resize(
            4,
            4); // 确定的大小是不可以更改大小的，虽然在编译器语法不会出错，但是在编译时会报错
        std::cout << "The matrix m is of size " << m.rows() << "x" << m.cols()
                  << std::endl;

        // https://blog.csdn.net/u013673826/article/details/94395412
        int rows{5}, cols{6};
        Eigen::MatrixXf tmp_mat;
        // tmp_mat=Eigen::Matrix<float,Dynamic,Dynamic>();
        // 因为Eigen<type,int,int>的template参数必须在编译的时候知道这个值，而不是运行时，因此只能赋constexp
        tmp_mat.resize(rows, cols);
        std::cout << "It has " << tmp_mat.size() << " coefficients"
                  << std::endl;
    }

    MatrixXf aa(2, 2);
    std::cout << "aa is of size " << aa.rows() << "x" << aa.cols() << std::endl;
    MatrixXf bb(3, 3);
    aa = bb;
    std::cout << "aa is of size " << aa.rows() << "x" << aa.cols() << std::endl;
    // 如果是固定大小就不能将动态大小的的矩阵赋值，下面会报错
    // Matrix2f aaa;
    // aaa =bb;

    // Matrix4f mymatrix; 等价于 float mymatrix[16];
    // MatrixXf mymatrix(rows,columns); 等价于 float *mymatrix = new
    // float[rows*columns];
    // 使用固定尺寸(<=4*4)需要编译前知道矩阵大小，而且对于足够大的尺寸，如大于32，
    // 固定尺寸的收益可以忽略不计，而且可能导致栈崩溃。而且基于环境，Eigen会对动态尺寸做优化（类似于std::vector）
}

void MatrixAndVectorCompileTime()
{
    LOG();
    // 固定大小的矩阵or向量在栈上分配内存，因为它在编译时期就可以确定大小
    // Matrix4f mymatrix  ≈  float mymatrix[16];
    // MatrixX表示运行时才确定矩阵的大小，因为它在堆上分配内存
    // MatrixXf mymatrix(rows,columns) ≈  float *mymatrix = new
    // float[rows*columns];
    MatrixXd m = MatrixXd::Random(3, 3); //  random values between -1 and 1
    m = (m + MatrixXd::Constant(3, 3, 1.2)) *
        50; // MatrixXd::Constant(3, 3, 1.2) represents a 3-by-3 matrix
            // expression having all coefficients equal to 1.2
    cout << "m =" << endl << m << endl;
    VectorXd v(3); // 尚未初始化
    v << 1, 2, 3;  //  uses the so-called comma-initializer
    cout << "m * v =" << endl << m * v << endl;

    // 块区域进行赋值
    Matrix3f mmm;
    mmm.row(0) << 1, 2, 3;               // 表示第一行
    mmm.block(1, 0, 2, 2) << 4, 5, 7, 8; // 表示起始是(1,0)  尺寸是2*2
    mmm.col(2).tail(2) << 6, 9;
    std::cout << mmm << std::endl;
}

void ArrayAndMatrix()
{
    LOG();
    // 第一种是没有参数，只能创建固定大小的对象
    std::cout << "A fixed-size array:\n";
    Array33f a1 = Array33f::Zero();
    std::cout << a1 << "\n\n";
    // 第二种是第一个参数，用来构造一维动态大小的对象
    std::cout << "A one-dimensional dynamic-size array:\n";
    ArrayXf a2 = ArrayXf::Zero(3);
    std::cout << a2 << "\n\n";
    // 第三种的带两个参数，用于构造二维对象
    std::cout << "A two-dimensional dynamic-size array:\n";
    ArrayXXf a3 = ArrayXXf::Zero(3, 4);
    std::cout << a3 << "\n";

    // 官方提供一些 typedef 供用户使用
    Array<float, Dynamic, 1> ArrayXf;
    Array<float, 3, 1> Array3f;
    Array<double, Dynamic, Dynamic> ArrayXXd;
    Array<double, 3, 3> Array33d;

    ArrayXXf m(2, 2);

    // assign some values coefficient by coefficient
    m(0, 0) = 1.0;
    m(0, 1) = 2.0;
    m(1, 0) = 3.0;
    m(1, 1) = m(0, 1) + m(1, 0);

    // print values to standard output
    cout << m << endl << endl;

    // using the comma-initializer is also allowed
    m << 1.0, 2.0, 3.0, 4.0;

    // print values to standard output
    cout << m << endl;

    ArrayXXf a(3, 3);
    ArrayXXf b(3, 3);
    a << 1, 2, 3, 4, 5, 6, 7, 8, 9;
    b << 1, 2, 3, 1, 2, 3, 1, 2, 3;

    // Adding two arrays
    cout << "a + b = " << endl << a + b << endl << endl;

    // 每个元素相加减
    cout << "a - 2 = " << endl << a - 2 << endl;
    cout << "a + 2 = " << endl << a + 2 << endl;

    MatrixXd aa(3, 3);
    MatrixXd bb(3, 3);

    aa << 1, 2, 3, 4, 5, 6, 7, 8, 9;
    bb << 1, 2, 3, 1, 2, 3, 1, 2, 3;

    cout << "aa + bb = " << endl << aa + bb << endl << endl;

    // 矩阵不支持 矩阵和标量操作
    // 加减不支持
    // cout << "aa - 2 = " << endl << aa + 2 << endl;
    // cout << "aa - 2 = " << endl << aa - 2 << endl;
    // 乘除支持
    cout << "aa - 2 = " << endl << aa * 2 << endl;
    cout << "aa - 2 = " << endl << aa / 2 << endl;

    /****** 乘法比较 *****/
    // array乘法是每个元素对应相乘
    ArrayXXf array_a(2, 2);
    ArrayXXf array_b(2, 2);
    array_a << 1, 2, 3, 4;
    array_b << 5, 6, 7, 8;
    cout << "array_a * array_b = " << endl << array_a * array_b << endl;

    // 矩阵相乘，是按照矩阵乘法规则进行相乘
    MatrixXd mat_a(2, 2);
    MatrixXd mat_b(2, 2);
    mat_a << 1, 2, 3, 4;
    mat_b << 5, 6, 7, 8;
    cout << "mat_a * mat_b = " << endl << mat_a * mat_b << endl;

    Eigen::ArrayXf array = Eigen::ArrayXf::Random(5);
    std::cout << "Random array:\n" << array << std::endl;
}

void FixedSizeAndDynamicSize()
{
    LOG();
    //固定尺寸与动态尺寸
    // 什么时候应该使用固定尺寸（例如Matrix4f），什么时候应该使用动态尺寸（例如MatrixXf）？
    //简单的答案是：在可能的地方使用固定尺寸来显示非常小的尺寸，在需要的地方使用动态尺寸来显示较大的尺寸。
    //对于小尺寸，尤其是对于小于（大约）16的尺寸，使用固定尺寸对性能有极大的好处，因为它使Eigen避免了动态内存分配并展开了循环。
    //在内部，固定大小的本征矩阵只是一个简单的数组，即
    // Matrix4f mymatrix;
    // 真的等于只是在做
    // float[16];
    // 因此这确实具有零运行时间成本。相比之下，动态大小矩阵的数组始终分配在堆上，因此

    // MatrixXf mymatrix（行，列）;
    // 等于做
    // float * mymatrix = new [行*列];
    // 除此之外，MatrixXf对象还将其行数和列数存储为成员变量。
    // 当然，使用固定大小的限制是，只有当您在编译时知道大小时，才有可能这样做。
    //同样，对于足够大的尺寸（例如，对于大于（大约）32的尺寸），使用固定尺寸的性能优势变得可以忽略不计。
    //更糟糕的是，尝试使用函数内部的固定大小创建非常大的矩阵可能会导致堆栈溢出，因为Eigen会尝试自动将数组分配为局部变量，而这通常是在堆栈上完成的。
    //最后，视情况而定，当使用动态尺寸时，Eigen还可尝试进行矢量化（使用SIMD指令），请参见参考矢量化。
}

void OptionalTemplateParameters()
{
    LOG();
    // 可选模板参数
    // 我们在页面开始时提到Matrix类采用六个模板参数，但到目前为止，我们仅讨论了前三个。其余三个参数是可选的。这是模板参数的完整列表：

    //       Matrix<typename Scalar,
    //        int RowsAtCompileTime,
    //        int ColsAtCompileTime,
    //        int Options = 0,
    //        int MaxRowsAtCompileTime = RowsAtCompileTime,
    //        int MaxColsAtCompileTime = ColsAtCompileTime>

    // Options是位字段。在这里，我们只讨论一点：RowMajor。它指定这种类型的矩阵使用行优先存储顺序。默认情况下，存储顺序为“按列的顺序存储”。
    //请参阅有关存储顺序的页面。例如，此类型表示行优先存储的3x3矩阵：
    // Matrix<float，3、3，RowMajor>
    // MaxRowsAtCompileTime并且MaxColsAtCompileTime在您希望指定时很有用，即使在编译时不知道矩阵的确切大小，在编译时也知道固定的上限。
    //您可能要这样做的最大原因是避免动态内存分配。例如，以下矩阵类型使用12个浮点数的普通数组，而不分配动态内存：
    // Matrix<float，Dynamic，Dynamic，0、3、4>
}

void ConvenienceTypedefs()
{
    LOG();
    // Eigen定义了以下Matrix typedef：

    // MatrixNt for Matrix<type, N, N>. For example, MatrixXi for Matrix<int,
    // Dynamic, Dynamic>. VectorNt for Matrix<type, N, 1>. For example, Vector2f
    // for Matrix<float, 2, 1>. RowVectorNt for Matrix<type, 1, N>. For example,
    // RowVector3d for Matrix<double, 1, 3>. Where:
    // N可以是任何一个2，3，4，或X（意思Dynamic）。
    // t可以是i（表示int），f（表示float），d（表示double），cf（表示complex
    // <float>）或cd（表示complex <double>）的任何一种。
    //仅针对这五个类型定义typedef的事实并不意味着它们是唯一受支持的标量类型。例如，支持所有标准整数类型，请参阅标量类型。
}

} // namespace Section1_MatrixClass
} // namespace CH1
