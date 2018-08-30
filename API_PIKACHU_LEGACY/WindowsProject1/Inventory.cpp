#include "stdafx.h"

Inventory::Inventory()
{
}


Inventory::~Inventory()
{
}

HRESULT Inventory::init()
{
	tab_key_check = false;
	tab_key_cnt = 0;
	
	inven = new image;
	inven->init("images/inventory.bmp", 20, 20, 400 * 0.9, 300 * 0.9, 1, 1, true, RGB(255, 0, 255));

	arrow = new image;
	arrow->init("images/arrow.bmp", 40, 40, 25, 35, 1, 1, true, RGB(255, 0, 255));

	arrow_rc = RectMake(40, 80, 25, 35);

	return S_OK;
}

void Inventory::render(HDC hdc)
{

	if (tab_key_check && tab_key_cnt % 2 == 1)
	{
		inven->render(hdc, 20, 20);
		arrow->render(hdc, arrow_rc.left, arrow_rc.top);
		//RectangleMake(hdc, arrow_rc.left, arrow_rc.top, arrow_rc.right - arrow_rc.left, arrow_rc.bottom - arrow_rc.top);
	}
	else
		//인벤토리 켜질때 화살표 위치 초기화
		arrow_rc = RectMake(40, 80, 25, 35);
}

void Inventory::tab_key_control()
{
	//기본 게임 조작키
	if (KEYMANAGER->isOnceKeyDown(VK_TAB))
	{
		//오프닝 화면에 스페이스바 키 입력후에, 설명화면으로 전환(한번만 해줘야됨)
		tab_key_check = true;
		tab_key_cnt++;
	}
	if(KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		//화살표 RC값 조절하기
		if (arrow_rc.bottom >= 260)
		{
			arrow_rc.bottom -= 50;
			arrow_rc.top -= 50;
		}
		arrow_rc.bottom += 50;
		arrow_rc.top += 50;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		//화살표 RC값 조절하기
		if (arrow_rc.top <= 80)
		{
			arrow_rc.bottom += 50;
			arrow_rc.top += 50;
		}
		arrow_rc.bottom -= 50;
		arrow_rc.top -= 50;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		//화살표 RC값 조절하기
		if (arrow_rc.left >= 190)
		{
			arrow_rc.left -= 150;
			arrow_rc.right -=150;
		}
		arrow_rc.left += 150;
		arrow_rc.right += 150;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		//화살표 RC값 조절하기
		if (arrow_rc.left <= 40)
		{
			arrow_rc.left += 150;
			arrow_rc.right += 150;
		}
		arrow_rc.left -= 150;
		arrow_rc.right -= 150;
	}
}
