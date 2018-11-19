/*
  A program which opens a window and draws three arms in a hierarchy

  Use the arrow keys and PgUp,PgDn, 
  keys to make the arms move.

  Use the keys 1,2 and 3 to switch between arms.

  Written by - 
               Harshavardhan Kode
*/
#ifndef _COLORCUBE_HPP_
#define _COLORCUBE_HPP_

// Defining the ESCAPE Key Code
#define ESCAPE 27
// Defining the DELETE Key Code
#define DELETE 127

#include <vector>
#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "hierarchy_node.hpp"

/*// Translation Parameters
GLfloat xpos=0.0,ypos=0.0,zpos=0.0;
// Rotation Parameters
GLfloat xrot=0.0,yrot=0.0,zrot=0.0;*/
// Camera position and rotation Parameters
GLfloat c_xpos = 0.0, c_ypos = 0.0, c_zpos = 2.0;
GLfloat c_up_x = 0.0, c_up_y = 1.0, c_up_z = 0.0;
GLfloat c_xrot=0.0,c_yrot=0.0,c_zrot=0.0;
float g_xtrans = 0.0, g_ytrans = 0.0, g_ztrans = -1600.0;
float trans_factor = 0.02;

//Running variable to toggle culling on/off
bool enable_culling=true;
//Running variable to toggle wireframe/solid modelling
bool solid=true;
//Enable/Disable perspective view
bool enable_perspective=false;
//Shader program attribs
GLuint vPosition,vColor,vTexture;

//global matrix stack for hierarchical modelling
std::vector<glm::mat4> matrixStack;

csX75::HNode*  root_node;
csX75::HNode*  curr_node;

csX75::HNode* hipl;
csX75::HNode* hipr;
csX75::HNode* head;
csX75::HNode* neck;
csX75::HNode* torso1;
csX75::HNode* torso2;
csX75::HNode* torso3;
csX75::HNode* thighl;
csX75::HNode* thighr;
csX75::HNode* kneel;
csX75::HNode* kneer;
csX75::HNode* legl;
csX75::HNode* legr;
csX75::HNode* footl;
csX75::HNode* footr;
csX75::HNode* shoulderl;
csX75::HNode* shoulderr;
csX75::HNode* uarml;
csX75::HNode* uarmr;
csX75::HNode* elbowl;
csX75::HNode* elbowr;
csX75::HNode* larml;
csX75::HNode* larmr;
csX75::HNode* handl;
csX75::HNode* handr;
csX75::HNode* lowerbox;
csX75::HNode* upperbox;

csX75::HNode* roombox;

// --------props--------

csX75::HNode* hat;
csX75::HNode* umbrellastick;
csX75::HNode* umbrellafolded;
csX75::HNode* umbrellaopen;


// ----------------
csX75::HNode* doghead;
csX75::HNode* dogneck;
csX75::HNode* dogtrunk;
csX75::HNode* dogtail;
csX75::HNode* dogarm1;
csX75::HNode* dogarm2;
csX75::HNode* dogarm3;
csX75::HNode* dogarm4;


//-------------------------------------------------------------------------

#endif
