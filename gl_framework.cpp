#include "gl_framework.hpp"
#include "hierarchy_node.hpp"
// #include "07_hierarchical_modelling.cpp"

extern GLfloat c_xrot,c_yrot,c_zrot;
extern bool enable_perspective;

extern csX75::HNode*  lowerbox,*curr_node,*upperbox;
extern csX75::HNode*  hipl,* hipr,* head,* neck,* torso1,* torso2,* torso3,* thighl,* thighr,* kneel,* kneer,* legl,* legr,* footl,* footr,* shoulderl,* shoulderr,* uarml,* uarmr,* elbowl,* elbowr,* larml,* larmr,* handl,* handr, * hat;
extern csX75::HNode*  doghead,*dogneck,*dogtrunk,*dogtail,*dogarm1,*dogarm2,*dogarm3,*dogarm4;
extern csX75::HNode*  umbrellafolded,* umbrellaopen;
extern float wsize;
extern float g_xtrans,g_ytrans,g_ztrans;
extern GLfloat c_xpos, c_ypos, c_zpos;
extern void saveFrame();

namespace csX75
{
  //! Initialize GL State
  void initGL(void)
  {
    //Set framebuffer clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //Set depth buffer furthest depth
    glClearDepth(1.0);
    //Set depth test to less-than
    glDepthFunc(GL_LESS);
    //Enable depth testing
    glEnable(GL_DEPTH_TEST);
  }
  
  //!GLFW Error Callback
  void error_callback(int error, const char* description)
  {
    std::cerr<<description<<std::endl;
  }
  
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height)
  {
    //!Resize the viewport to fit the window size - draw to entire window
    glViewport(0, 0, width, height);
  }

  void openbox(void){
  if(upperbox->get_rx()==180) return;
    upperbox->inc_rx();
  }
