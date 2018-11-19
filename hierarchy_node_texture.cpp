#include "hierarchy_node_texture.hpp"

#include <iostream>

extern GLuint vPosition,vColor,vTexture,uModelViewMatrix;
extern std::vector<glm::mat4> matrixStack;

namespace csX75
{

	HNodeTexture::HNodeTexture(HNode* a_parent, GLuint num_v, glm::vec4* a_vertices, glm::vec4* a_colours, glm::vec4* a_tex_coords, std::size_t v_size, std::size_t c_size, std::size_t t_size){

		num_vertices = num_v;
		vertex_buffer_size = v_size;
		color_buffer_size = c_size;
		texture_buffer_size = t_size;
		// initialize vao and vbo of the object;


		//Ask GL for a Vertex Attribute Objects (vao)
		glGenVertexArrays (1, &vao);
		//Ask GL for aVertex Buffer Object (vbo)
		glGenBuffers (1, &vbo);

		//bind them
		glBindVertexArray (vao);
		glBindBuffer (GL_ARRAY_BUFFER, vbo);

		
		glBufferData (GL_ARRAY_BUFFER, vertex_buffer_size + color_buffer_size + texture_buffer_size, NULL, GL_STATIC_DRAW);
		glBufferSubData( GL_ARRAY_BUFFER, 0, vertex_buffer_size, a_vertices );
		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size, color_buffer_size, a_colours );
		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size+color_buffer_size, texture_buffer_size, a_tex_coords );

		//setup the vertex array as per the shader
		glEnableVertexAttribArray( vPosition );
		glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

		glEnableVertexAttribArray( vColor );
		glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size));

		glEnableVertexAttribArray( vTexture );
		glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size+color_buffer_size));


		// set parent

		if(a_parent == NULL){
			parent = NULL;
		}
		else{
			parent = a_parent;
			parent->add_child(this);
		}

		//initial parameters are set to 0;

		tx=ty=tz=rx=ry=rz=0;

		update_matrices();
	}


	void HNodeTexture::update_matrices(){

		rotation = glm::rotate(glm::mat4(1.0f), glm::radians(rx), glm::vec3(1.0f,0.0f,0.0f));
		rotation = glm::rotate(rotation, glm::radians(ry), glm::vec3(0.0f,1.0f,0.0f));
		rotation = glm::rotate(rotation, glm::radians(rz), glm::vec3(0.0f,0.0f,1.0f));

		translation = glm::translate(glm::mat4(1.0f),glm::vec3(tx,ty,tz));


	}

	void HNodeTexture::add_child(HNode* a_child){
		children.push_back(a_child);

	}

	void HNodeTexture::change_parameters(GLfloat atx, GLfloat aty, GLfloat atz, GLfloat arx, GLfloat ary, GLfloat arz){
		tx = atx;
		ty = aty;
		tz = atz;
		rx = arx;
		ry = ary;
		rz = arz;

		update_matrices();
	}

	void HNodeTexture::render(){

		//matrixStack multiply
		glm::mat4* ms_mult = multiply_stack(matrixStack);

		glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(*ms_mult));
		glBindVertexArray (vao);
		glDrawArrays(GL_TRIANGLES, 0, num_vertices);

		// for memory 
		delete ms_mult;

	}

	void HNodeTexture::render_tree(){
		
		matrixStack.push_back(translation);
		matrixStack.push_back(rotation);

		render();
		for(int i=0;i<children.size();i++){
			children[i]->render_tree();
		}
		matrixStack.pop_back();
		matrixStack.pop_back();

	}

	void HNodeTexture::inc_rx(){
		rx+=5;
		update_matrices();
	}


	void HNodeTexture::inc_ry(){
		ry+=5;
		update_matrices();
	}

	void HNodeTexture::inc_rz(){
		rz+=5;
		update_matrices();
	}

	void HNodeTexture::dec_rx(){
		rx-=5;
		update_matrices();
	}

	void HNodeTexture::dec_ry(){
		ry-=5;
		update_matrices();
	}

	void HNodeTexture::dec_rz(){
		rz-=5;
		update_matrices();
	}
	GLfloat HNodeTexture::get_rx(){
		return rx;
	}

	GLfloat HNodeTexture::get_tx(){
		return tx;
	}
	glm::mat4* multiply_stack(std::vector<glm::mat4> matStack){
		glm::mat4* mult;
		mult = new glm::mat4(1.0f);
	
		for(int i=0;i<matStack.size();i++){
			*mult = (*mult) * matStack[i];
		}	

		return mult;
	}

}