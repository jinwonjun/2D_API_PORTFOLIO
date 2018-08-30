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
		//�κ��丮 ������ ȭ��ǥ ��ġ �ʱ�ȭ
		arrow_rc = RectMake(40, 80, 25, 35);
}

void Inventory::tab_key_control()
{
	//�⺻ ���� ����Ű
	if (KEYMANAGER->isOnceKeyDown(VK_TAB))
	{
		//������ ȭ�鿡 �����̽��� Ű �Է��Ŀ�, ����ȭ������ ��ȯ(�ѹ��� ����ߵ�)
		tab_key_check = true;
		tab_key_cnt++;
	}
	if(KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		//ȭ��ǥ RC�� �����ϱ�
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
		//ȭ��ǥ RC�� �����ϱ�
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
		//ȭ��ǥ RC�� �����ϱ�
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
		//ȭ��ǥ RC�� �����ϱ�
		if (arrow_rc.left <= 40)
		{
			arrow_rc.left += 150;
			arrow_rc.right += 150;
		}
		arrow_rc.left -= 150;
		arrow_rc.right -= 150;
	}
}
