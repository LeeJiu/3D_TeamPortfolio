#include "stdafx.h"
#include "cItem.h"


unsigned int cItem::increaseNum = 0;

cItem::cItem()
{
	m_lifeTime = 60.f; // 아이템 생존 시간. 
	m_itemNum = 0.f;
	m_active = true;

}


cItem::~cItem()
{
}

void cItem::init(cItem* copyItem)
{
	//cItem ===================
	m_itemName = copyItem->m_itemName;
	m_basicScale = copyItem->m_basicScale;
	m_basicRotation = copyItem->m_basicRotation;
	m_Dmg = copyItem->m_Dmg;
	//m_lifeTime = copyItem->m_lifeTime;
	m_active = copyItem->m_active;
	m_row = copyItem->m_row;
	m_coll = copyItem->m_coll;
	//cBaseObj=================
	*pTransform = *copyItem->pTransform;
	pMesh = copyItem->pMesh;
	BoundBox = copyItem->BoundBox;
	IgnoreCreateShadow = copyItem->IgnoreCreateShadow;

	pSkinned = copyItem->pSkinned;
	bActive = copyItem->bActive;
	pTerrain = copyItem->pTerrain;


	m_itemNum = ++increaseNum;

}

//void cItem::init(cItem copyItem)
//{
//	*this = copyItem;
//	m_itemNum = ++increaseNum;
//}
void cItem::createList(string name, int row, int coll)
{

	m_itemName = name;
	m_basicScale = pTransform->GetScale(); // 기존 스케일 값.
	m_basicRotation = pTransform->GetWorldRotateQuaternion();

	m_row = row;           // 행-----
	m_coll = coll;         // 열|

}

