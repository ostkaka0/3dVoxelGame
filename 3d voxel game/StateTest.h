#pragma once
#include "State.h"
#include "GL.h"

class VoxelMatrix;

class StateTest : public State
{
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection;
	// Or, for an ortho camera :
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates
	
	// Camera matrix
	glm::mat4 View;
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model;
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP; // Remember, matrix multiplication is the other way around

	VoxelMatrix *voxels;
public:
	virtual void Load(Game *game, EventHandler *eventHandler);
	virtual void Draw(Game *game, IRenderer *renderer);
	virtual void Update(Game *game);
};