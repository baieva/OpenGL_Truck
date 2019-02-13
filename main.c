//
//  main.c
//  Truck
//
//  Created by Mingjia Shi 104467237 on 2018/2/11.
//  Copyright © 2018年 Mingjia Shi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/OpenGL.h>
#include <math.h>

typedef void (*GLUTdisplayCB) (void);

void myInit(int *, char **, GLUTdisplayCB);
void SpecialInput(int,int,int,int);
void carMoving(void);
void initializeTruck(void);
void initializeRoad(void);
void createGlutMenu(void);
void menu(int);
void changeDire(void);

int carStarted = -1;
int speed = 1;
int direction = 1;
int x = 10;
int cx = 25;
double cd = 0;

int main(int argc, char ** argv) {
    
    myInit(&argc, argv, carMoving);
    
    initializeTruck();
    initializeRoad();
    
    glutMainLoop();
    return 0;
}

void myInit(int *argc, char ** argv,GLUTdisplayCB displayFunc) {
    glutInit(argc,argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100,150);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow(argv[0]);
    
    glutDisplayFunc(displayFunc);
    
    glClearColor(1.0,1.0,1.0,0.0);
    
    glColor3f(((float) 222)/((float) 255.0), ((float) 222)/((float) 255.0), ((float) 222)/((float) 255.0));
    glPointSize(9.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
    
    glutMouseFunc(SpecialInput);
    createGlutMenu();
}

void carMoving() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(carStarted > 0){
        x+=speed;
        cx+=speed;
        cd+=(M_PI/6 * speed);
    }
    initializeTruck();
    initializeRoad();
}

void initializeTruck() {
    if(direction > 0){
        glBegin(GL_POLYGON);
        glVertex2i(x, 30);
        glVertex2i(x+50, 30);
        glVertex2i(x+50, 60);
        glVertex2i(x, 60);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2i(x+50, 30);
        glVertex2i(x+70, 30);
        glVertex2i(x+70, 40);
        glVertex2i(x+60, 50);
        glVertex2i(x+50, 50);
        glEnd();
    }
    else{
        glBegin(GL_POLYGON);
        glVertex2i(x + 70, 30);
        glVertex2i(x+20, 30);
        glVertex2i(x+20, 60);
        glVertex2i(x + 70, 60);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2i(x+20, 30);
        glVertex2i(x, 30);
        glVertex2i(x, 40);
        glVertex2i(x+10, 50);
        glVertex2i(x+20, 50);
        glEnd();
    }
    glBegin(GL_POLYGON);
    glVertex2i(5 * cos(cd) + cx, 25 + 5 * sin(cd));
    glVertex2i(5 * cos(cd + M_PI/3) + cx, 25 + 5 * sin(cd + M_PI/3));
    glVertex2i(5 * cos(cd + 2 * M_PI/3) + cx, 25 + 5 * sin(cd + 2 * M_PI/3));
    glVertex2i(5 * cos(cd + M_PI) + cx, 25 + 5 * sin(cd + M_PI));
    glVertex2i(5 * cos(cd + 4 * M_PI/3) + cx, 25 + 5 * sin(cd + 4 * M_PI/3));
    glVertex2i(5 * cos(cd + 5 * M_PI/3) + cx, 25 + 5 * sin(cd + 5 * M_PI/3));
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(5 * cos(cd) + cx + 40, 25 + 5 * sin(cd));
    glVertex2i(5 * cos(cd + M_PI/3) + cx + 40, 25 + 5 * sin(cd + M_PI/3));
    glVertex2i(5 * cos(cd + 2 * M_PI/3) + cx + 40, 25 + 5 * sin(cd + 2 * M_PI/3));
    glVertex2i(5 * cos(cd + M_PI) + cx + 40, 25 + 5 * sin(cd + M_PI));
    glVertex2i(5 * cos(cd + 4 * M_PI/3) + cx + 40, 25 + 5 * sin(cd + 4 * M_PI/3));
    glVertex2i(5 * cos(cd + 5 * M_PI/3) + cx + 40, 25 + 5 * sin(cd + 5 * M_PI/3));
    glEnd();
    glFlush();
    glutPostRedisplay();
}

void initializeRoad() {
    glBegin(GL_LINES);
    glVertex2i(0, 10);
    glVertex2i(640, 10);
    glEnd();
    glFlush();
    
}

void createGlutMenu() {
    glutCreateMenu(menu);
    glutAddMenuEntry("Speed UP",1);
    glutAddMenuEntry("Slow Down", 2);
    glutAddMenuEntry("Change Dire", 3);
    glutAddMenuEntry("Exit", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void menu(int value){
    if(value == 1){
        speed++;
    }
    else if(value == 2) {
        if(speed > 0) speed--;
    }
    else if(value == 3) {
        changeDire();
    }
    else if(value == 4){
        exit(0);
    }
}

void changeDire() {
    direction = -direction;
    speed = -speed;
}

void SpecialInput(int button,int state,int x, int y) {
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        carStarted = -carStarted;
    }
}
