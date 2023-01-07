#include <iostream>
#include <GL/glut.h>

#define DEG2RAD 3.14159/180.0
#define nBricks 84

using namespace std;

struct Ball{
	//coordinates of the ball
	float x = 380, y = 420;
	//dimensions of the ball
	float width = 10, height = 8;
	//speed of the ball
	float vX=0.03, vY = 0.06;
};

struct Paddle{
	//coordinates of the platform
	float x = 380, y = 450;
	//dimensions of the platform
	float width = 100, height = 5;
};

struct Bricks{
	//coordinates of the bricks
	float x,y;
	//dimensions of the bricks
	float width=45,height=10;
	//state of the bricks
	bool isDestroyed = false;
};

Bricks bricks[nBricks];
Ball ball;
Paddle Paddle;
int score=0,roundCurrent=1;
int mouseX, mouseY;
bool win=false,lost=false,start=false;

void drawBall(){
	//apply the color of the ball (yellow)
	glColor3f(255, 255, 0);

	//draw the ball as a rectangle
	glBegin(GL_QUADS);
	glVertex2f(ball.x - ball.width / 2, ball.y - ball.height / 2);
	glVertex2f(ball.x + ball.width / 2, ball.y - ball.height / 2);
	glVertex2f(ball.x + ball.width / 2, ball.y + ball.height / 2);
	glVertex2f(ball.x - ball.width / 2, ball.y + ball.height / 2);
	glEnd();
}

void drawPaddle(){

	//apply the color of the platform (blue)
	glColor3f(0, 0, 255);

	//draw the platform
	glBegin(GL_QUADS);
	glVertex2f(Paddle.x - Paddle.width / 2, Paddle.y - Paddle.height / 2);
	glVertex2f(Paddle.x + Paddle.width / 2, Paddle.y - Paddle.height / 2);
	glVertex2f(Paddle.x + Paddle.width / 2, Paddle.y + Paddle.height / 2);
	glVertex2f(Paddle.x - Paddle.width / 2, Paddle.y + Paddle.height / 2);
	glEnd();
}

void drawBrick(){

	//coordinates of the bricks
	float posX=100, posY=80;
	for(int i=0; i< nBricks; i++){
		bricks[i].x = posX;
		bricks[i].y = posY;

		posX+=50;
		if(posX > 650){
			posX = 100;
			posY+= 28;
		}
	}

	//apply the color of the platform (green)
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
  //browse each brick
  for (int i = 0; i < nBricks; i++) {
	  	//check the state of the brick, if it is destroyed, go to the next iteration
	  	if(bricks[i].isDestroyed) continue;
	  	//check if the ball collides with the brick at position i

	  	//calculate the coordinates of the corners of the ball
	  	float bx1 = ball.x - ball.width / 2;
	  	float bx2 = ball.x + ball.width / 2;
	    float by1 = ball.y - ball.height / 2;
	    float by2 = ball.y + ball.height / 2;

	    //calculate the coordinates of the corners of the brick at position 1
	    float brx1 = bricks[i].x - bricks[i].width / 2;
	    float brx2 = bricks[i].x + bricks[i].width / 2;
	    float bry1 = bricks[i].y - bricks[i].height / 2;
	    float bry2 = bricks[i].y + bricks[i].height / 2;

	    //check if there has been a collision
	    if (bx1 > brx2 || bx2 < brx1 || by1 > bry2 || by2 < bry1)
	    continue; //no collision, so we go to the next iteration

	    // There was a collision, so true and and we change the state of the brick
	    bricks[i].isDestroyed = true;
	    return true;
    }
  	  return false;
}


