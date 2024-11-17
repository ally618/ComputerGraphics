#include <GL/glut.h>
#include <cmath>

// 전역 변수
GLfloat ballY = 6.0f;         // 공의 Y 위치 
GLfloat ballVelocity = 0.0f;  // 공의 속도
GLfloat gravity = -0.05f;     // 중력 가속도
GLfloat elasticity = 0.95f;    // 탄성

GLfloat ballRadius = 1.0f;    // 공의 반지름
GLfloat squash = 1.0f;        // 공의 수직 크기
GLfloat stretch = 1.0f;       // 공의 수평 크기

bool isWireframe = false;     // 와이어프레임 모드

GLfloat floorWidth = 10.0f;   // 바닥의 너비
GLfloat floorHeight = 0.1f;   // 바닥의 두께

void MyReshape(int w, int h) {
    if (h == 0) h = 1;
    GLfloat aspect = (GLfloat)w / (GLfloat)h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, aspect, 1.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void MyUpdate(int value) {
    
    ballVelocity += gravity;
    ballY += ballVelocity;

    // 바닥 충돌 처리
    if (ballY - ballRadius * squash <= floorHeight) {
        ballY = floorHeight + ballRadius * squash;
        ballVelocity = -ballVelocity * elasticity;

        // 탄성 효과: 좌우로 늘어남
        squash = 0.8f;
        stretch = 1.2f;
    }
    else {
        // 공이 공중에 있을 때 점차 원래 모양으로 복귀
        squash += (1.0f - squash) * 0.1f;
        stretch += (1.0f - stretch) * 0.1f;
    }

    glutPostRedisplay();
    glutTimerFunc(16, MyUpdate, 0); 
}

void MyDisplay() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // 시점변환 ----------------------------------------------------
    gluLookAt(0.0f, 6.0f, 15.0f, 0.0f, 2.0f, 0.0f, 0.0f, 1.0f, 0.0f);  
    // -------------------------------------------------------------
   
    // 바닥 
    glColor3f(0.6f, 0.6f, 0.6f); 
    glPushMatrix();
    glTranslatef(0.0f, floorHeight / 2.0f, 0.0f);
    glScalef(floorWidth, floorHeight, floorWidth);

    if (isWireframe)
        glutWireCube(1.0f);
    else
        glutSolidCube(1.0f);

    glPopMatrix();

    //공
    glPushMatrix();
    glTranslatef(0.0f, ballY, 0.0f);
    glScalef(stretch, squash, stretch);  // 탄성 변형 적용
    glColor3f(1.0f, 1.0f, 1.0f); 

    if (isWireframe)
        glutWireSphere(ballRadius, 20, 20);
    else
        glutSolidSphere(ballRadius, 20, 20);

    glPopMatrix();
    glutSwapBuffers();
}

void MyKeyboard(unsigned char KeyPressed, int x, int y) {

    switch (KeyPressed) {
    case 'w':
        isWireframe = true;  // 와이어프레임 모드
        break;
    case 's':
        isWireframe = false; // 솔리드 모드
        break;
    case 27:
        exit(0); // ESC 키로 종료
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Q3");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);
    glutKeyboardFunc(MyKeyboard);
    glutTimerFunc(16, MyUpdate, 0);

    glutMainLoop();
    return 0;
}