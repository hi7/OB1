#include "matrix.h"

Matrix::Matrix() {
    /*m = {
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1}
    };*/
}

void Matrix::mul(const Matrix& a, const Matrix& b) {
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            for(int k = 0; k < 4; ++k) {
                m[i][j] += a.m[i][k] * b.m[k][j];
            }
}
