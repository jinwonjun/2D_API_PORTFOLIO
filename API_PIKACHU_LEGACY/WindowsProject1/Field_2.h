#pragma once
class Field_2
{
private:
	image * field_2_img;
	int field_2_count;
	int field_2_index;
	int field_2_frame_index;//�ΰ� y�� ������ ������ �ε���
	RECT field_2_rc;//�ʵ� �浹 üũ ��Ʈ

	image * huioong;//���� ���� �ÿ� �ֿ��� �̹��� ����ֱ�
	image * feel;//����ǥ �̹���
	image * question;//����ǥ �̹���

public:
	Field_2();
	~Field_2();

	
	//===================���� ����====================
	RECT huioong_rc;//�浹 üũ�� rc
	RECT pika_rc_copy;//��ī�� ��Ʈ�� ī��
	bool CollideSignal;//�浹 üũ ���� �� �ֿ� �̹��� �÷��ֱ�
	int timer;//���� ����ֱ�� Ÿ�̸�

	int comment_time;//��� ġ�°� �ð� ���� ����
	int comment_index;//��� ���� ���� �ε����� ����

	//===================�Լ� ����====================
	HRESULT init();
	void render(HDC hdc);
	//���� �ʵ带 ȣ���غ���
	void field_2_Render();
	//��ī��� �浹 üũ
	bool treeColliderCheck(RECT PIKA_rc);
};

