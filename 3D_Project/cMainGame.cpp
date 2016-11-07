#include "StdAfx.h"
#include "cMainGame.h"
#include "cImage.h"
#include "t_Scene.h"
#include "move_Test.h"
#include "camera_Test.h"
#include "cScene_testPlayer.h"

cMainGame::cMainGame(void)
{
}

cMainGame::~cMainGame(void)
{
}

//����
HRESULT cMainGame::Init(void)
{
	//�����õ�
	SetRandomSeed();
	
	//����̽� ����
	CreateDevice();

	//�Ŵ��� ����
	TIME_MGR->Init();
	LOG_MGR->Init( LOG_WINDOW | LOG_FILE, g_hWnd, "Dump" );
	DXFONT_MGR->Init( Device );	
	GIZMO_MGR->Init( Device );
	SPRITE_MGR->Init( Device );
	SCENE_MGR->Init();
	
	//���ӿ� ���Ǵ� �� �߰�
	SCENE_MGR->AddScene("model_Test", new t_Scene());
	SCENE_MGR->AddScene("move_Test", new move_Test());
	SCENE_MGR->AddScene("camera_Test", new camera_Test());
	SCENE_MGR->AddScene("cScene_testPlayer", new cScene_testPlayer());

	////���� ���۾�
	SCENE_MGR->ChangeScene( "cScene_testPlayer" );

	//return E_FAIL;
	return S_OK;		
}	

//����
void cMainGame::Release()
{
	//�Ŵ��� ����
	GIZMO_MGR->Release();
	cGizmoManager::ReleaseInstance();
	TIME_MGR->Release();
	cTimeMgr::ReleaseInstance();
	KEY_MGR->Release();
	cKeyMgr::ReleaseInstance();
	LOG_MGR->Release();
	cLogMgr::ReleaseInstance();
	DXFONT_MGR->Release();
	cDXFontManager::ReleaseInstance();
	SPRITE_MGR->Release();
	cSpriteManager::ReleaseInstance();
	SCENE_MGR->Release();
	cScene_Mgr::ReleaseInstance();
	cPhysicManager::ReleaseInstance();

	RESOURCE_TEXTURE->ClearResource();
	cResourceMgr_Texture::ReleaseInstance();
	RESOURCE_FX->ClearResource();
	cResourceMgr_ShaderFX::ReleaseInstance();
	RESOURCE_STATICXMESH->ClearResource();
	cResourceMgr_XStaticMesh::ReleaseInstance();
	RESOURCE_SKINNEDXMESH->ClearResource();
	cResourceMgr_XSkinnedMesh::ReleaseInstance();




	//����̽� ����
	ReleaseDevice();
}

//������Ʈ
void cMainGame::Update()
{
	//Ÿ�ӸŴ��� ������Ʈ
	TIME_MGR->UpdateTime( 60.0f );
	
	//�������� ���� �ð�
	double timeDelta = TIME_MGR->GetFrameDeltaSec();

	//��������Ʈ
	SCENE_MGR->Update( timeDelta );

	ex_wheelDown = ex_wheelUp = false;
}

//��ο�
void cMainGame::Draw()
{
	//���۸� û���Ѵ�
	HRESULT result = Device->Clear(
		0,							//û���� ������ D3DRECT �迭 ����		( ��ü Ŭ���� 0 )
		NULL,						//û���� ������ D3DRECT �迭 ������		( ��ü Ŭ���� NULL )
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,		//û�ҵ� ���� �÷��� ( D3DCLEAR_TARGET �÷�����, D3DCLEAR_ZBUFFER ���̹���, D3DCLEAR_STENCIL ���ٽǹ���
		0xff202020,					//�÷����۸� û���ϰ� ä���� ����( 0xAARRGGBB )
		1.0f,						//���̹��۸� û���Ұ� ( 0 ~ 1, 0 �� ī�޶󿡼� ���ϰ���� 1 �� ī�޶󿡼� ���� �� )
		0							//���ٽ� ���۸� ä�ﰪ
		);
	
	//���� û�Ұ� �����ߴٸ�.......
	if( SUCCEEDED( result ) )
	{
		//����̽� ������ ���� ���
		Device->BeginScene();

		//������ ���

		//������
		SCENE_MGR->Render();


#ifdef _DEBUG		//����� ��忡���� ����
		//����̽� ������ ���� ���
		//���� �׸���
		//GIZMO_MGR->WorldGrid( 1, 10 );

		//Ÿ������ ���
		TIME_MGR->DrawTimeInfo();
#endif

		Device->EndScene();


		//�������� ���۳����� ȭ�鿡 ����
		Device->Present(  0, 0, 0, 0 );
	}
	

}

void cMainGame::OnMouseWheel(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	static int SumDelta = 0;
	short zDelta;
	UINT Lines;
	int Unit;

	SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0, &Lines, 0);
	Unit = WHEEL_DELTA / Lines;
	zDelta = (short)HIWORD(wParam);
	SumDelta += zDelta;
	while (abs(SumDelta) >= Unit){
		if (SumDelta > 0)
		{
			SendMessage(hWnd, WM_VSCROLL, SB_LINEUP, 0L);
			SumDelta -= Unit;
			ex_wheelDown = false;
			ex_wheelUp = true;
			LOG_MGR->AddLog("�پ� %d %d", ex_wheelUp, ex_wheelDown);
		}
		
		if (SumDelta < 0)
		{
			SendMessage(hWnd, WM_VSCROLL, SB_LINEDOWN, 0L);
			SumDelta += Unit;
			ex_wheelUp = false;
			ex_wheelDown = true;
			LOG_MGR->AddLog("�ٴٿ�, %d , %d", ex_wheelUp, ex_wheelDown);
		}

		//�̰� ��ũ�� ��ư���� ���� �ʱ�ȭ �Ǿ��ϴ´�?
	}
}



//////////////////////////////////////////////////////////////////////////

//���� ���ν��� �Լ�
LRESULT cMainGame::MainProc( HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam )
{
	switch( iMessage )
	{	
	case WM_TIMER:
		Update();
		break;

	case WM_KEYDOWN:
		switch( wParam )
		{
		case VK_ESCAPE:
			DestroyWindow( hWnd );
			break;
		}
		break;

	case WM_MOUSEWHEEL:
		{
			OnMouseWheel(hWnd, wParam, lParam);
			//return 0;
			break;
		}

	case WM_DESTROY:			//�����찡 �ı��ȴٸ�..
		PostQuitMessage( 0 );	//���α׷� ���� ��û ( �޽��� ������ ���������� �ȴ� )
		break;
	}
	return DefWindowProc( hWnd, iMessage, wParam, lParam );
}

