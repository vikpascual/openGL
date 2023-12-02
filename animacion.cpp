#define PROYECTO "ISGI::S5E01::Cuadrado rebotante"
#include <iostream> // Biblioteca de entrada salida
#include <sstream> // Biblioteca de manejo de strings
#include <cmath> // Biblioteca matematica de C
#include <gl\freeglut.h> // Biblioteca grafica
using namespace std;

static float radio = 10.0; // Radio de giro de la camara
static float zoomDirection = 1; //alejarse o acercarse
static float angulo = 0.0; // Angulo de travelling inicial de la camara
static float ojo[] = { 2,2,radio }; // Posicion inicial de la camara
static float velocidad = 12.0 * 3.1415926 / 180; // radianes/segundo
static const int tasaFPS = 40; // tasa que se quiere como maximo

static int idListaEstrella;
static int idListaCuerpo;
static int idListaCoche;
static int idListaHumano;

static float velocidadBrazos = 0;
static bool acelerar = true;
static float alturaInicialBrazos[] = {-2,-3,-4,-5};
static float direccionInicialBrazos[] = { -1,-1,-1,1 };

static float rotacionPiernas = 0;

static int altura_dientes = 5;//al final nada

static float velocidadRotacionEnganches = 3;
static int rotacionActualEnganches[] = {0,0,0,0};

static float colorBolas[12][3] = {};
static int bolaActual = 0;

static int asientoRotando[12][2] = {};
static int asientoActual = 0;

static int rotacionCentralActual = 0;

static int rotacionCabeza = 0;

void crearListaEstrella() {
	idListaEstrella = glGenLists(1);
	glNewList(idListaEstrella, GL_COMPILE);
	glPushAttrib(GL_CURRENT_BIT);


	/*90° clockwise rotation: (x,y)
	 becomes (y,−x)
	90° counterclockwise rotation: (x,y)
	 becomes (−y,x)
	180° clockwise and counterclockwise rotation: (x,y)
	 becomes (−x,−y)
	270° clockwise rotation: (x,y)
	 becomes (−y,x)
	270° counterclockwise rotation: (x,y)
	 becomes (y,−x)*/



	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < 4; i++) {
		glVertex3f(-1 * sin(i * 2 * 3.1415926 / 3), 1 * cos(i * 2 * 3.1415926 / 3), 0.0);
		glVertex3f(-0.7 * sin(i * 2 * 3.1415926 / 3), 0.7 * cos(i * 2 * 3.1415926 / 3), 0.0);

	}
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < 4; i++) {
		glVertex3f(1 * sin(i * 2 * 3.1415926 / 3), -1 * cos(i * 2 * 3.1415926 / 3), 0.0);
		glVertex3f(0.7 * sin(i * 2 * 3.1415926 / 3), -0.7 * cos(i * 2 * 3.1415926 / 3), 0.0);

	}
	glEnd();
	glPopAttrib();
	glEndList();
	glEnable(GL_DEPTH_TEST);


}

void crearListaCuerpo() {
	idListaCuerpo = glGenLists(1);
	float tamanyo_cuerpo = 0.5;
	glNewList(idListaCuerpo, GL_COMPILE);
	glPushAttrib(GL_CURRENT_BIT);
	

	for (int i = 0; i < 20; ) {
		glBegin(GL_POLYGON);
		glVertex3f(tamanyo_cuerpo * sin(i * 2 * 3.1415926 / 20), tamanyo_cuerpo * cos(i * 2 * 3.1415926 / 20), 0.0);
		glVertex3f(tamanyo_cuerpo * sin(i * 2 * 3.1415926 / 20), tamanyo_cuerpo * cos(i * 2 * 3.1415926 / 20), 1.0);
		i++;
		glVertex3f(tamanyo_cuerpo * sin(i * 2 * 3.1415926 / 20), tamanyo_cuerpo * cos(i * 2 * 3.1415926 / 20), 1.0);
		glVertex3f(tamanyo_cuerpo * sin(i * 2 * 3.1415926 / 20), tamanyo_cuerpo * cos(i * 2 * 3.1415926 / 20), 0.0);
		glEnd();
		//glVertex3f(1 * sin(i * 2 * 3.1415926 / 3), 1 * cos(i * 2 * 3.1415926 / 3), 0.0);
	}
	
	
	glPopAttrib();
	glEndList();
	glEnable(GL_DEPTH_TEST);


}

