#include <iostream>
#include <GL/glut.h>

#define DEG2RAD 3.14159/180.0
#define nBricks 84

using namespace std;


struct Ball{
	// Coordonn�es du centre de la balle
	float x = 380, y = 420;
	// Dimensions de la balle
	float width = 10, height = 8;
	//Vitesse de la balle
	float vX=0.03, vY = 0.06;
};

struct Paddle{
	// Coordonn�es du centre de la plateforme
	float x = 380, y = 450;
	// Dimensions de la plateforme
	float width = 100, height = 5;
};

struct Bricks{
	// Coordonn�es de la brique
	float x,y;
	// Dimensions de la brique
	float width=45,height=10;
	// �tat de la brique
	bool isDestroyed = false;
};

Bricks bricks[nBricks];
Ball ball;
Paddle Paddle;
int score=0,roundCurrent=1;
int mouseX, mouseY;
bool win=false,lost=false,start=false;

void drawBall(){
	// Appliquer la couleur de la balle (jaune)
	glColor3f(255, 255, 0);

	// Cr�er la balle quadrilat�re
	glBegin(GL_QUADS);
	glVertex2f(ball.x - ball.width / 2, ball.y - ball.height / 2);
	glVertex2f(ball.x + ball.width / 2, ball.y - ball.height / 2);
	glVertex2f(ball.x + ball.width / 2, ball.y + ball.height / 2);
	glVertex2f(ball.x - ball.width / 2, ball.y + ball.height / 2);
	glEnd();
}

void drawPaddle(){

	// Appliquer la couleur de la plateforme (bleu)
	glColor3f(0, 0, 255);

	// Cr�er la plateforme
	glBegin(GL_QUADS);

	glVertex2f(Paddle.x - Paddle.width / 2, Paddle.y - Paddle.height / 2);
	glVertex2f(Paddle.x + Paddle.width / 2, Paddle.y - Paddle.height / 2);
	glVertex2f(Paddle.x + Paddle.width / 2, Paddle.y + Paddle.height / 2);
	glVertex2f(Paddle.x - Paddle.width / 2, Paddle.y + Paddle.height / 2);
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

	// Appliquer la couleur de la brique (vert)
	glColor3f(0, 128, 0);
	glBegin(GL_QUADS);

	for(int i=0; i< nBricks; i++){

		if(!bricks[i].isDestroyed){
			glVertex2f(bricks[i].x - bricks[i].width/2, bricks[i].y - bricks[i].height/2);
			glVertex2f(bricks[i].x + bricks[i].width/2, bricks[i].y - bricks[i].height/2);
			glVertex2f(bricks[i].x + bricks[i].width/2, bricks[i].y + bricks[i].height/2);
			glVertex2f(bricks[i].x - bricks[i].width/2, bricks[i].y + bricks[i].height/2);
		}
	}

	glEnd();
}

bool checkCollisionBrick() {
  // Parcourir chaque brique
  for (int i = 0; i < nBricks; i++) {
    // V�rifier l'�tat de la brique, si elle est d�truite, on passe � la prochaine it�ration
	  	if(bricks[i].isDestroyed) continue;
	    // V�rifier si la balle entre en collision avec la brique � la position i

	  	float bx1 = ball.x - ball.width / 2;
	  	float bx2 = ball.x + ball.width / 2;
	    float by1 = ball.y - ball.height / 2;
	    float by2 = ball.y + ball.height / 2;

	    // Calculer des coordonn�es des coins de la brique � la position 1
	    float brx1 = bricks[i].x - bricks[i].width / 2;
	    float brx2 = bricks[i].x + bricks[i].width / 2;
	    float bry1 = bricks[i].y - bricks[i].height / 2;
	    float bry2 = bricks[i].y + bricks[i].height / 2;

	    // V�rifier s'il y a eu une collision
	    if (bx1 > brx2 || bx2 < brx1 || by1 > bry2 || by2 < bry1)
	    continue; // Pas de collision, on passe � la prochaine it�ration

	    // Il y a eu une collision, donc true
	    bricks[i].isDestroyed = true;
	    return true;
    }
  	  return false;
}


bool checkCollisionPaddle() {
	 // Calculer les coordonn�es des coins de la balle
	  float bx1 = ball.x - ball.width / 2;
	  float bx2 = ball.x + ball.width / 2;
	  float by1 = ball.y - ball.height / 2;
	  float by2 = ball.y + ball.height / 2;

	  // Calculer des coordonn�es des coins de la plateforme
	  float rx1 = Paddle.x - Paddle.width / 2;
	  float rx2 = Paddle.x + Paddle.width / 2;
	  float ry1 = Paddle.y - Paddle.height / 2;
	  float ry2 = Paddle.y + Paddle.height / 2;

	  // V�rifier s'il y a eu une collision
	  if (bx1 > rx2 || bx2 < rx1 || by1 > ry2 || by2 < ry1) {
	    return false; // Pas de collision
	  }
	  return true; // Collision d�tect�e

}


bool isWin(){
	for(int i=0; i< nBricks; i++){
		if(!bricks[i].isDestroyed)
			return false;
	}
	return true;
}

void onWinGame(){
	ball.x = 380;
	ball.y = 420;
	ball.vX = 0;
	ball.vY = 0;

	Paddle.x = 380;
	Paddle.y = 450;

	float posX=100, posY=80;
	// Coordonn�es du centre de la brique
	for(int i=0; i< nBricks; i++){
		bricks[i].x = posX;
		bricks[i].y = posY;
		bricks[i].isDestroyed = false;
		posX+=50;
		if(posX > 650){
			posX = 100;
			posY+= 28;
			}
		}
	roundCurrent++;
	win=true;
}

