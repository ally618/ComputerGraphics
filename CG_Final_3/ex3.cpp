#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
using namespace std;


// 시점 이동을 위한 변수
float cameraAngleX = 0.0f, cameraAngleY = 0.0f;
float cameraDistance = 20.0f;

// 도움말 표시 플래그
bool showHelp = false;

// 텍스처 ID
GLuint textures[10];  

// 초기화 함수
void init() {
    glEnable(GL_DEPTH_TEST);          // 깊이 테스트 활성화
    glEnable(GL_TEXTURE_2D);          // 텍스처 활성화

    GLfloat ambientLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // 흰색
    GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // 흰색
    GLfloat lightPos[] = { 0.0f, 5.0f, 5.0f, 1.0f }; // 조명 위치

    // 조명 활성화
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // 조명 색상 설정
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);    
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);    
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);  
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);       // 조명 위치 설정
   
}

// 텍스처 로드 함수
void loadTexture(const char* filename, GLuint textureIndex) {
    int width, height, nrChannels;
    // 이미지 로드
    unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);

    if (data) {
        // 텍스처 생성
        glGenTextures(1, &textures[textureIndex]);
        glBindTexture(GL_TEXTURE_2D, textures[textureIndex]);

        // 텍스처 속성 설정
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 

        // 텍스처 이미지 업로드
        if (nrChannels == 3) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else if (nrChannels == 4) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }

        // 메모리 해제
        stbi_image_free(data);
    }
    else {
        std::cerr << "Texture loading failed!" << std::endl;
    }
}

// 텍스처 경로 함수
void Textures() {
    loadTexture("texture/wood.jpg", 0);  
    loadTexture("texture/plave.jpg", 1); 
   
}

//책상
void drawTable() {
    glPushMatrix();

    // 테이블 상판에 텍스처 적용
    glEnable(GL_TEXTURE_2D);  // 텍스처 매핑 활성화
    glBindTexture(GL_TEXTURE_2D, textures[0]);  // 텍스처 바인딩

    // 테이블 상판(윗부분)
    glTranslatef(0.0f, -0.5f, 0.0f); // 테이블 위치
    glScalef(10.0f, 0.5f, 7.0f); // 테이블 크기

    // 텍스처 매핑된 사각형 상판 그리기
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.0f, -0.5f); // 왼쪽 아래
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.0f, -0.5f); // 오른쪽 아래
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.0f, 0.5f);    // 오른쪽 위
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.0f, 0.5f);// 왼쪽 위
    glEnd();
    glPopMatrix();  //상판 끝

    // 테이블 테두리(옆면) 텍스처 적용
    glPushMatrix();
    glTranslatef(0.0f, -0.95f, 0.0f); // 위치
    glEnable(GL_TEXTURE_2D);  // 텍스처 매핑 활성화
    glBindTexture(GL_TEXTURE_2D, textures[0]);  // wood.jpg 텍스처 바인딩

    // 좌측 테두리
    glPushMatrix();
    glTranslatef(-4.5f, 0.0f, 0.0f);  // 테이블 왼쪽에 배치
    glScalef(0.5f, 0.5f, 1.0f);  // 크기 조정 (얇은 직사각형)
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 0.0f, -3.5f);  // 좌측
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 0.0f, 3.5f);   // 좌측
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 3.5f);   // 위쪽
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -3.5f);  // 위쪽
    glEnd();
    glPopMatrix();

    // 우측 테두리
    glPushMatrix();
    glTranslatef(4.5f, 0.0f, 0.0f);  // 테이블 오른쪽에 배치
    glScalef(0.5f, 0.5f, 1.0f);  // 크기 조정
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, 0.0f, -3.5f);  // 우측
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 0.0f, 3.5f);   // 우측
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 3.5f);   // 위쪽
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -3.5f);  // 위쪽
    glEnd();
    glPopMatrix();

    // 앞쪽 테두리
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -3.0f);  // 테이블 앞쪽에 배치
    glScalef(1.0f, 0.5f, 0.5f);  // 크기 조정
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.0f, 0.0f, -1.0f);  // 앞쪽
    glTexCoord2f(1.0f, 0.0f); glVertex3f(5.0f, 0.0f, -1.0f);   // 앞쪽
    glTexCoord2f(1.0f, 1.0f); glVertex3f(5.0f, 1.0f, -1.0f);   // 위쪽
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-5.0f, 1.0f, -1.0f);  // 위쪽
    glEnd();
    glPopMatrix();

    // 뒤쪽 테두리
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 3.0f);  // 테이블 뒤쪽에 배치
    glScalef(1.0f, 0.5f, 0.5f);  // 크기 조정
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.0f, 0.0f, 1.0f);   // 뒤쪽
    glTexCoord2f(1.0f, 0.0f); glVertex3f(5.0f, 0.0f, 1.0f);    // 뒤쪽
    glTexCoord2f(1.0f, 1.0f); glVertex3f(5.0f, 1.0f, 1.0f);    // 위쪽
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-5.0f, 1.0f, 1.0f);   // 위쪽
    glEnd();
    glPopMatrix();

    glPopMatrix(); // 테두리 끝

    glDisable(GL_TEXTURE_2D);  // 텍스처 매핑 비활성화

    // 테이블 다리 
    GLfloat legMaterial[] = { 0.6f, 0.3f, 0.1f, 1.0f }; // 다리 색상 (갈색)
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, legMaterial);  // 다리 색상 설정 (앞뒤 모두 적용)
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, legMaterial);

    // 앞 왼쪽 다리
    glPushMatrix();
    glTranslatef(-4.5f, -2.0f, -3.0f); // 위치
    glScalef(0.2f, 2.0f, 0.2f); // 크기 (얇은 다리)
    glutSolidCube(1.0f); // 다리 생성
    glPopMatrix();

    // 앞 오른쪽 다리
    glPushMatrix();
    glTranslatef(4.5f, -2.0f, -3.0f); // 위치
    glScalef(0.2f, 2.0f, 0.2f); // 크기 (얇은 다리)
    glutSolidCube(1.0f); // 다리 생성
    glPopMatrix();

    // 뒤 왼쪽 다리
    glPushMatrix();
    glTranslatef(-4.5f, -2.0f, 3.0f); // 위치
    glScalef(0.2f, 2.0f, 0.2f); // 크기 (얇은 다리)
    glutSolidCube(1.0f); // 다리 생성
    glPopMatrix();

    // 뒤 오른쪽 다리
    glPushMatrix();
    glTranslatef(4.5f, -2.0f, 3.0f); // 위치
    glScalef(0.2f, 2.0f, 0.2f); // 크기 (얇은 다리)
    glutSolidCube(1.0f); // 다리 생성
    glPopMatrix();

    glPopMatrix();
}

