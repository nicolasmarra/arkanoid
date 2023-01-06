#include <iostream>
#include <GL/glut.h>
#include <math.h>

#define DEG2RAD 3.14159/180.0
#define nBricks 84

using namespace std;


struct Ball{
	// Coordonnées du centre de la balle
	float x = 380, y = 420;

	// Dimensions de la balle
	float width = 10, height = 8;

};

struct Rect{
	// Coordonnées du centre du rectangle
	float x = 380, y = 450;
	// Dimensions du rectangle
	float width = 100, height = 5;

};

struct Bricks{
	float x,y;
	bool isDestroyed = false;
};

Bricks bricks[nBricks];

Ball ball;
Rect rect;

void drawBall(){
	// Définir la couleur de la balle (jaune)
	glColor3f(255, 255, 0);

	// Dessiner la balle quadrilatère
	glBegin(GL_QUADS);
	glVertex2f(ball.x - ball.width / 2, ball.y - ball.height / 2);
	glVertex2f(ball.x + ball.width / 2, ball.y - ball.height / 2);
	glVertex2f(ball.x + ball.width / 2, ball.y + ball.height / 2);
	glVertex2f(ball.x - ball.width / 2, ball.y + ball.height / 2);
	glEnd();
}

void drawRect(){

	// Définir la couleur du rectangle (bleu)
	glColor3f(0, 0, 255);

	// Dessiner le rectangle
	glBegin(GL_QUADS);

	glVertex2f(rect.x - rect.width / 2, rect.y - rect.height / 2);
	glVertex2f(rect.x + rect.width / 2, rect.y - rect.height / 2);
	glVertex2f(rect.x + rect.width / 2, rect.y + rect.height / 2);
	glVertex2f(rect.x - rect.width / 2, rect.y + rect.height / 2);
	glEnd();
}

void drawBrick(){

	float posX=100, posY=80;
	// Coordonnées du centre de la brique
	for(int i=0; i< nBricks; i++){
		bricks[i].x = posX;
		bricks[i].y = posY;

		posX+=50;
		if(posX > 650){
			posX = 100;
			posY+= 28;
		}
	}

	// Définir la couleur de la balle (jaune)
	glColor3f(0, 128, 0);
	glBegin(GL_QUADS);

	for(int i=0; i< nBricks; i++){

		if(!bricks[i].isDestroyed){
			glVertex2f(bricks[i].x - 45/2, bricks[i].y - 10/2);
			glVertex2f(bricks[i].x + 45/2, bricks[i].y - 10/2);
			glVertex2f(bricks[i].x + 45/2, bricks[i].y + 10/2);
			glVertex2f(bricks[i].x - 45/2, bricks[i].y + 10/2);

		}

	}

	glEnd();

}

// Fonction de gestion des événements du clavier
/*
void keyboard(int key, int x, int y){
    switch(key){
        case GLUT_KEY_LEFT:
            barX -= 10;
            if(barX < 0){
                barX = 0;
            }
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            barX += 10;
            if(barX+barWidth > 480){
                barX = 480-barWidth;
            }
            glutPostRedisplay();
            break;
        default:
            break;
    }
}
*/

void myKeyboard(int key, int x, int y){
	// Traitement à effectuer lorsque la touche est enfoncée
	switch(key)
	{
			case GLUT_KEY_RIGHT:
		        rect.x += 15;
		        if(rect.x+rect.width > 810) rect.x  = 810 - rect.width;
		        break;
			case GLUT_KEY_LEFT:
				rect.x -= 15;
	            if(rect.x-rect.width < -50) rect.x = -50 + rect.width;
	            break;
	        default:
	        	break;
	}

	glutPostRedisplay(); // On demande un rafraîchissement de l'affichage

}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 0.0, 0.0);

    drawBall();
    drawRect();
    drawBrick();
    glutSwapBuffers();
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0); // black background
	glMatrixMode(GL_PROJECTION); // setup viewing projection
	glLoadIdentity(); // start with identity matrix
	//glOrtho(0, 1000, 1000, 0, -1, 1); // définissez les propriétés de vue (vue en 2D)

    gluOrtho2D(0.0, 760.0, 480.0, 0.0);
}

int main(int argc, char **argv)
{

	// Initialisation de FreeGLUT
	glutInit(&argc, argv);

	glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(200,50);
	glutInitWindowSize(800,600);
	glutCreateWindow ("ARKANOID");

	// Définition de la fonction de gestion des événements du clavier
	//glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(myKeyboard);

	glutDisplayFunc(display);

	init();



	glutMainLoop(); // Lancement de la boucle d'événements

	return 0;

}
