#include "stdafx.h"
#include "cUI_SkillDeck.h"


cUI_SkillDeck::cUI_SkillDeck()
{
}


cUI_SkillDeck::~cUI_SkillDeck()
{
}


void cUI_SkillDeck::init()
{
	m_UIDeck.x = WINSIZE_X / 2 - 315;
	m_UIDeck.y = WINSIZE_Y - 80;
	m_UIDeck.img = RESOURCE_TEXTURE->GetResource("../Resources/UI/UI_SkillDeck.tga");
	m_UIDeck.rc = RectMake(0, 0, 256, 64);


	m_UIDeckNumFront.x = WINSIZE_X / 2 - 315;
	m_UIDeckNumFront.y = WINSIZE_Y - 80;
	m_UIDeckNumFront.img = RESOURCE_TEXTURE->GetResource("../Resources/UI/UI_SkillDeckNumFront.tga");
	m_UIDeckNumFront.rc = RectMake(0, 0, 256, 64);

	m_UIDeckBack.x = WINSIZE_X / 2 + 60;
	m_UIDeckBack.y = WINSIZE_Y - 80;
	m_UIDeckBack.img = RESOURCE_TEXTURE->GetResource("../Resources/UI/UI_SkillDeck.tga");
	m_UIDeckBack.rc = RectMake(0, 0, 256, 64);

	m_UIDeckNumBack.x = WINSIZE_X / 2 + 60;
	m_UIDeckNumBack.y = WINSIZE_Y - 80;
	m_UIDeckNumBack.img = RESOURCE_TEXTURE->GetResource("../Resources/UI/UI_SkillDeckNumBack.tga");
	m_UIDeckNumBack.rc = RectMake(0, 0, 256, 64);

	for (int i = 0; i < SKILLNUM; i++)
	{
		m_UISkillBtn[i].x = WINSIZE_X / 2 - 315 + 51*i;
		m_UISkillBtn[i].y = WINSIZE_Y - 78;
		m_UISkillBtn[0].img = RESOURCE_TEXTURE->GetResource("../Resources/UI/UI_Skill_Mage1.tga");
		m_UISkillBtn[1].img = RESOURCE_TEXTURE->GetResource("../Resources/UI/UI_Skill_Mage2.tga");
		m_UISkillBtn[2].img = RESOURCE_TEXTURE->GetResource("../Resources/UI/UI_Skill_Mage3.tga");
		m_UISkillBtn[3].img = RESOURCE_TEXTURE->GetResource("../Resources/UI/UI_Skill_Mage4.tga");
		m_UISkillBtn[4].img = RESOURCE_TEXTURE->GetResource("../Resources/UI/UI_Skill_Mage5.tga");
		m_UISkillBtn[i].rc = RectMake(0, 0, 64, 64);
		m_UISkillBtn[i].rcColl = RectMake(m_UISkillBtn[i].x, m_UISkillBtn[i].y, 48, 48);

	}

	isBerserker = false;
	

}


void cUI_SkillDeck::update()
{
	if (KEY_MGR->IsOnceDown('N'))
	{
		if (isBerserker) isBerserker = false;
		else isBerserker = true;
	}

	if (isBerserker)
	{
		m_UISkillBtn[0].img = RESOURCE_TEXTURE->GetResource("../Resources/UI/UI_Skill_Ber1.tga");
		m_UISkillBtn[1].img = RESOURCE_TEXTURE->GetResource("../Resources/UI/UI_Skill_Ber2.tga");
		m_UISkillBtn[2].img = RESOURCE_TEXTURE->GetResource("../Resources/UI/UI_Skill_Ber3.tga");
		m_UISkillBtn[3].img = RESOURCE_TEXTURE->GetResource("../Resources/UI/UI_Skill_Ber4.tga");
		m_UISkillBtn[4].img = RESOURCE_TEXTURE->GetResource("../Resources/UI/UI_Skill_Ber5.tga");
	}

	if (!isBerserker)
	{
		m_UISkillBtn[0].img = RESOURCE_TEXTURE->GetResource("../Resources/UI/UI_Skill_Mage1.tga");
		m_UISkillBtn[1].img = RESOURCE_TEXTURE->GetResource("../Resources/UI/UI_Skill_Mage2.tga");
		m_UISkillBtn[2].img = RESOURCE_TEXTURE->GetResource("../Resources/UI/UI_Skill_Mage3.tga");
		m_UISkillBtn[3].img = RESOURCE_TEXTURE->GetResource("../Resources/UI/UI_Skill_Mage4.tga");
		m_UISkillBtn[4].img = RESOURCE_TEXTURE->GetResource("../Resources/UI/UI_Skill_Mage5.tga");
	}
	
	for (int i = 0; i < SKILLNUM; i++)
	{
		POINT ptMousePos = GetMousePos();
		D3DXVECTOR2 screenPos(ptMousePos.x, ptMousePos.y);

		if (PtInRect(&m_UISkillBtn[i].rcColl, ptMousePos))
		{
			if (KEY_MGR->IsOnceDown(VK_LBUTTON))
			{
				if (m_UISkillBtn[i].isClick) m_UISkillBtn[i].isClick = false;
				else m_UISkillBtn[i].isClick = true;
			}


		}
	}

	



}

void cUI_SkillDeck::uiRender()
{
	SPRITE_MGR->DrawTexture(
		m_UIDeck.img,
		&m_UIDeck.rc,
		m_UIDeck.x, m_UIDeck.y,
		0xffffffff,
		NULL);

	SPRITE_MGR->DrawTexture(
		m_UIDeckBack.img,
		&m_UIDeckBack.rc,
		m_UIDeckBack.x, m_UIDeckBack.y,
		0xffffffff,
		NULL);



	//==========================================
	//스킬 아이콘들은 이 사이에 랜더를 해줍시다!
	for (int i = 0; i < SKILLNUM; i++)
	{
		SPRITE_MGR->DrawTexture(
			m_UISkillBtn[i].img,
			&m_UISkillBtn[i].rc,
			m_UISkillBtn[i].x, m_UISkillBtn[i].y,
			0xffffffff,
			NULL);
	}


	//=========================================


	SPRITE_MGR->DrawTexture(
		m_UIDeckNumFront.img,
		&m_UIDeckNumFront.rc,
		m_UIDeckNumFront.x, m_UIDeckNumFront.y,
		0xffffffff,
		NULL);

	SPRITE_MGR->DrawTexture(
		m_UIDeckNumBack.img,
		&m_UIDeckNumBack.rc,
		m_UIDeckNumBack.x, m_UIDeckNumBack.y,
		0xffffffff,
		NULL);
}

