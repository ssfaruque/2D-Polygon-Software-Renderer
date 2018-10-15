#ifndef MATH_H
#define MATH_H

#include <glm/glm.hpp>

struct Vertex;

using Vector2f = glm::vec2;
using Vector3f = glm::vec3;
using Vector4f = glm::vec4;

using Matrix2f = glm::mat2;
using Matrix3f = glm::mat3;
using Matrix4f = glm::mat4;


#define dotProduct glm::dot
#define crossProduct glm::cross

#define sin glm::sin
#define cos glm::cos
#define tan glm::tan

#define transpose glm::transpose


inline float toRadians(float angle) {return glm::radians(angle);}

// 2D transformations
Matrix3f createTranslationMatrix3f(const Vector2f& vector);
Matrix3f createScaleMatrix3f(const Vector2f& vector);
Matrix3f create2DRotateMatrix(const Vertex& centroid, float angle);




#endif  // MATH_H