#include "math.h"
#include "types.h"

Matrix3f createTranslationMatrix3f(const Vector2f& vector)
{
    Matrix3f matrix(1.0f);
    matrix[0][2] = vector[0];
    matrix[1][2] = vector[1];
    return transpose(matrix);
}


Matrix4f createTranslationMatrix4f(const Vector3f& vector)
{
    Matrix4f matrix(1.0f);
    matrix[0][3] = vector[0];
    matrix[1][3] = vector[1];
    matrix[2][3] = vector[2];
    return transpose(matrix);
}


Matrix3f createScaleMatrix3f(const Vector2f& vector)
{
    Matrix3f matrix(1.0f);
    matrix[0][0] = vector[0];
    matrix[1][1] = vector[1];
    return transpose(matrix);
}


Matrix4f createScaleMatrix4f(const Vector3f& vector)
{
    Matrix4f matrix(1.0f);
    matrix[0][0] = vector[0];
    matrix[1][1] = vector[1];
    matrix[2][2] = vector[2];
    return transpose(matrix);
}


Matrix3f create2DRotateMatrix(const Vertex& centroid, float angle)
{
    Matrix3f matrix(1.0f);




    return transpose(matrix);
}


Matrix4f createRotateXMatrix4f(float angle)
{
    Matrix4f matrix(1.0f);
    matrix[1][1] = cos(angle); matrix[1][2] = -sin(angle);
    matrix[2][1] = sin(angle); matrix[2][2] = cos(angle);
    return transpose(matrix);
}


Matrix4f createRotateYMatrix4f(float angle)
{
    Matrix4f matrix(1.0f);
    matrix[0][0] = cos(angle); matrix[0][2] = sin(angle);
    matrix[2][0] = -sin(angle); matrix[2][2] = cos(angle);
    return transpose(matrix);
}


Matrix4f createRotateZMatrix4f(float angle)
{
    Matrix4f matrix(1.0f);
    matrix[0][0] = cos(angle); matrix[0][1] = -sin(angle);
    matrix[1][0] = sin(angle); matrix[1][1] = cos(angle);
    return transpose(matrix);
}