#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdio.h>
#include <vector>

#include "Point2d.h"
#include "bezier.h"

int left = 0, right = 500, bot = 0, top = 500;

int move_step = 1;
float scale = 1;

std::vector<Point2d*> points;
std::vector<Point2d*> bezier_points;

std::vector<int> get_axis(std::vector<Point2d*> & points, int axis){
    std::vector<int> axis_points;
    for (size_t i = 0; i < points.size(); i++)
    {
        axis_points.push_back((axis == 0) ? points[i]->x : points[i]->y);
    }
    return axis_points;
    
}

void mouseEvent(int button, int state, int x, int y){
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
        y = abs(y-500);
        points.push_back(new Point2d(x, y));
        // printf("%i %i \n", x, y);
        std::vector<int> x_axis = get_axis(points, 0);
        std::vector<int> y_axis = get_axis(points, 1);
        print_list(x_axis);
        print_list(y_axis);
        int _x, _y;
        if (points.size() <2 ) return;
        bezier_points.clear();
        for (double i = 0; i < 1; i+=0.004)
        {
            _x = bezier(points.size()-1, i, x_axis);
            _y = bezier(points.size()-1, i, y_axis);
            printf("%i %i \n", _x, points.size());
            bezier_points.push_back(new Point2d(_x, _y));
        }
    }


    
    glutPostRedisplay();
}

void display(){

    //Set Points
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glPointSize(3);
    glBegin(GL_POINTS);
        for (size_t i = 0; i < points.size(); i++)
        {
            glVertex2i(points[i]->x, points[i]->y);
        }
    glEnd();

    //Draw things
    //inc_line(p1,p2);
    glBegin(GL_POINTS);
        for (size_t i = 0; i < bezier_points.size(); i++)
        {
            glVertex2i(bezier_points[i]->x, bezier_points[i]->y);
        }
        
    glEnd();

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

    // glutKeyboardFunc(keyboard);
    // glutKeyboardUpFunc(keyboard_up);
    // glutSpecialFunc(special_keyboard);
    // glutSpecialUpFunc(special_keyboard_up);
    // glutIdleFunc(keys_scanner);

    glutMouseFunc(mouseEvent);

    glutMainLoop();
}

