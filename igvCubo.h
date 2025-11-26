#ifndef __IGV_CUBO
#define __IGV_CUBO

#include "igvMallaTriangulos.h"

/**
 * Los objetos de esta clase representan cubos en 3D
 */
class igvCubo : public igvMallaTriangulos
{
public:
    // Constructores y destructor
    igvCubo();
    igvCubo(float lado);
    ~igvCubo();
};

#endif   // __IGV_CUBO
