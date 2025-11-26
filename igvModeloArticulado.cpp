#include "igvModeloArticulado.h"
#include "igvCilindro.h"
#include "igvEsfera.h"
#include "igvCono.h"
#include "igvDisco.h"
#include <cmath>

igvModeloArticulado::igvModeloArticulado() {
    // Ángulos iniciales para pose característica de Luxo Jr.
    anguloBase = 0.0f;
    anguloBrazo1 = 60.0f;  // Brazo inferior levantado
    anguloBrazo2 = -100.0f; // Brazo superior doblado hacia abajo
    anguloPantalla = -20.0f; // Pantalla mirando ligeramente hacia abajo

    // Dimensiones estilo Luxo Jr. de Pixar
    dim.anchoBase = 0.8f;
    dim.largoBase = 1.2f;
    dim.alturaBase = 0.15f;

    dim.longitudBrazo1 = 1.8f;  // Brazo inferior corto y robusto
    dim.radioBrazo1 = 0.12f;
    dim.radioBrazo1Prox = 0.14f; // Parte cercana al hombro más gruesa
    dim.radioBrazo1Dist = 0.11f; // Parte cercana al codo ligeramente más delgada

    dim.radioArticulacion1 = 0.18f;  // Articulación grande y visible

    dim.longitudBrazo2 = 2.2f;  // Brazo superior más largo
    dim.radioBrazo2 = 0.09f;
    dim.radioBrazo2Prox = 0.1f; // Antebrazo cerca del codo
    dim.radioBrazo2Dist = 0.085f; // Antebrazo cerca de la muñeca

    dim.radioArticulacion2 = 0.15f;

    dim.separacionBarras = 0.25f;           // Distancia entre las barras paralelas
    dim.radioBarraSecundaria1 = 0.08f;      // Grosor de las barras dobles inferiores
    dim.radioBarraSecundaria2 = 0.065f;     // Grosor de las barras dobles superiores
    dim.radioRefuerzoHorizontal = 0.06f;    // Grosor de los travesaños horizontales

    dim.longitudCuello = 0.3f;
    dim.radioCuello = 0.08f;

    dim.radioBasePantalla = 0.7f;   // Base ancha de la pantalla
    dim.radioTopePantalla = 0.35f;  // Tope más estrecho
    dim.alturaPantalla = 0.9f;
    dim.grosorPantalla = 0.05f; // Espesor de la pantalla para dar profundidad

    dim.radioBombilla = 0.18f;   // Tamaño de la bombilla interior
    dim.alturaBombilla = 0.25f;  // Posición dentro del cono

    crearPrimitivas();
}

void igvModeloArticulado::crearPrimitivas() {
    cilindro = new igvCilindro(1.0f, 1.0f, 20, 10);
    esfera = new igvEsfera(1.0f, 20, 20);
    disco = new igvDisco(1.0f, 30);
    cono = new igvCono(1.0f, 1.0f, 30);
}

igvModeloArticulado::~igvModeloArticulado() {
    if (cilindro) delete cilindro;
    if (esfera) delete esfera;
    if (disco) delete disco;
    if (cono) delete cono;
}

void igvModeloArticulado::dibujarBase() {
    // Color gris oscuro para la base metálica
    GLfloat colorBase[] = {0.25f, 0.25f, 0.28f, 1.0f};
    GLfloat specular[] = {0.4f, 0.4f, 0.4f, 1.0f};
    GLfloat shininess[] = {32.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorBase);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

    glPushMatrix();
        // Base rectangular (simulada con cilindro escalado)
        glPushMatrix();
            glScalef(dim.largoBase, dim.alturaBase, dim.anchoBase);
            cilindro->visualizar();
        glPopMatrix();

        // Tapa inferior
        glPushMatrix();
            glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
            glScalef(dim.largoBase, 1.0f, dim.anchoBase);
            disco->visualizar();
        glPopMatrix();

        // Tapa superior
        glPushMatrix();
            glTranslatef(0.0f, dim.alturaBase, 0.0f);
            glScalef(dim.largoBase, 1.0f, dim.anchoBase);
            disco->visualizar();
        glPopMatrix();
    glPopMatrix();
}

