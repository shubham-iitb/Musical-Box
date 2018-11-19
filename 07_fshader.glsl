#version 130

in vec4 color;
in vec2 tex;
uniform sampler2D texture;
out vec4 frag_color;

void main () 
{
  frag_color = texture2D(texture,tex);
}
