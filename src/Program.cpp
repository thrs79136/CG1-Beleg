#include "Program.hpp"
#include "LoadShader.hpp"
#include "Cone.hpp"
#include "Cube.hpp"
#include "Data.hpp"

GLuint program;

// Shader-Variablen
GLuint ModelViewProjectionLoc;
GLuint ModelLoc;
GLuint ViewLoc;
GLuint ProjectionLoc;
GLuint NormalMatrixLoc;

GLuint lightPosLoc;
GLuint lightColorLoc;
GLuint lightDirLoc;
GLuint isLightSourceLoc;
GLuint useSpecularLightLoc;
GLuint viewPosLoc;
int displayLightLoc;
int displayLight[numLights] = {1,1,1,1};

// Texturen
GLuint texIDs[numTextures];

// Rotation, Verschiebung, etc.
GLint width=900, height=900;
mat4 Model = mat4(1.0);
mat4 View = mat4(1.0);
mat4 Projection = mat4(1.0);
mat4 ModelViewProjection = mat4(1.0);
GLfloat alpha =0.2, beta=0.8, dist=5, DELTA=0.5;

unsigned int VAOs[NumVAOs];
unsigned int VBOs[NumVBOs];
unsigned int Buffers[NumBuffers];

void renderScene()
{	
	#ifdef linux
	struct timeval now;
	gettimeofday(&now, NULL);
	long angle = ((now.tv_sec)*1000 + now.tv_usec/1000)/10%360;
	#endif
	#ifdef _WIN32
	#endif

	// Berechnung der von der Zeit abhaengigen Position
	float deg = (float)angle/180*(float)M_PI;
	float x = sin(deg)*(1.025-0.35*sin(2*deg));
	float y = cos(deg)*(1.025-0.35*sin(2*deg));

	vec3 conePositions[4];
	conePositions[0] = vec3(x,0,-y);
	conePositions[1] = vec3(y,0,x);
	conePositions[2] = vec3(-x,0,y);
	conePositions[3] = vec3(-y,0,-x);

	// Kegel
	glUniform1iv(displayLightLoc, numLights, displayLight);
	glUniform1i(useSpecularLightLoc, 0);
	for (int i=0; i<4; i++){
		glUniform1i(useSpecularLightLoc, i%2);
		Model = mat4(1.0f);
		Model = translate(Model, conePositions[i]);
		Model = rotate(Model, -(float)(deg + i*0.5*M_PI), vec3(0, 1, 0));
		ModelViewProjection = Projection*View*Model;
		glUniformMatrix4fv(ModelViewProjectionLoc, 1, GL_FALSE, &ModelViewProjection[0][0]);
		glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, &Model[0][0]);
		glUniformMatrix4fv(NormalMatrixLoc, 1, GL_FALSE, &mat4(transpose(inverse(Model*View)))[0][0]);
		drawCone(texIDs[i%2]);
	}

	const static vec3 midpoints[] = {
		vec3(1.5,0,0),
		vec3(0,0,-1.5),
		vec3(-1.5,0,0),
		vec3(0,0,1.5),
	};
	vec3 lightPositions[4];
	
	float x2 = sin(deg)*1.5;
	float y2 = cos(deg)*1.5;
	float x3 = sin(deg+M_PI/2.0)*1.5;
	float y3 = cos(deg+M_PI/2.0)*1.5;
	float x4 = sin(deg+M_PI)*1.5;
	float y4 = cos(deg+M_PI)*1.5;
	float x5 = sin(deg-M_PI/2.0)*1.5;
	float y5 = cos(deg-M_PI/2.0)*1.5;
	lightPositions[0] = midpoints[0] + vec3(-x2,y2,0);
	lightPositions[1] = midpoints[1] + vec3(0,y3,x3);
	lightPositions[2] = midpoints[2] + vec3(x4,y4,0);
	lightPositions[3] = midpoints[3] + vec3(0,y5,-x5);
	glUniform3fv(lightPosLoc, 4, value_ptr(lightPositions[0]));

	for (int i=0; i<numLights; i++){
		if (displayLight[i]){
			glUniform1i(isLightSourceLoc, i+1);
			Model = mat4(1.0f);
			Model = translate(Model, lightPositions[i]);
			Model = scale(Model, vec3(0.25));
			ModelViewProjection = Projection*View*Model;
			glUniformMatrix4fv(ModelViewProjectionLoc, 1, GL_FALSE, &ModelViewProjection[0][0]);
			glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, &Model[0][0]);
			glUniformMatrix4fv(NormalMatrixLoc, 1, GL_FALSE, &mat4(transpose(inverse(View*Model)))[0][0]);
			drawCube(0);
		}
	}
	glUniform1i(isLightSourceLoc, 0);
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// unten links
	vec3 viewpoint = vec3(0.15,-0.25,0.25);
	View = lookAt(	viewpoint,
					vec3(0.0, 0.0, 0.0),
					vec3(0.0, 0.7, 0.0));
	//Projection = perspective(300.0f, 1.0f, 0.1f, 100.0f);
	Projection = ortho(-3.5f,3.5f,-3.5f,3.5f,-3.5f,3.5f);
	glViewport(0,0,width/2, height/2);
	glUniform3fv(viewPosLoc, 1, &viewpoint[0]);
	renderScene();

	// unten rechts
	viewpoint = vec3(-3.0,0.1,-3.0);
	Projection = perspective(45.0f, 1.0f, 0.1f, 100.f);	
	View = lookAt(	viewpoint,
					vec3(0.0, 0.0, 0.0),
					vec3(0.0, 0.7, 0.0));
	glViewport(width/2, 0, width/2, height/2);
	glUniform3fv(viewPosLoc, 1, &viewpoint[0]);
	renderScene();

	// oben lins
	setViewPoint();
	glViewport(0, height/2, width/2, height/2);
	renderScene();

	// oben rechts
	Projection = perspective(45.0f, 1.0f, 0.1f, 100.f);	
	viewpoint = vec3(0.1, 3.0, 0.1);
	View = mat4(1.0);
	View = lookAt(	viewpoint,
					vec3(0.0, 0.0, 0.0),
					vec3(0.0, 0.7, 0.0));
	glViewport(width/2, height/2, width/2, height/2);
	glUniform3fv(viewPosLoc, 1, &viewpoint[0]);
	renderScene();

	glViewport(0,0,width,height);

	glFlush();
}

