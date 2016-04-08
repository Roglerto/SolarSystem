#include <GL/glu.h>
#include <GL/glut.h>
#include "aux-p4.hpp"
#include "materiales.hpp"

#include "luz.hpp"
#include "materiales.hpp"

//**********************************************************************

Textura::Textura( const std::string & nombreArchivoJPG ) 
{
// Constructor: lee el archivo y guarda los texels en memoria:
jpg::Imagen ima(nombreArchivoJPG);

imagen= &ima;

glGenTextures( 1, &ident_textura );
glBindTexture (GL_TEXTURE_2D, ident_textura);

gluBuild2DMipmaps( GL_TEXTURE_2D,
GL_RGB,
// formato interno
// Devuelve el número de columnas de la imagen:
ima.tamX()  ,
// Devuelve el número de filas de la imagen:
 ima.tamY()  ,
GL_RGB,
// formato y orden de los texels en RAM
GL_UNSIGNED_BYTE,
// tipo de cada componente de cada texel
// Devuelve un puntero a la zona donde estan los texels,
// puestos por filas, tres bytes (sin signo) por texel, en orden RGB:
 ima.leerPixels() 
// puntero a los bytes con texels (void *)
);


	
}

//----------------------------------------------------------------------

Textura::~Textura( ) 
{
  if(imagen!=NULL){
		delete imagen;
		imagen = NULL;
	}
}

//----------------------------------------------------------------------

void Textura::activar( ) 
{
glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ident_textura);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if(modo_gen_ct==mgct_coords_objeto){
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGenfv( GL_S, GL_OBJECT_PLANE, coefs_s ) ;
		glTexGenfv( GL_T, GL_OBJECT_PLANE, coefs_t ) ;
	}
   

}

