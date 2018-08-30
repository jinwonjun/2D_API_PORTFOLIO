#include "stdafx.h"

mainCharacter::mainCharacter()
{
}

mainCharacter::~mainCharacter()
{
}

HRESULT mainCharacter::init()
{
	//피카츄 비트맵 크기 156x57
	//피카츄 무브먼트 그리기와 초기화,  피카츄의 렉트 부분은 아직 해주지 않았음! //위치초기화 //좌우 이미지 일단 
	main_Pika = new image;
	main_Pika->init("images/picka.bmp", WINSIZEX / 2, WINSIZEY - 50, 1560 / 10 * 0.8, 570 / 10 * 0.8, 4, 2, true, RGB(255, 0, 255)); //위치와 이미지 초기화
	main_Pika_up = new image;
	main_Pika_up->init("images/picka_up.bmp", WINSIZEX / 2, WINSIZEY - 50, 300 * 0.4, 50 * 0.4, 6, 1, true, RGB(255, 0, 255));
	main_Pika_down = new image;
	main_Pika_down->init("images/picka_down.bmp", WINSIZEX / 2, WINSIZEY - 50, 244 * 0.4, 256 * 0.4, 4, 4, true, RGB(255, 0, 255));
	//RECT 선언 시에, 프레임크기와 맞출 렉트를 가져오려면, 1560 / 10 * 0.8(출력 기본크기) / X축 또는 Y축 프레임 갯수(나누기)
	main_Pika_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 60, 1560 / 10 /4 * 0.8, 570 / 10 /2 * 0.8);//주인공 렉트 위치 초기화
	
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
		main_Pika->setFrameY(1);//두줄짜리 그림이니깐 y축에 대한 열을 이동시켜줌
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
	//메인캐릭터 피카츄 그리기 , 메인이니깐 맨 마지막으로
	//기본상태
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
	//피카츄 렉트 확인용
	//RectangleMake(hdc, main_Pika_rc.left, main_Pika_rc.top, main_Pika_rc.right - main_Pika_rc.left, main_Pika_rc.bottom - main_Pika_rc.top);
}
