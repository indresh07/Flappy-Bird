#version 130

in vec2 vertexPosition;
in vec4 color;
in vec2 uv;

out vec2 fpos;
out vec4 fcolor;
out vec2 fuv;

uniform mat4 projMatrix;

void main(){
	
	gl_Position = (projMatrix * vec4( vertexPosition, 0.0, 1.0));

	fpos = vertexPosition;
	fcolor = color;
	fuv = vec2(uv.x, 1-uv.y);
}

