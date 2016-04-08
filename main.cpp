#include <ctype.h>
#include <cmath>
#include <iostream>
#include <vector>

#include <GL/gl.h>
#include <GL/glut.h>

#include "aux-p4.hpp"
#include "objetos-3.h"

#include "esfera-planeta.hpp"
#include "esfera-fondo.hpp"
#include "esfera-sol.hpp"
#include "esfera-satelite.hpp"
#include "luz.hpp"
#include "objeto-ply.hpp"
#include "textura.hpp"
#include "camara.hpp"

#define MAX_SEL 64

using namespace std;

bool vistanave=false;
bool vistaluna=false;

bool dibuorbi=false;

bool accionarrotacion1=false;
bool yapulsado1=false;
bool accionarrotacion2=false;
bool yapulsado2=false;
bool accionarrotacion3=false;
bool yapulsado3=false;
bool accionarrotacion4=false;
bool yapulsado4=false;
bool accionarrotacion5=false;
bool yapulsado5=false;
bool accionarrotacion6=false;
bool yapulsado6=false;
bool accionarrotacion7=false;
bool yapulsado7=false;
bool accionarrotacion8=false;
bool yapulsado8=false;

int moving, begin_x,begin_y;
int newModel = 1;
int trasl_x, trasl_y;
GLfloat escala_x, escala_y;
GLfloat angle =0.f,camaragiro=1,camaratrasnalte=2,camaragiro2=1;

float x0,  yy0;


int modo=0;
 int  is , js ,auxi,auxj;

int turno=0,fase=0,num;
//**********************************************************************
// tamaño de la ventana

int
  altoActual  = 1024, 
  anchoActual = 1024 ;
  
//**********************************************************************
// lista de objetos, y modo de dibujo

const unsigned 
   num_objetos = 6 ; // número total de objetos distintos que pueden dibujarse

const char *
   descr_objetos[num_objetos] =   // descripciones de los objetos:
   {  "lata de coca cola", 
      "esfera del mundo (mapa físico)",
      "esfera del mundo (amistades de facebook)",
      "tetera" ,
      "objeto ply",
      "orbita"
   } ;


EsferaPlaneta *    obj_esfera_mundo = NULL ;   // objeto indice 1
EsferaPlaneta *  obj_esfera_jupiter= NULL ;
EsferaSatelite *    obj_esfera_lunajupiter = NULL;
EsferaSatelite *    obj_esfera_lunajupiter2 = NULL;
EsferaPlaneta *    obj_esfera_mercurio = NULL ; 
EsferaSatelite *    obj_esfera_luna = NULL;
EsferaSol * obj_esfera_sol = NULL ;// objeto indice 2
EsferaPlaneta *    obj_esfera_venus = NULL;
EsferaPlaneta *     obj_esfera_marte= NULL;
EsferaSatelite *    obj_esfera_lunamarteuno= NULL;
EsferaSatelite *    obj_esfera_lunamartedos= NULL;
EsferaPlaneta *    obj_esfera_urano= NULL;
EsferaPlaneta *    obj_esfera_neptuno= NULL;
EsferaSatelite *    obj_esfera_lunaurano= NULL;

EsferaFondo *  obj_esfera_fondo= NULL;

EsferaPlaneta *    obj_esfera_saturno = NULL;
EsferaSatelite *    obj_esfera_anillosaturno = NULL;

ObjetoPLY *      obj_ply = NULL ;            // objeto indice 4

   
_draw_type                // declarado en 'objetos-3.h'
   modo_dibujo_actual ;   // modo actual de dibujo
   
const unsigned int
   num_modos_dibujo = ((unsigned int) SOLID_MATERIAL_GOUROUD)+1 ;



unsigned 
   i_objeto_act ; // índice del objeto que se está visualizando ahora mismo

//**********************************************************************
// fuentes de luz 

FuenteLuz 
   * fuente_luz_0 = NULL ,
   * fuente_luz_1 = NULL ;
   
//**********************************************************************
// parámetros de la matriz de vista y modelado

const GLfloat
   longi_cam_ini =  45.0,  // valor inicial para 'longi_cam' (ver abajo)
   lati_cam_ini  =  30.0 , // valor inicial para 'lati_cam' (ver abajo)
   dis_cam_ini   =  1.0 ;  // valor inicial para la distancia de la camara al origen
   
  GLfloat  movlon=longi_cam_ini, movlati=-1;
   
GLfloat
   longi_cam =  longi_cam_ini, // angulo de longitud actual de la cámara, en grados
   lati_cam  =  lati_cam_ini , // angulo de latitud actual de la cámara, en grados
   dis_cam   =  dis_cam_ini ;  // distancia de la camara al origen
   
