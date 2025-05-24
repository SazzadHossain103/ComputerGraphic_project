#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

struct Window {
    float x, y, width, height;
    bool isLightOn;
};

struct Building {
    float x, y;
    int floors;
    float width;
    vector<Window> windows;
};

vector<Building> buildings;
int buildingID = 0;
const float floorHeight = 6;
const float buildingWidth = 21;
const float windowWidth = 3;
const float windowHeight = 3;
const float doorHeight = 6;
const float doorWidth = 4;

bool isDay = true;
float cloud1X = 0;
float cloud2X = -50;
float cloud1Y = 70;
float cloud2Y = 67;

float carX = 0.0f;
float carY = 0.0f;


// --------------------------------------------------------------------------------------------------------------------------------------------------------------------

void addBuilding(float x, float y, int floors) {
    Building b;
    b.x = x;
    b.y = y;
    b.floors = floors;
    b.width = buildingWidth;

    // windows per floor
    for (int floor = 2; floor <= floors; floor++) {
        float winY = y + floor * floorHeight - 4;
        for (int i = 0; i < 3; ++i) {
            float winX = x + 3 + i * (windowWidth + 3);
            b.windows.push_back({winX, winY, windowWidth, windowHeight, true});
        }
    }

    buildings.push_back(b);
}


void drawBuildings() {
    for (auto &b : buildings) {
        // Draw buildin
        glColor3f(0.6f, 0.4f, 0.2f);
        glBegin(GL_POLYGON);
            glVertex2f(b.x, b.y);
            glVertex2f(b.x + b.width, b.y);
            glVertex2f(b.x + b.width, b.y + b.floors * 6);
            glVertex2f(b.x, b.y + b.floors * 6);
        glEnd();

        // Draw door
        glColor3f(0.3f, 0.2f, 0.1f);
        glBegin(GL_POLYGON);
            glVertex2f(b.x + b.width / 2 - (doorWidth / 2), b.y);
            glVertex2f(b.x + b.width / 2 + (doorWidth / 2), b.y);
            glVertex2f(b.x + b.width / 2 + (doorWidth / 2), b.y + doorHeight);
            glVertex2f(b.x + b.width / 2 - (doorWidth / 2), b.y + doorHeight);
        glEnd();
    }
}

void drawWindows() {
    for (auto &b : buildings) {
        for (auto &w : b.windows) {
            if (isDay) glColor3f(0.9f, 0.95f, 1.0f); // sky blue
            else { // night
                if (w.isLightOn) glColor3f(1.0f, 1.00f, 0.6f); // Bright yellow - light on
                else glColor3f(0.005f, 0.005f, 0.05f); // nearly black - light off
            }

            glBegin(GL_POLYGON);
                glVertex2f(w.x, w.y);
                glVertex2f(w.x + w.width, w.y);
                glVertex2f(w.x + w.width, w.y + w.height);
                glVertex2f(w.x, w.y + w.height);
            glEnd();
        }
    }
}


// --------------------------------------------------------------------------------------------------------------------------------------------------------------------
void drawSky() {
    if (isDay) glColor3f(0.53f, 0.81f, 0.98f); // light blue
    else glColor3f(0.05f, 0.05f, 0.2f); // dark night

    glBegin(GL_POLYGON);
        glVertex2f(0, 40);
        glVertex2f(150, 40);
        glVertex2f(150, 80);
        glVertex2f(0, 80);
    glEnd();
}

void drawSun() {
    float cx = 135, cy = 70, r = 5;
    if (isDay) glColor3f(1.0f, 1.0f, 0.0f); // yellow sun
    else glColor3f(0.9f, 0.9f, 0.9f); // pale gray moon

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (int i = 0; i <= 100; i++) {
            float angle = 2.0f * 3.1416f * i / 100;
            glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
        }
    glEnd();
}

void drawCloud(float x, float y) {
    // cloud overlapping the sun or not. horizontally
    bool aboveSun = isDay && (x + 13 > 130 && x < 143);

    if (aboveSun) glColor3f(1.0f, 0.6f, 0.6f); // reddish white
    else glColor3f(1.0f, 1.0f, 1.0f); // normal white

    float r = 3.0f;
    for (int i = 0; i < 5; i++) {
        float cx = x + i * 2.5f;
        float cy = y;
        if (i & 1) cy = y - 2.5f; // lower circle
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(cx, cy);
            for (int j = 0; j <= 100; j++) {
                float angle = 2 * 3.1416f * j / 100;
                glVertex2f(cx + r * cos(angle), cy + r * sin(angle));

            }
        glEnd();
    }
}

void updateClouds(int) {
    cloud1X += 0.2f;
    cloud2X += 0.15f;

    if (cloud1X > 160) cloud1X = -30;
    if (cloud2X > 160) cloud2X = -30;

    glutPostRedisplay();
    glutTimerFunc(30, updateClouds, 0);
}


