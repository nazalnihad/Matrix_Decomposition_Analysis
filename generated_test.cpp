#include <iostream>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void generate_spd_matrix(float **matrix, int n, const string filename)
{
    // Open the CSV file
    ifstream file(filename);
    string line;

    // Read the file line by line
    for (int i = 0; i < n && getline(file, line); i++)
    {
        stringstream ss(line);
        string item;

        // Parse each value and store it in the matrix
        for (int j = 0; j < n && getline(ss, item, ','); j++)
        {
            matrix[i][j] = stof(item);
        }
    }
    // Close the file
    file.close();
}

int main()
{
    // Define the size of the matrix
    int n = 10;

    // Allocate memory for the matrix
    float **matrix = new float *[n];
    for (int i = 0; i < n; i++)
        matrix[i] = new float[n];

    // Specify the filename
    char *filename = "spd_matrix.csv";

    // Generate the symmetric positive definite matrix
    generate_spd_matrix(matrix, n, filename);

    // Print the matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    // Free the allocated memory
    for (int i = 0; i < n; i++)
        delete[] matrix[i];
    delete[] matrix;

    return 0;
}
