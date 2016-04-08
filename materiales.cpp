#include <GL/glu.h>
#include <GL/glut.h>
#include "aux-p4.hpp"
#include "materiales.hpp"

#include "luz.hpp"


//**********************************************************************

Material::Material() 
{
   iluminacion = false ;
   tex = NULL ;
   
   coloresCero() ;
}

//----------------------------------------------------------------------

Material::Material( const std::string & nombreArchivoJPG ) 
{
   iluminacion    = false ;
   tex            = new Textura( nombreArchivoJPG ) ;
   
   coloresCero();
   
   del.difusa = vectorRGB( 0.5, 0.5, 0.5 );
   tra.difusa = vectorRGB( 0.2, 0.2, 0.2 );
   
   del.especular = vectorRGB( 1.0, 1.0, 1.0 );
   tra.especular = vectorRGB( 0.2, 0.2, 0.2 );
}

//----------------------------------------------------------------------

void Material::coloresCero()
{
   const vectorRGB ceroRGB(0.0,0.0,0.0);
   
   color         = 
   
   del.emision   = 
   del.ambiente  = 
   del.difusa    = 
   del.especular = 

   tra.emision   = 
   tra.ambiente  = 
   tra.difusa    = 
   tra.especular = ceroRGB ;
   
   del.exp_brillo = 
   tra.exp_brillo = 1.0 ;
}

//----------------------------------------------------------------------

Material::~Material() 
{      
   if ( tex != NULL )
   {  delete tex ;
      tex = NULL ;
   }
}


//----------------------------------------------------------------------

