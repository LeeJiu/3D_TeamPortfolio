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

	//i �� , j ��
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
			inven[i][j].isPoint = false; // ��¥ ����Ʈ������ �ִ� ��
			inven[i][j].itemNum = 0;//�������� 1���� �������. 
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
	weapon.isPoint = false; // ��¥ ����Ʈ������ �ִ� ��
	weapon.itemNum = 0;//�������� 1���� �������. 

	pickUp = false;
}
void cInven::release()
{
	for (int i = 0; i < INVEN_COUNT; i++)
	{
		for (int j = 0; j < INVEN_COUNT; j++)
		{
			if (inven[i][j].m_Item != NULL)
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
void cInven::update(float timeDelta, cCamera* camera)
{
	if (KEY_MGR->IsOnceDown('I'))
	{
		invenOpen = !invenOpen;
	}
	//itemIndex = -1;
	// Ŭ�� ���� ��
	if (pickUp == true)
	{
		if (clickItem != NULL)
		{
			clickItem->pTransform->SetWorldPosition(
				camera->GetWorldPosition().x + camera->GetForward().x * 10,
				camera->GetWorldPosition().y + camera->GetForward().y * 10,
				camera->GetWorldPosition().z + camera->GetForward().z * 10);

			clickItem->pTransform->LookPosition(camera->GetWorldPosition());
		}
	}

	if (KEY_MGR->IsOnceDown(VK_LBUTTON))
	{

		int cRow, cCol;
		Ray ray;
		POINT ptMousePos = GetMousePos();
		D3DXVECTOR2 screenPos(ptMousePos.x, ptMousePos.y);
		camera->ComputeRay(&ray, &screenPos);

		//============ ������ ���� �ȵ� ������..
		if (itemIndex == -1 && pickUp == true && clickItem != NULL) //�������� �����ų� ���� �ؾߴ�.( �������̸�)
		{
			if (PtInRect(&weapon.rcColl, ptMousePos) && weapon.m_Item ==NULL)
			{
				weapon.m_Item = clickItem;
				weapon.skillImage = RESOURCE_TEXTURE->GetResource("../Resources/UI/fot_lightingspear.bmp");
				weapon.isPoint = true;

				itemIndex = ITEM_MGR->findItem(clickItem->getItemNum());
				//������ ȸ���� �⺻���� �ٲ���. 
				weapon.m_Item->pTransform->SetRotateWorld(weapon.m_Item->getBasicRotaion());
				if (itemIndex != -1)
				{
					ITEM_MGR->v_item.erase(ITEM_MGR->v_item.begin() + itemIndex);
				}

				clickItem = NULL;
				pickUp = false;
			}//============ ������ ���� �� �ִٸ�.
			else if (PtInRect(&weapon.rcColl, ptMousePos) && weapon.m_Item != NULL)
			{  //staff _ basic master ,
				//stInven* temp;
				//temp = &weapon;
				//weapon = clickItem;
			}
			else // ������ ������. 
			{
				pickUp = false;
				//�ɸ��� ��ǥ ====================================
				clickItem->pTransform->SetWorldPosition(D3DXVECTOR3(0, 9, 0));
				clickItem = NULL;

			}


		}
		invenItemClick(); // �̰� ���� üũ �ؾߵ�.


		//	this->m_pTerrain->IsIntersectRay(&m_mousePos, &ray);
		for (int i = 0; i < ITEM_MGR->v_item.size(); i++)
		{
			if (PHYSICS_MGR->IsRayHitBound(&ray, &(ITEM_MGR->v_item[i]->BoundBox), (ITEM_MGR->v_item[i])->pTransform, NULL, NULL))
			{
				LOG_MGR->AddLog("������Ʈ �浹");
				clickItem = ITEM_MGR->v_item[i];
				pickUp = true;
				itemIndex = i;
				break;
			}
		}


		if (selctRect(&cRow, &cCol, ptMousePos))
		{
			if (inputItem(cRow, cCol, clickItem) == true)
			{
				// ������ ���� ����. 
				ITEM_MGR->v_item.erase(ITEM_MGR->v_item.begin() + itemIndex);
				clickItem = NULL;
				pickUp = false;
				itemIndex = -1;
			}
		}

	}


}


void cInven::render()
{
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
		}

		//=====================================
	}


}

bool cInven::inputItem(int row, int coll, cItem* item)
{
	if (invenOpen == false)return false;
	if (clickItem == NULL)return false;
	if (itemIndex == -1)return false;
	int tempRow = row + item->getRow();
	int tempColl = coll + item->getColl();

	// �κ��丮 �Ѿ�� �� 
	if (tempRow > INVEN_COUNT || tempColl > INVEN_COUNT)
	{
		return false;
	}

	// ���� �� �ִ��� Ȯ��
	for (int i = row; i < tempRow; i++)
	{
		for (int j = coll; j < tempColl; j++)
		{
			if (inven[i][j].itemNum != 0) // 0�� �ƴ϶�� �������� ��� �ִ°�.
			{
				return false;
			}
		}
	}


	for (int i = row; i < tempRow; i++)
	{
		for (int j = coll; j < tempColl; j++)
		{
			if (i == row&& j == coll)
			{
				inven[i][j].m_Item = clickItem;
				inven[i][j].isPoint = true;
				inven[i][j].itemNum = clickItem->getItemNum();
				inven[i][j].rcSize = RectMake(0, 0, item->getRow()*RECT_SIZE, item->getColl()*RECT_SIZE);
				// ������ string ������ �̹��� �ҽ� �ٲ���ߴ�			
				inven[i][j].skillImage = RESOURCE_TEXTURE->GetResource("../Resources/UI/fot_lightingspear.bmp");
			}
			else
			{
				//	inven[i][j].m_Item = clickItem;
				inven[i][j].m_Item = NULL;
				inven[i][j].isPoint = false;
				inven[i][j].itemNum = clickItem->getItemNum();

				//inven[i][j].skillImage = RESOURCE_TEXTURE->GetResource("../Resources/UI/fot_lightingspear.bmp");

			}
		}
	}

	return true;
}
void cInven::invenItemClick()
{
	if (invenOpen == false)return;//�κ��� ������ �ʾҴٸ�. 
	if (pickUp == true)return;    //�����ΰ� �۰� �ִٸ�.
	if (clickItem != NULL)return; //��� �ִ°Ϳ� �ּҰ� ��� �ִٸ�.

	int itemNum = 0;
	itemNum = findItemNum();
	if (itemNum == 0)return;

	for (int i = 0; i < INVEN_COUNT; i++)
	{
		for (int j = 0; j < INVEN_COUNT; j++)
		{
			if (inven[i][j].itemNum == itemNum&&inven[i][j].isPoint == true)
			{
				pickUp = true; //Ʈ��.
				clickItem = inven[i][j].m_Item;//������ �ְ� .
				clickItem->m_lifeTime = 60.f;

				//itemIndex = -1;


				ITEM_MGR->v_item.push_back(clickItem);//
			}
		}
	}
	// �κ��丮 �ʱ�ȭ.
	for (int i = 0; i < INVEN_COUNT; i++)
	{
		for (int j = 0; j < INVEN_COUNT; j++)
		{
			if (inven[i][j].itemNum == itemNum)
			{
				inven[i][j].m_Item = NULL;
				inven[i][j].skillImage = NULL;
				inven[i][j].isPoint = false; // ��¥ ����Ʈ������ �ִ� ��
				inven[i][j].itemNum = 0;//�������� 1���� �������. 
			}
		}
	}

}

int cInven::findItemNum()
{
	if (invenOpen == false)return 0;//�κ��� ������ �ʾҴٸ�. 
	if (pickUp == true)return 0;

	POINT ptMousePos = GetMousePos();

	int itemNum = 0;
	// ������ ��ȣ�� ã�´�. 
	for (int i = 0; i < INVEN_COUNT; i++)
	{
		for (int j = 0; j < INVEN_COUNT; j++)
		{
			if (PtInRect(&inven[i][j].rcColl, ptMousePos))
			{
				if (inven[i][j].itemNum != 0) // 0�� �ƴ϶�� �������� ��� �ִ°�.
				{
					itemNum = inven[i][j].itemNum;
					return itemNum;
				}
			}
		}
	}
	return 0;

}
bool cInven::selctRect(int* row, int* coll, POINT mouse)
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
	Device->GetViewport(&vp); // ����Ʈ ����ü�� �޾ƿ´�.

	D3DXMATRIXA16 matProj; // �� ���
	Device->GetTransform(D3DTS_PROJECTION, &matProj);

	//int rndX = vp.Width / 2;//rand() % WINSIZE_X;
	//int rndY = vp.Height / 2;//rand() % WINSIZE_Y;
	int rndX = x;
	int rndY = y;//rand() % WINSIZE_Y;
	D3DXVECTOR3 Org(0, 0, 0), Dir(0, 0, 0); //Org ī�޶��� ��ġ = eye / dir = lookAt 
	Dir.x = ((2.0f * rndX) / vp.Width - 1.0f) / matProj._11;
	Dir.y = ((-2.0f * rndY) / vp.Height + 1.0f) / matProj._22;
	Dir.z = 1.0f;

	D3DXVec3Normalize(&Dir, &Dir);

	D3DXMATRIXA16 matView, InverView; // �� ���

	Device->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&InverView, 0, &matView);
	D3DXVec3TransformCoord(&Org, &Org, &InverView);
	D3DXVec3TransformNormal(&Dir, &Dir, &InverView);
	D3DXVec3Normalize(&Dir, &Dir);

	D3DXVECTOR3 screenPos;
	//
	float d = -Org.y / Dir.y;

	screenPos.x = d * Dir.x + Org.x; // Org ����.
	screenPos.z = d * Dir.z + Org.z;
	screenPos.y = d * Dir.y + Org.y;

	return screenPos;
}