#include<windows.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>

double  r = .2, s = .3, l = .3;
int i;
float  tx = 10, bx = 10;
float  tx1 = 10, bx1 = 10;
float  birdOffset = -220.0f; // Horizontal offset for day birds
float  birdFlapPhase = 0.0f;  // Phase accumulator for bird wing flap
float  birdBobPhase  = 0.0f;  // Phase accumulator for slight vertical bob
bool isDay = true; // Flag to indicate whether it's day or night

void sun(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy)
{
    glBegin(GL_POLYGON);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 360; i++)
    {
        float angle = i * 3.1416 / 180;
        float x = rx * cos(angle);
        float y = ry * sin(angle);
        glVertex2f((x + cx), (y + cy));
    }
    glEnd();
}

void circle(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy)
{
    glBegin(GL_POLYGON);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 360; i++)
    {
        float angle = i * 3.1416 / 180;
        float x = rx * cos(angle);
        float y = ry * sin(angle);
        glVertex2f((x + cx), (y + cy));
    }
    glEnd();
}

void cloud(double x, double y)
{


    glBegin(GL_TRIANGLE_FAN);
    for(i=0; i<360; i++)
    {
        x=x+cos((i*3.14)/180)*r;
        y=y+sin((i*3.14)/180)*r;

        glVertex2d(x,y);

    }

    glEnd();
}
void sun(double x, double y)
{


    glBegin(GL_TRIANGLE_FAN);
    for(i=0; i<360; i++)
    {
        x=x+cos((i*3.14)/180)*s;
        y=y+sin((i*3.14)/180)*s;

        glVertex2d(x,y);

    }

    glEnd();
}


void leaf(double x, double y)
{


    glBegin(GL_TRIANGLE_FAN);
    for(i=0; i<360; i++)
    {
        x=x+cos((i*3.14)/180)*l;
        y=y+sin((i*3.14)/180)*l;

        glVertex2d(x,y);

    }


    glEnd();

}

void drawBird(float x, float y, float scale, float flap)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(scale, scale, 1);
    glLineWidth(2.2f);

    // Wing geometry (flapping)
    float tipY = flap * 0.4f;          // slight lift/drop at tips
    float peakY = 6.0f + flap;         // main wing peak movement
    glBegin(GL_LINE_STRIP);
    glColor3ub(20, 20, 20); // Wing outline
    glVertex2f(-12, tipY);
    glVertex2f(-6, peakY);
    glVertex2f(0, 0);
    glVertex2f(6, peakY);
    glVertex2f(12, tipY);
    glEnd();

    // Filled wings for a fuller silhouette
    glBegin(GL_TRIANGLES);
    glColor3ub(60, 60, 60);
    glVertex2f(-12, tipY);
    glVertex2f(-2, 1);
    glVertex2f(-6, peakY);
    glVertex2f(12, tipY);
    glVertex2f(2, 1);
    glVertex2f(6, peakY);
    glEnd();

    // Body (slight oval)
    glColor3ub(45, 45, 45);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-1, 0);
    glVertex2f(-2, 2);
    glVertex2f(2, 3);
    glVertex2f(6, 2);
    glVertex2f(7, 0);
    glVertex2f(6, -2);
    glVertex2f(2, -3);
    glVertex2f(-2, -2);
    glEnd();

    // Belly highlight
    glColor3ub(90, 90, 90);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0, -0.5f);
    glVertex2f(-1.5f, -1.5f);
    glVertex2f(2, -2.5f);
    glVertex2f(5.5f, -1.5f);
    glVertex2f(6.5f, -0.4f);
    glEnd();

    // Tail
    glColor3ub(35, 35, 35);
    glBegin(GL_TRIANGLES);
    glVertex2f(-8, 0);
    glVertex2f(-4, 2);
    glVertex2f(-4, -2);
    glEnd();

    // Head
    glColor3ub(40, 40, 40);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(7, 0);
    glVertex2f(8, 1.5f);
    glVertex2f(9, 0.8f);
    glVertex2f(9, -0.8f);
    glVertex2f(8, -1.5f);
    glEnd();

    // Beak
    glColor3ub(255, 160, 60);
    glBegin(GL_TRIANGLES);
    glVertex2f(9, 0);
    glVertex2f(11, 0.6f);
    glVertex2f(11, -0.6f);
    glEnd();

    // Eye
    glPointSize(2.5f);
    glColor3ub(235, 235, 235);
    glBegin(GL_POINTS);
    glVertex2f(8.2f, 0.5f);
    glEnd();
    glPointSize(1.0f);

    glLineWidth(1.0f);
    glPopMatrix();
}

//Fence
void fence(int x)
{
    glBegin(GL_POLYGON);
    glColor3ub(184,134,11);

    glVertex2i(190-x,130);
    glVertex2i(190-x,70);
    glVertex2i(187-x,70);
    glVertex2i(187-x,130);
    glVertex2i(190-x,130);

    glEnd();

}

//FenceNight
void fence1(int x)
{
    glBegin(GL_POLYGON);
    glColor3ub(100, 50, 20); // Dark brown
    glVertex2i(190 - x, 130);
    glVertex2i(190 - x, 70);
    glVertex2i(187 - x, 70);
    glVertex2i(187 - x, 130);
    glVertex2i(190 - x, 130);
    glEnd();
}
void init()
{
    glClearColor(0.0f, 0.0f, 0.1f, 1.0f); // Dark blue background
    glOrtho(-210, 210, -220, 310, -210, 310);
}

