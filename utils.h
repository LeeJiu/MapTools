#pragma once


#include <cmath>

#define PI      3.141592654f
#define PI2      (PI * 2)
#define PI8      float(PI / 8.0f)
#define PI16   float(PI / 16.f)
#define PI32   float(PI / 32.f)
#define PI64   float(PI / 64.f)
#define PI128   float (PI / 128.f)

#define ONE_RAD (PI / 180)

#define MAPSIZEX 10
#define MAPSIZEY 10
#define TILESIZE 52
#define TILEMAXX 4
#define TILEMAXY 3

//�Ǽ� ��Һ��ϱ� ���� ���� (���� ���� ������� ����)
#define FLOAT_EPSILON 0.001f 
#define FLOAT_EQUAL(f1, f2)      (fabs(f1 - f2) <= FLOAT_EPSILON) //�� �Ǽ��� ������ Ȯ��

#define TILENUM 15
#define WIDTH 128
#define OFFSET 48
#define TOTALTILE(tileNum) (tileNum) * (tileNum)

enum TILESTATE
{
	S_NONE, S_ECT, S_ONOBJ, S_ONENM, ZEN_POINT, BOSS, S_ONCHAR
};

enum OBJSTATE
{
	S_NOMAL, S_ZEN, E_NORMAL, E_BOSS
};

struct TagTile
{
	image* image;         // Ÿ���� �̹���
	RECT rc;            // Ÿ���� ��Ʈ (���̼�Ÿ���̶��ؼ� �������� �κи� ��Ʈ�� �����ϸ� ����)
	//POINT pivot;         // Ÿ�� ��Ʈ�� �߽���
	float pivotX;
	float pivotY;
	TILESTATE state;      // Ÿ���� ����
	TagTile* parent;      // A* �ش�Ÿ���� �θ�
	int x, y;            // Ÿ�����ε��� x, y
	int width;            // Ÿ���� ��
	int height;            // Ÿ���� ����
	int imageNum;         // �̹��� ��������
	int number;            // Ÿ���� ���� �ѹ��� 
	int f, g, h;         // A* �ʿ��� ������
	bool draw;            // Ÿ�� �׷��� ���� ( �� Ÿ������ �̹����� �׷����ִ��� Ȯ�� ����)
};

struct TagObject
{
	image* image;			// Ÿ���� �̹���
	RECT rc;				// Ÿ���� ��Ʈ (���̼�Ÿ���̶��ؼ� �������� �κи� ��Ʈ�� �����ϸ� ����)
	POINT pivot;			// Ÿ�� ��Ʈ�� �߽���
	int x, y;				// Ÿ�����ε��� x, y
	int width;				// Ÿ���� ��
	int height;				// Ÿ���� ����
	int imageNum;			// �̹��� ��������
	int number;				// Ÿ���� ���� �ѹ��� 
	bool draw;
	OBJSTATE state;
};

struct OBJ_Y_RENDER
{
	bool operator()(const TagObject* obj1, const TagObject* obj2)
	{
		return obj1->pivot.y < obj2->pivot.y;
	}
};

struct OBJ_NUM
{
	bool operator()(const TagObject* obj1, const TagObject* obj2)
	{
		return obj1->number < obj2->number;
	}
};

struct tagItem
{
	image* image;
	RECT rc;
	char* name;
	char* info;
	int atk;
	int intel;
	int def;
	int spd;
	int hit;
	int res;
	int buyPrice;   //�÷��̾ �� �� ����
	int sellPrice;   //�÷��̾ �� �� ����
};


namespace MY_UTIL
{
	//�Ÿ� ���ϴ� �Լ�
	float getDistance(float startX, float startY, float endX, float endY);

	//���� ���ϴ� �Լ�
	float getAngle(float startX, float startY, float endX, float endY);
}

enum CHARACTER_STATE
{
	IDLE, WALK, ATTACK, LIFT, PAIN, ETC
};

enum CHARACTER_DIRECTION
{
	LB, RB, RT, LT
};