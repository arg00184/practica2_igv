#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif

#include "igvModeloArticulado.h"
#include "igvMallaTriangulos.h"

class igvEscena3D {
public:
    igvEscena3D();

    ~igvEscena3D();

    void visualizar();

    bool get_ejes();

    void set_ejes(bool _ejes);

    void cambiarModoSombreado();

    void cambiarUsoNormales();

    void rotarBaseLampara(float incremento);

    void rotarBrazo1Lampara(float incremento);

    void rotarBrazo2Lampara(float incremento);

    void rotarPantallaLampara(float incremento);

    void resetearPoseLampara();

    void activarModoSeleccion(bool activo) { modoSeleccion = activo; }
    bool getModoSeleccion() const { return modoSeleccion; }
    int getParteSeleccionada() const { return parteSeleccionada; }
    void setParteSeleccionada(int parte) { parteSeleccionada = parte; }

    void seleccionarParte(int x, int y, int alto_ventana);

private:
    bool ejes = true;
    igvModeloArticulado modelo;
    igvMallaTriangulos malla;
    bool mallaCargada = false;
    bool modoSeleccion = false;
    int parteSeleccionada = -1; // -1: ninguna, 0: base, 1: brazo1, 2: brazo2, 3: pantalla

    void visualizarModoSeleccion();

    unsigned char *capturarBufferSeleccion(int x, int y);

    int identificarPartePorColor(unsigned char r, unsigned char g, unsigned char b);

    void pintar_ejes();
};

#endif
