#version 330

layout(points) in;
layout(triangle_strip, max_vertices=14) out;

in vec3 geometryColor[];
out vec3 fragmentColor;

uniform mat4 MVP;

void main()
{
	vec4 corners[8];
		corners[0] = vec4(-0.5, -0.5, -0.5, 1); corners[1] = vec4(-0.5, -0.5, +0.5, 1);
		corners[2] = vec4(-0.5, +0.5, -0.5, 1); corners[3] = vec4(-0.5, +0.5, +0.5, 1); 
		corners[4] = vec4(+0.5, -0.5, -0.5, 1); corners[5] = vec4(+0.5, -0.5, +0.5, 1);
		corners[6] = vec4(+0.5, +0.5, -0.5, 1); corners[7] = vec4(+0.5, +0.5, +0.5, 1);
		
	vec3 cornerColors[8];
		cornerColors[0] = vec3(1.f,    1.f,   1.f);   cornerColors[1] = vec3(1.f,	1.f,	1.f);
		cornerColors[2] = vec3(0.5f,   0.5f,  0.5f);  cornerColors[3] = vec3(0.5f,	0.5f,	0.5f);
		cornerColors[4] = vec3(1.f,    1.f,   1.f);   cornerColors[5] = vec3(1.f,	1.f,	1.f);
		cornerColors[6] = vec3(0.5f,   0.5f,  0.5f);  cornerColors[7] = vec3(0.5f,	0.5f,	0.5f);
		
	int vertices[14];
	vertices[0] = 0;  vertices[1] = 1;
	vertices[2] = 2;  vertices[3] = 3;
	vertices[4] = 7;  vertices[5] = 1;
	vertices[6] = 5;  vertices[7] = 0;
	vertices[8] = 4;  vertices[9] = 2;
	vertices[10] = 6; vertices[11] = 7;
	vertices[12] = 4; vertices[13] = 5;

	for(int i = 0; i < gl_in.length(); i++)
	{
		for (int j = 0; j < 14; j++)
		{
			int k = vertices[j];

			fragmentColor = geometryColor[i]*cornerColors[k];
			gl_Position = MVP * (gl_in[i].gl_Position + corners[k]);
			EmitVertex();
		}
		/*gl_Position = gl_in[i].gl_Position;
		EmitVertex();
		gl_Position = gl_in[i].gl_Position + vec4(1,1,1,1);
		EmitVertex();
		gl_Position = gl_in[i].gl_Position + vec4(-1,1,1,1);;
		EmitVertex();*/
		
		/*gl_Position = MVP * (gl_in[i].gl_Position + corners[0]);
		EmitVertex();
		gl_Position = MVP * (gl_in[i].gl_Position + corners[1]);
		EmitVertex();
		
		gl_Position = MVP * (gl_in[i].gl_Position + corners[2]);
		EmitVertex();
		gl_Position = MVP * (gl_in[i].gl_Position + corners[3]);
		EmitVertex();
		
		gl_Position = MVP * (gl_in[i].gl_Position + corners[7]);
		EmitVertex();
		gl_Position = MVP * (gl_in[i].gl_Position + corners[1]);
		EmitVertex();
		
		
		fragmentColor = vec3(1.f-geometryColor[i][0],1.f-geometryColor[i][1],1.f-geometryColor[i][2]);
		
		gl_Position = MVP * (gl_in[i].gl_Position + corners[5]);
		EmitVertex();
		gl_Position = MVP * (gl_in[i].gl_Position + corners[0]);
		EmitVertex();
		
		gl_Position = MVP * (gl_in[i].gl_Position + corners[4]);
		EmitVertex();
		gl_Position = MVP * (gl_in[i].gl_Position + corners[2]);
		EmitVertex();
		
		gl_Position = MVP * (gl_in[i].gl_Position + corners[6]);
		EmitVertex();
		gl_Position = MVP * (gl_in[i].gl_Position + corners[7]);
		EmitVertex();
		
		gl_Position = MVP * (gl_in[i].gl_Position + corners[4]);
		EmitVertex();
		gl_Position = MVP * (gl_in[i].gl_Position + corners[5]);
		EmitVertex();*/
	}
	EndPrimitive();
}
/*

layout(points) in;
layout(triangle_strip, max_vertices=14) out;

//in vec3 iColor[];
//out vec3 oColor;

vec4 corners[8];

void main() {

	//corners = {
		corners[0] = vec4(-0.5, -0.5, -0.5, 1); corners[1] = vec4(-0.5, -0.5, +0.5, 1);
		corners[2] = vec4(-0.5, +0.5, -0.5, 1); corners[3] = vec4(-0.5, +0.5, +0.5, 1); 
		corners[4] = vec4(+0.5, -0.5, -0.5, 1); corners[5] = vec4(+0.5, -0.5, +0.5, 1);
		corners[6] = vec4(+0.5, +0.5, -0.5, 1); corners[7] = vec4(+0.5, +0.5, +0.5, 1);
		//};

	for(int i = 0; i < gl_in.length(); i++)
	{
		//oColor = iColor[i];

		gl_Position = vec4(gl_in[i].gl_Position) + corners[0];
		EmitVertex();
		gl_Position = vec4(gl_in[i].gl_Position) + corners[1];
		EmitVertex();
		
		gl_Position = vec4(gl_in[i].gl_Position) + corners[2];
		EmitVertex();
		gl_Position = vec4(gl_in[i].gl_Position) + corners[3];
		EmitVertex();
		
		gl_Position = vec4(gl_in[i].gl_Position) + corners[7];
		EmitVertex();
		gl_Position = vec4(gl_in[i].gl_Position) + corners[1];
		EmitVertex();
		
		gl_Position = vec4(gl_in[i].gl_Position) + corners[5];
		EmitVertex();
		gl_Position = vec4(gl_in[i].gl_Position) + corners[0];
		EmitVertex();
		
		gl_Position = vec4(gl_in[i].gl_Position) + corners[4];
		EmitVertex();
		gl_Position = vec4(gl_in[i].gl_Position) + corners[2];
		EmitVertex();
		
		gl_Position = vec4(gl_in[i].gl_Position) + corners[6];
		EmitVertex();
		gl_Position = vec4(gl_in[i].gl_Position) + corners[7];
		EmitVertex();
		
		gl_Position = vec4(gl_in[i].gl_Position) + corners[4];
		EmitVertex();
		gl_Position = vec4(gl_in[i].gl_Position) + corners[5];
		EmitVertex();
	}
	
	EndPrimitive();
}*/