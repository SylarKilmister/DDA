/*Libreria usada solo en Windows - debe ir antes que las dem�s librerias*/
#include<windows.h>
/*Otras librerias necesarias*/
#include<math.h>
#include<iostream>
/*Libreria del OpenGL*/
#include<GL/glut.h>

using namespace std;
/*Declaramos los valores de la proyecci�n en la ventana*/
void iniciarProyecion()
{
    /*A nuestra proyecci�n le colocamos color negro de fondo (rgb negro= 0,0,0)*/
    glClearColor(0.0, 0.0, 0.0, 0.0);
    /*Creamos la proyecci�n*/
    glMatrixMode(GL_PROJECTION);
    /*Definimos los l�mites de nuestra proyecci�n
    de izquierda a derecha que vaya de -40 hasta 40
    igual cantidad de arriba hacia abajo
    */
    gluOrtho2D(-40, 40, -40, 40);
}

/*Primero dibujar la linea sin DDA*/

void dibujarLinea(GLint x0, GLint y0, GLint xf, GLint yf)
{

    /*Dibujar malla
    para que el pixel se vea pintado dentro del cuadro
    aumentamos 0.5 unidades desde el inicio del recorrido
    tanto para x como para y
    asi sucesivamente probar hasta que coincida
    incluso usar la malla en 3d
    */
    glColor3f(0.0, 0.0, 0.0);/*Color negro*/
    glPointSize(1);

    /*usar de preferencia en f (porque el aumento se declar� iniciando en 0.5 mas)*/

    for (float i = -39.5; i < 40; i++)
    {

        glBegin(GL_LINES);
        glVertex3f(i, 40, 1);
        glVertex3f(i, -40, 1);
        glVertex3f(40, i, 1);
        glVertex3f(-40, i, 1);
        glEnd();

    }
    /*Dibujar eje de coordenadas*/
    glColor3f(1.0, 1.0, 1.0);/*Color blanco*/

    /*Eje 'x' y 'y', recordar que va desde -40 hasta 40*/
    glBegin(GL_LINES);
    glVertex2i(40, 0);
    glVertex2i(-40, 0);
    glVertex2i(0, 40);
    glVertex2i(0, -40);
    glEnd();

    /*Eje y, recordar que va desde -40 hasta 40*/
    glBegin(GL_LINES);

    glEnd();

    /*Para cualquier gr�fico que se dibuje generalmente se hace mediante funci�n
    as�*/
    glBegin(GL_LINES);/*Inicio de la funci�n, con el tipo de figura*/
    /*Declaramos colo de la linea*/
    glColor3f(0.0, 0.0, 0.0);/*Color negro en rgb= 0,0,0 y es 3f por ser "float" los parametros*/
    /*Posici�n inicial y final de la linea*/
    glVertex2i(x0, y0);
    glVertex2i(xf, yf);
    glEnd();/*Fin de la funci�n*/
}


void setPixel(GLint x, GLint y)
{
    /*declaramos el color del pixel pintado*/
    glColor3f(1.0, 0.0, 0.0);/*Color rojo*/
    glPointSize(8);/*tama�o del pixel ser� de 5 (al ejecutar se entender� mejor)*/
    /*funcion*/
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

/*Algoritmo DDA*/

void dda(GLint x0, GLint y0, GLint xf, GLint yf)
{
    GLint i;
    float x, y, ax, ay, res;

    /*Primero verificamos si la variaci�n de x es mayor que la de y*/
    if (abs(xf - x0) >= abs(yf - y0))
    {
        res = abs(xf - x0);
    }
    else
    {
        res = abs(yf - y0);
    }

    /*
    en el caso de que varia mas en x, entonces res queda con su valor absoluto
    si y varia mas, entonces res queda con el valor absoluto de y
    ahora los aumentos(ax y ay)
    */

    ax = (xf - x0) / res;
    ay = (yf - y0) / res;

    /*En caso de que res sea el valor absoluto de la variaci�n de x, el ax queda en 1 y ay en la pendiente
    y viceversa si res es el valor absoluto de la variaci�n de y*/

    i = 0;

    x = (float)x0;
    y = (float)y0;

    /*se realiza el casteo para pasar a float los valores, ya que se necesita su resultado en decimales*/

    while (i <= res)
    {

        setPixel(roundf(x), roundf(y));
        cout << roundf(x) << " , " << roundf(y) << endl;
        x = x + ax;
        y = y + ay;
        i++;
    }
}

/*Funci�n que realizar� el pintado*/
void draw(void)
{
    /*LIMPIA BUFFER*/
    glClear(GL_COLOR_BUFFER_BIT);

    /*Declaramos variables*/
    GLint
        x0 = -10,
        y0 = -5,
        xf = 5,
        yf = 35;

    /*Colocamos antes del pintado sin dda por superposici�n*/
    dda(x0, y0, xf, yf);
    dibujarLinea(x0, y0, xf, yf);
    glFlush();/*Pinta lo dibujado*/

}

int main(int argc, char* argv[])
{
    /*Iniciamos Glut*/
    glutInit(&argc, argv);
    /*Modo gr�fico COLORES: RGB*/
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    /*Definimos el tama�o de la ventana*/
    glutInitWindowSize(800, 600);
    /*Definimos posici�n donde se ubicar� en pantalla*/
    glutInitWindowPosition(300, 100);

    /*Crear la ventana que contedr� el lienzo*/
    glutCreateWindow("DDA line");

    iniciarProyecion();
    /*Llamamos la funci�n a dibujar*/
    glutDisplayFunc(draw);
    /*Constante redibujado*/
    glutMainLoop();

}