#include <iostream>
#include <cmath>
using namespace std;

float **cholesky_decomposition(float **A, int n)
{
    float **L = new float *[n];
    for (int i = 0; i < n; i++)
    {
        L[i] = new float[n];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            float sum = 0;
            if (j == i)
            {
                for (int k = 0; k < j; k++)
                {
                    sum += pow(L[j][k], 2);
                }
                L[j][j] = sqrt(A[j][j] - sum);
            }
            else
            {
                for (int k = 0; k < j; k++)
                {
                    sum += (L[i][k] * L[j][k]);
                }
                L[i][j] = (A[i][j] - sum) / L[j][j];
            }
        }
    }

    return L; // Return the calculated L matrix
}

int main()
{
    int n = 3; // Size of the matrix
    float **A = new float *[n];
    for (int i = 0; i < n; i++)
    {
        A[i] = new float[n];
    }

    // Sample input matrix (symmetric and positive definite)
    A[0][0] = 4;
    A[0][1] = 12;
    A[0][2] = -16;
    A[1][0] = 12;
    A[1][1] = 37;
    A[1][2] = -43;
    A[2][0] = -16;
    A[2][1] = -43;
    A[2][2] = 98;

    float **L = cholesky_decomposition(A, n);

    // Print the resulting lower triangular matrix L
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            std::cout << L[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // Free memory
    for (int i = 0; i < n; i++)
    {
        delete[] A[i];
    }
    delete[] A;

    return 0;
}