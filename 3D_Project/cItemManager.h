#pragma once

#include "csingletonbase.h"
#include "cBaseObject.h"
#include "cItem.h"
#include <map>
#include <string>
#include <vector>
class cItemManager : public cSingletonBase<cItemManager>
{

public:
	std::map<int, cItem*> m_itemList;
	std::map<int, cItem*>::iterator m_itemIter;

	std::vector<cItem*> v_item;
	std::vector<cItem*>::iterator v_iter;

	cItemManager();
	~cItemManager();

	void init();
	void update(float timeDelta);
	void render();
	void release();
	void createItemList(); // 아이템 목록 만드는 함수. 
	void createItem(int itemNum, D3DXVECTOR3 pos); // 아이템 생성


};

#define ITEM_MGR cItemManager::GetInstance()