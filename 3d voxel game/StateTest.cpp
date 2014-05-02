#include "StateTest.h"

#include "GL.h"
#include <glm\glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Game.h"
#include "IRenderer.h"
#include "VoxelMatrix.h"
#include "Torus.h"
#include "Shader.h"

void StateTest::Load(Game *game, EventHandler *eventHandler)
{
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	Projection = glm::perspective(90.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	// Or, for an ortho camera :
	//Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

	// Camera matrix
	View       = glm::lookAt(
		glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
		glm::vec3(0,0,0), // and looks at the origin
		glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
	// Model matrix : an identity matrix (model will be at the origin)
	Model      = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around


	position = glm::vec3(0, 0, 5);
	rotation = glm::vec3(0, 0, 0);
	horizontalAngle = 0;
	verticalAngle = 0;
	mouseSpeed = 0.005f;
	moveSpeed = 16.0f;
	initialFoV = 90.0f;

	torus = new Torus();

	voxels = new VoxelMatrix(64, 64, 64);

	for (int x = -32; x < 32; x++)
	{
		for (int y = -32; y < 32; y++)
		{
			for (int z = -32; z < 32; z++)
			{
				if (x*x+y*y+z*z <= 30*30)
					voxels->setVoxel(x+32, y+32, z+32, reinterpret_cast<IVoxel*>(1));
			}
		}
	}
	/*voxels->setVoxel(3, 3, 3, reinterpret_cast<IVoxel*>(1));
	voxels->setVoxel(4, 3, 3, reinterpret_cast<IVoxel*>(1));
	voxels->setVoxel(5, 3, 3, reinterpret_cast<IVoxel*>(1));
	voxels->setVoxel(5, 4, 3, reinterpret_cast<IVoxel*>(1));
	voxels->setVoxel(3, 3, 5, reinterpret_cast<IVoxel*>(1));

	voxels->setVoxel(0, 0, 0, reinterpret_cast<IVoxel*>(1));
	voxels->setVoxel(0, 0, 15, reinterpret_cast<IVoxel*>(1));
	voxels->setVoxel(0, 15, 0, reinterpret_cast<IVoxel*>(1));
	voxels->setVoxel(0, 15, 15, reinterpret_cast<IVoxel*>(1));
	voxels->setVoxel(15, 0, 0, reinterpret_cast<IVoxel*>(1));
	voxels->setVoxel(15, 0, 15, reinterpret_cast<IVoxel*>(1));
	voxels->setVoxel(15, 15, 0, reinterpret_cast<IVoxel*>(1));
	voxels->setVoxel(15, 15, 15, reinterpret_cast<IVoxel*>(1));*/

	//shader = new Shader("shader");
	
	lastTime = glfwGetTime();
	nbFrames = 0;
	
}

void StateTest::Draw(Game *game, IRenderer *renderer)
{
	//shader->Bind();
	//shader->Update(MVP);

	for (int x = -1; x < 1; x++)
	{
		for (int y = -1; y < 1; y++)
		{
			for (int z = -1; z < 1; z++)
			{
				glm::mat4 ModelMatrix2 = glm::mat4(1.0);
				ModelMatrix2 = glm::translate(ModelMatrix2, glm::vec3((float)x*voxels->getWidth(), (float)y*voxels->getHeight(), (float)z*voxels->getWidth()));
				glm::mat4 MVP2 = Projection * View * ModelMatrix2;
				renderer->RenderMatrix(voxels, MVP2, SHADER_DEFAULT);
			}
		}
	}

	renderer->RenderMatrix(torus, MVP, SHADER_SPACE);
}

void StateTest::Update(Game *game)
{
	double currentTime = glfwGetTime();
     nbFrames++;
     if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1 sec ago
         // printf and reset timer
         printf("%f ms/frame\n", 1000.0/double(nbFrames));
         nbFrames = 0;
         lastTime += 1.0;
     }


	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
//	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(game->getWindow(), &xpos, &ypos);

	// Reset mouse position for next frame
	glfwSetCursorPos(game->getWindow(), 1024/2, 768/2);

	// Compute new orientation
	horizontalAngle += mouseSpeed * float(1024/2 - xpos );
	verticalAngle   += mouseSpeed * float( 768/2 - ypos );

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle), 
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
		);

	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f), 
		0,
		cos(horizontalAngle - 3.14f/2.0f)
		);

	// Up vector
	glm::vec3 up = glm::cross( right, direction );

	float tempMoveSpeed = moveSpeed;
	if(glfwGetKey(game->getWindow(), GLFW_KEY_SPACE ) == GLFW_PRESS)
		tempMoveSpeed = tempMoveSpeed*256;
	// Move forward
	if (glfwGetKey(game->getWindow(), GLFW_KEY_W ) == GLFW_PRESS){
		position += direction * deltaTime * tempMoveSpeed;
	}
	// Move backward
	if (glfwGetKey(game->getWindow(), GLFW_KEY_S ) == GLFW_PRESS){
		position -= direction * deltaTime * tempMoveSpeed;
	}
	// Strafe right
	if (glfwGetKey(game->getWindow(), GLFW_KEY_D ) == GLFW_PRESS){
		position += right * deltaTime * tempMoveSpeed;
	}
	// Strafe left
	if (glfwGetKey(game->getWindow(), GLFW_KEY_A ) == GLFW_PRESS){
		position -= right * deltaTime * tempMoveSpeed;
	}

	float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	Projection = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 655360.f);
	// Camera matrix
	View       = glm::lookAt(
		position,           // Camera is here
		position+direction, // and looks here : at the same position, plus "direction"
		up                  // Head is up (set to 0,-1,0 to look upside-down)
		);

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;



	/*View = glm::lookAt(
	glm::vec3(5*cos(glfwGetTime()),3,5*sin(glfwGetTime())), // Camera is at (4,3,3), in World Space << (now rotating)
	glm::vec3(0,0,0), // and looks at the origin
	glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
	);*/
	// Model matrix : an identity matrix (model will be at the origin)
	Model      = glm::mat4(1.0f);
	MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around
}