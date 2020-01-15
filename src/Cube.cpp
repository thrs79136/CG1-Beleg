#include "Cube.hpp"
#include "Data.hpp"

/*unsigned int VAOs[NumVAOs];
unsigned int VBOs[NumVBOs];
unsigned int Buffers[NumBuffers];
*/
int NumVertices = 180;

void generateCube() {
	static const GLfloat cube_positions[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

	float texPos[36][2];
	for (int i=0; i<36; i+=6){
		// x-Werte
		texPos[i][0] = texPos[i+5][0] = texPos[i+4][0] = 0;
		texPos[i+1][0] = texPos[i+2][0] = texPos[i+3][0] = 1;
		// y-Werte
		texPos[i][1] = texPos[i+1][1] = texPos[i+5][1] = 0;
		texPos[i+2][1] = texPos[i+3][1] = texPos[i+4][1] = 1;
	}

	glBindVertexArray(VAOs[Cube]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[CubeVBO]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_positions) + sizeof(texPos), cube_positions, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(cube_positions), sizeof(texPos), texPos);
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), NULL);
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(vTexture, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(cube_positions)));
	glEnableVertexAttribArray(vPosition);
	glEnableVertexAttribArray(vNormal);
	glEnableVertexAttribArray(vTexture);
}

void drawCube(int texID){
	glBindTexture(GL_TEXTURE_2D, texID);
	glBindVertexArray(VAOs[Cube]);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}