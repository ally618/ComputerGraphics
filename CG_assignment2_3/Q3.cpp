#include <GL/glut.h>
#include <cmath>

// ���� ����
GLfloat ballY = 6.0f;         // ���� Y ��ġ 
GLfloat ballVelocity = 0.0f;  // ���� �ӵ�
GLfloat gravity = -0.05f;     // �߷� ���ӵ�
GLfloat elasticity = 0.95f;    // ź��

GLfloat ballRadius = 1.0f;    // ���� ������
GLfloat squash = 1.0f;        // ���� ���� ũ��
GLfloat stretch = 1.0f;       // ���� ���� ũ��

bool isWireframe = false;     // ���̾������� ���

GLfloat floorWidth = 10.0f;   // �ٴ��� �ʺ�
GLfloat floorHeight = 0.1f;   // �ٴ��� �β�

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

    // �ٴ� �浹 ó��
    if (ballY - ballRadius * squash <= floorHeight) {
        ballY = floorHeight + ballRadius * squash;
        ballVelocity = -ballVelocity * elasticity;

        // ź�� ȿ��: �¿�� �þ
        squash = 0.8f;
        stretch = 1.2f;
    }
    else {
        // ���� ���߿� ���� �� ���� ���� ������� ����
        squash += (1.0f - squash) * 0.1f;
        stretch += (1.0f - stretch) * 0.1f;
    }

    glutPostRedisplay();
    glutTimerFunc(16, MyUpdate, 0); 
}

void MyDisplay() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // ������ȯ ----------------------------------------------------
    gluLookAt(0.0f, 6.0f, 15.0f, 0.0f, 2.0f, 0.0f, 0.0f, 1.0f, 0.0f);  
    // -------------------------------------------------------------
   
    // �ٴ� 
    glColor3f(0.6f, 0.6f, 0.6f); 
    glPushMatrix();
    glTranslatef(0.0f, floorHeight / 2.0f, 0.0f);
    glScalef(floorWidth, floorHeight, floorWidth);

    if (isWireframe)
        glutWireCube(1.0f);
    else
        glutSolidCube(1.0f);

    glPopMatrix();

    //��
    glPushMatrix();
    glTranslatef(0.0f, ballY, 0.0f);
    glScalef(stretch, squash, stretch);  // ź�� ���� ����
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
        isWireframe = true;  // ���̾������� ���
        break;
    case 's':
        isWireframe = false; // �ָ��� ���
        break;
    case 27:
        exit(0); // ESC Ű�� ����
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