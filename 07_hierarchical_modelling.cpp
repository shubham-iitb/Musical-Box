#include <math.h>   

#include "07_hierarchical_modelling.hpp"

GLuint shaderProgram;

glm::mat4 rotation_matrix;
glm::mat4 projection_matrix;
glm::mat4 c_rotation_matrix;
glm::mat4 c_translation_matrix;
glm::mat4 lookat_matrix;

glm::mat4 model_matrix;
glm::mat4 view_matrix;


glm::mat4 modelview_matrix;

GLuint uModelViewMatrix;


//----------------------------declarations-------------------------

const int num_vertices = 36;
const int num_vertices_box = 84;
float length=24,width=24,height=6,thickness=2;
float roomlength = 50, roomheight = 50, roomdepth = 50;
float wallthickness = 5;
float doorlength = 10, doorheight = 20, doorthickness = 5;
float windowlength = 10, windowheight = 20, windowthickness = 5;
int tri_idx=0;
int room_idx=0;
float wsize = 50.0;
glm::vec4 v_positions_box[num_vertices_box];
glm::vec4 v_colors_box[num_vertices_box];
glm::vec4 roomcolor = glm::vec4(0.2, 0.4, 0.5, 1.0);
glm::vec4 roomcolorinner = glm::vec4(0.9, 0.4, 0.6, 1.0);
glm::vec4 doorcolor = glm::vec4(0.5, 0.2, 0.4, 1.0);
glm::vec4 windowcolor = glm::vec4(0.5, 0.3, 0.2, 1.0);

glm::vec4 hiplpos[390960];
glm::vec4 hiplcol[390960];

glm::vec4 hiprpos[390960];
glm::vec4 hiprcol[390960];

glm::vec4 headpos[388800];
glm::vec4 headcol[388800];

glm::vec4 neckpos[388800];
glm::vec4 neckcol[388800];

glm::vec4 torso1pos[390960];
glm::vec4 torso1col[390960];

glm::vec4 torso2pos[390960];
glm::vec4 torso2col[390960];

glm::vec4 torso3pos[390960];
glm::vec4 torso3col[390960];

glm::vec4 thighlpos[390960];
glm::vec4 thighlcol[390960];

glm::vec4 thighrpos[390960];
glm::vec4 thighrcol[390960];

glm::vec4 kneelpos[388800];
glm::vec4 kneelcol[388800];

glm::vec4 kneerpos[388800];
glm::vec4 kneercol[388800];

glm::vec4 leglpos[390960];
glm::vec4 leglcol[390960];

glm::vec4 legrpos[390960];
glm::vec4 legrcol[390960];

glm::vec4 footlpos[388800];
glm::vec4 footlcol[388800];

glm::vec4 footrpos[388800];
glm::vec4 footrcol[388800];

glm::vec4 shoulderlpos[388800];
glm::vec4 shoulderlcol[388800];

glm::vec4 shoulderrpos[388800];
glm::vec4 shoulderrcol[388800];

glm::vec4 uarmlpos[390960];
glm::vec4 uarmlcol[390960];

glm::vec4 uarmrpos[390960];
glm::vec4 uarmrcol[390960];

glm::vec4 elbowlpos[388800];
glm::vec4 elbowlcol[388800];

glm::vec4 elbowrpos[388800];
glm::vec4 elbowrcol[388800];

glm::vec4 larmlpos[390960];
glm::vec4 larmlcol[390960];

glm::vec4 larmrpos[390960];
glm::vec4 larmrcol[390960];

glm::vec4 handlpos[388800];
glm::vec4 handlcol[388800];

glm::vec4 handrpos[388800];
glm::vec4 handrcol[388800];

/// ------ props ------

glm::vec4 hatcol[390960];
glm::vec4 hatpos[390960];

glm::vec4 umbrellastickcol[390960];
glm::vec4 umbrellastickpos[390960];

glm::vec4 umbrellafoldedcol[390960];
glm::vec4 umbrellafoldedpos[390960];

glm::vec4 umbrellaopencol[388800];
glm::vec4 umbrellaopenpos[388800];

//-----------------dog delcarations----------

glm::vec4 dogtrunkpos[388800];  // ellipse
glm::vec4 dogtrunkcol[388800];

glm::vec4 dogheadpos[388800];   // ellipse
glm::vec4 dogheadcol[388800];

glm::vec4 dogneckpos[390960];   //  frustom
glm::vec4 dogneckcol[390960];

glm::vec4 dogtailpos[390960];   // frustom
glm::vec4 dogtailcol[390960];

glm::vec4 dogarm1pos[390960];   // frustom
glm::vec4 dogarm1col[390960];

glm::vec4 dogarm2pos[390960];   // frustom
glm::vec4 dogarm2col[390960];

glm::vec4 dogarm3pos[390960];   // frustom
glm::vec4 dogarm3col[390960];

glm::vec4 dogarm4pos[390960];   // frustom
glm::vec4 dogarm4col[390960];

glm::vec4 roompos[174];   // room
glm::vec4 roomcol[174];



//------------------------declarations end-----------------------


//---------------------------- functions to build shapes -------------------------------------

