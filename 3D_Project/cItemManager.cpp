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
void cItemManager::update()
{

}
void cItemManager::render()
{

}
void cItemManager::createItemList()
{
	//itemList
	cItem* item; // 임시.
	item = new cItem;

	//std::map<int, cItem>::iterator pFind;
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);
	D3DXMATRIXA16 matCorrection = matScale;

	//원본 메쉬 로딩
	cXMesh_Static* mesh =
		RESOURCE_STATICXMESH->GetResource(
		"../Resources/Meshes/Weapon/STF_Master.X", &matCorrection);

	cBaseObject* obj;
	obj->SetMesh(mesh);
	obj->SetActive(false);

	item->createList("m_staff", *obj, obj->pTransform->GetScale(),
		2, 2);

	m_itemList.insert(std::make_pair(0, item));
}