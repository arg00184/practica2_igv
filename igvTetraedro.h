#ifndef __IGV_TETRAEDRO
#define __IGV_TETRAEDRO

#include "igvMallaTriangulos.h"

/**
 * Los objetos de esta clase representan tetraedros en 3D
 */
class igvTetraedro : public igvMallaTriangulos
{
public:
    // Constructores y destructor
    igvTetraedro();
    igvTetraedro(float lado);
    ~igvTetraedro();
};

#endif   // __IGV_TETRAEDRO