void igvModeloArticulado::dibujarBrazo1() {
    // Color blanco/gris claro para los brazos
    GLfloat colorBrazo[] = {0.85f, 0.85f, 0.87f, 1.0f};
    GLfloat specular[] = {0.6f, 0.6f, 0.6f, 1.0f};
    GLfloat shininess[] = {50.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorBrazo);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

    glPushMatrix();
        glTranslatef(0.0f, dim.alturaBase, 0.0f);
        glRotatef(anguloBrazo1, 0.0f, 0.0f, 1.0f);

        // Hombro redondeado
        glPushMatrix();
            glTranslatef(0.0f, dim.radioBrazo1Prox * 0.6f, 0.0f);
            glScalef(dim.radioBrazo1Prox, dim.radioBrazo1Prox, dim.radioBrazo1Prox);
            esfera->visualizar();
        glPopMatrix();

        // Parte proximal del brazo (más gruesa)
        glPushMatrix();
            glTranslatef(0.0f, dim.longitudBrazo1 * 0.25f, 0.0f);
            glScalef(dim.radioBrazo1Prox, dim.longitudBrazo1 * 0.5f, dim.radioBrazo1Prox);
            cilindro->visualizar();
        glPopMatrix();

        // Parte distal del brazo (acercándose al codo)
        glPushMatrix();
            glTranslatef(0.0f, dim.longitudBrazo1 * 0.75f, 0.0f);
            glScalef(dim.radioBrazo1Dist, dim.longitudBrazo1 * 0.5f, dim.radioBrazo1Dist);
            cilindro->visualizar();
        glPopMatrix();

        // Remate suave en el codo
        glPushMatrix();
            glTranslatef(0.0f, dim.longitudBrazo1, 0.0f);
            glScalef(dim.radioBrazo1Dist, dim.radioBrazo1Dist, dim.radioBrazo1Dist);
            esfera->visualizar();
        glPopMatrix();
    glPopMatrix();
}

void igvModeloArticulado::dibujarArticulacion1() {
    // Color gris medio para articulaciones
    GLfloat colorArticulacion[] = {0.4f, 0.4f, 0.42f, 1.0f};
    GLfloat specular[] = {0.5f, 0.5f, 0.5f, 1.0f};
    GLfloat shininess[] = {40.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorArticulacion);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

    glPushMatrix();
        glTranslatef(0.0f, dim.alturaBase, 0.0f);
        glRotatef(anguloBrazo1, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.0f, dim.longitudBrazo1, 0.0f);
        glScalef(dim.radioArticulacion1, dim.radioArticulacion1, dim.radioArticulacion1);
        esfera->visualizar();
    glPopMatrix();
}

void igvModeloArticulado::dibujarBrazo2() {
    // Color blanco/gris claro
    GLfloat colorBrazo[] = {0.85f, 0.85f, 0.87f, 1.0f};
    GLfloat specular[] = {0.6f, 0.6f, 0.6f, 1.0f};
    GLfloat shininess[] = {50.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorBrazo);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

    glPushMatrix();
        glTranslatef(0.0f, dim.alturaBase, 0.0f);
        glRotatef(anguloBrazo1, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.0f, dim.longitudBrazo1, 0.0f);
        glRotatef(anguloBrazo2, 0.0f, 0.0f, 1.0f);

        // Parte proximal del antebrazo (cerca del codo)
        glPushMatrix();
            glTranslatef(0.0f, dim.longitudBrazo2 * 0.25f, 0.0f);
            glScalef(dim.radioBrazo2Prox, dim.longitudBrazo2 * 0.5f, dim.radioBrazo2Prox);
            cilindro->visualizar();
        glPopMatrix();

        // Parte distal del antebrazo (cerca de la muñeca)
        glPushMatrix();
            glTranslatef(0.0f, dim.longitudBrazo2 * 0.75f, 0.0f);
            glScalef(dim.radioBrazo2Dist, dim.longitudBrazo2 * 0.5f, dim.radioBrazo2Dist);
            cilindro->visualizar();
        glPopMatrix();

        // Muñeca esférica
        glPushMatrix();
            glTranslatef(0.0f, dim.longitudBrazo2, 0.0f);
            glScalef(dim.radioBrazo2Dist * 0.9f, dim.radioBrazo2Dist * 0.9f, dim.radioBrazo2Dist * 0.9f);
            esfera->visualizar();
        glPopMatrix();
    glPopMatrix();
}