glm::vec4 positionsRoom[32] = {

  glm::vec4(0.0, 0.0,0.0, 1.0),
  glm::vec4(roomlength, 0.0,0.0, 1.0),
  glm::vec4(0.0, 0.0, roomdepth, 1.0),
  glm::vec4(roomlength, 0.0, roomdepth, 1.0),

  glm::vec4(0.0, roomheight,0.0, 1.0),
  glm::vec4(roomlength, roomheight,0.0, 1.0),
  glm::vec4(0.0, roomheight, roomdepth, 1.0),
  glm::vec4(roomlength, roomheight, roomdepth, 1.0),

  glm::vec4(0.0+wallthickness, 0.0,0.0+wallthickness, 1.0),
  glm::vec4(roomlength-wallthickness, 0.0,0.0+wallthickness, 1.0),
  glm::vec4(0.0+wallthickness, 0.0, roomdepth-wallthickness, 1.0),
  glm::vec4(roomlength-wallthickness, 0.0, roomdepth-wallthickness, 1.0),

  glm::vec4(0.0+wallthickness, roomheight-wallthickness,0.0+wallthickness, 1.0),
  glm::vec4(roomlength-wallthickness, roomheight-wallthickness,0.0+wallthickness, 1.0),
  glm::vec4(0.0+wallthickness, roomheight-wallthickness, roomdepth-wallthickness, 1.0),
  glm::vec4(roomlength-wallthickness, roomheight-wallthickness, roomdepth-wallthickness, 1.0),

  glm::vec4((roomlength-doorlength)/2.0, 0.0,0.0, 1.0),
  glm::vec4((roomlength+doorlength)/2.0, 0.0,0.0, 1.0),
  glm::vec4((roomlength-doorlength)/2.0, doorheight,0.0, 1.0),
  glm::vec4((roomlength+doorlength)/2.0, doorheight,0.0, 1.0),

  glm::vec4((roomlength-doorlength)/2.0, 0.0,doorthickness, 1.0),
  glm::vec4((roomlength+doorlength)/2.0, 0.0,doorthickness, 1.0),
  glm::vec4((roomlength-doorlength)/2.0, doorheight,doorthickness, 1.0),
  glm::vec4((roomlength+doorlength)/2.0, doorheight,doorthickness, 1.0),

  glm::vec4(roomlength, (roomheight-windowheight)/2.0, (roomdepth-windowlength)/2.0, 1.0),
  glm::vec4(roomlength, (roomheight-windowheight)/2.0, (roomdepth+windowlength)/2.0, 1.0),
  glm::vec4(roomlength, (roomheight+windowheight)/2.0, (roomdepth-windowlength)/2.0, 1.0),
  glm::vec4(roomlength, (roomheight+windowheight)/2.0, (roomdepth+windowlength)/2.0, 1.0),

  glm::vec4(roomlength-windowthickness, (roomheight-windowheight)/2.0, (roomdepth-windowlength)/2.0, 1.0),
  glm::vec4(roomlength-windowthickness, (roomheight-windowheight)/2.0, (roomdepth+windowlength)/2.0, 1.0),
  glm::vec4(roomlength-windowthickness, (roomheight+windowheight)/2.0, (roomdepth-windowlength)/2.0, 1.0),
  glm::vec4(roomlength-windowthickness, (roomheight+windowheight)/2.0, (roomdepth+windowlength)/2.0, 1.0),

};

glm::vec4 colorsRoom[32] = {

  roomcolor,
  roomcolor,
  roomcolor,
  roomcolor,

  roomcolor,
  roomcolor,
  roomcolor,
  roomcolor,

  roomcolorinner,
  roomcolorinner,
  roomcolorinner,
  roomcolorinner,


  roomcolorinner,
  roomcolorinner,
  roomcolorinner,
  roomcolorinner,

  doorcolor,
  doorcolor,
  doorcolor,
  doorcolor,

  doorcolor,
  doorcolor,
  doorcolor,
  doorcolor,

  windowcolor,
  windowcolor,
  windowcolor,
  windowcolor,

  windowcolor,
  windowcolor,
  windowcolor,
  windowcolor,

};




glm::vec4 positionsBox[16] = {

  glm::vec4(0.0, 0.0,0.0-height, 1.0),
  glm::vec4(length, 0.0,0.0-height, 1.0),
  glm::vec4(length, width,0.0-height, 1.0),
  glm::vec4(0.0, width,0.0-height, 1.0),

  glm::vec4(0.0, 0.0,0.0, 1.0),
  glm::vec4(length, 0.0,0.0, 1.0),
  glm::vec4(length, width,0.0, 1.0),
  glm::vec4(0.0, width,0.0, 1.0),

  glm::vec4(0.0+thickness, 0.0+thickness,0.0+thickness-height, 1.0),
  glm::vec4(length-thickness, 0.0+thickness,0.0+thickness-height, 1.0),
  glm::vec4(length-thickness, width-thickness,0.0+thickness-height, 1.0),
  glm::vec4(0.0+thickness, width-thickness,0.0+thickness-height, 1.0),

  glm::vec4(0.0+thickness, 0.0+thickness,0.0, 1.0),
  glm::vec4(length-thickness, 0.0+thickness,0.0, 1.0),
  glm::vec4(length-thickness, width-thickness,0.0, 1.0),
  glm::vec4(0.0+thickness, width-thickness,0.0, 1.0),
};


glm::vec4 colorsBox[16] = {
  glm::vec4(0.5, 0.2, 0.0, 1.0),
  glm::vec4(0.5, 0.2, 0.0, 1.0),
  glm::vec4(0.5, 0.2, 0.0, 1.0),
  glm::vec4(0.5, 0.2, 0.0, 1.0),
  glm::vec4(0.8, 0.3, 0.0, 1.0),
  glm::vec4(0.8, 0.3, 0.0, 1.0),
  glm::vec4(0.8, 0.3, 0.0, 1.0),
  glm::vec4(0.8, 0.3, 0.0, 1.0),
  glm::vec4(0.7, 0.0, 0.8, 1.0),
  glm::vec4(0.7, 0.0, 0.8, 1.0),
  glm::vec4(0.7, 0.0, 0.8, 1.0),
  glm::vec4(0.7, 0.0, 0.8, 1.0),
  glm::vec4(0.5, 0.0, 0.5, 1.0),
  glm::vec4(0.5, 0.0, 0.5, 1.0),
  glm::vec4(0.5, 0.0, 0.5, 1.0),
  glm::vec4(0.5, 0.0, 0.5, 1.0),
 
};


void quad_box(int a, int b, int c, int d)
{
  v_colors_box[tri_idx] = colorsBox[a]; v_positions_box[tri_idx] = positionsBox[a]; tri_idx++;
  v_colors_box[tri_idx] = colorsBox[b]; v_positions_box[tri_idx] = positionsBox[b]; tri_idx++;
  v_colors_box[tri_idx] = colorsBox[c]; v_positions_box[tri_idx] = positionsBox[c]; tri_idx++;
  v_colors_box[tri_idx] = colorsBox[a]; v_positions_box[tri_idx] = positionsBox[a]; tri_idx++;
  v_colors_box[tri_idx] = colorsBox[c]; v_positions_box[tri_idx] = positionsBox[c]; tri_idx++;
  v_colors_box[tri_idx] = colorsBox[d]; v_positions_box[tri_idx] = positionsBox[d]; tri_idx++;
 }