// Function to draw the day scenery
void drawDayScene()
{
    // Draw the scenery for day
    // Add your code for day scene here
//sky

//cloud/Sun/leaf



    glClear(GL_COLOR_BUFFER_BIT);
//sky
    glColor3ub(135,206,250);//light blue
    glRecti(-200,300,200,100);
//field
    glBegin(GL_POLYGON);
    glColor3ub(0,100,0);//green

    glVertex2i(-200,100);
    glVertex2i(-100,160);
    glVertex2i(0,100);
    glVertex2i(50,70);
    glVertex2i(100,180);
    glVertex2i(200,100);
    glColor3ub(255,215,0);//gold
    glVertex2i(200,-200);

    glVertex2i(-200,-200);
    glColor3ub(255,215,0);//gold
    glVertex2i(-200,100);

    glEnd();

//SUN
    glColor3ub(255,215,0);
    sun(15,25,90,250+15);
//fence
    int x=0;
    for(int i=0; i<39; i++)
    {
        fence(x);
        x+=10;
    }

    glColor3ub(184,134,11);
    glRecti(-200,120,200,115);
    glRecti(-200,100,200,95);
    glRecti(-200,85,200,80);

//CLOUD
    glPushMatrix();
    glColor3ub(220,220,220);
    glTranslatef(bx,0,0);
    cloud(0,250);
    cloud(15,245);
    cloud(10,240);
    cloud(-2,243);
    cloud(-80,250);
    cloud(-95,245);
    cloud(-90,240);
    cloud(-90,243);
    cloud(-75,243);

    glColor3ub(211,211,211);
    sun(-165,260);
    sun(-185,245);
    sun(-180,240);
    sun(-152,243);

    glPopMatrix();
    tx+=.01;
    if(tx>200)
        tx=-200;

// BIRDS (daytime)
    glPushMatrix();
    glTranslatef(birdOffset, 0, 0);
    float flap = sinf(birdFlapPhase) * 2.2f; // wing up-down (natural range)
    float bob1 = sinf(birdBobPhase + 0.0f) * 3.0f;
    float bob2 = sinf(birdBobPhase + 0.7f) * 3.0f;
    float bob3 = sinf(birdBobPhase + 1.4f) * 3.0f;
    drawBird(-170, 255 + bob1, 1.35f, flap);
    drawBird(-130, 245 + bob2, 1.25f, flap);
    drawBird(-95, 252 + bob3, 1.45f, flap);
    glPopMatrix();
    birdOffset += 0.12f; // slower flight speed
    if (birdOffset > 240.0f)
        birdOffset = -240.0f;
    birdFlapPhase += 0.12f;
    birdBobPhase  += 0.06f;


//TREE
    glColor3ub(139,69,19);//
    glRecti(-20,200,-13,140);
    glColor3ub(0,100,0);
    leaf(-30,190);
    glColor3ub(0,100,0);
    leaf(0,190);
    glColor3ub(0,100,0);
    leaf(-10,210);
    glColor3ub(0,100,0);
    leaf(-30,175);
    glColor3ub(0,100,0);
    leaf(-0,170);

    glBegin(GL_POLYGON); // Main Tree // first part
    glColor3ub(139,69,19);//
    glVertex2i(-170,160);
    glVertex2i(-168,120);
    glColor3ub(139,69,19);//
    glVertex2i(-178,40);
    glVertex2i(-145,40);
    glColor3ub(139,69,19);//
    glVertex2i(-153,120);
    glVertex2i(-150,160);
    glVertex2i(-170,160);
    glEnd();

    glBegin(GL_POLYGON);  // Main Tree // second part
    glColor3ub(139,69,19);//
    glVertex2i(-153,100);
    glVertex2i(-100,200);
    glVertex2i(-95,200);
    glVertex2i(-153,80);
    glVertex2i(-153,100);
    glEnd();

    glBegin(GL_POLYGON);  // Main Tree // third part
    glColor3ub(139,69,19);//
    glVertex2i(-170,160);
    glVertex2i(-185,210);
    glVertex2i(-190,210);
    glVertex2i(-168,90);
    glVertex2i(-170,160);

    glEnd();
    glBegin(GL_POLYGON);  // Main Tree // fourth part
    glColor3ub(139,69,19);//
    glVertex2i(-160,160);
    glVertex2i(-150,210);
    glVertex2i(-140,210);
    glVertex2i(-150,160);
    glVertex2i(-160,160);

    glEnd();

    glColor3ub(0,128,0);//leaf
    leaf(-95,200);
    glColor3ub(0,128,0);
    leaf(-80,180);
    glColor3ub(0,128,0);
    leaf(-110,180);
    glColor3ub(0,128,0);
    leaf(-120,200);
    glColor3ub(0,128,0);
    leaf(-150,200);
    glColor3ub(0,128,0);
    leaf(-130,180);
    glColor3ub(0,128,0);
    leaf(-125,220);
    glColor3ub(0,128,0);
    leaf(-140,230);
    glColor3ub(0,128,0);
    leaf(-190,210);
    glColor3ub(0,128,0);
    leaf(-180,200);
    glColor3ub(0,128,0);
    leaf(-175,225);
    glColor3ub(0,128,0);
    leaf(-195,190);

//Right side tree
    glBegin(GL_POLYGON); // Main Tree // first part
    glColor3ub(139, 69, 19);//
    glVertex2i(80, 130);
    glVertex2i(82, 90);
    glColor3ub(139, 69, 19);//
    glVertex2i(72, 10);
    glVertex2i(105, 10);
    glColor3ub(139, 69, 19);//
    glVertex2i(97, 90);
    glVertex2i(100, 130);
    glVertex2i(80, 130);
    glEnd();



    glBegin(GL_POLYGON);  // Main Tree // third part
    glColor3ub(139, 69, 19);//
    glVertex2i(80, 130);
    glVertex2i(65, 180);
    glVertex2i(60, 180);
    glVertex2i(82, 60);
    glVertex2i(80, 130);
    glEnd();

    glBegin(GL_POLYGON);  // Main Tree // fourth part
    glColor3ub(139, 69, 19);//
    glVertex2i(90, 130);
    glVertex2i(100, 180);
    glVertex2i(110, 180);
    glVertex2i(100, 130);
    glVertex2i(90, 130);
    glEnd();


    glColor3ub(0, 128, 0);
    leaf(130, 170);
    glColor3ub(0, 128, 0);
    leaf(100, 170);
    glColor3ub(0, 128, 0);
    leaf(120, 150);
    glColor3ub(0, 128, 0);
    leaf(125, 190);
    glColor3ub(0, 128, 0);
    leaf(110, 200);
    glColor3ub(0, 128, 0);
    leaf(60, 180);
    glColor3ub(0, 128, 0);
    leaf(70, 170);
    glColor3ub(0, 128, 0);
    leaf(75, 195);
    glColor3ub(0, 128, 0);
    leaf(55, 160);

////////////Flower///////////////
    glBegin(GL_TRIANGLES);  // First part
    glColor3ub(0, 100, 0);//
    glVertex2i(84, 24);
    glVertex2i(88, 46);
    glVertex2i(92, 24);
    glEnd();

    glBegin(GL_TRIANGLES);  // First part
    glColor3ub(0, 100, 0);//
    glVertex2i(76, 22);
    glVertex2i(72, 42);
    glVertex2i(82, 24);
    glEnd();

    glBegin(GL_TRIANGLES);  // First part
    glColor3ub(0, 100, 0);//
    glVertex2i(70, 16);
    glVertex2i(58, 30);
    glVertex2i(74, 20);
    glEnd();

    glBegin(GL_TRIANGLES);  // First part
    glColor3ub(0, 100, 0);//
    glVertex2i(94, 24);
    glVertex2i(108, 42);
    glVertex2i(100, 22);
    glEnd();

    glBegin(GL_TRIANGLES);  // First part
    glColor3ub(0, 100, 0);//
    glVertex2i(102, 20);
    glVertex2i(120, 30);
    glVertex2i(106, 16);
    glEnd();

// Draw circles with different colors
    glColor3ub(238, 130, 238);  // Violet
    circle(3, 5, 88, 46);

    glColor3ub(255, 0, 0);  // Red
    circle(3, 5, 72, 42);

    glColor3ub(0, 255, 0);  // Green
    circle(3, 5, 58, 30);

    glColor3ub(0, 0, 255);  // Blue
    circle(3, 5, 120, 30);

    glColor3ub(255, 165, 0);  // Orange
    circle(3, 5, 108, 42);
    glBegin(GL_POLYGON);  // First part

    glColor3ub(0, 100, 0);//
    glVertex2i(68, 10);
    glVertex2i(70, 16);
    glVertex2i(74, 20);
    glVertex2i(76, 22);
    glVertex2i(82, 24);
    glVertex2i(84, 24);
    glVertex2i(92, 24);
    glVertex2i(94, 26);
    glVertex2i(100, 22);
    glVertex2i(102, 20);
    glVertex2i(106, 16);
    glVertex2i(108, 10);
    glEnd();


    glBegin(GL_QUADS);
    glColor3ub(0, 0, 0);//
    glVertex2i(67, 10);
    glVertex2i(68, 11);
    glVertex2i(107, 11);
    glVertex2i(108, 10);
    glEnd();


//HOUSE one
    glBegin(GL_POLYGON);  // first Part
    glColor3ub(128,0,0);//gray
    glVertex2i(-58,115);
    glVertex2i(-75,145);
    glVertex2i(-115,150);//point
    glVertex2i(-90,100);
    glVertex2i(-62,100);
    glVertex2i(-58,115);

    glEnd();
    glBegin(GL_POLYGON);  // second Part
    glColor3ub(120,0,0);//maroon
    glVertex2i(-115,150);
    glVertex2i(-130,100);
    glVertex2i(-120,100);//point
    glVertex2i(-108,137);//point
    glVertex2i(-115,150);
    glEnd();
    glBegin(GL_POLYGON);  // third Part
    glColor3ub(46,139,87);//
    glVertex2i(-108,137);
    glVertex2i(-120,100);
    glVertex2i(-120,45);
    glVertex2i(-90,40);//point
    glVertex2i(-90,100);
    glVertex2i(-108,137);
    glEnd();

    glBegin(GL_POLYGON);  // fourth Part
    glColor3ub(143,188,143);//
    glVertex2i(-90,40);
    glVertex2i(-60,45);
    glVertex2i(-60,100);
    glVertex2i(-90,100);

    glEnd();

    glColor3ub(120,0,0);//maroon // Door One
    glRecti(-75,80,-65,40);
    glColor3ub(120,0,0);//maroon // Door One
    glRecti(-110,90,-100,70);
    glBegin(GL_POLYGON);  // third Part (lower part 1)
    glColor3ub(0,0,0);//
    glVertex2i(-90,40);
    glVertex2i(-123,45);
    glVertex2i(-123,35);
    glVertex2i(-90,30);
    glVertex2i(-90,40);

    glEnd();
    glBegin(GL_POLYGON);  // third Part (lower part 2)
    glColor3ub(0,0,0);//
    glVertex2i(-90,40);
    glVertex2i(-55,45);
    glVertex2i(-55,35);
    glVertex2i(-90,30);
    glVertex2i(-90,40);

    glEnd();

//HOUSE two
    glBegin(GL_POLYGON);  // First part

    glColor3ub(25,25,112);//midnight blue
    glVertex2i(-50,140);
    glVertex2i(0,149);
    glVertex2i(-12,88);
    glVertex2i(-65,89);
    glVertex2i(-50,140);
    glEnd();

    glBegin(GL_POLYGON);  // Second Part
    glColor3ub(70,130,180);//midnight blue
    glVertex2i(-60,90);
    glVertex2i(-60,30);
    glVertex2i(-10,25);
    glVertex2i(-10,95);
    glEnd();

//Gather Rice
    glBegin(GL_QUADS);
    glColor3ub(184,134,11);
    glVertex2i(10,40);
    glVertex2i(10,100);
    glVertex2i(55,100);
    glVertex2i(55,40);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(0,0,0);
    glVertex2i(10,40);
    glVertex2i(10,47);
    glVertex2i(55,47);
    glVertex2i(55,40);
    glEnd();

    glColor3ub(184,134,11);
    circle(22, 32, 33.1, 105);

    glBegin(GL_TRIANGLES);
    glColor3ub(184,134,11);
    glVertex2i(29,110);
    glVertex2i(32,150);
    glVertex2i(35,110);
    glEnd();

//Door
    glColor3ub(25,25,112);//midnight blue
    glRecti(-45,70,-30,27);

    glBegin(GL_POLYGON);   // Third part
    glColor3ub(95,158,160);//midnight blue
    glVertex2i(-10,25);
    glVertex2i(18,35);
    glVertex2i(18,100);
    glVertex2i(0,148);
    glVertex2i(-10,100);
    glVertex2i(-10,25);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(25,25,112);//midnight blue
    glVertex2i(-1,150);
    glVertex2i(20,100);
    glVertex2i(17,90);
    glVertex2i(-4,140);
    glVertex2i(-1,150);

    glEnd();


    glBegin(GL_POLYGON);  // door
    glColor3ub(25,25,112);//midnight blue
    glVertex2i(0,70);
    glVertex2i(10,73);
    glVertex2i(10,32);
    glVertex2i(0,29);
    glVertex2i(0,70);


    glEnd();
    glBegin(GL_POLYGON);  // (lower part 1)
    glColor3ub(0,0,0);//
    glVertex2i(-10,25);
    glVertex2i(-10,15);
    glVertex2i(20,27);
    glVertex2i(20,37);
    glVertex2i(-10,25);


    glEnd();
    glBegin(GL_POLYGON);  // (lower part 2)
    glColor3ub(0,0,0);//
    glVertex2i(-10,25);
    glVertex2i(-62,30);
    glVertex2i(-62,20);
    glVertex2i(-10,15);
    glVertex2i(-10,25);

    glEnd();


//RIVER
    glBegin(GL_POLYGON);
    glColor3ub(30,144,255);
    glVertex2i(-200,-50);
    glVertex2i(200,-30);
    glColor3ub(0,0,128);
    glVertex2i(200,-200);
    glVertex2i(-200,-200);
    glVertex2i(-200,-50);
    glEnd();
    glBegin(GL_POLYGON); // border
    glColor3ub(128,128,0);
    glVertex2i(-200,-45);
    glVertex2i(200,-25);
    glVertex2i(200,-30);
    glVertex2i(-200,-50 );
    glVertex2i(-200,-45);
    glEnd();


//BOAT
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);//Black
    glTranslatef(bx,0,0);
    glBegin(GL_POLYGON);
    glVertex2i(-180,-70);
    glVertex2i(-165,-100);
    glVertex2i(-150,-120);
    glVertex2i(-150,-100);
    glVertex2i(-180,-70);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(-150,-100);
    glVertex2i(-150,-120);
    glVertex2i(-120,-125);
    glVertex2i(-90,-120);
    glVertex2i(-85,-100);
    glVertex2i(-150,-100);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(-85,-100);
    glVertex2i(-90,-120);
    glVertex2i(-75,-105);
    glVertex2i(-60,-70);
    glVertex2i(-85,-100);
    glEnd();

