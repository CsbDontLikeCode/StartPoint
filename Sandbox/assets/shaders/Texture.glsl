#type VertexShader
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

uniform mat4 VP_Matrix;
uniform mat4 transform;

out vec2 v_TexCoord;


void main(){
	v_TexCoord = a_TexCoord;
	gl_Position = VP_Matrix * transform * vec4(a_Position, 1.0);

}

#type FragmentShader
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;	

uniform sampler2D u_Texture;

void main(){
	color = texture(u_Texture, v_TexCoord);
}