#pragma once

class cImage;			//�̷�Ŭ������ �ִ�
class cScene;

#define _WIN32_WINNT 0x400
#define _WIN32_WINDOWS 0x401

class cMainGame
{
private:	


public:
	cMainGame(void);
	~cMainGame(void);

	//����
	HRESULT Init(void);

	//����
	void Release();

	//������Ʈ
	void Update();

	//��ο�
	void Draw();

	//��
	void OnMouseWheel(HWND hWnd, WPARAM wParam, LPARAM lParam);
public:

	//���ν���
	LRESULT MainProc( HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam );

};
