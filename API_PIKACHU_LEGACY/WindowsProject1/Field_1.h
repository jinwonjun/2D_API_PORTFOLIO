#pragma once
class Field_1
{
private:
	image * field_1;//���� �ʵ� �̹��� ������
	image * pika_move;
	image * comment;//��ǳ�� �̹��� �ε�

	int pika_move_count;
	int pika_move_index;
	int pika_move_frame_index;//�ΰ� y�� ������ ������ �ε���
	int timer;

	image * fountain;
	int fountain_count;
	int fountain_index;
	int fountain_frame_index;//�ΰ� y�� ������ ������ �ε���
	
public:
	Field_1();
	~Field_1();

	//===================���� ����====================
	bool pika_comment_check;//��ī�� ��� �ϴ°� üũ ����, ���� �������� �̰� Ű������ �÷��̾� ǥ��
	RECT trees[40];//��ֹ� ���� �־�����
	RECT scene_check;//����ȯ Ȯ�ο� ��Ʈ
	bool scene_check_left = false;//����ȯ Ȯ�ο� bool��
	int comment_time;//��� ġ�°� �ð� ���� ����
	int comment_index;//��� ���� ���� �ε����� ����

	RECT battle_start_check;//������ ������ ��Ʈ �������ְ� ��Ʋ ������ �ѱ���
	bool battle_start;//rect�� ������, battle ���� Ŭ���� ȣ��, �⺻ false������ �ʱ�ȭ

	RECT field_1_to_3;//�ʵ� 1�� 3 üũ�� ��Ʈ
	bool field_1_to_3_check;//�ʵ� 1�� 3 üũ�� bool����
	//===================�Լ� ����====================
	HRESULT init();
	//���� �ʵ带 ȣ���غ���
	void render(HDC hdc);
	void pika_Motion_Render();
	void fountain_Render();
	bool treeColliderCheck(RECT PIKA_rc);//��ī��� ��ֹ�(����)�̶� �浹üũ ó��, �����Լ��� ���ϰ� �Ѱ���ߵ�
};

