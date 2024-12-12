#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
using namespace std;


// ���� �̵��� ���� ����
float cameraAngleX = 0.0f, cameraAngleY = 0.0f;
float cameraDistance = 20.0f;

// ���� ǥ�� �÷���
bool showHelp = false;

// �ؽ�ó ID
GLuint textures[10];  

// �ʱ�ȭ �Լ�
void init() {
    glEnable(GL_DEPTH_TEST);          // ���� �׽�Ʈ Ȱ��ȭ
    glEnable(GL_TEXTURE_2D);          // �ؽ�ó Ȱ��ȭ

    GLfloat ambientLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // ���
    GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // ���
    GLfloat lightPos[] = { 0.0f, 5.0f, 5.0f, 1.0f }; // ���� ��ġ

    // ���� Ȱ��ȭ
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // ���� ���� ����
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);    
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);    
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);  
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);       // ���� ��ġ ����
   
}

// �ؽ�ó �ε� �Լ�
void loadTexture(const char* filename, GLuint textureIndex) {
    int width, height, nrChannels;
    // �̹��� �ε�
    unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);

    if (data) {
        // �ؽ�ó ����
        glGenTextures(1, &textures[textureIndex]);
        glBindTexture(GL_TEXTURE_2D, textures[textureIndex]);

        // �ؽ�ó �Ӽ� ����
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 

        // �ؽ�ó �̹��� ���ε�
        if (nrChannels == 3) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else if (nrChannels == 4) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }

        // �޸� ����
        stbi_image_free(data);
    }
    else {
        std::cerr << "Texture loading failed!" << std::endl;
    }
}

// �ؽ�ó ��� �Լ�
void Textures() {
    loadTexture("texture/wood.jpg", 0);  
    loadTexture("texture/plave.jpg", 1); 
   
}

