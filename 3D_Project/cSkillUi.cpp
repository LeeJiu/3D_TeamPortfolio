#include "stdafx.h"
#include "cSkillUi.h"


cSkillUi::cSkillUi()
{
}


cSkillUi::~cSkillUi()
{
}
void cSkillUi::init()
{
    // WINSIZE_X	1280		//초기 윈도우 가로 크기
    // WINSIZE_Y	720			//초기 윈도우 세로 크기
	
	emtyBotton.skillImage = RESOURCE_TEXTURE->GetResource("../Resources/UI/skill_deck.bmp");
	emtyBotton.rcSize = RectMake(0, 0, 64, 64);

	for (int i = 0; i < SKILLNUM; i++)
	{
		skillBotton[i].x = 10*i + (i * 64)+WINSIZE_X/2;
		skillBotton[i].y = 636;
		skillBotton[i].skillImage = NULL;
		skillBotton[i].rcSize = RectMake(0, 0, 64, 64);
		skillBotton[i].rcColl = RectMake(skillBotton[i].x, skillBotton[i].y, 64, 64);
		//RECT rc = { 0, 0, 100, 100 };
		//skillBotton[i].rc = RectMake(10 + i * 64, 636, 64, 64);
	}

}
void cSkillUi::update()
{
	if (KEY_MGR->IsOnceDown(VK_LBUTTON))
	{
		POINT ptMousePos = GetMousePos();
		//D3DXVECTOR2 screenPos(ptMousePos.x, ptMousePos.y);
		for (int i = 0; i < SKILLNUM; i++)
		{
			if (PtInRect(&skillBotton[i].rcColl, ptMousePos))
			{
				LOG_MGR->AddLog("i = %d",
					i);
			}

		}
	}
}

void cSkillUi::uiRender()
{

	for (int i = 0; i < SKILLNUM; i++)
	{
		SPRITE_MGR->DrawTexture(
			emtyBotton.skillImage,
			&emtyBotton.rcSize,
			skillBotton[i].x, skillBotton[i].y,
			0xf0ffffff,
			NULL);

		if (skillBotton[i].skillImage != NULL)
		{
			SPRITE_MGR->DrawTexture(
				skillBotton[i].skillImage,
				&skillBotton[i].rcSize,
				skillBotton[i].x, skillBotton[i].y,
				0x80ffffff,
				NULL);
		}
	}
}