GLfloat   longi_cam_luna=100 ,
      lati_cam_luna  = 1 ,seguiluna=10,borrar=0.5;
      
GLfloat   longi_cam_nave=6 ,
      lati_cam_nave  = 0.2 ;
   
GLfloat
   ang_ry_obj = 0.0 , // ángulo actual de rotacion en Y+ del objeto, en grados
   ang_rx_obj = 0.0 , // ángulo actual de rotacion en X- del objeto, en grados
   ang_rz_obj = 0.0 , // ángulo actual de rotacion en Z+ del objeto, en grados
   f_esc_obj  = 1.0 ; // factor de escala del objeto (en tanto por uno)

//**********************************************************************
// gestión de los modos de teclado

typedef enum 
{  mt_rot_objeto, 
   mt_par_camara, 
   mt_rot_luz,
   mt_tipo_dibujo_objeto,
   mt_material_ply,
   num_modos_teclado
   
   
} 
   ModoTeclado ;
   
const char * 
   descr_mt[num_modos_teclado] =  // descripciones de los modos de teclado
      {  "F1: rotación , escala de objeto y ORBITAS \n" 
               "\t\t flechas hor/ver  -> rotaciones Y+)/X-.Y ACTIVACION ORBITAS\n"
               "\t\t pg.arr/ab.       -> rotacion en Z+.\n"
               "\t\t mas/meno         -> aumentar/disminuir tamaño de objeto.\n"
               "\t\t inicio           -> reinicializar posicion/tamaño del objeto.\n",
         "F2: rotación y zoom de cámara\n"
               "\t\t flechas   -> rotaciones hor./ver.\n"
               "\t\t mas/menos -> alejar/acercar cámara.\n"
               "\t\t inicio    -> reset.\n",
         "F3: rotación de la fuente de luz.\n"
               "\t\t flechas   -> rotaciones hor/ver.\n"
               "\t\t inicio    -> reset.\n",
         "F4: CAMARA LUNA\n",
         "F5: CAMARA OBJETO PLY.\n"
          
      } ;

ModoTeclado 
   modo_tecl_actual ;


//**********************************************************************
// fijar la matriz de vista, deja activo el modo de matriz modelview

void MatrizVista()
{
   const GLfloat
      longi_cam_rad = longi_cam*2.0f*M_PI / 360.0f ,
      lati_cam_rad  = lati_cam *2.0f*M_PI / 360.0f ;
      
   const GLfloat
      eyex = dis_cam*( sin(longi_cam_rad)*cos(lati_cam_rad) ),
      eyey = dis_cam*( sin(lati_cam_rad) ),
      eyez = dis_cam*( cos(longi_cam_rad)*cos(lati_cam_rad) );
      
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity() ;
   gluLookAt
   (  eyex, eyey, eyez,  // posición de la cámara
      0.0f, 0.0f, 0.0f,  // punto de atencion (== origen)
      0.0f, 1.0f, 0.0f   // vector 'up' (== eje Y+)
   ) ;
}
void MatrizVistaLuna()
{
glMatrixMode(GL_PROJECTION);
glLoadIdentity() ;


	gluPerspective(45, (float)anchoActual/(float)altoActual , 0.10, 100.0);
	
      
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity() ;


	gluLookAt
	(
	2, 0.2, 0,  // posición de la cámara  10, 0.5, -2,
	0, 0, -1,  // punto de atencion (== origen)   2, 0, 0, 
	0, 1, 0   // vector 'up' (== eje Y+)
	);
	
		
       glRotatef(camaragiro2,0,1,0);	
		
       glTranslatef(-6,0,0);

       glRotatef(camaragiro,0,1,0);	



   
}
void MatrizVistaNave()
{
glMatrixMode(GL_PROJECTION);
glLoadIdentity() ;

	gluPerspective(45, (float)anchoActual/(float)altoActual , 0.10, 100.0);
  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity() ;
	
	gluLookAt
	(
	-1, -7, 15,  // posición de la cámara  10, 0.5, -2,
	0, 0, 0,  // punto de atencion (== origen)   2, 0, 0, 
	0, 1, 0   // vector 'up' (== eje Y+)
	);
	
	
  // glRotatef(90,1,0,0);
        glRotatef(camaragiro,0,1,0);
//glRotatef(90,0,0,1);



}
//**********************************************************************

