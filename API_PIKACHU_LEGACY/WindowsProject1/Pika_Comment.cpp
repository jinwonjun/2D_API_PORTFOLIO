#include "stdafx.h"

Pika_Comment::Pika_Comment()
{
}


Pika_Comment::~Pika_Comment()
{
}

HRESULT Pika_Comment::init()
{
	pika_move = new image;
	pika_move->init("images/PikaAtk56_1.bmp", WINSIZEX / 2 + 100, WINSIZEY / 2 + 100, 4368, 135, 56, 1, true, RGB(255, 0, 255));

	comment = new image;
	comment->init("images/dialogue1.bmp", WINSIZEX / 2, 0, 400, 100, 1, 1, true, RGB(255, 0, 255));
	pika_move_count = 0;
	pika_move_index = 0;
	pika_move_frame_index = 0;

	
	timer = 0;

	comment_time = 0;//��� ġ�°� �ð� ���� ����
	comment_index = 1;//��� ���� ���� �ε����� ����

	return S_OK;
}

void Pika_Comment::pika_Motion_Render()
{
	pika_move_count++;
	if (pika_move_count % 3 == 0)//���ڴ� Ÿ�̸�, �ϰ������� ������ ������ ����
	{
		pika_move_count = 0;
		int frameX = (pika_move->getFrameX() + 1) % 56;
		pika_move->setFrameX(frameX);

		if (frameX == 0)
		{
			pika_move->setFrameY((pika_move->getFrameY() + 1) % 1);
		}
	}
}