//å��
void drawTable() {
    glPushMatrix();

    // ���̺� ���ǿ� �ؽ�ó ����
    glEnable(GL_TEXTURE_2D);  // �ؽ�ó ���� Ȱ��ȭ
    glBindTexture(GL_TEXTURE_2D, textures[0]);  // �ؽ�ó ���ε�

    // ���̺� ����(���κ�)
    glTranslatef(0.0f, -0.5f, 0.0f); // ���̺� ��ġ
    glScalef(10.0f, 0.5f, 7.0f); // ���̺� ũ��

    // �ؽ�ó ���ε� �簢�� ���� �׸���
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.0f, -0.5f); // ���� �Ʒ�
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.0f, -0.5f); // ������ �Ʒ�
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.0f, 0.5f);    // ������ ��
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.0f, 0.5f);// ���� ��
    glEnd();
    glPopMatrix();  //���� ��

    // ���̺� �׵θ�(����) �ؽ�ó ����
    glPushMatrix();
    glTranslatef(0.0f, -0.95f, 0.0f); // ��ġ
    glEnable(GL_TEXTURE_2D);  // �ؽ�ó ���� Ȱ��ȭ
    glBindTexture(GL_TEXTURE_2D, textures[0]);  // wood.jpg �ؽ�ó ���ε�

    // ���� �׵θ�
    glPushMatrix();
    glTranslatef(-4.5f, 0.0f, 0.0f);  // ���̺� ���ʿ� ��ġ
    glScalef(0.5f, 0.5f, 1.0f);  // ũ�� ���� (���� ���簢��)
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 0.0f, -3.5f);  // ����
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 0.0f, 3.5f);   // ����
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 3.5f);   // ����
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -3.5f);  // ����
    glEnd();
    glPopMatrix();

    // ���� �׵θ�
    glPushMatrix();
    glTranslatef(4.5f, 0.0f, 0.0f);  // ���̺� �����ʿ� ��ġ
    glScalef(0.5f, 0.5f, 1.0f);  // ũ�� ����
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, 0.0f, -3.5f);  // ����
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 0.0f, 3.5f);   // ����
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 3.5f);   // ����
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -3.5f);  // ����
    glEnd();
    glPopMatrix();

    // ���� �׵θ�
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -3.0f);  // ���̺� ���ʿ� ��ġ
    glScalef(1.0f, 0.5f, 0.5f);  // ũ�� ����
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.0f, 0.0f, -1.0f);  // ����
    glTexCoord2f(1.0f, 0.0f); glVertex3f(5.0f, 0.0f, -1.0f);   // ����
    glTexCoord2f(1.0f, 1.0f); glVertex3f(5.0f, 1.0f, -1.0f);   // ����
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-5.0f, 1.0f, -1.0f);  // ����
    glEnd();
    glPopMatrix();

    // ���� �׵θ�
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 3.0f);  // ���̺� ���ʿ� ��ġ
    glScalef(1.0f, 0.5f, 0.5f);  // ũ�� ����
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.0f, 0.0f, 1.0f);   // ����
    glTexCoord2f(1.0f, 0.0f); glVertex3f(5.0f, 0.0f, 1.0f);    // ����
    glTexCoord2f(1.0f, 1.0f); glVertex3f(5.0f, 1.0f, 1.0f);    // ����
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-5.0f, 1.0f, 1.0f);   // ����
    glEnd();
    glPopMatrix();

    glPopMatrix(); // �׵θ� ��

    glDisable(GL_TEXTURE_2D);  // �ؽ�ó ���� ��Ȱ��ȭ

    // ���̺� �ٸ� 
    GLfloat legMaterial[] = { 0.6f, 0.3f, 0.1f, 1.0f }; // �ٸ� ���� (����)
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, legMaterial);  // �ٸ� ���� ���� (�յ� ��� ����)
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, legMaterial);

    // �� ���� �ٸ�
    glPushMatrix();
    glTranslatef(-4.5f, -2.0f, -3.0f); // ��ġ
    glScalef(0.2f, 2.0f, 0.2f); // ũ�� (���� �ٸ�)
    glutSolidCube(1.0f); // �ٸ� ����
    glPopMatrix();

    // �� ������ �ٸ�
    glPushMatrix();
    glTranslatef(4.5f, -2.0f, -3.0f); // ��ġ
    glScalef(0.2f, 2.0f, 0.2f); // ũ�� (���� �ٸ�)
    glutSolidCube(1.0f); // �ٸ� ����
    glPopMatrix();

    // �� ���� �ٸ�
    glPushMatrix();
    glTranslatef(-4.5f, -2.0f, 3.0f); // ��ġ
    glScalef(0.2f, 2.0f, 0.2f); // ũ�� (���� �ٸ�)
    glutSolidCube(1.0f); // �ٸ� ����
    glPopMatrix();

    // �� ������ �ٸ�
    glPushMatrix();
    glTranslatef(4.5f, -2.0f, 3.0f); // ��ġ
    glScalef(0.2f, 2.0f, 0.2f); // ũ�� (���� �ٸ�)
    glutSolidCube(1.0f); // �ٸ� ����
    glPopMatrix();

    glPopMatrix();
}

//�����
void drawLamp() {

    // ���
    GLfloat standColor[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, standColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, standColor);
    glPushMatrix();
    glTranslatef(4.0f, 0.0f, -3.0f); // ��ġ
    glScalef(0.1f, 1.0f, 0.1f);  // ��� ũ�� (���� �����)
    glutSolidCube(1.0f); // ť��� ��� ǥ��
    glPopMatrix();

    // ����  (��ü)
    GLfloat bulbColor[] = { 1.0f, 1.0f, 0.5f, 1.0f }; // �����
    glMaterialfv(GL_FRONT, GL_AMBIENT, bulbColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, bulbColor);
    glPushMatrix();
    glTranslatef(4.0f, 1.0f, -3.0f); // ��� ���� �̵�
    glutSolidSphere(0.5f, 20, 20);  // ����  (��ü)
    glPopMatrix();

}

