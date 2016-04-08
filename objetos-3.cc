//**************************************************************************
// Práctica 3
//
// Domingo Martin Perandres 2005-2012
//
// GPL
//**************************************************************************

#include "file_ply_stl.hpp"
#include "objetos-3.h" 
#include "math.h"
#include "iostream"

using namespace std;


//*************************************************************************
// _object3D
//*************************************************************************
//*************************************************************************
//
//*************************************************************************

_object3D::_object3D()
{
  
  Point_size=POINT_SIZE;
  Line_width=LINE_WIDTH;
  
}



//*************************************************************************
//
//*************************************************************************

void _object3D::draw_points()
{
glDisable(GL_LIGHTING);
glDisable(GL_CULL_FACE);
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glColor4f(1,0,0,1);
glPointSize(5);

glBegin( GL_POINTS ) ;


for( int i=0 ; i < (int)Vertices.size() ; i++ ) {
	glVertex3f( Vertices[i].x, Vertices[i].y, Vertices[i].z );
}
glEnd() ;
  
}

//*************************************************************************
// _triangles_object3D
//*************************************************************************
 

_triangles_object3D::_triangles_object3D()
{
   Faces_normals_computed       = false ;
   Vertices_normals_computed    = false ;
   Vertices_tex_coords_computed = false ;
   material=NULL;  
   
   
   Point_size=POINT_SIZE;
Line_width=LINE_WIDTH;

Line_color.x=1;
Line_color.y=1;
Line_color.z=0;
Line_color.w=0;

Solid_color.x=0;
Solid_color.y=1;
Solid_color.z=1;
Solid_color.w=0;

Solid_chess_color1.x=0;
Solid_chess_color1.y=1;
Solid_chess_color1.z=1;
Solid_chess_color1.w=1;

Solid_chess_color2.x=0;
Solid_chess_color2.y=0;
Solid_chess_color2.z=1;
Solid_chess_color2.w=0;
}

//*************************************************************************
// Dibuja las aristas de los triangulos no iluminados
//*************************************************************************

void _triangles_object3D::draw_edges()
{   
glDisable(GL_LIGHTING);

glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glColor4f(Line_color.x,Line_color.y,Line_color.z,Line_color.w);
glBegin( GL_TRIANGLES ) ;

int Vertex_1,Vertex_2,Vertex_3;

for ( int i= 0 ; i < (int) Faces_vertices.size() ; i++ ){
	
	Vertex_1 = Faces_vertices[i].x ;
	Vertex_2 = Faces_vertices[i].y ;
	Vertex_3 = Faces_vertices[i].z ;
	
	glVertex3f( Vertices[Vertex_1].x, Vertices[Vertex_1].y,
	Vertices[Vertex_1].z);
	glVertex3f( Vertices[Vertex_2].x, Vertices[Vertex_2].y,
	Vertices[Vertex_2].z);
	glVertex3f( Vertices[Vertex_3].x, Vertices[Vertex_3].y,
	Vertices[Vertex_3].z);
}


glEnd() ;   
}

//*************************************************************************
// Dibuja triangulos no iluminados con apariencia de ajedrez
//*************************************************************************

void _triangles_object3D::draw_solid_chess()
{
int Vertex_1,Vertex_2,Vertex_3;

glDisable(GL_LIGHTING);
glDisable(GL_CULL_FACE);
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glBegin( GL_TRIANGLES );


for ( int i= 0 ; i < (int) Faces_vertices.size() ; i++ ){
	if ( i %2 == 0 ){ glColor4f(Solid_chess_color1.x,Solid_chess_color1.y,Solid_chess_color1.z,Solid_chess_color1.w) ;
		}else {glColor4f(Solid_chess_color2.x,Solid_chess_color2.y,Solid_chess_color2.z,Solid_chess_color2.w);
		}
	Vertex_1 = Faces_vertices[i].x ;
	Vertex_2 = Faces_vertices[i].y ;
	Vertex_3 = Faces_vertices[i].z ;
	
	glVertex3f( Vertices[Vertex_1].x, Vertices[Vertex_1].y,
	Vertices[Vertex_1].z);
	glVertex3f( Vertices[Vertex_2].x, Vertices[Vertex_2].y,
	Vertices[Vertex_2].z);
	glVertex3f( Vertices[Vertex_3].x, Vertices[Vertex_3].y,
	Vertices[Vertex_3].z);

}

glEnd() ;   
}

//*************************************************************************
// Dibuja triangulos no iluminados
//*************************************************************************

