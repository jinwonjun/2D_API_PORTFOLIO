#pragma once

class gameNode
{
private:
	image* m_backbuffer;//백버퍼
	void setBackbuffer();//백버퍼 셋팅하는 함수
public:
	gameNode();
	virtual~gameNode();

	virtual HRESULT init();
	virtual void  release();
	virtual void update();
	virtual void render(HDC hdc);

	//백버퍼 얻어오기
	image* getBackBuffer() { return m_backbuffer; }

	LRESULT MainProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

