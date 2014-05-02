#include "VoxelMatrix.h"
#include "Shader.h"
#include "Vertex.h"

VoxelMatrix::VoxelMatrix(const int width, const int height, const int depth)
	: m_width(width)
	, m_height(height)
	, m_depth(depth)
	, m_voxels(new IVoxel*[width*height*depth])
{
	for (int z = 0; z < depth; z++)
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				setVoxel(x, y, z, nullptr);
			}
		}
	}
}

VoxelMatrix::VoxelMatrix(const int width, const int height, const int depth, IVoxel **voxels)
	: m_width(width)
	, m_height(height)
	, m_depth(depth)
	, m_voxels(voxels)
{
}

bool VoxelMatrix::Render(IRenderer *renderer, glm::mat4 MVP, ShaderType shaderType)
{
	if (shaderType == SHADER_DEFAULT)
	{
		Shader *shader = renderer->getShader(shaderType);

#pragma region rendering
		if (m_changed)
		{
		GLuint vertexbuffer;

				

				glGenBuffers(1, &vertexbuffer);
				glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

				//GLuint colorVertexbuffer;
				//glGenBuffers(1, &colorVertexbuffer);
				//glBindBuffer(GL_ARRAY_BUFFER, colorVertexbuffer);

				std::vector<Vertex> g_vertex_buffer_data;
				g_vertex_buffer_data.reserve(3*2*6 * m_width*m_height*m_depth); // för att snabba på!
				for (int x = 0; x < m_width; x++)
				{
					for (int y = 0; y < m_height; y++)
					{
						for (int z = 0; z < m_depth; z++)
						{
							if (getVoxel(x, y, z) == 0)
								continue;

							GLfloat r,g,b;

							r = 0.25f + (float)(rand()%64)/256.f;
							g = 0.25f + (float)(rand()%64)/256.f;
							b = 0.25f + (float)(rand()%64)/256.f;

#pragma region cube2
							const Vertex vertices[8] =
							{
								Vertex(x-0.5, y-0.5, z-0.5, r, g, b), Vertex(x-0.5, y-0.5, z+0.5, r, g, b),
								Vertex(x-0.5, y+0.5, z-0.5, r, g, b), Vertex(x-0.5, y+0.5, z+0.5, r, g, b), 
								Vertex(x+0.5, y-0.5, z-0.5, r, g, b), Vertex(x+0.5, y-0.5, z+0.5, r, g, b),
								Vertex(x+0.5, y+0.5, z-0.5, r, g, b), Vertex(x+0.5, y+0.5, z+0.5, r, g, b)
							};
		
		
							//triangle strip
							/*const int vertexIds[14] =
							{
								 0,   1,
								 2,   3,
								 7,   1,
								 5,   0,
								 4,   2,
								 6,   7,
								 4,   5,
							};*/

							//faces
							const int vertexIds[36] =
							{
								 0, 1, 2,
								 2, 1, 3,

								 1, 5, 3,
								 3, 5, 7,

								 5, 4, 7,
								 7, 4, 6,

								 4, 0, 6,
								 6, 0, 2,

								 4, 5, 0,
								 5, 0, 1,

								 6, 7, 2,
								 2, 7, 3
							};

							const bool isVisible[6] = 
							{
								(getVoxel(x-1, y, z) == 0 || x == 0),
								(getVoxel(x, y, z+1) == 0 || z == 15),
								(getVoxel(x+1, y, z) == 0 || x == 15),
								(getVoxel(x, y, z-1) == 0 || z == 0),
								(getVoxel(x, y-1, z) == 0 || y == 0),
								(getVoxel(x, y+1, z) == 0 || y == 15)
							};

							for(int i = 0; i < 36; i++)
							{
								if (isVisible[(int)floor((float)i/6.f)])
								{
									int v = vertexIds[i];
									g_vertex_buffer_data.push_back(vertices[v]); 
								}
							}
#pragma endregion cube2


						}
					}
				}

				// Give our vertices to OpenGL.
				glBufferData(GL_ARRAY_BUFFER, g_vertex_buffer_data.size() * sizeof(Vertex), g_vertex_buffer_data.data(), GL_STATIC_DRAW);
				m_vertexBuffer = vertexbuffer;
				//matrix->m_colorVertexbuffer = colorVertexbuffer;
				m_size = g_vertex_buffer_data.size();
				m_changed = false;

				//vertexBuffers.push_back(std::pair<GLuint, GLuint>(vertexbuffer, g_vertex_buffer_data.size()));


				m_vertexBuffer = vertexbuffer;
				m_changed = false;
		}
#pragma endregion rendering



#pragma region redering2
			shader->Bind();
			shader->Update(MVP);//glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		

			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position))); //0, position

			//glEnableVertexAttribArray(1);       ////normal-saker kan man skita i just nu
			//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(baseOffset + offsetof(Vertex, normal)));       ////normal-saker kan man skita i just nu

			//glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, color)));//glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, color))); //1, färg

			glDrawArrays(GL_TRIANGLES, 0, m_size);

			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);

			//shader->Update(MVP);

			/*glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position))); //0, position

			//glEnableVertexAttribArray(1);       ////normal-saker kan man skita i just nu
			//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(baseOffset + offsetof(Vertex, normal)));       ////normal-saker kan man skita i just nu

			//glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, color)));//glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, color))); //1, färg

			glDrawArrays(GL_TRIANGLES, 0, m_size);

			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);*/

#pragma endregion

		return true;
	}
	else return false;
}

ShaderType VoxelMatrix::getShaderType() const
{
	return SHADER_DEFAULT;
}

int VoxelMatrix::getWidth()
{
	return m_width;
}

int VoxelMatrix::getHeight()
{
	return m_height;
}

IVoxel *VoxelMatrix::getVoxel(int x, int y, int z)
{
	return m_voxels[x%m_width + y%m_height*m_width + z%m_depth*m_height*m_width];
}

void VoxelMatrix::setVoxel(int x, int y, int z, IVoxel *voxel)
{
	m_voxels[x%m_width + y%m_height*m_width + z%m_depth*m_height*m_width] = voxel;
}