void colorbox(void)
{
    quad_box( 1, 0, 3, 2 );
    quad_box( 2, 3, 7, 6 );
    quad_box( 3, 0, 4, 7 );
    quad_box( 6, 5, 1, 2 );
    // quad_box( 4, 5, 6, 7 );
    quad_box( 5, 4, 0, 1 );
    quad_box( 9, 8, 11, 10 );
    quad_box( 10, 11, 15, 14 );
    quad_box( 11, 8, 12, 15 );
    quad_box( 14, 13, 9, 10 );
    // quad_box( 12, 13, 14, 15 );
    quad_box( 13, 12, 8, 9 );
    quad_box( 4, 12, 13, 5 );
    quad_box( 5, 13, 14, 6 );
    quad_box( 6, 14, 15, 7 );
    quad_box( 7, 15, 12, 4 );
}

void room_quad_box(int a, int b, int c, int d)
{
  roomcol[room_idx] = colorsRoom[a]; roompos[room_idx] = positionsRoom[a]; room_idx++;
  roomcol[room_idx] = colorsRoom[b]; roompos[room_idx] = positionsRoom[b]; room_idx++;
  roomcol[room_idx] = colorsRoom[c]; roompos[room_idx] = positionsRoom[c]; room_idx++;
  roomcol[room_idx] = colorsRoom[b]; roompos[room_idx] = positionsRoom[b]; room_idx++;
  roomcol[room_idx] = colorsRoom[c]; roompos[room_idx] = positionsRoom[c]; room_idx++;
  roomcol[room_idx] = colorsRoom[d]; roompos[room_idx] = positionsRoom[d]; room_idx++;
 }

void room(void)
{
  room_quad_box(0,1,2,3);  
  room_quad_box(4,5,6,7);  
  room_quad_box(12,13,14,15);  
  room_quad_box(2,3,6,7);  
  room_quad_box(10,11,14,15);  
  room_quad_box(0,2,4,6);
  room_quad_box(8,10,12,14);

  room_quad_box(0,16,4,18);
  room_quad_box(4,18,19,5);
  room_quad_box(19,5,17,1);

  room_quad_box(8,20,12,22);  
  room_quad_box(12,22,23,13);
  room_quad_box(23,13,21,9);

  room_quad_box(16,20,18,22);
  room_quad_box(18,22,19,23);
  room_quad_box(19,23,17,21);

  room_quad_box(1,24,5,26);
  room_quad_box(5,26,7,27);
  room_quad_box(7,27,3,25);
  room_quad_box(3,25,1,24);

  room_quad_box(9,13,30,28);
  room_quad_box(30,31,13,15);
  room_quad_box(15,31,29,11);
  room_quad_box(11,29,9,28);  

  room_quad_box(24,28,26,30);
  room_quad_box(26,30,27,31);
  room_quad_box(27,31,25,29);
  room_quad_box(25,29,24,28);  

}
int get_cylinder_size(float height,float radius){
  int lats = 180;
  int longts = 360;
  return 2*longts*3+lats*longts*6;
}

void cylinder(float height,float radius,glm::vec4 vpos[]){
  float lats = 180;
  float sc = height/lats;
  int longts = 360;

  int ind = 0;

  for(int i=0;i<longts;i++){
    vpos[ind] = glm::vec4(radius*cos(i*M_PI/180),radius*sin(i*M_PI/180),0.0,1.0);
    ind++;
    vpos[ind] = glm::vec4(0.0,0.0,0.0,1.0);
    ind++;
    vpos[ind] = glm::vec4(radius*cos((i+1)*M_PI/180),radius*sin((i+1)*M_PI/180),0.0,1.0);
    ind++;
  }

  for(int j=0;j<lats;j++){
    for(int i=0;i<longts;i++){
    vpos[ind] = glm::vec4(radius*cos(i*M_PI/180),radius*sin(i*M_PI/180),j*sc,1.0);
    ind++;
    vpos[ind] = glm::vec4(radius*cos(i*M_PI/180),radius*sin(i*M_PI/180),(j+1)*sc,1.0);
    ind++;
    vpos[ind] = glm::vec4(radius*cos((i+1)*M_PI/180),radius*sin((i+1)*M_PI/180),j*sc,1.0);
    ind++;

    vpos[ind] = glm::vec4(radius*cos(i*M_PI/180),radius*sin(i*M_PI/180),(j+1)*sc,1.0);
    ind++;
    vpos[ind] = glm::vec4(radius*cos((i+1)*M_PI/180),radius*sin((i+1)*M_PI/180),j*sc,1.0);
    ind++;
    vpos[ind] = glm::vec4(radius*cos((i+1)*M_PI/180),radius*sin((i+1)*M_PI/180),(j+1)*sc,1.0);
    ind++;

    }
  }

  for(int i=0;i<longts;i++){
    vpos[ind] = glm::vec4(radius*cos(i*M_PI/180),radius*sin(i*M_PI/180),height,1.0);
    ind++;
    vpos[ind] = glm::vec4(0.0,0.0,height,1.0);
    ind++;
    vpos[ind] = glm::vec4(radius*cos((i+1)*M_PI/180),radius*sin((i+1)*M_PI/180),height,1.0);
    ind++;
  } 

}


int get_frustom_size(float height,float r1, float r2){
  int lats = 180;
  int longts = 360;
  return 2*longts*3+lats*longts*6;
}