void endGame(){
	ball.x = 380;
	ball.y = 420;
	ball.vX = 0;
	ball.vY = 0;

	Paddle.x = 380;
	Paddle.y = 450;

	score=0;
	roundCurrent=1;
	float posX=100, posY=80;
	// Coordonn�es du centre de la brique
	for(int i=0; i< nBricks; i++){
		bricks[i].x = posX;
		bricks[i].y = posY;
		bricks[i].isDestroyed = false;
		posX+=50;
		if(posX > 650){
			posX = 100;
			posY+= 28;
		}
	}
	lost=true;
}

void onBallMove(){

	ball.x += ball.vX;

	//V�rifier s'il y a une collision entre la plateforme et la balle
	if(checkCollisionPaddle()){
		ball.vY = -ball.vY;
	}

	//V�rifier s'il y a une collision entre une brique  et la balle
	if(checkCollisionBrick()){
		ball.vX = -ball.vX;
		score+= 5;
	}

	ball.y -= ball.vY;
	if(checkCollisionBrick()){
		ball.vY = -ball.vY;
		score+= 5;
	}

	// Gestion des rebonds de la balle sur les bords de l'�cran
	if(ball.x-ball.width < 0 || ball.x+ball.width > 775)
		ball.vX = -ball.vX;

	if(ball.y < 0)
		ball.vY = -ball.vY;

	if(ball.y + ball.width > 500){

	//GAMEOVER

	endGame();

	}
	//V�rifier s'il y a une une victoire
	if(isWin())
		onWinGame();
    glutSwapBuffers();
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
  if (key == ' ') {
	  if(ball.vX <= 0 && ball.vY <= 0)
	  {
		  ball.vX = 0.03*roundCurrent;
	      ball.vY = 0.06*roundCurrent;
	  }
	  start=true;
	  win=false;
	  lost=false;
	  glutIdleFunc(onBallMove);

  }
}

void onMouseMove(int x, int y)
{
    //calculer le d�placement de la souris par rapport � la position pr�c�dente
    int dx = x - mouseX;

    //nouvelle position de la souris
    mouseX = x;

    //appliquer le d�placement � la plateforme
    Paddle.x += dx;
    if(Paddle.x+Paddle.width > 830) Paddle.x  = 830 - Paddle.width;
    else if(Paddle.x-Paddle.width < -50) Paddle.x = -50 + Paddle.width;
}

void onMouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // Enregistrer la position de la souris
        mouseX = x;
        mouseY = y;
    }
}
void showText(){

	// d�finir la couleur du texte
	glColor3f(255, 255, 255);

	//d�finir la position du texte
    glRasterPos2f(75, 30);

    // afficher le texte
    char scoreText[32];
    sprintf(scoreText, "Score: %d", score);
	int len = strlen(scoreText);
	for (int i = 0; i < len; i++)
	{
	    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, scoreText[i]);
	}

	// d�finir la couleur du texte
	glColor3f(1.0, 1.0, 1.0);

	//d�finir la position du texte
	glRasterPos2f(580, 30);

	// afficher le texte
	char roundCurrentText[32];
	sprintf(roundCurrentText, "Round: %d",roundCurrent);
	int len1 = strlen(roundCurrentText);
	for (int i = 0; i < len1; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, roundCurrentText[i]);
	}
}


void showTextWinLost(const char*text, int pos){
	// d�finir la couleur du texte
	glColor3f(255, 255, 255);

	 // d�finir la position du texte
	 glRasterPos2f(pos, 350);

	 // afficher le texte
	 int len = strlen(text);
	 for (int i = 0; i < len; i++)
	 {
	    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	 }

}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 0.0, 0.0);
    drawBall();
    drawPaddle();
    drawBrick();
    showText();

    if(!start)
    	showTextWinLost("Appuyez sur la barre d'espace pour commencer!",180);

    if(win)
    	showTextWinLost("Bien jou�! Vous avez gagn�,Appuyez sur la barre d'espace pour continuer!",40);
    else if(lost)
    	showTextWinLost("Vous avez perdu!Appuyez sur la barre d'espace pour recommencer!",80);


    glutSwapBuffers();
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0); // black backgroundCurrent
	glMatrixMode(GL_PROJECTION); // setup viewing projection
	glLoadIdentity(); // start with identity matrix
	glOrtho(0.0, 780, 500, 0.0, -1.0, 1.0); // d�finissez les propri�t�s de vue (vue en 2D)
}


int main(int argc, char **argv)
{
	// Initialisation de FreeGLUT
	glutInit(&argc, argv);

	// d�finir le mode d'affichage
	glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	// d�finir la position de la fen�tre
	glutInitWindowPosition(200,50);

	// d�finir la taille de la fen�tre
	glutInitWindowSize(800,600);

	//cr�ation de la fen�tre
	glutCreateWindow ("ARKANOID");

	//d�finition des fonctions pour le mouvement de la souris et les clics de souris
	glutMotionFunc(onMouseMove);
	glutMouseFunc(onMouseClick);

	//d�finition de la fonction de gestion des �v�nements du clavier
	glutKeyboardFunc(keyboard);

	glutDisplayFunc(display);
    init();

	glutMainLoop(); // Lancement de la boucle d'�v�nements

	return 0;

}
