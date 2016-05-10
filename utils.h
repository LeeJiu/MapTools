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

//실수 대소비교하기 위한 변수 (가장 작은 단위라고 보자)
#define FLOAT_EPSILON 0.001f 
#define FLOAT_EQUAL(f1, f2)		(fabs(f1 - f2) <= FLOAT_EPSILON) //두 실수가 같은지 확인

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
	image* image;			// 타일의 이미지
	RECT rc;				// 타일의 렉트 (아이소타일이라해서 보여지는 부분만 렉트라 생각하면 ㄴㄴ)
	POINT pivot;			// 타일 렉트의 중심점
	TILESTATE state;		// 타일의 상태
	MAPNAME mapName;		// 타일맵이름 (이건 변경해도 됨. 크아기준으로 만들었던거라 ice맵 캠프맵 이런식으로 있어서 나눠줬던것)
	TagTile* parent;		// A* 해당타일의 부모
	int x, y;				// 타일의인덱스 x, y
	int width;				// 타일의 폭
	int height;				// 타일의 높이
	int imageNum;			// 이미지 가져오기
	int number;				// 타일의 고유 넘버값 
	int f, g, h;			// A* 필요한 변수값
	bool draw;				// 타일 그려진 유무 ( 이 타일위에 이미지가 그려져있는지 확인 유무)
};

namespace MY_UTIL
{
	//거리 구하는 함수
	float getDistance(float startX, float startY, float endX, float endY);

	//각도 구하는 함수
	float getAngle(float startX, float startY, float endX, float endY);
}
