#include <cmath>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <GL/gl.h>
#include <GL/glut.h>

#include "arcball.h"
#include <placement3d.h>

using namespace std;

const double MARGIN = 0.9;
const int WIDTH = 600, HEIGHT = 600;

Solution solution;
int maxRange;
double scaleRatio;
ArcBall* arcBall = new ArcBall(WIDTH, HEIGHT);

char *inFile = 0, *outFile = 0;
bool _help, _s, _p;

void reshape(int w, int h)
{
    int s = min(w, h);
    glViewport((w - s) / 2, (h - s) / 2, s, s);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    arcBall->setBounds(w, h);
}

double trans(double x)
{
    return x / scaleRatio - 0.4;
}

void drawAixs()
{
    double trans0 = trans(0);
    double trans1 = trans(maxRange / MARGIN);
    glBegin(GL_LINES);
        // X
        glColor3f(1, 0, 0);
        glVertex3f(trans0, trans0, trans0);
        glVertex3f(trans1, trans0, trans0);
        // Y
        glColor3f(0, 1, 0);
        glVertex3f(trans0, trans0, trans0);
        glVertex3f(trans0, trans1, trans0);
        // Z
        glColor3f(0, 0, 1);
        glVertex3f(trans0, trans0, trans0);
        glVertex3f(trans0, trans0, trans1);
    glEnd();
}

/**
           z
           |
           |        x
           |      /
           |    /
           |  /
           |/
y _________O
*/
void drawBoxEdges(const PlacedBox& box)
{
    double x1 = trans(box.x), y1 = trans(box.y), z1 = trans(box.z);
    double x2 = trans(box.x2), y2 = trans(box.y2), z2 = trans(box.z2);

    // Draw edges
    glColor3f(0, 0, 0);
    // Down
    glBegin(GL_LINE_LOOP);
        glVertex3f(x1, y1, z1);
        glVertex3f(x2, y1, z1);
        glVertex3f(x2, y2, z1);
        glVertex3f(x1, y2, z1);
    glEnd();
    // Up
    glBegin(GL_LINE_LOOP);
        glVertex3f(x1, y1, z2);
        glVertex3f(x2, y1, z2);
        glVertex3f(x2, y2, z2);
        glVertex3f(x1, y2, z2);
    glEnd();
    // Left
    glBegin(GL_LINE_LOOP);
        glVertex3f(x1, y1, z1);
        glVertex3f(x1, y2, z1);
        glVertex3f(x1, y2, z2);
        glVertex3f(x1, y1, z2);
    glEnd();
    // Right
    glBegin(GL_LINE_LOOP);
        glVertex3f(x2, y1, z1);
        glVertex3f(x2, y2, z1);
        glVertex3f(x2, y2, z2);
        glVertex3f(x2, y1, z2);
    glEnd();
    // Front
    glBegin(GL_LINE_LOOP);
        glVertex3f(x1, y1, z1);
        glVertex3f(x2, y1, z1);
        glVertex3f(x2, y1, z2);
        glVertex3f(x1, y1, z2);
    glEnd();
    // Back
    glBegin(GL_LINE_LOOP);
        glVertex3f(x1, y2, z1);
        glVertex3f(x2, y2, z1);
        glVertex3f(x2, y2, z2);
        glVertex3f(x1, y2, z2);
    glEnd();
}

void drawBoxFaces(const PlacedBox& box)
{
    double x1 = trans(box.x), y1 = trans(box.y), z1 = trans(box.z);
    double x2 = trans(box.x2), y2 = trans(box.y2), z2 = trans(box.z2);

    // Draw faces
    glColor4f(0.6, 0.6, 0.6, 0.7);
    glBegin(GL_QUADS);
        // Down
        glVertex3f(x1, y1, z1);
        glVertex3f(x2, y1, z1);
        glVertex3f(x2, y2, z1);
        glVertex3f(x1, y2, z1);
        // Up
        glVertex3f(x1, y1, z2);
        glVertex3f(x2, y1, z2);
        glVertex3f(x2, y2, z2);
        glVertex3f(x1, y2, z2);
        // Left
        glVertex3f(x1, y1, z1);
        glVertex3f(x1, y2, z1);
        glVertex3f(x1, y2, z2);
        glVertex3f(x1, y1, z2);
        // Right
        glVertex3f(x2, y1, z1);
        glVertex3f(x2, y2, z1);
        glVertex3f(x2, y2, z2);
        glVertex3f(x2, y1, z2);
        // Front
        glVertex3f(x1, y1, z1);
        glVertex3f(x2, y1, z1);
        glVertex3f(x2, y1, z2);
        glVertex3f(x1, y1, z2);
        // Back
        glVertex3f(x1, y2, z1);
        glVertex3f(x2, y2, z1);
        glVertex3f(x2, y2, z2);
        glVertex3f(x1, y2, z2);
    glEnd();
}

