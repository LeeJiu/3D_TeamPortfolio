#include "stdafx.h"
#include "cInven.h"


cInven::cInven()
{
	row = INVEN_COUNT;
	col = INVEN_COUNT;
	invenOpen = false;
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
			inven[i][j].x = WINSIZE_X / 2 + (j * RECT_SIZE) + 150;
			//(i * RECT_SIZE) + WINSIZE_X / 2
			//WINSIZE_Y / 2 + (j * RECT_SIZE);
			inven[i][j].y = (i * RECT_SIZE) + WINSIZE_Y / 2 - 150;
			inven[i][j].rcSize = RectMake(0, 0, RECT_SIZE, RECT_SIZE);
			inven[i][j].rcColl = RectMake(inven[i][j].x, inven[i][j].y, RECT_SIZE, RECT_SIZE);
			inven[i][j].skillImage = NULL;
			inven[i][j].isPoint = false; // 진짜 포인트가지고 있는 놈
			inven[i][j].itemNum = 0;//아이템은 1부터 만들어짐. 
			inven[i][j].i = i;
			inven[i][j].j = j;

		}
		//RECT rc = { 0, 0, 100, 100 };
		//skillBotton[i].rc = RectMake(10 + i * 64, 636, 64, 64);
	}

	weapon.m_Item = NULL;
	weapon.x = WINSIZE_X / 2 + 150;
	weapon.y = WINSIZE_Y / 2 - 250;
	weapon.skillImage = NULL;
	weapon.rcSize = RectMake(0, 0, RECT_SIZE, RECT_SIZE);
	weapon.rcColl = RectMake(weapon.x, weapon.y, RECT_SIZE, RECT_SIZE);
	weapon.isPoint = false; // 진짜 포인트가지고 있는 놈
	weapon.itemNum = 0;//아이템은 1부터 만들어짐. 


	clickItem = NULL;
	pickUp = false;
}
void cInven::release()
{
	for (int i = 0; i < INVEN_COUNT; i++)
	{
		for (int j = 0; j < INVEN_COUNT; j++)
		{
				if (inven[i][j].m_Item != NULL && inven[i][j].isPoint == true)
				{
				SAFE_DELETE(inven[i][j].m_Item);
				}
		}
	}

	if (weapon.m_Item != NULL)
	{
		SAFE_DELETE(weapon.m_Item);
	}
}
void cInven::update(float timeDelta, cCamera* camera, D3DXVECTOR3& pos)
{
	/* itemIndex 가 -1 일때는 아이템들고 있는게 없을 때
	clickItem = NULL
	인벤토리에 들어가기 전에는 아이템 매니져에서 들고 있음.
	pickUp <- 아이템 들고 있을때 T,
	*/

	//인벤토리 열고 닫기. 
	//if (KEY_MGR->IsOnceDown('I'))
	{
		//invenOpen = !invenOpen;
	}
	// 물건을 들고 있을때 
	// 화면 가운데 오브젝트를 가져 온다. 


	if (pickUp == true)
	{
		if (clickItem != NULL)
		{
			clickItem->m_lifeTime = 60.f;
			clickItem->pTransform->SetWorldPosition(
				camera->GetWorldPosition().x + camera->GetForward().x * 10,
				camera->GetWorldPosition().y + camera->GetForward().y * 10,
				camera->GetWorldPosition().z + camera->GetForward().z * 10);

			clickItem->pTransform->LookPosition(camera->GetWorldPosition());
		}
	}

	if (KEY_MGR->IsOnceDown(VK_LBUTTON))
	{

		int cRow = 0;
		int cCol = 0;
		Ray ray;
		POINT ptMousePos = GetMousePos();
		D3DXVECTOR2 screenPos(ptMousePos.x, ptMousePos.y);
		camera->ComputeRay(&ray, &screenPos);


		discard(&cRow, &cCol, ptMousePos, pos);

		//  바운드 충돌을 해서 아이템 인덱스를 찾아 낸다. 
		for (int i = 0; i < ITEM_MGR->v_item.size(); i++)
		{
			if (PHYSICS_MGR->IsRayHitBound(&ray, &(ITEM_MGR->v_item[i]->BoundBox), (ITEM_MGR->v_item[i])->pTransform, NULL, NULL))
			{
				LOG_MGR->AddLog("오브젝트 충돌");
				clickItem = ITEM_MGR->v_item[i];
				pickUp = true;
				itemIndex = i;
				break;
			}
		}


		if (clickItem == NULL) // 클릭된 아이템이 없을 때
		{
			//인벤 클릭해서 아이템이 있으면 매니져로
			if (invenToManager(&cRow, &cCol, ptMousePos))
			{

			}
			// 웨폰 클릭해서 아이템이 있으면 매니져로
			else if (weaponToManager(ptMousePos))
			{

			}

		}
		else if (clickItem != NULL) //클릭된 아이템이 있을 떄
		{
			//인벤에 넣는다.
			if (invenInputItem(&cRow, &cCol, clickItem, ptMousePos))
			{
				SOUND_MGR->play("inputWeapon",0.8);
			}//웨폰에 넣는다. 
			else if (weaponInputItem(clickItem, ptMousePos))
			{

			}

		}

	}


}

