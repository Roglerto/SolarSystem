
#include <ctype.h>
#include <cmath>
#include <iostream>
#include <vector>

#include <GL/gl.h>
#include <GL/glut.h>

#include "jpg_imagen.hpp"
#include "materiales.hpp"
#include "objetos-4.hpp"
#include "esfera-sol.hpp"
#include "luz.hpp"

using namespace std;


//**********************************************************************
//
// Clase MatEsferaSOL
// -----------------------
// clase para el material del cuerpo de la esfera SOL
//
//**********************************************************************

class MatEsferaSol : public Material 
{ 
   public: 
   MatEsferaSol() ; 
} ;

//----------------------------------------------------------------------
// Constructor

MatEsferaSol::MatEsferaSol()
{
    coloresCero() ; // no necesario?
   
   iluminacion    = true ;
   tex            = new Textura( "sol.jpg" ) ;
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
// Clase EsferaSol
//
//**********************************************************************

EsferaSol::EsferaSol()

:  _sup_par_triangles_object3D( 64, 64, FPEsfera() ) 
{
   material = new MatEsferaSol() ;
   
   
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

void EsferaSol::draw_solid_material_gouroud()
{
int Vertex_1,Vertex_2,Vertex_3,j=0;

glShadeModel(GL_SMOOTH);
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
material->activarsol();




glEnableClientState( GL_VERTEX_ARRAY );
glVertexPointer(3, GL_FLOAT, 0, &Vertices[0] );

glEnableClientState( GL_INDEX_ARRAY );
glIndexPointer( GL_UNSIGNED_INT, 0,&Faces_vertices[0] );

glEnableClientState( GL_NORMAL_ARRAY);
glNormalPointer(GL_FLOAT,0,&Vertices_normals[0]);

glEnableClientState(GL_TEXTURE_COORD_ARRAY);
glTexCoordPointer(2, GL_FLOAT,  0, &Vertices_tex_coords[0]);




glPushMatrix();
glTranslatef(1, 0.5, 0.5);
glScalef(1.5,1.5,1.5); //1.5

glDrawElements( GL_TRIANGLES, Faces_vertices.size()*3, GL_UNSIGNED_INT, &Faces_vertices[0] );


glPopMatrix();


}



