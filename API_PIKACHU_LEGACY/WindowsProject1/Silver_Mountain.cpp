#include "stdafx.h"

Silver_Mountain::Silver_Mountain()
{
}

Silver_Mountain::~Silver_Mountain()
{
}

HRESULT Silver_Mountain::init()
{
	field_3_img = new image;
	//field_3_img->init("images/silver_mountain.bmp", WINSIZEX / 2, 0,400,1074,1,1, true, RGB(255, 0, 255));
	field_3_img->init("images/silver_mountain.bmp", 400, 1074, 400, 1074, 1, 1, true, RGB(255, 0, 255));
	//field_3_rc = RectMake(0,WINSIZEY/2-15,WINSIZEX,WINSIZEY/2+15);//�ʵ� bmp ���� ��Ʈ
	field_3_rc = field_3_img->getBoundingBox();

	field_3_msk = new image;
	field_3_msk->init("images/silver_mountain_msk_2.bmp", 400, 1074, 400, 1074, 1, 1, true, RGB(255, 0, 255));
	field_3_rc_msk = field_3_msk->getBoundingBox();

	Boss_check_rc = RectMake(170,-230,30,45);

	silver_mountain_check = false;
	return S_OK;
}

//������ �浹 üũ ó��
bool Silver_Mountain::bossColliderCheck(RECT PIKA_rc)
{
	RECT temp;
	if (IntersectRect(&temp, &Boss_check_rc, &PIKA_rc))
	{
		return true;
	}

	return false;
}
//�Ű����� 4���� �ϱ� 1�̸� ����// 2�̸� ������// 3�̸� ����// 4�� �Ʒ���
bool Silver_Mountain::field_3_pixel_Check(RECT PIKA_rc, int direction)
{
	COLORREF color;
	switch (direction)
	{
	case 1:
	{
		color = GetPixel(field_3_msk->getMemDC(), PIKA_rc.left - PIKA_SPEED, PIKA_rc.top);
	}
	break;
	case 2:
	{
		color = GetPixel(field_3_msk->getMemDC(), PIKA_rc.right + PIKA_SPEED, PIKA_rc.top);
	}
	break;
	case 3:
	{
		color = GetPixel(field_3_msk->getMemDC(), PIKA_rc.right, PIKA_rc.top - PIKA_SPEED);
	}
	break;
	case 4:
	{
		color = GetPixel(field_3_msk->getMemDC(), PIKA_rc.left, PIKA_rc.bottom + PIKA_SPEED);
	}
	break;
	default:
		break;
	}
	
	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);

	//�̵��� ��ǥ�� ����Ÿ�ų� �����̸� �浹
	if ((r == 255 && g == 0 && b == 255) || (r == 0 && g == 0 && b == 255))
	{
		return true;
	}

	return false;
}
//�׸���
void Silver_Mountain::render(HDC hdc)
{
	field_3_img->render(hdc, field_3_rc.left, (field_3_rc.bottom - 764));
	//����ŷ �̹��� Ȯ�ο�
	//field_3_msk->render(field_3_msk->getMemDC(), field_3_rc_msk.left, (field_3_rc_msk.bottom) - 764);
	//field_3_msk->render(hdc, field_3_rc_msk.left, (field_3_rc_msk.bottom) - 764);
	
}
//������� Ű��(��Ʈ ��ġ��)�� �޾Ƽ� �� ����������
void Silver_Mountain::field_3_Render()
{
	//printf("left : %d , right : %d , top : %d, bottom : %d\n", field_3_rc.left, field_3_rc.right, field_3_rc.top, field_3_rc.bottom);
	//�ʵ� ���� ���� �ѹ��� �����ֱ�
	if (field_3_rc.bottom >= 350 && silver_mountain_check == false)
	{
		field_3_rc.top -= PIKA_SPEED;
		field_3_rc.bottom -= PIKA_SPEED;

		field_3_rc_msk.top -= PIKA_SPEED;
		field_3_rc_msk.bottom -= PIKA_SPEED;

		if (field_3_rc.bottom == 348)
		{
			silver_mountain_check = true;
		}
	}
}