void MatrizProyeccion()
{
  // glMatrixMode(GL_PROJECTION);
  // glLoadIdentity() ;
   
   if ( anchoActual < altoActual  )
   {  const GLfloat ratioYX = GLfloat(altoActual)/GLfloat(anchoActual) ;
      glOrtho( -dis_cam,dis_cam, -dis_cam*ratioYX,dis_cam*ratioYX, -dis_cam*3.0,dis_cam*3.0 );
   }
   else
   {  const GLfloat ratioXY = GLfloat(anchoActual)/GLfloat(altoActual) ;
      glOrtho( -dis_cam*ratioXY,dis_cam*ratioXY, -dis_cam,dis_cam, -dis_cam*3.0,dis_cam*3.0 );
   }
   
}


//**********************************************************************

void FuncRedimensionar( int nuevoAncho, int nuevoAlto )
{
  altoActual = nuevoAlto ;
  anchoActual = nuevoAncho ;
  
  glViewport(0,0,anchoActual,altoActual);
  
  using namespace std ;
  //cout << "ventana redimensionada, nuevo tamaño: " << anchoActual << " x " << altoActual << " pixels." << endl << flush ;
}

//**********************************************************************



//**********************************************************************

void DibujarFondo()
{


   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ) ;
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   glOrtho( -1,1, -1,1, -1,1 );
   glMatrixMode( GL_MODELVIEW );
   glLoadIdentity();
   
   //glDisable(GL_LIGHTING);
   //glDisable(GL_TEXTURE_2D);
   //glDisable(GL_DEPTH_TEST);
   glShadeModel(GL_SMOOTH);
   //glDisable(GL_CULL_FACE);
   glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

   glEnable( GL_DEPTH_TEST);

}

//**********************************************************************
// DibujarObjetoActual
// -------------------
// dibuja el objeto actual en el modo de dibujo actual

void DibujarObjetoActual()
{

        obj_esfera_mundo->draw_solid_material_gouroud();
        
      if(dibuorbi){
            obj_esfera_mundo->dibujaorbita();
            obj_esfera_venus->dibujaorbita();
            obj_esfera_mercurio->dibujaorbita();
            obj_esfera_marte->dibujaorbita();
            obj_esfera_jupiter->dibujaorbita();
            obj_esfera_saturno->dibujaorbita();
            obj_esfera_urano->dibujaorbita();
            obj_esfera_neptuno->dibujaorbita();
        
   }
   obj_esfera_jupiter->draw_solid_material_gouroud();
   obj_esfera_luna->draw_solid_material_gouroud();
   obj_esfera_sol->draw_solid_material_gouroud();
   obj_esfera_venus->draw_solid_material_gouroud();
   obj_esfera_mercurio->draw_solid_material_gouroud();
   obj_esfera_marte->draw_solid_material_gouroud();
   obj_esfera_lunamarteuno->draw_solid_material_gouroud();
   obj_esfera_lunamartedos->draw_solid_material_gouroud();
   obj_esfera_saturno->draw_solid_material_gouroud();
   obj_esfera_anillosaturno->draw_solid_material_gouroud();
   obj_esfera_lunaurano->draw_solid_material_gouroud();
        
   obj_esfera_urano->draw_solid_material_gouroud();
   obj_esfera_neptuno->draw_solid_material_gouroud();

   obj_ply->draw_solid_material_gouroud(); 
   obj_esfera_lunajupiter ->draw_solid_material_gouroud(); 
   obj_esfera_lunajupiter2 ->draw_solid_material_gouroud(); 
         
   obj_esfera_fondo->draw_solid_material_gouroud();
   
         
}

//**********************************************************************

void DibujarVentana()
{
   using namespace std ;
   //static unsigned long count = 0 ;
   //cout << "redibujando ventana (" << (++count) << ") ... " << flush ;
   
   //assert( glGetError() == GL_NO_ERROR );
   assert( fuente_luz_0 != NULL && fuente_luz_1 != NULL) ;
   assert( i_objeto_act < num_objetos );
   //assert( objetos[i_objeto_act] != NULL ) ;
   
   DibujarFondo();
   MatrizVistaLuna();
   
   if(!vistanave && !vistaluna){
        MatrizProyeccion();   
   	MatrizVista(); 
   }else if(vistanave){
   	MatrizVistaNave();
   }else if(vistaluna)
   		
   		
   
   glMatrixMode( GL_MODELVIEW );
   

   fuente_luz_0->activar();
   fuente_luz_1->activar();
   
   glMatrixMode( GL_MODELVIEW );
   glPushMatrix();
      glRotated( ang_rz_obj,  0.0, 0.0, 1.0 );  // (3) rot Z+
      glRotated( ang_rx_obj, -1.0, 0.0, 0.0 ) ; // (2) rot X-
      glRotated( ang_ry_obj,  0.0, 1.0, 0.0 );  // (1) rot Y+
      
     if(!vistanave && !vistaluna){
      	glScalef( f_esc_obj, f_esc_obj, f_esc_obj );  
      	
      }else 
      	glScalef( 1, 1, 1 ); 
      	
      DibujarObjetoActual( );
   glPopMatrix();    
   
   glutSwapBuffers();
   
   //assert( glGetError() == GL_NO_ERROR );
   
   //cout << "hecho." << endl << flush ;
}