void crearListaCoche() {
	idListaCoche = glGenLists(1);
	glNewList(idListaCoche, GL_COMPILE);
	glPushAttrib(GL_CURRENT_BIT);
	glColor3f(0.725, 0.478, 0.341);
	float cochesSize = 2;
	glScalef(cochesSize, cochesSize, cochesSize);
	//respaldo

	glPushMatrix();

		glBegin(GL_POLYGON);
		glVertex3f(0, 1, 0);
		glVertex3f(0, 1, 0.1);
		glVertex3f(1, 1, 0.1);
		glVertex3f(1, 1, 0);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(1, 1, 0);
		glVertex3f(1, 1, 0.1);
		glVertex3f(1, 0, 0.1);
		glVertex3f(1, 0, 0);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 0.1);
		glVertex3f(0, 1, 0.1);
		glVertex3f(0, 1, 0);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(0, 1, 0.1);
		glVertex3f(1, 1, 0.1);
		glVertex3f(1, 0, 0.1);
		glVertex3f(0, 0, 0.1);
		glVertex3f(0, 1, 0.1);
		glEnd();
		
		//ancho del respaldo
		
	glPopMatrix();

	//asiento
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
		glBegin(GL_POLYGON);
		glVertex3f(0, 1, 0);
		glVertex3f(0, 1, 0.1);
		glVertex3f(1, 1, 0.1);
		glVertex3f(1, 1, 0);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(1, 1, 0);
		glVertex3f(1, 1, 0.1);
		glVertex3f(1, 0, 0.1);
		glVertex3f(1, 0, 0);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(1, 0, 0);
		glVertex3f(1, 0, 0.1);
		glVertex3f(0, 0, 0.1);
		glVertex3f(0, 0, 0);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 0.1);
		glVertex3f(0, 1, 0.1);
		glVertex3f(0, 1, 0);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(0, 1, 0.1);
		glVertex3f(1, 1, 0.1);
		glVertex3f(1, 0, 0.1);
		glVertex3f(0, 0, 0.1);
		glVertex3f(0, 1, 0.1);
		glEnd();
		glPushMatrix();
		glTranslatef(0,0,-2);
		glScalef(0.5, 0.5, 0.5);
		glCallList(idListaHumano);
		glPopMatrix();


	glPopMatrix();


	glPopAttrib();
	glEndList();
	glEnable(GL_DEPTH_TEST);


}

