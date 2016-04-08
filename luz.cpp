#include <GL/glu.h>
#include <GL/glut.h>
#include "aux-p4.hpp"
#include "materiales.hpp"

#include "luz.hpp"

FuenteLuz::FuenteLuz( GLenum p_ind_fuente, GLfloat p_longi_ini, GLfloat p_lati_ini, const vectorRGB & p_color )
{
   assert( glGetError() == GL_NO_ERROR );
   
   // guardar el indice opengl de la fuente, y comprobar que es 
   // alguno de GL_LIGHT0, GL_LIGHT1, etc.....
   
   ind_fuente = p_ind_fuente ;
   GLenum max_num_fuentes ;
   
   glGetIntegerv( GL_MAX_LIGHTS, (GLint *) &max_num_fuentes );
   assert( GL_LIGHT0 <= ind_fuente );
   assert( ind_fuente <= GL_LIGHT0 + max_num_fuentes );
   
   // inicializar parámetros de la fuente de luz
   longi_ini = p_longi_ini ;
   lati_ini  = p_lati_ini  ;
   longi = longi_ini ;
   lati  = lati_ini ;
   
   col_ambiente  = p_color ;
   col_difuso    = p_color ;
   col_especular = p_color ;
   
   assert( glGetError() == GL_NO_ERROR );
}

//----------------------------------------------------------------------

void FuenteLuz::activar()
{

GLfloat Light_position[6]={0, 0, 0, 1,128,180.0};

GLfloat Ambient_component[4]={col_ambiente.x,col_ambiente.y,col_ambiente.z,1};
GLfloat Difu_component[4]={col_difuso.x,col_difuso.y,col_difuso.z,1};
GLfloat Especu_component[4]={col_especular.x,col_especular.y,col_especular.z,1};

glEnable(GL_LIGHTING);
glEnable(ind_fuente);
glEnable(GL_RESCALE_NORMAL);

//glLightModelfv(GL_LIGHT_MODEL_AMBIENT,Ambient_component);
//glLightModelfv(GL_DIFFUSE,Difu_component);
//glLightModelfv(GL_SPECULAR,Especu_component);

glLightModeli( GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE );

glLightfv(ind_fuente, GL_AMBIENT, Ambient_component);
glLightfv(ind_fuente, GL_DIFFUSE, Difu_component);
glLightfv(ind_fuente, GL_SPECULAR, Especu_component);


glMatrixMode(GL_MODELVIEW);
glPushMatrix();
	//glLoadIdentity();
	glRotatef(longi,1.0,1.0,1.0);
	glRotatef(lati,0.0,0.0,0.0);	
	glLightfv(ind_fuente,GL_POSITION,Light_position);
glPopMatrix();


}

//----------------------------------------------------------------------

bool FuenteLuz::gestionarEventoTeclaEspecial( int key ) 
{
   bool actualizar = true ;
   const float incr = 3.0f ;
   
   switch( key )
   {
      case GLUT_KEY_RIGHT:
         longi = longi+incr ;
         break ;
      case GLUT_KEY_LEFT:
         longi = longi-incr ;
         break ;
      case GLUT_KEY_UP:
         lati = minim( lati+incr, 90.0) ;
         break ;
      case GLUT_KEY_DOWN:
         lati = maxim( lati-incr, -90.0 ) ;
         break ;
      case GLUT_KEY_HOME:
         lati  = lati_ini ;
         longi = longi_ini ;
         break ;
      default :
         actualizar = false ;
         cout << "tecla no usable para la fuente de luz." << endl << flush ;
   }
   
   //if ( actualizar )
   //   cout << "fuente de luz cambiada: longi == " << longi << ", lati == " << lati << endl << flush ;
   return actualizar ;
}
