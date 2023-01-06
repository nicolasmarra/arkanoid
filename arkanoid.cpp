#include <iostream>
#include <GL/glut.h>
#include <math.h>

#define DEG2RAD 3.14159/180.0
#define nBricks 84

using namespace std;


struct Ball{
	// Coordonn�es du centre de la balle
	float x = 380, y = 420;

	// Dimensions de la balle
	float width = 10, height = 8;

};

struct Rect{
	// Coordonn�es du centre du rectangle
	float x = 380, y = 450;
	// Dimensions du rectangle
	float width = 150, height = 5;

};

struct Bricks{
	float x,y;
	bool isDestroyed = false;
};

Bricks bricks[nBricks];

Ball ball;
Rect rect;

void drawBall(){
	// D�finir la couleur de la balle (jaune)
	glColor3f(255, 255, 0);

	// Dessiner la balle quadrilat�re
	glBegin(GL_QUADS);
	glVertex2f(ball.x - ball.width / 2, ball.y - ball.height / 2);
	glVertex2f(ball.x + ball.width / 2, ball.y - ball.height / 2);
	glVertex2f(ball.x + ball.width / 2, ball.y + ball.height / 2);
	glVertex2f(ball.x - ball.width / 2, ball.y + ball.height / 2);
	glEnd();
}

void drawRect(){

	// D�finir la couleur du rectangle (bleu)
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
	// Coordonn�es du centre de la brique
	for(int i=0; i< nBricks; i++){
		bricks[i].x = posX;
		bricks[i].y = posY;

		posX+=50;
		if(posX > 650){
			posX = 100;
			posY+= 28;
		}
	}

	// D�finir la couleur de la balle (jaune)
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
	//glOrtho(0, 1000, 1000, 0, -1, 1); // d�finissez les propri�t�s de vue (vue en 2D)

    gluOrtho2D(0.0, 760.0, 480.0, 0.0);
}

int main(int argc, char **argv)
{

glutInit(&argc, argv);
glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

glutInitWindowPosition(200,50);
glutInitWindowSize(800,600);
glutCreateWindow ("ARKANOID");


glutDisplayFunc(display);

init();

glutMainLoop();

return 0;

}