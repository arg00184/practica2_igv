#include "igvTetraedro.h"
#include <cmath>


igvTetraedro::igvTetraedro() : igvMallaTriangulos()
{
}

igvTetraedro::igvTetraedro(float lado)
{
    
    num_vertices = 4;
    vertices = new float[num_vertices * 3];
    normales = new float[num_vertices * 3];

    float a = lado / std::sqrt(2.0f);
    float h = lado * std::sqrt(2.0f / 3.0f);
    float d = lado * std::sqrt(3.0f) / 6.0f;
    vertices[0] = 0.0f;
    vertices[1] = -h / 4.0f;
    vertices[2] = a / 2.0f;
    vertices[3] = -a / 2.0f;
    vertices[4] = -h / 4.0f;
    vertices[5] = -lado / (2.0f * std::sqrt(3.0f));
    vertices[6] = a / 2.0f;
    vertices[7] = -h / 4.0f;
    vertices[8] = -lado / (2.0f * std::sqrt(3.0f));
    vertices[9] = 0.0f;
    vertices[10] = 3.0f * h / 4.0f;
    vertices[11] = 0.0f;

    num_triangulos = 4;
    triangulos = new unsigned int[num_triangulos * 3];
    
    int t = 0;
    triangulos[t++] = 0;
    triangulos[t++] = 2;
    triangulos[t++] = 1;
    triangulos[t++] = 0;
    triangulos[t++] = 3;
    triangulos[t++] = 2;
    triangulos[t++] = 0;
    triangulos[t++] = 1;
    triangulos[t++] = 3;
    triangulos[t++] = 1;
    triangulos[t++] = 2;
    triangulos[t++] = 3;

    calcularNormalesVertices();
}

/**
 * Destructor
 */
igvTetraedro::~igvTetraedro()
{
}
