#include "Program.hpp"

int main(int argc, char *argv[]){
	FreeImage_Initialise();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(900, 900);
	glutInitContextVersion(4, 5);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow(argv[0]);
	glewExperimental = GL_TRUE;
	if (glewInit()){
		printf("Error");
		exit(-1);
	}
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutTimerFunc(0,timer,0);

	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMotionFunc(motion);
	glutMainLoop();
}