void closebox(void){
  if(upperbox->get_rx()==0) return;
  upperbox->dec_rx();
  }

  void umbrellabutton(void){
    if(umbrellaopen->get_tx()==1000.0){
      umbrellafolded->change_parameters(1000.0,0.0,3.0,0.0,0.0,0.0);
      umbrellaopen->change_parameters(0.0,0.0,10.0,0.0,0.0,0.0);      
    }
    else{
      umbrellafolded->change_parameters(0.0,0.0,3.0,0.0,0.0,0.0);
      umbrellaopen->change_parameters(1000.0,0.0,10.0,0.0,0.0,0.0);
    }

  }


  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    //!Close the window if the ESC key was pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);

    // else if (key == GLFW_KEY_3 && action == GLFW_PRESS)   // to control the humanoid model
    //   curr_node = torso3; 
    // else if (key == GLFW_KEY_4 && action == GLFW_PRESS)   // to control the animal model
    //   curr_node = dogtrunk; 
    // else if (key == GLFW_KEY_5 && action == GLFW_PRESS)   // to control the animal model
    //   umbrellabutton();

    else if (key == GLFW_KEY_H && action == GLFW_PRESS)
      curr_node = torso2;  

    else if (key == GLFW_KEY_7 && action == GLFW_PRESS)
      curr_node = neck;  

    else if (key == GLFW_KEY_Y && action == GLFW_PRESS)
      curr_node = shoulderr; 
    else if (key == GLFW_KEY_U && action == GLFW_PRESS)
      curr_node = shoulderl; 
    else if (key == GLFW_KEY_T && action == GLFW_PRESS)
      curr_node = elbowr; 
    else if (key == GLFW_KEY_I && action == GLFW_PRESS)
      curr_node = elbowl; 
    else if (key == GLFW_KEY_R && action == GLFW_PRESS)
      curr_node = handr; 
    else if (key == GLFW_KEY_O && action == GLFW_PRESS)
      curr_node = handl; 

    else if (key == GLFW_KEY_B && action == GLFW_PRESS)
      curr_node = hipr; 
    else if (key == GLFW_KEY_N && action == GLFW_PRESS)
      curr_node = hipl; 
    else if (key == GLFW_KEY_V && action == GLFW_PRESS)
      curr_node = kneer; 
    else if (key == GLFW_KEY_M && action == GLFW_PRESS)
      curr_node = kneel; 
    else if (key == GLFW_KEY_C && action == GLFW_PRESS)
      curr_node = footr; 
    else if (key == GLFW_KEY_COMMA && action == GLFW_PRESS)
      curr_node = footl; 

    else if (key == GLFW_KEY_LEFT_BRACKET && action == GLFW_PRESS)
      curr_node = dogneck; 
    else if (key == GLFW_KEY_RIGHT_BRACKET && action == GLFW_PRESS)
      curr_node = dogtail; 
    else if (key == GLFW_KEY_J && action == GLFW_PRESS)
      curr_node = dogarm1; 
    else if (key == GLFW_KEY_K && action == GLFW_PRESS)
      curr_node = dogarm2; 
    else if (key == GLFW_KEY_L && action == GLFW_PRESS)
      curr_node = dogarm3; 
    else if (key == GLFW_KEY_SEMICOLON && action == GLFW_PRESS)
      curr_node = dogarm4;      

    else if (key == GLFW_KEY_0 && action == GLFW_PRESS)
      curr_node = lowerbox; 
    else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS){
      if(curr_node==elbowl || curr_node==elbowr || curr_node==kneel || curr_node==kneer){
        }
      else curr_node->dec_ry();
    }
    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS){
      if(curr_node==elbowl || curr_node==elbowr || curr_node==kneel || curr_node==kneer){
        }
      else curr_node->inc_ry();
    }
    else if (key == GLFW_KEY_UP && action == GLFW_PRESS){
      if(curr_node==kneel || curr_node==kneer){
          if(curr_node->get_rx()>=-160) curr_node->dec_rx();
        }
        else if(curr_node==elbowl || curr_node==elbowr){
            if(curr_node->get_rx()>0) curr_node->dec_rx();
        }
      else curr_node->dec_rx();
    }
    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS){
      if(curr_node==kneel || curr_node==kneer){
        if(curr_node->get_rx()<0) curr_node->inc_rx();
        }
        else if(curr_node==elbowl || curr_node==elbowr){
            if(curr_node->get_rx()<160) curr_node->inc_rx();
        }
      else curr_node->inc_rx();
    }
    else if (key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS){
      if(curr_node==elbowl || curr_node==elbowr || curr_node==kneel || curr_node==kneer){
        }
      else curr_node->dec_rz();
    }
    else if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS){
      if(curr_node==elbowl || curr_node==elbowr || curr_node==kneel || curr_node==kneer){
        }
      else curr_node->inc_rz();
    }

    // else if (key == GLFW_KEY_1 && action == GLFW_PRESS)
    //   openbox();
    // else if (key == GLFW_KEY_2 && action == GLFW_PRESS)
    //   closebox();
    else if (key == GLFW_KEY_P && action == GLFW_PRESS)
      enable_perspective = !enable_perspective;   
    // else if (key == GLFW_KEY_RIGHT_ALT && action == GLFW_PRESS)
      // saveFrame();   
    else if (key == GLFW_KEY_A  && action == GLFW_PRESS)
      c_yrot -= 5.0;
    else if (key == GLFW_KEY_D  && action == GLFW_PRESS)
      c_yrot += 5.0;
    else if (key == GLFW_KEY_W  && action == GLFW_PRESS)
      c_xrot -= 5.0;
    else if (key == GLFW_KEY_S  && action == GLFW_PRESS)
      c_xrot += 5.0;        
    else if (key == GLFW_KEY_Q  && action == GLFW_PRESS)
      c_zrot -= 5.0;
    else if (key == GLFW_KEY_E  && action == GLFW_PRESS)
      c_zrot += 5.0;   
    else if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS)
      wsize = wsize - 2;
    else if (key == GLFW_KEY_RIGHT_SHIFT && action == GLFW_PRESS)
      wsize = wsize + 2;
    else if (key == GLFW_KEY_KP_1 && action == GLFW_PRESS)
      c_xpos += 2;      
    else if (key == GLFW_KEY_KP_3 && action == GLFW_PRESS)
      c_xpos -= 2;    
    else if (key == GLFW_KEY_KP_4 && action == GLFW_PRESS)
      c_ypos+= 2;    
    else if (key == GLFW_KEY_KP_6 && action == GLFW_PRESS)
      c_ypos-= 2;    
    else if (key == GLFW_KEY_KP_7 && action == GLFW_PRESS)
      c_zpos+= 2;    
    else if (key == GLFW_KEY_KP_9 && action == GLFW_PRESS)
      c_zpos-= 2;    
    else if (key == GLFW_KEY_KP_0 && action == GLFW_PRESS)
      c_xrot+= 5;    
    else if (key == GLFW_KEY_KP_2 && action == GLFW_PRESS)
      c_xrot-= 5;    
    else if (key == GLFW_KEY_KP_5 && action == GLFW_PRESS)
      c_yrot+= 5;    
    else if (key == GLFW_KEY_KP_8 && action == GLFW_PRESS)
      c_yrot-= 5;    
      
            
  }
};  
  