void _triangles_object3D::draw_solid_non_illuminated()
{

glDisable(GL_LIGHTING);
glDisable(GL_CULL_FACE);
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

int Vertex_1,Vertex_2,Vertex_3;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glColor4f(Solid_chess_color2.x,Solid_chess_color2.y,Solid_chess_color2.z,Solid_chess_color2.w);
glBegin( GL_TRIANGLES );


for ( int i= 0 ; i < (int) Faces_vertices.size() ; i++ ){

		
	Vertex_1 = Faces_vertices[i].x ;
	Vertex_2 = Faces_vertices[i].y ;
	Vertex_3 = Faces_vertices[i].z ;
	
	glVertex3f( Vertices[Vertex_1].x, Vertices[Vertex_1].y,
	Vertices[Vertex_1].z);
	glVertex3f( Vertices[Vertex_2].x, Vertices[Vertex_2].y,
	Vertices[Vertex_2].z);
	glVertex3f( Vertices[Vertex_3].x, Vertices[Vertex_3].y,
	Vertices[Vertex_3].z);

}

glEnd() ;
  
}



//*************************************************************************
// Dibuja puntos, aristas y caras a la vez
//*************************************************************************

void _triangles_object3D::draw_points_edges_solid_non_illuminated()
{
draw_points();
draw_edges();
draw_solid_non_illuminated();
}
//**********************************************************************





//**********************************************************************

/*
void _triangles_object3D::draw_solid_material_gouroud()
{
int Vertex_1,Vertex_2,Vertex_3,j=0;

if(Faces_normals_computed == false ){
   compute_faces_normals();
   Faces_normals_computed = true;
}
if(Vertices_normals_computed == false){
   compute_vertices_normals();
   Vertices_normals_computed = true;

}

glShadeModel(GL_SMOOTH);
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
material->activar();

cout<< "tamaño vertices "<< Nuevos_Vertices.size() <<endl;
cout<< "tamaño  caras"<<Nuevos_Faces_vertices.size() <<endl;
cout<< "tamaño  normales" << Nuevos_Vertices_normals.size() <<endl;
cout<< "tamaño  coord text"<<Nuevos_Vertices_tex_coords.size() <<endl;

for(int i=0;i<Vertices.size();i++){
    Nuevos_Vertices.push_back(Vertices[i].x);
    Nuevos_Vertices.push_back(Vertices[i].y);
    Nuevos_Vertices.push_back(Vertices[i].z);
}
j=0;
for( int w=0;w<Faces_vertices.size();w++){
    Nuevos_Faces_vertices.push_back(Faces_vertices[w].x);
    Nuevos_Faces_vertices.push_back(Faces_vertices[w].y);
    Nuevos_Faces_vertices.push_back(Faces_vertices[w].z);
}
j=0;
for(int ko=0;ko<Vertices_normals.size();ko++){
    Nuevos_Vertices_normals.push_back(Vertices_normals[ko].x);
    Nuevos_Vertices_normals.push_back(Vertices_normals[ko].y);
    Nuevos_Vertices_normals.push_back(Vertices_normals[ko].z);
}
j=0;
for( int lol=0;lol<Vertices_tex_coords.size();lol++){
    Nuevos_Vertices_tex_coords.push_back(Vertices_tex_coords[lol].x);
    Nuevos_Vertices_tex_coords.push_back(Vertices_tex_coords[lol].y);
    
}

cout<< "tamaño vertices "<< Nuevos_Vertices.size() <<endl;
cout<< "tamaño  caras"<<Nuevos_Faces_vertices.size() <<endl;
cout<< "tamaño  normales" << Nuevos_Vertices_normals.size() <<endl;
cout<< "tamaño  coord text"<<Nuevos_Vertices_tex_coords.size() <<endl;

glEnableClientState( GL_VERTEX_ARRAY );
glVertexPointer(3, GL_FLOAT, 0, &Vertices[0] );

glEnableClientState( GL_INDEX_ARRAY );
glIndexPointer( GL_UNSIGNED_INT, 0,&Faces_vertices[0] );

glEnableClientState( GL_NORMAL_ARRAY);
glNormalPointer(GL_FLOAT,0,&Vertices_normals[0]);

glEnableClientState(GL_TEXTURE_COORD_ARRAY);
glTexCoordPointer(2, GL_FLOAT,  0, &Vertices_tex_coords[0]);




glPushMatrix();
glTranslatef(	2, 0, 0);
////glScalef(2,2,2);

glDrawElements( GL_TRIANGLES, Faces_vertices.size()*3, GL_UNSIGNED_INT, &Faces_vertices[0] );


glPopMatrix();

glBegin( GL_TRIANGLES );



for ( int i= 0 ; i < (int) Faces_vertices.size() ; i++ ){

	
	Vertex_1 = Faces_vertices[i].x ;
	Vertex_2 = Faces_vertices[i].y ;
	Vertex_3 = Faces_vertices[i].z ;
	
	
	glTranslated(	100, 
 	0, 
 	0);
	
	glNormal3f( Vertices_normals[Vertex_1].x , Vertices_normals[Vertex_1].y,Vertices_normals[Vertex_1].z );
	glTexCoord2f(Vertices_tex_coords[Vertex_1].x,Vertices_tex_coords[Vertex_1].y );
	 glVertex3f( Vertices[Vertex_1].x, Vertices[Vertex_1].y,
	Vertices[Vertex_1].z);

	
	
	glTranslated(	100, 
 	0, 
 	0);

	glNormal3f( Vertices_normals[Vertex_2].x , Vertices_normals[Vertex_2].y ,
				Vertices_normals[Vertex_2].z );
	glTexCoord2f(Vertices_tex_coords[Vertex_2].x,Vertices_tex_coords[Vertex_2].y );
	 glVertex3f( Vertices[Vertex_2].x, Vertices[Vertex_2].y,
	Vertices[Vertex_2].z);

	
	
	glTranslated(	100, 
 	0, 
 	0);

	glNormal3f( Vertices_normals[Vertex_3].x , Vertices_normals[Vertex_3].y ,
				Vertices_normals[Vertex_3].z );
	glTexCoord2f(Vertices_tex_coords[Vertex_3].x,Vertices_tex_coords[Vertex_3].y );
	 glVertex3f( Vertices[Vertex_3].x, Vertices[Vertex_3].y,
	Vertices[Vertex_3].z);


	
}

glEnd() ;  
*/ 

