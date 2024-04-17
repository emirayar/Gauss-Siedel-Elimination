// Numeric Analysis Assignment 1
// Solution of linear equation system with Gauss-Seidel Method.
// Name: Emir Ayar
// Number: 200030473
// Educating: Mechatronics Engineering
// Date: 14.04.2024

#include <stdio.h>
#include <math.h>

#define MAX_SIZE 50   // Maximum number of equations
#define MAX_ITER 1000 // Maximum number of iterations

// Function to swap two floating point numbers
void swap(float *x, float *y) {
    float temp = *x;
    *x = *y;
    *y = temp;
}

// Function to print a matrix
void printMatrix(float matrix[MAX_SIZE][MAX_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%.2f ", matrix[i][j]); // Print each element of the matrix with 2 decimal places
        }
        printf("\n"); // Move to the next row after printing all elements of a row
    }
}

// Function to print a vector
void printVector(float vector[MAX_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        printf("%.12f ", vector[i]); // Print each element of the vector with 12 decimal places
    }
    printf("\n"); // Move to the next line after printing all elements of the vector
}

int main() {
    int equation_count; // Number of equations in the linear system
    printf("Enter the number of equations: ");
    scanf("%d", &equation_count);

    float coefficient_matrix[MAX_SIZE][MAX_SIZE]; // Coefficient matrix of the linear system
    float result_vector[MAX_SIZE]; // Result vector of the linear system
    float variable_vector[MAX_SIZE]; // Initial guess for the solution vector
    float temp_variable_vector[MAX_SIZE]; // Temporary vector to hold updated solution values
    float error; // Error value to check convergence

    // Prompt the user to enter the coefficients of equations and the results
    printf("Enter coefficients of equations and results:\n");
    for (int i = 0; i < equation_count; i++) {
        // Prompt the user to enter the coefficients of the current equation
        printf("Enter coefficients of equation %d:\n", i + 1);
        for (int j = 0; j < equation_count; j++) {
            scanf("%f", &coefficient_matrix[i][j]); // Read the coefficient from the user
        }
        // Prompt the user to enter the result of the current equation
        printf("Enter the result of equation %d: ", i + 1);
        scanf("%f", &result_vector[i]); // Read the result from the user
    }

    // Rearrange the coefficient matrix and result vector to improve convergence
    for (int i = 0; i < equation_count; i++) {
        int max_index = i;
        for (int j = i + 1; j < equation_count; j++) {
            // Find the row with the largest absolute value in the current column
            if (fabs(coefficient_matrix[j][i]) > fabs(coefficient_matrix[max_index][i])) {
                max_index = j;
            }
        }
        // Swap the rows to make the largest absolute value the diagonal element
        if (max_index != i) {
            for (int k = 0; k < equation_count; k++) {
                swap(&coefficient_matrix[i][k], &coefficient_matrix[max_index][k]);
            }
            swap(&result_vector[i], &result_vector[max_index]);
        }
    }

    // Print the rearranged coefficient matrix
    printf("Matrix after rearrangement:\n");
    printMatrix(coefficient_matrix, equation_count);

    // Prompt the user to enter the initial values of variables
    printf("Enter the initial values of variables:\n");
    for (int i = 0; i < equation_count; i++) {
        scanf("%f", &variable_vector[i]); // Read the initial value of each variable from the user
    }

    // Perform Gauss-Seidel iterations to solve the linear system
    for (int iter = 1; iter <= MAX_ITER; iter++) {
        error = 0.0; // Initialize the error to zero
        for (int i = 0; i < equation_count; i++) {
            temp_variable_vector[i] = result_vector[i]; // Initialize the temporary vector with result values
            for (int j = 0; j < equation_count; j++) {
                if (j != i) {
                    // Subtract the product of coefficient and variable from the result
                    temp_variable_vector[i] -= coefficient_matrix[i][j] * temp_variable_vector[j];
                }
            }
            // Divide the updated result by the diagonal coefficient
            temp_variable_vector[i] /= coefficient_matrix[i][i];
            // Update the error with the maximum difference between old and new variable values
            error = fmax(error, fabs(temp_variable_vector[i] - variable_vector[i]));
            // Update the variable value with the new value
            variable_vector[i] = temp_variable_vector[i];
        }
        // Print the current iteration number
        printf("Iteration %d\n", iter);
        // Print the current variable values
        printVector(variable_vector, equation_count);
        // Print the current error value
        printf("Error: %.12f\n", error);
        // Check if the error is below the tolerance level and break the loop if true
        if (error < 0.01) {
            break;
        }
    }

    // Print the final solution vector
    printf("Solution:\n");
    printVector(variable_vector, equation_count);

    return 0;
}
