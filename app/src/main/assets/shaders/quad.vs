uniform mat4 model;
uniform mat4 projection;

attribute vec2 aPos;
attribute vec2 aTexCoords;

varying vec2 texCoords;

void main()
{
  texCoords = aTexCoords;
  gl_Position = projection * model * vec4(aPos, 0.0, 1.0);
}