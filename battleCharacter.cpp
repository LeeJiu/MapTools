#include "stdafx.h"
#include "battleCharacter.h"


battleCharacter::battleCharacter()
{
}


battleCharacter::~battleCharacter()
{
}

HRESULT battleCharacter::init()
{
	_character.imageCharacter = new image;
	_character.imageCharacter->init("image/priny.bmp", 714, 484, 7, 4, true, 0xff00ff);
	
	
	return E_NOTIMPL;
}

void battleCharacter::release()
{
}

void battleCharacter::update()
{
}

void battleCharacter::render()
{
}

void battleCharacter::characterMoveFrameSet(CHARACTER_DIRECTION direction)
{
	

}