void crearListaPersona() {
	idListaHumano = glGenLists(1);
	glNewList(idListaHumano, GL_COMPILE);
	glPushAttrib(GL_CURRENT_BIT);
	
	glPushMatrix();
	glTranslatef(1, 1, 0.5);
	//cabeza
	glPushMatrix();
	glColor3f(1, 0.682, 0.788);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();
	//ojo1
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(-0.5, 0.7, 0);
	glScalef(0.3, 0.3, 0.3);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();
	//pupila1
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(-0.5, 1, 0);
	glScalef(0.1, 0.1, 0.1);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();
	//ojo2
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0.5, 0.7, 0);
	glScalef(0.3, 0.3, 0.3);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();
	//pupila2
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(0.5, 1, 0);
	glScalef(0.1, 0.1, 0.1);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();

	//boca
	for (int i = -1; i < 2; i++) {
		glPushMatrix();
		glColor3f(0, 0, 0);
		glTranslatef(0.1*i, 1, 0.3 );
		glScalef(0.1, 0.1, 0.1);
		glutSolidCube(1);
		glPopMatrix();
	}

	//cuerpo
	
	for (int i = 0; i < 3; i++) {
		glPushMatrix();
		glColor3f(1, 1, 0.33);
		glTranslatef(0, 0, i);
		glScalef(1.25, 1.25, 1);
		glCallList(idListaCuerpo);
		glPopMatrix();

	}
	//cadera
	glPushMatrix();
	glColor3f(0, 0, 1);
	glTranslatef(0, 0, 3);
	glScalef(0.7, 0.7, 0.7);
	glutSolidSphere(1,20,20);
	glPopMatrix();
	
	//pierna1
	glPushMatrix();
	int colorPantalon = 0;
	glRotatef(-90, 1, 0, 0);
	//glRotatef(rotacionPiernas, 0, 1, 0);
	//glTranslatef(-5, 0, 0);
	glScalef(0.5, 0.5, 0.5);
	glTranslatef(-0.6,-6.5,0);
	for (int i = 0; i < 3; i++) {
		glPushMatrix();
		if (colorPantalon <=1) {
			glColor3f(0, 0, 1);
			colorPantalon++;
		}
		else {
			glColor3f(1, 0.682, 0.788);
		}
		
		glTranslatef(0, 0, i);
		
		glCallList(idListaCuerpo);
		glPopMatrix();
	}
	glPushMatrix();//rodilla
	glTranslatef(0, 0, 3);
	glScalef(0.6, 0.6, 0.6);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();
	
	glPopMatrix();//finpierna

	//pierna2
	glPushMatrix();
	colorPantalon = 0;
	glRotatef(-90, 1, 0, 0);
	//glRotatef(rotacionPiernas, 0, 1, 0);
	//glTranslatef(-5, 0, 0);
	glScalef(0.5, 0.5, 0.5);
	glTranslatef(0.6, -6.5, 0);
	for (int i = 0; i < 3; i++) {
		glPushMatrix();//rodilla
		if (colorPantalon <= 1) {
			glColor3f(0, 0, 1);
			colorPantalon++;
		}
		else {
			glColor3f(1, 0.682, 0.788);
		}

		glTranslatef(0, 0, i);

		glCallList(idListaCuerpo);
		glPopMatrix();
	}
	glPushMatrix();
	glTranslatef(0, 0, 3);
	glScalef(0.6, 0.6, 0.6);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();

	glPopMatrix();//finpierna

	//espinilla1
	glPushMatrix();
	glScalef(0.5, 0.5, 0.5);
	glTranslatef(-0.6, 3,6.5);
	for (int i = 0; i < 3; i++) {
		glPushMatrix();

		glTranslatef(0, 0, i);

		glCallList(idListaCuerpo);
		glPopMatrix();
	}
	glPushMatrix();//tobillo
	glTranslatef(0, 0, 3);
	glutSolidSphere(0.5, 20, 20);

	glPopMatrix();
	glPopMatrix();//finespinilla

	//espinilla2
	glPushMatrix();
	glScalef(0.5, 0.5, 0.5);
	glTranslatef(0.6, 3, 6.5);
	for (int i = 0; i < 3; i++) {
		glPushMatrix();
		glTranslatef(0, 0, i);

		glCallList(idListaCuerpo);
		glPopMatrix();
	}
	glPushMatrix();//tobillo
	glTranslatef(0, 0, 3);
	glutSolidSphere(0.5, 20, 20);

	glPopMatrix();

	glPopMatrix();//finespinilla


	//hombro1
	glColor3f(1, 0, 0.33);
	glPushMatrix();
	glScalef(0.5, 0.5, 0.5);
	glTranslatef(1.5, 0.25, 2.5);
	glPushMatrix();
	glScalef(0.6, 0.6, 0.6);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();

	//brazo1(biceps)
	glPushMatrix();
	colorPantalon = 0;
	//glRotatef(90, 0, 0, 1);//adelante o atras
	glRotatef(30,0 , -1, 0);//abertura max 180
	glRotatef(180, -1, 0, 0);//arriba,abajo
	//glScalef(0.5, 0.5, 0.5);
	//glTranslatef(1.5, 0.25, 2.5);
	for (int i = 0; i < 2; i++) {
		glPushMatrix();//codo
		if (colorPantalon <= 0) {
			glColor3f(1, 0, 0.33);
			colorPantalon++;
		}
		else {
			glColor3f(1, 0.682, 0.788);
		}

		glTranslatef(0, 0, i);

		glCallList(idListaCuerpo);
		glPopMatrix();
	}
	glPushMatrix();
	glTranslatef(0, 0, 2);
	glScalef(0.6, 0.6, 0.6);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();

	for (int i = 0; i < 2; i++) {
		glPushMatrix();//antebrazo
		glTranslatef(0, 0, 2 + i);

		glCallList(idListaCuerpo);
		glPopMatrix();
	}

	glPushMatrix();
	glTranslatef(0, 0, 4);
	glScalef(0.5, 0.5, 0.5);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();

	glPopMatrix();//fin biceps


	glPopMatrix();

	//hombro2
	glColor3f(1, 0, 0.33);
	glPushMatrix();
	glScalef(0.5, 0.5, 0.5);
	glTranslatef(-1.5, 0.25, 2.5);
	glPushMatrix();
	glScalef(0.6, 0.6, 0.6);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();

	//brazo2(biceps)
	glPushMatrix();
	colorPantalon = 0;

	
	glRotatef(30, 0, 1, 0);//abertura max 180
	glRotatef(180, 1, 0, 0);//arriba,abajo
	//glScalef(0.5, 0.5, 0.5);
	//glTranslatef(1.5, 0.25, 2.5);
	for (int i = 0; i < 2; i++) {
		glPushMatrix();//codo
		if (colorPantalon <= 0) {
			glColor3f(1, 0, 0.33);
			colorPantalon++;
		}
		else {
			glColor3f(1, 0.682, 0.788);
		}

		glTranslatef(0, 0, i);

		glCallList(idListaCuerpo);
		glPopMatrix();
	}
	glPushMatrix();
	glTranslatef(0, 0, 2);
	glScalef(0.6, 0.6, 0.6);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();

	for (int i = 0; i < 2; i++) {
		glPushMatrix();//antebrazo
		glTranslatef(0, 0, 2 + i);

		glCallList(idListaCuerpo);
		glPopMatrix();
	}

	glPushMatrix();
	glTranslatef(0, 0, 4);
	glScalef(0.5, 0.5, 0.5);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();

	glPopMatrix();//fin biceps


	glPopMatrix();

	glPopMatrix();
	glPopAttrib();

	glEndList();
	glEnable(GL_DEPTH_TEST);

}

