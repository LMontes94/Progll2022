#include <sys/timeb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>                   // Libreria de utilidades de OpenGL
#include <GL/gl.h>
#include <GL/glu.h>

#define LIBRE 0
#define PEON 1
#define TORRE 2
#define CABALLO 3
#define ARFIL 4
#define REINA 5
#define REY 6

#define BLANCA 0
#define NEGRA 1


/********************* DECLARACION DE VARIABLES GOLBALES ***********************/

// Variables para Display Lists
static GLint TableroNegro, TableroBlanco, PeonNegro, PeonBlanco, TorreNegro, TorreBlanco,
CaballoNegro, CaballoBlanco, ArfilNegro, ArfilBlanco, ReinaNegro, ReinaBlanco,
ReyNegro, ReyBlanco, Borde;

// Posiciones de cámara
float D=120.0;   // Distancia de la camara al modelo
static GLfloat view_rotx=40.0, view_roty=90.0, view_rotz=0.0;   // Rotacion de la camara

// Tamaño ventana
static float viewX=600, viewY=600;      // Tamaño del viewport (ventanaX) en pixels
static float vofx=0.0,vofy=0.0;         // Desplazamiento ventana

// Colores
float blanco[4]={0.9,0.9,0.9,0.0};
float negro[4]={0.25,0.25,0.25,0.0};
float marron[4]={0.5,0.3,0.3,0.0};

// Estructura para almacenar tablero de juego
typedef struct {
        int ficha;
	int color;
        } TABLERO_JUEGO;
TABLERO_JUEGO tablero[8][8];

// Datos selección
int seleccionado=0;
int SELECT_pos_i_inicial, SELECT_pos_j_inicial, SELECT_pos_i_final, SELECT_pos_j_final;
int turno;

// Otras variables
int Animando_Turno=0;
int jaque;
char mensaje[50];

// Datos para menus
static int menu;     // Identificador del menu glut
typedef enum{JUEGO_NUEVO,SALIR} opciones_menu;  // Ident. de opciones del menu

// Datos para raton
int RatonPulsado = GL_FALSE;    // Contiene estado botones del raton
int Xref=0, Yref=0;             // Ultima posicion del raton



/************************** GEOMETRIA ****************************/
// Construye una caja con un vertice en origen y otro en (x,y,z)
static void Box( GLfloat x, GLfloat y, GLfloat z )
{
   /* Caras transversales */
   glBegin( GL_QUAD_STRIP );{
      glNormal3f( 0.0, 0.0, -1.0 );   /* Vertical hacia atras */
      glVertex3f( x, 0, 0 );
      glVertex3f( 0, 0, 0 );
      glVertex3f( x, y, 0 );
      glVertex3f( 0, y, 0 );
      glNormal3f( 0.0, 1.0, 0.0 );       /* Superior, horizontal */
      glVertex3f( x, y, z );
      glVertex3f( 0, y, z );
      glNormal3f( 0.0, 0.0, 1.0 );       /*Vertical delantera*/
      glVertex3f( x, 0, z );
      glVertex3f( 0, 0, z );
      glNormal3f( 0.0, -1.0, 0.0 );       /*Inferior */
      glVertex3f( x, 0, 0 );
      glVertex3f( 0, 0, 0 );  }
    glEnd();

   /* Costados */
   glBegin( GL_QUADS );{
      glNormal3f( 1.0, 0.0, 0.0 );
      glVertex3f( x, 0, 0 );
      glVertex3f( x, y, 0 );
      glVertex3f( x, y, z );
      glVertex3f( x, 0, z ); }
   glEnd();

   glBegin( GL_QUADS );{
      glNormal3f( -1.0, 0.0, 0.0 );
      glVertex3f( 0, 0, 0 );
      glVertex3f( 0, 0, z );
      glVertex3f( 0, y, z );
      glVertex3f( 0, y, 0 ); }
   glEnd();

}


// Construye un Disco
void Disco(GLfloat radio)
{
  GLUquadricObj *qobj;
  qobj = gluNewQuadric();
  gluDisk(qobj,0.0,radio,10,10);
  gluDeleteQuadric(qobj);
}


// Construye un Cilindro
void Cilindro(GLfloat radio,GLfloat altura)
{
  GLUquadricObj *qobj;
  // cilindro
  glPushMatrix();
	glTranslatef(0.0,altura-1,0.0);
    	glPushMatrix();
  		qobj = gluNewQuadric();
        	glRotatef(90.0,1.0,0.0,0.0);
        	glTranslatef(0.0,0.0,-1.0);
        	gluCylinder(qobj,radio,radio,altura,10,10);
        	gluDeleteQuadric(qobj);
    	glPopMatrix();
  glPopMatrix();
  // tapa superior
  glPushMatrix();
	glTranslatef(0.0,altura,0.0);
	glRotatef(-90.0,1.0,0.0,0.0);
	Disco(radio);
  glPopMatrix();
  // tapa inferior
  glPushMatrix();
	glRotatef(-90.0,1.0,0.0,0.0);
	Disco(radio);
  glPopMatrix();
}


// Construye una Esfera
void Esfera(GLfloat radio)
{
  GLUquadricObj *qobj;
  qobj = gluNewQuadric();
  gluSphere(qobj,radio,10,10);
  gluDeleteQuadric(qobj);
}


// Construye la Base de las piezas
void Base(int altura)
{
	Cilindro(3.0,1.0);
	glPushMatrix();
		glTranslatef(0.0,1.0,0.0);
		Cilindro(1.0,altura);
	glPopMatrix();
}


// Construye la pieza Peon
void Peon()
{
	glPushMatrix();
		glScalef(1.0,0.9,1.0);
		Base(6.0);
		glPushMatrix();
			glTranslatef(0.0,7.0,0.0);
			Cilindro(2.0,0.5);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0,9.0,0.0);
			Esfera(2.0);
		glPopMatrix();
	glPopMatrix();
}


// Construye la pieza Torre
void Torre()
{
	Base(6.0);
	glPushMatrix();
		glTranslatef(-2.0,7.0,-2.0);
		Box(4.0,2.0,4.0);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-2.0,9.0,-2.0);
		Box(1.0,1.0,1.0);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-2.0,9.0,1.0);
		Box(1.0,1.0,1.0);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(1.0,9.0,1.0);
		Box(1.0,1.0,1.0);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(1.0,9.0,-2.0);
		Box(1.0,1.0,1.0);
	glPopMatrix();
}


// Construye la pieza Caballo
void Caballo()
{
	Base(6.0);
	glPushMatrix();
		glTranslatef(-2.0,4.5,-1.5);
		Box(4.0,2.5,3.0);
		glTranslatef(-2.0,2.5,0.0);
		Box(6.0,3.5,3.0);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-2.0,8.5,-1.5);
		Esfera(1.0);
		glTranslatef(0.0,0.0,3.0);
		Esfera(1.0);
	glPopMatrix();
}


// Construye la pieza Arfil
void Arfil()
{
	Base(6.0);
	glPushMatrix();
		glTranslatef(0.0,7.0,0.0);
		glScalef(1.0,1.25,1.0);
		Esfera(2.0);
	glPopMatrix();
	glPushMatrix();
  		glTranslatef(0.0,9.5,0.0);
  		Esfera(1.0);
	glPopMatrix();
}


