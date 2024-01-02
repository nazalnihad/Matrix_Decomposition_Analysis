#include <iostream>
#include <cmath>

float **qr_decomposition(float **A, int n)
{
    float **Q = new float *[n];
    float **R = new float *[n];
    for (int i = 0; i < n; i++)
    {
        Q[i] = new float[n];
        R[i] = new float[n];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            Q[i][j] = 0;
            R[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++)
    {
        float norm = 0;
        for (int j = 0; j < n; j++)
        {
            norm += A[j][i] * A[j][i];
        }
        norm = sqrt(norm);
        R[i][i] = norm;

        for (int j = 0; j < n; j++)
        {
            Q[j][i] = A[j][i] / norm;
        }

        for (int j = i + 1; j < n; j++)
        {
            float dot = 0;
            for (int k = 0; k < n; k++)
            {
                dot += Q[k][i] * A[k][j];
            }
            R[i][j] = dot;

            for (int k = 0; k < n; k++)
            {
                A[k][j] -= Q[k][i] * dot;
            }
        }
    }

    // Combine Q and R into a single 2D array to return
    float **QR = new float *[2 * n];
    for (int i = 0; i < 2 * n; i++)
    {
        QR[i] = new float[n];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            QR[i][j] = Q[i][j];
            QR[i + n][j] = R[i][j];
        }
    }

    for (int i = 0; i < n; i++)
    {
        delete[] Q[i];
        delete[] R[i];
    }
    delete[] Q;
    delete[] R;

    return QR;
}

int main()
{
    int n = 3;
    float **A = new float *[n];
    for (int i = 0; i < n; i++)
    {
        A[i] = new float[n];
    }

    // Sample input matrix
    A[0][0] = 1.4;
    A[0][1] = 1.7;
    A[0][2] = 2.9;
    A[1][0] = 0.7;
    A[1][1] = 1;
    A[1][2] = 3;
    A[2][0] = 1.8;
    A[2][1] = 4.3;
    A[2][2] = 2;

    float **QR = qr_decomposition(A, n);

    // Print the resulting Q and R matrices
    std::cout << "Q:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << QR[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "\nR:\n";
    for (int i = n; i < 2 * n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << QR[i][j] << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < 2 * n; i++)
    {
        delete[] QR[i];
    }
    delete[] QR;


    for (int i = 0; i < n; i++)
    {
        delete[] A[i];
    }
    delete[] A;

    return 0;
}
