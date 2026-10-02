#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <sstream>

using namespace std;

class Matrix
{
private:

    int rows, cols;
    double A[10][10];

public:

    // ==========================================
    // GET DIMENSIONS WITH VALIDATION
    // ==========================================

    void getDimensions()
    {
        while (true)
        {
            cout << "Enter number of rows (1-10): ";
            cin >> rows;

            if (cin.fail() || rows < 1 || rows > 10)
            {
                cin.clear();
                cin.ignore(1000, '\n');

                cout << "Invalid number of rows.\n";
                cout << "Please enter a value between 1 and 10.\n\n";
            }
            else
            {
                break;
            }
        }

        while (true)
        {
            cout << "Enter number of columns (1-10): ";
            cin >> cols;

            if (cin.fail() || cols < 1 || cols > 10)
            {
                cin.clear();
                cin.ignore(1000, '\n');

                cout << "Invalid number of columns.\n";
                cout << "Please enter a value between 1 and 10.\n\n";
            }
            else
            {
                break;
            }
        }
    }


    // ==========================================
    // INPUT MATRIX ELEMENTS WITH VALIDATION
    // ==========================================

    void input()
    {
        cout << "\nEnter matrix elements:\n";

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                while (true)
                {
                    cout << "A[" << i + 1 << "][" << j + 1 << "]: ";
                    cin >> A[i][j];

                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(1000, '\n');

                        cout << "Invalid input.\n";
                        cout << "Please enter a numeric value.\n";
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
    }


    // ==========================================
    // DISPLAY MATRIX
    // ==========================================

    void displayMatrix(string name)
    {
        if (name != "")
        {
            cout << name << " =\n";
        }

        int width[12];

        // Find the required width for each column
        for (int j = 0; j < cols; j++)
        {
            width[j] = 0;

            for (int i = 0; i < rows; i++)
            {
                stringstream ss;
                ss << A[i][j];

                string value = ss.str();

                if (value.length() > width[j])
                {
                    width[j] = value.length();
                }
            }
        }

        // Display Matrix
        for (int i = 0; i < rows; i++)
        {
            cout << "| ";

            for (int j = 0; j < cols; j++)
            {
                stringstream ss;
                ss << A[i][j];

                string value = ss.str();

                cout << setw(width[j]) << value;

                if (j < cols - 1)
                    cout << "   ";
            }

            cout << " |\n";
        }
    }


    // ==========================================
    // GET NUMBER OF ROWS
    // ==========================================

    int getRows()
    {
        return rows;
    }


    // ==========================================
    // GET NUMBER OF COLUMNS
    // ==========================================

    int getCols()
    {
        return cols;
    }


    // ==========================================
    // SET DIMENSIONS
    // Used by the web backend
    // ==========================================

    void setDimensions(int r, int c)
    {
        rows = r;
        cols = c;
    }


    // ==========================================
    // SET MATRIX VALUE
    // Used by the web backend
    // ==========================================

    void setValue(int r, int c, double value)
    {
        A[r][c] = value;
    }


    // ==========================================
    // GET MATRIX VALUE
    // Used by the web backend
    // ==========================================

    double getValue(int r, int c)
    {
        return A[r][c];
    }


    // ==========================================
    // MATRIX ADDITION
    // ==========================================

    Matrix addition(Matrix B)
    {
        Matrix C;

        C.rows = rows;
        C.cols = cols;

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                C.A[i][j] = A[i][j] + B.A[i][j];
            }
        }

