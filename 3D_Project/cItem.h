#pragma once

#include "cBaseObject.h"
#include "cBaseObject.h"
#include <string>

static unsigned int increaseNum; // 고유번호 계산

class cItem : public cBaseObject
{
	static unsigned int increaseNum; // 고유번호 계산


	string m_itemName;
	D3DXVECTOR3 m_basicScale;   // 변환시킬 스케일
	D3DXQUATERNION m_basicRotation; // 기존 회전값
	bool m_active;          // 활성화 여부
	int m_row, m_coll;         // 행렬 
	
	
	unsigned int m_itemNum; // 아이템 고유 번호 .
	int m_Dmg;				//무공
	
public:
	
	float m_lifeTime;       // 아이템 생존 시간. 
	int getRow(){ return m_row; }
	int getColl(){ return m_coll; }

	void init(cItem* copyItem);
	void createList(string name, int row, int coll);
	//cTransform* getTrans(){ return pTransform; }
	unsigned int getItemNum(){ return m_itemNum; }
	D3DXQUATERNION getBasicRotaion(){ return m_basicRotation; }
	string getItemName(){ return m_itemName; }
	void setDmg(int dmg) { m_Dmg = dmg; }
	int getDmg() { return m_Dmg; }
	cItem();
	~cItem();
	
};