void cInven::render()
{
	// 이벤토리 열었을 때.
	if (invenOpen == true)
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
						0xffffffff,
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
			//LOG_MGR->AddLog("이지현 즐 : %d", weapon.m_Item->m_Dmg);

		}

		//=====================================
	}


}

bool cInven::invenInputItem(int* row, int* coll, cItem* item, POINT mouse)
{
	if (invenOpen == false)return false;
	if (clickItem == NULL)return false;
	if (itemIndex == -1)return false;

	// 인벤토리에 클릭 됐는지 안됐는지
	if (invenSelectRect(row, coll, mouse) == false)return false;



	int tempRow = *row + item->getRow();
	int tempColl = *coll + item->getColl();

	// 인벤토리 넘어갔을 때 
	if (tempRow > INVEN_COUNT || tempColl > INVEN_COUNT)
	{
		return false;
	}

	// 넣을 수 있는지 확인
	for (int i = *row; i < tempRow; i++)
	{
		for (int j = *coll; j < tempColl; j++)
		{
			if (inven[i][j].itemNum != 0) // 0이 아니라면 아이템이 들어 있는것.
			{
				return false;
			}
		}
	}


	for (int i = *row; i < tempRow; i++)
	{
		for (int j = *coll; j < tempColl; j++)
		{
			if (i == *row&& j == *coll)
			{
				inven[i][j].m_Item = clickItem;
				inven[i][j].isPoint = true;
				inven[i][j].itemNum = clickItem->getItemNum();
				inven[i][j].rcSize = RectMake(0, 0, item->getRow()*RECT_SIZE, item->getColl()*RECT_SIZE);
				// 아이템 string 값으로 이미지 소스 바꺼줘야댐			
				inven[i][j].skillImage = findIcon(item->getItemName());

				//inven[i][j].skillImage = RESOURCE_TEXTURE->GetResource("../Resources/UI/fot_lightingspear.bmp");
			}
			else
			{
				//	inven[i][j].m_Item = clickItem;
				inven[i][j].m_Item = clickItem;
				inven[i][j].isPoint = false;
				inven[i][j].itemNum = clickItem->getItemNum();

				//inven[i][j].skillImage = RESOURCE_TEXTURE->GetResource("../Resources/UI/fot_lightingspear.bmp");

			}
		}
	}

	//아이템 인덱스 = 아이템 매니져의 vector에 비긴+index값
	itemIndex = ITEM_MGR->findItem(clickItem->getItemNum());
	// 매니져에서 아이템 지울때 
	ITEM_MGR->v_item.erase(ITEM_MGR->v_item.begin() + itemIndex);
	clickItem = NULL;
	itemIndex = -1;
	pickUp = false;

	return true;
}

bool cInven::invenSelectRect(int* row, int* coll, POINT mouse)
{
	for (int i = 0; i < INVEN_COUNT; i++)
	{
		for (int j = 0; j < INVEN_COUNT; j++)
		{
			if (PtInRect(&inven[i][j].rcColl, mouse))
			{
				*row = i;
				*coll = j;
				return true;
			}
		}
	}

	return false;
}
D3DXVECTOR3 cInven::screenPos(int x, int y)
{


	D3DVIEWPORT9 vp;
	Device->GetViewport(&vp); // 뷰포트 구조체를 받아온다.

	D3DXMATRIXA16 matProj; // 뷰 행렬
	Device->GetTransform(D3DTS_PROJECTION, &matProj);

	//int rndX = vp.Width / 2;//rand() % WINSIZE_X;
	//int rndY = vp.Height / 2;//rand() % WINSIZE_Y;
	int rndX = x;
	int rndY = y;//rand() % WINSIZE_Y;
	D3DXVECTOR3 Org(0, 0, 0), Dir(0, 0, 0); //Org 카메라의 위치 = eye / dir = lookAt 
	Dir.x = ((2.0f * rndX) / vp.Width - 1.0f) / matProj._11;
	Dir.y = ((-2.0f * rndY) / vp.Height + 1.0f) / matProj._22;
	Dir.z = 1.0f;

	D3DXVec3Normalize(&Dir, &Dir);

	D3DXMATRIXA16 matView, InverView; // 뷰 행렬

	Device->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&InverView, 0, &matView);
	D3DXVec3TransformCoord(&Org, &Org, &InverView);
	D3DXVec3TransformNormal(&Dir, &Dir, &InverView);
	D3DXVec3Normalize(&Dir, &Dir);

	D3DXVECTOR3 screenPos;
	//
	float d = -Org.y / Dir.y;

	screenPos.x = d * Dir.x + Org.x; // Org 원점.
	screenPos.z = d * Dir.z + Org.z;
	screenPos.y = d * Dir.y + Org.y;

	return screenPos;
}