void igvModeloArticulado::dibujarArticulacion2() {
    // Color gris medio
    GLfloat colorArticulacion[] = {0.4f, 0.4f, 0.42f, 1.0f};
    GLfloat specular[] = {0.5f, 0.5f, 0.5f, 1.0f};
    GLfloat shininess[] = {40.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorArticulacion);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

    glPushMatrix();
        glTranslatef(0.0f, dim.alturaBase, 0.0f);
        glRotatef(anguloBrazo1, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.0f, dim.longitudBrazo1, 0.0f);
        glRotatef(anguloBrazo2, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.0f, dim.longitudBrazo2, 0.0f);
        glScalef(dim.radioArticulacion2, dim.radioArticulacion2, dim.radioArticulacion2);
        esfera->visualizar();
    glPopMatrix();
}

void igvModeloArticulado::dibujarCuelloPantalla() {
    // Color gris oscuro para el cuello
    GLfloat colorCuello[] = {0.3f, 0.3f, 0.32f, 1.0f};
    GLfloat specular[] = {0.4f, 0.4f, 0.4f, 1.0f};
    GLfloat shininess[] = {35.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorCuello);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

    glPushMatrix();
        glTranslatef(0.0f, dim.alturaBase, 0.0f);
        glRotatef(anguloBrazo1, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.0f, dim.longitudBrazo1, 0.0f);
        glRotatef(anguloBrazo2, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.0f, dim.longitudBrazo2, 0.0f);
        glRotatef(anguloPantalla, 0.0f, 0.0f, 1.0f);

        glPushMatrix();
            glScalef(dim.radioCuello, dim.longitudCuello, dim.radioCuello);
            cilindro->visualizar();
        glPopMatrix();
    glPopMatrix();
}

void igvModeloArticulado::dibujarPantalla() {
    // Color blanco brillante para la pantalla
    GLfloat colorPantalla[] = {0.92f, 0.92f, 0.94f, 1.0f};
    GLfloat specular[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat shininess[] = {60.0f};

    // Interior más oscuro
    GLfloat colorInterior[] = {0.55f, 0.55f, 0.58f, 1.0f};
    GLfloat colorBombilla[] = {1.0f, 0.93f, 0.7f, 1.0f};
    GLfloat emisivaBombilla[] = {0.6f, 0.55f, 0.4f, 1.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorPantalla);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

    glPushMatrix();
        glTranslatef(0.0f, dim.alturaBase, 0.0f);
        glRotatef(anguloBrazo1, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.0f, dim.longitudBrazo1, 0.0f);
        glRotatef(anguloBrazo2, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.0f, dim.longitudBrazo2, 0.0f);
        glRotatef(anguloPantalla, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.0f, dim.longitudCuello, 0.0f);

        // Cono de la pantalla (invertido)
        glPushMatrix();
            glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
            glScalef(dim.radioBasePantalla, dim.alturaPantalla, dim.radioBasePantalla);
            cono->visualizar();
        glPopMatrix();

        // Disco en la boca de la pantalla
        glPushMatrix();
            glTranslatef(0.0f, -dim.alturaPantalla, 0.0f);
            glScalef(dim.radioBasePantalla, 1.0f, dim.radioBasePantalla);
            disco->visualizar();
        glPopMatrix();

        // Interior de la pantalla para dar profundidad
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorInterior);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
        glPushMatrix();
            glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
            glScalef(dim.radioBasePantalla - dim.grosorPantalla, dim.alturaPantalla - dim.grosorPantalla, dim.radioBasePantalla - dim.grosorPantalla);
            cono->visualizar();
        glPopMatrix();

        // Bombilla dentro de la pantalla
        glPushMatrix();
            glTranslatef(0.0f, -dim.alturaBombilla, 0.0f);
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorBombilla);
            glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
            glMaterialfv(GL_FRONT, GL_EMISSION, emisivaBombilla);
            glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
            glScalef(dim.radioBombilla, dim.radioBombilla, dim.radioBombilla);
            esfera->visualizar();
            // Desactivar emisión para siguientes objetos
            GLfloat sinEmision[] = {0.0f, 0.0f, 0.0f, 1.0f};
            glMaterialfv(GL_FRONT, GL_EMISSION, sinEmision);
        glPopMatrix();
    glPopMatrix();
}

