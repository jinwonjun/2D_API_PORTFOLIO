#include "stdafx.h"

npc_dr_o::npc_dr_o()
{
}

npc_dr_o::~npc_dr_o()
{
}

HRESULT npc_dr_o::init()
{
	dr_o_count = 0;
	dr_o_index = 0;
	dr_o_frame_index = 0;
	dr_o = new image;
	dr_o->init("images/sprite13m.bmp", WINSIZEX / 2, WINSIZEY / 2 +100, 144 * 0.8 , 256 * 0.8, 3, 4, true, RGB(255, 0, 255));

	dr_o_comment = new image;
	dr_o_comment->init("images/dr_o_meet_m.bmp", WINSIZEX / 2, 0, 400, 340, 1, 1, true, RGB(255, 0, 255));

	dr_o_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 100, 144 / 3 * 0.8 , 256 / 4 * 0.8);//���ΰ� ��Ʈ ��ġ �ʱ�ȭ
	//������ �⺻�� �ʱ�ȭ
	dr_o->setFrameX(-1);
	dr_o->setFrameY(-1);
	//����ǥ �̹���
	question = new image;
	question->init("images/question.bmp", WINSIZEX / 2, WINSIZEY / 2 + 100 - 68, 68, 62, 1, 1, true, RGB(255, 0, 255));
	//����ǥ �̹���
	feel = new image;
	feel->init("images/feel.bmp", WINSIZEX / 2, WINSIZEY / 2 + 100 - 68, 68, 62, 1, 1, true, RGB(255, 0, 255));
	//ȭ�� �̹���
	angry = new image;
	angry->init("images/angry.bmp", WINSIZEX / 2, WINSIZEY / 2 + 100 - 68, 68, 62, 1, 1, true, RGB(255, 0, 255));

	//�浹 üũ �ñ׳�
	CollideSignal = false;
	//��Ʈ �ð��� üũ ����
	timer = 0;

	comment_time = 0;
	comment_index = 1;

	return S_OK;
}

//������ ������(NPC �⺻������ ĳ���� ��ġ���� ����� ���⼳��)
//�ϴ� ��¸���(��ī���� ��Ʈ ���� �Ű������� �༭ ������ ��ġ�� �ĺ�������)
void npc_dr_o::DR_O_Render(RECT pika_rc)
{
	pika_rc_copy = pika_rc;//��ī�� ��ġ�� ����
	//�ڻ���̶� ��ī�� ������ ������ ���ؼ� ������ �غ���ƾƾ�
	float temp;
	temp = getAngle((pika_rc.right + pika_rc.left) / 2, (pika_rc.bottom + pika_rc.top) / 2, (dr_o_rc.right + dr_o_rc.left) / 2, (dr_o_rc.bottom + dr_o_rc.top) / 2);
	//printf("%f\n", temp);

	dr_o_count++;
	if (dr_o_count % 10 == 0)//���ڴ� Ÿ�̸�, �ϰ������� ������ ������ ����
	{
		dr_o_count = 0;
		int frameX = (dr_o->getFrameX() + 1) % 3;
		dr_o->setFrameX(frameX);

		//����(�����)
		if (-3.0f < temp && -0.4f > temp)
		{
			dr_o->setFrameY(0);
		}
		//������(������ ����)
		if (2.0f < temp && 4.0f > temp)
		{
			dr_o->setFrameY(1);
		}
		//�Ʒ���(�ո�)
		if (0.8f < temp && 2.0f > temp)
		{
			dr_o->setFrameY(2);
		}
		//����(���� ����)
		if (-0.4f < temp && 0.8f > temp)
		{
			dr_o->setFrameY(3);
		}
	}
	
	//��ī��� �浹üũ �ñ׳� �����
	RECT tempRC;
	if (IntersectRect(&tempRC, &dr_o_rc, &pika_rc))
	{
		CollideSignal = true;
	}
}

//���� �Ѱ� �׷��ֱ�
void npc_dr_o::render(HDC hdc)
{
	dr_o->frameRender(hdc, dr_o->getX(), dr_o->getY(), dr_o->getFrameX(), dr_o->getFrameY());
	
	//��Ʈ ��ġ�� Ȯ�ο�
	//RectangleMake(hdc, dr_o_rc.left, dr_o_rc.top, dr_o_rc.right - dr_o_rc.left, dr_o_rc.bottom - dr_o_rc.top);

	//���ڻ�� ��ī�� ��Ʈ �浹 üũ �ɾ true�϶� ǥ�����ֱ�
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
			question->render(hdc, dr_o_rc.left, dr_o_rc.top - 40);
		}
		else if (timer >= 50 && timer < 100)
		{
			//����ǥ
			feel->render(hdc, dr_o_rc.left, dr_o_rc.top - 40);
		}
		else if (timer >= 100 && timer < 200)
		{
			//�̹��� �߰�
			dr_o_comment->render(hdc, 0, WINSIZEY / 2-15);
			wstring str1 = L"�Ѹ�?!?!!! �߻��� ��ī�� �̷� ���� ���� ������ ������?!";
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
			dr_o_comment->render(hdc, 0, WINSIZEY / 2-15);
			wstring str2 = L"�ű�!!! ��....��¦�� ����!";
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
			//ȭ�� ǥ��
			angry->render(hdc, pika_rc_copy.left, pika_rc_copy.top - 40);
			if (timer > 500)
			{
				CollideSignal = false;
				timer = 0;
			}
		}
		//������Ʈ �������� �� ����
		SelectObject(hdc, oldfont);
		DeleteObject(font);
	}
}

float npc_dr_o::getAngle(float x1, float y1, float x2, float y2)
{

	float x = x2 - x1;
	float y = y2 - y1;
	//���� ������ �Ÿ��� ���ϴ� ����
	float distance = sqrtf(x * x + y *y);
	//���� ������ ���� ���ϴ� ����
	float angle = acosf(x / distance);

	if (y2 > y1)
	{
		angle = -angle;

		if (angle >= 2 * PI) angle -= 2 * PI;
	}
	//_cannon.cannonEnd.x = cosf(_cannon.angle) * _cannon.cannon + _cannon.center.x;
	//_cannon.cannonEnd.y = -sinf(_cannon.angle) * _cannon.cannon + _cannon.center.y;
	return angle;
}