// Construye la pieza Reina
void Reina()
{
	glPushMatrix();
		glScalef(1.0,1.25,1.0);
		Base(6.0);
		glPushMatrix();
			glTranslatef(0.0,7.0,0.0);
			Cilindro(2.0,2.0);
			glTranslatef(0.0,1.0,0.0);
			Cilindro(2.5,0.5);
  			Esfera(2.0);
			glTranslatef(0.0,1.5,0.0);
			Esfera(1.0);
		glPopMatrix();
	glPopMatrix();
}


// Construye la pieza Rey
void Rey()
{
	glPushMatrix();
		glScalef(1.0,1.25,1.0);
		Base(6.0);
		glPushMatrix();
			glTranslatef(0.0,7.0,0.0);
			Cilindro(2.0,1.0);
			glTranslatef(0.0,1.0,0.0);
			Cilindro(2.5,1.0);
			glTranslatef(0.0,1.0,0.0);
  			Esfera(2.0);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-0.5,10.0,-0.25);
			Box(1.0,2.5,0.5);
			glTranslatef(-0.25,1.0,0.0);
			Box(1.5,1.0,0.5);
		glPopMatrix();
	glPopMatrix();
}



/**************************** MOVIMIENTOS DE LAS PIEZAS **********************/
// Movimientos Arfil -> movimientos diagonales de cualquier longitud
int** Movimientos_Arfil(int *n_movs, int pos_i_inicial, int pos_j_inicial)
{
  int movimientos[13][2];
  int **movs;
  int pos_i_final, pos_j_final, i, j;
  int color=tablero[pos_i_inicial][pos_j_inicial].color;
  int obstaculo;
  
  // Movimientos diagonal superior derecha
  if((pos_i_inicial<7)&&(pos_j_inicial<7))
  	{
	obstaculo = 0;
	for(i=pos_i_inicial+1,j=pos_j_inicial+1; i<8 && j<8 && !obstaculo; i++,j++)
		{
		pos_i_final = i;
		pos_j_final = j;
		if(tablero[pos_i_final][pos_j_final].ficha!=LIBRE) obstaculo=1;
		if((obstaculo==0)||(tablero[pos_i_final][pos_j_final].color!=color))
			{
			movimientos[*n_movs][0]=pos_i_final;
			movimientos[*n_movs][1]=pos_j_final;
			*n_movs = *n_movs+1;
			}
		}
	}

  // Movimientos diagonal inferior derecha
  if((pos_i_inicial>0)&&(pos_j_inicial<7))
  	{
	obstaculo = 0;
	for(i=pos_i_inicial-1,j=pos_j_inicial+1; i>=0 && j<8 && !obstaculo; i--,j++)
		{
		pos_i_final = i;
		pos_j_final = j;
		if(tablero[pos_i_final][pos_j_final].ficha!=LIBRE) obstaculo=1;
		if((obstaculo==0)||(tablero[pos_i_final][pos_j_final].color!=color))
			{
			movimientos[*n_movs][0]=pos_i_final;
			movimientos[*n_movs][1]=pos_j_final;
			*n_movs = *n_movs+1;
			}
		}
	}

  // Movimientos diagonal inferior izquierda
  if((pos_i_inicial>0)&&(pos_j_inicial>0))
  	{
	obstaculo = 0;
	for(i=pos_i_inicial-1,j=pos_j_inicial-1; i>=0 && j>=0 && !obstaculo; i--,j--)
		{
		pos_i_final = i;
		pos_j_final = j;
		if(tablero[pos_i_final][pos_j_final].ficha!=LIBRE) obstaculo=1;
		if((obstaculo==0)||(tablero[pos_i_final][pos_j_final].color!=color))
			{
			movimientos[*n_movs][0]=pos_i_final;
			movimientos[*n_movs][1]=pos_j_final;
			*n_movs = *n_movs+1;
			}
		}
	}

  // Movimientos diagonal superior izquierda
  if((pos_i_inicial<7)&&(pos_j_inicial>0))
  	{
	obstaculo = 0;
	for(i=pos_i_inicial+1,j=pos_j_inicial-1; i<8 && j>=0 && !obstaculo; i++,j--)
		{
		pos_i_final = i;
		pos_j_final = j;
		if(tablero[pos_i_final][pos_j_final].ficha!=LIBRE) obstaculo=1;
		if((obstaculo==0)||(tablero[pos_i_final][pos_j_final].color!=color))
			{
			movimientos[*n_movs][0]=pos_i_final;
			movimientos[*n_movs][1]=pos_j_final;
			*n_movs = *n_movs+1;
			}
		}
	}

  if(*n_movs!=0) {
  movs = (int **) malloc (*n_movs * sizeof(int *));//printf("\n");
  for(i=0;i<*n_movs;i++)
  	{
  	movs[i] = (int *) malloc(2*sizeof(int));
	movs[i][0] = movimientos[i][0];
	movs[i][1] = movimientos[i][1];
	//printf("\n%d %d",movs[i][0],movs[i][1]);
	}
  }
  return movs;
}


// Movimientos Torre -> movimientos verticales y horizontales de cualquier longitud
int** Movimientos_Torre(int *n_movs, int pos_i_inicial, int pos_j_inicial)
{
  int movimientos[14][2];
  int **movs;
  int pos_i_final, pos_j_final, i;
  int color=tablero[pos_i_inicial][pos_j_inicial].color;
  int obstaculo;

  // Movimientos al ESTE
  if(pos_j_inicial<7)
  	{
	obstaculo = 0;
	pos_i_final=pos_i_inicial;
	for(i=pos_j_inicial+1; i<8  && !obstaculo; i++)
		{
		pos_j_final = i;
		if(tablero[pos_i_final][pos_j_final].ficha!=LIBRE) obstaculo=1;
		if((obstaculo==0)||(tablero[pos_i_final][pos_j_final].color!=color))
			{
			movimientos[*n_movs][0]=pos_i_final;
			movimientos[*n_movs][1]=pos_j_final;
			*n_movs = *n_movs+1;
			}
		}
	}

  // Movimientos al OESTE
  if(pos_j_inicial>0)
  	{
	obstaculo = 0;
	pos_i_final=pos_i_inicial;
	for(i=pos_j_inicial-1; i>=0  && !obstaculo; i--)
		{
		pos_j_final = i;
		if(tablero[pos_i_final][pos_j_final].ficha!=LIBRE) obstaculo=1;
		if((obstaculo==0)||(tablero[pos_i_final][pos_j_final].color!=color))
			{
			movimientos[*n_movs][0]=pos_i_final;
			movimientos[*n_movs][1]=pos_j_final;
			*n_movs = *n_movs+1;
			}
		}
	}
	
  // Movimientos al NORTE
  if(pos_i_inicial<7)
  	{
	obstaculo = 0;
	pos_j_final=pos_j_inicial;
	for(i=pos_i_inicial+1; i<8  && !obstaculo; i++)
		{
		pos_i_final = i;
		if(tablero[pos_i_final][pos_j_final].ficha!=LIBRE) obstaculo=1;
		if((obstaculo==0)||(tablero[pos_i_final][pos_j_final].color!=color))
			{
			movimientos[*n_movs][0]=pos_i_final;
			movimientos[*n_movs][1]=pos_j_final;
			*n_movs = *n_movs+1;
			}
		}
	}
	
  // Movimientos al SUR
  if(pos_i_inicial>0)
  	{
	obstaculo = 0;
	pos_j_final=pos_j_inicial;
	for(i=pos_i_inicial-1; i>=0  && !obstaculo; i--)
		{
		pos_i_final = i;
		if(tablero[pos_i_final][pos_j_final].ficha!=LIBRE) obstaculo=1;
		if((obstaculo==0)||(tablero[pos_i_final][pos_j_final].color!=color))
			{
			movimientos[*n_movs][0]=pos_i_final;
			movimientos[*n_movs][1]=pos_j_final;
			*n_movs = *n_movs+1;
			}
		}
	}

  if(*n_movs!=0) {
  movs = (int **) malloc (*n_movs * sizeof(int *));//printf("\n");
  for(i=0;i<*n_movs;i++)
  	{
  	movs[i] = (int *) malloc(2*sizeof(int));
	movs[i][0] = movimientos[i][0];
	movs[i][1] = movimientos[i][1];
	//printf("\n%d %d",movs[i][0],movs[i][1]);
	}
  }
  return movs;
}