//BOAT FLAG
    glBegin(GL_POLYGON);
    glColor3ub(173,216,230);
    glVertex2i(-57,-40);
    glVertex2i(-50,-10);
    glVertex2i(-49,10);
    glVertex2i(-50,30);
    glVertex2i(-55,45);
    glVertex2i(-63,57);
    glVertex2i(-73,68); // end
    glVertex2i(-105,45);
    glVertex2i(-50,-10);


    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(173,216,230);

    glVertex2i(-68,-70);
    glVertex2i(-57,-40);
    glVertex2i(-85,10);
    glVertex2i(-68,-70);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(173,216,230);
    glVertex2i(-85,-100);
    glVertex2i(-68,-70);
    glVertex2i(-80,-10);
    glVertex2i(-85,-100);

    glEnd();

    glColor3ub(139,69,19);
    glRecti(-88,80,-86,-100);  // Boat stand
    glBegin(GL_POLYGON);
    glColor3f(0.55,0.27,0.0745);//wood color
    glVertex2i(-85,-100);
    glVertex2i(-87,-80);
    glVertex2i(-93,-62);
    glVertex2i(-97,-55);
    glVertex2i(-105,-50);
    glVertex2i(-120,-48);
    glVertex2i(-120,-100);
    glVertex2i(-85,-100);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.55,0.27,0.0745);//wood color
    glVertex2i(-150,-100);
    glVertex2i(-148,-80);
    glVertex2i(-142,-62);
    glVertex2i(-138,-55);
    glVertex2i(-130,-50);
    glVertex2i(-115,-48);
    glVertex2i(-115,-100);
    glVertex2i(-150,-100);


    glEnd();