void frustom(float height,float r1,float r2,glm::vec4 vpos[]){
  float lats = 180;
  float sc = height/lats;
  int longts = 360;

  int ind = 0;

  for(int i=0;i<longts;i++){
    vpos[ind] = glm::vec4(r1*cos(i*M_PI/180),r1*sin(i*M_PI/180),0.0,1.0);
    ind++;
    vpos[ind] = glm::vec4(0.0,0.0,0.0,1.0);
    ind++;
    vpos[ind] = glm::vec4(r1*cos((i+1)*M_PI/180),r1*sin((i+1)*M_PI/180),0.0,1.0);
    ind++;
  }

  for(int j=0;j<lats;j++){
    for(int i=0;i<longts;i++){
      float rr1 = r1 - j*((r1-r2)*1.0)/lats;
      float rr2 = r1 - (j+1)*((r1-r2)*1.0)/lats;
    vpos[ind] = glm::vec4(rr1*cos(i*M_PI/180),rr1*sin(i*M_PI/180),j*sc,1.0);
    ind++;
    vpos[ind] = glm::vec4(rr2*cos(i*M_PI/180),rr2*sin(i*M_PI/180),(j+1)*sc,1.0);
    ind++;
    vpos[ind] = glm::vec4(rr1*cos((i+1)*M_PI/180),rr1*sin((i+1)*M_PI/180),j*sc,1.0);
    ind++;

    vpos[ind] = glm::vec4(rr2*cos(i*M_PI/180),rr2*sin(i*M_PI/180),(j+1)*sc,1.0);
    ind++;
    vpos[ind] = glm::vec4(rr1*cos((i+1)*M_PI/180),rr1*sin((i+1)*M_PI/180),j*sc,1.0);
    ind++;
    vpos[ind] = glm::vec4(rr2*cos((i+1)*M_PI/180),rr2*sin((i+1)*M_PI/180),(j+1)*sc,1.0);
    ind++;

    }
  }

  for(int i=0;i<longts;i++){
    vpos[ind] = glm::vec4(r2*cos(i*M_PI/180),r2*sin(i*M_PI/180),height,1.0);
    ind++;
    vpos[ind] = glm::vec4(0.0,0.0,height,1.0);
    ind++;
    vpos[ind] = glm::vec4(r2*cos((i+1)*M_PI/180),r2*sin((i+1)*M_PI/180),height,1.0);
    ind++;
  }

}



int get_ellipse_size(float a1,float a2, float a3){
  float lats = 180;
  int longts = 360;
  return lats*longts*6;
}

void ellipse(double a1,double a3,double a2,glm::vec4 vpos[]){
  double lats = 180;
  double sc = a1/lats;
  int longts = 360;
  int n = lats*longts*6;

  int ind = 0;

  for(double i=0;i<lats;i++){

    for(double j=0;j<longts;j++){

      vpos[ind] = glm::vec4(a3*sin(i*M_PI/180)*cos(j*M_PI/180)/2,a2*sin(i*M_PI/180)*sin(j*M_PI/180)/2,a1/2+a1*cos(i*M_PI/180)/2,1.0);
      ind++;      
      vpos[ind] = glm::vec4(a3*sin(i*M_PI/180)*cos((j+1)*M_PI/180)/2,a2*sin(i*M_PI/180)*sin((j+1)*M_PI/180)/2,a1/2+a1*cos(i*M_PI/180)/2,1.0);
      ind++;      
      vpos[ind] = glm::vec4(a3*sin((i+1)*M_PI/180)*cos(j*M_PI/180)/2,a2*sin((i+1)*M_PI/180)*sin(j*M_PI/180)/2,a1/2+a1*cos((i+1)*M_PI/180)/2,1.0);
      ind++;      
      vpos[ind] = glm::vec4(a3*sin(i*M_PI/180)*cos((j+1)*M_PI/180)/2,a2*sin(i*M_PI/180)*sin((j+1)*M_PI/180)/2,a1/2+a1*cos(i*M_PI/180)/2,1.0);
      ind++;      
      vpos[ind] = glm::vec4(a3*sin((i+1)*M_PI/180)*cos(j*M_PI/180)/2,a2*sin((i+1)*M_PI/180)*sin(j*M_PI/180)/2,a1/2+a1*cos((i+1)*M_PI/180)/2,1.0);
      ind++;      
      vpos[ind] = glm::vec4(a3*sin((i+1)*M_PI/180)*cos((j+1)*M_PI/180)/2,a2*sin((i+1)*M_PI/180)*sin((j+1)*M_PI/180)/2,a1/2+a1*cos((i+1)*M_PI/180)/2,1.0);
      ind++;      

    }
  } 

}



int get_elliptical_frustom_size(float height,float r1a,float r1b,float r2a,float r2b){
  float lats = 180;
  int longts = 360;
  return longts*12;
}

void elliptical_frustom(float height,float r1a,float r1b,float r2a,float r2b,glm::vec4 vpos[]){
  float lats = 180;

  int longts = 360;

  int ind = 0;

  for(int i=0;i<longts;i++){
    vpos[ind] = glm::vec4(r1a/2*cos(i*M_PI/180),r1b/2*sin(i*M_PI/180),0.0,1.0);
    ind++;
    vpos[ind] = glm::vec4(0.0,0.0,0.0,1.0);
    ind++;
    vpos[ind] = glm::vec4(r1a/2*cos((i+1)*M_PI/180),r1b/2*sin((i+1)*M_PI/180),0.0,1.0);
    ind++;

    vpos[ind] = glm::vec4(r2a/2*cos(i*M_PI/180),r2b/2*sin(i*M_PI/180),height,1.0);
    ind++;
    vpos[ind] = glm::vec4(0.0,0.0,height,1.0);
    ind++;
    vpos[ind] = glm::vec4(r2a/2*cos((i+1)*M_PI/180),r2b/2*sin((i+1)*M_PI/180),height,1.0);
    ind++;


    vpos[ind] = glm::vec4(r1a/2*cos(i*M_PI/180),r1b/2*sin(i*M_PI/180),0.0,1.0);
    ind++;
    vpos[ind] = glm::vec4(r1a/2*cos((i+1)*M_PI/180),r1b/2*sin((i+1)*M_PI/180),0.0,1.0);
    ind++;
    vpos[ind] = glm::vec4(r2a/2*cos(i*M_PI/180),r2b/2*sin(i*M_PI/180),height,1.0);
    ind++;

    vpos[ind] = glm::vec4(r1a/2*cos((i+1)*M_PI/180),r1b/2*sin((i+1)*M_PI/180),0.0,1.0);
    ind++;
    vpos[ind] = glm::vec4(r2a/2*cos(i*M_PI/180),r2b/2*sin(i*M_PI/180),height,1.0);
    ind++;
    vpos[ind] = glm::vec4(r2a/2*cos((i+1)*M_PI/180),r2b/2*sin((i+1)*M_PI/180),height,1.0);
    ind++;   
  }

}


