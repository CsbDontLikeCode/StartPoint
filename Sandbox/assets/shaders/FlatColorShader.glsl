#type VertexShader
#version 330 core

layout(location = 0) in vec3 a_Position;

uniform mat4 u_ProjectView;
uniform mat4 u_Transform;

void main(){
	gl_Position = u_ProjectView * u_Transform * vec4(a_Position, 1.0);

}

#type FragmentShader
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;

void main(){
	color = u_Color;
}