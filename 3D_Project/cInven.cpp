#include "stdafx.h"
#include "cInven.h"


cInven::cInven()
{
	row = INVEN_COUNT;
	col = INVEN_COUNT;
	isActive = false;
}


cInven::~cInven()
{
}

void cInven::init()
{
	emptyInven.skillImage = RESOURCE_TEXTURE->GetResource("../Resources/UI/skill_deck.bmp");
	emptyInven.rcSize = RectMake(0, 0, RECT_SIZE, RECT_SIZE);

	//i 행 , j 열
	for (int i = 0; i < INVEN_COUNT; i++)
	{
		for (int j = 0; j < INVEN_COUNT; j++)
		{
			inven[i][j].m_Item = NULL;
			inven[i][j].x = WINSIZE_X / 2 + (j * RECT_SIZE);
			//(i * RECT_SIZE) + WINSIZE_X / 2
			//WINSIZE_Y / 2 + (j * RECT_SIZE);
			inven[i][j].y = (i * RECT_SIZE) + WINSIZE_Y / 2;
			inven[i][j].skillImage = NULL;
			inven[i][j].rcSize = RectMake(0, 0, RECT_SIZE, RECT_SIZE);
			inven[i][j].rcColl = RectMake(inven[i][j].x, inven[i][j].y, RECT_SIZE, RECT_SIZE);
			inven[i][j].isPoint = false; // 진짜 포인트가지고 있는 놈
			inven[i][j].itemNum = 0;//아이템은 1부터 만들어짐. 
			inven[i][j].i = i;
			inven[i][j].j = j;

		}
		//RECT rc = { 0, 0, 100, 100 };
		//skillBotton[i].rc = RectMake(10 + i * 64, 636, 64, 64);
	}

	weapon.m_Item = NULL;
	weapon.x = WINSIZE_X / 2;
	weapon.y = WINSIZE_Y / 2 - 100;
	weapon.skillImage = NULL;
	weapon.rcSize = RectMake(0, 0, RECT_SIZE, RECT_SIZE);
	weapon.rcColl = RectMake(weapon.x, weapon.y, RECT_SIZE, RECT_SIZE);
	weapon.isPoint = false; // 진짜 포인트가지고 있는 놈
	weapon.itemNum = 0;//아이템은 1부터 만들어짐. 

}
void cInven::update()
{
	if (KEY_MGR->IsOnceDown('I'))
	{
		isActive = !isActive;

	}

	if (KEY_MGR->IsOnceDown(VK_LBUTTON) && isActive == true)
	{

		POINT ptMousePos = GetMousePos();
		//D3DXVECTOR2 screenPos(ptMousePos.x, ptMousePos.y);
		for (int i = 0; i < INVEN_COUNT; i++)
		{
			for (int j = 0; j < INVEN_COUNT; j++)
			{
				if (PtInRect(&inven[i][j].rcColl, ptMousePos))
				{
					LOG_MGR->AddLog("i = %d , j = %d",
						inven[i][j].i, inven[i][j].j);
				}

			}
		}
	}
}

void cInven::render()
{
	if (isActive == true)
	{
		//------------------------------------
		for (int i = 0; i < INVEN_COUNT; i++)
		{
			for (int j = 0; j < INVEN_COUNT; j++)
			{

				SPRITE_MGR->DrawTexture(
					emptyInven.skillImage,
					&emptyInven.rcSize,
					inven[i][j].x, inven[i][j].y,
					0xf0ffffff,
					NULL);

				if (inven[i][j].skillImage != NULL)
				{
					SPRITE_MGR->DrawTexture(
						inven[i][j].skillImage,
						&inven[i][j].rcSize,
						inven[i][j].x, inven[i][j].y,
						0x80ffffff,
						NULL);
				}


			}

		}

		SPRITE_MGR->DrawTexture(
			emptyInven.skillImage,
			&emptyInven.rcSize,
			weapon.x, weapon.y,
			0xf0ffffff,
			NULL);

		if (weapon.skillImage != NULL)
		{
			SPRITE_MGR->DrawTexture(
				weapon.skillImage,
				&weapon.rcSize,
				weapon.x, weapon.y,
				0x80ffffff,
				NULL);
		}

		//=====================================
	}


}

bool cInven::inputItem(cItem* item)
{
	//i 행 , j 열
	for (int i = 0; i < INVEN_COUNT; i++)
	{
		for (int j = 0; j < INVEN_COUNT; j++)
		{
			// 2중 포문!
			if (inven[i][j].itemNum == 0)
			{
				// 인덱스가 인벤에 들어가는지 확인/
				int tempRow = item->getRow() + i;
				int tempCol = item->getColl() + j;

				// 인덱스 범위 들어가면
				if (tempRow < INVEN_COUNT &&tempCol < INVEN_COUNT)
				{
					for (int tempI = i; tempI < tempRow; tempI++)
					{
						for (int tempJ = j; tempJ < tempCol; tempJ++)
						{
							if (inven[tempI][tempJ].itemNum != 0)
							{
								break;
							}
						}
					}
				}
				else
				{
					return;
				}




			}

		}
	}
}