//**********************************************************************

void Inicializa( int argc, char *argv[] )
{
   using namespace std ;
   assert( glGetError() == GL_NO_ERROR );
   assert( argc >= 3 );
   
   // inicializar opengl
   glEnable(GL_DEPTH_TEST);
   
   // crear objetos
   
   obj_esfera_sol = new EsferaSol() ;
   
   
   string estrellas = "estrellas.jpg";
   obj_esfera_fondo    = new EsferaFondo(estrellas,50,50,50);
   
  //PLANETAS

  //velocidad/indice/textura/tamaño/rotacion en su eje/orbita del planeta/distancia del planeta al sol/dibujaorbita
  string tierra = "earth.jpg";
   obj_esfera_mundo    = new EsferaPlaneta(1,39,tierra,0.5,0.5,0.5,1,0,1,0,10,0,1,0,5,0,0,3);
   
   string venus = "venus.jpg";
   obj_esfera_venus    = new EsferaPlaneta(1,2,venus,0.2,0.2,0.2,1,0,1,0,180,0,1,0,2.9,0,0,2);
   
   string mercurio = "mercurio.jpg";
   obj_esfera_mercurio    = new EsferaPlaneta(1,11,mercurio,0.4,0.4,0.4,1,0,1,0,45,0,1,0,3.5,0,0,2.40);
   
   string saturno = "saturno.jpg";
   obj_esfera_saturno  = new EsferaPlaneta(1,6,saturno,0.6,0.6,0.6,1,0,1,0,270,0,1,0,9,0,0,5);
   
    string marte = "marte.jpg";
   obj_esfera_marte    = new EsferaPlaneta(1,4,marte,0.4,0.4,0.4,1,0,1,0,75,0,1,0,5.9,0,0,3.9);
   
   string jupiter = "jupiter.jpg";
   obj_esfera_jupiter    = new EsferaPlaneta(1,5,jupiter,0.9,0.9,0.9,1,0,1,0,175,0,1,0,7,0,0,4.1);
   
   string neptuno = "neptuno.jpg";
   obj_esfera_neptuno    = new EsferaPlaneta(1,7,neptuno,0.25,0.25,0.25,1,0,1,0,345,0,1,0,10,0,0,5.9);
   
   string urano = "urano.jpg";
   obj_esfera_urano    = new EsferaPlaneta(1,8,urano,0.35,0.35,0.35,1,0,1,0,140,0,1,0,12,0,0,6.8);
   
   //SATELITES
   
   //textura/tamaño/orbita alrededor del planeta/rotacion en su eje/distancia del planeta/orbita del planeta/distancia del planeta al sol/
   string luna = "luna.jpg";
   obj_esfera_luna    = new EsferaSatelite( luna,0.2,0.2,0.2,0.5,0,1,0,0,0,0,0,1,0.2,0,10,0,1,0,5,0,0);
   
   string anillosatu = "saturno.jpg";
   obj_esfera_anillosaturno = new EsferaSatelite(anillosatu,1.2,0.01,1.2,0,0,0,0,1,0,1,5,0,0,0,270,0,1,0,9,0,0);
   
   string lunamarte1 = "luna.jpg";
   obj_esfera_lunamarteuno    = new EsferaSatelite( lunamarte1,0.1,0.1,0.1,128,0,1,0,0,0.01,0,0,1,0.2,0,75,0,1,0,5.9,0,0);
   
   string lunamarte2 = "anillosaturno.jpg";
   obj_esfera_lunamartedos    = new EsferaSatelite( lunamarte2,0.2,0.2,0.2,0.2,0,1,0,0,0,0,0,1,0.002,0,75,0,1,0,5.9,0,0);
   
   string lunajupiter = "marmol.jpg";
	obj_esfera_lunajupiter = new EsferaSatelite(lunajupiter,0.1,0.1,0.1,0.5,1,1,0,1,0,0,0,1.5,0.2,0.5,175,0,1,0,7,0,0);
   
   string lunajupiter2 = "marmol.jpg";
	obj_esfera_lunajupiter2 = new EsferaSatelite(lunajupiter2,0.2,0.2,0.3,0.5,1,1,0,1,0,0,0,-1.5,0,-0.2,175,0,1,0,7,0,0);

 string lunurano = "anillosaturno.jpg";
	obj_esfera_lunaurano = new EsferaSatelite(lunurano,0.1,0.3,0.2,0.5,1,0,1,1,0,0,0,-1.5,0,-0.2,140,0,1,0,12,0,0);

   //objeto ply

   obj_ply             = new ObjetoPLY(std::string(argv[1]),std::string(argv[2]));

   
   // inicialmente, el objeto activo es el objeto 0
   i_objeto_act = 0 ; 
   
   // inicialmente, se dibuja todo en modo caras
   modo_dibujo_actual = SOLID_MATERIAL_GOUROUD ;
   
   // crear fuentes de luz
   fuente_luz_0 = new FuenteLuz(GL_LIGHT0, 80.0f, 50.0f, vectorRGB(1.0f,1.0f,1.0f));
   fuente_luz_1 = new FuenteLuz(GL_LIGHT1,-100.0f,-30.0f, vectorRGB(0.8f,0.3f,0.2f));
   
   // inicializar el modo de teclado
   modo_tecl_actual = mt_rot_objeto ;
   cout << "modo teclado: " << descr_mt[modo_tecl_actual] << endl << flush ;

   // ya está
   assert( glGetError() == GL_NO_ERROR );
   //cout << "inicialización realizada." << endl << flush ;
}


