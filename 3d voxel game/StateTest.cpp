#include "StateTest.h"

#include "Game.h"
#include "IRenderer.h"
#include "VoxelMatrix.h"
#include "GL.h"

void StateTest::Load(Game *game, EventHandler *eventHandler)
{
		// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	// Or, for an ortho camera :
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates
	
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


	voxels = new VoxelMatrix(16, 16, 16);

	voxels->setVoxel(3, 3, 3, reinterpret_cast<IVoxel*>(1));
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
	voxels->setVoxel(15, 15, 15, reinterpret_cast<IVoxel*>(1));


}

void StateTest::Draw(Game *game, IRenderer *renderer)
{
	//glMatrixMode(GL_PROJECTION);
	//renderer->PushMatrix();
	//renderer->Scale(1, 1 , -1);
	//renderer->Translate(0,0, 10);
	renderer->RenderMatrix(voxels, MVP);
	//renderer->Scale(-1, -1, -1);
	//renderer->Translate(0,0, -10);
	//renderer->PopMatrix();
}

void StateTest::Update(Game *game)
{

}