//å
void drawBook() {
    glPushMatrix();
    GLfloat matAmbient[] = { 0.4f, 0.2f, 0.6f, 1.0f }; // ����� �迭
    GLfloat matDiffuse[] = { 0.5f, 0.3f, 0.7f, 1.0f }; //Ȯ�걤 �ݻ�� ���� ����
    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);

    // ���� ���� å�� ���η� �����α�
    for (int i = 0; i < 5; ++i) {
        glPushMatrix();
        glTranslatef(i * 0.4f - 4.5f, 0.5f, -2.0f); // ��ġ ����
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // å�� ���η� ����
        glScalef(0.2f, 1.2f, 1.8f); // å ũ�� 
        glutSolidCube(1.0f); // å ����
        glPopMatrix();
    }
    glPopMatrix();
}

//å ǥ��
void drawBookName() {
    glPushMatrix();
    GLfloat matAmbient[] = { 0.4f, 0.4f, 0.4f, 1.0f }; // ȸ��
    GLfloat matDiffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f }; //Ȯ�걤 �ݻ��
    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);

    // ���� ��
    for (int i = 0; i < 5; ++i) {
        glPushMatrix();
        glTranslatef(i * 0.4f - 4.41f, 0.9f, -2.0f); // ��ġ ����
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // ���η� ����
        glScalef(0.05f, 0.8f, 0.5f); //ũ�� 
        glutSolidCube(1.0f); //����
        glPopMatrix();
    }
    glPopMatrix();
}

// ��ǻ�� 
void drawComputer() {
    glPushMatrix();

    // ����� ���
    GLfloat standColor[] = { 0.5f, 0.5f, 0.5f, 1.0f }; // ��
    glMaterialfv(GL_FRONT, GL_AMBIENT, standColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, standColor);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -2.0f);  // ��� ��ġ
    glScalef(0.2f, 1.0f, 0.2f);  // ��� ũ�� 
    glutSolidCube(1.0f); // ť��� ��� ǥ��
    glPopMatrix();

    // ����� ȭ�� (���÷��� �κ�)
    glEnable(GL_TEXTURE_2D);  // �ؽ�ó ���� Ȱ��ȭ
    glBindTexture(GL_TEXTURE_2D, textures[1]);  // plave.jpg �ؽ�ó ���ε�
    glPushMatrix();
    glTranslatef(0.0f, 1.5f, -1.9f);  // ��ġ
    glScalef(1.0f, 1.0f, 0.1f);  // ȭ�� ũ��

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.5f, -1.0f, 0.0f);  // ���ϴ�
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.5f, -1.0f, 0.0f);   // ���ϴ�
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.5f, 1.0f, 0.0f);    // ����
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.5f, 1.0f, 0.0f);   // �»��
    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);  // �ؽ�ó ���� ��Ȱ��ȭ


    // ����� �׵θ� (����)
    GLfloat borderColor[] = { 0.7f, 0.7f, 0.7f, 1.0f }; // ���� �׵θ�
    glMaterialfv(GL_FRONT, GL_AMBIENT, borderColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, borderColor);
    glPushMatrix();
    glTranslatef(0.0f, 1.5f, -2.0f);  // ��ġ
    glScalef(3.1f, 2.1f, 0.1f);  // �׵θ� ũ�� (����ͺ��� ��¦ ŭ)
    glutSolidCube(1.0f); // ť��� �׵θ� ǥ��
    glPopMatrix();

    // Ű����
    GLfloat keyboardColor[] = { 0.4f, 0.4f, 0.4f, 1.0f }; // ȸ��
    glMaterialfv(GL_FRONT, GL_AMBIENT, keyboardColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, keyboardColor);
    glPushMatrix();
    glTranslatef(0.0f, -0.2f, 0.6f);  // Ű���� ��ġ
    glScalef(2.8f, 0.1f, 1.0f);  // Ű���� ũ��
    glutSolidCube(1.0f); // ť��� Ű���� ǥ��
    glPopMatrix();

    // Ű���� Ű��
    GLfloat keyColor[] = { 0.1f, 0.1f, 0.1f, 1.0f }; // Ű���� Ű ����
    glMaterialfv(GL_FRONT, GL_AMBIENT, keyColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, keyColor);
    float keyWidth = 0.18f, keyHeight = 0.05f, keyDepth = 0.1f;

    // Ű���� Ű���� 4x10 �迭�� ���� (�� 4���� Ű)
    float xOffset = -1.1f, yOffset = -0.1f, zOffset = 0.24f;

    // Ű ���� ������ ������ ������ Ű�� Ű���� ���� �� �µ��� ����
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 10; ++col) {
            glPushMatrix();
            glTranslatef(xOffset + col * 0.25f, yOffset, zOffset + row * 0.22f);  // Ű ���� ���� ����
            glScalef(keyWidth, keyHeight, keyDepth);  // Ű ũ��
            glutSolidCube(1.0f); // ť��� Ű ǥ��
            glPopMatrix();
        }
    }
    glPopMatrix();
}

