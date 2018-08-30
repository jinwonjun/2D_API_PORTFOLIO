#include "stdafx.h"
#include "mainGame.h"

//2�� �з��� API ��Ʈ������ ���̽��ϰ� �����

mainGame::mainGame()
{
}

mainGame::~mainGame()
{
} 

HRESULT mainGame::init()
{
	gameNode::init();
	//������ �� �������� �� �ʱ�ȭ
	open = new Game_Opening;
	open->init();
	//�ʵ�1 �������� �� �ʱ�ȭ
	field_1 = new Field_1;
	field_1->init();
	//�ʵ�2 �������� �� �ʱ�ȭ
	field_2 = new Field_2;
	field_2->init();
	//�ʵ�3 �������� �� �ʱ�ȭ
	field_3 = new Silver_Mountain;
	field_3->init();
	field_3_pixel_check = false;

	//���� ĳ���� ���� ���� �� �ʱ�ȭ
	pika = new mainCharacter;
	pika->init();

	//npc ���� ���� �� �ʱ�ȭ
	DR_O = new npc_dr_o;
	DR_O->init();

	//��ī�� �ڸ��͸� �������� �� �ʱ�ȭ
	pika_comment = new Pika_Comment;
	pika_comment->init();

	//�κ��丮 �������� �� �ʱ�ȭ
	Invent = new Inventory;
	Invent->init();

	//���� ������ ���� ���� �� �ʱ�ȭ
	battle = new battle_scene;
	battle->init();
	//�浹 üũ bool�� �ʱ�ȭ
	tree_collide_pika = false;
	tree_collide_pika_2 = false;
	//�� ���� ���� ���ǰ� �ʱ�ȭ(1�� �ʵ�� 1, 2�� �ʵ�� 2, �̷���)
	map_check_signal = 0;
	//���� ���� ��ī�� �ʱ�ȭ �˻�� bool�� �ʱ�ȭ
	pika_position_initialize_1 = false;
	pika_position_initialize_2 = false;
	pika_position_initialize_3 = false;

	return S_OK; // �Լ��� ���������� ���ư��� �ǹ���.
}

void mainGame::release()
{
	gameNode::release();

	//SAFE_DELETE( m_bgImage );
	//SAFE_DELETE(m_rockman);
	open->~Game_Opening();
	field_1->~Field_1();
	pika->~mainCharacter();
	DR_O->~npc_dr_o();
	battle->release();
	Invent->~Inventory();
}

void mainGame::update()
{
	gameNode::update();
	//�ΰ� �׸��� ������Ʈ
	open->Logo_Up_Render();
	open->Logo_down_Render();

	//�� ���� ���� ��ī�� ��ġ �ʱ�ȭ
	scene_position_initialize();

	//�ʵ� �κ�
	//�ʵ�1 ���� �Լ� ȣ��
	field_1->pika_Motion_Render();
	field_1->fountain_Render();
	//�浹ó�� üũ�� ��� �޾ƿ�
	tree_collide_pika = false;
	tree_collide_pika_2 = false;
	//�ʵ�2 ���� �Լ� ȣ��
	field_2->field_2_Render();
	//�ʵ�3 ���� �Լ� ȣ��
	//�׽� �ʱ�ȭ
	field_3_pixel_check = false;

	if (field_1->field_1_to_3_check)
	{
		field_3->field_3_Render();
		//field_3_pixel_check = field_3->field_3_pixel_Check(pika->main_Pika_rc);
		//�ʵ�3���� ������ �浹 üũ �� ��Ʋ �� ȣ��
		if (field_3->bossColliderCheck(pika->main_Pika_rc))
		{
			battle->battle_scene_check = true;
			
			pika->main_Pika_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 80, 1560 / 10 / 4 * 0.8, 570 / 10 / 2 * 0.8);//���ΰ� ��Ʈ ��ġ �ʱ�ȭ
		}
	}

	//��ī�� �ڸ��͸� �ִϸ��̼�ó��
	pika_comment->pika_Motion_Render();

	//NPC ��Ʈ��
	DR_O->DR_O_Render(pika->main_Pika_rc);

	//��ī��(�÷��̾�)��Ʈ�� ���� �⺻�� �ʱ�ȭ �� ����
	pika->leftPress = false;
	pika->rightPress = false;
	pika->downPress = false;
	pika->pickaDownRender();//��ī�� �� ���, idle���� �׷��ִ� ���� �Լ�

	//�κ��丮 ������ ���� ���ǰ� �ִ� �Լ� ȣ��
	Invent->tab_key_control();

	//��Ʋ�� ȣ��
	if (battle->battle_scene_check)
	{
		battle->update();
	}

	//��Ʋ�� �ƴ� ��� ����϶��� ȣ���ϵ��� ����
	if (! battle->battle_scene_check)
	{
		//�ʵ� �󿡼� Ű �Է� ���� main �Լ����� ó����.(ĳ���� ��Ʈ���̶� ���� �Լ����� ó��.)
		pika_field_key_control();
	}
	
	//�⺻ ���� ����Ű, ������ ���� Ű ���� �̰ɷ� ��.
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		//������ ȭ�鿡 �����̽��� Ű �Է��Ŀ�, ����ȭ������ ��ȯ(�ѹ��� ����ߵ�)
		open->GameStartSignal = true;
	}
}