int get_cone_size(float height,float r1){
  int lats = 180;
  int longts = 360;
  return lats*longts*6;
}




void cone(float height,float r1,glm::vec4 vpos[]){
  float lats = 180;
  float sc = height/lats;
  int longts = 360;

  int ind = 0;


  for(int j=0;j<lats;j++){
    for(int i=0;i<longts;i++){
      float rr1 = r1 - j*(r1*1.0)/lats;
      float rr2 = r1 - (j+1)*(r1*1.0)/lats;
    vpos[ind] = glm::vec4(rr1*cos(i*M_PI/180),rr1*sin(i*M_PI/180),j*sc,1.0);
    ind++;
    vpos[ind] = glm::vec4(rr2*cos(i*M_PI/180),rr2*sin(i*M_PI/180),(j+1)*sc,1.0);
    ind++;
    vpos[ind] = glm::vec4(rr1*cos((i+1)*M_PI/180),rr1*sin((i+1)*M_PI/180),j*sc,1.0);
    ind++;

    vpos[ind] = glm::vec4(rr2*cos(i*M_PI/180),rr2*sin(i*M_PI/180),(j+1)*sc,1.0);
    ind++;
    vpos[ind] = glm::vec4(rr1*cos((i+1)*M_PI/180),rr1*sin((i+1)*M_PI/180),j*sc,1.0);
    ind++;
    vpos[ind] = glm::vec4(rr2*cos((i+1)*M_PI/180),rr2*sin((i+1)*M_PI/180),(j+1)*sc,1.0);
    ind++;

    }
  }


}

void same_colors(float a,float b, float c,int n,glm::vec4 vcol[]){
  for(int i=0;i<n;i++){
    vcol[i]=  glm::vec4(a,b,c,1.0);
  }
}
//-----------------------------------------------------------------------------------

