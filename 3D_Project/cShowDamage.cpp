#include "stdafx.h"
#include "cShowDamage.h"


cShowDamage::cShowDamage()
{
}

cShowDamage::~cShowDamage()
{
}

void cShowDamage::Init()
{
	
}

void cShowDamage::SetNumber(int number, cTransform * trans)
{
	char temp[32];

	num = 0;
	num = number;
	if (num != 0)
	{
		if (num < 10)
		{
			
			stDamage damage;
			damage.unit = num;
			damage.unit_Rc = RectMake(WINSIZE_X/2, WINSIZE_Y/2, TEX_WIDTH, TEX_HEIGHT);
			//damage.unit_Rc = RectMake(trans->GetWorldPosition().x, trans->GetWorldPosition().y, 5, 5);
			char temp[32];
			sprintf_s(temp, "../Resources/Textures/num_%d.tga", damage.unit);
			damage.unit_tex = RESOURCE_TEXTURE->GetResource(temp);
			damage.countTime = 0;
			damage.time = 5;
			damage.isDrawing = true;
			damage.tens_tex = NULL;		//�����ڸ� ���� �ؽ��Ŀ� �ΰ��� �־ ���� ��������.

			v_damage.push_back(damage);
		}
		//����� ����ҰŸ� ���⼭ trans���� �������ؼ� �����̹����� ���缭����ָ鵩. -> texture��
		//else if (10 <= num && num < 100)
		//{
		//	unit = (number % 10);
		//	tens = (number / 10);
		//
		//
		//	sprintf_s(temp, "../Resources/Textures/num_%d.tga", unit);
		//	unit_quard->SetTexture(RESOURCE_TEXTURE->GetResource(temp));
		//	sprintf_s(temp, "../Resources/Textures/num_%d.tga", tens);
		//	tens_quard->SetTexture(RESOURCE_TEXTURE->GetResource(temp));
		//
		//	LOG_MGR->AddLog(" %d,%d", unit, tens);
		//}
		//else if (100 <= num && num < 1000)
		//{
		//	unit = (number % 10);
		//	tens = (number / 10) % 10;
		//	hund = (number / 100);
		//
		//	unit_quard->pTransform->AttachTo(trans);
		//	tens_quard->pTransform->AttachTo(trans);
		//	hund_quard->pTransform->AttachTo(trans);
		//
		//	sprintf_s(temp, "../Resources/Textures/num_%d.tga", unit);
		//	unit_quard->SetTexture(RESOURCE_TEXTURE->GetResource(temp));
		//	sprintf_s(temp, "../Resources/Textures/num_%d.tga", tens);
		//	tens_quard->SetTexture(RESOURCE_TEXTURE->GetResource(temp));
		//	sprintf_s(temp, "../Resources/Textures/num_%d.tga", hund);
		//	hund_quard->SetTexture(RESOURCE_TEXTURE->GetResource(temp));
		//}
		//else if (1000 <= num && num < 10000)
		//{
		//	unit = (number % 10);
		//	tens = (number / 10) % 10;
		//	hund = (number / 100) % 10;
		//	thou = (number / 1000);
		//
		//	sprintf_s(temp, "../Resources/Textures/num_%d.tga", unit);
		//	unit_quard->SetTexture(RESOURCE_TEXTURE->GetResource(temp));
		//	sprintf_s(temp, "../Resources/Textures/num_%d.tga", tens);
		//	tens_quard->SetTexture(RESOURCE_TEXTURE->GetResource(temp));
		//	sprintf_s(temp, "../Resources/Textures/num_%d.tga", hund);
		//	hund_quard->SetTexture(RESOURCE_TEXTURE->GetResource(temp));
		//	sprintf_s(temp, "../Resources/Textures/num_%d.tga", thou);
		//	thou_quard->SetTexture(RESOURCE_TEXTURE->GetResource(temp));
		//}
		//else if (10000 <= num && num < 100000)
		//{
		//	unit = (number % 10);
		//	tens = (number / 10) % 10;
		//	hund = (number / 100) % 10;
		//	thou = (number / 1000) % 10;
		//	mil = (number / 10000);
		//
		//	sprintf_s(temp, "../Resources/Textures/num_%d.tga", unit);
		//	unit_quard->SetTexture(RESOURCE_TEXTURE->GetResource(temp));
		//	sprintf_s(temp, "../Resources/Textures/num_%d.tga", tens);
		//	tens_quard->SetTexture(RESOURCE_TEXTURE->GetResource(temp));
		//	sprintf_s(temp, "../Resources/Textures/num_%d.tga", hund);
		//	hund_quard->SetTexture(RESOURCE_TEXTURE->GetResource(temp));
		//	sprintf_s(temp, "../Resources/Textures/num_%d.tga", thou);
		//	thou_quard->SetTexture(RESOURCE_TEXTURE->GetResource(temp));
		//	sprintf_s(temp, "../Resources/Textures/num_%d.tga", mil);
		//	mil_quard->SetTexture(RESOURCE_TEXTURE->GetResource(temp));
		//}
		//else
		//{
		//	LOG_MGR->AddLog("���� ǥ�� ������ ����ٴ뽺");
		//	return;
		//}
	}
}

//���� ��Ȱ���� ���ϸ� ť�ιٲ�
void cShowDamage::Release()
{
	for (vi_damage = v_damage.begin(); vi_damage != v_damage.end(); vi_damage++)
	{
		if (vi_damage->isDrawing) continue;
		v_damage.erase(vi_damage);
	}
}

void cShowDamage::Update(float timeDelta)
{
	size = v_damage.size();

	for (int i = 0; i < size; i++)
	{
		if (!v_damage[i].isDrawing) continue;

		v_damage[i].countTime += timeDelta;

		if (v_damage[i].countTime > v_damage[i].time)
			v_damage[i].isDrawing = false;
	}

	//Release();  //���������𸣴� �ϴ� ��Ű��.
}

void cShowDamage::Render()
{
	for (int i = 0; i < size; i++)
	{
		if (!v_damage[i].isDrawing) continue;
		
		if (v_damage[i].tens_tex == NULL)
		{
			SPRITE_MGR->DrawTexture(
				v_damage[i].unit_tex,
				&v_damage[i].unit_Rc,
				v_damage[i].unit_Rc.left,
				v_damage[i].unit_Rc.top,
				0xf0ffffff,
				NULL
			);
		}
	}
}
