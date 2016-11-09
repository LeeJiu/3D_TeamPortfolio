// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:


#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다
#include <string>


//필요한 헤더 (DirectSDK 설치폴더/Include)
//d3dx9.h
//d3d9.h
//#include "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include/d3d9.h"
//#include "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include/d3dx9.h"

//(DirectSDK 설치폴더/Include) 경로가 프로젝트의 System 폴더로 등록이 되어있다면 < > 로도 포함가능
#include <d3d9.h>
#include <d3dx9.h>

//System 폴더 (DirectSDK 설치폴더/Include) 등록 방법
//솔루션탐색기에서 프로젝트 우클릭
//속성
//구성속성의 VC++ 디렉터리 항목선택
//창의 우측을봐라.
//포함디렉토리칸의 오른속문자열라인을 선택하면 나오는 아래화살표 클릭
//<편집..> 문자를클릭
//포함디렉토리 창이 열리면서 우측 상단의 폴더추가 아이콘클릭
//클릭해서 나오는 빈간 오른쪽 ... 버튼 눌러
//탐색기 나오면서 (DirectSDK 설치폴더/Include) 선택


//필요라이브러리 (DirectSDK 설치폴더/Lib/x86)
//d3dx9.lib
//d3d9.lib
//#pragma comment( lib, "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x86/d3d9.lib" )
//#pragma comment( lib, "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x86/d3dx9.lib" )
#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )


//System 폴더 (DirectSDK 설치폴더/Lib/x86) 등록 방법
//솔루션탐색기에서 프로젝트 우클릭
//속성
//구성속성의 VC++ 디렉터리 항목선택
//창의 우측을봐라.
//라이브러리 디렉토리칸의 오른속문자열라인을 선택하면 나오는 아래화살표 클릭
//<편집..> 문자를클릭
//포함디렉토리 창이 열리면서 우측 상단의 폴더추가 아이콘클릭
//클릭해서 나오는 빈간 오른쪽 ... 버튼 눌러
//탐색기 나오면서 (DirectSDK 설치폴더/Lib/x86) 선택





//
// 매크로 상수
//
#define WINSIZE_X	1280		//초기 윈도우 가로 크기
#define WINSIZE_Y	720			//초기 윈도우 세로 크기
#define WINPOS_X	0			//초기 윈도우 시작 위치 X
#define WINPOS_Y	0			//초기 윈도우 시작 위치 Y
#define WIN_CLASS	"Windows Exam"		//윈도우 클레스 이름
#define WIN_TITLE	"Windows Exam"		//윈도우 타이틀 이름
#define WIN_STYLE	WS_CAPTION | WS_SYSMENU | WS_BORDER	//윈도우 형태


//캐릭터 상태 디파인문


enum PLAYER_STATE
{
	ROBBY_IDLE,         //게임 시작 선택창 대기모션

	PET_IDLE,           //펫 탑승
	PET_RUN,            //펫 이동

	SIT_SRT,           //앉기_시작
	SIT_LOOP,          //앉아있는 상태
	SIT_UP,            //일어서는 모션
	LOOP,              //습득상태

	HELLO,             //인사
	CRY,               //울기
	DANCE,             //춤을춰라 나의 인형아!

	STF_DMG,           //피격
	STF_DIE,           //죽어가는 중
	STF_DEAD,          //죽음
	STF_DOWN,          //넉백
	STF_STUN,          //넉백상태_루프
	STF_WAKEUP,        //넉백 일어나기

	STF_IDLE,            //평화상태
	STF_WAIT,            //전투대기
	STF_WALK,            //걷기
	STF_WALK_BACK,       //뒤로걷기
	STF_RUN,             //달리기
	RUN_R,               //오른쪽으로 달리기
	RUN_L,               //왼쪽으로 달리기
	STF_STOP,            //달리다 멈추기
	STF_PASSOUT,         //기력소모
	STF_JUMP,            //점프


	STF_WEAPON,          //무기 착용
	STF_UNWEAPON,        //무기 해제

	//공격 상태

	STF_ATK1,           //기본공격 1
	STF_ATK2,           //기본공격 2

	STF_BUFF,           //스킬_버프
	STF_TYFUNG,         //스킬_태풍
	STF_THUNDER,        //스킬_라이트닝 로드
	STF_FROZEN,         //스킬_빙하지대
	STF_FIRE,           //스킬_즉시소각
	STF_SPLASH,         //스킬_전방폭파
	STF_BUMB,           //스킬_지면폭파
	STF_DRAIN,          //스킬_드레인
	STF_SWING,          //스킬_후려찍기
	STF_STORM,          //스킬_천둥벼락
	STF_MAGIC_SHOT,     //스킬_마법발사

	STF_BLINK,          //스킬_ 점멸
	END
};


#define ONE_RAD 0.017453f				//라디안1 동


//
// 매크로 함수
//
#define SAFE_DELETE(p)		{ if(p){ delete (p); (p) = NULL; } }
#define SAFE_DELETE_ARR(p)	{ if(p){ delete[] (p); (p) = NULL; } }
#define SAFE_RELEASE(p)		{ if(p){ (p)->Release(); (p) = NULL; } }

//
// 전역 변수
//
extern HWND			g_hWnd;		//윈도우 핸들 ( 자신의 프로그램에서 돌고있는 윈도우 번호 )
extern HINSTANCE	g_hInst;	//프로그램 인스턴스 핸들 ( OS 가 부여한 프로그램 번호 )

extern bool			ex_wheelUp;
extern bool			ex_wheelDown;
//
//
//
#include <string>
#include <vector>
#include <map>




//
// 매니져
//
#include "MyUtil.h"

using namespace MyUtil;
using namespace std;


//
// 기타 등등
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