//조명등
void drawLamp() {

    // 기둥
    GLfloat standColor[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, standColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, standColor);
    glPushMatrix();
    glTranslatef(4.0f, 0.0f, -3.0f); // 위치
    glScalef(0.1f, 1.0f, 0.1f);  // 기둥 크기 (얇은 원기둥)
    glutSolidCube(1.0f); // 큐브로 기둥 표현
    glPopMatrix();

    // 전구  (구체)
    GLfloat bulbColor[] = { 1.0f, 1.0f, 0.5f, 1.0f }; // 노란색
    glMaterialfv(GL_FRONT, GL_AMBIENT, bulbColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, bulbColor);
    glPushMatrix();
    glTranslatef(4.0f, 1.0f, -3.0f); // 기둥 위로 이동
    glutSolidSphere(0.5f, 20, 20);  // 전구  (구체)
    glPopMatrix();

}

//책
void drawBook() {
    glPushMatrix();
    GLfloat matAmbient[] = { 0.4f, 0.2f, 0.6f, 1.0f }; // 보라색 계열
    GLfloat matDiffuse[] = { 0.5f, 0.3f, 0.7f, 1.0f }; //확산광 반사색 밝은 보라
    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);

    // 여러 개의 책을 세로로 세워두기
    for (int i = 0; i < 5; ++i) {
        glPushMatrix();
        glTranslatef(i * 0.4f - 4.5f, 0.5f, -2.0f); // 위치 조정
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // 책을 세로로 세움
        glScalef(0.2f, 1.2f, 1.8f); // 책 크기 
        glutSolidCube(1.0f); // 책 생성
        glPopMatrix();
    }
    glPopMatrix();
}

//책 표지
void drawBookName() {
    glPushMatrix();
    GLfloat matAmbient[] = { 0.4f, 0.4f, 0.4f, 1.0f }; // 회색
    GLfloat matDiffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f }; //확산광 반사색
    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);

    // 여러 개
    for (int i = 0; i < 5; ++i) {
        glPushMatrix();
        glTranslatef(i * 0.4f - 4.41f, 0.9f, -2.0f); // 위치 조정
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // 세로로 세움
        glScalef(0.05f, 0.8f, 0.5f); //크기 
        glutSolidCube(1.0f); //생성
        glPopMatrix();
    }
    glPopMatrix();
}

