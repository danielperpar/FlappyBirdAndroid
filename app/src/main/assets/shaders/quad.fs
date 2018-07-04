precision mediump float;

uniform sampler2D textureSampler;
uniform float alpha;

varying vec2 texCoords;

void main()
{
  vec4 color = texture2D(textureSampler, texCoords);
  gl_FragColor = vec4(color.rgb, color.a * alpha);
}