void initBuffersGL(void)
{

  // Load shaders and use the resulting shader program
  std::string vertex_shader_file("07_vshader.glsl");
  std::string fragment_shader_file("07_fshader.glsl");

  std::vector<GLuint> shaderList;
  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgram = csX75::CreateProgramGL(shaderList);
  glUseProgram( shaderProgram );

  // getting the attributes from the shader program
  vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
  vColor = glGetAttribLocation( shaderProgram, "vColor" ); 
  uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");

  // Creating the hierarchy:
  colorbox();
  room();

  roombox = new csX75::HNode(NULL,174,roompos,roomcol,sizeof(roompos),sizeof(roomcol));


  lowerbox = new csX75::HNode(NULL,num_vertices_box,v_positions_box,v_colors_box,sizeof(v_positions_box),sizeof(v_colors_box));
  lowerbox->change_parameters(-length/2,0.0,0.0,75.0,180.0,0.0);
  upperbox = new csX75::HNode(lowerbox,num_vertices_box,v_positions_box,v_colors_box,sizeof(v_positions_box),sizeof(v_colors_box));
  upperbox->change_parameters(0.0,length,0.0,120.0,0.0,0.0);




  //------------------------------------------------- Humanoid---------------------------------------------------------


  int torso3size = get_elliptical_frustom_size(5,6,3,7,3);
  elliptical_frustom(5,6,3,7,3,torso3pos);
  same_colors(1.0, 0.0, 0.0,torso3size,torso3col);
  torso3 = new csX75::HNode(NULL,torso3size,torso3pos,torso3col,sizeof(torso3pos),sizeof(torso3col));
  torso3->change_parameters(0,14,0,90.0,0.0,0.0);

  int torso2size = get_ellipse_size(3,6,3);
  ellipse(3,6,3,torso2pos);
  same_colors(0.7, 0.0, 0.0,torso2size,torso2col);
  torso2 = new csX75::HNode(torso3,torso2size,torso2pos,torso2col,sizeof(torso2pos),sizeof(torso2col));
  torso2->change_parameters(0.0,0.0,0.5,180.0,0.0,0.0);

  int torso1size = get_elliptical_frustom_size(7,6,3,9,4);
  elliptical_frustom(7,6,3,9,4,torso1pos);
  same_colors(0.9, 0.0, 0.0,torso1size,torso1col);
  torso1 = new csX75::HNode(torso2,torso1size,torso1pos,torso1col,sizeof(torso1pos),sizeof(torso1col));
  torso1->change_parameters(0.0,0.0,2.5,0.0,0.0,0.0);

  int shoulderlsize = get_ellipse_size(2,2,2);
  ellipse(2,2,2,shoulderlpos);
  same_colors(0.0,0.0,0.8,shoulderlsize,shoulderlcol);
  shoulderl = new csX75::HNode(torso1,shoulderlsize,shoulderlpos,shoulderlcol,sizeof(shoulderlpos),sizeof(shoulderlcol));
  shoulderl->change_parameters(5.5,0.0,5.5,0.0,0.0,0.0);

  int shoulderrsize = get_ellipse_size(2,2,2);
  ellipse(2,2,2,shoulderrpos);
  same_colors(0.0,0.0,0.8,shoulderrsize,shoulderrcol);
  shoulderr = new csX75::HNode(torso1,shoulderrsize,shoulderrpos,shoulderrcol,sizeof(shoulderrpos),sizeof(shoulderrcol));
  shoulderr->change_parameters(-5.5,0.0,5.5,0.0,0.0,0.0);

  int uarmlsize = get_frustom_size(7,1.2,0.8);
  frustom(7,1.2,0.8,uarmlpos);
  same_colors(0.8,0.0,0.0,uarmlsize,uarmlcol);
  uarml = new csX75::HNode(shoulderl,uarmlsize,uarmlpos,uarmlcol,sizeof(uarmlpos),sizeof(uarmlcol));
  uarml->change_parameters(0.0,0.0,0.0,180.0,0.0,0.0);

  int uarmrsize = get_frustom_size(7,1.2,0.8);
  frustom(7,1.2,0.8,uarmrpos);
  same_colors(0.8,0.0,0.0,uarmrsize,uarmrcol);
  uarmr = new csX75::HNode(shoulderr,uarmrsize,uarmrpos,uarmrcol,sizeof(uarmrpos),sizeof(uarmrcol));
  uarmr->change_parameters(0.0,0.0,0.0,180.0,0.0,0.0);

  int elbowlsize = get_ellipse_size(1.0,1.5,1.5);
  ellipse(1.0,1.5,1.5,elbowlpos);
  same_colors(0.0,0.0,0.8,elbowlsize,elbowlcol);
  elbowl = new csX75::HNode(uarml,elbowlsize,elbowlpos,elbowlcol,sizeof(elbowlpos),sizeof(elbowlcol));
  elbowl->change_parameters(0.0,0.0,6.5,0.0,0.0,0.0);

  int elbowrsize = get_ellipse_size(1.0,1.5,1.5);
  ellipse(1.0,1.5,1.5,elbowrpos);
  same_colors(0.0,0.0,0.8,elbowrsize,elbowrcol);
  elbowr = new csX75::HNode(uarmr,elbowrsize,elbowrpos,elbowrcol,sizeof(elbowrpos),sizeof(elbowrcol));
  elbowr->change_parameters(0.0,0.0,6.5,0.0,0.0,0.0);

  int larmlsize = get_frustom_size(6,0.8,0.5);
  frustom(6,0.8,0.5,larmlpos);
  same_colors(1.0,1.0,0.0,larmlsize,larmlcol);
  larml = new csX75::HNode(elbowl,larmlsize,larmlpos,larmlcol,sizeof(larmlpos),sizeof(larmlcol));
  larml->change_parameters(0.0,0.0,1.0,0.0,0.0,0.0);

  int larmrsize = get_frustom_size(6,0.8,0.5);
  frustom(6,0.8,0.5,larmrpos);
  same_colors(1.0,1.0,0.0,larmrsize,larmrcol);
  larmr = new csX75::HNode(elbowr,larmrsize,larmrpos,larmrcol,sizeof(larmrpos),sizeof(larmrcol));
  larmr->change_parameters(0.0,0.0,1.0,0.0,0.0,0.0);

  int handlsize = get_ellipse_size(4,2,1.5);
  ellipse(4,2,1.5,handlpos);
  same_colors(1.0,0.8,0.6,handlsize,handlcol);
  handl = new csX75::HNode(larml,handlsize,handlpos,handlcol,sizeof(handlpos),sizeof(handlcol));
  handl->change_parameters(0.0,0.0,5.0,0.0,0.0,0.0);

  int handrsize = get_ellipse_size(4,2,1.5);
  ellipse(4,2,1.5,handrpos);
  same_colors(1.0,0.8,0.6,handrsize,handrcol);
  handr = new csX75::HNode(larmr,handrsize,handrpos,handrcol,sizeof(handrpos),sizeof(handrcol));
  handr->change_parameters(0.0,0.0,5.0,0.0,0.0,0.0);


  int necksize = get_ellipse_size(1.5,3.5,3.5);
  ellipse(1.5,3.5,3.5,neckpos);
  same_colors(0.9,0.7,0.5,necksize,neckcol);
  neck = new csX75::HNode(torso1,necksize,neckpos,neckcol,sizeof(neckpos),sizeof(neckcol));
  neck->change_parameters(0.0,0.0,6.5,0.0,0.0,0.0);

  int headsize = get_ellipse_size(7,4,4);
  ellipse(7,4,4,headpos);
  same_colors(1.0,0.8,0.6,headsize,headcol);
  head = new csX75::HNode(neck,headsize,headpos,headcol,sizeof(headpos),sizeof(headcol));
  head->change_parameters(0.0,0.0,1.5,0.0,0.0,0.0);

  int hiplsize = get_ellipse_size(1.5,3.5,3.5);
  ellipse(1.5,3.5,3.5,hiplpos);
  same_colors(0.0, 0.0, 0.8,hiplsize,hiplcol);
  hipl = new csX75::HNode(torso3,hiplsize,hiplpos,hiplcol,sizeof(hiplpos),sizeof(hiplcol));
  hipl->change_parameters(2.0,0.0,5.0,0.0,0.0,0.0);

  int hiprsize = get_ellipse_size(1.5,3.5,3.5);
  ellipse(1.5,3.5,3.5,hiprpos);
  same_colors(0.0, 0.0, 0.8,hiprsize,hiprcol);
  hipr = new csX75::HNode(torso3,hiprsize,hiprpos,hiprcol,sizeof(hiprpos),sizeof(hiprcol));
  hipr->change_parameters(-2.0,0.0,5.0,0.0,0.0,0.0);

  int thighlsize = get_frustom_size(7,1.5,1.0);
  frustom(7,1.5,1.0,thighlpos);
  same_colors(0.0, 0.0, 0.8,thighlsize,thighlcol);
  thighl = new csX75::HNode(hipl,thighlsize,thighlpos,thighlcol,sizeof(thighlpos),sizeof(thighlcol));
  thighl->change_parameters(0.0,0.0,1.5,0.0,0.0,0.0);

  int thighrsize = get_frustom_size(7,1.5,1.0);
  frustom(7,1.5,1.0,thighrpos);
  same_colors(0.0, 0.0, 0.8,thighrsize,thighrcol);
  thighr = new csX75::HNode(hipr,thighrsize,thighrpos,thighrcol,sizeof(thighrpos),sizeof(thighrcol));
  thighr->change_parameters(0.0,0.0,1.5,0.0,0.0,0.0);

  int kneelsize = get_ellipse_size(1.5,2.5,2.5);
  ellipse(1.5,2.5,2.5,kneelpos);
  same_colors(0.0, 0.0, 0.6,kneelsize,kneelcol);
  kneel = new csX75::HNode(thighl,kneelsize,kneelpos,kneelcol,sizeof(kneelpos),sizeof(kneelcol));
  kneel->change_parameters(0.0,0.0,6.5,0.0,0.0,0.0);

  int kneersize = get_ellipse_size(1.5,2.5,2.5);
  ellipse(1.5,2.5,2.5,kneerpos);
  same_colors(0.0, 0.0, 0.6,kneersize,kneercol);
  kneer = new csX75::HNode(thighr,kneersize,kneerpos,kneercol,sizeof(kneerpos),sizeof(kneercol));
  kneer->change_parameters(0.0,0.0,6.5,0.0,0.0,0.0);

  int leglsize = get_frustom_size(7,1.2,0.8);
  frustom(7,1.2,0.8,leglpos);
  same_colors(0.0, 0.0, 0.6,leglsize,leglcol);
  legl = new csX75::HNode(kneel,leglsize,leglpos,leglcol,sizeof(leglpos),sizeof(leglcol));
  legl->change_parameters(0.0,0.0,1.25,0.0,0.0,0.0);

  int legrsize = get_frustom_size(7,1.2,0.8);
  frustom(7,1.2,0.8,legrpos);
  same_colors(0.0, 0.0, 0.6,legrsize,legrcol);
  legr = new csX75::HNode(kneer,legrsize,legrpos,legrcol,sizeof(legrpos),sizeof(legrcol));
  legr->change_parameters(0.0,0.0,1.25,0.0,0.0,0.0);


  int footlsize = get_ellipse_size(1.5,3,6);
  ellipse(1.50,3,6.0,footlpos);
  same_colors(0.2,0.2,0.2,footlsize,footlcol);
  footl = new csX75::HNode(legl,footlsize,footlpos,footlcol,sizeof(footlpos),sizeof(footlcol));
  footl->change_parameters(0.0,1.0,7.0,0.0,0.0,0.0);

  int footrsize = get_ellipse_size(1.5,3,6);
  ellipse(1.5,3,6,footrpos);
  same_colors(0.2,0.2,0.2,footrsize,footrcol);
  footr = new csX75::HNode(legr,footrsize,footrpos,footrcol,sizeof(footrpos),sizeof(footrcol));
  footr->change_parameters(0.0,1.0,7.0,0.0,0.0,0.0);



  // --------------------------------------------- props ------------------------------------------------------------


  int hatsize = get_frustom_size(2,1.5,4);
  frustom(2,1.5,4,hatpos);
  same_colors(0.5, 0.5, 1.0,hatsize,hatcol);
  hat = new csX75::HNode(head,hatsize,hatpos,hatcol,sizeof(hatpos),sizeof(hatcol));
  hat->change_parameters(0.0,0.0,6.0,0.0,0.0,0.0);


  int umbrellasticksize = get_frustom_size(15,0.3,0.3);
  frustom(15,0.3,0.3,umbrellastickpos);
  same_colors(0.5, 0.5, 1.0,umbrellasticksize,umbrellastickcol);
  umbrellastick = new csX75::HNode(handr,umbrellasticksize,umbrellastickpos,umbrellastickcol,sizeof(umbrellastickpos),sizeof(umbrellastickcol));
  umbrellastick->change_parameters(0.0,0.0,4.0,0.0,0.0,0.0);

  int umbrellafoldedsize = get_frustom_size(12,0.9,0.4);
  frustom(12,0.9,0.4,umbrellafoldedpos);
  same_colors(1.0, 0.0, 0.0,umbrellafoldedsize,umbrellafoldedcol);
  umbrellafolded = new csX75::HNode(umbrellastick,umbrellafoldedsize,umbrellafoldedpos,umbrellafoldedcol,sizeof(umbrellafoldedpos),sizeof(umbrellafoldedcol));
  umbrellafolded->change_parameters(0.0,0.0,3.0,0.0,0.0,0.0);


  int umbrellaopensize = get_cone_size(5,9);
  cone(5,9,umbrellaopenpos);
  same_colors(1.0, 0.0, 0.0,umbrellaopensize,umbrellaopencol);
  umbrellaopen = new csX75::HNode(umbrellastick,umbrellaopensize,umbrellaopenpos,umbrellaopencol,sizeof(umbrellaopenpos),sizeof(umbrellaopencol));
  umbrellaopen->change_parameters(1000.0,0.0,10.0,0.0,0.0,0.0);

  

//---------------------------------------------------- dog  -----------------------------------------------------------

  int dogtrunksize = get_ellipse_size(15,8,6);
  ellipse(15,8,6,dogtrunkpos);
  same_colors(0.7,0.7,0.5,dogtrunksize,dogtrunkcol);
  dogtrunk = new csX75::HNode(NULL,dogtrunksize,dogtrunkpos,dogtrunkcol,sizeof(dogtrunkpos),sizeof(dogtrunkcol));
  dogtrunk->change_parameters(1.5*length,0.0,0.0,0.0,-90.0,0.0);

  int dognecksize = get_frustom_size(4,1.6,0.8);
  frustom(4,1.6,0.8,dogneckpos);
  same_colors(0.7,0.7,0.7,dognecksize,dogneckcol);
  dogneck = new csX75::HNode(dogtrunk,dognecksize,dogneckpos,dogneckcol,sizeof(dogneckpos),sizeof(dogneckcol));
  dogneck->change_parameters(0.0,1.6,1.6,42.0,180.0,0.0);

  int dogheadsize = get_ellipse_size(5,3,2);
  ellipse(5,3,2,dogheadpos);
  same_colors(0.5,0.5,0.5,dogheadsize,dogheadcol);
  doghead = new csX75::HNode(dogneck,dogheadsize,dogheadpos,dogheadcol,sizeof(dogheadpos),sizeof(dogheadcol));
  doghead->change_parameters(0,-4,4,-90,0,0);

  int dogarm1size = get_frustom_size(6,1,0.5);
  frustom(6,1,0.5,dogarm1pos);
  same_colors(0.3,0.3,0.5,dogarm1size,dogarm1col);
  dogarm1 = new csX75::HNode(dogtrunk,dogarm1size,dogarm1pos,dogarm1col,sizeof(dogarm1pos),sizeof(dogarm1col));
  dogarm1->change_parameters(-2,-2.5,4,90,0,0);

  int dogarm2size = get_frustom_size(6,1,0.5);
  frustom(6,1,0.5,dogarm2pos);
  same_colors(0.3,0.3,0.5,dogarm2size,dogarm2col);
  dogarm2 = new csX75::HNode(dogtrunk,dogarm2size,dogarm2pos,dogarm2col,sizeof(dogarm2pos),sizeof(dogarm2col));
  dogarm2->change_parameters(2,-2.5,4,90,0,0);

  int dogarm3size = get_frustom_size(6,1,0.5);
  frustom(6,1,0.5,dogarm3pos);
  same_colors(0.3,0.3,0.5,dogarm3size,dogarm3col);
  dogarm3 = new csX75::HNode(dogtrunk,dogarm3size,dogarm3pos,dogarm3col,sizeof(dogarm3pos),sizeof(dogarm3col));
  dogarm3->change_parameters(-2,-2.5,11,90,0,0);

  int dogarm4size = get_frustom_size(6,1,0.5);
  frustom(6,1,0.5,dogarm4pos);
  same_colors(0.3,0.3,0.5,dogarm4size,dogarm4col);
  dogarm4 = new csX75::HNode(dogtrunk,dogarm4size,dogarm4pos,dogarm4col,sizeof(dogarm4pos),sizeof(dogarm4col));
  dogarm4->change_parameters(2,-2.5,11,90,0,0);

  int dogtailsize = get_frustom_size(10,0.5,0.1);
  frustom(10,0.5,0.1,dogtailpos);
  same_colors(0.3,0.3,0.3,dogtailsize,dogtailcol);
  dogtail = new csX75::HNode(dogtrunk,dogtailsize,dogtailpos,dogtailcol,sizeof(dogtailpos),sizeof(dogtailcol));
  dogtail->change_parameters(0,1.5,13.5,-40,0,0);

  //-----------------------------------------------------------------------------------------------------------
  root_node = curr_node = roombox;

}

