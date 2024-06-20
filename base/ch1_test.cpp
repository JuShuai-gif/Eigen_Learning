#include "ch1_DenseMatrixAndArray/Section1_MatrixClass.hpp"
#include "ch1_DenseMatrixAndArray/Section2_MatrixAndVectorArithmetic.hpp"
#include "ch1_DenseMatrixAndArray/Section3_ArrayAndCoefficientwiseOperations.hpp"

void PrintMsg(int i)
{
    cout << endl
         << "*******  Results   of   Chapter1   Section" << i << "  ********"
         << endl;
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

void TestChapter1Section2()
{
    PrintMsg(2);
    CH1::Section2_MatrixAndVectorArithmetic::AdditionAndSubtraction();
    CH1::Section2_MatrixAndVectorArithmetic::ScalarMultiplicationAndDivision();
    CH1::Section2_MatrixAndVectorArithmetic::TranspositionAndConjugation();
    CH1::Section2_MatrixAndVectorArithmetic::MatrixMatrixAndMatrixVectorMultiplication();
    CH1::Section2_MatrixAndVectorArithmetic::DotProductAndCrossProduct();
    CH1::Section2_MatrixAndVectorArithmetic::BasicArithmeticReductionOperations();
    CH1::Section2_MatrixAndVectorArithmetic::ValidityOfoperations();
}

void TestChapter1Section3()
{
    PrintMsg(3);
    CH1::Section3_ArrayAndCoefficientwiseOperations::AccessingValuesInsideAnArray();
    CH1::Section3_ArrayAndCoefficientwiseOperations::AdditionAndSubtraction();
    CH1::Section3_ArrayAndCoefficientwiseOperations::ArrayMultiplication();
    CH1::Section3_ArrayAndCoefficientwiseOperations::ConvertingBetweenArrayAndMatrixExpressions();
    CH1::Section3_ArrayAndCoefficientwiseOperations::OtherCoefficientwiseOperations();
}


int main()
{
    // build pass
    // TestChapter1Section1();
    TestChapter1Section3();

    return 0;
}