// 컴퓨터 
void drawComputer() {
    glPushMatrix();

    // 모니터 기둥
    GLfloat standColor[] = { 0.5f, 0.5f, 0.5f, 1.0f }; // 색
    glMaterialfv(GL_FRONT, GL_AMBIENT, standColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, standColor);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -2.0f);  // 기둥 위치
    glScalef(0.2f, 1.0f, 0.2f);  // 기둥 크기 
    glutSolidCube(1.0f); // 큐브로 기둥 표현
    glPopMatrix();

    // 모니터 화면 (디스플레이 부분)
    glEnable(GL_TEXTURE_2D);  // 텍스처 매핑 활성화
    glBindTexture(GL_TEXTURE_2D, textures[1]);  // plave.jpg 텍스처 바인딩
    glPushMatrix();
    glTranslatef(0.0f, 1.5f, -1.9f);  // 위치
    glScalef(1.0f, 1.0f, 0.1f);  // 화면 크기

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.5f, -1.0f, 0.0f);  // 좌하단
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.5f, -1.0f, 0.0f);   // 우하단
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.5f, 1.0f, 0.0f);    // 우상단
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.5f, 1.0f, 0.0f);   // 좌상단
    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);  // 텍스처 매핑 비활성화


    // 모니터 테두리 (은색)
    GLfloat borderColor[] = { 0.7f, 0.7f, 0.7f, 1.0f }; // 은색 테두리
    glMaterialfv(GL_FRONT, GL_AMBIENT, borderColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, borderColor);
    glPushMatrix();
    glTranslatef(0.0f, 1.5f, -2.0f);  // 위치
    glScalef(3.1f, 2.1f, 0.1f);  // 테두리 크기 (모니터보다 살짝 큼)
    glutSolidCube(1.0f); // 큐브로 테두리 표현
    glPopMatrix();

    // 키보드
    GLfloat keyboardColor[] = { 0.4f, 0.4f, 0.4f, 1.0f }; // 회색
    glMaterialfv(GL_FRONT, GL_AMBIENT, keyboardColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, keyboardColor);
    glPushMatrix();
    glTranslatef(0.0f, -0.2f, 0.6f);  // 키보드 위치
    glScalef(2.8f, 0.1f, 1.0f);  // 키보드 크기
    glutSolidCube(1.0f); // 큐브로 키보드 표현
    glPopMatrix();

    // 키보드 키들
    GLfloat keyColor[] = { 0.1f, 0.1f, 0.1f, 1.0f }; // 키보드 키 색상
    glMaterialfv(GL_FRONT, GL_AMBIENT, keyColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, keyColor);
    float keyWidth = 0.18f, keyHeight = 0.05f, keyDepth = 0.1f;

    // 키보드 키들을 4x10 배열로 생성 (약 4줄의 키)
    float xOffset = -1.1f, yOffset = -0.1f, zOffset = 0.24f;

    // 키 간의 간격을 적당히 좁혀서 키가 키보드 내에 잘 맞도록 조정
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 10; ++col) {
            glPushMatrix();
            glTranslatef(xOffset + col * 0.25f, yOffset, zOffset + row * 0.22f);  // 키 간의 간격 조정
            glScalef(keyWidth, keyHeight, keyDepth);  // 키 크기
            glutSolidCube(1.0f); // 큐브로 키 표현
            glPopMatrix();
        }
    }
    glPopMatrix();
}

// 알람시계 
void drawClock(float Angle) {
    GLUquadric* quad = gluNewQuadric(); 

    // 시계 본체
    GLfloat bodyColor[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, bodyColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, bodyColor);
    glPushMatrix();
    glTranslatef(2.6f, 0.3f, -0.9f);
    gluDisk(quad, 0.0f, 0.5f, 50, 1);  // 원형 디스크
    glPopMatrix();

    // 원기둥을 사용하여 시계 두께 추가
    GLfloat bodyCylinderColor[] = { 1.0f, 0.0f, 0.0f, 1.0f }; // 빨간색
    glMaterialfv(GL_FRONT, GL_AMBIENT, bodyCylinderColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, bodyCylinderColor);
    glPushMatrix();
    glTranslatef(2.6f, 0.3f, -0.9f);  // 원기둥 위치
    gluCylinder(quad, 0.5f, 0.5f, 0.2f, 50, 10);  // 원기둥
    glPopMatrix();

    //초침 
    GLfloat minuteHandColor[] = { 0.0f, 0.0f, 0.0f, 1.0f }; // 검정색
    glMaterialfv(GL_FRONT, GL_AMBIENT, minuteHandColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, minuteHandColor);
    glPushMatrix();
    glTranslatef(2.6f, 0.3f, -0.89f);
    glRotatef(Angle, 0.0f, 0.0f, 1.0f);  //z축 중심 회전
    glScalef(0.02f, 0.32f, 0.02f);
    glutSolidCube(1.0f);  // 초침
    glPopMatrix();

    // 알람시계 종 모양 추가 (양쪽에 위치)
    GLfloat bellColor[] = { 1.0f, 0.5f, 0.0f, 1.0f }; // 노랑색
    glMaterialfv(GL_FRONT, GL_AMBIENT, bellColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, bellColor);

    // 왼쪽 종
    glPushMatrix();
    glTranslatef(2.2f, 0.7f, -0.9f); // 왼쪽 종 위치
    glScalef(0.42f, 0.42f, 0.42f);
    glutSolidSphere(0.3f, 20, 20);  // 종
    glPopMatrix();

    // 오른쪽 종
    glPushMatrix();
    glTranslatef(3.0f, 0.7f, -0.9f); // 오른쪽 종 위치
    glScalef(0.42f, 0.42f, 0.42f);
    glutSolidSphere(0.3f, 20, 20);  // 종
    glPopMatrix();

    // 종을 두드리는 망치 (가운데)
    GLfloat hammerColor[] = { 1.0f, 0.5f, 0.0f, 1.0f }; 
    glMaterialfv(GL_FRONT, GL_AMBIENT, hammerColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, hammerColor);
    glPushMatrix();
    glTranslatef(2.6f, 0.9f, -0.8f); // 망치 위치
    glScalef(0.05f, 0.12f, 0.05f);  //  망치
    glutSolidCube(1.0f);
    glPopMatrix();
}

