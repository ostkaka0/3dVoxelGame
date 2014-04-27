#version 330

layout(points) in;
layout(triangle_strip, max_vertices = 14) out;

//in vec3 iColor[];
//out vec3 oColor;

vec4 corners[8];

void main() {

	//corners = {
		corners[0] = vec4(-0.5, -0.5, -0.5, 1); corners[1] = vec4(-0.5, -0.5, +0.5, 1); corners[2] = vec4(-0.5, +0.5, -0.5, 1); corners[3] = vec4(-0.5, +0.5, +0.5, 1); 
		corners[4] = vec4(+0.5, -0.5, -0.5, 1); corners[5] = vec4(+0.5, -0.5, +0.5, 1); corners[6] = vec4(+0.5, +0.5, -0.5, 1); corners[7] = vec4(+0.5, +0.5, +0., 15);
		//};

	//oColor = iColor[0];

	gl_Position = gl_in[0].gl_Position + corners[0];
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + corners[1];
	EmitVertex();
	
	gl_Position = gl_in[0].gl_Position + corners[2];
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + corners[3];
	EmitVertex();
	
	gl_Position = gl_in[0].gl_Position + corners[7];
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + corners[1];
	EmitVertex();
	
	gl_Position = gl_in[0].gl_Position + corners[5];
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + corners[0];
	
	gl_Position = gl_in[0].gl_Position + corners[4];
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + corners[2];
	EmitVertex();
	
	gl_Position = gl_in[0].gl_Position + corners[6];
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + corners[7];
	EmitVertex();
	
	gl_Position = gl_in[0].gl_Position + corners[4];
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + corners[5];
	EmitVertex();
	
	EndPrimitive();
}