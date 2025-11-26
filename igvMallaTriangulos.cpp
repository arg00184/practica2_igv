#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include "igvMallaTriangulos.h"


igvMallaTriangulos::igvMallaTriangulos(long int _num_vertices, float *_vertices
                                       , long int _num_triangulos
                                       , unsigned int *_triangulos) : num_vertices(_num_vertices)
                                                                      , num_triangulos(_num_triangulos) {
    num_vertices = _num_vertices;
    vertices = new float[num_vertices * 3];
    for (long int i = 0; i < (num_vertices * 3); ++i) {
        vertices[i] = _vertices[i];
    }

    normales = nullptr;

    num_triangulos = _num_triangulos;
    triangulos = new unsigned int[num_triangulos * 3];
    for (long int i = 0; i < (num_triangulos * 3); ++i) {
        triangulos[i] = _triangulos[i];
    }
}

igvMallaTriangulos::~igvMallaTriangulos() {
    if (vertices) {
        delete []vertices;
        vertices = nullptr;
    }

    if (normales) {
        delete []normales;
        normales = nullptr;
    }

    if (triangulos) {
        delete []triangulos;
        triangulos = nullptr;
    }
}

void igvMallaTriangulos::visualizar() {
    if (!gouraud) {
        glShadeModel(GL_FLAT);
    } else {
        glShadeModel(GL_SMOOTH);
    }

    glEnable(GL_NORMALIZE);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    if (usarnormales) {
        glEnableClientState(GL_NORMAL_ARRAY);
        glNormalPointer(GL_FLOAT, 0, normales);
    }

    glDrawElements(GL_TRIANGLES, num_triangulos * 3, GL_UNSIGNED_INT, triangulos);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

void igvMallaTriangulos::calcularNormalesVertices() {
    if (!normales) {
        normales = new float[num_vertices * 3];
    }
    for (long int i = 0; i < num_vertices * 3; i++) {
        normales[i] = 0.0f;
    }
    for (long int t = 0; t < num_triangulos; t++) {
        unsigned int i0 = triangulos[t * 3 + 0];
        unsigned int i1 = triangulos[t * 3 + 1];
        unsigned int i2 = triangulos[t * 3 + 2];
        float v1x = vertices[i1 * 3 + 0] - vertices[i0 * 3 + 0];
        float v1y = vertices[i1 * 3 + 1] - vertices[i0 * 3 + 1];
        float v1z = vertices[i1 * 3 + 2] - vertices[i0 * 3 + 2];
        float v2x = vertices[i2 * 3 + 0] - vertices[i0 * 3 + 0];
        float v2y = vertices[i2 * 3 + 1] - vertices[i0 * 3 + 1];
        float v2z = vertices[i2 * 3 + 2] - vertices[i0 * 3 + 2];
        float nx = v1y * v2z - v1z * v2y;
        float ny = v1z * v2x - v1x * v2z;
        float nz = v1x * v2y - v1y * v2x;
        normales[i0 * 3 + 0] += nx;
        normales[i0 * 3 + 1] += ny;
        normales[i0 * 3 + 2] += nz;
        normales[i1 * 3 + 0] += nx;
        normales[i1 * 3 + 1] += ny;
        normales[i1 * 3 + 2] += nz;
        normales[i2 * 3 + 0] += nx;
        normales[i2 * 3 + 1] += ny;
        normales[i2 * 3 + 2] += nz;
    }
    for (long int v = 0; v < num_vertices; v++) {
        float nx = normales[v * 3 + 0];
        float ny = normales[v * 3 + 1];
        float nz = normales[v * 3 + 2];
        float longitud = std::sqrt(nx * nx + ny * ny + nz * nz);
        if (longitud > 0.0f) {
            normales[v * 3 + 0] = nx / longitud;
            normales[v * 3 + 1] = ny / longitud;
            normales[v * 3 + 2] = nz / longitud;
        }
    }
}
