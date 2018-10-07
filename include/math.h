#ifndef MATH_H
#define MATH_H

template<typename T, int N>
struct Matrix;

template<typename T, int N>
struct Vector;


template<typename T, int N>
struct Matrix
{
    T data[N][N];

    Matrix<T, N> operator+(const Matrix<T, N>& other);
    friend Matrix<T, N> operator+(const Matrix<T, N>& matrix, const T& other)
    {
        Matrix<T, N> result;

        for(int i = 0; i < N; ++i)
        {
            for(int j = 0; j < N; ++j)
                result.data[i][j] = matrix.data[i][j] + other;
        }

        return result;
    }
    Matrix<T, N> operator-(const Matrix<T, N>& other);
    Matrix<T, N> operator-(const T& other);
    Matrix<T, N> operator*(const Matrix<T, N>& other);
    Vector<T, N> operator*(const Vector<T, N>& other);
    Matrix<T, N> operator*(const T& other);
};


template<typename T, int N>
struct Vector
{
    T data[N];

    Vector<T, N> operator+(const Vector<T, N>& other);
    Vector<T, N> operator+(const T& other);
    Vector<T, N> operator-(const Vector<T, N>& other);
    Vector<T, N> operator-(const T& other);
    Vector<T, N> operator*(const Vector<T, N>& other);
    Vector<T, N> operator*(const T& other);
};


using Vector2 = Vector<float, 2>;
using Vector3 = Vector<float, 3>;
using Vector4 = Vector<float, 4>;

using Matrix2 = Matrix<float, 2>;
using Matrix3 = Matrix<float, 3>;
using Matrix4 = Matrix<float, 4>;


#endif  // MATH_H