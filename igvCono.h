#ifndef __IGV_CONO
#define __IGV_CONO

#include "igvMallaTriangulos.h"

/**
 * Los objetos de esta clase representan conos en 3D
 */
class igvCono : public igvMallaTriangulos
{
public:
    // Constructores y destructor
    igvCono();
    igvCono(float radioBase, float altura, int divisiones);
    ~igvCono();
};

#endif   // __IGV_CONO