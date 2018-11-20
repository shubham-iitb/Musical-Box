#version 130

uniform sampler2D texture;
in vec4 color;
in vec2 tex;
out vec4 frag_color;

void main () 
{
  frag_color = texture2D(texture,tex);
}
