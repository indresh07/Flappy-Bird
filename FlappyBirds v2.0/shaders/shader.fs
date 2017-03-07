#version 130

in vec2 fpos;
in vec4 fcolor;
in vec2 fuv;

out vec4 color;

uniform sampler2D mySampler;

void main(){

	vec4 Texture = texture( mySampler, fuv);
	
	color = Texture;
}