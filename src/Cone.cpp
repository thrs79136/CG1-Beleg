#include "Cone.hpp"
#include "Data.hpp"
#include <iostream>
using namespace std;

void generateCone(float height, float radius){
	GLfloat vertices[NumVertices*6][6];
	/*
		top coordinate
		v_1
		v_2
		top coordinate
		v_2
		v_3
	*/

	// Festlegen der Koordinaten der Spitze und des Mittelpunkts der Grundflaeche
	float z = -0.5f+height;
	for (int i=0; i<NumVertices*6; i+=3){
		if (i==NumVertices*3) z = -0.5f;
		vertices[i][0] = 0.0f;
		vertices[i][1] = 0.0f;
		vertices[i][2] = z;
	}

	for (int deg = 0; deg<360; deg+=360/NumVertices){
		int i = deg/(360/NumVertices)*3+1;
		float x = sin((float)deg*M_PI/180.0) * radius;
		float y = cos((float)deg*M_PI/180.0) * radius;
		vertices[NumVertices*3+i][0] = vertices[i][0] = x;
		vertices[NumVertices*3+i][1] = vertices[i][1] = y;
		vertices[NumVertices*3+i][2] = vertices[i][2] = -0.5f;
		if (i-2 >= 0) i = i-2;
		else i = NumVertices*3-1;
		vertices[NumVertices*3+i][0] = vertices[i][0] = x;
		vertices[NumVertices*3+i][1] = vertices[i][1] = y;
		vertices[NumVertices*3+i][2] = vertices[i][2] = -0.5f;
	}

	float coneTexVertices[NumVertices*6][2];
	calcConeTexCoords(height, radius, coneTexVertices);

	float sign = 1.0f;
	// Normalvektoren
	for (int i = 0; i<NumVertices*6; i+=3){
		// (v3-v1)x(v2-v1)
		if (i==NumVertices*3) sign = -1.0f;
		vec3 normalVector = cross(vec3(vertices[i+2][0], vertices[i+2][1], vertices[i+2][2])-vec3(vertices[i][0], vertices[i][1], vertices[i][2]),
			vec3(vertices[i+1][0], vertices[i+1][1], vertices[i+1][2])-vec3(vertices[i][0], vertices[i][1], vertices[i][2]));
		for (int j=i; j<i+3; j++){
			vertices[j][3] = normalVector[0];
			vertices[j][4] = normalVector[1];
			// Normalvektoren der Grundflaeche sind nach unten gerichtet
			vertices[j][5] = sign*normalVector[2];
		}
	}

	glBindVertexArray(VAOs[Cone]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[ConeVBO]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(coneTexVertices), vertices, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(coneTexVertices), *coneTexVertices);
	glBindVertexArray(VAOs[Cone]);
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), NULL);
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(vTexture, 2, GL_FLOAT, GL_FALSE, 0, (void*)sizeof(vertices));
	glEnableVertexAttribArray(vPosition);
	glEnableVertexAttribArray(vNormal);
	glEnableVertexAttribArray(vTexture);
}

void drawCone(int texID){
	glBindTexture(GL_TEXTURE_2D, texID);
	glBindVertexArray(VAOs[Cone]);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices*6);
}

void calcConeTexCoords(float h, float r, float vertices[][2]){

	int n = NumVertices;

	// alle Angaben im Bogenmass
	float alpha = 2*M_PI/(float)n;
	float s=sqrt(r*r+h*h);
    float a = sqrt((1-cos(alpha))*2*r*r);
	float gamma = acos(1-(a*a/(2*s*s)));

	float factor = 1/(2*s);
	r*=factor;

	for (int i=0; i<=n; i++){
		// Mantelflaeche
		float deg1 = gamma*(float)i;
		float x1 = 0.5 + sin(deg1)*0.5f;
		float y1 = 0.5 + cos(deg1)*0.5f; 
		
		float deg2 = alpha*(float)i;
		float x2 = 0.5 + sin(deg2) * r;
		float y2 = 0.5 + cos(deg2) * r;

		if (i*3<n*3){
			vertices[i*3+1][0] = x1;
			vertices[i*3+1][1] = y1;
			// Mittelpunkt
			vertices[i*3][0] = 0.5;
			vertices[i*3][1] = 0.5;
			
			vertices[i*3+3*n+1][0] = x2;
			vertices[i*3+3*n+1][1] = y2;
			//Mittelpunkt
			vertices[i*3+3*n][0] = 0.5;
			vertices[i*3+3*n][1] = 0.5;
		}
		if (i*3>=0){
			vertices[i*3-1][0] = x1;
			vertices[i*3-1][1] = y1;

			vertices[i*3+3*n-1][0] = x2;
			vertices[i*3+3*n-1][1] = y2;
		}
	}
}