void dibujarCabezaPulpo() {
	glPushMatrix();
	for (float i = 1; i <= 6; i ++) {
		float mod = i / 10;
		glColor3f(1 + mod, 1 - mod, 0 + mod);
		glRotatef(30, 0, 1, 0);
		glCallList(idListaEstrella);
	}
	glPopMatrix();

	glutWireSphere(1.0, 20, 20);
}

void dibujarCuerpo(){
	for (int i = 1; i < 10; i++) {
		glPushMatrix();
		glRotatef(90, 1, 0, 0);
		glTranslatef(0, 0, i);
		glCallList(idListaCuerpo); // Dibuja una tetera detras
		glPopMatrix();
	}

}
void dibujarBrazos() {
	bolaActual = 0;
	asientoActual = 0;
	for (int j = 0; j < 4; j++) {
		glPushMatrix();

		glRotatef(90*j, 0,1,0);

		glPushMatrix();
			float altura_brazo = alturaInicialBrazos[j];
			float largura_brazo = 5;
			glTranslatef(0, altura_brazo, 0);
			glScalef(0.5, 0.5, 0.5);
			glRotatef(30, -1, 0, 0);
			for (int i = 0; i < largura_brazo; i++) {
				glPushMatrix();
				glTranslatef(0, 0, i);
				glCallList(idListaCuerpo); // Dibuja una tetera detras
				glPopMatrix();
			}
			//posicion de la bola
			glTranslatef(0, 0, largura_brazo);
			//CAMBIAR LAS BOLAS DE CORLOR SIN QUE AFECTE A LOS BRAZOS
			glPushAttrib(GL_CURRENT_BIT);

			glColor3f(colorBolas[bolaActual][0], colorBolas[bolaActual][1], colorBolas[bolaActual][2]);
			bolaActual++;
			glutSolidSphere(1.0, 20, 20);
			glPopAttrib();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0, altura_brazo, 0);
			glScalef(0.5, 0.5, 0.5);
			//glRotatef(0, -1, 0, 0);
			for (int i = 0; i < largura_brazo ; i++) {
				glPushMatrix();
				//teniendo 3 angulos y la coordenada de un punto podemos calcular la Y del "triangulo" que forma el brazo con la bola
				glTranslatef(0, 4 + largura_brazo * sin(60), i + largura_brazo);
				glCallList(idListaCuerpo); // Dibuja una tetera detras
				glPopMatrix();
			}
			//posicion de la bola y gancho
			glTranslatef(0, 4 + largura_brazo * sin(60), largura_brazo + largura_brazo );
			
			//CAMBIAR LAS BOLAS DE CORLOR SIN QUE AFECTE A LOS BRAZOS
			glPushAttrib(GL_CURRENT_BIT);
			glColor3f(colorBolas[bolaActual][0], colorBolas[bolaActual][1], colorBolas[bolaActual][2]);
			bolaActual++;
			glutSolidSphere(1.0, 20, 20);
			glPopAttrib();


			//brazo y bola enganche coches
			for (int i = 0; i < 5; i++) {
				glPushMatrix();
				glRotatef(90, 1, 0, 0);
				glTranslatef(0, 0, i);
				glCallList(idListaCuerpo); // Dibuja una tetera detras
				glPopMatrix();
			}

			glTranslatef(0, -5.5, 0);

			

			//CAMBIAR LAS BOLAS DE CORLOR SIN QUE AFECTE A LOS BRAZOS
			glPushAttrib(GL_CURRENT_BIT);
			glColor3f(1, 0, 0);
			glutSolidSphere(1.0, 20, 20);
			glPopAttrib();

			//ganchos para los coches
			for (int i = 0; i < 3; i++) {
				glPushMatrix();
				glRotatef(120 * i + rotacionActualEnganches[j], 0, 1, 0);

				for (int z = 0; z < 4; z++) {
					glPushMatrix();
					glTranslatef(0, 0, z);
					glCallList(idListaCuerpo);
					glPopMatrix();

				}
				//dibujar coches aqui y personas
				if (asientoRotando[asientoActual][0] != 0) {
					glRotatef(asientoRotando[asientoActual][0] * asientoRotando[asientoActual][1]*4, 0, 0, 1);
					asientoRotando[asientoActual][1]++;//aumentamos el angulo que tiene que rotar
					if (asientoRotando[asientoActual][1] == 90){ //360/4
						asientoRotando[asientoActual][0] = 0;
						asientoRotando[asientoActual][1] = 0;
					}
				}
				asientoActual++;
				
				glTranslatef(-1, 0, 4);
				glPushAttrib(GL_CURRENT_BIT);
				glCallList(idListaCoche);
				glPopAttrib();
				glPopMatrix();

			}

		glPopMatrix();

		

		glPopMatrix();
	}
	

}