void renderGL(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  matrixStack.clear();

  //Creating the lookat and the up vectors for the camera
  c_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(c_xrot), glm::vec3(1.0f,0.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_yrot), glm::vec3(0.0f,1.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_zrot), glm::vec3(0.0f,0.0f,1.0f));

  glm::vec4 c_pos = glm::vec4(c_xpos,c_ypos,c_zpos, 1.0)*c_rotation_matrix;
  glm::vec4 c_up = glm::vec4(c_up_x,c_up_y,c_up_z, 1.0)*c_rotation_matrix;
  //Creating the lookat matrix
  lookat_matrix = glm::lookAt(glm::vec3(c_pos),glm::vec3(roomlength/2.0,roomheight/2.0,roomdepth/2.0),glm::vec3(c_up));

  //creating the projection matrix
  if(enable_perspective)
    projection_matrix = glm::frustum(-1.0, 1.0, -1.0, 1.0, 1.0, 70000.0);
    //projection_matrix = glm::perspective(glm::radians(90.0),1.0,0.1,5.0);
  else
    projection_matrix = glm::ortho(-wsize*4, wsize*4, -wsize*4, 5*wsize, 4*wsize, -wsize*4);

  glm::mat4 id = glm::mat4(1.0f);
  glm::vec3 translation_amt(g_xtrans*trans_factor,g_ytrans*trans_factor,g_ztrans*trans_factor);
  c_translation_matrix = glm::translate(id, translation_amt);

  // view_matrix = projection_matrix*lookat_matrix*c_rotation_matrix*c_translation_matrix;
  view_matrix = projection_matrix*lookat_matrix;

  matrixStack.push_back(view_matrix);


  // lowerbox->render_tree();
  // torso3->render_tree();
  // dogtrunk->render_tree();

  roombox->render_tree();

}

