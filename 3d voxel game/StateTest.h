#pragma once
#include "State.h"
#include "GL.h"

class VoxelMatrix;
class Shader;
class Torus;

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

	glm::vec3 position;
	glm::vec3 rotation;
	float horizontalAngle;
	float verticalAngle;
	float mouseSpeed;
	float moveSpeed;
	float initialFoV;

	VoxelMatrix *voxels;
	Torus *torus;

	Shader *shader;

	// fps counter
	double lastTime;
	int nbFrames;

public:
	virtual void Load(Game *game, EventHandler *eventHandler);
	virtual void Draw(Game *game, IRenderer *renderer);
	virtual void Update(Game *game);
};