// �˶��ð� 
void drawClock(float Angle) {
    GLUquadric* quad = gluNewQuadric(); 

    // �ð� ��ü
    GLfloat bodyColor[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, bodyColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, bodyColor);
    glPushMatrix();
    glTranslatef(2.6f, 0.3f, -0.9f);
    gluDisk(quad, 0.0f, 0.5f, 50, 1);  // ���� ��ũ
    glPopMatrix();

    // ������� ����Ͽ� �ð� �β� �߰�
    GLfloat bodyCylinderColor[] = { 1.0f, 0.0f, 0.0f, 1.0f }; // ������
    glMaterialfv(GL_FRONT, GL_AMBIENT, bodyCylinderColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, bodyCylinderColor);
    glPushMatrix();
    glTranslatef(2.6f, 0.3f, -0.9f);  // ����� ��ġ
    gluCylinder(quad, 0.5f, 0.5f, 0.2f, 50, 10);  // �����
    glPopMatrix();

    //��ħ 
    GLfloat minuteHandColor[] = { 0.0f, 0.0f, 0.0f, 1.0f }; // ������
    glMaterialfv(GL_FRONT, GL_AMBIENT, minuteHandColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, minuteHandColor);
    glPushMatrix();
    glTranslatef(2.6f, 0.3f, -0.89f);
    glRotatef(Angle, 0.0f, 0.0f, 1.0f);  //z�� �߽� ȸ��
    glScalef(0.02f, 0.32f, 0.02f);
    glutSolidCube(1.0f);  // ��ħ
    glPopMatrix();

    // �˶��ð� �� ��� �߰� (���ʿ� ��ġ)
    GLfloat bellColor[] = { 1.0f, 0.5f, 0.0f, 1.0f }; // �����
    glMaterialfv(GL_FRONT, GL_AMBIENT, bellColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, bellColor);

    // ���� ��
    glPushMatrix();
    glTranslatef(2.2f, 0.7f, -0.9f); // ���� �� ��ġ
    glScalef(0.42f, 0.42f, 0.42f);
    glutSolidSphere(0.3f, 20, 20);  // ��
    glPopMatrix();

    // ������ ��
    glPushMatrix();
    glTranslatef(3.0f, 0.7f, -0.9f); // ������ �� ��ġ
    glScalef(0.42f, 0.42f, 0.42f);
    glutSolidSphere(0.3f, 20, 20);  // ��
    glPopMatrix();

    // ���� �ε帮�� ��ġ (���)
    GLfloat hammerColor[] = { 1.0f, 0.5f, 0.0f, 1.0f }; 
    glMaterialfv(GL_FRONT, GL_AMBIENT, hammerColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, hammerColor);
    glPushMatrix();
    glTranslatef(2.6f, 0.9f, -0.8f); // ��ġ ��ġ
    glScalef(0.05f, 0.12f, 0.05f);  //  ��ġ
    glutSolidCube(1.0f);
    glPopMatrix();
}

// ��ħ ���� ���
float calculateAngle() {
    static float angle = 0.0f;
    angle += 0.5f; // ��ħ 1�ʴ� 0.5���� ȸ��
    if (angle >= 360.0f) angle -= 360.0f;  //�� ���� ���� �ٽ� 0��
    return angle;
}

