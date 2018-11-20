#version 130

in vec4 vPosition;
in vec4 vColor;
in vec2 vTexture;
out vec4 color;
out vec2 tex;
uniform mat4 uModelViewMatrix;

void main (void) 
{
  gl_Position = uModelViewMatrix * vPosition;
  color = vColor;
  tex = vTexture;
}
