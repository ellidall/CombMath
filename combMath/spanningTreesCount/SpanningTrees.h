#pragma once

#include <iostream>
#include <vector>
#include <iomanip>

using Matrix = std::vector<std::vector<int>>;

Matrix InitializeMatrixByZero(int matrixSize);

void PrintMatrix(const Matrix& matrix);

Matrix BuildKirchhoffMatrixByAdjacencyMatrix(const Matrix& adjacencyMatrix);

Matrix CreateMinorMatrix(const Matrix& matrix, int i);

int GetMatrixDet(Matrix& matrix);

int CountSpanningTreesByKirchhoffMatrix(const Matrix& kirchhoffMatrix);

bool AreMatricesEqual(const Matrix& matrix1, const Matrix& matrix2);