// Movimientos Caballo -> avanza de 2 casillas en horizontal o vertical y gira
// en ángulo recto para pararse en la casilla de la izquierda o derecha
int** Movimientos_Caballo(int *n_movs, int pos_i_inicial, int pos_j_inicial)
{
  int movimientos[8][2];
  int **movs;
  int pos_i_final, pos_j_final, i;
  int color=tablero[pos_i_inicial][pos_j_inicial].color;

  // Un desplazamiento al ESTE
  pos_j_final = pos_j_inicial+1;
  if(pos_j_final<8)
  	{
	// Dos desplazamientos al NORTE
	pos_i_final = pos_i_inicial + 2;
	if(pos_i_final<8)
		if((tablero[pos_i_final][pos_j_final].ficha==LIBRE)||(tablero[pos_i_final][pos_j_final].color!=color))
			{
			movimientos[*n_movs][0]=pos_i_final;
			movimientos[*n_movs][1]=pos_j_final;
			*n_movs = *n_movs+1;
			}
	// Dos desplazamientos al SUR
	pos_i_final = pos_i_inicial - 2;
	if(pos_i_final>=0)
		if((tablero[pos_i_final][pos_j_final].ficha==LIBRE)||(tablero[pos_i_final][pos_j_final].color!=color))
			{
			movimientos[*n_movs][0]=pos_i_final;
			movimientos[*n_movs][1]=pos_j_final;
			*n_movs = *n_movs+1;
			}
	}

  // Un desplazamiento al OESTE
  pos_j_final = pos_j_inicial-1;
  if(pos_j_final>=0)
  	{
	// Dos desplazamientos al NORTE
	pos_i_final = pos_i_inicial + 2;
	if(pos_i_final<8)
		if((tablero[pos_i_final][pos_j_final].ficha==LIBRE)||(tablero[pos_i_final][pos_j_final].color!=color))
			{
			movimientos[*n_movs][0]=pos_i_final;
			movimientos[*n_movs][1]=pos_j_final;
			*n_movs = *n_movs+1;
			}
	// Dos desplazamientos al SUR
	pos_i_final = pos_i_inicial - 2;
	if(pos_i_final>=0)
		if((tablero[pos_i_final][pos_j_final].ficha==LIBRE)||(tablero[pos_i_final][pos_j_final].color!=color))
			{
			movimientos[*n_movs][0]=pos_i_final;
			movimientos[*n_movs][1]=pos_j_final;
			*n_movs = *n_movs+1;
			}
	}

  // Dos desplazamientos al ESTE
  pos_j_final = pos_j_inicial+2;
  if(pos_j_final<8)
  	{
	// Un desplazamiento al NORTE
	pos_i_final = pos_i_inicial + 1;
	if(pos_i_final<8)
		if((tablero[pos_i_final][pos_j_final].ficha==LIBRE)||(tablero[pos_i_final][pos_j_final].color!=color))
			{
			movimientos[*n_movs][0]=pos_i_final;
			movimientos[*n_movs][1]=pos_j_final;
			*n_movs = *n_movs+1;
			}
	// Un desplazamiento al SUR
	pos_i_final = pos_i_inicial - 1;
	if(pos_i_final>=0)
		if((tablero[pos_i_final][pos_j_final].ficha==LIBRE)||(tablero[pos_i_final][pos_j_final].color!=color))
			{
			movimientos[*n_movs][0]=pos_i_final;
			movimientos[*n_movs][1]=pos_j_final;
			*n_movs = *n_movs+1;
			}
	}

  // Dos desplazamientos al OESTE
  pos_j_final = pos_j_inicial-2;
  if(pos_j_final>=0)
  	{
	// Un desplazamiento al NORTE
	pos_i_final = pos_i_inicial + 1;
	if(pos_i_final<8)
		if((tablero[pos_i_final][pos_j_final].ficha==LIBRE)||(tablero[pos_i_final][pos_j_final].color!=color))
			{
			movimientos[*n_movs][0]=pos_i_final;
			movimientos[*n_movs][1]=pos_j_final;
			*n_movs = *n_movs+1;
			}
	// Un desplazamiento al SUR
	pos_i_final = pos_i_inicial - 1;
	if(pos_i_final>=0)
		if((tablero[pos_i_final][pos_j_final].ficha==LIBRE)||(tablero[pos_i_final][pos_j_final].color!=color))
			{
			movimientos[*n_movs][0]=pos_i_final;
			movimientos[*n_movs][1]=pos_j_final;
			*n_movs = *n_movs+1;
			}
	}


  if(*n_movs!=0) {
  movs = (int **) malloc (*n_movs * sizeof(int *));//printf("\n");
  for(i=0;i<*n_movs;i++)
  	{
  	movs[i] = (int *) malloc(2*sizeof(int));
	movs[i][0] = movimientos[i][0];
	movs[i][1] = movimientos[i][1];
	//printf("\n%d %d",movs[i][0],movs[i][1]);
	}
  }
  return movs;
}


// Movimientos Reina -> movimientos torre + movimientos arfil
int** Movimientos_Reina(int *n_movs, int pos_i_inicial, int pos_j_inicial)
{
  int **movs, **movs1, **movs2;
  int n_movs1=0, n_movs2=0, i;

  movs1=Movimientos_Torre(&n_movs1, pos_i_inicial, pos_j_inicial);
  movs2=Movimientos_Arfil(&n_movs2, pos_i_inicial, pos_j_inicial);

  *n_movs=n_movs1+n_movs2;

  if(*n_movs!=0) {
  movs = (int **) malloc (*n_movs * sizeof(int *));


  if(n_movs1!=0) {
  for(i=0;i<n_movs1;i++)
  	{
  	movs[i] = (int *) malloc(2*sizeof(int));
	movs[i][0] = movs1[i][0];
	movs[i][1] = movs1[i][1];
	free(movs1[i]);
	}
  free(movs1);
  } // end movs1

  if(n_movs2!=0) {
  for(i=0;i<n_movs2;i++)
  	{
  	movs[i+n_movs1] = (int *) malloc(2*sizeof(int));
	movs[i+n_movs1][0] = movs2[i][0];
	movs[i+n_movs1][1] = movs2[i][1];
	free(movs2[i]);
	}
  free(movs2);
  } // end movs2
  } // end movs principal

  return movs;
}