//BOAT LINE
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 0.0f);//Black
    glVertex2i(-142,-62);
    glVertex2i(-73,68);
    glVertex2i(-73,63);

    glVertex2i(-142,-62);
    glVertex2i(-105,45);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 0.0f);//Black
    glVertex2i(-148,-80);
    glVertex2i(-87,-80);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 0.0f);//Black
    glVertex2i(-142,-62);
    glVertex2i(-93,-62);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 0.0f);//Black
    glVertex2i(-115,-48);
    glVertex2i(-115,-100);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 0.0f);//Black
    glVertex2i(-130,-50);
    glVertex2i(-130,-100);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 0.0f);//Black
    glVertex2i(-100,-52);
    glVertex2i(-100,-100);
    glEnd();


    glPopMatrix();
    bx+=.03;
    if(bx>270)
        bx=-180;


    glutPostRedisplay();
    glColor3ub(255,255,255);//
    glRecti(-210,310,-200,-210);
    glRecti(200,310,210,-210);

    glFlush();
}




// Function to draw the night scenery
void drawNightScene()
{
    // Draw the scenery for night
    // Add your code for night scene here
//sky

//cloud/Sun/leaf

    glClear(GL_COLOR_BUFFER_BIT);

    // Sky
    glColor3ub(0, 0, 50); // Dark blue
    glRecti(-200, 300, 200, 100);

    // Field
    glBegin(GL_POLYGON);
    glColor3ub(0, 10, 0); // Dark green
    glVertex2i(-200, 100);
    glVertex2i(-100, 160);
    glVertex2i(0, 100);
    glVertex2i(50, 70);
    glVertex2i(100, 180);
    glVertex2i(200, 100);
    glColor3ub(0,100,0); // Green
    glVertex2i(200, -200);
    glVertex2i(-200, -200);
    glColor3ub(255,215,0); // Golden
    glVertex2i(-200, 100);
    glEnd();


    // Sun
    glColor3ub(255,215,0);
    sun(15,25,90,250+15);
    glColor3ub(0, 0, 50); // Yellow
    sun(15,25,95, 255+15);

    // Fence
    int x = 0;
    for (int i = 0; i < 39; i++)
    {
        fence1(x);
        x += 10;
    }


    glColor3ub(100, 50, 20);
    glRecti(-200,120,200,115);
    glRecti(-200,100,200,95);
    glRecti(-200,85,200,80);

// Cloud
    glPushMatrix();
    glColor3ub(150, 150, 150); // Gray
    glTranslatef(tx1, 0, 0);
    cloud(0, 250);
    cloud(15, 245);
    cloud(10, 240);
    cloud(-2, 243);
    cloud(-80, 250);
    cloud(-95, 245);
    cloud(-90, 240);
    cloud(-90, 243);
    cloud(-75, 243);

    glColor3ub(211,211,211);
    sun(-165,260);
    sun(-185,245);
    sun(-180,240);
    sun(-152,243);
    glPopMatrix();

    glPopMatrix();
    tx1+=.01;
    if(tx1>200)
        tx1=-200;


//TREE
    glColor3ub(139,69,19); // Forest green
    glRecti(-20, 200, -13, 140);
    glColor3ub(0, 100, 0); // Dark green
    leaf(-30, 190);
    glColor3ub(0, 100, 0);
    leaf(0, 190);
    glColor3ub(0, 100, 0);
    leaf(-10, 210);
    glColor3ub(0, 100, 0);
    leaf(-30, 175);
    glColor3ub(0, 100, 0);
    leaf(0, 170);

    glBegin(GL_POLYGON); // Main Tree // first part
    glColor3ub(139,69,19);//
    glVertex2i(-170,160);
    glVertex2i(-168,120);
    glColor3ub(139,69,19);//
    glVertex2i(-178,40);
    glVertex2i(-145,40);
    glColor3ub(139,69,19);//
    glVertex2i(-153,120);
    glVertex2i(-150,160);
    glVertex2i(-170,160);
    glEnd();

    glBegin(GL_POLYGON);  // Main Tree // second part
    glColor3ub(139,69,19);//
    glVertex2i(-153,100);
    glVertex2i(-100,200);
    glVertex2i(-95,200);
    glVertex2i(-153,80);
    glVertex2i(-153,100);
    glEnd();

    glBegin(GL_POLYGON);  // Main Tree // third part
    glColor3ub(139,69,19);//
    glVertex2i(-170,160);
    glVertex2i(-185,210);
    glVertex2i(-190,210);
    glVertex2i(-168,90);
    glVertex2i(-170,160);

    glEnd();
    glBegin(GL_POLYGON);  // Main Tree // fourth part
    glColor3ub(139,69,19);//
    glVertex2i(-160,160);
    glVertex2i(-150,210);
    glVertex2i(-140,210);
    glVertex2i(-150,160);
    glVertex2i(-160,160);

    glEnd();

    glColor3ub(0,128,0);//leaf
    leaf(-95,200);
    glColor3ub(0,128,0);
    leaf(-80,180);
    glColor3ub(0,128,0);
    leaf(-110,180);
    glColor3ub(0,128,0);
    leaf(-120,200);
    glColor3ub(0,128,0);
    leaf(-150,200);
    glColor3ub(0,128,0);
    leaf(-130,180);
    glColor3ub(0,128,0);
    leaf(-125,220);
    glColor3ub(0,128,0);
    leaf(-140,230);
    glColor3ub(0,128,0);
    leaf(-190,210);
    glColor3ub(0,128,0);
    leaf(-180,200);
    glColor3ub(0,128,0);
    leaf(-175,225);
    glColor3ub(0,128,0);
    leaf(-195,190);

//Right side tree
    glBegin(GL_POLYGON); // Main Tree // first part
    glColor3ub(139, 69, 19);//
    glVertex2i(80, 130);
    glVertex2i(82, 90);
    glColor3ub(139, 69, 19);//
    glVertex2i(72, 10);
    glVertex2i(105, 10);
    glColor3ub(139, 69, 19);//
    glVertex2i(97, 90);
    glVertex2i(100, 130);
    glVertex2i(80, 130);
    glEnd();



    glBegin(GL_POLYGON);  // Main Tree // third part
    glColor3ub(139, 69, 19);//
    glVertex2i(80, 130);
    glVertex2i(65, 180);
    glVertex2i(60, 180);
    glVertex2i(82, 60);
    glVertex2i(80, 130);
    glEnd();

    glBegin(GL_POLYGON);  // Main Tree // fourth part
    glColor3ub(139, 69, 19);//
    glVertex2i(90, 130);
    glVertex2i(100, 180);
    glVertex2i(110, 180);
    glVertex2i(100, 130);
    glVertex2i(90, 130);
    glEnd();


    glColor3ub(0, 128, 0);
    leaf(130, 170);
    glColor3ub(0, 128, 0);
    leaf(100, 170);
    glColor3ub(0, 128, 0);
    leaf(120, 150);
    glColor3ub(0, 128, 0);
    leaf(125, 190);
    glColor3ub(0, 128, 0);
    leaf(110, 200);
    glColor3ub(0, 128, 0);
    leaf(60, 180);
    glColor3ub(0, 128, 0);
    leaf(70, 170);
    glColor3ub(0, 128, 0);
    leaf(75, 195);
    glColor3ub(0, 128, 0);
    leaf(55, 160);

////////////Flower///////////////
    glBegin(GL_TRIANGLES);  // First part
    glColor3ub(0, 100, 0);//
    glVertex2i(84, 24);
    glVertex2i(88, 46);
    glVertex2i(92, 24);
    glEnd();

    glBegin(GL_TRIANGLES);  // First part
    glColor3ub(0, 100, 0);//
    glVertex2i(76, 22);
    glVertex2i(72, 42);
    glVertex2i(82, 24);
    glEnd();

    glBegin(GL_TRIANGLES);  // First part
    glColor3ub(0, 100, 0);//
    glVertex2i(70, 16);
    glVertex2i(58, 30);
    glVertex2i(74, 20);
    glEnd();

    glBegin(GL_TRIANGLES);  // First part
    glColor3ub(0, 100, 0);//
    glVertex2i(94, 24);
    glVertex2i(108, 42);
    glVertex2i(100, 22);
    glEnd();

    glBegin(GL_TRIANGLES);  // First part
    glColor3ub(0, 100, 0);//
    glVertex2i(102, 20);
    glVertex2i(120, 30);
    glVertex2i(106, 16);
    glEnd();

// Draw circles with different colors
    glColor3ub(238, 130, 238);  // Violet
    circle(3, 5, 88, 46);

    glColor3ub(255, 0, 0);  // Red
    circle(3, 5, 72, 42);

    glColor3ub(0, 255, 0);  // Green
    circle(3, 5, 58, 30);

    glColor3ub(0, 0, 255);  // Blue
    circle(3, 5, 120, 30);

    glColor3ub(255, 165, 0);  // Orange
    circle(3, 5, 108, 42);
    glBegin(GL_POLYGON);  // First part

    glColor3ub(0, 100, 0);//
    glVertex2i(68, 10);
    glVertex2i(70, 16);
    glVertex2i(74, 20);
    glVertex2i(76, 22);
    glVertex2i(82, 24);
    glVertex2i(84, 24);
    glVertex2i(92, 24);
    glVertex2i(94, 26);
    glVertex2i(100, 22);
    glVertex2i(102, 20);
    glVertex2i(106, 16);
    glVertex2i(108, 10);
    glEnd();


    glBegin(GL_QUADS);
    glColor3ub(0, 0, 0);//
    glVertex2i(67, 10);
    glVertex2i(68, 11);
    glVertex2i(107, 11);
    glVertex2i(108, 10);
    glEnd();


//HOUSE one
    glBegin(GL_POLYGON);  // first Part
    glColor3ub(128,0,0);//gray
    glVertex2i(-58,115);
    glVertex2i(-75,145);
    glVertex2i(-115,150);//point
    glVertex2i(-90,100);
    glVertex2i(-62,100);
    glVertex2i(-58,115);

    glEnd();
    glBegin(GL_POLYGON);  // second Part
    glColor3ub(120,0,0);//maroon
    glVertex2i(-115,150);
    glVertex2i(-130,100);
    glVertex2i(-120,100);//point
    glVertex2i(-108,137);//point
    glVertex2i(-115,150);
    glEnd();
    glBegin(GL_POLYGON);  // third Part
    glColor3ub(46,139,87);//
    glVertex2i(-108,137);
    glVertex2i(-120,100);
    glVertex2i(-120,45);
    glVertex2i(-90,40);//point
    glVertex2i(-90,100);
    glVertex2i(-108,137);
    glEnd();

    glBegin(GL_POLYGON);  // fourth Part
    glColor3ub(143,188,143);//
    glVertex2i(-90,40);
    glVertex2i(-60,45);
    glVertex2i(-60,100);
    glVertex2i(-90,100);

    glEnd();

    glColor3ub(120,0,0);//maroon // Door One
    glRecti(-75,80,-65,40);
    glColor3ub(120,0,0);//maroon // Door One
    glRecti(-110,90,-100,70);
    glBegin(GL_POLYGON);  // third Part (lower part 1)
    glColor3ub(0,0,0);//
    glVertex2i(-90,40);
    glVertex2i(-123,45);
    glVertex2i(-123,35);
    glVertex2i(-90,30);
    glVertex2i(-90,40);

    glEnd();
    glBegin(GL_POLYGON);  // third Part (lower part 2)
    glColor3ub(0,0,0);//
    glVertex2i(-90,40);
    glVertex2i(-55,45);
    glVertex2i(-55,35);
    glVertex2i(-90,30);
    glVertex2i(-90,40);

    glEnd();

//HOUSE two
    glBegin(GL_POLYGON);  // First part

    glColor3ub(25,25,112);//midnight blue
    glVertex2i(-50,140);
    glVertex2i(0,149);
    glVertex2i(-12,88);
    glVertex2i(-65,89);
    glVertex2i(-50,140);
    glEnd();

    glBegin(GL_POLYGON);  // Second Part
    glColor3ub(70,130,180);//midnight blue
    glVertex2i(-60,90);
    glVertex2i(-60,30);
    glVertex2i(-10,25);
    glVertex2i(-10,95);
    glEnd();

//Gather Rice
    glBegin(GL_QUADS);
    glColor3ub(100, 50, 20);
    glVertex2i(10,40);
    glVertex2i(10,100);
    glVertex2i(55,100);
    glVertex2i(55,40);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(0,0,0);
    glVertex2i(10,40);
    glVertex2i(10,47);
    glVertex2i(55,47);
    glVertex2i(55,40);
    glEnd();

    glColor3ub(100, 50, 20);
    circle(22, 32, 33.1, 105);

    glBegin(GL_TRIANGLES);
    glColor3ub(100, 50, 20);
    glVertex2i(29,110);
    glVertex2i(32,150);
    glVertex2i(35,110);
    glEnd();

//Door
    glColor3ub(25,25,112);//midnight blue
    glRecti(-45,70,-30,27);

    glBegin(GL_POLYGON);   // Third part
    glColor3ub(95,158,160);//midnight blue
    glVertex2i(-10,25);
    glVertex2i(18,35);
    glVertex2i(18,100);
    glVertex2i(0,148);
    glVertex2i(-10,100);
    glVertex2i(-10,25);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(25,25,112);//midnight blue
    glVertex2i(-1,150);
    glVertex2i(20,100);
    glVertex2i(17,90);
    glVertex2i(-4,140);
    glVertex2i(-1,150);

    glEnd();


    glBegin(GL_POLYGON);  // door
    glColor3ub(25,25,112);//midnight blue
    glVertex2i(0,70);
    glVertex2i(10,73);
    glVertex2i(10,32);
    glVertex2i(0,29);
    glVertex2i(0,70);


    glEnd();
    glBegin(GL_POLYGON);  // (lower part 1)
    glColor3ub(0,0,0);//
    glVertex2i(-10,25);
    glVertex2i(-10,15);
    glVertex2i(20,27);
    glVertex2i(20,37);
    glVertex2i(-10,25);


    glEnd();
    glBegin(GL_POLYGON);  // (lower part 2)
    glColor3ub(0,0,0);//
    glVertex2i(-10,25);
    glVertex2i(-62,30);
    glVertex2i(-62,20);
    glVertex2i(-10,15);
    glVertex2i(-10,25);

    glEnd();


// River
    glBegin(GL_POLYGON);
    glColor3ub(0, 0, 139); // Dark blue
    glVertex2i(-200, -50);
    glVertex2i(200, -30);
    glColor3ub(0, 0, 75); // Navy blue
    glVertex2i(200, -200);
    glVertex2i(-200, -200);
    glVertex2i(-200, -50);
    glEnd();
    glBegin(GL_POLYGON); // border
    glColor3ub(0,0,0);
    glVertex2i(-200,-45);
    glVertex2i(200,-25);
    glVertex2i(200,-30);
    glVertex2i(-200,-50 );
    glVertex2i(-200,-45);
    glEnd();


//BOAT
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);//Black
    glTranslatef(bx1,50,0);
    glBegin(GL_POLYGON);
    glVertex2i(-180,-70);
    glVertex2i(-165,-100);
    glVertex2i(-150,-120);
    glVertex2i(-150,-100);
    glVertex2i(-180,-70);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(-150,-100);
    glVertex2i(-150,-120);
    glVertex2i(-120,-125);
    glVertex2i(-90,-120);
    glVertex2i(-85,-100);
    glVertex2i(-150,-100);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(-85,-100);
    glVertex2i(-90,-120);
    glVertex2i(-75,-105);
    glVertex2i(-60,-70);
    glVertex2i(-85,-100);
    glEnd();

