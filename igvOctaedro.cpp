#include "igvOctaedro.h"
#include <cmath>


igvOctaedro::igvOctaedro() : igvMallaTriangulos()
{
}


igvOctaedro::igvOctaedro(float lado)
{
    float mitad = lado / std::sqrt(2.0f);
    
    num_vertices = 6;
    vertices = new float[num_vertices * 3];
    normales = new float[num_vertices * 3];

    vertices[0] = mitad; vertices[1] = 0.0f; vertices[2] = 0.0f;
    vertices[3] = -mitad; vertices[4] = 0.0f; vertices[5] = 0.0f;
    vertices[6] = 0.0f; vertices[7] = mitad; vertices[8] = 0.0f;
    vertices[9] = 0.0f; vertices[10] = -mitad; vertices[11] = 0.0f;
    vertices[12] = 0.0f; vertices[13] = 0.0f; vertices[14] = mitad;
    vertices[15] = 0.0f; vertices[16] = 0.0f; vertices[17] = -mitad;


    num_triangulos = 8;
    triangulos = new unsigned int[num_triangulos * 3];
    int t = 0;
    triangulos[t++] = 2; triangulos[t++] = 0; triangulos[t++] = 4;
    triangulos[t++] = 2; triangulos[t++] = 4; triangulos[t++] = 1;
    triangulos[t++] = 2; triangulos[t++] = 1; triangulos[t++] = 5;
    triangulos[t++] = 2; triangulos[t++] = 5; triangulos[t++] = 0;
    triangulos[t++] = 3; triangulos[t++] = 4; triangulos[t++] = 0;
    triangulos[t++] = 3; triangulos[t++] = 1; triangulos[t++] = 4;
    triangulos[t++] = 3; triangulos[t++] = 5; triangulos[t++] = 1;
    triangulos[t++] = 3; triangulos[t++] = 0; triangulos[t++] = 5;
    calcularNormalesVertices();
}

/**
 * Destructor
 */
igvOctaedro::~igvOctaedro()
{
}