// Movimientos Rey -> en cualquier dirección pero de una sola casilla
int** Movimientos_Rey(int *n_movs, int pos_i_inicial, int pos_j_inicial)
{
  int movimientos[8][2];
  int **movs;
  int pos_i_final, pos_j_final, i;
  int color=tablero[pos_i_inicial][pos_j_inicial].color;
  
  // Movimiento al ESTE
  if(pos_j_inicial<7)
  	{
	pos_i_final=pos_i_inicial;
	pos_j_final=pos_j_inicial+1;
	if((tablero[pos_i_final][pos_j_final].ficha==LIBRE)||(tablero[pos_i_final][pos_j_final].color!=color))
		{
		movimientos[*n_movs][0]=pos_i_final;
		movimientos[*n_movs][1]=pos_j_final;
		*n_movs = *n_movs+1;
		}
	}

  // Movimiento al OESTE
  if(pos_j_inicial>0)
  	{
	pos_i_final=pos_i_inicial;
	pos_j_final=pos_j_inicial-1;
	if((tablero[pos_i_final][pos_j_final].ficha==LIBRE)||(tablero[pos_i_final][pos_j_final].color!=color))
		{
		movimientos[*n_movs][0]=pos_i_final;
		movimientos[*n_movs][1]=pos_j_final;
		*n_movs = *n_movs+1;
		}
	}
	
  // Movimiento al NORTE
  if(pos_i_inicial<7)
  	{
	pos_j_final=pos_j_inicial;
	pos_i_final=pos_i_inicial+1;
	if((tablero[pos_i_final][pos_j_final].ficha==LIBRE)||(tablero[pos_i_final][pos_j_final].color!=color))
		{
		movimientos[*n_movs][0]=pos_i_final;
		movimientos[*n_movs][1]=pos_j_final;
		*n_movs = *n_movs+1;
		}
	}
	
  // Movimiento al SUR
  if(pos_i_inicial>0)
  	{
	pos_j_final=pos_j_inicial;
	pos_i_final=pos_i_inicial-1;
	if((tablero[pos_i_final][pos_j_final].ficha==LIBRE)||(tablero[pos_i_final][pos_j_final].color!=color))
		{
		movimientos[*n_movs][0]=pos_i_final;
		movimientos[*n_movs][1]=pos_j_final;
		*n_movs = *n_movs+1;
		}
	}
	
  // Movimiento diagonal superior derecha
  if((pos_i_inicial<7)&&(pos_j_inicial<7))
  	{
	pos_i_final=pos_i_inicial+1;
	pos_j_final=pos_j_inicial+1;
	if((tablero[pos_i_final][pos_j_final].ficha==LIBRE)||(tablero[pos_i_final][pos_j_final].color!=color))
		{
		movimientos[*n_movs][0]=pos_i_final;
		movimientos[*n_movs][1]=pos_j_final;
		*n_movs = *n_movs+1;
		}
	}

  // Movimiento diagonal inferior derecha
  if((pos_i_inicial>0)&&(pos_j_inicial<7))
  	{
	pos_i_final=pos_i_inicial-1;
	pos_j_final=pos_j_inicial+1;
	if((tablero[pos_i_final][pos_j_final].ficha==LIBRE)||(tablero[pos_i_final][pos_j_final].color!=color))
		{
		movimientos[*n_movs][0]=pos_i_final;
		movimientos[*n_movs][1]=pos_j_final;
		*n_movs = *n_movs+1;
		}
	}

  // Movimiento diagonal inferior izquierda
  if((pos_i_inicial>0)&&(pos_j_inicial>0))
  	{
	pos_i_final=pos_i_inicial-1;
	pos_j_final=pos_j_inicial-1;
	if((tablero[pos_i_final][pos_j_final].ficha==LIBRE)||(tablero[pos_i_final][pos_j_final].color!=color))
		{
		movimientos[*n_movs][0]=pos_i_final;
		movimientos[*n_movs][1]=pos_j_final;
		*n_movs = *n_movs+1;
		}
	}

  // Movimiento diagonal superior izquierda
  if((pos_i_inicial<7)&&(pos_j_inicial>0))
  	{
	pos_i_final=pos_i_inicial+1;
	pos_j_final=pos_j_inicial-1;
	if((tablero[pos_i_final][pos_j_final].ficha==LIBRE)||(tablero[pos_i_final][pos_j_final].color!=color))
		{
		movimientos[*n_movs][0]=pos_i_final;
		movimientos[*n_movs][1]=pos_j_final;
		*n_movs = *n_movs+1;
		}
	}

  if(*n_movs!=0) {
  movs = (int **) malloc (*n_movs * sizeof(int *));//printf("\n");
  for(i=0;i<*n_movs;i++)
  	{
  	movs[i] = (int *) malloc(2*sizeof(int));
	movs[i][0] = movimientos[i][0];
	movs[i][1] = movimientos[i][1];
	//printf("\n%d %d",movs[i][0],movs[i][1]);
	}
  }
  return movs;
}


