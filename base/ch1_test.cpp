#include "ch1_DenseMatrixAndArray/Section1_MatrixClass.hpp"


void PrintMsg(int i)
{
        cout << endl
             << "*******  Results   of   Chapter1   Section" << i << "  ********" << endl;
}

void TestChapter1Section1()
{
        PrintMsg(1);
        CH1::Section1_MatrixClass::CoefficientAccessors();
        CH1::Section1_MatrixClass::CommaInitialization();
        CH1::Section1_MatrixClass::Resizing();
        CH1::Section1_MatrixClass::MatrixAndVectorCompileTime();
        CH1::Section1_MatrixClass::ArrayAndMatrix();
}

int main()
{
        // build pass
        TestChapter1Section1();

        

        return 0;
}