void Material::activar()
{
GLfloat del_Emision_component[4]={del.emision.x,del.emision.y,del.emision.z,1.0};
GLfloat del_Ambient_component[4]={del.ambiente.x,del.ambiente.y,del.ambiente.z,1.0};
GLfloat del_Difu_component[4]={del.difusa.x,del.difusa.y,del.difusa.z,1};
GLfloat del_Especu_component[4]={del.especular.x,del.especular.y,del.especular.z,1.0};

GLfloat tra_Emision_component[4]={tra.emision.x,tra.emision.y,tra.emision.z,1.0};
GLfloat tra_Ambient_component[4]={tra.ambiente.x,tra.ambiente.y,tra.ambiente.z,1.0};
GLfloat tra_Difu_component[4]={tra.difusa.x,tra.difusa.y,tra.difusa.z,1.0};
GLfloat tra_Especu_component[4]={tra.especular.x,tra.especular.y,tra.especular.z,1.0};

GLfloat component[4]={color.x,color.y,color.z,1.0};

glDisable(GL_CULL_FACE);
glPolygonMode(GL_FRONT,GL_FILL);
glPolygonMode(GL_BACK,GL_FILL);


if(tex!=NULL)  
	tex->activar(); 
	
if(tex==NULL)  {
	glDisable(GL_TEXTURE_2D);
	
	glColorMaterial(GL_FRONT_AND_BACK, GL_EMISSION);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
	glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	
	}

if(iluminacion){
	glEnable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);// tutoria deshabilitar color material 1 para delanteras y traseras
	glEnable(GL_NORMALIZE);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, component);

	//MEFALTA-1 tutoria gl LIGHMODEL activar light model de 2 caras
	//MEFALTA -2 gl lightmodel activar evaulación por separado de la componente especular

	//glLightModelf( GL_DIFFUSE, color ) ;
	//glLightModelf( GL_SPECULAR, color ) ;
	//glLightModelf( GL_EMISSION, color ) ;


	//CARAS DELANTERAS
	
	glMaterialfv( GL_FRONT, GL_EMISSION, del_Emision_component ) ;
	
	// hace M A := (r, g, b), inicialmente (0.2,0.2,0.2)
	glMaterialfv( GL_FRONT, GL_AMBIENT, del_Ambient_component ) ;
	// hace MD := (r, g, b), inicialmente (0.8,0.8,0.8)
	glMaterialfv( GL_FRONT, GL_DIFFUSE, del_Difu_component ) ;
	// hace MS := (r, g, b), inicialmente (0,0,0)	
	glMaterialfv( GL_FRONT, GL_SPECULAR, del_Especu_component ) ;
	// hace e := v, inicialmente 0.0 (debe estar entre 0.0 y 128.0)
	glMaterialf( GL_FRONT, GL_SHININESS, del.exp_brillo ) ;
	
	
	//CARAS TRASERAS
	
	glMaterialfv( GL_BACK, GL_EMISSION, tra_Emision_component ) ;
	
	// hace M A := (r, g, b), inicialmente (0.2,0.2,0.2)
	glMaterialfv( GL_BACK, GL_AMBIENT, tra_Ambient_component ) ;
	// hace MD := (r, g, b), inicialmente (0.8,0.8,0.8)
	glMaterialfv( GL_BACK, GL_DIFFUSE, tra_Difu_component ) ;
	// hace MS := (r, g, b), inicialmente (0,0,0)
	glMaterialfv( GL_BACK, GL_SPECULAR, tra_Especu_component ) ;
	// hace e := v, inicialmente 0.0 (debe estar entre 0.0 y 128.0)
	glMaterialf( GL_BACK, GL_SHININESS, tra.exp_brillo ) ;
	
	

	
}else{
	glDisable(GL_LIGHTING);// color del material cuando iluminacion==false
	glColor4fv(component);


}
glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Reflexiones Delanteras
	glColorMaterial(GL_FRONT, GL_EMISSION);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glColorMaterial(GL_FRONT, GL_SPECULAR);

	// Reflexiones Traseras
	glColorMaterial(GL_BACK, GL_EMISSION);
	glColorMaterial(GL_BACK, GL_AMBIENT);
	glColorMaterial(GL_BACK, GL_DIFFUSE);
	glColorMaterial(GL_BACK, GL_SPECULAR);

 
}
void Material::activarsol()
{
GLfloat del_Emision_component[4]={del.emision.x,del.emision.y,del.emision.z,1.0};
GLfloat del_Ambient_component[4]={del.ambiente.x,del.ambiente.y,del.ambiente.z,1.0};
GLfloat del_Difu_component[4]={del.difusa.x,del.difusa.y,del.difusa.z,1};
GLfloat del_Especu_component[4]={del.especular.x,del.especular.y,del.especular.z,1.0};

GLfloat tra_Emision_component[4]={tra.emision.x,tra.emision.y,tra.emision.z,1.0};
GLfloat tra_Ambient_component[4]={tra.ambiente.x,tra.ambiente.y,tra.ambiente.z,1.0};
GLfloat tra_Difu_component[4]={tra.difusa.x,tra.difusa.y,tra.difusa.z,1.0};
GLfloat tra_Especu_component[4]={tra.especular.x,tra.especular.y,tra.especular.z,1.0};

GLfloat component[4]={255,255,0,1.0};

glDisable(GL_CULL_FACE);
glPolygonMode(GL_FRONT,GL_FILL);
glPolygonMode(GL_BACK,GL_FILL);


if(tex!=NULL)  
	tex->activar(); 
	
if(tex==NULL)  {
	glDisable(GL_TEXTURE_2D);
	
	glColorMaterial(GL_FRONT_AND_BACK, GL_EMISSION);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
	glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	
	}


	//glEnable(GL_LIGHTING);
	//glEnable(GL_COLOR_MATERIAL);// tutoria deshabilitar color material 1 para delanteras y traseras
	//glEnable(GL_NORMALIZE);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, component);

 
}

