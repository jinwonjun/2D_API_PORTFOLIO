#pragma once
#include"gameNode.h"

/*
1. image * Ÿ�� �����ϱ�
2. int m_count;//�ϸ� ������ ���� ī��Ʈ ����
	int m_index;//������ �̹��� �ε���
	bool m_isLeft; //����üũ
3. init �κ� �̹��� Ÿ�� new �� ����
4. m_rockman->init("images/�ϸ�2.bmp", WINSIZEX / 2, WINSIZEY / 2, 1440, 300, 10, 2, true, RGB(255, 0, 255));//�ǿ����� �Ķ���ʹ� ������ ����Ÿ �����ų�
5. 
*/
class mainGame :  public gameNode
{

private:
//==============�ý��� ���� ������==============


	//����ĳ����(��ī��)���� ����
	mainCharacter *pika;
	//���� ������ ��������
	Game_Opening *open;
	
	//========= �ʵ� ���� ����================
	//�ʵ�_1 ��������
	Field_1 * field_1;
	//�ʵ�_2 ��������
	Field_2 * field_2;
	//�ʵ�_3 ��������
	Silver_Mountain * field_3;


	//========= �κ��丮 ���� ����============
	Inventory * Invent;


	//========= NPC ���� ����=================
	npc_dr_o *DR_O;

	//=== ��ī�� �ڸ��͸� ��� ���� ����======
	Pika_Comment *pika_comment;

	//======== ���� ������ ���� ����==========
	battle_scene * battle;

public:
	mainGame();
	~mainGame();
	//===========���� ���� �κ�================
	bool tree_collide_pika;//��ī��� ������ ��ֹ� üũ��(1���ʵ�)
	bool tree_collide_pika_2;//��ī��� ������ ��ֹ� üũ��(2���ʵ�)
	int map_check_signal;//��� ������ üũ�غ���
	bool pika_position_initialize_1;//��ī�� ��� �Ѿ �ÿ� ��ġ �ʱ�ȭ üũ��
	bool pika_position_initialize_2;//��ī�� ��� �Ѿ �ÿ� ��ġ �ʱ�ȭ üũ��
	bool pika_position_initialize_3;
	bool field_3_pixel_check;
	//===========�Լ� ���� �κ�================
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void pika_field_key_control();//�ʵ� �󿡼��� ��ī�� Ű���� ��Ʈ��
	void scene_position_initialize();//�� �ʵ忡 ���� ��ī�� ��ġ �ʱ�ȭ�� ���� ������

};