void _triangles_object3D::draw_solid_material_flat()
{


int Vertex_1,Vertex_2,Vertex_3;

if(Faces_normals_computed == false ){
   compute_faces_normals();
   Faces_normals_computed = true;
}
if(Vertices_normals_computed == false){
   compute_vertices_normals();
   Vertices_normals_computed = true;

}


glShadeModel(GL_FLAT);
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
material->activar();

glBegin( GL_TRIANGLES );



for ( int i= 0 ; i < (int) Faces_vertices.size() ; i++ ){

	
	
	Vertex_1 = Faces_vertices[i].x ;
	Vertex_2 = Faces_vertices[i].y ;
	Vertex_3 = Faces_vertices[i].z ;
	
	glNormal3f( Vertices_normals[Vertex_1].x , Vertices_normals[Vertex_1].y ,
				Vertices_normals[Vertex_1].z );
	glTexCoord2f(Vertices_tex_coords[Vertex_1].x,Vertices_tex_coords[Vertex_1].y );
	 glVertex3f( Vertices[Vertex_1].x, Vertices[Vertex_1].y,
	Vertices[Vertex_1].z);
	
	glNormal3f( Vertices_normals[Vertex_2].x , Vertices_normals[Vertex_2].y ,
				Vertices_normals[Vertex_2].z );
	glTexCoord2f(Vertices_tex_coords[Vertex_2].x,Vertices_tex_coords[Vertex_2].y );
	 glVertex3f( Vertices[Vertex_2].x, Vertices[Vertex_2].y,
	Vertices[Vertex_2].z);
	
	glNormal3f( Vertices_normals[Vertex_3].x , Vertices_normals[Vertex_3].y ,
				Vertices_normals[Vertex_3].z );
	glTexCoord2f(Vertices_tex_coords[Vertex_3].x,Vertices_tex_coords[Vertex_3].y );
	 glVertex3f( Vertices[Vertex_3].x, Vertices[Vertex_3].y,
	Vertices[Vertex_3].z);
	

}

glEnd() ;

   
}


//*************************************************************************
//
//*************************************************************************

void _triangles_object3D::draw( _draw_type Draw_type )
{
switch (Draw_type){
	
	
	case SOLID_MATERIAL_FLAT:  draw_solid_material_flat(); break;
	//case SOLID_MATERIAL_GOUROUD:draw_solid_material_gouroud();  break;


}
  
}