void setBlend()
{
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH, GL_NICEST);

    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH, GL_NICEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void display()
{
    glClearColor(1, 1, 1, 0);
    glEnable (GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    setBlend();

    glLoadIdentity();
    gluLookAt(0, -2, 0,  0, 0, 0,  0, 0, 1);
    glScalef(arcBall->zoomRate, arcBall->zoomRate, arcBall->zoomRate);
    glMultMatrixf(arcBall->Transform.M);

    glLineWidth(2);
    drawAixs();

    for (auto i = solution.BoxesBegin(); i != solution.BoxesEnd(); i++)
        drawBoxEdges(*i);

    glDepthMask(GL_FALSE);
    for (auto i = solution.BoxesBegin(); i != solution.BoxesEnd(); i++)
        drawBoxFaces(*i);
    glDepthMask(GL_TRUE);

    glFlush();
    glutSwapBuffers();
}

int getArgs(int argc, char* argv[])
{
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            if (!strcmp(argv[i], "--help")) _help = true;
            else if (!strcmp(argv[i], "-s") || !strcmp(argv[i], "-p") || !strcmp(argv[i], "-o"))
            {
                if (i+1 == argc)
                {
                    printf("ERROR: missing filename after '%s'", argv[i]);
                    return 1;
                }
                if (!strcmp(argv[i], "-o"))
                    outFile = argv[++i];
                else
                {
                    if (!strcmp(argv[i], "-s"))
                        _s = true;
                    else
                        _p = true;
                    inFile = argv[++i];
                }
            }
        }
        else
        {
            printf("ERROR: unrecognized command line option '%s'\n", argv[i]);
            return 1;
        }
    }
    return 0;
}

///  Mouse dragging
void mouseMoveEvent(int x,int y)
{
    arcBall->MousePt.s.X = x;
    arcBall->MousePt.s.Y = y;
    arcBall->upstate();
    glutPostRedisplay();
}

/// Mouse events (clicks and wheel up/down)
void mouseEvent(int button, int state, int x, int y)
{
    if (button == 3) arcBall->zoomIn(1.1);                      // Wheel up
    else if (button == 4) arcBall->zoomOut(1.1);                // Wheel down
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        arcBall->isClicked = true;
        mouseMoveEvent(x,y);
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
        arcBall->isClicked = false;

    arcBall->upstate();
    glutPostRedisplay();
}

int init(int argc, char* argv[])
{
    if (getArgs(argc, argv)) return 1;
    if (!inFile || _help)
    {
        printf("Usage: %s [OPTIONS]\n"
               "OPTIONS:\n"
               "  --help          Show this information\n"
               "  -s <file>       Load a placement solution from <file>\n"
               "  -p <file>       Load an unsolved placement problem from <file>\n"
               "  -o <file>       Save the placement solution into <file> (with -p option)\n", argv[0]);
        return 1;
    }

    srand(time(0));
    if (_p)
    {
        BoxList boxes = Box::LoadBoxesFromFile(inFile);

        Placement3D* p3d = new Placement3D(boxes);
		p3d->SetDebug();
        solution = p3d->GetSolution();
        delete p3d;

        if (outFile) solution.SaveToFile(outFile);
    }
    else
        solution = Solution::LoadSolutionFromFile(inFile);

    bool valid = solution.Check();
    printf("Checking validity: %s\n", valid ? "OK" : "INVALID");
    if (!valid) puts("WARNING: solution is INVALID");

    Box boundingBox = solution.GetBoundingBox();
    printf("Total number of boxes: %d\n", solution.Size());
    printf("Total volume of boxes: %d\n", solution.GetBoxesVolume());
    printf("Volume of bounding box: %d\n", solution.GetBoundingBoxVolume());
    printf("Wasted volume: %d\n", solution.GetWastedVolume());
    printf("Wasted volume ratio: %.3lf%%\n", solution.GetWastedVolumeRatio() * 100);

    maxRange = max(max(boundingBox.l, boundingBox.w), boundingBox.h);
    scaleRatio = maxRange / MARGIN;

    return 0;
}

int main(int argc, char* argv[])
{
    if (init(argc, argv)) return 1;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Placement 3D demo");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouseEvent);
    glutMotionFunc(mouseMoveEvent);
    glutMainLoop();

    return 0;
}
