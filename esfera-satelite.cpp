
#include <ctype.h>
#include <cmath>
#include <iostream>
#include <vector>

#include <GL/gl.h>
#include <GL/glut.h>

#include "jpg_imagen.hpp"
#include "materiales.hpp"
#include "objetos-4.hpp"
#include "esfera-satelite.hpp"
#include "luz.hpp"

using namespace std;


//**********************************************************************
//
// Clase MatEsferaLuna
// -----------------------
// clase para el material de la luna
//
//**********************************************************************

class MatEsferaSatelite : public Material 
{ 
   public: 
   MatEsferaSatelite(string & nombreArchivoJPG ) ; 
} ;

//----------------------------------------------------------------------

MatEsferaSatelite::MatEsferaSatelite(string & nombreArchivoJPG )
{
   coloresCero() ; // no necesario?
   
   iluminacion    = true ;
   tex         = new Textura( nombreArchivoJPG  ) ;
   //tex            = new Textura( "rejilla.jpg" ) ;
   
   del.ambiente  = vectorRGB( 0.1,0.1,0.1 ) ;
   del.difusa    = vectorRGB( 0.8,0.8,0.9 ) ;
   del.especular = vectorRGB( 1.0,1.0,1.0 ) ;
   del.exp_brillo = 120.0f ;
   
   tra.difusa    = vectorRGB( 0.2,0.2,0.2 ) ;
   tra.especular = vectorRGB( 0.0,0.0,0.0 ) ;
   tra.exp_brillo = 60 ;
}

//**********************************************************************
//
// Clase satelite
//
//**********************************************************************

EsferaSatelite::EsferaSatelite(string & nombreArchivoJPG,float var1,float var2,float var3,float var4,float var5,float var6,float var7,float var8,float var9,float var10,float var11,float var12,float var13,float var14,float var15,float var16,float var17,float var18,float var19,float var20,float var21 )

:  _sup_par_triangles_object3D( 64, 64, FPEsfera() ) 
{
   material = new MatEsferaSatelite( nombreArchivoJPG ) ;
   
   tamx=var1;
   tamy=var2;
   tamz=var3;
   
   orbitavar=var4;  //0.5
   orbitavarx=var5;
   orbitavary=var6;
   orbitavarz=var7;
   
   rotacionprovar=var8;
   rotacionprovarx=var9;
   rotacionprovary=var10;
   rotacionprovarz=var11;
   
   disx=var12;
   disy=var13;
   disz=var14;
   
   orbitaplaneta=var15;   //10
   orbitaplanetax=var16;
   orbitaplanetay=var17;
   orbitaplanetaz=var18;
   
   displanesolx=var19 ;
   displanesoly=var20 ;
   displanesolz=var21 ;
   
   
   
   eventorotacion=false;
   
   
   if(!Vertices_normals_computed)
    compute_vertices_normals();
   
   for(int i=0;i<Vertices.size();i++){
    Nuevos_Vertices.push_back(Vertices[i].x);
    Nuevos_Vertices.push_back(Vertices[i].y);
    Nuevos_Vertices.push_back(Vertices[i].z);
}

for( int w=0;w<Faces_vertices.size();w++){
    Nuevos_Faces_vertices.push_back(Faces_vertices[w].x);
    Nuevos_Faces_vertices.push_back(Faces_vertices[w].y);
    Nuevos_Faces_vertices.push_back(Faces_vertices[w].z);
}

for(int ko=0;ko<Vertices_normals.size();ko++){
    Nuevos_Vertices_normals.push_back(Vertices_normals[ko].x);
    Nuevos_Vertices_normals.push_back(Vertices_normals[ko].y);
    Nuevos_Vertices_normals.push_back(Vertices_normals[ko].z);
}

for( int lol=0;lol<Vertices_tex_coords.size();lol++){
    Nuevos_Vertices_tex_coords.push_back(Vertices_tex_coords[lol].x);
    Nuevos_Vertices_tex_coords.push_back(Vertices_tex_coords[lol].y);
    
}


}

void EsferaSatelite::draw_solid_material_gouroud()
{
int Vertex_1,Vertex_2,Vertex_3,j=0;


glShadeModel(GL_SMOOTH);
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
material->activar();





glEnableClientState( GL_VERTEX_ARRAY );
glVertexPointer(3, GL_FLOAT, 0, &Vertices[0] );

glEnableClientState( GL_INDEX_ARRAY );
glIndexPointer( GL_UNSIGNED_INT, 0,&Faces_vertices[0] );

glEnableClientState( GL_NORMAL_ARRAY);
glNormalPointer(GL_FLOAT,0,&Vertices_normals[0]);

glEnableClientState(GL_TEXTURE_COORD_ARRAY);
glTexCoordPointer(2, GL_FLOAT,  0, &Vertices_tex_coords[0]);

//glInitNames();

glPushMatrix();
	glRotatef(orbitaplaneta,orbitaplanetax,orbitaplanetay,orbitaplanetaz);//0 1   0
	glTranslatef(displanesolx, displanesoly,displanesolz);   //displanesol    4  0  0
	
	

	glPushMatrix();
	
 
		     //0.2
		glRotatef(orbitavar,orbitavarx,orbitavary,orbitavarz);     //0    1    0
		glTranslatef(	disx, disy, disz);  //4   0.5 0
		//glRotatef(rotacionprovar,rotacionprovarx,rotacionprovary,rotacionprovarz);   //0.1
		glScaled(tamx,tamy,tamz);


		//glLoadName(indice);

		glDrawElements( GL_TRIANGLES, Faces_vertices.size()*3, GL_UNSIGNED_INT, &Faces_vertices[0] );


	//glPopName();
	glPopMatrix();

glPopMatrix();

}

void  EsferaSatelite::rotacion(){
  
  rotacionprovar=rotacionprovar+1;
 }
 
void  EsferaSatelite::orbita(){
  
  orbitavar=orbitavar+1;
  orbitaplaneta=orbitaplaneta+1;
 }

void EsferaSatelite::activarrotacion(){

    eventorotacion=true;
}

void EsferaSatelite::desactivarrotacion(){

    eventorotacion=false;

}