//**********************************************************************

void Terminar()
{
   // liberar memoria:
   // (falta)
   // mensaje
   cout << "programa finalizado normalmente." << endl << flush ;
}

int pick(int x, int y)
{
GLuint BufferSeleccion[MAX_SEL] ;
GLint hits, viewport[4];
int i=0;
int t=0,tam=0,objetosel=0;
bool encontrado=false;
GLfloat z1;


 // 1. Declarar buffer de selección
glSelectBuffer(MAX_SEL, BufferSeleccion);
// 2. Obtener los parámetros del viewport
glGetIntegerv (GL_VIEWPORT, viewport);
// 3. Pasar OpenGL a modo selección
glRenderMode (GL_SELECT);
// 4. Fijar la transformación de proyección para la seleccion
glInitNames();
glPushName(0);
glMatrixMode (GL_PROJECTION);
glLoadIdentity ();
gluPickMatrix (x,(viewport[3] - y),1, 1, viewport);
MatrizProyeccion(); // SIN REALIZAR LoadIdentity !
// 5. Dibujar la escena
DibujarVentana();
glPopName();
// 6. Pasar OpenGL a modo render
hits = glRenderMode (GL_RENDER);
// 7, Restablecer la transformación de proyección (sin gluPickMatrix)
glMatrixMode (GL_PROJECTION);
glLoadIdentity ();
MatrizProyeccion();

// 8. Analizar el contenido del buffer de selección
cout << "numero de hits " << hits <<endl;

for(int ta=0;ta<hits;ta++){
	cout <<" tam "<< BufferSeleccion[(ta*4)]<< " zmin "<<BufferSeleccion[(ta*4)+1]<<" zmax  "<<BufferSeleccion[(ta*4)+2]<<" nombre "<<BufferSeleccion[(ta*4)+3] <<endl;
}

objetosel=BufferSeleccion[(0*4)+3];

GLfloat z=(float)BufferSeleccion[(0*4)+1];



for(int tag=1;tag<hits && !encontrado;tag++){
		// Obtengo la profundidad del objeto en curso...
               if(BufferSeleccion[(tag*4)]!=0){
	       		z1=BufferSeleccion[(tag*4)+1];
		//cout <<"profundidad z1  " <<BufferSeleccion[(tag*4)+1]<<" z "<<z  <<endl;
		// ... y si es menos que z ...
			if(z1 < z)
			{	// ... la pongo en z...
				z=z1;
				// ... y el nombre del objeto en la 
				//variable para eso.
			
				objetosel=BufferSeleccion[(tag*4)+3];
				cout<< " objeto selec " <<BufferSeleccion[(tag*4)+3] <<endl;
			}
		}
		
}	   	
		

  
 return objetosel;
}

//**********************************************************************

