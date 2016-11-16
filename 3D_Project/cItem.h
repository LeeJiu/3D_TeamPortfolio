#pragma once

#include "cBaseObject.h"
#include <string>


class cItem
{
	static unsigned int increaseNum; // 고유번호 계산

	string m_itemName;
	cBaseObject m_itemObj; // 아이템 오브젝트
	D3DXVECTOR3 m_scale;   // 아이엠 스케일
	D3DXVECTOR3 m_base_scale;   // 기존 스케일값.

	float m_lifeTime;       // 아이템 생존 시간. 
	bool m_active;          // 활성화 여부
	int m_row,m_coll;         // 행렬 
	unsigned int m_itemNum; // 아이템 고유 번호 .

public:
	void init();
	void createList(string name,cBaseObject item,D3DXVECTOR3 scale
		,int row,int coll );

	cItem();
	~cItem();
};