void cambiaColorBolasYRotacionAsientos() {
	float valorAleatorio;
	for (int i = 0; i < 12; ++i) {
		for (int j = 0; j < 3; ++j) {
			// Generar un valor aleatorio entre 0.0 y 1.0
			colorBolas[i][j] = static_cast<float>(rand()) / RAND_MAX;
		}
		valorAleatorio = static_cast<float>(rand()) / RAND_MAX; 
		if (asientoRotando[i][0] == 0) {
			if (valorAleatorio <= 0.10) {
				asientoRotando[i][0] = -1; //sentido contrario
				asientoRotando[i][1] = 0; //angulo actual
			}
			else if (valorAleatorio >= 0.90) {
				asientoRotando[i][0] = 1; //sentido normal
				asientoRotando[i][1] = 0; //angulo actual
			}
			else {
				asientoRotando[i][0] = 0; //nada
				asientoRotando[i][1] = 0;
			}
		}
		

	}
}

void muestraFPS()
// Calcula la frecuencia y la muestra en el título de la ventana
// cada segundo
{
	int ahora, tiempo_transcurrido;
	static int antes = 0;
	static int FPS = 0;
	stringstream titulo;
	//Cuenta de llamadas a esta función en el último segundo
	FPS++;
	ahora = glutGet(GLUT_ELAPSED_TIME); //Tiempo transcurrido desde el inicio
	tiempo_transcurrido = ahora - antes; //Tiempo transcurrido desde antes
	if (tiempo_transcurrido > 1000) { //Acaba de rebasar el segundo
		titulo << "FPS: " << FPS; //Se muestra una vez por segundo
		glutSetWindowTitle(titulo.str().c_str());
		antes = ahora; //Ahora ya es antes
		FPS = 0; //Reset del conteo
	}
}
void init()
// Funcion propia de inicializacion
{
	cout << "Version: OpenGL " << glGetString(GL_VERSION) << endl;
	glClearColor(0, 0.1, 0.60,1); // Color de fondo a blanco
	glEnable(GL_DEPTH_TEST); // Habilita visibilidad
}
void display()
// Funcion de atencion al dibujo
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Borra la pantalla
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(ojo[0], ojo[1], ojo[2], 0, 0, 0, 0, 1, 0); // Situa la camara
	
	glPushMatrix();
	glRotatef(-rotacionCentralActual++ * 2, 0, 1, 0);
	glTranslatef(0, 2, 0);

	glPushMatrix(); // matriz cabeza
	glRotatef(rotacionCabeza++ * 2, 1, 0, 0);
	glColor3f(1, 0, 0);
	dibujarCabezaPulpo(); // Dibuja una tetera detras
	glPopMatrix();

	//matriz cuerpo
	glPushMatrix(); 
	glColor3f(1, 0, 1);
	dibujarCuerpo(); // Dibuja una tetera detras
	glPopMatrix();
	
	//matriz brazos
	glPushMatrix(); 
	glColor3f(0, 0, 1);
	//glTranslatef(0, -4, 0);
	//glScalef(0.5,0.5,0.5);
	
	dibujarBrazos(); // Dibuja una tetera detras
	glPopMatrix();

	
	glPopMatrix();

	//suelo
	glPushMatrix();
	glTranslatef(-10, -10, -10);
	glRotatef(90, 1, 0, 0);
	glScalef(20, 20, 20);
	glColor3f(0, 0, 0);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 0, 0);


	glEnd();
	glPopMatrix();

	muestraFPS(); // Hemos dibujado un frame
	glutSwapBuffers(); // Intercambia los buffers
}
void reshape(GLint w, GLint h)
// Funcion de atencion al redimensionamiento
{
	// Usamos toda el area de dibujo
	glViewport(0, 0, w, h);
	// Definimos la camara (matriz de proyeccion)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float razon = (float)w / h;
	/* CAMARA PERSPECTIVA */
	gluPerspective(60, razon, 1, 40);
}
void onTimer(int valor)
// Funcion de atencion al timer periodico
{
	//Calculamos el tiempo transcurrido desde la última vez
	static int segundoActual = 0;
	static int antes = 0;
	int ahora, tiempo_transcurrido;
	ahora = glutGet(GLUT_ELAPSED_TIME);
	if ((int)ahora/1000  > segundoActual) {
		cambiaColorBolasYRotacionAsientos();
		segundoActual++;

		if (acelerar) {
			velocidadBrazos += 0.05;
		}
		else {
			velocidadBrazos -= 0.05;
		}
		if (velocidadBrazos >= 0.2 || velocidadBrazos <= 0 ){
			acelerar = not acelerar;
		}

		std::cout << segundoActual << std::endl;
	}

	//Tiempo transcurrido desde el inicio
	tiempo_transcurrido = ahora - antes; //Tiempo transcurrido desde antes msg
	// angulo = angulo anterior + velocidad x tiempo
	radio += zoomDirection * 0.1;
	ojo[1] += zoomDirection * 0.1;
	if (radio >= 20 || radio <= 10) {
		zoomDirection *= -1;
	}
	angulo += velocidad * tiempo_transcurrido / 1000.0;
	ojo[0] = radio * sin(angulo);
	ojo[2] = radio * cos(angulo);
	antes = ahora;

	
	//Altura de los brazos
	
	for (int i = 0;  i < 4; i++) {
		alturaInicialBrazos[i] = alturaInicialBrazos[i] + direccionInicialBrazos[i] * velocidadBrazos;
		if (alturaInicialBrazos[i] > -2 || alturaInicialBrazos[i] < -6) {
			direccionInicialBrazos[i] = -1 * direccionInicialBrazos[i];
		}
		//depende de si el brazo es par o impar giran en sentido del reloj o al revés
		if (i % 2 == 0){
			rotacionActualEnganches[i] = rotacionActualEnganches[i] + velocidadRotacionEnganches;
			
		}else {
			rotacionActualEnganches[i] = rotacionActualEnganches[i] - velocidadRotacionEnganches;

		}
		
	}
	
	glutTimerFunc(1000 / tasaFPS, onTimer, tasaFPS); // Se encola un nuevo timer
	glutPostRedisplay(); // Se manda el dibujo
}
void main(int argc, char** argv)
// Programa principal
{
	glutInit(&argc, argv); // Inicializacion de GLUT
	std::srand(static_cast<unsigned>(std::time(nullptr)));//para los colores y demás
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Alta de buffers a usar
	glutInitWindowSize(400, 400); // Tamanyo inicial de la ventana
	glutCreateWindow(PROYECTO); // Creacion de la ventana con su titulo
	std::cout << PROYECTO << " running" << std::endl; // Mensaje por consola
	crearListaEstrella();
	crearListaCuerpo();
	crearListaPersona();
	crearListaCoche();
	crearListaPersona();
	glutDisplayFunc(display); // Alta de la funcion de atencion a display
	glutReshapeFunc(reshape); // Alta de la funcion de atencion a reshape
	glutTimerFunc(1000 / tasaFPS, onTimer, tasaFPS); // Alta de la funcion de atencion al timer
	init(); // Inicializacion propia
	glutMainLoop();
}