void mainGame::render(HDC hdc)
{
	//gameNode::render(hdc);
	//����ۿ� �ѷ���(������ �� ���� �ǵ�����)
	HDC memDC = this->getBackBuffer()->getMemDC();
	//��� �� ��Ʈ��
	PatBlt( memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS );
	//========================================//
	//���� ���� ������ ���
	open->render(memDC);
	//���� �⺻ RPG�� ������!!!
	if (open->GameStartSignal == false && open->timer >= 200)
	{
		//�ʵ� �׸���
		//field_1->render(memDC);
		// �ʵ带 �Ѿ����!
		//field_1->scene_check_left ���ǰ� üũ �κ��� �ϴ��� pika_field_key_control(); �Լ��� update()���� ��� ���� ������ üũ ������.
		if (field_1->scene_check_left)
		{
			map_check_signal = 2;
			field_1->scene_check = RectMake(WINSIZEX - 30, WINSIZEY - 130, 30, 30);
			field_2->render(memDC);

			//��ī�� ��ġ �ʱ�ȭ�� �ñ׳�, 2�ʿ��� 1�ñ׳��� �ʱ�ȭ
			pika_position_initialize_1 = false;

			DR_O->CollideSignal = false;//���ڻ�� �浹üũ ������
			field_1->battle_start = false;//���� ���� �浹üũ ������
			field_1->field_1_to_3_check = false;//1�������� 3������ �Ѿ�� �浹üũ ����

			//��ī�� �׸���, �ֿ��� ��Ʈ ���ö� �׸��� ����
			if (field_1->pika_comment_check && field_2->timer<100)//��ī�� ��� ������ ��ī�� ��� �׸���
			{
				pika->render(memDC);
			}
			if (field_2->timer >= 300 && field_2->CollideSignal)//��ī�� �ڸ�Ʈ ȣ��
			{
				pika_comment->render(memDC, 3);
				//�� ������ �ʱ�ȭ
				if (field_2->timer == 899)
				{
					field_2->timer = 0;
					pika_comment->timer = 0;
					field_2->CollideSignal = false;
				}
			}
			//�˻�� ��Ʈ �׸���
			//�ʳѾ�� �˻� ��Ʈ
			//RectangleMake(memDC, field_1->scene_check.left, field_1->scene_check.top, field_1->scene_check.right - field_1->scene_check.left, field_1->scene_check.bottom - field_1->scene_check.top);
			//��ī�� ��Ʈ
			//RectangleMake(memDC, pika->main_Pika_rc.left, pika->main_Pika_rc.top, pika->main_Pika_rc.right - pika->main_Pika_rc.left, pika->main_Pika_rc.bottom - pika->main_Pika_rc.top);
		}
		else
		{
			map_check_signal = 1; //�� ��� �� �Ҵ�(�浹 �˻� ���� �߰��뵵)

			field_1->scene_check = RectMake(0, WINSIZEY - 100, 30, 30);
			field_1->render(memDC);

			//��ī�� ��ġ �ʱ�ȭ�� �ñ׳�, 1�ʿ��� 2�ñ׳��� �ʱ�ȭ
			pika_position_initialize_2 = false;

			field_2->CollideSignal = false;//�ֿ��̶� �浹 üũ ������

			//��ī�� �׸���
			if (field_1->pika_comment_check)//��ī�� ��� ������ ��ī�� ��� �׸���
			{
				pika->render(memDC);
			}

			//�ʵ� 1������ ���ڻ縦 �׷�����
			DR_O->render(memDC);
			if (DR_O->timer > 350)
			{
				pika_comment->render(memDC, 1);
				if (DR_O->timer == 500)
				{
					//������ ���� ���� �ε��� �� Ÿ�̸� �ʱ�ȭ
					pika_comment->comment_index = 1;
					pika_comment->comment_time = 0;
				}
			}
			//3�� �ʵ�׸���
			if (field_1->field_1_to_3_check)
			{
				//�ʵ� ������ �����ϸ� ���� ������ �ٲ���
				//battle->battle_scene_check = true;
				map_check_signal = 3;
				DR_O->CollideSignal = false;//���ڻ�� �浹üũ ������
				field_3->render(memDC);//�ʵ� �׷��ֱ�
				open->only_up_logo_render(memDC);//��� �ΰ� �׸���

				//3�� ������ 1�� �� ��ȯ ���� üũ��
				//field_1->field_1_to_3 = RectMake(170, WINSIZEY - 30, 60, 30);//�ʵ� 1�� 3 üũ�� ��Ʈ
				//RectangleMake(memDC, field_1->field_1_to_3.left, field_1->field_1_to_3.top, field_1->field_1_to_3.right - field_1->field_1_to_3.left, field_1->field_1_to_3.bottom - field_1->field_1_to_3.top);

				if (pika_position_initialize_3 && field_3->silver_mountain_check)//�ʱ�ȭ ���� �ɱ�
				{
					pika->render(memDC);//��ī�� �׸���
				}
			}
			//�˻�� ��Ʈ �׸���
			//RectangleMake(memDC, field_1->scene_check.left, field_1->scene_check.top, field_1->scene_check.right - field_1->scene_check.left, field_1->scene_check.bottom - field_1->scene_check.top);
		}
	}

	//�ʵ忡���� ȣ�� �ؾߵǴϱ� �κ��丮 ���� �ɾ�����
	if (map_check_signal==1 || map_check_signal == 2 || map_check_signal == 3)
	{
		Invent->render(memDC);
	}
	//���� ������� �̵�
	if (battle->battle_scene_check)
	{
		map_check_signal = 0;
		battle->render(memDC);
		//������� ���� �� ��ī�� �ڸ��͸�
		if (battle->pikaHp <= 0 || battle->boss.bossHp <= 0)
		{
			//������� ������ �ڸ��͸� �˷��ֱ�, �ڸ�Ʈ ���� ȣ������ ���� �ʱ�ȭ
			pika_comment->render(memDC, 2);
			//�ʱ�ȭ �� �缳��
			if (pika_comment->timer == 300)
			{
				battle->init();//�ڸ��͸� ������ �ʱ�ȭ��Ű��
				pika_comment->timer = 0;//Ÿ�̸� �ʱ�ȭ
				pika_position_initialize_1 = false;
				battle->battle_scene_check = false;
				//map_check_signal = 3;
				scene_position_initialize();//��ī�� ��ġ �ʱ�ȭ
			}
		}
	}

	//printf("�ʵ� �� üũ ���� : %d\n", map_check_signal);

	//========================================//
	//����ۿ� ������ HDC�� �׸���.(�̰͵� �������� ����)
	this->getBackBuffer()->render( hdc, 0, 0 );
	
}

