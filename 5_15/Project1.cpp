#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

int FlatShaded = 0;
int Wireframed = 0;
int ViewX = 0, ViewY = 0;

void InitLight() {
    GLfloat mat_diffuse[] = { 0.5, 0.4, 0.3, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
    GLfloat mat_shininess[] = { 15.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat light_position[] = { -3, 6, 3.0, 0.0 };
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void DrawTable() {
    // 탁자 상판
    glPushMatrix();
    glTranslatef(0.0, 0.4, 0.0);  // 상판의 위치
    glScalef(1.0, 0.05, 1.0);  // 상판의 두께 조정 
    glutSolidCube(1.0);  
    glPopMatrix();

    // 탁자 다리
    glPushMatrix();
    glTranslatef(0.25, 0.2, 0);  // 다리의 위치
    glScalef(0.05, 0.4, 0.05);  // 다리의 크기 조정
    glutSolidCube(1.0);  
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.25, 0.2, 0);
    glScalef(0.05, 0.4, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

   
}

void DrawObjects() {
    // 구
    glPushMatrix();
    glTranslatef(-0.15, 0.5, 0.0);  
    glutSolidSphere(0.1, 20, 20);  
    glPopMatrix();

    //정육면체
    glPushMatrix();
    glTranslatef(0.15, 0.45, -0.15);
    glScalef(0.1, 0.1, 0.1); 
    glutSolidCube(1.0); 
    glPopMatrix();

    //정사면체
    glPushMatrix();
    glTranslatef(0.0, 0.45, 0.0);
    glScalef(0.1, 0.1, 0.1);  
    glutSolidTetrahedron();
    glPopMatrix();

}

void MyMouseMove(GLint X, GLint Y) {
    glutPostRedisplay();
}

void MyKeyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'q': case 'Q': case '\033':
        exit(0);
        break;
    case 's':
        if (FlatShaded) {
            FlatShaded = 0;
            glShadeModel(GL_SMOOTH);
        }
        else {
            FlatShaded = 1;
            glShadeModel(GL_FLAT);
        }
        glutPostRedisplay();
        break;
    }
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0.0, 0.0, 0.0, 
        0.0, 0.0, -1.0, 
        0.0, 1.0, 0.0);


    DrawTable();
    DrawObjects();

    glFlush();
}

void MyReshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL Table with Objects");

    glClearColor(0.4, 0.4, 0.4, 0.0);
    InitLight();
    glutDisplayFunc(MyDisplay);
    glutKeyboardFunc(MyKeyboard);
    glutMotionFunc(MyMouseMove);
    glutReshapeFunc(MyReshape);
    glutMainLoop();
    return 0;
}
