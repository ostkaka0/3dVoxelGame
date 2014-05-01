#version 330

layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;

in vec3 geometryColor[];
out vec3 fragmentColor;

uniform mat4 MVP;

void main()
{
	for(int i = 0; i < gl_in.length(); i++)
	{
		gl_Position = MVP * gl_in[i].gl_Position;
		fragmentColor = geometryColor[i]*(0.5+mod(gl_in[i].gl_Position[1], 2.0));
		EmitVertex();
	}
	EndPrimitive();
}