        return C;
    }


    // ==========================================
    // MATRIX SUBTRACTION
    // ==========================================

    Matrix subtraction(Matrix B)
    {
        Matrix C;

        C.rows = rows;
        C.cols = cols;

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                C.A[i][j] = A[i][j] - B.A[i][j];
            }
        }

        return C;
    }


    // ==========================================
    // MATRIX MULTIPLICATION
    // ==========================================

    Matrix multiplication(Matrix B)
    {
        Matrix C;

        C.rows = rows;
        C.cols = B.cols;

        for (int i = 0; i < C.rows; i++)
        {
            for (int j = 0; j < C.cols; j++)
            {
                C.A[i][j] = 0;

                for (int k = 0; k < cols; k++)
                {
                    C.A[i][j] += A[i][k] * B.A[k][j];
                }
            }
        }

        return C;
    }


    // ==========================================
    // MATRIX TRANSPOSE
    // ==========================================

    Matrix transpose()
    {
        Matrix C;

        C.rows = cols;
        C.cols = rows;

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                C.A[j][i] = A[i][j];
            }
        }

        return C;
    }


    // ==========================================
    // DETERMINANT FOR ANY SQUARE MATRIX
    // ==========================================

    double determinant()
    {
        if (rows != cols)
        {
            return 0;
        }

        double temp[10][10];

        // Copy matrix
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                temp[i][j] = A[i][j];
            }
        }

        double det = 1;

        for (int i = 0; i < rows; i++)
        {
            // Find pivot row
            int pivot = i;

            for (int j = i + 1; j < rows; j++)
            {
                if (fabs(temp[j][i]) > fabs(temp[pivot][i]))
                {
                    pivot = j;
                }
            }

            // Matrix is singular
            if (fabs(temp[pivot][i]) < 1e-10)
            {
                return 0;
            }

            // Swap rows
            if (pivot != i)
            {
                for (int j = 0; j < cols; j++)
                {
                    double t = temp[i][j];
                    temp[i][j] = temp[pivot][j];
                    temp[pivot][j] = t;
                }

                det = -det;
            }

            det *= temp[i][i];

            // Eliminate elements below pivot
            for (int j = i + 1; j < rows; j++)
            {
                double factor = temp[j][i] / temp[i][i];

                for (int k = i; k < cols; k++)
                {
                    temp[j][k] -= factor * temp[i][k];
                }
            }
        }

        // Remove floating-point error
        if (fabs(det) < 1e-10)
        {
            det = 0;
        }

        return det;
    }


    // ==========================================
    // MATRIX INVERSE FOR ANY SQUARE MATRIX
    // ==========================================

    Matrix inverse()
    {
        Matrix result;

        result.rows = rows;
        result.cols = cols;

        double augmented[10][20];

        // Create augmented matrix [A | I]
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                augmented[i][j] = A[i][j];
            }

            for (int j = 0; j < cols; j++)
            {
                if (i == j)
                {
                    augmented[i][j + cols] = 1;
                }
                else
                {
                    augmented[i][j + cols] = 0;
                }
            }
        }


        // Gauss-Jordan elimination
        for (int i = 0; i < rows; i++)
        {
            // Find pivot
            int pivot = i;

            for (int j = i + 1; j < rows; j++)
            {
                if (fabs(augmented[j][i]) >
                    fabs(augmented[pivot][i]))
                {
                    pivot = j;
                }
            }


            // Singular matrix
            if (fabs(augmented[pivot][i]) < 1e-10)
            {
                result.rows = 0;
                result.cols = 0;

                return result;
            }


            // Swap rows
            if (pivot != i)
            {
                for (int j = 0; j < 2 * cols; j++)
                {
                    double temp = augmented[i][j];

                    augmented[i][j] =
                        augmented[pivot][j];

                    augmented[pivot][j] = temp;
                }
            }


            // Make pivot equal to 1
            double pivotValue = augmented[i][i];

            for (int j = 0; j < 2 * cols; j++)
            {
                augmented[i][j] /= pivotValue;
            }


            // Make all other elements in this column zero
            for (int j = 0; j < rows; j++)
            {
                if (j != i)
                {
                    double factor = augmented[j][i];

                    for (int k = 0; k < 2 * cols; k++)
                    {
                        augmented[j][k] -=
                            factor * augmented[i][k];
                    }
                }
            }
        }


        // Extract inverse matrix
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                result.A[i][j] =
                    augmented[i][j + cols];

                // Remove tiny floating-point values
                if (fabs(result.A[i][j]) < 1e-10)
                {
                    result.A[i][j] = 0;
                }
            }
        }

        return result;
    }
};

#endif