// Movimientos Peon -> una casilla al frente. Si aún no ha jugado, puede avanzar
// en dos casillas. Debe comer en diagonal.
int** Movimientos_Peon(int *n_movs, int pos_i_inicial, int pos_j_inicial)
{
  int movimientos[3][2];
  int **movs;
  int pos_i_final, pos_j_final, i;
  int color=tablero[pos_i_inicial][pos_j_inicial].color;
  
  if(color==BLANCA)
  	{
	// Movimiento al NORTE
  	if(pos_i_inicial<7)
		{
		pos_j_final=pos_j_inicial;
		pos_i_final=pos_i_inicial+1;
		if(tablero[pos_i_final][pos_j_final].ficha==LIBRE)
			{
			movimientos[*n_movs][0]=pos_i_final;
			movimientos[*n_movs][1]=pos_j_final;
			*n_movs = *n_movs+1;
			// Si aún no se ha movido puede avanzar en dos posiciones
			if(pos_i_inicial==1)
				{
				pos_i_final++;
				if(tablero[pos_i_final][pos_j_final].ficha==LIBRE)
					{
					movimientos[*n_movs][0]=pos_i_final;
					movimientos[*n_movs][1]=pos_j_final;
					*n_movs = *n_movs+1;
					}
				}
			}
		}
	// Movimientos diagonales (sólo para comer)
	// Movimiento diagonal superior derecha
  	if((pos_i_inicial<7)&&(pos_j_inicial<7))
  		{
		pos_i_final=pos_i_inicial+1;
		pos_j_final=pos_j_inicial+1;
		if((tablero[pos_i_final][pos_j_final].color!=color)&&(tablero[pos_i_final][pos_j_final].ficha!=LIBRE))
			{
			movimientos[*n_movs][0]=pos_i_final;
			movimientos[*n_movs][1]=pos_j_final;
			*n_movs = *n_movs+1;
			}
		}
	// Movimiento diagonal superior izquierda
  	if((pos_i_inicial<7)&&(pos_j_inicial>0))
  		{
		pos_i_final=pos_i_inicial+1;
		pos_j_final=pos_j_inicial-1;
		if((tablero[pos_i_final][pos_j_final].color!=color)&&(tablero[pos_i_final][pos_j_final].ficha!=LIBRE))
			{
			movimientos[*n_movs][0]=pos_i_final;
			movimientos[*n_movs][1]=pos_j_final;
			*n_movs = *n_movs+1;
			}
		}
	}

  else  // ficha NEGRA
  	{
	 // Movimiento al SUR
  	if(pos_i_inicial>0)
  		{
		pos_j_final=pos_j_inicial;
		pos_i_final=pos_i_inicial-1;
		if(tablero[pos_i_final][pos_j_final].ficha==LIBRE)
			{
			movimientos[*n_movs][0]=pos_i_final;
			movimientos[*n_movs][1]=pos_j_final;
			*n_movs = *n_movs+1;
			// Si aún no se ha movido puede avanzar en dos posiciones
			if(pos_i_inicial==6)
				{
				pos_i_final--;
				if(tablero[pos_i_final][pos_j_final].ficha==LIBRE)
					{
					movimientos[*n_movs][0]=pos_i_final;
					movimientos[*n_movs][1]=pos_j_final;
					*n_movs = *n_movs+1;
					}
				}
			}
		}
	// Movimientos diagonales (sólo para comer)
	// Movimiento diagonal inferior derecha
  	if((pos_i_inicial>0)&&(pos_j_inicial<7))
  		{
		pos_i_final=pos_i_inicial-1;
		pos_j_final=pos_j_inicial+1;
		if((tablero[pos_i_final][pos_j_final].color!=color)&&(tablero[pos_i_final][pos_j_final].ficha!=LIBRE))
			{
			movimientos[*n_movs][0]=pos_i_final;
			movimientos[*n_movs][1]=pos_j_final;
			*n_movs = *n_movs+1;
			}
		}
  	// Movimiento diagonal inferior izquierda
  	if((pos_i_inicial>0)&&(pos_j_inicial>0))
  		{
		pos_i_final=pos_i_inicial-1;
		pos_j_final=pos_j_inicial-1;
		if((tablero[pos_i_final][pos_j_final].color!=color)&&(tablero[pos_i_final][pos_j_final].ficha!=LIBRE))
			{
			movimientos[*n_movs][0]=pos_i_final;
			movimientos[*n_movs][1]=pos_j_final;
			*n_movs = *n_movs+1;
			}
		}
	}

  if(*n_movs!=0) {
  movs = (int **) malloc (*n_movs * sizeof(int *));//printf("\n");
  for(i=0;i<*n_movs;i++)
  	{
  	movs[i] = (int *) malloc(2*sizeof(int));
	movs[i][0] = movimientos[i][0];
	movs[i][1] = movimientos[i][1];
	//printf("\n%d %d",movs[i][0],movs[i][1]);
	}
  }
  return movs;
}



/***************** COMPROBACIONES DE JAQUE Y JAQUE MATE ********************/
/* Comprueba si el rey en posición 'pos_i_rey, pos_j_rey' está en jaque, devuelve:
   0 -> si no lo está
   1 -> si está en jaque
*/
int jaque_aux(int pos_i_rey,int pos_j_rey)
{
 int i,j,k,en_jaque=0;
 int **movs, n_movs;
 int color=tablero[pos_i_rey][pos_j_rey].color;

 for(i=0;i<8;i++)
   for(j=0;j<8;j++)
   	{
	if((tablero[i][j].ficha!=LIBRE)&&(tablero[i][j].color!=color))
		{
		n_movs=0;
		switch(tablero[i][j].ficha) {
  		case PEON:    movs=Movimientos_Peon(&n_movs,i,j);
		     	      break;
		case TORRE:   movs=Movimientos_Torre(&n_movs,i,j);
		    	      break;
		case CABALLO: movs=Movimientos_Caballo(&n_movs,i,j);
		     	      break;
		case ARFIL:   movs=Movimientos_Arfil(&n_movs,i,j);
			      break;
		case REINA:   movs=Movimientos_Reina(&n_movs,i,j);
			      break;
		case REY:     movs=Movimientos_Rey(&n_movs,i,j);
			      break; }

		for(k=0;k<n_movs && !en_jaque;k++)
			if((movs[k][0]==pos_i_rey)&&(movs[k][1]==pos_j_rey))
				en_jaque=1;

  		if(n_movs!=0) {
  			for(k=0;k<n_movs;k++)
  			free(movs[k]);
  		free(movs); }
		}
	}
	
  return en_jaque;
}


/* Comprueba si el rey 'color' está en JAQUE MATE, devuelve:
   0 -> si no lo está
   1 -> si está en jaque
   2 -> si está en jaque mate
*/
int jaque_mate(int color)
{
 int i,j,aux, en_jaque=0, pos_i_rey, pos_j_rey;
 int **movs, n_movs;
 int aux_ficha, aux_color;

 // Vemos en que posición se encuentra el rey
 for(i=0;i<8;i++)
   for(j=0;j<8;j++)
	if((tablero[i][j].ficha==REY)&&(tablero[i][j].color==color))
		{
		pos_i_rey=i;
		pos_j_rey=j;
		}

  // Vemos si está en jaque
  en_jaque=jaque_aux(pos_i_rey,pos_j_rey);

  // Vemos si está en jaque mate
  if(en_jaque)
  	{
	aux=0;
	n_movs=0;
	movs=Movimientos_Rey(&n_movs,pos_i_rey,pos_j_rey);
	for(i=0;i<n_movs;i++)
		{
		aux_ficha = tablero[movs[i][0]][movs[i][1]].ficha;
		aux_color = tablero[movs[i][0]][movs[i][1]].color;

		tablero[movs[i][0]][movs[i][1]].ficha = REY;
		tablero[movs[i][0]][movs[i][1]].color = color;
		tablero[pos_i_rey][pos_j_rey].ficha = LIBRE;

		// comprobamos si estaría en jaque en la nueva posición
		aux += jaque_aux(movs[i][0],movs[i][1]);

		// Deshacemos los cambios
		tablero[movs[i][0]][movs[i][1]].ficha = aux_ficha;
		tablero[movs[i][0]][movs[i][1]].color = aux_color;
		tablero[pos_i_rey][pos_j_rey].ficha=REY;
		tablero[pos_i_rey][pos_j_rey].color=color;
		}
	if(aux==n_movs) en_jaque=2;

	if(n_movs!=0) {
  	  for(i=0;i<n_movs;i++)
  	    free(movs[i]);
  	  free(movs); }
	}

  return en_jaque;
}