// 초침 각도 계산
float calculateAngle() {
    static float angle = 0.0f;
    angle += 0.5f; // 초침 1초당 0.5도씩 회전
    if (angle >= 360.0f) angle -= 360.0f;  //한 바퀴 돌면 다시 0도
    return angle;
}

// 타이머 함수
void timer(int value) {
    glutPostRedisplay();    //현재 프레임 다시 그리기
    glutTimerFunc(100, timer, 0);   //0.1초 후에 timer함수 다시 호출
}

//컵
void drawCup() {
    glPushMatrix();

    // 컵 본체 (원기둥)
    GLfloat cupColor[] = { 0.2f, 0.28f, 0.22f, 1.0f }; // 초록
    glMaterialfv(GL_FRONT, GL_AMBIENT, cupColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cupColor);
    glTranslatef(-2.5f, -0.3f, 2.0f); // 위치 
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // 원기둥 세움
    glScalef(0.3f, 0.3f, 0.3f); // 크기 

    GLUquadric* quad = gluNewQuadric();
    gluCylinder(quad, 1.0, 1.0, 2.2, 32, 32);

    // 컵 손잡이 
    glPushMatrix();
    glTranslatef(-1.0f, -0.2f, 1.0f); // 손잡이 위치 조정
    glRotatef(90.0f, 90.0f, 1.0f, 0.0f); // 손잡이 회전
    glutSolidTorus(0.2, 0.5, 32, 32); // 토러스 
    glPopMatrix();

    // 컵의 윗부분 (커피)
    GLfloat coffeeColor[] = { 0.33f, 0.15f, 0.05f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, coffeeColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, coffeeColor);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1.7f); // 위치
    gluDisk(quad, 0.0, 1.0, 32, 32); //  원판
    glPopMatrix();

    gluDeleteQuadric(quad); 
    glPopMatrix();
}


// 텍스트 렌더링 함수
void renderBitmapString(float x, float y, float z, const char* string) {
    glRasterPos3f(x, y, z);
    while (*string) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string);
        string++;
    }
}

// 도움말 메시지 표시
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

// 장면 렌더링 함수
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 카메라 설정
    glLoadIdentity();
    gluLookAt(cameraDistance * sin(cameraAngleX * M_PI / 180.0f), 5.0f, cameraDistance * cos(cameraAngleX * M_PI / 180.0f),
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f);

    // 장면 렌더링
    drawTable();
    drawLamp();
    drawBook();
    drawBookName();
    drawComputer();
    drawCup();
    drawClock(calculateAngle());
    
    // 도움말 표시
    displayHelp();

    glutSwapBuffers();
}

// 창 크기 변경 처리
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w / h, 1.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

// 키보드 입력 처리 함수
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w': // 카메라 앞으로 이동
        cameraDistance -= 1.0f;
        if (cameraDistance < 5.0f) cameraDistance = 5.0f; // 너무 가까이 가지 않게 제한
        break;
    case 's': // 카메라 뒤로 이동
        cameraDistance += 1.0f;
        break;
    case 'a': // 카메라 왼쪽으로 회전
        cameraAngleX -= 5.0f;
        break;
    case 'd': // 카메라 오른쪽으로 회전
        cameraAngleX += 5.0f;
        break;
    case 'h': // 도움말 표시
        showHelp = !showHelp;
        break;
    case 27: // ESC 키로 종료
        exit(0);
    }
    glutPostRedisplay(); // 화면 갱신 요청
}

// 메인 함수
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("202204167 황신영");

    init();
    Textures();  // 텍스처 로드

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(100, timer, 0);
    glutMainLoop();

    return 0;
}