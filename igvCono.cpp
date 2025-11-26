#include "igvCono.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/**
 * Constructor por defecto
 */
igvCono::igvCono() : igvMallaTriangulos()
{
}

/**
 * Constructor parametrizado
 * @param radioBase Radio de la base del cono
 * @param altura Altura del cono
 * @param divisiones Número de divisiones alrededor de la base
 * @pre Se asume que los parámetros tienen valores válidos
 * @post Se crea una nueva malla de triángulos que representa un cono
 */
igvCono::igvCono(float radioBase, float altura, int divisiones)
{
    if (divisiones < 3) divisiones = 3;
    num_vertices = divisiones + 2;
    vertices = new float[num_vertices * 3];
    normales = new float[num_vertices * 3];
    vertices[0] = 0.0f;
    vertices[1] = altura;
    vertices[2] = 0.0f;
    for (int i = 0; i < divisiones; ++i)
    {
        float angulo = (i / (float)divisiones) * 2.0f * (float)M_PI;
        float x = radioBase * std::cos(angulo);
        float z = radioBase * std::sin(angulo);
        
        int idx = (i + 1) * 3;
        vertices[idx + 0] = x;
        vertices[idx + 1] = 0.0f;
        vertices[idx + 2] = z;

    }
    int idxCentro = (divisiones + 1) * 3;
    vertices[idxCentro + 0] = 0.0f;
    vertices[idxCentro + 1] = 0.0f;
    vertices[idxCentro + 2] = 0.0f;
    num_triangulos = divisiones * 2;
    triangulos = new unsigned int[num_triangulos * 3];
    
    int t = 0;
    for (int i = 0; i < divisiones; ++i)
    {
        triangulos[t++] = 0;  // Ápice
        triangulos[t++] = i + 1;
        triangulos[t++] = ((i + 1) % divisiones) + 1;
    }
    unsigned int centroCono = divisiones + 1;
    for (int i = 0; i < divisiones; ++i)
    {
        triangulos[t++] = centroCono;  // Centro de la base
        triangulos[t++] = ((i + 1) % divisiones) + 1;
        triangulos[t++] = i + 1;
    }
    calcularNormalesVertices();
}

/**
 * Destructor
 */
igvCono::~igvCono()
{
}