#include <iostream>
#include <cmath>
#include <ctime>
#include <algorithm>

using namespace std;

// Function to generate a positive definite matrix
void generate_spd_matrix(float **matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = rand() % 10 + 1;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] += matrix[j][i];
            matrix[j][i] = matrix[i][j];
        }
    }
}

// Cholesky decomposition
void cholesky_decomposition(float **A, int n)
{
    float **L = new float *[n];
    for (int i = 0; i < n; i++)
        L[i] = new float[n];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            float sum = 0;
            if (j == i)
            {
                for (int k = 0; k < j; k++)
                    sum += pow(L[j][k], 2);
                L[j][j] = sqrt(A[j][j] - sum);
            }
            else
            {
                for (int k = 0; k < j; k++)
                    sum += (L[i][k] * L[j][k]);
                L[i][j] = (A[i][j] - sum) / L[j][j];
            }
        }
    }

    for (int i = 0; i < n; i++)
        delete[] L[i];
    delete[] L;
}

// LU decomposition
void lu_decomposition(float **A, int n)
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
                sum += (L[i][j] * U[j][k]);
            U[i][k] = A[i][k] - sum;
        }

        for (int k = i; k < n; k++)
        {
            if (i == k)
                L[i][i] = 1;
            else
            {
                float sum = 0;
                for (int j = 0; j < i; j++)
                    sum += (L[k][j] * U[j][i]);
                L[k][i] = (A[k][i] - sum) / U[i][i];
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        delete[] L[i];
        delete[] U[i];
    }
    delete[] L;
    delete[] U;
}

// QR decomposition
void qr_decomposition(float **A, int n)
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
            norm += A[j][i] * A[j][i];
        norm = sqrt(norm);
        R[i][i] = norm;

        for (int j = 0; j < n; j++)
            Q[j][i] = A[j][i] / norm;

        for (int j = i + 1; j < n; j++)
        {
            float dot = 0;
            for (int k = 0; k < n; k++)
                dot += Q[k][i] * A[k][j];
            R[i][j] = dot;

            for (int k = 0; k < n; k++)
                A[k][j] -= Q[k][i] * dot;
        }
    }

    for (int i = 0; i < n; i++)
    {
        delete[] Q[i];
        delete[] R[i];
    }
    delete[] Q;
    delete[] R;
}

int main()
{
    srand(time(0));
    int n, iterations;
    cout << "Enter the size of the matrix : ";
    cin >> n;
    cout << "Enter no of iterations : ";
    cin >> iterations;

    float **matrix = new float *[n];
    for (int i = 0; i < n; i++)
        matrix[i] = new float[n];

    generate_spd_matrix(matrix, n);

    clock_t start, end;
    double cpu_time_used;
    double times[3];

    start = clock();
    for (int i = 0; i < iterations; i++)
        cholesky_decomposition(matrix, n);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    times[0] = cpu_time_used / iterations;

    start = clock();
    for (int i = 0; i < iterations; i++)
        qr_decomposition(matrix, n);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    times[1] = cpu_time_used / iterations;

    start = clock();
    for (int i = 0; i < iterations; i++)
        lu_decomposition(matrix, n);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    times[2] = cpu_time_used / iterations;

    double min_time = min(times[0], min(times[1], times[2]));
    double ratios[3] = {times[0] / min_time, times[1] / min_time, times[2] / min_time};
    int rounded_ratios[3];
    for (int i = 0; i < 3; i++)
    {
        rounded_ratios[i] = static_cast<int>(round(ratios[i]));
    }
    cout << "Average time taken for Cholesky Decomposition: " << times[0] << endl;
    cout << "Average time taken for QR Decomposition: " << times[1] << endl;
    cout << "Average time taken for LU Decomposition: " << times[2] << endl;
    cout << "Ratios of -> Cholesky : QR : LU : " << rounded_ratios[0] << " : " << rounded_ratios[1] << " : " << rounded_ratios[2] << endl;

    for (int i = 0; i < n; i++)
        delete[] matrix[i];
    delete[] matrix;

    return 0;
}
