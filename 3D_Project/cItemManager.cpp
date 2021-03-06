#include "stdafx.h"
#include "cItemManager.h"


cItemManager::cItemManager()
{
}


cItemManager::~cItemManager()
{
}
void cItemManager::init()
{
	createItemList();

}
void cItemManager::update(float timeDelta)
{
	if (KEY_MGR->IsOnceDown('P'))
	{
		for (v_iter = v_item.begin(); v_iter != v_item.end(); ++v_iter)
		{

			LOG_MGR->AddLog("다미지 =%d , ", (*v_iter)->getDmg());
		}
	}

	for (v_iter = v_item.begin(); v_iter != v_item.end(); )
	{
		(*v_iter)->m_lifeTime -= timeDelta;
		
		if ((*v_iter)->m_lifeTime < 0.f)
		{
			SAFE_DELETE(*v_iter);
			v_iter=v_item.erase(v_iter);
		}
		else
		{
			++v_iter;
		}

	}

}
void cItemManager::render()
{
	for (v_iter = v_item.begin(); v_iter != v_item.end(); ++v_iter)
	{
		(*v_iter)->Render();
	}
}
void cItemManager::release()
{
	for (m_itemIter = m_itemList.begin(); m_itemIter != m_itemList.end(); ++m_itemIter)
	{
		SAFE_DELETE(m_itemIter->second);
	}

	for (v_iter = v_item.begin(); v_iter != v_item.end(); ++v_iter)
	{
		SAFE_DELETE(*v_iter);
	}

}
void cItemManager::createItemList()
{
	//itemList
	cItem* item; // 임시.
	item = new cItem;

	//std::map<int, cItem>::iterator pFind;
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.05f, 0.05f, 0.05f);
	D3DXMATRIXA16 matCorrection = matScale;

	//원본 메쉬 로딩
	cXMesh_Static* mesh =
		RESOURCE_STATICXMESH->GetResource(
		"../Resources/Meshes/Weapon/STF_Master.X", &matCorrection);

	item->SetMesh(mesh);
	item->SetActive(true);

	item->createList("m_staff",	2, 2);// 2 x 2 크기를 넣을때 .
	item->pTransform->SetRotateWorld( 90 * ONE_RAD,0, 0);
	item->setDmg(100);


	m_itemList.insert(std::make_pair(0, item));
	//==================== 위와 같이 아이템 하나하나
	// 한땀한땀 넣으면 된당.
	item = new cItem;

	//원본 메쉬 로딩
     mesh =
		RESOURCE_STATICXMESH->GetResource(
		"../Resources/Meshes/Weapon/TAX_Master.X", &matCorrection);

	item->SetMesh(mesh);
	item->SetActive(true);

	item->createList("m_axe", 2, 2);// 2 x 2 크기를 넣을때 .
	item->pTransform->SetRotateWorld(90 * ONE_RAD, 0, 0);
	item->setDmg(100);
	m_itemList.insert(std::make_pair(1, item));
	//========================
	//기본템
	item = new cItem;
	//원본 메쉬 로딩
	mesh =
		RESOURCE_STATICXMESH->GetResource(
			"../Resources/Meshes/Weapon/TAX_Basic.X", &matCorrection);

	item->SetMesh(mesh);
	item->SetActive(true);

	item->createList("b_axe", 2, 2);// 2 x 2 크기를 넣을때 .
	item->pTransform->SetRotateWorld(90 * ONE_RAD, 0, 0);
	item->setDmg(30);

	m_itemList.insert(std::make_pair(2, item));
	//========================
	//기본템-법사
	item = new cItem;
	//원본 메쉬 로딩
	mesh =
		RESOURCE_STATICXMESH->GetResource(
			"../Resources/Meshes/Weapon/STF_Basic.X", &matCorrection);

	item->SetMesh(mesh);
	item->SetActive(true);

	item->createList("b_stf", 2, 2);// 2 x 2 크기를 넣을때 .
	item->pTransform->SetRotateWorld(90 * ONE_RAD, 0, 0);
	item->setDmg(30);

	m_itemList.insert(std::make_pair(3, item));
}
void cItemManager::createItem(int itemNum, D3DXVECTOR3 pos)
{
	cItem* temp = new cItem;
	m_itemIter = m_itemList.find(itemNum);
	temp->init(m_itemIter->second);
	//memcpy(temp, m_itemIter->second, sizeof(cItem));
	//*temp = *m_itemIter->second;
	pos.y = pos.y + 0.2f; // 터레인 위에 조금 띄움
	temp->pTransform->SetWorldPosition(pos);
	//temp->pTransform->SetRotateWorld()
	//============= 푸쉬백 ============
	v_item.push_back(temp);
}
int cItemManager::findItem(int itemNum)
{
	for (int i = 0; i < ITEM_MGR->v_item.size(); i++)
	{
		if (ITEM_MGR->v_item[i]->getItemNum() == itemNum)
		{
			return i;
		}
	}

	return -1;
}

cItem * cItemManager::getItem(int itemNum)
{
	return m_itemList.find(itemNum)->second;
}
