#ifndef __IGV_OCTAEDRO
#define __IGV_OCTAEDRO

#include "igvMallaTriangulos.h"

/**
 * Los objetos de esta clase representan octaedros en 3D
 */
class igvOctaedro : public igvMallaTriangulos
{
public:
    // Constructores y destructor
    igvOctaedro();
    igvOctaedro(float lado);
    ~igvOctaedro();
};

#endif   // __IGV_OCTAEDRO
