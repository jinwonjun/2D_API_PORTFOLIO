#pragma once
class npc_dr_o
{
private:
	image * dr_o;//������ �������� �̹���
	int dr_o_count;
	int dr_o_index;
	int dr_o_frame_index;//�ΰ� y�� ������ ������ �ε���
	//���ڻ���
	image *  dr_o_comment;//�ڸ�Ʈ ��¿� �̹���
	image * feel;//����ǥ �̹���
	image * question;//����ǥ �̹���
	//��ī����
	image * angry;

public:
	npc_dr_o();
	~npc_dr_o();

	//===================���� ����====================
	RECT dr_o_rc;//npc ��Ʈ ����
	RECT pika_rc_copy;//��ī�� ��Ʈ�� ī��

	bool CollideSignal;//�浹 üũ ���� �� ���ڻ� �̹��� �÷��ֱ�
	int timer;//���� ����ֱ�� Ÿ�̸�

	int comment_time;//��� ġ�°� �ð� ���� ����
	int comment_index;//��� ���� ���� �ε����� ����
	//===================�Լ� ����====================
	HRESULT init();
	void DR_O_Render(RECT pika_rc);
	void render(HDC hdc);

	float getAngle(float x1, float y1, float x2, float y2);
};

