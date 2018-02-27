
#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <GL/gl.h>
#include<GL/glut.h> //已包含gl.h和glu.h
#include<math.h>
#include<time.h>
#include<studio.h>

#define WIDTH 700
#define HEIGHT 700

static GLfloat angle = 0.0f;

//绘制头


double CalFrequency()
{
	static int count;
	static double save;
	static clock_t last, current;
	double timegap;

	++count;
	if (count <= 50)
	{
		return save;
		last = current;
		current = clock();
		timegap = (current - last) / (double)CLK_TCK;
		save = 50.0 / timegap;
		return save;
	}
}

//用来画图
static int day = 200; //?day的变化：从0到359
void myDisplay(void)
{
	double FPS = CalFrequency();
	printf("FPS = %F\n", FPS);
	//深度测试
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //双缓冲

	//创建透视效果视图
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//当前矩阵设为单位矩阵
	gluPerspective(90.0f, 1.0f, 1.0f, 20.0f);

	//视图变换
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 5.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	//?定义太阳光源，它是一种白色的光源?????{?
	GLfloat sun_light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat sun_light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}
	//?定义太阳的材质并绘制太阳?????{?
	GLfloat sun_mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat sun_mat_diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat sun_mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat sun_mat_emission[] = { 0.5f, 0.0f, 0.0f, 1.0f };
	GLfloat sun_mat_shininess = 0.0f;
	glMaterialfv(GL_FRONT,GL_AMBIENT,sun_mat_ambient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,sun_mat_diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR,sun_mat_specular);
	glMaterialfv(GL_FRONT,GL_EMISSION,sun_mat_emission);
	glMaterialf (GL_FRONT,GL_SHININESS,sun_mat_shininess);
	glutSolidSphere(2.0,40,32);
}

	//?绘制红色的“太阳”?????
	glColor3f(1.0f,0.0f,0.0f);
	glutSolidSphere(696000, 20, 20);

	//?绘制蓝色的“地球"
	glColor3f(0.0f, 0.0f, 1.0f);
	glRotatef(day / 360.0*360.0, 0.0f, 0.0f, -1.0f); // 前三为原点直线，最后为角度
	glTranslatef(1500000, 0.0f, 0.0f);//参数为位移值
	glutSolidSphere(159450, 20, 20);

	//?绘制黄色的“月亮”
	glColor3f(1.0f, 1.0f, 0.0f);
	glRotatef(day / 30.0*360.0 - day / 360.0*360.0, 0.0f, 0.0f, -1.0f);
	glTranslatef(380000,0.0f,0.0f);
	glutSolidSphere(43450, 20, 20);

	glFlush(); //强制刷新
	glutSwapBuffers(); //交换缓冲区
}

//日期往后移一天 重绘
void myIdle(void)
{
	++day;
	if (day >= 360)
		{day = 0;}
	myDisplay();
}

int main(int argc, char *argv[]) //argc参数数量，argv参数向量。linux.
{
	//GLUT工具包所提供的函数
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); //设置初始显示模式
	glutInitWindowPosition(300, 0);
	glutInitWindowSize(700, 700);
	glutCreateWindow("M's Android Robot");//调用glutMainLoop才能看到窗口
	
	glutDisplayFunc(&myDisplay); //myDisplay函数用来画图
	glutIdleFunc(&myIdle); //动起来

	glutMainLoop();//让绘图循环进行,可以显示窗口，并且等待窗口关闭后才会返回
	return 0;
}