void _triangles_object3D::draw_solid_normales_caras(){
int Vertex_1,Vertex_2,Vertex_3;

if(Faces_normals_computed == false ){
   compute_faces_normals();
   Faces_normals_computed = true;
}

glDisable(GL_LIGHTING);
glDisable(GL_CULL_FACE);
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
//glShadeMode(GL_FLAT);

glBegin( GL_TRIANGLES );



for ( int i= 0 ; i < (int) Faces_vertices.size() ; i++ ){

	if(Faces_normals[i].y<0){
		glColor4f(Solid_chess_color2.x,Faces_normals[i].y,Solid_chess_color2.z,Solid_chess_color2.w);
		
	}else glColor4f(Solid_chess_color1.x,Faces_normals[i].y,Solid_chess_color1.z,Solid_chess_color1.w);
	
	Vertex_1 = Faces_vertices[i].x ;
	Vertex_2 = Faces_vertices[i].y ;
	Vertex_3 = Faces_vertices[i].z ;
	
	glVertex3f( Vertices[Vertex_1].x, Vertices[Vertex_1].y,
	Vertices[Vertex_1].z);
	glVertex3f( Vertices[Vertex_2].x, Vertices[Vertex_2].y,
	Vertices[Vertex_2].z);
	glVertex3f( Vertices[Vertex_3].x, Vertices[Vertex_3].y,
	Vertices[Vertex_3].z);

}

glEnd() ;




}



void _triangles_object3D::draw_solid_normales_vertices(){


int Vertex_1,Vertex_2,Vertex_3;


if(Vertices_normals_computed == false){
   compute_vertices_normals();
   Vertices_normals_computed = true;

}

glDisable(GL_LIGHTING);
glDisable(GL_CULL_FACE);
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
//glShadeMode(GL_FLAT);

glBegin( GL_TRIANGLES );



for ( int i= 0 ; i < (int) Faces_vertices.size() ; i++ ){

	
	Vertex_1 = Faces_vertices[i].x ;
	Vertex_2 = Faces_vertices[i].y ;
	Vertex_3 = Faces_vertices[i].z ;
	
	if(Vertices_normals[Vertex_1].y<0){
		glColor4f(Solid_chess_color2.x,Vertices_normals[Vertex_1].y,Solid_chess_color2.z,Solid_chess_color2.w);
		
	}else glColor4f(Solid_chess_color1.x,Vertices_normals[Vertex_1].y,Solid_chess_color1.z,Solid_chess_color1.w);

	glVertex3f( Vertices[Vertex_1].x, Vertices[Vertex_1].y,
	Vertices[Vertex_1].z);

	if(Vertices_normals[Vertex_2].y<0){
		glColor4f(Solid_chess_color2.x,Vertices_normals[Vertex_2].y,Solid_chess_color2.z,Solid_chess_color2.w);
		
	}else glColor4f(Solid_chess_color1.x,Vertices_normals[Vertex_2].y,Solid_chess_color1.z,Solid_chess_color1.w);

	glVertex3f( Vertices[Vertex_2].x, Vertices[Vertex_2].y,
	Vertices[Vertex_2].z);

	if(Vertices_normals[Vertex_3].y<0){
		glColor4f(Solid_chess_color2.x,Vertices_normals[Vertex_3].y,Solid_chess_color2.z,Solid_chess_color2.w);
		
	}else glColor4f(Solid_chess_color1.x,Vertices_normals[Vertex_3].y,Solid_chess_color1.z,Solid_chess_color1.w);

	glVertex3f( Vertices[Vertex_3].x, Vertices[Vertex_3].y,
	Vertices[Vertex_3].z);

}

glEnd() ;




}



//*************************************************************************
// calcula las normales de las caras
//*************************************************************************

void _triangles_object3D::compute_faces_normals()
{
_vertex3f a,a2,a3,b,b2,b3,n1,n2,n3,c,c2,c3,abvector,acvector,dato;
int Vertex_1,Vertex_2,Vertex_3;


for(int i=0; i < (int) Faces_vertices.size(); i++){

	Vertex_1 = Faces_vertices[i].x ;
	Vertex_2 = Faces_vertices[i].y ;
	Vertex_3 = Faces_vertices[i].z ;




	a.x=Vertices[Vertex_1].x;
	a.y=Vertices[Vertex_1].y ; // vertice p1
	a.z=Vertices[Vertex_1].z;
	
	
	
	
	b.x=Vertices[Vertex_2].x;
	b.y=Vertices[Vertex_2].y ;  //vertice p0
	b.z=Vertices[Vertex_2].z;
	

	
	abvector.x=b.x-a.x;
	abvector.y=b.y-a.y ;   // vector A
	abvector.z=b.z-a.z;
	
	
	
	c.x=Vertices[Vertex_3].x;
	c.y=Vertices[Vertex_3].y ;   //vertice p2
	c.z=Vertices[Vertex_3].z;
	
		
	acvector.x=c.x-a.x;
	acvector.y=c.y-a.y ;   // vector A
	acvector.z=c.z-a.z;
	
	
	
	//CALCULAMOS producto vectorial de abvectorxacvector
	
	dato.x=(abvector.y*acvector.z) - (abvector.z*acvector.y);
	dato.y=(-1)* ((abvector.x*acvector.z) - (abvector.z*acvector.x));
	dato.z=(abvector.x*acvector.y) - (abvector.y*acvector.x);

	
	Faces_normals.push_back(dato);
	
	}

	for(int i=0; i < (int) Faces_normals.size(); i++){
	
	Faces_normals[i].normalize();

	}
	
	Faces_normals_computed=true;   
}