void GestionEventoRaton( int button, int state, int x, int y )
{
   


 if (button == GLUT_RIGHT_BUTTON   && state == GLUT_DOWN) {
	moving = 0;
	}
 if (button == GLUT_LEFT_BUTTON   && state == GLUT_DOWN) {
      
      	    num= pick(x, y);
      	    

      	    
      	    switch(num){
      	    
      	    case(11):        	    
      	    
      	             if(!yapulsado1){
      	              accionarrotacion1=true;
      	              yapulsado1=true;
      	            } else {
      	              accionarrotacion1=false;
      	              yapulsado1=false;
      	              }
      	    
      	    break;
      	    
      	    case(2):        	    
      	    
      	             if(!yapulsado2){
      	              accionarrotacion2=true;
      	              yapulsado2=true;
      	            } else {
      	              accionarrotacion2=false;
      	              yapulsado2=false;
      	              }
      	    
      	    break;
      	    
      	    case(39):        	    
      	    
      	             if(!yapulsado3){
      	              accionarrotacion3=true;
      	              yapulsado3=true;
      	            } else {
      	              accionarrotacion3=false;
      	              yapulsado3=false;
      	              }
      	    
      	    break;
      	    
      	    case(4):        	    
      	    
      	             if(!yapulsado4){
      	              accionarrotacion4=true;
      	              yapulsado4=true;
      	            } else {
      	              accionarrotacion4=false;
      	              yapulsado4=false;
      	              }
      	    
      	    break;
      	    
      	    case(5):        	    
      	    
      	             if(!yapulsado5){
      	              accionarrotacion5=true;
      	              yapulsado5=true;
      	            } else {
      	              accionarrotacion5=false;
      	              yapulsado5=false;
      	              }
      	    
      	    break;
      	    
      	    case(6):        	    
      	    
      	             if(!yapulsado6){
      	              accionarrotacion6=true;
      	              yapulsado6=true;
      	            } else {
      	              accionarrotacion6=false;
      	              yapulsado6=false;
      	              }
      	    
      	    break;
      	    
      	    case(7):        	    
      	    
      	             if(!yapulsado7){
      	              accionarrotacion7=true;
      	              yapulsado7=true;
      	            } else {
      	              accionarrotacion7=false;
      	              yapulsado7=false;
      	              }
      	    
      	    break;
      	    
      	    case(8):        	    
      	    
      	             if(!yapulsado8){
      	              accionarrotacion8=true;
      	              yapulsado8=true;
      	            } else {
      	              accionarrotacion8=false;
      	              yapulsado8=false;
      	              }
      	    
      	    break;
      	    
      	    
      	    }
            
}

 if ((button == GLUT_LEFT_BUTTON || button == GLUT_RIGHT_BUTTON) && state == GLUT_UP) {
	moving = 0;
	}
		
} 
    

//**********************************************************************

bool GestionEventoTeclaEspecialObjeto( int key ) 
{
   bool actualizar = true ;
   const double incr = 3.0 ;
   
   	
   switch( key )
   {
   
      case GLUT_KEY_LEFT:   
         ang_ry_obj += incr ;
         break ;
      case GLUT_KEY_RIGHT:
         ang_ry_obj -= incr  ;
         break ;
      case GLUT_KEY_UP:
         ang_rx_obj += incr  ;
         break ;
      case GLUT_KEY_DOWN:
         ang_rx_obj -= incr  ;
         break ;
      case GLUT_KEY_PAGE_UP :
         ang_rz_obj += incr  ;
         break ;
      case GLUT_KEY_PAGE_DOWN :
         ang_rz_obj -= incr  ;
         break ;
      case GLUT_KEY_HOME:
         ang_rz_obj = 0.0f ;
         ang_ry_obj = 0.0f ;
         ang_rx_obj = 0.0f ;
         f_esc_obj  = 1.0f ;
         break ;
      default :
         actualizar = false ;
         cout << "tecla no usable en este modo." << endl << flush ;
   }
   return actualizar ;
}

//**********************************************************************

bool GestionEventoTeclaNormalObjeto( unsigned char key ) 
{
   using namespace std ;
   bool 
      actualizar = true ;
   const float
      f_delta = 0.05f ;  // incremento/decr. del tamaño un 5% al pulsar
   //cout << "GestionEventoTeclaNormalObjeto(key==" << key << ")" << endl << flush ;
   switch( key )
   {
      case '+' :
         if ( f_esc_obj < 10.0f )
            f_esc_obj *= (1.0f+f_delta) ;
         break ;
      case '-' :
         if ( f_esc_obj > 0.1f ) 
            f_esc_obj /= (1.0f+f_delta) ;
         break ;
      default :
         cout << "tecla no usable en este modo." << endl << flush ;
         actualizar = false ;
         break ;
   }
   return actualizar ;
}

//**********************************************************************

bool GestionEventoTeclaEspecialTipoObjeto( int key )
{  
   
}

//**********************************************************************
// gestor del evento de pulsación de tecla especial en modo 'cámara'

