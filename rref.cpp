// File Name: rref
// Author: Steven Landis
// Email: stevenlandis@umail.ucsb.edu
// Last changed: 17/oct/2016
// Description: uses a matrix class to reduce
#include<iostream>
using namespace std;

class Matrix {
private:
    double *c;
    //pointer to contents array

    int rows, cols, len;
    void decrement(int row, int col, double value) {
    //decreases a cell by a certain amount
    //used in rref
        if (row >= 0 and row < rows and col >= 0 and col < cols) {
            c[col + row * cols] -= value;
        }
    }
    void scale(int row, int col, double value) {
    //scales a cell by a certain amount
    //used in rref
        if (row >= 0 and row < rows and col >= 0 and col < cols) {
            c[col + row * cols] *= value;
        }
    }

public:
    Matrix(int rows, int cols) {
    //initializes empty matrix
        this->rows = rows;
        this->cols = cols;
        this->len = rows*cols;
        c = new double[rows*cols];
        zero();
    }
    Matrix(int rows, int cols, double * constructorArray) {
    //initializes matrix from a one-dimensional array
        this->rows = rows;
        this->cols = cols;
        this->len = rows*cols;
        c = constructorArray;
    }
    void zero() {
        //sets all cells to zero
        for (int i = 0; i < len; i++) {
            c[i]=0;
        }
    }
    double get(int row, int col) {
    //retrieves the value in a cell
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            return 0.0;
        }
        return c[col + row * cols];
    }
    void set(int row, int col, double value) {
    //sets the value of a cell
        if (row >= 0 and row < rows and col >= 0 and col < cols) {
            c[col + row * cols] = value;
        }
    }
    void rref() {
    //puts the matrix in rref
        for (int i = 0; i < cols; i++) {
            int pivot = -1;
            //pivot set to sentinal value

            //Search for pivot cell in current column:
            for (int j = 0; j < rows; j++) {
                bool zeroes = true;
                for (int k = i-1; k >= 0; k--) {
                    if (get(j,k) != 0) {
                        zeroes = false;
                        k = 0;
                        //stop the loop early
                    }
                }
                if (zeroes) {
                    pivot = j;
                    j = rows;
                    //found pivot, stop loop early
                }
            }
            if (pivot >= 0) {
            //if pivot cell was found:
                if (get(pivot, i) == 0) {
                //if the pivot cell is zero, switch with another row:
                    for (int j = pivot + 1; j < rows; j++) {
                        if (get(j, i) != 0) {
                            //swap the two rows
                            for (int k = 0; k < cols; k++) {
                                //swap (pivot, k) and (j, k)
                                double buffer = get(pivot, k);
                                set(pivot, k, get(j, k));
                                set(j, k, buffer);
                            }
                            j = rows;
                        }
                    }
                }
                if (get(pivot, i) != 0.0) {
                //if the switching worked:
                    double scalar = 1/get(pivot, i);
                    for (int j = 0; j < cols; j++) {
                        scale(pivot, j, scalar);
                    }
                    for (int j = 0; j < rows; j++) {
                        if (j != pivot) {
                            double scalar = get(j, i);
                            for (int k = 0; k < cols; k++) {
                                decrement(j, k, scalar * get(pivot, k));
                            }
                        }
                    }
                }
            }
        }
    }
    void disp() {
    //displays the matrix
        cout.setf(ios::fixed);
        cout.setf(ios::showpoint);
        cout.precision(4);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << get(i,j) << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    double base[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    auto a = new Matrix(4, 4, base);
    cout << "Initial Matrix Is:\n";
    a->disp();
    a->rref();
    cout << "\nFinal Matrix Is:\n";
    a->disp();

    return 0;
}