void Material::activarfondo()
{
GLfloat del_Emision_component[4]={del.emision.x,del.emision.y,del.emision.z,1.0};
GLfloat del_Ambient_component[4]={del.ambiente.x,del.ambiente.y,del.ambiente.z,1.0};
GLfloat del_Difu_component[4]={del.difusa.x,del.difusa.y,del.difusa.z,1};
GLfloat del_Especu_component[4]={del.especular.x,del.especular.y,del.especular.z,1.0};

GLfloat tra_Emision_component[4]={tra.emision.x,tra.emision.y,tra.emision.z,1.0};
GLfloat tra_Ambient_component[4]={tra.ambiente.x,tra.ambiente.y,tra.ambiente.z,1.0};
GLfloat tra_Difu_component[4]={tra.difusa.x,tra.difusa.y,tra.difusa.z,1.0};
GLfloat tra_Especu_component[4]={tra.especular.x,tra.especular.y,tra.especular.z,1.0};

GLfloat component[4]={color.x,color.y,color.z,1.0};

glDisable(GL_CULL_FACE);//glfront face
glDisable(GL_FRONT_FACE);
glPolygonMode(GL_FRONT,GL_FILL);
glPolygonMode(GL_BACK,GL_FILL);


if(tex!=NULL)  
	tex->activar(); 
	
if(tex==NULL)  {
	glDisable(GL_TEXTURE_2D);
	
	glColorMaterial(GL_FRONT_AND_BACK, GL_EMISSION);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
	glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	
	}

if(iluminacion){
	glEnable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);// tutoria deshabilitar color material 1 para delanteras y traseras
	glEnable(GL_NORMALIZE);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, component);

	//MEFALTA-1 tutoria gl LIGHMODEL activar light model de 2 caras
	//MEFALTA -2 gl lightmodel activar evaulación por separado de la componente especular

	//glLightModelf( GL_DIFFUSE, color ) ;
	//glLightModelf( GL_SPECULAR, color ) ;
	//glLightModelf( GL_EMISSION, color ) ;


	//CARAS DELANTERAS
	
	glMaterialfv( GL_FRONT, GL_EMISSION, del_Emision_component ) ;
	
	// hace M A := (r, g, b), inicialmente (0.2,0.2,0.2)
	glMaterialfv( GL_FRONT, GL_AMBIENT, del_Ambient_component ) ;
	// hace MD := (r, g, b), inicialmente (0.8,0.8,0.8)
	glMaterialfv( GL_FRONT, GL_DIFFUSE, del_Difu_component ) ;
	// hace MS := (r, g, b), inicialmente (0,0,0)	
	glMaterialfv( GL_FRONT, GL_SPECULAR, del_Especu_component ) ;
	// hace e := v, inicialmente 0.0 (debe estar entre 0.0 y 128.0)
	glMaterialf( GL_FRONT, GL_SHININESS, del.exp_brillo ) ;
	
	
	//CARAS TRASERAS
	
	glMaterialfv( GL_BACK, GL_EMISSION, tra_Emision_component ) ;
	
	// hace M A := (r, g, b), inicialmente (0.2,0.2,0.2)
	glMaterialfv( GL_BACK, GL_AMBIENT, tra_Ambient_component ) ;
	// hace MD := (r, g, b), inicialmente (0.8,0.8,0.8)
	glMaterialfv( GL_BACK, GL_DIFFUSE, tra_Difu_component ) ;
	// hace MS := (r, g, b), inicialmente (0,0,0)
	glMaterialfv( GL_BACK, GL_SPECULAR, tra_Especu_component ) ;
	// hace e := v, inicialmente 0.0 (debe estar entre 0.0 y 128.0)
	glMaterialf( GL_BACK, GL_SHININESS, tra.exp_brillo ) ;
	
	

	
}else{
	glDisable(GL_LIGHTING);// color del material cuando iluminacion==false
	glColor4fv(component);


}
glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Reflexiones Delanteras
	glColorMaterial(GL_FRONT, GL_EMISSION);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glColorMaterial(GL_FRONT, GL_SPECULAR);

	// Reflexiones Traseras
	glColorMaterial(GL_BACK, GL_EMISSION);
	glColorMaterial(GL_BACK, GL_AMBIENT);
	glColorMaterial(GL_BACK, GL_DIFFUSE);
	glColorMaterial(GL_BACK, GL_SPECULAR);

 
}

//**********************************************************************