bool GestionEventoTeclaEspecialCamara( int key )
{
   bool actualizar = true ;
   
   const GLfloat incr = 3.0 ;
   
   
   switch( key )
   {
      case GLUT_KEY_UP :
         lati_cam = minim( lati_cam+incr, 89.7f );
         
         break ;
      case GLUT_KEY_DOWN :
         lati_cam = maxim( lati_cam-incr, -89.7f );
         break ;
      case GLUT_KEY_LEFT :
         longi_cam += incr ;
         break ;
      case GLUT_KEY_RIGHT :
         longi_cam -= incr ;
         break ;
      case GLUT_KEY_HOME :
         longi_cam = longi_cam_ini ;
         lati_cam  = lati_cam_ini ;
         dis_cam   = dis_cam_ini ;
         break;
      default:
         actualizar = false ;
         cout << "tecla no usada en modo 'cámara'" << endl << flush ;
         break ;
   }
   return actualizar ;
}

//**********************************************************************

bool GestionEventoTeclaNormalCamara( unsigned char key ) 
{
   using namespace std ;
   bool 
      actualizar = true ;
   const float
      f_delta = 0.05f ;  // incremento/decr. de distancia un 5% al pulsar +/-
   //cout << "GestionEventoTeclaNormalCamara(key==" << key << ")" << endl << flush ;
   
   switch( key )
   {
      case '-' :
         if ( dis_cam < 10.0f )
            dis_cam *= (1.0f+f_delta) ;
         break ;
      case '+' :
         if ( dis_cam > 0.1f ) 
            dis_cam /= (1.0f+f_delta) ;
         break ;
      default :
         cout << "tecla no usable en este modo." << endl << flush ;
         actualizar = false ;
         break ;
   }
   return actualizar ;
}


//**********************************************************************

void GestionEventoTeclaNormal( unsigned char key, int x, int y )
{
   using namespace std ;
   bool
      actualizar = true ;
   char 
      upper_key = toupper(key);
   
   switch( upper_key )
   {
      case ' ' :
         modo_tecl_actual = ModoTeclado( (unsigned(modo_tecl_actual)+1) % num_modos_teclado ) ;
         cout << "modo teclado: " << descr_mt[modo_tecl_actual] << endl << flush ;
         break ;
      case 27  :  // código de la tecla 'escape' 
      case 'Q' : 
         Terminar();
         exit(0);
         break ; // inútil, pero si se quita el exit.....
      default  :
         switch ( modo_tecl_actual )
         {
            case mt_rot_objeto :
               actualizar = GestionEventoTeclaNormalObjeto(key) ;
               break ;
            case mt_par_camara :
               actualizar = GestionEventoTeclaNormalCamara(key) ;
               break ;
               
            
            default :
               actualizar = false ;
               cout << "tecla no usada en este modo." << endl << flush ;
               break ;
         }
         if ( actualizar )
            glutPostRedisplay();
         break ;
   }
}

//**********************************************************************

void GestionEventoTeclaEspecial( int key, int x, int y )
{
   using namespace std ;
   bool redisplay = false ;
   assert( fuente_luz_0 != NULL );
   
   assert( num_modos_teclado <= 12 );
   
   // acceso directo a los modos con las teclas de función
   // (asume valores consecutivos de GLUT_KEY_Fi)
   if ( GLUT_KEY_F1 <= key && key < GLUT_KEY_F1+num_modos_teclado )
   {
      modo_tecl_actual = ModoTeclado( key - GLUT_KEY_F1 );
      cout << "modo teclado: " << descr_mt[modo_tecl_actual] << endl << flush ;
   }
   else
   {  switch( modo_tecl_actual ) // gestionar la tecla en cada modo
   
      {
   
         case mt_rot_objeto :
            obj_ply->disminuir_cam();
            dibuorbi=true;
            vistanave=false;
            vistaluna=false;
            redisplay = GestionEventoTeclaEspecialObjeto(key) ;
            //DibujarVentana();
            break ;
         case mt_rot_luz :
            obj_ply->disminuir_cam();
            dibuorbi=false;
            vistanave=false;
            vistaluna=false;
            redisplay = fuente_luz_0->gestionarEventoTeclaEspecial(key) ;
           // DibujarVentana();
            break ;
        case mt_par_camara :
            obj_ply->disminuir_cam();
            dibuorbi=false;
            vistanave=false;
            vistaluna=false;

            redisplay = GestionEventoTeclaEspecialCamara(key) ;
            break ;
         case mt_tipo_dibujo_objeto://CAMARA DESDE LA LUNA
            obj_ply->disminuir_cam();
            dibuorbi=false;
            vistanave=false;
            vistaluna=true;

            glutPostRedisplay();
 
            break ;
         case mt_material_ply ://CAMARA DESDE LA NAVE
            obj_ply->ampliar_cam();
            dibuorbi=false;
            vistanave=true;
            vistaluna=false;
            glutPostRedisplay();
           
            break ;
            
        
         default :
            cout << "tecla (aun) no usable en este modo" << endl << flush ;
            break ;
      }
   }
   if ( redisplay )
      glutPostRedisplay();
}

