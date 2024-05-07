#include "SpanningTrees.h"

Matrix InitializeMatrixByZero(int matrixSize)
{
	Matrix matrix(matrixSize, std::vector<int>(matrixSize, 0));
	return matrix;
}

void PrintMatrix(const Matrix& matrix)
{
	for (const auto& row : matrix)
	{
		for (int val : row)
		{
			std::cout << std::setw(3) << val << " ";
		}
		std::cout << std::endl;
	}
}

Matrix BuildKirchhoffMatrixByAdjacencyMatrix(const Matrix& adjacencyMatrix)
{
	int matrixSize = adjacencyMatrix.size();
	Matrix kirchhoffMatrix = InitializeMatrixByZero(matrixSize);

	for (int i = 0; i < matrixSize; i++)
	{
		int degree = 0;
		for (int j = 0; j < matrixSize; j++)
		{
			if (i != j)
			{
				kirchhoffMatrix[i][j] = -adjacencyMatrix[i][j];
				degree += adjacencyMatrix[i][j];
			}
		}
		kirchhoffMatrix[i][i] = degree;
	}

	return kirchhoffMatrix;
}

Matrix CreateMinorMatrix(const Matrix& matrix, int i)
{
	int matrixSize = matrix.size();
	Matrix minorMatrix = InitializeMatrixByZero(matrixSize - 1);

	for (int j = 0, row = 0; j < matrixSize; j++)
	{
		if (j == i)
			continue;
		for (int k = 0, col = 0; k < matrixSize; k++)
		{
			if (k == i)
				continue;
			minorMatrix[row][col] = matrix[j][k];
			col++;
		}
		row++;
	}

	return minorMatrix;
}

int GetMatrixDet(Matrix& matrix)
{
	int n = matrix.size();
	int det = 1;

	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			while (matrix[j][i] != 0)
			{
				int t = matrix[i][i] / matrix[j][i];
				for (int k = i; k < n; k++)
				{
					matrix[i][k] -= t * matrix[j][k];
				}
				for (int k = i; k < n; k++)
				{
					std::swap(matrix[i][k], matrix[j][k]);
				}
				det = -det;
			}
		}
		det *= matrix[i][i];
	}

	return det;
}

int CountSpanningTreesByKirchhoffMatrix(const Matrix& kirchhoffMatrix)
{
	int matrixSize = kirchhoffMatrix.size();
	int totalSpanningTrees = 0;

	for (int i = 0; i < matrixSize; i++)
	{
		Matrix minor = CreateMinorMatrix(kirchhoffMatrix, i);
		totalSpanningTrees += GetMatrixDet(minor);
	}

	return totalSpanningTrees / matrixSize;
}

bool AreMatricesEqual(const Matrix& matrix1, const Matrix& matrix2)
{
	if (matrix1.size() != matrix2.size() || matrix1[0].size() != matrix2[0].size())
	{
		return false;
	}

	for (size_t i = 0; i < matrix1.size(); i++)
	{
		for (size_t j = 0; j < matrix1[0].size(); j++)
		{
			if (matrix1[i][j] != matrix2[i][j])
			{
				return false;
			}
		}
	}

	return true;
}