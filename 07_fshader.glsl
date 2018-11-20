//#version 130

#version 400

uniform sampler2D texture1;
in vec4 color;
in vec2 tex;
out vec4 frag_color;

void main () 
{
  //frag_color = texture2D(texture1,tex);
  frag_color = texture(texture1,tex);
}