//***************************************************************************
// Funcion IDLE
// Procedimiento de fondo. Es llamado por glut cuando no hay eventos pendientes.
//***************************************************************************

void idle()
{
  if(accionarrotacion1){
    obj_esfera_mercurio->activarrotacion();
    obj_esfera_mercurio->rotacion();
   } else if(!accionarrotacion1)
         obj_esfera_mercurio->desactivarrotacion();
   
    if(accionarrotacion2){
    obj_esfera_venus->activarrotacion();
    obj_esfera_venus->rotacion();
   } else if(!accionarrotacion2)
         obj_esfera_venus->desactivarrotacion();
         
     if(accionarrotacion3){
    obj_esfera_mundo->activarrotacion();
    obj_esfera_mundo->rotacion();
   } else if(!accionarrotacion3)
         obj_esfera_mundo->desactivarrotacion();
         
      if(accionarrotacion4){
    obj_esfera_marte->activarrotacion();
    obj_esfera_marte->rotacion();
   } else if(!accionarrotacion4)
         obj_esfera_marte->desactivarrotacion();
         
      if(accionarrotacion5){
    obj_esfera_jupiter->activarrotacion();
    obj_esfera_jupiter->rotacion();
   } else if(!accionarrotacion5)
         obj_esfera_jupiter->desactivarrotacion();
         
       if(accionarrotacion6){
    obj_esfera_saturno->activarrotacion();
    obj_esfera_saturno->rotacion();
   } else if(!accionarrotacion6)
         obj_esfera_saturno->desactivarrotacion();
         
        if(accionarrotacion7){
    obj_esfera_neptuno->activarrotacion();
    obj_esfera_neptuno->rotacion();
   } else if(!accionarrotacion7)
         obj_esfera_neptuno->desactivarrotacion();
         
      if(accionarrotacion8){
    obj_esfera_urano->activarrotacion();
    obj_esfera_urano->rotacion();
   } else if(!accionarrotacion8)
         obj_esfera_urano->desactivarrotacion();
         

  obj_esfera_mundo->orbita();
  camaragiro--;
  camaragiro2--;
  
  obj_esfera_venus->orbita();
  obj_esfera_mercurio->orbita();
  obj_esfera_luna->orbita();
  obj_esfera_lunamarteuno->orbita();
  obj_esfera_lunamartedos->orbita();
  
  obj_esfera_saturno->orbita();
  obj_esfera_anillosaturno->orbita();

    
  obj_esfera_marte->orbita();
  obj_esfera_jupiter->orbita();
     
  obj_esfera_lunajupiter->orbita();
  obj_esfera_lunajupiter2->orbita();
  obj_esfera_lunaurano->orbita();
  obj_esfera_urano->orbita();
  obj_esfera_neptuno->orbita();
  
  obj_ply->orbita();

  glutPostRedisplay();

}




//**********************************************************************

int main( int argc, char *argv[] )
{
   // comprobar parámetros
   if ( argc < 3 )
   {  cout << "uso: " << argv[0] << "  <archivo.ply (sin extension)>  <archivo.jpg (con extension)>" << endl << flush ;
      exit(1);
   }
   
   // inicializar glut
   glutInit(&argc, argv);
   
   // crear ventana
   anchoActual = int( 0.85f*glutGet(GLUT_SCREEN_HEIGHT) ) ;
   altoActual  = anchoActual ;
   glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
   glutInitWindowSize(anchoActual,altoActual);
   glutCreateWindow("IG 12-13 : practica 4");
   
   // definir callbacks
   glutDisplayFunc( DibujarVentana ) ;
   glutReshapeFunc( FuncRedimensionar );
   glutMouseFunc( GestionEventoRaton );
   glutKeyboardFunc( GestionEventoTeclaNormal ) ;
   glutSpecialFunc( GestionEventoTeclaEspecial ); 
   
   // inicializar objetos de la aplicación
   Inicializa(argc,argv) ;
   
  
 
   // asignación de la funcion "idle" para ejecución de fondo
   glutIdleFunc( idle);

   // bucle de eventos
   glutMainLoop();
   
   // terminar la aplicación
   Terminar() ;
   return 0 ;
}