// --------------------------------------------------------------------------------------------------------------------------------------------------------------------

void drawRoad() {
    glColor3f(0.3f, 0.3f, 0.3f); // gray
    glBegin(GL_POLYGON);
        glVertex2f(0, 0);
        glVertex2f(0, 20);
        glVertex2f(150, 20);
        glVertex2f(150, 0);
    glEnd();

    // lane dividers
     glColor3f(1.0f, 1.0f, 1.0f); // white
    for (float i = 0; i < 150; i += 20) {
        glBegin(GL_POLYGON);
            glVertex2f(i, 9.5);         // centered vertically in road
            glVertex2f(i + 8, 9.5);
            glVertex2f(i + 8, 10.5);
            glVertex2f(i, 10.5);
        glEnd();
    }
}


void drawWheel(float cx, float cy, float r) {
    int num_segments = 100;
    glColor3f(0.0f, 0.0f, 0.0f); // black
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (int i = 0; i <= num_segments; i++) {
            float theta = 2.0f * 3.1416f * i / num_segments;
            float x = r * cos(theta);
            float y = r * sin(theta);
            glVertex2f(cx + x, cy + y);
        }
    glEnd();
}

void drawCar() {
    // Car body
    glColor3f(0.9f, 0.0f, 0.0f); // red
    glBegin(GL_POLYGON);
        glVertex2f(43.4f + carX, 14.7f + carY);
        glVertex2f(61.6f + carX, 14.7f + carY);
        glVertex2f(61.6f + carX, 19.6f + carY);
        glVertex2f(43.4f + carX, 19.6f + carY);
    glEnd();

    // Car roof
    glColor3f(0.8f, 0.0f, 0.0f); // darker red
    glBegin(GL_POLYGON);
        glVertex2f(46.9f + carX, 19.6f + carY);
        glVertex2f(58.1f + carX, 19.6f + carY);
        glVertex2f(55.3f + carX, 23.1f + carY);
        glVertex2f(49.7f + carX, 23.1f + carY);
    glEnd();

    // Wheels
    drawWheel(47.6f + carX, 14.0f + carY, 2.1f); // left wheel
    drawWheel(57.4f + carX, 14.0f + carY, 2.1f); // right wheel
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------

void mouseClick(int button, int state, int x, int y) {
    if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN) return;

    // Convert screen to OpenGL coordinates
    float worldX = (float)x / glutGet(GLUT_WINDOW_WIDTH) * 150;
    float worldY = (float)(glutGet(GLUT_WINDOW_HEIGHT) - y) / glutGet(GLUT_WINDOW_HEIGHT) * 80;

    // Check if clicked on sun/moon
    float sunX = 135, sunY = 75, sunRadius = 5;
    float distSquared = (worldX - sunX)*(worldX - sunX) + (worldY - sunY)*(worldY - sunY);
    if (distSquared <= sunRadius * sunRadius) {
        isDay ^= true;
        glutPostRedisplay();
        return;
    }

    if (!isDay) {
        for (auto &b : buildings) {
            for (auto &w : b.windows) {
                if (worldX >= w.x && worldX <= w.x + w.width &&
                    worldY >= w.y && worldY <= w.y + w.height) {
                    w.isLightOn ^= true;
                    glutPostRedisplay();
                    return;
                }
            }
        }
    }


}

void keyboard(int key, int x, int y) {
    float step = 1.0f;

    if (key == GLUT_KEY_LEFT) {
        if (43.4f + carX > 0)
            carX -= step;
    }
    else if (key == GLUT_KEY_RIGHT) {
        if (61.6f + carX < 150)
            carX += step;
    }
    else if (key == GLUT_KEY_UP) {
        if (17.0f + carY < 20)
            carY += step;
    }
    else if (key == GLUT_KEY_DOWN) {
        if (11.9f + carY > 0)
            carY -= step;
    }

    glutPostRedisplay();
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawSky();
    drawSun();
    drawCloud(cloud1X, cloud1Y);
    drawCloud(cloud2X, cloud2Y);

    drawBuildings();
    drawWindows();

    drawRoad();
    drawCar();

    glFlush();
}

void precalculation() {
    addBuilding(5, 25, 4);
    addBuilding(30, 25, 7);
    addBuilding(55, 25, 5);
    addBuilding(80, 25, 3);
    addBuilding(105, 25, 6);
    addBuilding(130, 25, 4);
}

void init() {
    glClearColor(0.0f, 0.75f, 0.0f, 0.0f); // green
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 150, 0, 80);
}

int main(int argc, char** argv) {
    precalculation();

    glutInit(&argc, argv);

    glutInitWindowSize(1500, 800);
    glutInitWindowPosition (50, 50);
    glutCreateWindow("Project");

    glutDisplayFunc(display);

    glutMouseFunc(mouseClick);
    glutSpecialFunc(keyboard);
    updateClouds(0);

    init();
    glutMainLoop();
    return 0;
}
