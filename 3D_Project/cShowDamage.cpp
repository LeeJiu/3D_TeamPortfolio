#include "stdafx.h"
#include "cShowDamage.h"


cShowDamage::cShowDamage()
{
}

cShowDamage::~cShowDamage()
{
}

void cShowDamage::Init()
{
	
}

void cShowDamage::SetNumber(int number, cTransform * trans)
{
	char temp[32];

	num = 0;
	num = number;
	if (num != 0)
	{
		if (num <= 0 && num < 10)
		{
			stDamage damage;
			damage.unit = num;
			damage.Rc = RectMake(0, 0, TEX_WIDTH, TEX_HEIGHT);
			damage.unit_x = WINSIZE_X / 2;
			damage.unit_y = WINSIZE_Y / 2;
			char temp[32];
			sprintf_s(temp, "../Resources/Textures/num_%d.tga", damage.unit);
			damage.unit_tex = RESOURCE_TEXTURE->GetResource(temp);
			damage.countTime = 0;
			damage.time = 1;
			damage.isDrawing = true;
			damage.isEnd = false;
			damage.tens_tex = NULL;		//다음자리 숫자 텍스쳐에 널값을 넣어서 랜더 막을거임.

			v_damage.push_back(damage);
		}
		else if (num >= 10 && num < 100)
		{
			stDamage damage;
			damage.unit = (num % 10);
			damage.tens = (num / 10);
			damage.Rc = RectMake(0, 0, TEX_WIDTH, TEX_HEIGHT);
			damage.unit_x = WINSIZE_X / 2;
			damage.unit_y = WINSIZE_Y / 2;
			char temp[32];
			sprintf_s(temp, "../Resources/Textures/num_%d.tga", damage.unit);
			damage.unit_tex = RESOURCE_TEXTURE->GetResource(temp);
			sprintf_s(temp, "../Resources/Textures/num_%d.tga", damage.tens);
			damage.tens_tex = RESOURCE_TEXTURE->GetResource(temp);
			damage.countTime = 0;
			damage.time = 1;
			damage.isDrawing = true;
			damage.isEnd = false;
			damage.hund_tex = NULL;		//다음자리 숫자 텍스쳐에 널값을 넣어서 랜더 막을거임.

			v_damage.push_back(damage);
		}
		else if (num >= 100 && num < 1000)
		{
			stDamage damage;
			damage.unit = (num % 10);
			damage.tens = (number / 10) % 10;
			damage.hund = (number / 100);
			damage.Rc = RectMake(0, 0, TEX_WIDTH, TEX_HEIGHT);
			damage.unit_x = WINSIZE_X / 2;
			damage.unit_y = WINSIZE_Y / 2;
			char temp[32];
			sprintf_s(temp, "../Resources/Textures/num_%d.tga", damage.unit);
			damage.unit_tex = RESOURCE_TEXTURE->GetResource(temp);
			sprintf_s(temp, "../Resources/Textures/num_%d.tga", damage.tens);
			damage.tens_tex = RESOURCE_TEXTURE->GetResource(temp);
			sprintf_s(temp, "../Resources/Textures/num_%d.tga", damage.hund);
			damage.hund_tex = RESOURCE_TEXTURE->GetResource(temp);
			damage.countTime = 0;
			damage.time = 1;
			damage.isDrawing = true;
			damage.isEnd = false;
			damage.thou_tex = NULL;		//다음자리 숫자 텍스쳐에 널값을 넣어서 랜더 막을거임.

			v_damage.push_back(damage);
		}
		else if (1000 <= num && num < 10000)
		{
			stDamage damage;
			damage.unit = (number % 10);
			damage.tens = (number / 10) % 10;
			damage.hund = (number / 100) % 10;
			damage.thou = (number / 1000) % 10;
			damage.Rc = RectMake(0, 0, TEX_WIDTH, TEX_HEIGHT);
			damage.unit_x = WINSIZE_X / 2;
			damage.unit_y = WINSIZE_Y / 2;
			char temp[32];
			sprintf_s(temp, "../Resources/Textures/num_%d.tga", damage.unit);
			damage.unit_tex = RESOURCE_TEXTURE->GetResource(temp);
			sprintf_s(temp, "../Resources/Textures/num_%d.tga", damage.tens);
			damage.tens_tex = RESOURCE_TEXTURE->GetResource(temp);
			sprintf_s(temp, "../Resources/Textures/num_%d.tga", damage.hund);
			damage.hund_tex = RESOURCE_TEXTURE->GetResource(temp);
			sprintf_s(temp, "../Resources/Textures/num_%d.tga", damage.thou);
			damage.thou_tex = RESOURCE_TEXTURE->GetResource(temp);
			damage.countTime = 0;
			damage.time = 1;
			damage.isDrawing = true;
			damage.isEnd = false;
			damage.mil_tex = NULL;		//다음자리 숫자 텍스쳐에 널값을 넣어서 랜더 막을거임.

			v_damage.push_back(damage);

		}
	}
}

