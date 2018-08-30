#include "stdafx.h"


Game_Opening::Game_Opening()
{
}

Game_Opening::~Game_Opening()
{
	//SAFE_DELETE(down_logo);
}

HRESULT Game_Opening::init()
{
	//�ΰ� ��� �̹��� �ҷ�����
	//��� �ΰ� �κ� �ʱ�ȭ
	logo_count = 0;
	logo_index = 0;
	logo_frame_index = 0;
	up_logo = new image;
	up_logo->init("images/logo_1.bmp", WINSIZEX / 2, WINSIZEY / 2 - 180, 7968 * 1.2, 840 * 1.2, 16, 3, true, RGB(255, 0, 255));
	up_logo->setFrameX(-1);
	up_logo->setFrameY(-1);

	//�ϴ� �ΰ� �κ� �ʱ�ȭ
	logo_down_count = 55;
	logo_down_index = 0;
	logo_down_frame_index = 0;//�ΰ� y�� ������ ������ �ε���
	down_logo = new image;
	down_logo->init("images/logo_2.bmp", WINSIZEX / 2, WINSIZEY / 2 + 160, 1762 * 0.7, 398 * 0.7, 2, 1, true, RGB(255, 0, 255));
	down_logo->setFrameX(-1);
	down_logo->setFrameY(-1);

	//============== �ý��� ���� ������ ==============
	GameStartSignal = false;//��ŸƮŰ Ȯ�� �ñ׳�
	timer = 0;//Ÿ�̸� �ʱ�ȭ

	//============== UI ���� �ʱ�ȭ ���� =============
	//�Ḹ���׸�
	test = new image;
	test->init("images/test_2.bmp", WINSIZEX / 2, 0, 400, 330, 1, 1, true, RGB(255, 0, 255));

	//��� ġ�� �κ� �ʱ�ȭ
	comment_time = 0;
	comment_index = 1;

	return S_OK;
}

//��� �ΰ�
void Game_Opening::Logo_Up_Render()
{
	logo_count++;
	if (logo_count % 5 == 0)//���ڴ� Ÿ�̸�, �ϰ������� ������ ������ ����
	{
		logo_count = 0;
		int frameX = (up_logo->getFrameX() + 1) % 16;
		up_logo->setFrameX(frameX);

		if (frameX == 0)
		{
			up_logo->setFrameY((up_logo->getFrameY() + 1) % 3);
		}
		if (up_logo->getFrameY() == 2)//������ ǥ�� ������ �ǵ�����
		{
			up_logo->setFrameX(0);
			up_logo->setFrameY(0);
		}
	}
}
//�ϴ� �ΰ�
void Game_Opening::Logo_down_Render()
{
	logo_down_count++;
	if (logo_down_count % 30 == 0)//���ڴ� Ÿ�̸�, �ϰ������� ������ ������ ����
	{
		logo_down_count = 0;
		int frameX = (down_logo->getFrameX() + 1) % 2;
		down_logo->setFrameX(frameX);

		if (frameX == 0)
		{
			down_logo->setFrameY((down_logo->getFrameY() + 1) % 1);
		}
	}
}

void Game_Opening::render(HDC hdc)
{
	down_logo->frameRender(hdc, down_logo->getX(), down_logo->getY(), down_logo->getFrameX(), down_logo->getFrameY());
	up_logo->frameRender(hdc, up_logo->getX(), up_logo->getY(), up_logo->getFrameX(), up_logo->getFrameY());

	//��� ����(�κ��丮)�� ��ü�� ��Ȳ�� ������ֱ� ���� bool���� �ʿ���!
	if (GameStartSignal)
	{
		//�̹��� �߰�
		test->render(hdc, 0, WINSIZEY / 2);
		//��Ʈ ����
		HFONT font, oldfont;
		font = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "PokemonGSC");
		oldfont = (HFONT)SelectObject(hdc, font);
		//��ȭ���� ��ġ ��Ʈ
		RECT rt = { 15,WINSIZEY - 90,WINSIZEX - 15,WINSIZEY };
		timer++;
		if (timer < 100)
		{
			wstring str1 = L"��ī�� ���� �� �����̴簡! ���ϸ�Ʈ���̳� ��� �Ű� ������� ������!";
			if (comment_time % 100 && comment_index < str1.size())
			{
				comment_index++;
			}
			wstring temp(str1.begin(), str1.begin() + comment_index);
			DrawTextW(hdc, temp.c_str(), -1, &rt, DT_WORDBREAK);
			comment_time++;
			//���� ��Ʈ ������ֱ� ���� �ε��� �ʱ�ȭ ��Ű��
			if (timer == 99)
			{
				comment_index = 1;
				comment_time = 0;
			}
		}
		else if (timer >= 100 && timer < 200)
		{
			wstring str2 = L"�ۿ� �߿�ϱ� �ĵ� �ε��� ���� �尡��! �� ���� �� �� ������ �̸�!";
			if (comment_time % 100 && comment_index < str2.size())
			{
				comment_index++;
			}
			wstring temp(str2.begin(), str2.begin() + comment_index);
			DrawTextW(hdc, temp.c_str(), -1, &rt, DT_WORDBREAK);
			comment_time++;
		}
		else
			GameStartSignal = false;
		//������Ʈ �������� �� ����
		SelectObject(hdc, oldfont);
		DeleteObject(font);
	}
}

void Game_Opening::only_up_logo_render(HDC hdc)
{
	up_logo->frameRender(hdc, up_logo->getX(), up_logo->getY(), up_logo->getFrameX(), up_logo->getFrameY());
}
