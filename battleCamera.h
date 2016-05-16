#pragma once
#include "gameNode.h"
class battleCamera : public gameNode
{
	TagTile* _tile[TILENUM][TILENUM];
	RECT _rc;
	////////   cameraTile   /////////
	int _cameraTileX, _cameraTileY;// cameraTile �ε��� x, y;
	float _scroolSpeed;				// cameraTile �ӵ�
	float _scroolAngle;				// cameraTile �̵�����

									//////   cameraCharacter   //////
	int _moveSpeed;					// cameraCharacter �ӵ�

	bool _isMapScrool;				// �� ��ũ�� ����
public:
	battleCamera();
	~battleCamera();

	HRESULT init(vector<TagTile*>& tile);
	void release();
	void update();
	void render();

	void setCameraTile(int x, int y);
	void setCameraCharacter(RECT rc);

	void cameraTile();
	void cameraCharacter(vector<TagTile*> cameraTile);
	void cameraFree();

};

