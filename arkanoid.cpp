#include <iostream>
#include <GL/glut.h>

#define DEG2RAD 3.14159/180.0
#define nBricks 84

using namespace std;


struct Ball{
	// Coordonnées du centre de la balle
	float x = 380, y = 420;
	// Dimensions de la balle
	float width = 10, height = 8;
	//Vitesse de la balle
	float vX=0.03, vY = 0.06;
};

struct Paddle{
	// Coordonnées du centre de la plateforme
	float x = 380, y = 450;
	// Dimensions de la plateforme
	float width = 100, height = 5;
};

struct Bricks{
	// Coordonnées de la brique
	float x,y;
	// Dimensions de la brique
	float width=45,height=10;
	// état de la brique
	bool isDestroyed = false;
};

Bricks bricks[nBricks];

Ball ball;
Paddle Paddle;

int score=0,round=1;

void drawBall(){
	// Appliquer la couleur de la balle (jaune)
	glColor3f(255, 255, 0);

	// Créer la balle quadrilatère
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

	// Créer la plateforme
	glBegin(GL_QUADS);

	glVertex2f(Paddle.x - Paddle.width / 2, Paddle.y - Paddle.height / 2);
	glVertex2f(Paddle.x + Paddle.width / 2, Paddle.y - Paddle.height / 2);
	glVertex2f(Paddle.x + Paddle.width / 2, Paddle.y + Paddle.height / 2);
	glVertex2f(Paddle.x - Paddle.width / 2, Paddle.y + Paddle.height / 2);
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

// Fonction de gestion des événements du clavier
void keyPress(int key, int x, int y){
	// Traitement à effectuer lorsque la touche est enfoncée
	switch(key)
	{
			case GLUT_KEY_RIGHT:
		        Paddle.x += 15;
		        if(Paddle.x+Paddle.width > 830) Paddle.x  = 830 - Paddle.width;
		        break;
			case GLUT_KEY_LEFT:
				Paddle.x -= 15;
	            if(Paddle.x-Paddle.width < -50) Paddle.x = -50 + Paddle.width;
	            break;
	        default:
	        	break;
	}

	glutPostRedisplay(); // On demande un rafraîchissement de l'affichage

}

/*
bool checkCollisionBrick() {
  // Parcourir chaque brique
  for (int i = 0; i < nBricks; i++) {
    // Vérifier l'état de la brique, si elle est détruite, on passe à la prochaine itération
	  	if(bricks[i].isDestroyed) continue;
	    // Vérifier si la balle entre en collision avec la brique à la position i
	  	if (ball.x + ball.width > bricks[i].x &&
        ball.x < bricks[i].x + bricks[i].width &&
        ball.y + ball.width > bricks[i].y &&
        ball.y < bricks[i].y + bricks[i].height) {
	  	// Il y a collision, donc la brique a été détruite et retourne true
	  		bricks[i].isDestroyed = true;
	  		return true;
    }
  }

  // Il n'y a pas eu de collision, donc false
  return false;
}*/

bool checkCollisionBrick() {
  // Parcourir chaque brique
  for (int i = 0; i < nBricks; i++) {
    // Vérifier l'état de la brique, si elle est détruite, on passe à la prochaine itération
	  	if(bricks[i].isDestroyed) continue;
	    // Vérifier si la balle entre en collision avec la brique à la position i

	  	float bx1 = ball.x - ball.width / 2;
	  	float bx2 = ball.x + ball.width / 2;
	    float by1 = ball.y - ball.height / 2;
	    float by2 = ball.y + ball.height / 2;

	    // Calculer des coordonnées des coins de la brique à la position 1
	    float brx1 = bricks[i].x - bricks[i].width / 2;
	    float brx2 = bricks[i].x + bricks[i].width / 2;
	    float bry1 = bricks[i].y - bricks[i].height / 2;
	    float bry2 = bricks[i].y + bricks[i].height / 2;

	    // Vérifier s'il y a eu une collision
	    if (bx1 > brx2 || bx2 < brx1 || by1 > bry2 || by2 < bry1)
	    continue; // Pas de collision, on passe à la prochaine itération

	    // Il y a eu une collision, donc true
	    bricks[i].isDestroyed = true;
	    return true;
    }
  	  return false;
}


bool checkCollisionPaddle() {
	 // Calculer les coordonnées des coins de la balle
	  float bx1 = ball.x - ball.width / 2;
	  float bx2 = ball.x + ball.width / 2;
	  float by1 = ball.y - ball.height / 2;
	  float by2 = ball.y + ball.height / 2;

	  // Calculer des coordonnées des coins de la plateforme
	  float rx1 = Paddle.x - Paddle.width / 2;
	  float rx2 = Paddle.x + Paddle.width / 2;
	  float ry1 = Paddle.y - Paddle.height / 2;
	  float ry2 = Paddle.y + Paddle.height / 2;

	  // Vérifier s'il y a eu une collision
	  if (bx1 > rx2 || bx2 < rx1 || by1 > ry2 || by2 < ry1) {
	    return false; // Pas de collision
	  }
	  return true; // Collision détectée

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
	// Coordonnées du centre de la brique
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
	round++;
}

void endGame(){
	ball.x = 380;
	ball.y = 420;
	ball.vX = 0;
	ball.vY = 0;

	Paddle.x = 380;
	Paddle.y = 450;

	score=0;
	round=1;
	float posX=100, posY=80;
	// Coordonnées du centre de la brique
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

}

void onBallMove(){

	ball.x += ball.vX;

	//Vérifier s'il y a une collision entre la plateforme et la balle
	if(checkCollisionPaddle()){
		ball.vY = -ball.vY;
	}

	//Vérifier s'il y a une collision entre une brique  et la balle
	if(checkCollisionBrick()){
		ball.vX = -ball.vX;
		score+= 5;
	}

	ball.y -= ball.vY;
	if(checkCollisionBrick()){
		ball.vY = -ball.vY;
		score+= 5;
	}

	// Gestion des rebonds de la balle sur les bords de l'écran
	if(ball.x-ball.width < 0 || ball.x+ball.width > 775)
		ball.vX = -ball.vX;

	if(ball.y < 0)
		ball.vY = -ball.vY;

	if(ball.y + ball.width > 500){

	//GAMEOVER

	endGame();

	}
	//Vérifier s'il y a une une victoire
	if(isWin())
		onWinGame();
    glutSwapBuffers();
	glutPostRedisplay();
}

void mouseEvent(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
    	if(ball.vX <= 0 && ball.vY <= 0){
    		ball.vX = 0.03*round;
    		ball.vY = 0.06*round;
    	}
        glutIdleFunc(onBallMove);
    }
}

