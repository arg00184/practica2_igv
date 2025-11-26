#ifndef __IGV_MODELO_ARTICULADO
#define __IGV_MODELO_ARTICULADO

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
#include "igvMallaTriangulos.h"

class igvModeloArticulado {
private:
    igvMallaTriangulos* cilindro;
    igvMallaTriangulos* esfera;
    igvMallaTriangulos* disco;
    igvMallaTriangulos* cono;

    float anguloBase;
    float anguloBrazo1;
    float anguloBrazo2;
    float anguloPantalla;

    struct Dimensiones {
        // Base rectangular
        float anchoBase;
        float largoBase;
        float alturaBase;

        // Brazo inferior (más grueso y corto)
        float longitudBrazo1;
        float radioBrazo1;

        // Articulaciones
        float radioArticulacion1;
        float radioArticulacion2;

        // Brazo superior (más delgado y largo)
        float longitudBrazo2;
        float radioBrazo2;

        // Cabeza/pantalla cónica
        float radioBasePantalla;
        float radioTopePantalla;
        float alturaPantalla;

        // Cuello de la pantalla
        float longitudCuello;
        float radioCuello;
    } dim;

    void dibujarBase();
    void dibujarBrazo1();
    void dibujarArticulacion1();
    void dibujarBrazo2();
    void dibujarArticulacion2();
    void dibujarCuelloPantalla();
    void dibujarPantalla();

    void crearPrimitivas();

public:
    igvModeloArticulado();
    ~igvModeloArticulado();

    void visualizar();
    void cambiarModoSombreado();
    void cambiarUsoNormales();

    void rotarBase(float incremento);
    void rotarBrazo1(float incremento);
    void rotarBrazo2(float incremento);
    void rotarPantalla(float incremento);

    float getAnguloBase() const { return anguloBase; }
    float getAnguloBrazo1() const { return anguloBrazo1; }
    float getAnguloBrazo2() const { return anguloBrazo2; }
    float getAnguloPantalla() const { return anguloPantalla; }

    void setAnguloBase(float angulo) { anguloBase = angulo; }
    void setAnguloBrazo1(float angulo) { anguloBrazo1 = angulo; }
    void setAnguloBrazo2(float angulo) { anguloBrazo2 = angulo; }
    void setAnguloPantalla(float angulo) { anguloPantalla = angulo; }

    void resetearPose();

    void visualizarConColoresSeleccion();
};

#endif // __IGV_MODELO_ARTICULADO