void init(){   
	printf("\n%s", (char*)glGetString(GL_RENDERER));
	printf("\n%s", (char*)glGetString(GL_VERSION));
	printf("\n%s\n", (char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
	program = loadShaders("/home/theresa/openglbeleg/include/main.vs", "/home/theresa/openglbeleg/include/main.fs");
	glUseProgram(program);
    // VAO-, VBO-, Buffer- und Textur-IDs erzeugen
    glGenVertexArrays(NumVAOs, VAOs);
	glGenBuffers(NumVBOs, VBOs);
	glGenBuffers(NumBuffers, Buffers);
    glGenTextures(numTextures, texIDs);

    // Texturen laden
	loadTextures();

    // Positionen der Shader-Variablen ermitteln
	ModelViewProjectionLoc = glGetUniformLocation(program, "ModelViewProjection");
    ModelLoc = glGetUniformLocation(program, "Model");
	ViewLoc = glGetUniformLocation(program, "View");
	ProjectionLoc = glGetUniformLocation(program, "Projection");
	NormalMatrixLoc = glGetUniformLocation(program, "NormalMatrix");
    lightPosLoc = glGetUniformLocation(program, "lightPos");
    lightColorLoc = glGetUniformLocation(program, "lightColor");
	lightDirLoc = glGetUniformLocation(program, "lightDir");
    isLightSourceLoc = glGetUniformLocation(program, "isLightSource");
	useSpecularLightLoc = glGetUniformLocation(program, "useSpecularLight");
	displayLightLoc = glGetUniformLocation(program, "displayLight");
	viewPosLoc = glGetUniformLocation(program, "viewPos");

	// Richtung des Richtungslichts
	glUniform3f(lightDirLoc, -1, -1, 1);

	// Festlegen der Projektionsmatrix
	Projection = perspective(45.0f, 1.0f, 0.1f, 100.f);

	// Farben der Punktlichte
	static vec3 lightColors[] = {
		vec3(0.0, 0.0, 1.0), //blau
		vec3(1.0, 0.5, 0.0), //orange
		vec3(1.0, 1.0, 0.0), //gelb
		vec3(1.0, 0.0, 0.0), //rot
		vec3(1.0, 1.0, 1.0), // weiss (Richtungslicht)
	};
    glUniform3fv(lightColorLoc, 5, value_ptr(lightColors[0]));
	
    // Objekte erzeugen
	generateCube();
	generateCone();

	glEnable(GL_DEPTH_TEST);
}

void loadTextures() {
	for (int i=0; i<numTextures; i++){
		FREE_IMAGE_FORMAT fif=FreeImage_GetFileType(texturePaths[i].c_str(),0);
		FIBITMAP *bitmap=FreeImage_Load(fif,texturePaths[i].c_str());
		FIBITMAP *bitmap2 = FreeImage_ConvertTo32Bits(bitmap);
		FreeImage_Unload(bitmap);
		int width = FreeImage_GetWidth(bitmap2);
		int height = FreeImage_GetHeight(bitmap2);
		FREE_IMAGE_COLOR_TYPE colorType = FreeImage_GetColorType(bitmap2);
		glBindTexture(GL_TEXTURE_2D,texIDs[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D,0, GL_RGBA,width,height,0,GL_BGRA, GL_UNSIGNED_BYTE,(void*)(FreeImage_GetBits(bitmap2)));
		FreeImage_Unload(bitmap2);
	}
}

void setViewPoint(){
	static GLfloat viewpoint[3];
	viewpoint[0] = dist * sin(beta) * sin(alpha);
	viewpoint[1] = dist * cos(beta);
	viewpoint[2] = dist * sin(beta) * cos(alpha);
	
	View = glm::lookAt(glm::vec3(viewpoint[0], viewpoint[1], viewpoint[2]),
	glm::vec3(0, 0, 0), glm::vec3(0.0, cos(beta - 3.141593 * 0.5), 0.0));
    glUniform3f(viewPosLoc, viewpoint[0], viewpoint[1], viewpoint[2]);
}

void reshape(int w, int h) {
	width = w;
	height = h;
}

void timer(int value) {
	//increment();
	glutPostRedisplay();
	glutTimerFunc(10, timer, 0);
}

void keyboard(unsigned char theKey, int mouseX, int mouseY) {
	switch (theKey) {
	case 'V':
	case 'v': dist -= DELTA; 
			if (dist<=0) dist=0.1;
			break;
	case 'Z':
	case 'z': dist += DELTA;; break;
	case 'B':
	case 'b': displayLight[0]^=1; break;
	case 'O':
	case 'o': displayLight[1]^=1; break;
	case 'G':
	case 'g': displayLight[2]^=1; break;
	case 'R':
	case 'r': displayLight[3]^=1; break;
	case 'E':
	case 'e': exit(0);
	}
}

void special(int specKey, int mouseX, int mouseY) {
	switch (specKey) {
	case GLUT_KEY_LEFT: alpha -= DELTA; break;
	case GLUT_KEY_RIGHT: alpha += DELTA; break;
	case GLUT_KEY_UP: beta -= DELTA; break;
	case GLUT_KEY_DOWN: beta += DELTA; break;
	}
}

void motion(int mouseX, int mouseY) {
	if (mouseX < (width / 2)) { alpha -= (mouseX - (width / 2)) / 10000.0; }
	else { alpha -= (mouseX - (width / 2)) / 10000.0; }
	if (mouseY < (height / 2)) { beta -= (mouseY - (height / 2)) / 10000.0; }
	else { beta -= (mouseY - (height / 2)) / 10000.0; }
}