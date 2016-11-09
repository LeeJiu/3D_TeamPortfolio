// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:


#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�
#include <string>


//�ʿ��� ��� (DirectSDK ��ġ����/Include)
//d3dx9.h
//d3d9.h
//#include "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include/d3d9.h"
//#include "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include/d3dx9.h"

//(DirectSDK ��ġ����/Include) ��ΰ� ������Ʈ�� System ������ ����� �Ǿ��ִٸ� < > �ε� ���԰���
#include <d3d9.h>
#include <d3dx9.h>

//System ���� (DirectSDK ��ġ����/Include) ��� ���
//�ַ��Ž���⿡�� ������Ʈ ��Ŭ��
//�Ӽ�
//�����Ӽ��� VC++ ���͸� �׸���
//â�� ����������.
//���Ե��丮ĭ�� �����ӹ��ڿ������� �����ϸ� ������ �Ʒ�ȭ��ǥ Ŭ��
//<����..> ���ڸ�Ŭ��
//���Ե��丮 â�� �����鼭 ���� ����� �����߰� ������Ŭ��
//Ŭ���ؼ� ������ �� ������ ... ��ư ����
//Ž���� �����鼭 (DirectSDK ��ġ����/Include) ����


//�ʿ���̺귯�� (DirectSDK ��ġ����/Lib/x86)
//d3dx9.lib
//d3d9.lib
//#pragma comment( lib, "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x86/d3d9.lib" )
//#pragma comment( lib, "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x86/d3dx9.lib" )
#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )


//System ���� (DirectSDK ��ġ����/Lib/x86) ��� ���
//�ַ��Ž���⿡�� ������Ʈ ��Ŭ��
//�Ӽ�
//�����Ӽ��� VC++ ���͸� �׸���
//â�� ����������.
//���̺귯�� ���丮ĭ�� �����ӹ��ڿ������� �����ϸ� ������ �Ʒ�ȭ��ǥ Ŭ��
//<����..> ���ڸ�Ŭ��
//���Ե��丮 â�� �����鼭 ���� ����� �����߰� ������Ŭ��
//Ŭ���ؼ� ������ �� ������ ... ��ư ����
//Ž���� �����鼭 (DirectSDK ��ġ����/Lib/x86) ����





//
// ��ũ�� ���
//
#define WINSIZE_X	1280		//�ʱ� ������ ���� ũ��
#define WINSIZE_Y	720			//�ʱ� ������ ���� ũ��
#define WINPOS_X	0			//�ʱ� ������ ���� ��ġ X
#define WINPOS_Y	0			//�ʱ� ������ ���� ��ġ Y
#define WIN_CLASS	"Windows Exam"		//������ Ŭ���� �̸�
#define WIN_TITLE	"Windows Exam"		//������ Ÿ��Ʋ �̸�
#define WIN_STYLE	WS_CAPTION | WS_SYSMENU | WS_BORDER	//������ ����


//ĳ���� ���� �����ι�


enum PLAYER_STATE
{
	ROBBY_IDLE,         //���� ���� ����â �����

	PET_IDLE,           //�� ž��
	PET_RUN,            //�� �̵�

	SIT_SRT,           //�ɱ�_����
	SIT_LOOP,          //�ɾ��ִ� ����
	SIT_UP,            //�Ͼ�� ���
	LOOP,              //�������

	HELLO,             //�λ�
	CRY,               //���
	DANCE,             //������� ���� ������!

	STF_DMG,           //�ǰ�
	STF_DIE,           //�׾�� ��
	STF_DEAD,          //����
	STF_DOWN,          //�˹�
	STF_STUN,          //�˹����_����
	STF_WAKEUP,        //�˹� �Ͼ��

	STF_IDLE,            //��ȭ����
	STF_WAIT,            //�������
	STF_WALK,            //�ȱ�
	STF_WALK_BACK,       //�ڷΰȱ�
	STF_RUN,             //�޸���
	RUN_R,               //���������� �޸���
	RUN_L,               //�������� �޸���
	STF_STOP,            //�޸��� ���߱�
	STF_PASSOUT,         //��¼Ҹ�
	STF_JUMP,            //����


	STF_WEAPON,          //���� ����
	STF_UNWEAPON,        //���� ����

	//���� ����

	STF_ATK1,           //�⺻���� 1
	STF_ATK2,           //�⺻���� 2

	STF_BUFF,           //��ų_����
	STF_TYFUNG,         //��ų_��ǳ
	STF_THUNDER,        //��ų_����Ʈ�� �ε�
	STF_FROZEN,         //��ų_��������
	STF_FIRE,           //��ų_��üҰ�
	STF_SPLASH,         //��ų_��������
	STF_BUMB,           //��ų_��������
	STF_DRAIN,          //��ų_�巹��
	STF_SWING,          //��ų_�ķ����
	STF_STORM,          //��ų_õ�պ���
	STF_MAGIC_SHOT,     //��ų_�����߻�

	STF_BLINK,          //��ų_ ����
	END
};


#define ONE_RAD 0.017453f				//����1 ��


//
// ��ũ�� �Լ�
//
#define SAFE_DELETE(p)		{ if(p){ delete (p); (p) = NULL; } }
#define SAFE_DELETE_ARR(p)	{ if(p){ delete[] (p); (p) = NULL; } }
#define SAFE_RELEASE(p)		{ if(p){ (p)->Release(); (p) = NULL; } }

//
// ���� ����
//
extern HWND			g_hWnd;		//������ �ڵ� ( �ڽ��� ���α׷����� �����ִ� ������ ��ȣ )
extern HINSTANCE	g_hInst;	//���α׷� �ν��Ͻ� �ڵ� ( OS �� �ο��� ���α׷� ��ȣ )

extern bool			ex_wheelUp;
extern bool			ex_wheelDown;
//
//
//
#include <string>
#include <vector>
#include <map>




//
// �Ŵ���
//
#include "MyUtil.h"

using namespace MyUtil;
using namespace std;


//
// ��Ÿ ���
//
#include "cTimeMgr.h"
#include "cKeyMgr.h"
#include "cLogMgr.h"
#include "cDXFontManager.h"
#include "cGizmoManager.h"
#include "cPhysicManager.h"
#include "cSpriteManager.h"
#include "cScene_Mgr.h"
#include "cResourceMgr_Texture.h"
#include "cResourceMgr_ShaderFX.h"
#include "cResourceMgr_XStaticMesh.h"
#include "cResourceMgr_XSkinnedMesh.h"
#include "cSoundManager.h"