// Función que comprueba si el movimiento realizado es correcto, devuelve 1
// si lo es, 0 en caso contrario
int MovimientoCorrecto()
{
  int **movs, n_movs, i, correcto;

  n_movs=0;
  correcto=0;
  
  // Si la ficha no se ha movido
  if((SELECT_pos_i_inicial==SELECT_pos_i_final)&&(SELECT_pos_j_inicial==SELECT_pos_j_final))
  	correcto=0;
  
  else {
  switch(tablero[SELECT_pos_i_inicial][SELECT_pos_j_inicial].ficha) {
  	case PEON:    movs=Movimientos_Peon(&n_movs,SELECT_pos_i_inicial,SELECT_pos_j_inicial);
		      break;
	case TORRE:   movs=Movimientos_Torre(&n_movs,SELECT_pos_i_inicial,SELECT_pos_j_inicial);
		      break;
	case CABALLO: movs=Movimientos_Caballo(&n_movs,SELECT_pos_i_inicial,SELECT_pos_j_inicial);
		      break;
	case ARFIL:   movs=Movimientos_Arfil(&n_movs,SELECT_pos_i_inicial,SELECT_pos_j_inicial);
		      break;
	case REINA:   movs=Movimientos_Reina(&n_movs,SELECT_pos_i_inicial,SELECT_pos_j_inicial);
		      break;
	case REY:     movs=Movimientos_Rey(&n_movs,SELECT_pos_i_inicial,SELECT_pos_j_inicial);
		      break;
	}

  for(i=0;i<n_movs && !correcto;i++)
  	{
  	if((movs[i][0]==SELECT_pos_i_final)&&(movs[i][1]==SELECT_pos_j_final))
		correcto=1;
	}


  if(n_movs!=0) {
  	for(i=0;i<n_movs;i++)
  		free(movs[i]);
  	free(movs);
  	}
  }  // end else

  return correcto;
}



/*********************** FUNCIÓN DE DIBUJO **************************/
static void Dibuja( )
// Dibuja el modelo
{
   static GLfloat pos[4] = { 0, 20.0, 0, 0.0 }; // Posicion de la luz
   int i,j,color;

   glClearColor(0,0,0,1);   // Fija el color de fondo a negro
   glClear( GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT );   // Inicializa el buffer de color
   glLightfv( GL_LIGHT0, GL_POSITION, pos );    // Luz en posicion "pos"
   glShadeModel( GL_FLAT );             // Las caras se pintan de color plano

   glPushMatrix();
   glCallList(Borde);
	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
			{
			glLoadName(i*8+j);
			// Señalamos la ficha seleccionada
			if((seleccionado)&&(SELECT_pos_i_inicial==i)&&(SELECT_pos_j_inicial==j))
					{
					glPushMatrix();
					glTranslatef(0.0,2.0,0.0);
					}
			// Dibujar tablero
			glPushMatrix();
				glTranslatef(i*10.0,0.0,j*10.0);
				if((i+j)%2==0) glCallList(TableroNegro);
				else glCallList(TableroBlanco);
			glPopMatrix();
		
			// Dibujar fichas
			if(tablero[i][j].ficha!=LIBRE)
				{
				if(tablero[i][j].color == NEGRA) color=1;
				else color=0;
				glPushMatrix();
				glTranslatef(10.0*i+5.0,2.0,10.0*j+5.0);
				switch(tablero[i][j].ficha) {
				  case PEON: if(color) glCallList(PeonNegro);
				  	     else glCallList(PeonBlanco);
					     break;
				  case TORRE: if(color) glCallList(TorreNegro);
				  	      else glCallList(TorreBlanco);
					      break;
				  case CABALLO: if(color) glCallList(CaballoNegro);
						else glCallList(CaballoBlanco);
						break;
				  case ARFIL: if(color) glCallList(ArfilNegro);
				  	      else glCallList(ArfilBlanco);
					      break;
				  case REINA: if(color) glCallList(ReinaNegro);
				  	      else glCallList(ReinaBlanco);
					      break;
				  case REY: if(color) glCallList(ReyNegro);
				  	    else glCallList(ReyBlanco);
					    break; }
				glPopMatrix();
				}
			if((seleccionado)&&(SELECT_pos_i_inicial==i)&&(SELECT_pos_j_inicial==j))
					glPopMatrix();
			}
   glPopMatrix();
   glFlush();  // Fuerza el dibujo de las primitivas introducidas
   glutSwapBuffers();          // Intercambia buffers: visualiza lo dibujado
}


/******************* FUNCIONES PARA TRANSFORMADA DE VISUALIZACIÓN **********************/
void ViewTrans()        //@Calcula la transf. sin inicializar
{
float calto;

  if(viewX>0)
  	calto =  viewY/viewX;
  else
  	calto = 1;
  glFrustum(-1+vofx,1+vofx,calto*(-1+vofy),calto*(1+vofy),2,1000);
        // Transformacion de visualizacion
  glMatrixMode(GL_MODELVIEW); // A partir de este momento las transformaciones son de modelado
  glLoadIdentity();     // Inicializa la transformacion

  // ## Codigo de cambio de camara
  glTranslatef( 0, 0,-D);    // Aleja la camara

  glRotatef( view_rotx, 1.0, 0.0, 0.0 ); // Rotaciones de la camara
  glRotatef( view_roty, 0.0, 1.0, 0.0 );
  glRotatef( view_rotz, 0.0, 0.0, 1.0 );

  glTranslatef(-40.0,0.0,-40.0);               // Centrado del modelo
}


void setViewTrans()
// Fija la transformacion de visualizacion. Se llama cada vez que
// se cambia algun parametro que le afecte
{
   glMatrixMode(GL_PROJECTION); // Especificamos la transformación de visualización
   glLoadIdentity();    // Inicializa la transformacion
   ViewTrans();
}


void Ventana(GLsizei ancho,GLsizei alto)
// Este procedimiento es llamado por el sistema cuando se cambia el tamaño
// de la ventana X. ancho y alto son el tamaño en pixel de la ventana.
{
  glViewport(0,0,ancho,alto);
  // Establecemos el Viewport usando la nueva anchura y altura de la ventana X

  viewX = ancho; // Almacena las dimensiones en variables del programa
  viewY = alto;
  setViewTrans(); // Recalcula la transformacion de visualizacion
}



/************************ FUNCIONES DE TECLADO ********************/
/* @teclado ---------------------------------------------------------------- */
 static void letra (unsigned char k, int x, int y)
// Este procedimiento es llamado por el sistema cuando se pulsa una tecla normal
// El codigo k es el ascii de la letra
{
  switch (k) {

  case '+':             // + Camara mas cerca
    D -= 5.0;
    break;
  case '-':             // - Camara mas lejos
    D += 5.0;
    break;
  case 27:  /* Escape */  // Terminar
    printf("\n");
    exit(0);
    break;
  default:
    return;
  }
  
  setViewTrans();
  glutPostRedisplay();  // Algunas de las opciones cambian paramentros
}                       // de la camara. Es necesario actualziar la imagen

 static void especial(int k, int x, int y)
// Este procedimiento es llamado por el sistema cuando se pulsa una tecla
// especial. El codigo k esta definido en glut mediante constantes
{
  switch (k) {
  case GLUT_KEY_UP:
    if(view_rotx<90) view_rotx += 5.0;
    break;
  case GLUT_KEY_DOWN:
    if(view_rotx>0) view_rotx -= 5.0;
    break;
  case GLUT_KEY_LEFT:
    if((view_roty<180 && turno==BLANCA)||(view_roty<360 && turno==NEGRA)) 
    	view_roty += 5.0;
    break;
  case GLUT_KEY_RIGHT:
    if((view_roty>0 && turno==BLANCA)||(view_roty>180 && turno==NEGRA)) view_roty -= 5.0;
    break;
  default:
    return;
  }
  setViewTrans();
  glutPostRedisplay();  // Actualiza la imagen (ver proc. letra)
}


