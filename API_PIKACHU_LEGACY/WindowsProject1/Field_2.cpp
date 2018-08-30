#include "stdafx.h"

Field_2::Field_2()
{
}


Field_2::~Field_2()
{
}

HRESULT Field_2::init()
{
	field_2_img = new image;
	field_2_img->init("images/field_2_4_19.bmp",WINSIZEX/2,WINSIZEY/2+155,2000,6327,4,19,true, RGB(255, 0, 255));
	field_2_count=0;
	field_2_index=0;
	field_2_frame_index=0;//�ΰ� y�� ������ ������ �ε���
	field_2_img->setFrameX(-1);
	field_2_img->setFrameY(-1);

	field_2_rc = RectMake(0,WINSIZEY/2-13,115,WINSIZEY/2 +20);

	huioong = new image;
	huioong->init("images/huioong_meet.bmp", WINSIZEX / 2, 0, 400, 340, 1, 1, true, RGB(255, 0, 255));
	huioong_rc = RectMake(180,WINSIZEY/2 + 122, 40,50);//�浹 üũ�� rc

	//����ǥ �̹���
	question = new image;
	question->init("images/question.bmp", WINSIZEX / 2, WINSIZEY / 2 + 100 - 68, 68, 62, 1, 1, true, RGB(255, 0, 255));
	//����ǥ �̹���
	feel = new image;
	feel->init("images/feel.bmp", WINSIZEX / 2, WINSIZEY / 2 + 100 - 68, 68, 62, 1, 1, true, RGB(255, 0, 255));

	comment_time = 0;
	comment_index = 1;

	return S_OK;
}

void Field_2::field_2_Render()
{
	field_2_count++;
	if (field_2_count % 2 == 0)//���ڴ� Ÿ�̸�, �ϰ������� ������ ������ ����
	{
		field_2_count = 0;
		int frameX = (field_2_img->getFrameX() + 1) % 4;
		field_2_img->setFrameX(frameX);

		if (frameX == 0)
		{
			field_2_img->setFrameY((field_2_img->getFrameY() + 1) % 19);
		}
	}
}

bool Field_2::treeColliderCheck(RECT PIKA_rc)
{
	pika_rc_copy = PIKA_rc;//��ī�� ��ġ�� ����

	//��ī��� �浹üũ �ñ׳� �����
	RECT tempRC;
	if (IntersectRect(&tempRC, &huioong_rc, &PIKA_rc))
	{
		CollideSignal = true;
	}

	RECT temp;//���� �ӽ� ������ ����
	if (IntersectRect(&temp, &field_2_rc, &PIKA_rc))
	{
		return true;
	}

	return false;
}

void Field_2::render(HDC hdc)
{
	field_2_img->frameRender(hdc, field_2_img->getX(), field_2_img->getY(), field_2_img->getFrameX(), field_2_img->getFrameY());
	//RectangleMake(hdc, huioong_rc.left, huioong_rc.top, huioong_rc.right - huioong_rc.left, huioong_rc.bottom - huioong_rc.top);
	//RectangleMake(hdc, field_2_rc.left, field_2_rc.top, field_2_rc.right- field_2_rc.left, field_2_rc.bottom- field_2_rc.top);

	//�ֿ��̶� ��ī�� ��Ʈ �浹 üũ �ɾ true�϶� ǥ�����ֱ�
	if (CollideSignal)
	{
		//��Ʈ ����
		HFONT font, oldfont;
		font = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "PokemonGSC");
		oldfont = (HFONT)SelectObject(hdc, font);
		//��ȭ���� ��ġ ��Ʈ
		RECT rt = { 15,WINSIZEY - 90,WINSIZEX - 15,WINSIZEY };
		timer++;
		if (timer < 50)
		{
			//����ǥ
			question->render(hdc, huioong_rc.left, huioong_rc.top - 40);
		}
		else if (timer >= 50 && timer < 100)
		{
			//����ǥ
			feel->render(hdc, huioong_rc.left, huioong_rc.top - 40);
		}
		else if (timer >= 100 && timer < 200)
		{
			//�̹��� �߰�
			huioong->render(hdc, 0, WINSIZEY / 2 - 15);
			wstring str1 = L"����?!?! �� ��ġ�� �ʾ� ������ ģ���� ������! ������ �ϴ� ���̱���?";
			if (comment_time % 100 && comment_index < str1.size())
			{
				comment_index++;
			}
			wstring temp(str1.begin(), str1.begin() + comment_index);
			DrawTextW(hdc, temp.c_str(), -1, &rt, DT_WORDBREAK);
			comment_time++;
			//���� ��Ʈ ������ֱ� ���� �ε��� �ʱ�ȭ ��Ű��
			if (timer == 199)
			{
				comment_index = 1;
				comment_time = 0;
			}
		}
		else if (timer >= 200 && timer < 300)
		{
			//�̹��� �߰�
			huioong->render(hdc, 0, WINSIZEY / 2 - 15);
			wstring str2 = L"��� ����� ���ϸ��� Ž�ϴ� �� �ƴ϶���! �׷��� �׻� �����Ϸ�!";
			if (comment_time % 100 && comment_index < str2.size())
			{
				comment_index++;
			}
			wstring temp(str2.begin(), str2.begin() + comment_index);
			DrawTextW(hdc, temp.c_str(), -1, &rt, DT_WORDBREAK);
			comment_time++;
			//���� ��Ʈ ������ֱ� ���� �ε��� �ʱ�ȭ ��Ű��
			if (timer == 299)
			{
				comment_index = 1;
				comment_time = 0;
			}
		}
		//�ʱ�ȭ
		else
		{
			//��ü Ÿ�̸Ӵ� 900�϶� �ʱ�ȭ ��Ű��
			//��ī�� ��Ʈ�� �̾������ؼ� ������ �ð��� �ø�.
			if (timer >= 900)
			{
				//�ߵ������� true�϶���!
				CollideSignal = false;
				timer = 0;
			}
		}
		//������Ʈ �������� �� ����
		SelectObject(hdc, oldfont);
		DeleteObject(font);
	}

}