#include "igvCubo.h"
#include <cmath>

/**
 * Constructor por defecto
 */
igvCubo::igvCubo() : igvMallaTriangulos()
{
}

/**
 * Constructor parametrizado
 * @param lado Longitud del lado del cubo
 * @pre Se asume que el parámetro tiene un valor válido
 * @post Se crea una nueva malla de triángulos que representa un cubo
 */
igvCubo::igvCubo(float lado)
{
    float mitad = lado / 2.0f;

    num_vertices = 8;
    vertices = new float[num_vertices * 3];
    normales = new float[num_vertices * 3];
    vertices[0] = -mitad; vertices[1] = -mitad; vertices[2] = mitad;
    vertices[3] = mitad; vertices[4] = -mitad; vertices[5] = mitad;
    vertices[6] = mitad; vertices[7] = mitad; vertices[8] = mitad;
    vertices[9] = -mitad; vertices[10] = mitad; vertices[11] = mitad;
    vertices[12] = -mitad; vertices[13] = -mitad; vertices[14] = -mitad;
    vertices[15] = mitad; vertices[16] = -mitad; vertices[17] = -mitad;
    vertices[18] = mitad; vertices[19] = mitad; vertices[20] = -mitad;
    vertices[21] = -mitad; vertices[22] = mitad; vertices[23] = -mitad;

    num_triangulos = 12;
    triangulos = new unsigned int[num_triangulos * 3];
    
    int t = 0;
    triangulos[t++] = 0; triangulos[t++] = 1; triangulos[t++] = 2;
    triangulos[t++] = 0; triangulos[t++] = 2; triangulos[t++] = 3;
    triangulos[t++] = 5; triangulos[t++] = 4; triangulos[t++] = 7;
    triangulos[t++] = 5; triangulos[t++] = 7; triangulos[t++] = 6;
    triangulos[t++] = 4; triangulos[t++] = 0; triangulos[t++] = 3;
    triangulos[t++] = 4; triangulos[t++] = 3; triangulos[t++] = 7;
    triangulos[t++] = 1; triangulos[t++] = 5; triangulos[t++] = 6;
    triangulos[t++] = 1; triangulos[t++] = 6; triangulos[t++] = 2;
    triangulos[t++] = 3; triangulos[t++] = 2; triangulos[t++] = 6;
    triangulos[t++] = 3; triangulos[t++] = 6; triangulos[t++] = 7;
    triangulos[t++] = 4; triangulos[t++] = 5; triangulos[t++] = 1;
    triangulos[t++] = 4; triangulos[t++] = 1; triangulos[t++] = 0;

    calcularNormalesVertices();
}

/**
 * Destructor
 */
igvCubo::~igvCubo()
{
}
