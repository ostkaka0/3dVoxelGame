#include "Torus.h"
#include "Shader.h"
#include "Vertex2.h"

Torus::Torus(void)
	:texture("Jellyfish.bmp")
{
}


Torus::~Torus(void)
{
}

bool Torus::Render(IRenderer *renderer, glm::mat4 MVP, ShaderType shaderType)
{
	if (shaderType == SHADER_SPACE)
	{
		Shader *shader = renderer->getShader(shaderType);

#pragma region rendering
		if (m_changed)
		{
				GLuint vertexbuffer;

				//spaceShader->Bind();

				glGenBuffers(1, &vertexbuffer);
				glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

				//GLuint colorVertexbuffer;
				//glGenBuffers(1, &colorVertexbuffer);
				//glBindBuffer(GL_ARRAY_BUFFER, colorVertexbuffer);

				std::vector<Vertex2> g_vertex_buffer_data;
				g_vertex_buffer_data.reserve(32*32*6); // för att snabba på!

				  //glFrontFace(GL_CW);
 
				  //glBindTexture(GL_TEXTURE_2D, texture);
				  //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
 
				  const double PI = 3.1415926535897932384626433832795;
				  const double TAU = 2 * PI;
				  const int rSeg = 64;//128;
				  const int cSeg = 128;//256;
				  const double c = 32000.f;
				  const double r = 8000.f;
 
				  for (int i = 0; i < rSeg; i++) {
					//glBegin(GL_QUAD_STRIP);
					for (int j = 0; j <= cSeg; j++) {
					  for (int l = 0; l < 6; l++) {
						  
						  //std::cout << i << " " << j << " " << l << std::endl;

						int k = (l%3 == 1 || l == 5)? 1:0;		// 0,1,0 , 0,1,1
						int m = j + ((l >= 2 && l <= 4)? 1:0);	// 0,0,1 , 1,1,0

						//if (l >= 2)
						//	k = 1-k;

						double s = (i + k) % rSeg + 0.5;
						double t = m % (cSeg + 1);
 
						double x = (c + r * cos(s * TAU / rSeg)) * cos(t * TAU / cSeg);
						double y = (c + r * cos(s * TAU / rSeg)) * sin(t * TAU / cSeg);
						double z = r * sin(s * TAU / rSeg);
 
						double u = (i + k) / (float) rSeg;
						double v = t / (float) cSeg;
 
						//glTexCoord2d(u, v);
						//glNormal3f(2 * x, 2 * y, 2 * z);
						//glVertex3d(2 * x, 2 * y, 2 * z);
						g_vertex_buffer_data.push_back(Vertex2(2*x, 2*y+2*c-2*r-8, 2*z, (float)t/**matrix->texture.getHeight()*//cSeg,(float)s/*matrix->texture.getWidth()*//rSeg));
					  }
					}
					//glEnd();
				  }
 
				  //glFrontFace(GL_CCW);
				

				// Give our vertices to OpenGL.
				glBufferData(GL_ARRAY_BUFFER, g_vertex_buffer_data.size() * sizeof(Vertex2), g_vertex_buffer_data.data(), GL_STATIC_DRAW);
				m_vertexBuffer = vertexbuffer;
				//matrix->m_colorVertexbuffer = colorVertexbuffer;
				m_size = g_vertex_buffer_data.size();
				m_changed = false;

				//vertexBuffers.push_back(std::pair<GLuint, GLuint>(vertexbuffer, g_vertex_buffer_data.size()));

				m_vertexBuffer = vertexbuffer;
				m_changed = false;
		}
#pragma endregion

#pragma region rendering2
		shader->Bind();
		shader->Update(MVP);//glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		GLint textureId = shader->getUniform(1);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture.getTextureId());
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(textureId, 0);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2), reinterpret_cast<void*>(offsetof(Vertex2, position)));//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position))); //0, position

		//glEnableVertexAttribArray(1);       ////normal-saker kan man skita i just nu
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(baseOffset + offsetof(Vertex, normal)));       ////normal-saker kan man skita i just nu

		//glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(1);
		//glBindBuffer(GL_ARRAY_BUFFER, mt->m_vertexBuffer);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2), reinterpret_cast<void*>(offsetof(Vertex2, UV)));//glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, color))); //1, färg

		glDrawArrays(GL_TRIANGLES, 0, m_size);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
#pragma endregion

		return true;
	}
	else return false;
}

ShaderType Torus::getShaderType() const
{
	return SHADER_SPACE;
}
