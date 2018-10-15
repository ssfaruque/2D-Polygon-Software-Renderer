#include "entity.h"


Vertex Entity::calcCentroid() const 
{
    float x = 0.0f, y = 0.0f, z = 0.0f;

    for(const auto& vertex : m_vertices)
    {
        x += vertex.x;
        y += vertex.y;
        z += vertex.z;
    }

    x /= getNumVertices();
    y /= getNumVertices();
    z /= getNumVertices();

    return Vertex(x, y, z, 1.0f);
}


void Entity::translate(const Vector2f& vector)
{
    Matrix3f translateMatrix = createTranslationMatrix3f(vector);

    for(auto& vertex : m_vertices)
    {
        Vector3f vertexVecCast = Vector3f(vertex.x, vertex.y, 1.0f);
        Vector3f newPosition = translateMatrix * vertexVecCast;   
        vertex = Vertex(newPosition.x, newPosition.y);                  
    }
}


void Entity::scale(const Vector2f& vector)
{
    Matrix3f scaleMatrix = createScaleMatrix3f(vector);

    for(auto& vertex : m_vertices)
    {
        Vector3f vertexVecCast = Vector3f(vertex.x, vertex.y, 1.0f);
        Vector3f newPosition = scaleMatrix * vertexVecCast;   
        vertex = Vertex(newPosition.x, newPosition.y);                  
    }
}


void Entity::rotate(float angle)
{
    Vertex centroid = calcCentroid();
    angle = toRadians(angle);
    Matrix3f rotateMatrix = create2DRotateMatrix(centroid, angle);

    for(auto& vertex : m_vertices)
    {
        Vector3f vertexVecCast = Vector3f(vertex.x, vertex.y, 1.0f);
        Vector3f newPosition = rotateMatrix * vertexVecCast;   
        vertex = Vertex(newPosition.x, newPosition.y);                  
    }
}