#pragma once

#include "cBaseObject.h"
#include "cBaseObject.h"
#include <string>


class cItem : public cBaseObject
{
	static unsigned int increaseNum; // 고유번호 계산
	string m_itemName;
	D3DXVECTOR3 m_basicScale;   // 변환시킬 스케일
	D3DXQUATERNION m_basicRotation; // 기존 회전값
	float m_lifeTime;       // 아이템 생존 시간. 
	bool m_active;          // 활성화 여부
	int m_row, m_coll;         // 행렬 
	unsigned int m_itemNum; // 아이템 고유 번호 .

public:
	void init(cItem* copyItem);
	void init(cItem copyItem);

	void createList(string name, int row, int coll);
	//cTransform* getTrans(){ return pTransform; }
	unsigned int getItemNum(){ return m_itemNum; }
	cItem();
	~cItem();
};

