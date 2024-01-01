#include <iostream>

float **lu_decomposition(float **A, int n)
{
    float **L = new float *[n];
    float **U = new float *[n];
    for (int i = 0; i < n; i++)
    {
        L[i] = new float[n];
        U[i] = new float[n];
    }

    for (int i = 0; i < n; i++)
    {
        for (int k = i; k < n; k++)
        {
            float sum = 0;
            for (int j = 0; j < i; j++)
            {
                sum += (L[i][j] * U[j][k]);
            }
            U[i][k] = A[i][k] - sum;
        }

        for (int k = i; k < n; k++)
        {
            if (i == k)
            {
                L[i][i] = 1;
            }
            else
            {
                float sum = 0;
                for (int j = 0; j < i; j++)
                {
                    sum += (L[k][j] * U[j][i]);
                }
                L[k][i] = (A[k][i] - sum) / U[i][i];
            }
        }
    }

    // Combine L and U into a single 2D array to return
    float **LU = new float *[2 * n];
    for (int i = 0; i < 2 * n; i++)
    {
        LU[i] = new float[n];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            LU[i][j] = L[i][j];
            LU[i + n][j] = U[i][j];
        }
    }

    for (int i = 0; i < n; i++)
    {
        delete[] L[i];
        delete[] U[i];
    }
    delete[] L;
    delete[] U;

    return LU;
}

int main()
{
    int n = 3;
    float **A = new float *[n];
    for (int i = 0; i < n; i++)
    {
        A[i] = new float[n];
    }
    
    A[0][0] = 2;
    A[0][1] = 4;
    A[0][2] = -4;
    A[1][0] = 1;
    A[1][1] = -4;
    A[1][2] = 3;
    A[2][0] = -6;
    A[2][1] = -9;
    A[2][2] = 5;

    float **LU = lu_decomposition(A, n);

    // Print the resulting matrices
    std::cout << "L:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << LU[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "\nU:\n";
    for (int i = n; i < 2 * n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << LU[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
