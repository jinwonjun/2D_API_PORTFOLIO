#pragma once
class Silver_Mountain
{
private:
	image * field_3_img;
	image * field_3_msk;//�浹 üũ �־��� ����ŷ �̹��� �����
public:
	Silver_Mountain();
	~Silver_Mountain();
	//===================���� ����====================
	bool silver_mountain_check;//���� �ѹ��� ������� �ʱ�ȭ ������
	RECT field_3_rc;//�ʵ� �浹 üũ ��Ʈ
	RECT Boss_check_rc;//���� �浹 üũ ��Ʈ
	RECT field_3_rc_msk;//����ŷ�̹��� ��Ʈ
	//===================�Լ� ����====================
	HRESULT init();
	void render(HDC hdc);
	//���� �ʵ带 ȣ���غ���
	void field_3_Render();
	//��ī��� �浹 üũ
	bool bossColliderCheck(RECT PIKA_rc);//��ī��� �浹üũ ó��, �����Լ��� ���ϰ� �Ѱ���ߵ�
	bool field_3_pixel_Check(RECT PIKA_rc, int direction);
};