void mainGame::pika_field_key_control()
{
	//�� �̵� ��Ʈ üũ�ؼ� ���ǰ� �ٲٱ�
	RECT temp;
	if (IntersectRect(&temp, &field_1->scene_check, &pika->main_Pika_rc))
	{
		field_1->scene_check_left = false;
	}

	//Ű�Է� �κ�
	//�κ��丮 ���� ���� ���� ��ī�� �����Ʈ ����
	if (Invent->tab_key_cnt % 2 == 0)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			//�浹 üũ
			tree_collide_pika = field_1->treeColliderCheck(pika->main_Pika_rc);
			tree_collide_pika_2 = field_2->treeColliderCheck(pika->main_Pika_rc);

			pika->leftPress = true;
			pika->pickaRender();//���ʹ���Ű�϶� �ִϸ��̼�
			pika->pika_isLeft = true;
			pika->main_Pika->setX(pika->main_Pika->getX() - 5.0f);

			pika->main_Pika_rc.left -= PIKA_SPEED;
			pika->main_Pika_rc.right -= PIKA_SPEED;
			if (pika->main_Pika_rc.left <= 0)
			{
				pika->main_Pika_rc.left += PIKA_SPEED;
				pika->main_Pika_rc.right += PIKA_SPEED;
			}
			//1�� �浹 üũ
			if (tree_collide_pika && map_check_signal == 1)
			{
				pika->main_Pika_rc.left += PIKA_COL_SPEED;
				pika->main_Pika_rc.right += PIKA_COL_SPEED;
			}
			//2�� �浹 üũ
			if (tree_collide_pika_2 && map_check_signal == 2)
			{
				pika->main_Pika_rc.left += (PIKA_COL_SPEED);
				pika->main_Pika_rc.right += (PIKA_COL_SPEED);
			}
			//3�� �浹 üũ
			field_3_pixel_check = field_3->field_3_pixel_Check(pika->main_Pika_rc,1);
			if (map_check_signal == 3 && field_3_pixel_check)
			{
				pika->main_Pika_rc.left += (PIKA_COL_SPEED);
				pika->main_Pika_rc.right += (PIKA_COL_SPEED);
			}
			//printf("%d", tree_collide_pika);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			tree_collide_pika = field_1->treeColliderCheck(pika->main_Pika_rc);
			tree_collide_pika_2 = field_2->treeColliderCheck(pika->main_Pika_rc);

			pika->rightPress = true;
			pika->pickaRender();//������ �����϶� �ִϸ��̼�
			pika->main_Pika_rc.left += PIKA_SPEED;
			pika->main_Pika_rc.right += PIKA_SPEED;
			if (pika->main_Pika_rc.right >= WINSIZEX)
			{
				pika->main_Pika_rc.left -= PIKA_SPEED;
				pika->main_Pika_rc.right -= PIKA_SPEED;
			}
			//1�� �浹 üũ
			if (tree_collide_pika && map_check_signal == 1)
			{
				pika->main_Pika_rc.left -= PIKA_COL_SPEED;
				pika->main_Pika_rc.right -= PIKA_COL_SPEED;
			}
			//2�� �浹 üũ
			if (tree_collide_pika_2 && map_check_signal == 2)
			{
				pika->main_Pika_rc.left -= (PIKA_COL_SPEED);
				pika->main_Pika_rc.right -= (PIKA_COL_SPEED);
			}
			//3�� �浹 üũ
			field_3_pixel_check = field_3->field_3_pixel_Check(pika->main_Pika_rc,2);
			if (map_check_signal == 3 && field_3_pixel_check)
			{
				pika->main_Pika_rc.left -= (PIKA_COL_SPEED);
				pika->main_Pika_rc.right -= (PIKA_COL_SPEED);
			}
			pika->pika_isLeft = false;
			pika->main_Pika->setX(pika->main_Pika->getX() + 5.0f);
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP)) //���� Ŀ�ǵ�
		{
			tree_collide_pika = field_1->treeColliderCheck(pika->main_Pika_rc);
			tree_collide_pika_2 = field_2->treeColliderCheck(pika->main_Pika_rc);

			pika->downPress = true;
			pika->pickaUpRender();
			pika->main_Pika_rc.top -= PIKA_SPEED;
			pika->main_Pika_rc.bottom -= PIKA_SPEED;
			if (pika->main_Pika_rc.top <= WINSIZEY / 2 - 20)
			{
				pika->main_Pika_rc.top += PIKA_SPEED;
				pika->main_Pika_rc.bottom += PIKA_SPEED;
			}
			//1�� �浹 üũ
			if (tree_collide_pika && map_check_signal == 1)
			{
				pika->main_Pika_rc.top += PIKA_COL_SPEED;
				pika->main_Pika_rc.bottom += PIKA_COL_SPEED;
			}
			//2�� �浹 üũ
			if (tree_collide_pika_2 && map_check_signal == 2)
			{
				pika->main_Pika_rc.top += (PIKA_COL_SPEED);
				pika->main_Pika_rc.bottom += (PIKA_COL_SPEED);
			}
			//3�� �� ��Ʈ�� �� �浹üũ ���� ����
			if (map_check_signal == 3 && field_3->silver_mountain_check && field_3->field_3_rc.bottom < 1073)
			{
				field_3->field_3_rc.top += SILVER_MOUNTAIN_SCROLL;
				field_3->field_3_rc.bottom += SILVER_MOUNTAIN_SCROLL;

				field_3->field_3_rc_msk.top += SILVER_MOUNTAIN_SCROLL;
				field_3->field_3_rc_msk.bottom += SILVER_MOUNTAIN_SCROLL;

				field_3->Boss_check_rc.top += SILVER_MOUNTAIN_SCROLL;
				field_3->Boss_check_rc.bottom += SILVER_MOUNTAIN_SCROLL;
			}
			//3�� �浹 üũ
			field_3_pixel_check = field_3->field_3_pixel_Check(pika->main_Pika_rc,3);
			if (map_check_signal == 3 && field_3_pixel_check)
			{
				pika->main_Pika_rc.top += (PIKA_COL_SPEED);
				pika->main_Pika_rc.bottom += (PIKA_COL_SPEED);
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))//�Ʒ��� Ŀ�ǵ�
		{
			tree_collide_pika = field_1->treeColliderCheck(pika->main_Pika_rc);
			tree_collide_pika_2 = field_2->treeColliderCheck(pika->main_Pika_rc);

			pika->main_Pika_rc.top += PIKA_SPEED;
			pika->main_Pika_rc.bottom += PIKA_SPEED;
			if (pika->main_Pika_rc.bottom >= WINSIZEY)
			{
				pika->main_Pika_rc.top -= PIKA_SPEED;
				pika->main_Pika_rc.bottom -= PIKA_SPEED;
			}
			//1�� �浹 üũ
			if (tree_collide_pika && map_check_signal == 1)
			{
				pika->main_Pika_rc.top -= (SILVER_MOUNTAIN_SCROLL);
				pika->main_Pika_rc.bottom -= (SILVER_MOUNTAIN_SCROLL);
			}
			//2�� �浹 üũ
			if (tree_collide_pika_2 && map_check_signal == 2)
			{
				pika->main_Pika_rc.top -= (PIKA_COL_SPEED);
				pika->main_Pika_rc.bottom -= (PIKA_COL_SPEED);
			}

			//3�� �� ��Ʈ�� �� �浹üũ ���� ����
			if (map_check_signal == 3 && field_3->silver_mountain_check && field_3->field_3_rc.bottom > 348)
			{
				field_3->field_3_rc.top -= SILVER_MOUNTAIN_SCROLL;
				field_3->field_3_rc.bottom -= SILVER_MOUNTAIN_SCROLL;

				field_3->field_3_rc_msk.top -= SILVER_MOUNTAIN_SCROLL;
				field_3->field_3_rc_msk.bottom -= SILVER_MOUNTAIN_SCROLL;

				field_3->Boss_check_rc.top -= SILVER_MOUNTAIN_SCROLL;
				field_3->Boss_check_rc.bottom -= SILVER_MOUNTAIN_SCROLL;

			}
			//3�� �浹 üũ
			field_3_pixel_check = field_3->field_3_pixel_Check(pika->main_Pika_rc,4);
			if (map_check_signal == 3 && field_3_pixel_check)
			{
				pika->main_Pika_rc.top -= (PIKA_COL_SPEED);
				pika->main_Pika_rc.bottom -= (PIKA_COL_SPEED);
			}
		}
	}
}

