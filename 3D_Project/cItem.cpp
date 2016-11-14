#include "stdafx.h"
#include "cItem.h"


unsigned int cItem::increaseNum = 0;

cItem::cItem()
{
	m_lifeTime = 10.f; // ������ ���� �ð�. 
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
	m_basicScale = pTransform->GetScale(); // ���� ������ ��.
	m_basicRotation = pTransform->GetWorldRotateQuaternion();

	m_row = row;           // ��-----
	m_coll = coll;         // ��|

}