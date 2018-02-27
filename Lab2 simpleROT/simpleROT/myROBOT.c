#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <GL/gl.h>
#include<GL/glut.h> //已包含gl.h和glu.h
#include<math.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>

int angx[5] = { 0, 0, 0, 0, 0 };

//定义机器人光源，白色
GLfloat light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };//光源位置
GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f }; //环境光
GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };   //漫反射光 黑色 
GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //镜面反射光 黑色

//定义机器人的材质
GLfloat rot_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat rot_ambient[] = { 146 / 255.0f, 94.0 / 255.0f, 162 / 255.0f, 1.0f };
GLfloat rot_diffuse[] = { 146 / 255.0f, 94.0 / 255.0f, 162 / 255.0f, 1.0f };
GLfloat rot_specular[] = { 146 / 255.0f, 94.0 / 255.0f, 162 / 255.0f, 1.0f };
GLfloat rot_emission[] = { 146 / 255.0f, 94.0 / 255.0f, 162 / 255.0f, 1.0f }; //材质本身发光
GLfloat rot_shininess = 30.0f;//镜面指数，产生的亮点大小，0-128

//画出机器人的头
void Head(void)
{
	glColor3ub(146, 94, 162);
	glTranslatef(0, 0.6f, 0);
	glutSolidSphere(0.1f, 100, 100);//球
}
//画身体
void Body(void)
{

	glColor3ub(146, 94, 162);
	glTranslatef(0, 0.3f, 0);//移动
	glScalef(0.3,0.4,0.2);  //模型变换成长方体
	glutSolidCube(1.0); //绘制实心立方体
}
//左胳膊
void leftArm(void)
{
	glColor3ub(146, 94, 162);
	glTranslatef(-0.2f, 0.5f, 0);//移动
	glRotatef(75, 1.0f,0, 0 );//旋转
	GLUquadric *pobj;
	pobj = gluNewQuadric();
	gluCylinder(pobj,0.05,0.05,0.3,20,30); //绘制圆柱
}
//右胳膊
void rightArm(void)
{
	glColor3ub(146, 94, 162);
	glTranslatef(0.2f, 0.5f, 0);//移动
	glRotatef(75, 1.0f, 0, 0);//旋转	
	GLUquadric *pobj;
	pobj = gluNewQuadric();
	gluCylinder(pobj, 0.05, 0.05, 0.3, 20, 30); //绘制圆柱
}
//左腿
void leftLeg(void)
{
	glColor3ub(146, 94, 162);
	glTranslatef(-0.1f, 0.1f, 0);
	glRotatef(75, 1.0f, 0, 0);
	GLUquadric *pobj;
	pobj = gluNewQuadric();
	gluCylinder(pobj,  0.06,0.07 ,0.4, 20, 30); //绘制实心立方体
}
//右腿
void rightLeg(void)
{
	glColor3ub(146, 94, 162);
	glTranslatef(0.1f, 0.1f, 0);//再移动
	glRotatef(75, 1.0f, 0, 0);//先旋转
	GLUquadric *pobj;
	pobj = gluNewQuadric();
	gluCylinder(pobj, 0.06,0.07, 0.4, 20, 30); //绘制实心立方体
}

void keyBoard(unsigned char key, int x, int y)
{
	if (key = 'a') {
		angx[0] +=5;
		angx[0] = angx[0] % 360;
	}
	if (key = 'b') {
		angx[1] += 5;
		angx[1] = angx[1] % 360;
	}
	if (key = 'c') {
		angx[2] += 5;
		angx[2] = angx[2] % 360;
	}
	if (key = 'd') {
		angx[3] += 5;
		angx[3] = angx[3] % 360;
	}
	if (key = 'e') {
		angx[4] += 5;
		angx[4] = angx[4] % 360;
	}
	if (key = 'f') {
		angx[5] += 5;
		angx[5] = angx[5] % 360;
	}
	glutPostRedisplay();
}
void  myDisplay(void)
{
	glEnable(GL_DEPTH_TEST);//深度测试
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清楚颜色深度缓存位

	
	
	//旋转左腿
	glPushMatrix();
	glTranslatef(-0.1f, 0.1f, 0);
	glRotatef(angx[4], 0.1f, 0, 0);
	glTranslatef(0.1f,- 0.1f, 0);
	leftLeg();
	glPopMatrix();
	
	//旋转右腿
	glPushMatrix();
	glTranslatef(0.1f, 0.1f, 0);
	glRotatef(angx[5], 0.1f, 0, 0);
	glTranslatef(-0.1f, -0.1f, 0);
	rightLeg();
	glPopMatrix();

	//旋转右胳膊
	glPushMatrix();
	glTranslatef(0.2f, 0.5f, 0);
	glRotatef(angx[3], 0.1f, 0, 0);
	glTranslatef(-0.2f, -0.5f, 0);
	rightArm();
	glPopMatrix();
	//旋转左胳膊
	glPushMatrix();
	glTranslatef(-0.2f, 0.5f, 0);
	glRotatef(angx[2], 0.1f, 0, 0);
	glTranslatef(0.2f, -0.5f, 0);
	leftArm();
	glPopMatrix();

	//旋转身体
	glPushMatrix();
	glTranslatef(0, 0.3f, 0);
	glRotatef(angx[1], 0, 0.1f, 0);
	glTranslatef(0, -0.3f, 0);
	Body();
	glPopMatrix();

	//旋转头
	glPushMatrix();
	glTranslatef(0, 0.6f, 0);
	glRotatef(angx[0], 0, 0.1f, 0);
	glTranslatef(0, -0.6f, 0);
	Head();
	glPopMatrix();

	glFlush(); //强制刷新缓冲
	glutSwapBuffers();//交换缓冲区域
}

int main(int argc, char *argv[]) //argc参数数量，argv参数向量。linux.
{
	//初始化窗口
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); //设置初始显示模式,DOUBLE双缓冲
	glutInitWindowPosition(300, 0);
	glutInitWindowSize(700, 700);
	glutCreateWindow("My Robot");//调用glutMainLoop才能看到窗口

	glutKeyboardFunc(keyBoard);//先键盘
	glutDisplayFunc(&myDisplay);//myDisplay函数用来画图

	glutMainLoop();//让绘图循环进行,可以显示窗口，并且等待窗口关闭后才会返回
	return 0;
}

