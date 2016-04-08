
#include <ctype.h>
#include <cmath>
#include <iostream>
#include <vector>

#include <GL/gl.h>
#include <GL/glut.h>

#include "jpg_imagen.hpp"
#include "materiales.hpp"
#include "objetos-4.hpp"
#include "esfera-planeta.hpp"
#include "luz.hpp"

using namespace std;



//**********************************************************************
//
// Clase MatEsferaMundo
// -----------------------
// clase para el material de la esfera del mundo
//
//**********************************************************************

class MatEsferaPlaneta : public Material 
{ 
   public: 
   MatEsferaPlaneta(string & nombreArchivoJPG) ; 
} ;

//----------------------------------------------------------------------

MatEsferaPlaneta::MatEsferaPlaneta(string & nombreArchivoJPG)
{
   coloresCero() ; // no necesario?
   
   iluminacion    = true ;
   tex            = new Textura(  nombreArchivoJPG ) ;
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
// Clase EsferaPlaneta
//
//**********************************************************************

EsferaPlaneta::EsferaPlaneta(float v,int i,string & nombreArchivoJPG,float var1,float var2,float var3,float var4,float var5,float var6,float var7,float var8,float var9,float var10,float var11,float var12,float var13,float var14,float var15)

:  _sup_par_triangles_object3D( 64, 64, FPEsfera() ) 
{
   material = new MatEsferaPlaneta(nombreArchivoJPG) ;
   //rotacionvar=0;
   //orbitavar=10;
   
   tamx=var1;
   tamy=var2;
   tamz=var3;
   
   orbitaplaneta=var8;
   orbitaplanetax=var9;
   orbitaplanetay=var10;
   orbitaplanetaz=var11;
   
   rotacionprovar=var4;
   rotacionprovarx=var5;
   rotacionprovary=var6;
   rotacionprovarz=var7;
   
   displanesolx=var12 ;
   displanesoly=var13 ;
   displanesolz =var14;
   
   radio=var15;
   
   eventorotacion=false;
   
    velocidad=v;
    indice=i;
   
   //obj_esfera_luna     = new EsferaLuna();
   
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

void EsferaPlaneta::draw_solid_material_gouroud()
{
int Vertex_1,Vertex_2,Vertex_3,j=0;
//glEnable(GL_CULL_FACE);
glShadeModel(GL_SMOOTH);
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
material->activar();




//glInitNames();


glPushMatrix();


glRotatef(orbitaplaneta,orbitaplanetax,orbitaplanetay,orbitaplanetaz);
glTranslatef(	displanesolx, displanesoly, displanesolz);
if(eventorotacion){
  //glPushMatrix();
  glRotatef(rotacionprovar,rotacionprovarx,rotacionprovary,rotacionprovarz);
  //glPopMatrix();
}

//obj_esfera_luna->draw_solid_material_gouroud();

glScaled(tamx,tamy,tamz);
//glLoadName(indice);

glEnableClientState( GL_VERTEX_ARRAY );
glVertexPointer(3, GL_FLOAT, 0, &Vertices[0] );

glEnableClientState( GL_INDEX_ARRAY );
glIndexPointer( GL_UNSIGNED_INT, 0,&Faces_vertices[0] );

glEnableClientState( GL_NORMAL_ARRAY);
glNormalPointer(GL_FLOAT,0,&Vertices_normals[0]);

glEnableClientState(GL_TEXTURE_COORD_ARRAY);
glTexCoordPointer(2, GL_FLOAT,  0, &Vertices_tex_coords[0]);

glLoadName(indice);
glDrawElements( GL_TRIANGLES, Faces_vertices.size()*3, GL_UNSIGNED_INT, &Faces_vertices[0] );


//glPopName();
glPopMatrix();


}



void  EsferaPlaneta::dibujaorbita(){

int iner=(double)radio-1;
 
 glPushMatrix();
 glRotatef(90,1,0,0);
 
 glutWireTorus( iner,
                    (double)radio,
                    1, 100);
 glPopMatrix();


}



void  EsferaPlaneta::rotacion(){
  
  rotacionprovar=rotacionprovar+velocidad;
 }
 
void  EsferaPlaneta::orbita(){
  
  orbitaplaneta=orbitaplaneta+velocidad;
 }

void EsferaPlaneta::activarrotacion(){

    eventorotacion=true;
}

void EsferaPlaneta::desactivarrotacion(){

    eventorotacion=false;

}