LPDIRECT3DTEXTURE9 cInven::findIcon(string name)
{
	//m_staff ,m_axe
	if (strcmp(name.c_str(), "m_staff") == 0)
	{
		return RESOURCE_TEXTURE->GetResource("../Resources/UI/fot_lightingspear.bmp");
	}
	else if (strcmp(name.c_str(), "m_axe") == 0)
	{
		return RESOURCE_TEXTURE->GetResource("../Resources/UI/fot_firestorm.bmp");
	}
	return RESOURCE_TEXTURE->GetResource("../Resources/UI/ele_tonadoflare.bmp");

}


bool cInven::weaponSelectRect(POINT mouse)
{
	if (PtInRect(&weapon.rcColl, mouse))
	{
		return true;
	}
	return false;
}

bool cInven::weaponInputItem(cItem* item, POINT mouse)
{
	if (invenOpen == false)return false;
	if (clickItem == NULL)return false;
	if (itemIndex == -1)return false;

	if (weaponSelectRect(mouse) == false)return false;

	weapon.m_Item = clickItem;
	weapon.skillImage = findIcon(clickItem->getItemName());
	weapon.itemNum = clickItem->getItemNum();
	itemIndex = ITEM_MGR->findItem(clickItem->getItemNum());
	//아이템 회전값 기본으로 바꺼줌. 
	weapon.m_Item->pTransform->SetRotateWorld(weapon.m_Item->getBasicRotaion());
	if (itemIndex != -1)
	{
		ITEM_MGR->v_item.erase(ITEM_MGR->v_item.begin() + itemIndex);
	}
	//
	clickItem = NULL;
	pickUp = false;
	itemIndex = -1;

}

bool cInven::invenToManager(int* row, int* coll, POINT mouse)
{
	if (invenOpen == false)return false;//인벤이 열리지 않았다면. 
	if (clickItem != NULL)return false; // 손에 들고 있는게 없어야된다.

	//인벤토리클릭
	if (invenSelectRect(row, coll, mouse) == false)return false;
	//빈 인벤토리가 아니라면
	if (inven[*row][*coll].itemNum == 0)return false;

	int tempItemNum = inven[*row][*coll].itemNum;
	pickUp = true; //트루.
	clickItem = inven[*row][*coll].m_Item;//아이템 넣고 .
	clickItem->m_lifeTime = 60.f;
	ITEM_MGR->v_item.push_back(clickItem);//

	// 인벤토리 초기화.
	for (int i = 0; i < INVEN_COUNT; i++)
	{
		for (int j = 0; j < INVEN_COUNT; j++)
		{
			if (inven[i][j].itemNum == tempItemNum)
			{
				inven[i][j].m_Item = NULL;
				inven[i][j].skillImage = NULL;
				inven[i][j].isPoint = false; // 진짜 포인트가지고 있는 놈
				inven[i][j].itemNum = 0;//아이템은 1부터 만들어짐. 
			}
		}
	}

	itemIndex = ITEM_MGR->findItem(clickItem->getItemNum());


}

bool cInven::weaponToManager(POINT mouse)
{
	if (invenOpen == false)return false;//인벤이 열리지 않았다면. 
	if (clickItem != NULL)return false; // 손에 들고 있는게 없어야된다.

	//인벤토리클릭
	if (weaponSelectRect(mouse) == false)return false;
	//빈 인벤토리가 아니라면
	if (weapon.itemNum == 0)return false;

	int tempItemNum = weapon.itemNum;
	pickUp = true; //트루.
	clickItem = weapon.m_Item;//아이템 넣고 .
	clickItem->m_lifeTime = 60.f;

	ITEM_MGR->v_item.push_back(clickItem);//

	weapon.m_Item = NULL;
	weapon.skillImage = NULL;
	weapon.isPoint = false; // 진짜 포인트가지고 있는 놈
	weapon.itemNum = 0;//아이템은 1부터 만들어짐. 


	itemIndex = ITEM_MGR->findItem(clickItem->getItemNum());

}

void cInven::discard(int* row, int* coll, POINT mouse, D3DXVECTOR3& pos)
{
	//케릭터 좌표 =================================== 받아야댐 =
	if (clickItem != NULL)
	{
		if (invenSelectRect(row, coll, mouse) == true) return;
		if (weaponSelectRect(mouse) == true) return;

		clickItem->pTransform->SetWorldPosition(D3DXVECTOR3(pos.x, pos.y, pos.z));
		itemIndex = -1;
		clickItem = NULL;
		pickUp = false;
	}

}