int main(int argc, char** argv)
{
  //! The pointer to the GLFW window
  GLFWwindow* window;

  //! Setting up the GLFW Error callback
  glfwSetErrorCallback(csX75::error_callback);

  //! Initialize GLFW
  if (!glfwInit())
    return -1;

  //We want OpenGL 4.0
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  //This is for MacOSX - can be omitted otherwise
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
  //We don't want the old OpenGL 
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

  //! Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(1024, 1024, "CS475/CS675 Tutorial 7: Hierarchical Modelling", NULL, NULL);
  if (!window)
    {
      glfwTerminate();
      return -1;
    }
  
  //! Make the window's context current 
  glfwMakeContextCurrent(window);

  //Initialize GLEW
  //Turn this on to get Shader based OpenGL
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err)
    {
      //Problem: glewInit failed, something is seriously wrong.
      std::cerr<<"GLEW Init Failed : %s"<<std::endl;
    }

  //Print and see what context got enabled
  std::cout<<"Vendor: "<<glGetString (GL_VENDOR)<<std::endl;
  std::cout<<"Renderer: "<<glGetString (GL_RENDERER)<<std::endl;
  std::cout<<"Version: "<<glGetString (GL_VERSION)<<std::endl;
  std::cout<<"GLSL Version: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<std::endl;

  //Keyboard Callback
  glfwSetKeyCallback(window, csX75::key_callback);
  //Framebuffer resize callback
  glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  //Initialize GL state
  csX75::initGL();
  initBuffersGL();

  // Loop until the user closes the window
  while (glfwWindowShouldClose(window) == 0)
    {
       
      // Render here
      renderGL();

      // Swap front and back buffers
      glfwSwapBuffers(window);
      
      // Poll for and process events
      glfwPollEvents();
    }
  
  glfwTerminate();
  return 0;
}

//-------------------------------------------------------------------------