void showText(){

	// définir la couleur du texte
	glColor3f(1.0, 1.0, 1.0);

	//définir la position du texte
    glRasterPos2f(75, 30);

    // afficher le texte
    char scoreText[32];
    sprintf(scoreText, "Score: %d", score);
	int len = strlen(scoreText);
	for (int i = 0; i < len; i++)
	{
	    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, scoreText[i]);
	}

	// définir la couleur du texte
	glColor3f(1.0, 1.0, 1.0);

	//définir la position du texte
	glRasterPos2f(580, 30);

	// afficher le texte
	char roundText[32];
	sprintf(roundText, "Round: %d",round);
	int len1 = strlen(roundText);
	for (int i = 0; i < len1; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, roundText[i]);
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
    glutSwapBuffers();
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0); // black background
	glMatrixMode(GL_PROJECTION); // setup viewing projection
	glLoadIdentity(); // start with identity matrix
	glOrtho(0.0, 780, 500, 0.0, -1.0, 1.0); // définissez les propriétés de vue (vue en 2D)
}


int main(int argc, char **argv)
{
	// Initialisation de FreeGLUT
	glutInit(&argc, argv);

	// définir le mode d'affichage
	glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	// définir la position de la fenêtre
	glutInitWindowPosition(200,50);

	// définir la taille de la fenêtre
	glutInitWindowSize(800,600);

	//création de la fenêtre
	glutCreateWindow ("ARKANOID");

	// Définition de la fonction de gestion des événements du clavier
	//glutKeyboardFunc(myKeyboard);

	glutSpecialFunc(keyPress);
	glutMouseFunc(mouseEvent);
	glutDisplayFunc(display);

    init();

	glutMainLoop(); // Lancement de la boucle d'événements

	return 0;

}