// Ÿ�̸� �Լ�
void timer(int value) {
    glutPostRedisplay();    //���� ������ �ٽ� �׸���
    glutTimerFunc(100, timer, 0);   //0.1�� �Ŀ� timer�Լ� �ٽ� ȣ��
}

//��
void drawCup() {
    glPushMatrix();

    // �� ��ü (�����)
    GLfloat cupColor[] = { 0.2f, 0.28f, 0.22f, 1.0f }; // �ʷ�
    glMaterialfv(GL_FRONT, GL_AMBIENT, cupColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cupColor);
    glTranslatef(-2.5f, -0.3f, 2.0f); // ��ġ 
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // ����� ����
    glScalef(0.3f, 0.3f, 0.3f); // ũ�� 

    GLUquadric* quad = gluNewQuadric();
    gluCylinder(quad, 1.0, 1.0, 2.2, 32, 32);

    // �� ������ 
    glPushMatrix();
    glTranslatef(-1.0f, -0.2f, 1.0f); // ������ ��ġ ����
    glRotatef(90.0f, 90.0f, 1.0f, 0.0f); // ������ ȸ��
    glutSolidTorus(0.2, 0.5, 32, 32); // �䷯�� 
    glPopMatrix();

    // ���� ���κ� (Ŀ��)
    GLfloat coffeeColor[] = { 0.33f, 0.15f, 0.05f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, coffeeColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, coffeeColor);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1.7f); // ��ġ
    gluDisk(quad, 0.0, 1.0, 32, 32); //  ����
    glPopMatrix();

    gluDeleteQuadric(quad); 
    glPopMatrix();
}


// �ؽ�Ʈ ������ �Լ�
void renderBitmapString(float x, float y, float z, const char* string) {
    glRasterPos3f(x, y, z);
    while (*string) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string);
        string++;
    }
}

// ���� �޽��� ǥ��
void displayHelp() {
    if (showHelp) {
        renderBitmapString(-10.0f, 5.0f, -1.0f, "Help Menu:");
        renderBitmapString(-10.1f, 4.0f, -1.0f, "H - Help");
        renderBitmapString(-10.2f, 3.0f, -1.0f, "W - Move forward");
        renderBitmapString(-10.3f, 2.0f, -1.0f, "S - Move backward");
        renderBitmapString(-10.4f, 1.0f, -1.0f, "A - Move left");
        renderBitmapString(-10.5f, 0.0f, -1.0f, "D - Move right");
    }
}

// ��� ������ �Լ�
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ī�޶� ����
    glLoadIdentity();
    gluLookAt(cameraDistance * sin(cameraAngleX * M_PI / 180.0f), 5.0f, cameraDistance * cos(cameraAngleX * M_PI / 180.0f),
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f);

    // ��� ������
    drawTable();
    drawLamp();
    drawBook();
    drawBookName();
    drawComputer();
    drawCup();
    drawClock(calculateAngle());
    
    // ���� ǥ��
    displayHelp();

    glutSwapBuffers();
}

// â ũ�� ���� ó��
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w / h, 1.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

// Ű���� �Է� ó�� �Լ�
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w': // ī�޶� ������ �̵�
        cameraDistance -= 1.0f;
        if (cameraDistance < 5.0f) cameraDistance = 5.0f; // �ʹ� ������ ���� �ʰ� ����
        break;
    case 's': // ī�޶� �ڷ� �̵�
        cameraDistance += 1.0f;
        break;
    case 'a': // ī�޶� �������� ȸ��
        cameraAngleX -= 5.0f;
        break;
    case 'd': // ī�޶� ���������� ȸ��
        cameraAngleX += 5.0f;
        break;
    case 'h': // ���� ǥ��
        showHelp = !showHelp;
        break;
    case 27: // ESC Ű�� ����
        exit(0);
    }
    glutPostRedisplay(); // ȭ�� ���� ��û
}

// ���� �Լ�
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("202204167 Ȳ�ſ�");

    init();
    Textures();  // �ؽ�ó �ε�

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(100, timer, 0);
    glutMainLoop();

    return 0;
}