void igvModeloArticulado::visualizar() {
    glPushMatrix();
        glRotatef(anguloBase, 0.0f, 1.0f, 0.0f);
        dibujarBase();
        dibujarBrazo1();
        dibujarArticulacion1();
        dibujarBrazo2();
        dibujarArticulacion2();
        dibujarCuelloPantalla();
        dibujarPantalla();
    glPopMatrix();
}

void igvModeloArticulado::cambiarModoSombreado() {
    if (cilindro) cilindro->cambiarvis();
    if (esfera) esfera->cambiarvis();
    if (disco) disco->cambiarvis();
    if (cono) cono->cambiarvis();
}

void igvModeloArticulado::cambiarUsoNormales() {
    if (cilindro) cilindro->cambiarnormales();
    if (esfera) esfera->cambiarnormales();
    if (disco) disco->cambiarnormales();
    if (cono) cono->cambiarnormales();
}

void igvModeloArticulado::rotarBase(float incremento) {
    anguloBase += incremento;
    while (anguloBase >= 360.0f) anguloBase -= 360.0f;
    while (anguloBase < 0.0f) anguloBase += 360.0f;
}

void igvModeloArticulado::rotarBrazo1(float incremento) {
    anguloBrazo1 += incremento;
    if (anguloBrazo1 > 120.0f) anguloBrazo1 = 120.0f;
    if (anguloBrazo1 < -10.0f) anguloBrazo1 = -10.0f;
}

void igvModeloArticulado::rotarBrazo2(float incremento) {
    anguloBrazo2 += incremento;
    if (anguloBrazo2 > 30.0f) anguloBrazo2 = 30.0f;
    if (anguloBrazo2 < -150.0f) anguloBrazo2 = -150.0f;
}

void igvModeloArticulado::rotarPantalla(float incremento) {
    anguloPantalla += incremento;
    if (anguloPantalla > 45.0f) anguloPantalla = 45.0f;
    if (anguloPantalla < -90.0f) anguloPantalla = -90.0f;
}

void igvModeloArticulado::resetearPose() {
    anguloBase = 0.0f;
    anguloBrazo1 = 60.0f;
    anguloBrazo2 = -100.0f;
    anguloPantalla = -20.0f;
}