//삭제 원활하지 못하면 큐로바꺼
void cShowDamage::Clean()
{
	for (vi_damage = v_damage.begin(); vi_damage != v_damage.end(); )
	{
		if (!vi_damage->isEnd)
		{
			vi_damage++;
		}
		else if(vi_damage->isEnd)
		{
			vi_damage = v_damage.erase(vi_damage);
		}
	}
}

void cShowDamage::Update(float timeDelta)
{
	size = v_damage.size();

	for (int i = 0; i < size; i++)
	{
		if (!v_damage[i].isDrawing) continue;

		v_damage[i].countTime += timeDelta;
		v_damage[i].unit_y -= 1.5;

		if (v_damage[i].countTime > v_damage[i].time)
		{
			v_damage[i].isDrawing = false;
			v_damage[i].isEnd = true;
		}
	}

	//Clean();  //터질지도모르니 일단 숨키자.
}

void cShowDamage::Render()
{
	for (int i = 0; i < size; i++)
	{
		if (!v_damage[i].isEnd)
		{
			if (v_damage[i].unit_tex != NULL && v_damage[i].tens_tex == NULL)
			{
				SPRITE_MGR->DrawTexture(
					v_damage[i].unit_tex,
					&v_damage[i].Rc,
					v_damage[i].unit_x,
					v_damage[i].unit_y,
					0xf0ffffff,
					NULL
				);
			}
			else if (v_damage[i].tens_tex !=NULL && v_damage[i].hund_tex == NULL)
			{
				SPRITE_MGR->DrawTexture(
					v_damage[i].unit_tex,
					&v_damage[i].Rc,
					v_damage[i].unit_x,
					v_damage[i].unit_y,
					0xf0ffffff,
					NULL
				);

				SPRITE_MGR->DrawTexture(
					v_damage[i].tens_tex,
					&v_damage[i].Rc,
					v_damage[i].unit_x - 20,
					v_damage[i].unit_y,
					0xf0ffffff,
					NULL
				);
			}
			else if (v_damage[i].hund_tex != NULL && v_damage[i].thou_tex == NULL)
			{
				SPRITE_MGR->DrawTexture(
					v_damage[i].unit_tex,
					&v_damage[i].Rc,
					v_damage[i].unit_x,
					v_damage[i].unit_y,
					0xf0ffffff,
					NULL
				);

				SPRITE_MGR->DrawTexture(
					v_damage[i].tens_tex,
					&v_damage[i].Rc,
					v_damage[i].unit_x - 25,
					v_damage[i].unit_y,
					0xf0ffffff,
					NULL
				);

				SPRITE_MGR->DrawTexture(
					v_damage[i].hund_tex,
					&v_damage[i].Rc,
					v_damage[i].unit_x - 50,
					v_damage[i].unit_y,
					0xf0ffffff,
					NULL
				);
			}
			else if (v_damage[i].thou_tex != NULL && v_damage[i].mil_tex == NULL)
			{
				SPRITE_MGR->DrawTexture(
					v_damage[i].unit_tex,
					&v_damage[i].Rc,
					v_damage[i].unit_x,
					v_damage[i].unit_y,
					0xf0ffffff,
					NULL
				);

				SPRITE_MGR->DrawTexture(
					v_damage[i].tens_tex,
					&v_damage[i].Rc,
					v_damage[i].unit_x - 25,
					v_damage[i].unit_y,
					0xf0ffffff,
					NULL
				);

				SPRITE_MGR->DrawTexture(
					v_damage[i].hund_tex,
					&v_damage[i].Rc,
					v_damage[i].unit_x - 50,
					v_damage[i].unit_y,
					0xf0ffffff,
					NULL
				);

				SPRITE_MGR->DrawTexture(
					v_damage[i].thou_tex,
					&v_damage[i].Rc,
					v_damage[i].unit_x - 75,
					v_damage[i].unit_y,
					0xf0ffffff,
					NULL
				);
			}
		}
	}
}
