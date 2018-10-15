#include "math.h"
#include "types.h"


Matrix3f createTranslationMatrix3f(const Vector2f& vector)
{
    Matrix3f matrix(1.0f);
    matrix[0][2] = vector[0];
    matrix[1][2] = vector[1];
    return transpose(matrix);
}


Matrix3f createScaleMatrix3f(const Vector2f& vector)
{
    Matrix3f matrix(1.0f);
    matrix[0][0] = vector[0];
    matrix[1][1] = vector[1];
    return transpose(matrix);
}


Matrix3f create2DRotateMatrix(const Vertex& centroid, float angle)
{
    Matrix3f matrix(1.0f);

    matrix[0][0] = cos(angle);
    matrix[0][1] = -sin(angle);
    matrix[0][2] = centroid.x * (1 - cos(angle)) + centroid.y * sin(angle);

    matrix[1][0] = sin(angle);
    matrix[1][1] = cos(angle);
    matrix[1][2] = centroid.y * (1 - cos(angle)) - centroid.x * sin(angle); 

    return transpose(matrix);
}