//BOAT FLAG
    glBegin(GL_POLYGON);
    glColor3ub(173,216,230);
    glVertex2i(-57,-40);
    glVertex2i(-50,-10);
    glVertex2i(-49,10);
    glVertex2i(-50,30);
    glVertex2i(-55,45);
    glVertex2i(-63,57);
    glVertex2i(-73,68); // end
    glVertex2i(-105,45);
    glVertex2i(-50,-10);


    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(173,216,230);

    glVertex2i(-68,-70);
    glVertex2i(-57,-40);
    glVertex2i(-85,10);
    glVertex2i(-68,-70);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(173,216,230);
    glVertex2i(-85,-100);
    glVertex2i(-68,-70);
    glVertex2i(-80,-10);
    glVertex2i(-85,-100);

    glEnd();

    glColor3ub(139,69,19);
    glRecti(-88,80,-86,-100);  // Boat stand
    glBegin(GL_POLYGON);
    glColor3f(0.55,0.27,0.0745);//wood color
    glVertex2i(-85,-100);
    glVertex2i(-87,-80);
    glVertex2i(-93,-62);
    glVertex2i(-97,-55);
    glVertex2i(-105,-50);
    glVertex2i(-120,-48);
    glVertex2i(-120,-100);
    glVertex2i(-85,-100);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.55,0.27,0.0745);//wood color
    glVertex2i(-150,-100);
    glVertex2i(-148,-80);
    glVertex2i(-142,-62);
    glVertex2i(-138,-55);
    glVertex2i(-130,-50);
    glVertex2i(-115,-48);
    glVertex2i(-115,-100);
    glVertex2i(-150,-100);


    glEnd();

