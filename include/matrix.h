typedef float matrix_t[4][4];

class Matrix {
    public:
        matrix_t m;
        Matrix();
        void mul(const Matrix& a, const Matrix& b);
};