bool checkCollisionPaddle() {
	  //calculate the coordinates of the corners of the ball
	  float bx1 = ball.x - ball.width / 2;
	  float bx2 = ball.x + ball.width / 2;
	  float by1 = ball.y - ball.height / 2;
	  float by2 = ball.y + ball.height / 2;

	  //calculate the coordinates of the corners of the platform
	  float rx1 = Paddle.x - Paddle.width / 2;
	  float rx2 = Paddle.x + Paddle.width / 2;
	  float ry1 = Paddle.y - Paddle.height / 2;
	  float ry2 = Paddle.y + Paddle.height / 2;

	  //check if there has been a collision
	  if (bx1 > rx2 || bx2 < rx1 || by1 > ry2 || by2 < ry1) {
	    return false; //no collision
	  }
	  return true; //collision detected

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
	//coordinates of the brick
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
	//coordinates of the bricks
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

	//check if there is a collision between the platform and the ball
	if(checkCollisionPaddle()){
		ball.vY = -ball.vY;
	}

	//check if there is a collision between a brick and the ball
	if(checkCollisionBrick()){
		ball.vX = -ball.vX;
		score+= 5;
	}

	ball.y -= ball.vY;
	if(checkCollisionBrick()){
		ball.vY = -ball.vY;
		score+= 5;
	}

	// Management of the ball's bounces on the edges of the screen
	if(ball.x-ball.width < 0 || ball.x+ball.width > 775)
		ball.vX = -ball.vX;

	if(ball.y < 0)
		ball.vY = -ball.vY;

	if(ball.y + ball.height > 480){
	//GAMEOVER
	endGame();

	}
	//check if there is a win
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
	//calculate mouse movement from previous position
    int dx = x - mouseX;

    //new mouse position
    mouseX = x;

    //apply the trip to the platform
    Paddle.x += dx;
    if(Paddle.x+Paddle.width > 830) Paddle.x  = 830 - Paddle.width;
    else if(Paddle.x-Paddle.width < -50) Paddle.x = -50 + Paddle.width;
}

void onMouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
    	//save the mouse position
        mouseX = x;
        mouseY = y;
    }
}
void showText(){

	//set the text color (white)
	glColor3f(255, 255, 255);

	//set text position
    glRasterPos2f(75, 30);

    //display the text
    char scoreText[32];
    sprintf(scoreText, "Score: %d", score);
	int len = strlen(scoreText);
	for (int i = 0; i < len; i++)
	{
	    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, scoreText[i]);
	}

	//set the text color (white)
	glColor3f(255, 255, 255);

	//set text position
	glRasterPos2f(580, 30);

	//display the text
	char roundCurrentText[32];
	sprintf(roundCurrentText, "Round: %d",roundCurrent);
	int len1 = strlen(roundCurrentText);
	for (int i = 0; i < len1; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, roundCurrentText[i]);
	}
}


void showTextWinLost(const char*text, int pos){
	//set the text color (white)
	glColor3f(255, 255, 255);

	//set text position
	 glRasterPos2f(pos, 350);

	 //display the text
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
    	showTextWinLost("Bien joué! Vous avez gagné,Appuyez sur la barre d'espace pour continuer!",40);
    else if(lost)
    	showTextWinLost("Vous avez perdu!Appuyez sur la barre d'espace pour recommencer!",80);


    glutSwapBuffers();
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0); // black backgroundCurrent
	glMatrixMode(GL_PROJECTION); //setup viewing projection
	glLoadIdentity(); //start with identity matrix
	glOrtho(0.0, 780, 500, 0.0, -1.0, 1.0); //define the view properties (2D view)
}


int main(int argc, char **argv)
{
	//initialize FreeGLUT
	glutInit(&argc, argv);

	//set the display mode
	glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	//set the position of the window
	glutInitWindowPosition(200,50);

	//set the size of the window
	glutInitWindowSize(800,600);

	//creation of the window
	glutCreateWindow ("ARKANOID");

	//definition of functions for mouse
	glutMotionFunc(onMouseMove);
	glutMouseFunc(onMouseClick);

	//definition of the keyboard event management function
	glutKeyboardFunc(keyboard);

	//definition of the display function
	glutDisplayFunc(display);
    init();

	glutMainLoop();//launching the event loop
	return 0;

}
