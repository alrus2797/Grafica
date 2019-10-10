#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdio.h>
#include <vector>

#include "Poligon2d.h"
#include "Circle2d.h"

#include "Axis2d.h"

int left = -500, right = 500, bot = -500, top = 500;

Poligon2d rombus({
        {0  , 250},
        {250, 0},
        {500, 250},
        {250, 500},
    });
Circle2d circle(Point2d(0,0), 100);
int move_step = 1;
float scale = 1;

bool key_pressed[256];

bool special_key_pressed[256];

void keyboard(unsigned char key, int x, int y){
    // switch (key)
    // {
    // case 'a':
    //     printf("Hey\n");
    //     break;
    // case 'b':
    //     printf("Hey2\n");
    //     break;
    // case '+':
    //     printf("Curr step %i: ", move_step);
    //     move_step++;
    //     break;
    // case '-':
    //     printf("Curr step %i: ", move_step);
    //     move_step--;
    //     break;
    
    // default:
    //     break;
    // }

    // glutPostRedisplay();

    key_pressed[key] = true;
}

void keyboard_up(unsigned char key, int x, int y){
    key_pressed[key] = false;
}

void special_keyboard(int key, int x, int y){
    // switch (key)
    // {
    // case GLUT_KEY_LEFT:
    //     rombus.move(-move_step,0);
    //     break;
    // case GLUT_KEY_RIGHT:
    //     rombus.move(move_step,0);
    //     break;
    // case GLUT_KEY_UP:
    //     rombus.move(0, move_step);
    //     break;
    // case GLUT_KEY_DOWN:
    //     rombus.move(0, -move_step);
    //     break;
    // case glut_key_
    // default:
    //     break;
    // }

    // glutPostRedisplay();

    special_key_pressed[key] = true;
}

void special_keyboard_up(int key, int x, int y){
    special_key_pressed[key] = false;
}

void keys_scanner(){
    if (special_key_pressed[GLUT_KEY_LEFT])
        rombus.move(-move_step,0);
    else if (special_key_pressed[GLUT_KEY_RIGHT])
        rombus.move(move_step,0);
    else if (special_key_pressed[GLUT_KEY_UP])
        rombus.move(0, move_step);
    else if (special_key_pressed[GLUT_KEY_DOWN])
        rombus.move(0, -move_step);

    else if (key_pressed['+']){
        move_step++;
        printf("Curr move step: %i \n", move_step);
    }
    else if (key_pressed['-']){
        move_step--;
        printf("Curr move step: %i \n", move_step);
    }
    else if (key_pressed['q']){
        scale *= 2;
        printf("Curr scale: %.3f \n", scale);
        rombus.scale(2, 2);
    }
    else if (key_pressed['w']){
        scale /= 2;
        printf("Curr scale: %.3f \n", scale);
        rombus.scale(0.5, 0.5);
    }
    else if (key_pressed['a']){
        rombus.rotate(-45);
    }
    else if (key_pressed['s']){
        rombus.rotate(45);
    }



    for (size_t i = 0; i < 256; i++)
    {
        key_pressed[i] = 0;
        special_key_pressed[i] = 0;
    }
    
    glutPostRedisplay();
}

void display(){
    //Set Axis

    Axis2d axis(left, right, bot, top);

  

    //Set Points
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();


    rombus.draw();
    // circle.basic_octant_draw();

    axis.draw();

    //Draw things
    //inc_line(p1,p2);

    glFlush();
}
void reshape(int width, int heigth){
    glViewport(0, 0, (GLsizei)width, (GLsizei)heigth);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluOrtho2D(left, right, bot, top);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv){
    glutInit(& argc, argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition(200,100);
    glutInitWindowSize(500,500);

    glutCreateWindow("Hello 2D");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glClearColor(0, 0, 0, 1);

    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboard_up);
    glutSpecialFunc(special_keyboard);
    glutSpecialUpFunc(special_keyboard_up);
    glutIdleFunc(keys_scanner);

    glutMainLoop();
}

