#version 330 core

#define MAXFOG 32
#define FOGRED   0.f
#define FOGGREEN 0.5f
#define FOGBLUE  1.f

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;

// Output data ; will be interpolated for each fragment.
out vec3 fragmentColor;
// Values that stay constant for the whole mesh.
uniform mat4 MVP;

void main(){	

	// Output position of the vertex, in clip space : MVP * position
	gl_Position =  MVP * vec4(vertexPosition_modelspace,1);

	// The color of each vertex will be interpolated
	// to produce the color of each fragment
	
	float distance = sqrt(gl_Position[0]*gl_Position[0] + gl_Position[1]*gl_Position[1] + gl_Position[2]*gl_Position[2]);
	
	fragmentColor = vertexColor;
	
	if (distance >= MAXFOG)
	{
		fragmentColor[0] = FOGRED;
		fragmentColor[1] = FOGGREEN;
		fragmentColor[2] = FOGBLUE;
	}
	else if (distance > 1)
	{
		distance /= MAXFOG;
		
		fragmentColor[0] += distance*(FOGRED-fragmentColor[0]);
		fragmentColor[1] += distance*(FOGGREEN-fragmentColor[1]);
		fragmentColor[2] += distance*(FOGBLUE-fragmentColor[2]);
	}
	
	
	//fragmentColor[0] = 1.f;
}