/***************************** ANIMACIÓN DEL TABLERO *********************/
static void timeUp()
// Esta funcion es llamada por el sistema como funcion de fondo.
// Se utiliza para animar el modelo
{
  int para=1;
  if(Animando_Turno)
  	{
  	if(view_roty<270 && turno==BLANCA)  {view_roty+=5; para=0;}
	else if(view_roty>90 && turno==NEGRA) {view_roty-=5; para=0;}
	if(para)
	     {
	     if(turno==BLANCA) turno=NEGRA;
	     else turno=BLANCA;
	     Animando_Turno=0;

	     // Vemos si hemos puesto al adversario en jaque
	     jaque=jaque_mate(turno);
	     if(jaque==1) {printf("\n%s","JAQUE"); fflush(stdout);}
	     else if(jaque==2) {
	     	if(turno==BLANCA) {printf("\n%s","JAQUE MATE, ganan las negras"); fflush(stdout);}
		else {printf("\n%s","JAQUE MATE, ganan las blancas"); fflush(stdout);}
		}
	     }
	}
	
  setViewTrans();
  glutPostRedisplay();
}


/************************** INTERACCIÓN ***************************/
void pick(int x, int y)
{
   GLuint buff[512];	// Buffer de seleccion
   GLint hits;          // Numero de elementos seleccionados
   GLint viewport[4];   // Viewport
   int i,b,Zmin,z,k,aux_ficha,aux_color;


   glSelectBuffer (512, buff);     	// Fija el buffer de seleccion
   (void) glRenderMode (GL_SELECT); // Paso a modo seleccion

   glInitNames();                   // Inicializa el stack de nombres
   glPushName(-1);					// Valor de fondo

   glMatrixMode (GL_PROJECTION);    // Pasa a modo proyección
   glPushMatrix ();
   glLoadIdentity ();               // Inicializa la tranasformacion

   glGetIntegerv (GL_VIEWPORT, viewport);   // Obtiene el viewport
   gluPickMatrix ((GLdouble) x, (GLdouble) (viewport[3] - y),
                  2.0, 2.0, viewport);  // Añade la transformacion
	// para reducir la imagen a una ventana de 5 pixels arededor del
	// punto en el que seleccionar
   ViewTrans();  // Fija el resto de la transformacion de visualizacion

   Dibuja();	// Dibuja el modelo (no se genera imagen estamos en Render mode)
   glMatrixMode (GL_PROJECTION);	// Pasamos a modo proyección
   glPopMatrix ();              	// Deja la transformacion como estaba

   hits = glRenderMode (GL_RENDER); // Obtiene informacion de seleccion
									// en hits y buff
   if(hits>0) {
        b=0;
	Zmin=-1;
	for(k=0;k<hits;k++) {
		if(buff[b]!=0) {
		  z=buff[b+1];
		  if(Zmin==-1 || z<Zmin)
		  	{
			i=buff[b+3];
			Zmin=z;
			}
		b+=buff[b]+3;
		}
	}
      
      if(!seleccionado)
      	{
	SELECT_pos_i_inicial = i/8;
	SELECT_pos_j_inicial = i%8;
	if((tablero[SELECT_pos_i_inicial][SELECT_pos_j_inicial].color == turno)
	  &&tablero[SELECT_pos_i_inicial][SELECT_pos_j_inicial].ficha != LIBRE)
	  	seleccionado=1;
	}
      else
      	{
	seleccionado = 0;
	SELECT_pos_i_final = i/8;
	SELECT_pos_j_final = i%8;

	// Movimiento correcto
	if(MovimientoCorrecto())
		{
		aux_ficha = tablero[SELECT_pos_i_final][SELECT_pos_j_final].ficha;
		aux_color = tablero[SELECT_pos_i_final][SELECT_pos_j_final].color;

		// Realizar jugada
		tablero[SELECT_pos_i_final][SELECT_pos_j_final].ficha = tablero[SELECT_pos_i_inicial][SELECT_pos_j_inicial].ficha;
		tablero[SELECT_pos_i_final][SELECT_pos_j_final].color = tablero[SELECT_pos_i_inicial][SELECT_pos_j_inicial].color;
		tablero[SELECT_pos_i_inicial][SELECT_pos_j_inicial].ficha = LIBRE;

		// Si no salimos de jaque o ponemos en jaque a nuestro rey, deshacemos jugada
		jaque = jaque_mate(turno);
		if(jaque)
			{
			{printf("\n%s","Está poniendo su REY en JAQUE"); fflush(stdout);}
			tablero[SELECT_pos_i_inicial][SELECT_pos_j_inicial].ficha = tablero[SELECT_pos_i_final][SELECT_pos_j_final].ficha;
			tablero[SELECT_pos_i_inicial][SELECT_pos_j_inicial].color = tablero[SELECT_pos_i_final][SELECT_pos_j_final].color;

			tablero[SELECT_pos_i_final][SELECT_pos_j_final].ficha = aux_ficha;
			tablero[SELECT_pos_i_final][SELECT_pos_j_final].color = aux_color;
			}

		else 	Animando_Turno=1;  // Actualizar el turno
		}
	else {printf("\n%s","Movimiento Incorrecto"); fflush(stdout);}
	}
   } //end hits>0


   setViewTrans();			// Fija la transformacion de visualizacion
}



/************************** FUNCIONES RATÓN *************************/
// @raton -------------------------------------------------------------------
 void clickRaton( int boton, int estado, int x, int y )
// Este procedimiento sera llamado por el sistema cuando se haga click
// con el raton. Los parametros indican el estado del raton en ese momento.
{
   if(boton== GLUT_LEFT_BUTTON && estado == GLUT_DOWN && jaque!=2) {
                // Se ha actuado sobre el izquierdo que esta ahora pulsado
	pick(x, y);
	setViewTrans();               // Actualiza tranf. de visualizacion
        glutPostRedisplay();          // Actualiza imagen


        if( ~(RatonPulsado)){   // No estaba pulsado
           Xref=x;                 // Almacena posicion (en coor. de pantalla)
           Yref=y;
           RatonPulsado=GL_TRUE;   // Recuerda que esta pulsado
           }
        }
   else RatonPulsado=GL_FALSE;  // Recuerda que no esta pulsado
}

static void RatonMovido( int x, int y )
// Esta función es llamada cuando el raton se mueve. La utilzamos
// para desplazar la imagen
{
}

