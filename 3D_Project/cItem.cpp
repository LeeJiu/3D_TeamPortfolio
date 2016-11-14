#include "stdafx.h"
#include "cItem.h"


unsigned int cItem::increaseNum = 0;

cItem::cItem()
{
	m_lifeTime = 10.f; // 아이템 생존 시간. 
	m_itemNum = 0.f;
	m_active = true;
}


cItem::~cItem()
{
}

void cItem::init(cItem* copyItem)
{
	*this = *copyItem;
	m_itemNum = ++increaseNum;
}

void cItem::init(cItem copyItem)
{
	*this = copyItem;
	m_itemNum = ++increaseNum;
}
void cItem::createList(string name, int row, int coll)
{

	m_itemName = name;
	m_basicScale = pTransform->GetScale(); // 기존 스케일 값.
	m_basicRotation = pTransform->GetWorldRotateQuaternion();

	m_row = row;           // 행-----
	m_coll = coll;         // 열|

}