#include <GL/glut.h>

GLfloat rtri = 0.0f; 
GLfloat scale = 1.0f; 
GLfloat translateX = 0.0f; 
GLfloat translateY = 0.0f; 
GLfloat translateZ = -6.0f; 

void MyReshape(int w, int h) {
    if (h == 0) h = 1; 
    GLfloat aspect = (GLfloat)w / (GLfloat)h;
    glViewport(0, 0, w, h); 
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();
    gluPerspective(45.0f, aspect, 1.0f, 100.0f); 
    glMatrixMode(GL_MODELVIEW); 
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glLoadIdentity(); 

    //-------------------------------------------------------시점변환
    gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
    //-------------------------------------------------------

    glTranslatef(translateX, translateY, translateZ); // 이동
    glScalef(scale, scale, scale); // 크기 조정
    glRotatef(rtri, 0.0f, 1.0f, 0.0f); // Y축 기준 회전
    glBegin(GL_TRIANGLES);

    glColor3f(1.0f, 0.0f, 0.0f);          // Red
    glVertex3f(0.0f, 1.0f, 0.0f);          // Top Of Triangle (Front)
    glColor3f(0.0f, 1.0f, 0.0f);          // Green
    glVertex3f(-1.0f, -1.0f, 1.0f);          // Left Of Triangle (Front)
    glColor3f(0.0f, 0.0f, 1.0f);          // Blue
    glVertex3f(1.0f, -1.0f, 1.0f);          // Right Of Triangle (Front)


    glColor3f(1.0f, 0.0f, 0.0f);          // Red
    glVertex3f(0.0f, 1.0f, 0.0f);          // Top Of Triangle (Right)
    glColor3f(0.0f, 0.0f, 1.0f);          // Blue
    glVertex3f(1.0f, -1.0f, 1.0f);          // Left Of Triangle (Right)
    glColor3f(0.0f, 1.0f, 0.0f);          // Green
    glVertex3f(1.0f, -1.0f, -1.0f);         // Right Of Triangle (Right)


    glColor3f(1.0f, 0.0f, 0.0f);          // Red
    glVertex3f(0.0f, 1.0f, 0.0f);          // Top Of Triangle (Back)
    glColor3f(0.0f, 1.0f, 0.0f);          // Green
    glVertex3f(1.0f, -1.0f, -1.0f);         // Left Of Triangle (Back)
    glColor3f(0.0f, 0.0f, 1.0f);          // Blue
    glVertex3f(-1.0f, -1.0f, -1.0f);         // Right Of Triangle (Back)


    glColor3f(1.0f, 0.0f, 0.0f);          // Red
    glVertex3f(0.0f, 1.0f, 0.0f);          // Top Of Triangle (Left)
    glColor3f(0.0f, 0.0f, 1.0f);          // Blue
    glVertex3f(-1.0f, -1.0f, -1.0f);          // Left Of Triangle (Left)
    glColor3f(0.0f, 1.0f, 0.0f);          // Green
    glVertex3f(-1.0f, -1.0f, 1.0f);          // Right Of Triangle (Left)

    glEnd();                        // Done Drawing The Pyramid

    glutSwapBuffers(); // 화면 버퍼 교체
}


void MyKeyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w': translateY += 0.1f; break; // 위
    case 's': translateY -= 0.1f; break; // 아래
    case 'a': translateX -= 0.1f; break; // 왼쪽
    case 'd': translateX += 0.1f; break; // 오른쪽
    case '1': scale += 0.1f; break; // 크기 증가
    case '2': scale -= 0.1f; break; // 크기 감소
    case 'r':
        rtri += 5.0f; // 회전
        if (rtri > 360.0f) rtri -= 360.0f;
        break;
    case 27: exit(0); // ESC 키로 종료
    }
    glutPostRedisplay();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Q2");

    glEnable(GL_DEPTH_TEST); 

    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);
    glutKeyboardFunc(MyKeyboard);

    glutMainLoop();
    return 0;
}
