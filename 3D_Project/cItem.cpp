#include "stdafx.h"
#include "cItem.h"


unsigned int increaseNum = 0;

cItem::cItem()
{
	m_lifeTime = 10.f; // 아이템 생존 시간. 
	m_active = true;
}


cItem::~cItem()
{
}

void cItem::init()
{
	m_itemNum = increaseNum++;

	// 생성 위치,
	// 
}
void cItem::createList(string name, cBaseObject item, D3DXVECTOR3 scale
	, int row, int coll)
{
	m_itemName = name;
	m_itemObj = item;
	m_scale = scale;

	m_row = row; 
	m_coll = coll;

}