//�� ��° �Ű������� Ŀ���͸� ���� �༭ ���� ���� ��ȭ�ϰ� ������
void Pika_Comment::render(HDC hdc, int statement)
{
	//��� case�� ���� ���� �ʱ�ȭ �����ֱ�
	//comment_index = 1;
	//comment_time = 0;
	//ó�� ������ ���� �ڸ��͸� ���� statement �Ű������� �Ѱ��ֱ�(mainGame.cpp �� �������� ������.)
	switch (statement)
	{
	case 1:
	{
		pika_move->frameRender(hdc, pika_move->getX(), pika_move->getY(), pika_move->getFrameX(), pika_move->getFrameY());
		comment->render(hdc, 0, WINSIZEY - 110);
		HFONT font, oldfont;
		font = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "PokemonGSC");
		oldfont = (HFONT)SelectObject(hdc, font);
		//��ȭ���� ��ġ ��Ʈ
		RECT rt = { 15,WINSIZEY - 90,WINSIZEX - 15,WINSIZEY };
		wstring str1 = L"���� �� ������... Ǯ���� ���� ģ������ ��������! ������ �����ڱ�!";
		//char str[] = "���� �� ������... Ǯ���� ���� ģ������ ��������! ������ �����ڱ�!";
		//DrawText(hdc, str, -1, &rt, DT_WORDBREAK);
		if (comment_time % 100 && comment_index < str1.size())
		{
			comment_index++;
		}
		wstring temp(str1.begin(), str1.begin() + comment_index);
		DrawTextW(hdc, temp.c_str(), -1, &rt, DT_WORDBREAK);
		comment_time++;
		
		//������Ʈ �������� �� ����
		SelectObject(hdc, oldfont);
		DeleteObject(font);
	}
	break;
	case 2:
	{
		//printf("�ڸ�Ʈ �ε��� : %d, �ڸ�Ʈ Ÿ�� : %d\n", comment_index, comment_time);
		pika_move->frameRender(hdc, pika_move->getX(), pika_move->getY(), pika_move->getFrameX(), pika_move->getFrameY());
		comment->render(hdc, 0, WINSIZEY - 110);
		HFONT font, oldfont;
		font = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "PokemonGSC");
		oldfont = (HFONT)SelectObject(hdc, font);
		//��ȭ���� ��ġ ��Ʈ
		RECT rt = { 15,WINSIZEY - 90,WINSIZEX - 15,WINSIZEY };
		timer++;
		if (timer < 150)
		{
			//char str[] = "�⺻ ���� ����� �����̾�! ȸ�� �������� �ʵ忡 ������!";
			//DrawText(hdc, str, -1, &rt, DT_WORDBREAK);
			wstring str2 = L"�⺻ ���� ����� �����̾�! ȸ�� �������� �ʵ忡 ������!";
			if (comment_time % 100 && comment_index < str2.size())
			{
				comment_index++;
			}
			wstring temp(str2.begin(), str2.begin() + comment_index);
			DrawTextW(hdc, temp.c_str(), -1, &rt, DT_WORDBREAK);
			comment_time++;
			if (timer == 149)
			{
				comment_index = 1;
				comment_time = 0;
			}
		}
		else if (timer >= 150 && timer < 300)
		{
			wstring str3 = L"������ ���ؼ� �������� �������� ������ �غ���!";
			if (comment_time % 100 && comment_index < str3.size())
			{
				comment_index++;
			}
			wstring temp(str3.begin(), str3.begin() + comment_index);
			DrawTextW(hdc, temp.c_str(), -1, &rt, DT_WORDBREAK);
			comment_time++;
			if (timer == 299)
			{
				comment_time = 0;
				comment_index = 1;
			}
		}
		else
			timer = 300;//�ʱ�ȭ�� �̻���
		//������Ʈ �������� �� ����
		SelectObject(hdc, oldfont);
		DeleteObject(font);
	}
	break;
	case 3:
	{
		pika_move->frameRender(hdc, pika_move->getX(), pika_move->getY(), pika_move->getFrameX(), pika_move->getFrameY());
		comment->render(hdc, 0, WINSIZEY - 110);
		HFONT font, oldfont;
		font = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "PokemonGSC");
		oldfont = (HFONT)SelectObject(hdc, font);
		//��ȭ���� ��ġ ��Ʈ
		RECT rt = { 15,WINSIZEY - 90,WINSIZEX - 15,WINSIZEY };
		timer++;
		if (timer < 150)
		{
			wstring str1 = L"���ϰ� �־�! RPG�� �⺻�� �ϴ� ���̴뺸�°���!";
			if (comment_time % 100 && comment_index < str1.size())
			{
				comment_index++;
			}
			wstring temp(str1.begin(), str1.begin() + comment_index);
			DrawTextW(hdc, temp.c_str(), -1, &rt, DT_WORDBREAK);
			comment_time++;
			if (timer == 149)
			{
				comment_time = 0;
				comment_index = 1;
			}
		}
		else if (timer >= 150 && timer < 300)
		{
			wstring str2 = L"�׷��ٸ� TABŰ�� �ѹ� ��������!\n�𸣸� �ϴ� �غ� �Ӹ�!!!";
			if (comment_time % 100 && comment_index < str2.size())
			{
				comment_index++;
			}
			wstring temp(str2.begin(), str2.begin() + comment_index);
			DrawTextW(hdc, temp.c_str(), -1, &rt, DT_WORDBREAK);
			comment_time++;
			if (timer == 299)
			{
				comment_time = 0;
				comment_index = 1;
			}
		}
		else if (timer >= 300 && timer < 450)
		{
			wstring str3 = L"������ �̱���(STL ���͸� ����ؾߵ�...��)...������ ���Ҹ��� ����?";
			if (comment_time % 100 && comment_index < str3.size())
			{
				comment_index++;
			}
			wstring temp(str3.begin(), str3.begin() + comment_index);
			DrawTextW(hdc, temp.c_str(), -1, &rt, DT_WORDBREAK);
			comment_time++;
			if (timer == 449)
			{
				comment_time = 0;
				comment_index = 1;
			}
		}
		else if (timer >= 450 && timer < 600)
		{
			wstring str4 = L"�������� ���ؼ� �� ������ �� �־�!\n��! �׷��ٸ� ������ ��� �����غ���?";
			if (comment_time % 100 && comment_index < str4.size())
			{
				comment_index++;
			}
			wstring temp(str4.begin(), str4.begin() + comment_index);
			DrawTextW(hdc, temp.c_str(), -1, &rt, DT_WORDBREAK);
			comment_time++;
			if (timer == 599)
			{
				comment_time = 0;
				comment_index = 1;
			}
		}
		else
			timer = 600;//�ʱ�ȭ�� �̻���
						//������Ʈ �������� �� ����
		SelectObject(hdc, oldfont);
		DeleteObject(font);
	}
	break;
	default:

		break;
	}
}