
#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <GL/gl.h>
#include<GL/glut.h> //�Ѱ���gl.h��glu.h
#include<math.h>
#include<time.h>
#include<studio.h>

#define WIDTH 700
#define HEIGHT 700

static GLfloat angle = 0.0f;

//����ͷ


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

//������ͼ
static int day = 200; //?day�ı仯����0��359
void myDisplay(void)
{
	double FPS = CalFrequency();
	printf("FPS = %F\n", FPS);
	//��Ȳ���
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //˫����

	//����͸��Ч����ͼ
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//��ǰ������Ϊ��λ����
	gluPerspective(90.0f, 1.0f, 1.0f, 20.0f);

	//��ͼ�任
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 5.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	//?����̫����Դ������һ�ְ�ɫ�Ĺ�Դ?????{?
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
	//?����̫���Ĳ��ʲ�����̫��?????{?
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

	//?���ƺ�ɫ�ġ�̫����?????
	glColor3f(1.0f,0.0f,0.0f);
	glutSolidSphere(696000, 20, 20);

	//?������ɫ�ġ�����"
	glColor3f(0.0f, 0.0f, 1.0f);
	glRotatef(day / 360.0*360.0, 0.0f, 0.0f, -1.0f); // ǰ��Ϊԭ��ֱ�ߣ����Ϊ�Ƕ�
	glTranslatef(1500000, 0.0f, 0.0f);//����Ϊλ��ֵ
	glutSolidSphere(159450, 20, 20);

	//?���ƻ�ɫ�ġ�������
	glColor3f(1.0f, 1.0f, 0.0f);
	glRotatef(day / 30.0*360.0 - day / 360.0*360.0, 0.0f, 0.0f, -1.0f);
	glTranslatef(380000,0.0f,0.0f);
	glutSolidSphere(43450, 20, 20);

	glFlush(); //ǿ��ˢ��
	glutSwapBuffers(); //����������
}

//����������һ�� �ػ�
void myIdle(void)
{
	++day;
	if (day >= 360)
		{day = 0;}
	myDisplay();
}

int main(int argc, char *argv[]) //argc����������argv����������linux.
{
	//GLUT���߰����ṩ�ĺ���
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); //���ó�ʼ��ʾģʽ
	glutInitWindowPosition(300, 0);
	glutInitWindowSize(700, 700);
	glutCreateWindow("M's Android Robot");//����glutMainLoop���ܿ�������
	
	glutDisplayFunc(&myDisplay); //myDisplay����������ͼ
	glutIdleFunc(&myIdle); //������

	glutMainLoop();//�û�ͼѭ������,������ʾ���ڣ����ҵȴ����ڹرպ�Ż᷵��
	return 0;
}