void mainGame::scene_position_initialize()
{
	//�� �Ѿ� ���ÿ� ��ġ �ʱ�ȭ �ϱ�
	//1->2 �������� �Ѿ ��
	if (field_1->scene_check_left && map_check_signal == 2 && pika_position_initialize_2 == false)
	{
		pika->main_Pika_rc = RectMakeCenter(WINSIZEX - 60, WINSIZEY - 130, 1560 / 10 / 4 * 0.8, 570 / 10 / 2 * 0.8);//���ΰ� ��Ʈ ��ġ �ʱ�ȭ
		pika_position_initialize_2 = true;
	}
	//2->1�������� �Ѿ ��
	if (!field_1->scene_check_left && map_check_signal == 1 && pika_position_initialize_1 == false)
	{
		//pika->main_Pika_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 60, 1560 / 10 / 4 * 0.8, 570 / 10 / 2 * 0.8);//���ΰ� ��Ʈ ��ġ �ʱ�ȭ

		pika->main_Pika_rc = RectMakeCenter(80, WINSIZEY - 80, 1560 / 10 / 4 * 0.8, 570 / 10 / 2 * 0.8);//���ΰ� ��Ʈ ��ġ �ʱ�ȭ

		pika_position_initialize_1 = true;
	}
	//1->3�������� �Ѿ �� 
	if (map_check_signal == 3 && pika_position_initialize_3 == false)
	{
		//pika->main_Pika_rc = RectMakeCenter(80, WINSIZEY - 80, 1560 / 10 / 4 * 0.8, 570 / 10 / 2 * 0.8);//���ΰ� ��Ʈ ��ġ �ʱ�ȭ
		pika->main_Pika_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 80, 1560 / 10 / 4 * 0.8, 570 / 10 / 2 * 0.8);//���ΰ� ��Ʈ ��ġ �ʱ�ȭ
		pika_position_initialize_3 = true;
	}
}


