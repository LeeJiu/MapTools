#pragma once


#include <cmath>

#define PI		3.141592654f
#define PI2		(PI * 2)
#define PI8		float(PI / 8.0f)
#define PI16	float(PI / 16.f)
#define PI32	float(PI / 32.f)
#define PI64	float(PI / 64.f)
#define PI128	float (PI / 128.f)

#define ONE_RAD (PI / 180)

#define MAPSIZEX 10
#define MAPSIZEY 10
#define TILESIZE 52
#define TILEMAXX 4
#define TILEMAXY 3

//�Ǽ� ��Һ��ϱ� ���� ���� (���� ���� ������� ����)
#define FLOAT_EPSILON 0.001f 
#define FLOAT_EQUAL(f1, f2)		(fabs(f1 - f2) <= FLOAT_EPSILON) //�� �Ǽ��� ������ Ȯ��

#define TILENUM 15
#define WIDTH 192

enum TILESTATE
{
	S_NONE, S_ICE, S_FIRE
};

enum MAPNAME
{
	M_NONE, M_CAMP, M_FLOOPY, M_ICE
};

struct TagTile
{
	image* image;			// Ÿ���� �̹���
	RECT rc;				// Ÿ���� ��Ʈ (���̼�Ÿ���̶��ؼ� �������� �κи� ��Ʈ�� �����ϸ� ����)
	POINT pivot;			// Ÿ�� ��Ʈ�� �߽���
	TILESTATE state;		// Ÿ���� ����
	MAPNAME mapName;		// Ÿ�ϸ��̸� (�̰� �����ص� ��. ũ�Ʊ������� ��������Ŷ� ice�� ķ���� �̷������� �־ ���������)
	TagTile* parent;		// A* �ش�Ÿ���� �θ�
	int x, y;				// Ÿ�����ε��� x, y
	int width;				// Ÿ���� ��
	int height;				// Ÿ���� ����
	int imageNum;			// �̹��� ��������
	int number;				// Ÿ���� ���� �ѹ��� 
	int f, g, h;			// A* �ʿ��� ������
	bool draw;				// Ÿ�� �׷��� ���� ( �� Ÿ������ �̹����� �׷����ִ��� Ȯ�� ����)
};

namespace MY_UTIL
{
	//�Ÿ� ���ϴ� �Լ�
	float getDistance(float startX, float startY, float endX, float endY);

	//���� ���ϴ� �Լ�
	float getAngle(float startX, float startY, float endX, float endY);
}
