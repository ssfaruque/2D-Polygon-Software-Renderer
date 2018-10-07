#ifndef MATH_H
#define MATH_H

#include <iomanip>


template<typename T, int N>
struct Matrix;

template<typename T, int N>
struct Vector;


template<typename T, int N>
struct Matrix
{
    T data[N][N];

    friend Matrix<T, N> operator+(const Matrix<T, N>& left, const Matrix<T, N>& right)
    {
        Matrix<T, N> result;

        for(int i = 0; i < N; ++i)
        {
            for(int j = 0; j < N; ++j)
                result.data[i][j] = left.data[i][j] + right.data[i][j];
        }

        return result;
    }


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


    friend Matrix<T, N> operator-(const Matrix<T, N>& left, const Matrix<T, N>& right)
    {
        Matrix<T, N> result;

        for(int i = 0; i < N; ++i)
        {
            for(int j = 0; j < N; ++j)
                result.data[i][j] = left.data[i][j] - right.data[i][j];
        }

        return result;
    }

    friend Matrix<T, N> operator-(const Matrix<T, N>& matrix, const T& other)
    {
        Matrix<T, N> result;

        for(int i = 0; i < N; ++i)
        {
            for(int j = 0; j < N; ++j)
                result.data[i][j] = matrix.data[i][j] - other;
        }

        return result;
    }


    friend Matrix<T, N> operator*(const Matrix<T, N>& left, const Matrix<T, N>& right)
    {
        Matrix<T, N> result;


        return result;
    }


    friend Vector<T, N> operator*(const Matrix<T, N>& matrix, const Vector<T, N>& vec)
    {
        Vector<T, N> result;


        return result;
    }


    friend Matrix<T, N> operator*(const Matrix<T, N>& matrix, const T& other)
    {
        Matrix<T, N> result;

        for(int i = 0; i < N; ++i)
        {
            for(int j = 0; j < N; ++j)
                result.data[i][j] = matrix.data[i][j] * other;
        }

        return result;
    }


    Matrix(T diagonalVal = 1)
    {
        for(int i = 0; i < N; ++i)
        {
            for(int j = 0; j < N; ++j)
            {
                if(i == j)
                    data[i][j] = diagonalVal;

                else
                    data[i][j] = 0;
            }
        }
    }


    friend std::ostream& operator<<(std::ostream& os, const Matrix<T, N>& matrix)
    {
        os << "---------------------------------------------" << std::endl;

        for(int i = 0; i < N; ++i)
        {
            for(int j = 0; j < N; ++j)
            {
                os << std::left << std::setw(10) << matrix.data[i][j] << " ";
            }

            os << std::endl;
        }

        os << "---------------------------------------------" << std::endl;

        return os;
    }
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