//*************************************************************************
// Calcular normales de vértices,
//
//*************************************************************************

void _triangles_object3D::compute_vertices_normals()
{
_vertex3f a,a2,a3,b,b2,b3,n1,n2,n3,c,c2,c3,abvector,acvector,dato;
int Vertex_1,Vertex_2,Vertex_3;




if(!Faces_normals_computed)
	compute_faces_normals();


/*
para cada vertice i ( 0... numvert-1)
	normal_vert[i] = (0,0,0)

para cada cara j  ( 0.. num.cara -1)
	i0,i1,i2 = indices vert cara j-esima
	ar1=vert i1-vert i0
	ar2= vert i2 - vert i0
	normalcara[j]= ar1*ar2/||ar1*ar2||
	normalvert[i0]=normalvert[i0]+normalcara[j]
      
	(idem vert i1 y i2)

pàra cada vert i ( i 00..numvert-1)
	normalizar normal vert i-esimo

-----------------------------------------------------



*/

Vertices_normals.resize(Vertices.size());

a.x=0;
a.y=0;
a.z=0;


for(int i=0; i < (int) Vertices.size(); i++){
	Vertices_normals[i]=a;
}


for ( int i= 0 ; i < (int) Faces_vertices.size() ; i++ ){
	
	Vertex_1 = Faces_vertices[i].x ;
	Vertex_2 = Faces_vertices[i].y ;
	Vertex_3 = Faces_vertices[i].z ;

	Vertices_normals[Vertex_1].x=Vertices_normals[Vertex_1].x+Faces_normals[i].x;
	Vertices_normals[Vertex_1].y=Vertices_normals[Vertex_1].y+Faces_normals[i].y;
	Vertices_normals[Vertex_1].z=Vertices_normals[Vertex_1].z+Faces_normals[i].z;
	
	Vertices_normals[Vertex_2].x=Vertices_normals[Vertex_2].x+Faces_normals[i].x;
	Vertices_normals[Vertex_2].y=Vertices_normals[Vertex_2].y+Faces_normals[i].y;
	Vertices_normals[Vertex_2].z=Vertices_normals[Vertex_2].z+Faces_normals[i].z;

	Vertices_normals[Vertex_3].x=Vertices_normals[Vertex_3].x+Faces_normals[i].x;
	Vertices_normals[Vertex_3].y=Vertices_normals[Vertex_3].y+Faces_normals[i].y;
	Vertices_normals[Vertex_3].z=Vertices_normals[Vertex_3].z+Faces_normals[i].z;

	


}




for(int i=0; i < (int) Vertices_normals.size(); i++){
	
	Vertices_normals[i].normalize();
	

}

Vertices_normals_computed=true;


}

//----------------------------------------------------------------------

int _triangles_object3D::create(vector<float> Vertices1,vector<int> Faces1)
{

_vertex3f Vertex;
_vertex3i vert;

	
for(int i=0; i< (int) Vertices1.size();i++){
	Vertex.x=Vertices1[i];
	i++;
	Vertex.y=Vertices1[i];
	i++;
	Vertex.z=Vertices1[i];
	
	Vertices.push_back(Vertex);
	
}

for(int k=0; k< (int) Faces1.size();k++){
	vert.x=Faces1[k];
	k++;
	vert.y=Faces1[k];
	k++;
	vert.z=Faces1[k];
	
	Faces_vertices.push_back(vert);
}

return 0;
}



//**********************************************************************
// clase _ply_triangles_object3D

_ply_triangles_object3D::_ply_triangles_object3D( const std::string & nombreArchivo ) 
{
const char * archivo = nombreArchivo.c_str();

_file_ply::read( archivo, vertices,faces );

create(vertices,faces);

Vertices_tex_coords.resize(Vertices.size());

}


