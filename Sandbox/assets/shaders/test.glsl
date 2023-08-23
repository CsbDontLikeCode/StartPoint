#type VertexShader
#version 330 core

layout(location = 0) in vec3 a_WorldPosition;

void main(){
	gl_Position = vec4(a_WorldPosition, 1.0);
}

#type FragmentShader
#version 330 core

layout(location = 0) out vec4 color;

void main(){
	color = vec4(0.0, 1.0, 0.0, 1.0);
}