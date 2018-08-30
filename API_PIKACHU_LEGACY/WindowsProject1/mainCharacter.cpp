#include "stdafx.h"

mainCharacter::mainCharacter()
{
}

mainCharacter::~mainCharacter()
{
}

HRESULT mainCharacter::init()
{
	//��ī�� ��Ʈ�� ũ�� 156x57
	//��ī�� �����Ʈ �׸���� �ʱ�ȭ,  ��ī���� ��Ʈ �κ��� ���� ������ �ʾ���! //��ġ�ʱ�ȭ //�¿� �̹��� �ϴ� 
	main_Pika = new image;
	main_Pika->init("images/picka.bmp", WINSIZEX / 2, WINSIZEY - 50, 1560 / 10 * 0.8, 570 / 10 * 0.8, 4, 2, true, RGB(255, 0, 255)); //��ġ�� �̹��� �ʱ�ȭ
	main_Pika_up = new image;
	main_Pika_up->init("images/picka_up.bmp", WINSIZEX / 2, WINSIZEY - 50, 300 * 0.4, 50 * 0.4, 6, 1, true, RGB(255, 0, 255));
	main_Pika_down = new image;
	main_Pika_down->init("images/picka_down.bmp", WINSIZEX / 2, WINSIZEY - 50, 244 * 0.4, 256 * 0.4, 4, 4, true, RGB(255, 0, 255));
	//RECT ���� �ÿ�, ������ũ��� ���� ��Ʈ�� ����������, 1560 / 10 * 0.8(��� �⺻ũ��) / X�� �Ǵ� Y�� ������ ����(������)
	main_Pika_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 60, 1560 / 10 /4 * 0.8, 570 / 10 /2 * 0.8);//���ΰ� ��Ʈ ��ġ �ʱ�ȭ
	
	//pikaHp = 1000;
	pika_isLeft = false;
	pika_count = 0;
	pika_index = 0;
	pika_up_count = 0;
	pika_up_index = 0;
	pika_down_count = 0;
	pika_down_index = 0;

	leftPress = false;
	rightPress = false;
	downPress = false;
	return S_OK;
}

void mainCharacter::pickaRender()
{
	if (pika_isLeft)
	{
		pika_count++;
		main_Pika->setFrameY(1);//����¥�� �׸��̴ϱ� y�࿡ ���� ���� �̵�������
		if (pika_count % 5 == 0)
		{
			pika_count = 0;
			pika_index--;
			if (pika_index < 0)
			{
				pika_index = 4;
			}
			main_Pika->setFrameX(pika_index);
		}
	}
	else
	{
		pika_count++;
		main_Pika->setFrameY(0);
		if (pika_count % 5 == 0)
		{
			pika_count = 0;
			pika_index++;
			if (pika_index >3)
			{
				pika_index = 0;
			}
			main_Pika->setFrameX(pika_index);
		}
	}
}

void mainCharacter::pickaUpRender()
{
	pika_up_count++;
	main_Pika_up->setFrameY(0);
	if (pika_up_count % 5 == 0)
	{
		pika_up_count = 0;
		pika_up_index++;
		if (pika_up_index >5)
		{
			pika_up_index = 0;
		}
		main_Pika_up->setFrameX(pika_up_index);
	}
}

void mainCharacter::pickaDownRender()
{
	pika_down_count++;
	main_Pika_down->setFrameY(0);
	if (pika_down_count % 2 == 0)
	{
		pika_down_count = 0;
		pika_down_index++;
		if (pika_down_index >5)
		{
			pika_down_index = 0;
		}
		main_Pika_down->setFrameX(pika_down_index);
	}
}

void mainCharacter::render(HDC hdc)
{
	//����ĳ���� ��ī�� �׸��� , �����̴ϱ� �� ����������
	//�⺻����
	if (!leftPress && !rightPress)
	{
		if (downPress)
		{
			main_Pika_up->frameRender(hdc, main_Pika_rc.left, main_Pika_rc.top, main_Pika_up->getFrameX(), main_Pika_up->getFrameY());
		}
		else
			main_Pika_down->frameRender(hdc, main_Pika_rc.left, main_Pika_rc.top, main_Pika_down->getFrameX(), main_Pika_down->getFrameY());
		//main_Pika_up->frameRender(hdc, main_Pika_rc.left, main_Pika_rc.top, main_Pika_up->getFrameX(), main_Pika_up->getFrameY());
	}
	if (leftPress || rightPress)
	{
		main_Pika->frameRender(hdc, main_Pika_rc.left, main_Pika_rc.top, main_Pika->getFrameX(), main_Pika->getFrameY());
	}
	//��ī�� ��Ʈ Ȯ�ο�
	//RectangleMake(hdc, main_Pika_rc.left, main_Pika_rc.top, main_Pika_rc.right - main_Pika_rc.left, main_Pika_rc.bottom - main_Pika_rc.top);
}