//BOAT LINE
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 0.f);//Black
    glVertex2i(-142,-62);
    glVertex2i(-73,68);
    glVertex2i(-73,63);

    glVertex2i(-142,-62);
    glVertex2i(-105,45);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 0.0f);//Black
    glVertex2i(-148,-80);
    glVertex2i(-87,-80);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 0.0f);//Black
    glVertex2i(-142,-62);
    glVertex2i(-93,-62);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 0.0f);//Black
    glVertex2i(-115,-48);
    glVertex2i(-115,-100);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 0.0f);//Black
    glVertex2i(-130,-50);
    glVertex2i(-130,-100);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 0.0f);//Black
    glVertex2i(-100,-52);
    glVertex2i(-100,-100);
    glEnd();


    glPopMatrix();
    bx1+=.00;
    if(bx1>270)
        bx1=-180;


    glutPostRedisplay();
    glColor3ub(255, 255, 255); // White
    glRecti(-210, 310, -200, -210);
    glRecti(200, 310, 210, -210);
    glFlush();
}



// Keyboard callback function
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'd':
    case 'D':
        isDay = true;
        break;
    case 'n':
    case 'N':
        isDay = false;
        break;
    }
    glutPostRedisplay();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (isDay)
    {
        drawDayScene();
    }
    else
    {
        drawNightScene();
    }

    glFlush();
}

int main(int argc,char *argv[])
{
    glutInit(&argc,argv);
    glutInitWindowSize(1200,800);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Village Scenery");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard); // Register keyboard callback
    glutMainLoop();
    return 0;
}
