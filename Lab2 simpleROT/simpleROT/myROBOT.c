#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <GL/gl.h>
#include<GL/glut.h> //�Ѱ���gl.h��glu.h
#include<math.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>

int angx[5] = { 0, 0, 0, 0, 0 };

//��������˹�Դ����ɫ
GLfloat light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };//��Դλ��
GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f }; //������
GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };   //������� ��ɫ 
GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //���淴��� ��ɫ

//��������˵Ĳ���
GLfloat rot_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat rot_ambient[] = { 146 / 255.0f, 94.0 / 255.0f, 162 / 255.0f, 1.0f };
GLfloat rot_diffuse[] = { 146 / 255.0f, 94.0 / 255.0f, 162 / 255.0f, 1.0f };
GLfloat rot_specular[] = { 146 / 255.0f, 94.0 / 255.0f, 162 / 255.0f, 1.0f };
GLfloat rot_emission[] = { 146 / 255.0f, 94.0 / 255.0f, 162 / 255.0f, 1.0f }; //���ʱ�����
GLfloat rot_shininess = 30.0f;//����ָ���������������С��0-128

//���������˵�ͷ
void Head(void)
{
	glColor3ub(146, 94, 162);
	glTranslatef(0, 0.6f, 0);
	glutSolidSphere(0.1f, 100, 100);//��
}
//������
void Body(void)
{

	glColor3ub(146, 94, 162);
	glTranslatef(0, 0.3f, 0);//�ƶ�
	glScalef(0.3,0.4,0.2);  //ģ�ͱ任�ɳ�����
	glutSolidCube(1.0); //����ʵ��������
}
//��첲
void leftArm(void)
{
	glColor3ub(146, 94, 162);
	glTranslatef(-0.2f, 0.5f, 0);//�ƶ�
	glRotatef(75, 1.0f,0, 0 );//��ת
	GLUquadric *pobj;
	pobj = gluNewQuadric();
	gluCylinder(pobj,0.05,0.05,0.3,20,30); //����Բ��
}
//�Ҹ첲
void rightArm(void)
{
	glColor3ub(146, 94, 162);
	glTranslatef(0.2f, 0.5f, 0);//�ƶ�
	glRotatef(75, 1.0f, 0, 0);//��ת	
	GLUquadric *pobj;
	pobj = gluNewQuadric();
	gluCylinder(pobj, 0.05, 0.05, 0.3, 20, 30); //����Բ��
}
//����
void leftLeg(void)
{
	glColor3ub(146, 94, 162);
	glTranslatef(-0.1f, 0.1f, 0);
	glRotatef(75, 1.0f, 0, 0);
	GLUquadric *pobj;
	pobj = gluNewQuadric();
	gluCylinder(pobj,  0.06,0.07 ,0.4, 20, 30); //����ʵ��������
}
//����
void rightLeg(void)
{
	glColor3ub(146, 94, 162);
	glTranslatef(0.1f, 0.1f, 0);//���ƶ�
	glRotatef(75, 1.0f, 0, 0);//����ת
	GLUquadric *pobj;
	pobj = gluNewQuadric();
	gluCylinder(pobj, 0.06,0.07, 0.4, 20, 30); //����ʵ��������
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
	glEnable(GL_DEPTH_TEST);//��Ȳ���
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�����ɫ��Ȼ���λ

	
	
	//��ת����
	glPushMatrix();
	glTranslatef(-0.1f, 0.1f, 0);
	glRotatef(angx[4], 0.1f, 0, 0);
	glTranslatef(0.1f,- 0.1f, 0);
	leftLeg();
	glPopMatrix();
	
	//��ת����
	glPushMatrix();
	glTranslatef(0.1f, 0.1f, 0);
	glRotatef(angx[5], 0.1f, 0, 0);
	glTranslatef(-0.1f, -0.1f, 0);
	rightLeg();
	glPopMatrix();

	//��ת�Ҹ첲
	glPushMatrix();
	glTranslatef(0.2f, 0.5f, 0);
	glRotatef(angx[3], 0.1f, 0, 0);
	glTranslatef(-0.2f, -0.5f, 0);
	rightArm();
	glPopMatrix();
	//��ת��첲
	glPushMatrix();
	glTranslatef(-0.2f, 0.5f, 0);
	glRotatef(angx[2], 0.1f, 0, 0);
	glTranslatef(0.2f, -0.5f, 0);
	leftArm();
	glPopMatrix();

	//��ת����
	glPushMatrix();
	glTranslatef(0, 0.3f, 0);
	glRotatef(angx[1], 0, 0.1f, 0);
	glTranslatef(0, -0.3f, 0);
	Body();
	glPopMatrix();

	//��תͷ
	glPushMatrix();
	glTranslatef(0, 0.6f, 0);
	glRotatef(angx[0], 0, 0.1f, 0);
	glTranslatef(0, -0.6f, 0);
	Head();
	glPopMatrix();

	glFlush(); //ǿ��ˢ�»���
	glutSwapBuffers();//������������
}

int main(int argc, char *argv[]) //argc����������argv����������linux.
{
	//��ʼ������
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); //���ó�ʼ��ʾģʽ,DOUBLE˫����
	glutInitWindowPosition(300, 0);
	glutInitWindowSize(700, 700);
	glutCreateWindow("My Robot");//����glutMainLoop���ܿ�������

	glutKeyboardFunc(keyBoard);//�ȼ���
	glutDisplayFunc(&myDisplay);//myDisplay����������ͼ

	glutMainLoop();//�û�ͼѭ������,������ʾ���ڣ����ҵȴ����ڹرպ�Ż᷵��
	return 0;
}