void igvModeloArticulado::visualizarConColoresSeleccion() {
    glPushMatrix();
        glRotatef(anguloBase, 0.0f, 1.0f, 0.0f);

        // Base - Color ROJO (255, 0, 0)
        glColor3ub(255, 0, 0);
        glPushMatrix();
            glPushMatrix();
                glScalef(dim.largoBase, dim.alturaBase, dim.anchoBase);
                cilindro->visualizar();
            glPopMatrix();
            glPushMatrix();
                glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
                glScalef(dim.largoBase, 1.0f, dim.anchoBase);
                disco->visualizar();
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0.0f, dim.alturaBase, 0.0f);
                glScalef(dim.largoBase, 1.0f, dim.anchoBase);
                disco->visualizar();
            glPopMatrix();
        glPopMatrix();

        // Brazo1 - Color VERDE (0, 255, 0)
        glColor3ub(0, 255, 0);
        glPushMatrix();
            glTranslatef(0.0f, dim.alturaBase, 0.0f);
            glRotatef(anguloBrazo1, 0.0f, 0.0f, 1.0f);
            glPushMatrix();
                glTranslatef(0.0f, dim.radioBrazo1Prox * 0.6f, 0.0f);
                glScalef(dim.radioBrazo1Prox, dim.radioBrazo1Prox, dim.radioBrazo1Prox);
                esfera->visualizar();
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0.0f, dim.longitudBrazo1 * 0.25f, 0.0f);
                glScalef(dim.radioBrazo1Prox, dim.longitudBrazo1 * 0.5f, dim.radioBrazo1Prox);
                cilindro->visualizar();
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0.0f, dim.longitudBrazo1 * 0.75f, 0.0f);
                glScalef(dim.radioBrazo1Dist, dim.longitudBrazo1 * 0.5f, dim.radioBrazo1Dist);
                cilindro->visualizar();
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0.0f, dim.longitudBrazo1, 0.0f);
                glScalef(dim.radioBrazo1Dist, dim.radioBrazo1Dist, dim.radioBrazo1Dist);
                esfera->visualizar();
            glPopMatrix();
        glPopMatrix();

        // Articulación 1 - mismo color que Brazo1
        glPushMatrix();
            glTranslatef(0.0f, dim.alturaBase, 0.0f);
            glRotatef(anguloBrazo1, 0.0f, 0.0f, 1.0f);
            glTranslatef(0.0f, dim.longitudBrazo1, 0.0f);
            glScalef(dim.radioArticulacion1, dim.radioArticulacion1, dim.radioArticulacion1);
            esfera->visualizar();
        glPopMatrix();

        // Brazo2 - Color AZUL (0, 0, 255)
        glColor3ub(0, 0, 255);
        glPushMatrix();
            glTranslatef(0.0f, dim.alturaBase, 0.0f);
            glRotatef(anguloBrazo1, 0.0f, 0.0f, 1.0f);
            glTranslatef(0.0f, dim.longitudBrazo1, 0.0f);
            glRotatef(anguloBrazo2, 0.0f, 0.0f, 1.0f);
            glPushMatrix();
                glTranslatef(0.0f, dim.longitudBrazo2 * 0.25f, 0.0f);
                glScalef(dim.radioBrazo2Prox, dim.longitudBrazo2 * 0.5f, dim.radioBrazo2Prox);
                cilindro->visualizar();
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0.0f, dim.longitudBrazo2 * 0.75f, 0.0f);
                glScalef(dim.radioBrazo2Dist, dim.longitudBrazo2 * 0.5f, dim.radioBrazo2Dist);
                cilindro->visualizar();
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0.0f, dim.longitudBrazo2, 0.0f);
                glScalef(dim.radioBrazo2Dist * 0.9f, dim.radioBrazo2Dist * 0.9f, dim.radioBrazo2Dist * 0.9f);
                esfera->visualizar();
            glPopMatrix();
        glPopMatrix();

        // Articulación 2 - mismo color que Brazo2
        glPushMatrix();
            glTranslatef(0.0f, dim.alturaBase, 0.0f);
            glRotatef(anguloBrazo1, 0.0f, 0.0f, 1.0f);
            glTranslatef(0.0f, dim.longitudBrazo1, 0.0f);
            glRotatef(anguloBrazo2, 0.0f, 0.0f, 1.0f);
            glTranslatef(0.0f, dim.longitudBrazo2, 0.0f);
            glScalef(dim.radioArticulacion2, dim.radioArticulacion2, dim.radioArticulacion2);
            esfera->visualizar();
        glPopMatrix();

        // Pantalla - Color AMARILLO (255, 255, 0)
        glColor3ub(255, 255, 0);
        glPushMatrix();
            glTranslatef(0.0f, dim.alturaBase, 0.0f);
            glRotatef(anguloBrazo1, 0.0f, 0.0f, 1.0f);
            glTranslatef(0.0f, dim.longitudBrazo1, 0.0f);
            glRotatef(anguloBrazo2, 0.0f, 0.0f, 1.0f);
            glTranslatef(0.0f, dim.longitudBrazo2, 0.0f);
            glRotatef(anguloPantalla, 0.0f, 0.0f, 1.0f);

            // Cuello
            glPushMatrix();
                glScalef(dim.radioCuello, dim.longitudCuello, dim.radioCuello);
                cilindro->visualizar();
            glPopMatrix();

            // Pantalla
            glTranslatef(0.0f, dim.longitudCuello, 0.0f);
            glPushMatrix();
                glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
                glScalef(dim.radioBasePantalla, dim.alturaPantalla, dim.radioBasePantalla);
                cono->visualizar();
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0.0f, -dim.alturaPantalla, 0.0f);
                glScalef(dim.radioBasePantalla, 1.0f, dim.radioBasePantalla);
                disco->visualizar();
            glPopMatrix();
            // Interior y bombilla
            glPushMatrix();
                glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
                glScalef(dim.radioBasePantalla - dim.grosorPantalla, dim.alturaPantalla - dim.grosorPantalla, dim.radioBasePantalla - dim.grosorPantalla);
                cono->visualizar();
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0.0f, -dim.alturaBombilla, 0.0f);
                glScalef(dim.radioBombilla, dim.radioBombilla, dim.radioBombilla);
                esfera->visualizar();
            glPopMatrix();
        glPopMatrix();

    glPopMatrix();
}