/*********************CREACIÖN DE UN JUEGO NUEVO ************************/
void JuegoNuevo()
{
int i,j;

for(i=0;i<8;i++)
	for(j=0;j<8;j++)
		tablero[i][j].ficha=LIBRE;

// Colocar fichas blancas
tablero[0][0].ficha = TORRE; tablero[0][0].color = BLANCA;
tablero[0][1].ficha = CABALLO; tablero[0][1].color = BLANCA;
tablero[0][2].ficha = ARFIL; tablero[0][2].color = BLANCA;
tablero[0][3].ficha = REINA; tablero[0][3].color = BLANCA;
tablero[0][4].ficha = REY; tablero[0][4].color = BLANCA;
tablero[0][5].ficha = ARFIL; tablero[0][5].color = BLANCA;
tablero[0][6].ficha = CABALLO; tablero[0][6].color = BLANCA;
tablero[0][7].ficha = TORRE; tablero[0][7].color = BLANCA;
for(i=0;i<8;i++)
	{tablero[1][i].ficha = PEON; tablero[1][i].color = BLANCA;}

// Colocar fichas negras
tablero[7][0].ficha = TORRE; tablero[7][0].color = NEGRA;
tablero[7][1].ficha = CABALLO; tablero[7][1].color = NEGRA;
tablero[7][2].ficha = ARFIL; tablero[7][2].color = NEGRA;
tablero[7][3].ficha = REINA; tablero[7][3].color = NEGRA;
tablero[7][4].ficha = REY; tablero[7][4].color = NEGRA;
tablero[7][5].ficha = ARFIL; tablero[7][5].color = NEGRA;
tablero[7][6].ficha = CABALLO; tablero[7][6].color = NEGRA;
tablero[7][7].ficha = TORRE; tablero[7][7].color = NEGRA;
for(i=0;i<8;i++)
	{tablero[6][i].ficha = PEON; tablero[6][i].color = NEGRA;}

turno=BLANCA;
seleccionado=0;
Animando_Turno=0;
jaque=0;
D=120.0;
view_rotx=40.0; view_roty=90.0; view_rotz=0.0;

setViewTrans();               // Actualiza tranf. de visualizacion
glutPostRedisplay();          // Actualiza imagen
}


/********************** MENÚ ***********************/
 void seleccionMenu( int opcion )
// Este procedimiento es llamado por el sistema cuando se selecciona una
// opcion del menu glut. El parametro contiene el identificador de la opcion
{
   switch ( opcion )
   {
   case JUEGO_NUEVO:
   	JuegoNuevo();
	break;

   case SALIR:
   	  printf("\n");
   	  exit(0);      // Salir del programa
   }
}

 void CreaMenu()
// Este proc. se usa para definir el menu glut. Se llama desde main.
{
   menu = glutCreateMenu( seleccionMenu );      // Crea menu
   glutAddMenuEntry("Nuevo Juego", JUEGO_NUEVO);
   glutAddMenuEntry( "Salir", SALIR );           // Añade opcion salir
   glutAttachMenu( GLUT_RIGHT_BUTTON ); // El menu se abre con boton derecho
}



/********************** INICIALIZACIÓN DEL MODELO ************************/
void initModel()
{
// Creación de un nuevo juego
JuegoNuevo();

// Creación de los Display Lists
TableroBlanco = glGenLists(1);
glNewList(TableroBlanco, GL_COMPILE);
glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,blanco);
Box(10.0,2.0,10.0);
glEndList();

TableroNegro = glGenLists(1);
glNewList(TableroNegro, GL_COMPILE);
glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,negro);
Box(10.0,2.0,10.0);
glEndList();

PeonBlanco = glGenLists(1);
glNewList(PeonBlanco, GL_COMPILE);
glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,blanco);
Peon();
glEndList();

PeonNegro = glGenLists(1);
glNewList(PeonNegro, GL_COMPILE);
glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,negro);
Peon();
glEndList();

TorreBlanco = glGenLists(1);
glNewList(TorreBlanco, GL_COMPILE);
glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,blanco);
Torre();
glEndList();

TorreNegro = glGenLists(1);
glNewList(TorreNegro, GL_COMPILE);
glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,negro);
Torre();
glEndList();

ArfilBlanco = glGenLists(1);
glNewList(ArfilBlanco, GL_COMPILE);
glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,blanco);
Arfil();
glEndList();

ArfilNegro = glGenLists(1);
glNewList(ArfilNegro, GL_COMPILE);
glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,negro);
Arfil();
glEndList();

CaballoBlanco = glGenLists(1);
glNewList(CaballoBlanco, GL_COMPILE);
glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,blanco);
glPushMatrix();
  glRotatef(180,0.0,1.0,0.0);
  Caballo();
glPopMatrix();
glEndList();

CaballoNegro = glGenLists(1);
glNewList(CaballoNegro, GL_COMPILE);
glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,negro);
Caballo();
glEndList();

ReinaBlanco = glGenLists(1);
glNewList(ReinaBlanco, GL_COMPILE);
glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,blanco);
Reina();
glEndList();

ReinaNegro = glGenLists(1);
glNewList(ReinaNegro, GL_COMPILE);
glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,negro);
Reina();
glEndList();

ReyBlanco = glGenLists(1);
glNewList(ReyBlanco, GL_COMPILE);
glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,blanco);
glPushMatrix();
  glRotatef(90,0.0,1.0,0.0);
  Rey();
glPopMatrix();
glEndList();

ReyNegro = glGenLists(1);
glNewList(ReyNegro, GL_COMPILE);
glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,negro);
glPushMatrix();
  glRotatef(90,0.0,1.0,0.0);
  Rey();
glPopMatrix();
glEndList();

Borde = glGenLists(1);
glNewList(Borde, GL_COMPILE);
glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,marron);
glPushMatrix();
  glTranslatef(-5.0,0.0,-5.0);
  Box(90.0,2.0,5.0);
  glTranslatef(0.0,0.0,85.0);
  Box(90.0,2.0,5.0);
glPopMatrix();
glPushMatrix();
  glRotatef(-90.0,0.0,1.0,0.0);
  Box(80.0,2.0,5.0);
  glTranslatef(0.0,0.0,-85.0);
  Box(80.0,2.0,5.0);
glPopMatrix();
glEndList();

glEnable( GL_NORMALIZE );
}




/* @main ------------------------------------------------------------------------- */
int main( int argc, char *argv[] )
{
   glutInit( &argc, argv ); // Inicializa glu y Mesa


// Crea una ventana X para la salida gráfica
   glutInitWindowPosition( 0, 0 );              // Posicion
   glutInitWindowSize( viewX, viewY );          // Tamaño
   glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH ); // Tipo
                // Color RGBA, doble buffer y z-buffer
   glutCreateWindow("AJEDREZ (Manuel González López)");   // Crea la ventana

// Inicializa las funciones de dibujo y cambio de tamaño de la ventana X
   glutDisplayFunc( Dibuja );   // Indica funcion de redibujo
   glutReshapeFunc( Ventana );  // Indica funcion de cambio de tamaño de ventana X

// Inicializacion
    initModel();    // Modelo
    CreaMenu();     // Menus

// FUNCIONES DE INTERACCIÓN
    glutMouseFunc( clickRaton ); // Indica la funcion a llamar cuando se hace click
    glutKeyboardFunc(letra);    // Llamada para teclado
    glutSpecialFunc(especial);   // Llamada para teclas especiales
    glutMotionFunc( RatonMovido );      // Llamada cuando se mueve el raton
    glutIdleFunc( timeUp);      // Funcion de fondo

// Activacion de funciones
    glEnable(GL_CULL_FACE);     // Activa eliminacion de caras traseras
    glEnable( GL_LIGHTING );    // Activa uso de luces
    glEnable( GL_LIGHT0 );      // Activa luz 0
    glEnable(GL_DEPTH_TEST);    // Activa test de profundidad

// Empieza
   glutMainLoop();              // Llama al gestor de eventos de glut
   return 0;
}