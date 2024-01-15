import random
import numpy as np
import csv


def generate_spd_matrix(n):
    # Create a random matrix
    A = np.random.randint(0, 10, size=(n, n))
    # make it symmetric
    symmetric_matrix = (A + A.T) // 2
    # make it positive definite
    spd_matrix = symmetric_matrix @ symmetric_matrix.T

    return spd_matrix


n = int(input("Enter matrix size : "))  # Size of the matrix
spd_matrix = generate_spd_matrix(n)

# Save the matrix to a CSV file
with open('spd_matrix.csv', 'w', newline='') as csvfile:
    writer = csv.writer(csvfile)
    for row in spd_matrix:
        writer.writerow(row)
