#include "stdafx.h"

battle_scene::battle_scene()
{
}


battle_scene::~battle_scene()
{
}

HRESULT battle_scene::init()
{
	invincible = false;

	//mainGame::pickaShotRender();

	m_bgImage = new image;
	m_bgImage->init("images_b/background.bmp", 400, 650);

	//������ �̰� ������
	m_apple = new image;
	m_apple->init("images_b/poketball.bmp", 50, 50, true, RGB(255, 0, 255));//255, 0, 255 ��������� �̰ɷ� �Ѱű���!! �ű��ϴ�
	m_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 100, 100);

	//�ǽ� ���� ����
	m_rockman = new image;
	//m_rockman->init("images/�ϸ�2.bmp", WINSIZEX / 2, WINSIZEY / 2, 1440, 300, 10, 2, true, RGB(255, 0, 255));//�ǿ����� �Ķ���ʹ� ������ ����Ÿ �����ų�
	m_rockman->init("images_b/poketball4.bmp", WINSIZEX / 2, WINSIZEY / 2, 200, 50, 4, 1, true, RGB(255, 0, 255));//�ǿ����� �Ķ���ʹ� ������ ����Ÿ �����ų�
																												//���� ���� �ʱ�ȭ
	m_isLeft = false;
	m_count = 0;
	m_index = 0;
	//���� ������� �ʱ�ȭ�κ�
	bossDeathCheck = false;
	boss.bossCheckL = false;
	boss.bossCheckR = false;
	boss.bossHp = BOSS_HP_MAX;//�ϴ� �ӽ÷� �س��� ���� ������ �ٲ��ֱ�!!!
	boss.bossPosition = RectMakeCenter(WINSIZEX / 2 + WINSIZEX, 55, 200, 115);//������� ��Ʈ ����
	boss.bossImage = new image;
	boss.bossImage->init("images_b/boss1.bmp", 200, 115, true, RGB(255, 0, 255));
	boss.hpRect = RectMake(WINSIZEX - 100, 0, 100, 15);//100x15¥�� ��Ʈ ��ġ �ʱ�ȭ
	for (int i = 0; i < 9; i++)
	{
		string str = "images_b/" + to_string(i) + ".bmp";
		boss.bossHp_image[i] = new image; //������ ����� �̹����� �־�����
		boss.bossHp_image[i]->init(str.c_str(), 100, 15, true, RGB(255, 0, 255));
	}


	//��ī�� ��Ʈ�� ũ�� 156x57
	//��ī�� �����Ʈ �׸���� �ʱ�ȭ,  ��ī���� ��Ʈ �κ��� ���� ������ �ʾ���! //��ġ�ʱ�ȭ //�¿� �̹��� �ϴ� 
	main_Pika = new image;
	main_Pika->init("images_b/picka.bmp", WINSIZEX / 2, WINSIZEY - 50, 1560 / 10, 570 / 10, 4, 2, true, RGB(255, 0, 255)); //��ġ�� �̹��� �ʱ�ȭ
	main_Pika_up = new image;
	main_Pika_up->init("images_b/picka_up.bmp", WINSIZEX / 2, WINSIZEY - 50, 300 * 0.6, 50 * 0.6, 6, 1, true, RGB(255, 0, 255));
	main_Pika_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 50, 1560 / 10, 570 / 10);//���ΰ� ��Ʈ ��ġ �ʱ�ȭ

	pikaHp = PIKA_HP_MAX;
	pika_isLeft = false;
	pika_count = 0;
	pika_index = 0;
	pika_up_count = 0;
	pika_up_index = 0;

	//��ī�� �̻��� ��� �̹��� ���̱� , �߻�ü ��Ʈ�� �ʱ�ȭ ���� �����
	pika_shot = new image;
	pika_shot->init("images_b/shot.bmp", WINSIZEX / 2, WINSIZEY - 50, 1316, 96, 14, 1, true, RGB(255, 0, 255));
	//pika  ��Ʈ �޾ƿ���
	pika_shot_index = 0;
	pika_shot_count = 0;
	pika_shot_rc.rc = RectMakeCenter((main_Pika_rc.left + main_Pika_rc.right) / 2, main_Pika_rc.top - pika_shot->getFrameHeight(), pika_shot->getFrameWidth(), pika_shot->getFrameHeight());//�⺻ �Ѿ��� ĳ������ �Ӹ� ���� �����ǰ� ����
	pika_shot_rc.deathCheck = false;//�ʱ�ȭ
	pika_shot_rc.touch = false;//�ʱ�ȭ
	bulletCheck = false;//�⺻ �̻��� üũ
	bulletCnt = 0;//�Ѿ��� 3�� �߻� �Ǹ� �ؿ��� Ʈ�簪 �ٻ���
	doubleEngine = false;//�ΰ� �߽��غ� üũ!
	doubleEngineLaunch = false;//�ΰ� �߽�!

	pika_hp_rc = RectMake(0, WINSIZEY - 15, 100, 15);//100x15¥�� ��Ʈ ��ġ �ʱ�ȭ
	pika_hp_image[9];
	for (int i = 0; i < 9; i++)
	{
		string str2 = "images_b/" + to_string(i) + ".bmp";
		pika_hp_image[i] = new image; //������ ����� �̹����� �־�����
		pika_hp_image[i]->init(str2.c_str(), 100, 15, true, RGB(255, 0, 255));
	}

	//��ī�� �ǰ݉����� �׸��� 
	pikaHit.touch = false;
	pikaHit.rc = RectMake(WINSIZEX / 2, WINSIZEY / 2, 16, 18);
	pikaHit.tagRect_image = new image;
	pikaHit.tagRect_image->init("images_b/bulletHit.bmp", WINSIZEX / 2, WINSIZEY / 2, 352, 18, 22, 1, true, RGB(255, 0, 255));
	pika_hit_count = 0;
	pika_hit_index = 0;
	pika_hit_check = false;

	//�ΰ� �κ� �ʱ�ȭ
	logo_count = 0;
	logo_index = 0;
	logo_frame_index = 0;
	//�Ǹ���
	//m_rockman->init("frame_0000.bmp", WINSIZEX / 2, WINSIZEY / 2, 460, 460, 1, 1, true, RGB(255, 0, 255));//�ǿ����� �Ķ���ʹ� ������ ����Ÿ �����ų�
	logo = new image;
	logo->init("images_b/logo_bmp2.bmp", WINSIZEX / 2, WINSIZEY / 2, 3009, 1239, 17, 7, true, RGB(255, 0, 255));
	//�ΰ� �ε��� �ʱ�ȭ ���Ѽ� �����ִ� �κ�. initRender�� ���ڸ��� �����ϱ� ������, -1�� �ʱ�ȭ�ϰ� ��������Ѵ�.
	logo->setFrameX(-1);
	logo->setFrameY(-1);

	//���� �̹��� �������� �׿� ����� �͵� �ʱ�ȭ�ϱ�
	exp[0].explosion_count = 0;
	exp[0].explosion_index = 0;
	exp[0].explosion_check = false;//true�� �ٲ�� �ִϸ��̼����� ����ϰ� ������
	exp[0].explosion_Image = new image;
	exp[0].explosion_Image->init("images_b/explosion1.bmp", WINSIZEX / 2, WINSIZEY / 2, 396 * 2, 32 * 2, 12, 1, true, RGB(255, 0, 255)); //�ϴ� �̹��� ����

	explosionPosition = RectMakeCenter(WINSIZEX * 2, WINSIZEY * 2, 396, 32); //���� ��ġ �ϴ� ���� ���հ����� �������ϰ� �ҷ�����
	explosionCheck = false;//������ üũ�κ�, �ϴ� �޽��� �ʱ�ȭ

						   //������� �������̶� �׿� ����� �͵� �ʱ�ȭ
	death_count = 0;
	death_index = 0;
	death.tagRect_image = new image;
	death.tagRect_image->init("images_b/death.bmp", WINSIZEX / 2, WINSIZEY / 2, 708, 118, 6, 1, true, RGB(255, 0, 255)); // 708 118 6 1

																													   //=============================1������ �׳� �������°� �ʱ�ȭ ���� �κ�=================================
	m_box_count = 0;
	m_box_index = 0;
	m_box2_count = 0;
	m_box2_index = 0;
	for (int i = 0; i < 2; i++) //��ֹ�1 ũ�⸦ �迭�� ���� ����
	{
		m_box[i].touch = false;
		m_box[i].tagRect_image = new image; // �������� ���Ϻ� �̹��� �Ⱦ��ֱ�
		m_box[i].tagRect_image->init("images_b/poketball5.bmp", WINSIZEX / 2, WINSIZEY / 2, 1040 * 0.5, 129 * 0.5, 8, 1, true, RGB(255, 0, 255));
		m_box[i].rc = RectMakeCenter(50 + i * 280, 50, 50, 50); //�ϴ� �̰� ���� ��ǥ�� ����� �޾ƾ���

		m_box2[i].tagRect_image = new image; // �������� ���Ϻ� �̹��� �Ⱦ��ֱ�
		m_box2[i].tagRect_image->init("images_b/poketball5.bmp", WINSIZEX / 2, WINSIZEY / 2, 1040 * 0.5, 129 * 0.5, 8, 1, true, RGB(255, 0, 255));
		m_box2[i].touch = false;
		m_box2[i].rc = RectMakeCenter(50 + i * 150, 0, 50, 50);
	}
	//========================================2������ ���� �κ� ============================================
	guideBullet[4];
	guide_count = 0;
	guide_index = 0;

	for (int i = 0; i < 4; i++)
	{
		guideBullet[i].deathCheck = false;
		guideBullet[i].tagRect_image = new image;
		guideBullet[i].tagRect_image->init("images_b/poketball.bmp", 50, 50, true, RGB(255, 0, 255));
		guideBullet[i].touch = false;
		guideBullet[i].rc = RectMake(0, 0, 50, 50);//��Ʈ �ʱ�ȭ
	}
	//======================================���� ���� ��� �κ� =============================================
	angleCheck = false;
	_cannon.angle = PI / 2;//������ ������!
	_cannon.cannon = 80.0f;
	_cannon.center.x = WINSIZEX / 2;
	_cannon.center.y = 0;

	memset(_bullet, 0, sizeof(_bullet));

	for (int i = 0; i < BULLETMAX; i++) //���ư��� �ִϸ��̼� �������ϱ�!!
	{
		_bullet[i].speed = 3.0f;
		_bullet[i].fire = false;
		_bullet[i].radius = 10.0f;
		_bullet[i].touch = false;
		_bullet[i].rc = RectMakeCenter(_bullet[i].x, _bullet[i].y, 20, 20);
		_bullet[i].bulletImage = new image;
		_bullet[i].bulletImage->init("images_b/poketball4.bmp", WINSIZEX / 2, WINSIZEY / 2, 80, 20, 4, 1, true, RGB(255, 0, 255));
	}
	//==========================����� Ű�Է� �ʱ�ȭ �κ� ==============================
	leftPress = false;
	rightPress = false;
	invincible = false;

	battle_scene_check = false;//�⺻�� false�� �ٲ�

	return S_OK;
}

void battle_scene::release()
{
	SAFE_DELETE(m_bgImage);
	SAFE_DELETE(m_rockman);
}

void battle_scene::update()
{
	leftPress = false;
	rightPress = false;
	//battle_scene::update();
	bulletRender();//���� ������ ��� �Լ�
	logoRender();//�ΰ� �׸��� ���� �Լ�
	pickaUpRender();//��ī�� ������ ����, idle���� �׷��ִ� ���� �Լ�
	pickaShotRender();//��ī�� �߽� �Ҷ� �׷��ִ� �Լ�
	normalRotateRender();//���Ϻ� �����°� �������°� �׷��ִ� �Լ�
	deathRender();//���� ��� �ϴ� ����غ���
	pickaHitRender();//��ī�� �ǰ� ��� �ϴ� ����غ���

	m_rockrc = m_rockman->getBoundingBox(); //�̹����� rc�� ��������

	if (boss.bossHp <= BOSS_HP_MAX * 0.9)
	{
		addBulletMove();

		if (boss.bossHp <= BOSS_HP_MAX * 0.6)
		{
			//========================���� 2������ ���� �̻��� �κ�==================================================
			//���� �̻��� 1 �����
			//�÷��̾ ����´�!!!
			guideCalMove();
			addBulletMove2();
			if (boss.bossHp <= BOSS_HP_MAX * 0.3)
			{
				//======================���� 3������ ���� ���� ����� �κ�==============================================
				if (_cannon.angle <= 3.0f && angleCheck == false)
				{
					bulletFire();
					_cannon.angle -= 0.1f;
					if (_cannon.angle >= 3.0f)
					{
						angleCheck = true;
					}
				}
				if (angleCheck && _bullet[10].fire)
				{
					bulletFire();
					_cannon.angle -= 0.1f;
				}
				bulletMove();
				_cannon.cannonEnd.x = cosf(_cannon.angle) * _cannon.cannon + _cannon.center.x;
				_cannon.cannonEnd.y = -sinf(_cannon.angle) * _cannon.cannon + _cannon.center.y;
				//=================================2������ ���ѹݺ� ��Ű�� ========================================== 	
				if (_bullet[BULLETMAX - 1].fire)
				{
					for (int i = 0; i < BULLETMAX; i++)
					{
						if (_bullet[i].y >= WINSIZEY)
						{
							_bullet[i].fire = false;
						}
						if (_bullet[i].y <= 0)
						{
							_bullet[i].fire = false;
						}
						if (_bullet[i].x <= 0)
						{
							_bullet[i].fire = false;
						}
						if (_bullet[i].x >= WINSIZEX)
						{
							_bullet[i].fire = false;
						}

					}
				}
			}
		}
	}
	//======================================����� Ŀ�ǵ� �κ�===================================================
	//0x5A <-- zŰ
	//0x58 <-- xŰ
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) //���� Ŀ�ǵ�
	{
		leftPress = true;
		pickaRender();//���ʹ���Ű�϶� �ִϸ��̼�
		m_rc.left -= 5.0f;
		m_rc.right -= 5.0f;

		m_isLeft = true;
		m_rockman->setX(m_rockman->getX() - 5.0f);

		pika_isLeft = true;
		main_Pika->setX(main_Pika->getX() - 5.0f);

		main_Pika_rc.left -= 5.0f;
		main_Pika_rc.right -= 5.0f;
		if (main_Pika_rc.left <= 0)
		{
			main_Pika_rc.left += 5.0f;
			main_Pika_rc.right += 5.0f;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))//������ Ŀ�ǵ�
	{
		rightPress = true;
		pickaRender();//������ �����϶� �ִϸ��̼�
		main_Pika_rc.left += 5.0f;
		main_Pika_rc.right += 5.0f;
		if (main_Pika_rc.right >= WINSIZEX + 115)
		{
			main_Pika_rc.left -= 5.0f;
			main_Pika_rc.right -= 5.0f;
		}
		m_rc.left += 5.0f;
		m_rc.right += 5.0f;

		m_isLeft = false;
		m_rockman->setX(m_rockman->getX() + 5.0f);

		pika_isLeft = false;
		main_Pika->setX(main_Pika->getX() + 5.0f);
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP)) //���� Ŀ�ǵ�
	{
		main_Pika_rc.top -= 5.0f;
		main_Pika_rc.bottom -= 5.0f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))//�Ʒ��� Ŀ�ǵ�
	{
		main_Pika_rc.top += 5.0f;
		main_Pika_rc.bottom += 5.0f;
		if (main_Pika_rc.bottom >= WINSIZEY + 20)
		{
			main_Pika_rc.top -= 5.0f;
			main_Pika_rc.bottom -= 5.0f;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_SPACE))
	{
		bulletCheck = true;
	}
	if (bulletCheck == false)//�߻��� ������ ���� ��ǥ�� �غ��ϱ�
	{
		pika_shot_rc.rc.top = main_Pika_rc.top - pika_shot->getFrameHeight();
		pika_shot_rc.rc.bottom = main_Pika_rc.top;
		pika_shot_rc.rc.left = main_Pika_rc.left - pika_shot->getFrameWidth() / 2 + 20;
		pika_shot_rc.rc.right = main_Pika_rc.left + pika_shot->getFrameWidth() / 2 - 20; //pika_shot->getFrameWidth()
	}//��ǥ�� �����ϱ�!!!
	if (bulletCheck)
	{
		pika_shot_rc.rc.top -= 30; //�����̴� �ӵ�
		pika_shot_rc.rc.bottom -= 30;

		if (pika_shot_rc.rc.top <= 0 || explosionCheck)
		{
			//�ڴ��������� �������ġ �ľ����ֱ�
			pika_shot_rc.rc.top = main_Pika_rc.top - pika_shot->getFrameHeight();
			pika_shot_rc.rc.bottom = main_Pika_rc.top;
			pika_shot_rc.rc.left = main_Pika_rc.left - pika_shot->getFrameWidth() / 2 + 20;
			pika_shot_rc.rc.right = main_Pika_rc.left + pika_shot->getFrameWidth() / 2 - 20; //pika_shot->getFrameWidth()
			bulletCheck = false;
			bulletCnt++;
			if (bulletCnt == 3)
			{
				doubleEngine = true;//3�� �����Ǹ� �غ� �Ϸ�!
				bulletCnt = 0;//�Ѿ� ī��Ʈ �ʱ�ȭ
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown(0x5A))//�̻��� �ΰ� �߽�!!! �Ϲ� �̻����� 3�� �򶧸��� ���� �ְԲ� �غ���
	{
		if (doubleEngine)
		{
			doubleEngineLaunch = true;
		}
		invincible = true;
	}
	//==========================������� �����Ʈ �κ�==========================================
	if (boss.bossCheckL == false && boss.bossCheckR == false) //������� ���� �̵�
	{
		boss.bossPosition.left -= 2;
		boss.bossPosition.right -= 2;
		if (boss.bossPosition.left <= 10)
		{
			boss.bossCheckL = true;
		}
	}
	if (boss.bossCheckL == true && boss.bossCheckR == false) //������� ���������� �̵�
	{
		boss.bossPosition.left += 2;
		boss.bossPosition.right += 2;
		if (boss.bossPosition.right >= 390)
		{
			boss.bossCheckR = false;
			boss.bossCheckL = false;

		}
	}
	//======================================������� �ǰݽ� �ִϸ��̼� ȣ�� �� �浹 üũ===================================================
	RECT temp;//�ǰݽ� ȣ�⿡ ���� �ӽð� �����
	if (IntersectRect(&temp, &boss.bossPosition, &pika_shot_rc.rc))
	{
		explosionPosition.left = temp.left + 30;
		explosionPosition.right = temp.right + 30;//�浹���� �ÿ� ��ǥ �Ѱ��ֱ�
		explosionPosition.top = temp.top;
		explosionPosition.bottom = temp.bottom;
		explosionV.push_back(explosionPosition);
		//explosionPosition = temp;
		explosionCheck = true;
		boss.bossHp -= 3;
	}
	//======================================��ī�� �ǰݽ� �ִϸ��̼� ȣ�� �� �浹 üũ===================================================
	RECT temp2;//ū���Ϻ� �������°� �ӽ� ���� ��Ʈ 
	for (int i = 0; i < 3; i++)//ū ���Ϻ� �������°� (���� ���̵� 1������� �� ����)
	{
		if (IntersectRect(&temp2, &main_Pika_rc, &m_box[i].rc))
		{
			if (!invincible)
			{
				pikaHp -= 1;
				m_box[i].touch = true;
			}
		}
		if (IntersectRect(&temp2, &main_Pika_rc, &m_box2[i].rc))
		{
			pikaHp -= 1;
			m_box2[i].touch = true;
		}
	}
	RECT temp3;//���� �̻��� �浹 �κ� �ӽú���
	for (int i = 0; i < 4; i++)
	{
		if (IntersectRect(&temp3, &main_Pika_rc, &guideBullet[i].rc))
		{
			pikaHp -= 1;
			guideBullet[i].touch = true;
		}
	}
}
void battle_scene::logoRender()
{
	logo_count++;
	//logo->setFrameY(logo_frame_index);//�ϴ� 0 ������
	if (logo_count % 3 == 0)
	{
		logo_count = 0;
		int frameX = (logo->getFrameX() + 1) % 17;
		logo->setFrameX(frameX);

		if (frameX == 0)
		{
			logo->setFrameY((logo->getFrameY() + 1) % 7);
		}
	}
}
//��ī�� �����Ʈ �κ�
void battle_scene::pickaRender()
{
	if (pika_isLeft)
	{
		pika_count++;
		main_Pika->setFrameY(1);//����¥�� �׸��̴ϱ� y�࿡ ���� ���� �̵�������
		if (pika_count % 5 == 0)
		{
			pika_count = 0;
			pika_index--;
			if (pika_index < 0)
			{
				pika_index = 4;
			}
			main_Pika->setFrameX(pika_index);
		}
	}
	else
	{
		pika_count++;
		main_Pika->setFrameY(0);
		if (pika_count % 5 == 0)
		{
			pika_count = 0;
			pika_index++;
			if (pika_index >3)
			{
				pika_index = 0;
			}
			main_Pika->setFrameX(pika_index);
		}
	}
}
void battle_scene::pickaUpRender()
{
	pika_up_count++;
	main_Pika_up->setFrameY(0);
	if (pika_up_count % 5 == 0)
	{
		pika_up_count = 0;
		pika_up_index++;
		if (pika_up_index >5)
		{
			pika_up_index = 0;
		}
		main_Pika_up->setFrameX(pika_up_index);
	}
}
//��ī�� �߻�ü ������
void battle_scene::pickaShotRender()
{
	pika_shot_count++;
	pika_shot->setFrameY(0);
	if (pika_shot_count % 5 == 0)
	{
		pika_shot_count = 0;
		pika_shot_index++;
		if (pika_shot_index >14)
		{
			pika_shot_index = 0;
		}
		pika_shot->setFrameX(pika_shot_index);
	}
}
//��ī�� �ǰ݉����� �ִϸ��̼� �Լ�
void battle_scene::pickaHitRender()
{
	pika_hit_count++;
	pikaHit.tagRect_image->setFrameY(0);
	if (pika_hit_count % 5 == 0)
	{
		pika_hit_count = 0;
		pika_hit_index++;
		if (pika_hit_index >22)
		{
			pika_hit_index = 0;
		}
		pikaHit.tagRect_image->setFrameX(pika_hit_index);
	}
}
//���� ��� ������ �ִϸ��̼����� �غ��ô�
void battle_scene::deathRender()
{
	death_count++;
	death.tagRect_image->setFrameY(0);
	if (death_count % 20 == 0)
	{
		death_count = 0;
		death_index++;
		if (death_index >5)
		{
			death_index = 0;
		}
		death.tagRect_image->setFrameX(death_index);
	}
}
//���� �������� �ΰ� ���߱���ü�� �ε����� �Ķ���ͷ� ����ϴ°ɷ� ���� 0�� ��¾��� �߉�
void battle_scene::explosionRender()
{
	exp[0].explosion_count++;
	exp[0].explosion_Image->setFrameY(0);
	if (exp[0].explosion_count % 3 == 0)
	{
		exp[0].explosion_count = 0;
		exp[0].explosion_index++;
		if (exp[0].explosion_index >11)
		{
			exp[0].explosion_index = 0;
		}
		exp[0].explosion_Image->setFrameX(exp[0].explosion_index);
	}
}
//���� ��� ������ ���ֱ�
void battle_scene::bulletRender()
{
	bullet_count++;

	for (int i = 0; i < BULLETMAX; i++) //���ư��� �ִϸ��̼� �������ϱ�!!
	{
		_bullet[i].bulletImage->setFrameY(0);
	}
	if (bullet_count % 10 == 0)
	{
		bullet_count = 0;
		bullet_index++;
		if (bullet_index >3)
		{
			bullet_index = 0;
		}
		for (int i = 0; i < BULLETMAX; i++) //���ư��� �ִϸ��̼� �������ϱ�!!
		{
			_bullet[i].bulletImage->setFrameX(bullet_index);
		}
	}
}
//��Ư�� ������ ������
void battle_scene::addBulletMove()
{
	//======================���� 3������ ���� ���� ����� �κ�==============================================
	if (_cannon.angle <= 3.0f && angleCheck == false)
	{
		bulletFire();
		_cannon.angle -= 0.5f;
		if (_cannon.angle >= 3.0f)
		{
			angleCheck = true;
		}
	}
	if (angleCheck && _bullet[10].fire)
	{
		bulletFire();
		_cannon.angle -= 0.1f;
	}
	bulletMove();
	_cannon.cannonEnd.x = cosf(_cannon.angle) * _cannon.cannon + _cannon.center.x;
	_cannon.cannonEnd.y = -sinf(_cannon.angle) * _cannon.cannon + _cannon.center.y;
	//=================================2������ ���ѹݺ� ��Ű�� ========================================== 	
	if (_bullet[BULLETMAX - 1].fire)
	{
		for (int i = 0; i < BULLETMAX; i++)
		{
			if (_bullet[i].y >= WINSIZEY)
			{
				_bullet[i].fire = false;
			}
			if (_bullet[i].y <= 0)
			{
				_bullet[i].fire = false;
			}
			if (_bullet[i].x <= 0)
			{
				_bullet[i].fire = false;
			}
			if (_bullet[i].x >= WINSIZEX)
			{
				_bullet[i].fire = false;
			}

		}
	}
}
void battle_scene::addBulletMove2()
{
	if (_cannon.angle <= 3.0f && angleCheck == false)
	{
		bulletFire();
		_cannon.angle -= 0.3f;
		if (_cannon.angle >= 3.0f)
		{
			angleCheck = true;
		}
	}
	if (angleCheck && _bullet[10].fire)
	{
		bulletFire();
		_cannon.angle -= 0.1f;
	}
	bulletMove();
	_cannon.cannonEnd.x = cosf(_cannon.angle) * _cannon.cannon + _cannon.center.x;
	_cannon.cannonEnd.y = -sinf(_cannon.angle) * _cannon.cannon + _cannon.center.y;
	//=================================2������ ���ѹݺ� ��Ű�� ========================================== 	
	if (_bullet[BULLETMAX - 1].fire)
	{
		for (int i = 0; i < BULLETMAX; i++)
		{
			if (_bullet[i].y >= WINSIZEY)
			{
				_bullet[i].fire = false;
			}
			if (_bullet[i].y <= 0)
			{
				_bullet[i].fire = false;
			}
			if (_bullet[i].x <= 0)
			{
				_bullet[i].fire = false;
			}
			if (_bullet[i].x >= WINSIZEX)
			{
				_bullet[i].fire = false;
			}

		}
	}
}
//���Ϻ� �׳� ������ �⺻ �𵨷� ����
void battle_scene::normalRotateRender()
{
	m_box_count++;
	//m_box2_count++;
	for (int i = 0; i < 2; i++) //���ư��� �ִϸ��̼� �������ϱ�!!
	{
		m_box[i].tagRect_image->setFrameY(0);
	}
	if (m_box_count % 10 == 0)
	{
		m_box_count = 0;
		m_box_index++;
		if (m_box_index >7)
		{
			m_box_index = 0;
		}
		for (int i = 0; i < 2; i++) //���ư��� �ִϸ��̼� �������ϱ�!!
		{
			m_box[i].tagRect_image->setFrameX(m_box_index);
		}
	}
	if (m_box2_count % 10 == 0)
	{
		m_box2_count = 0;
		m_box2_index++;
		if (m_box2_index >7)
		{
			m_box2_index = 0;
		}
		for (int i = 0; i < 2; i++) //���ư��� �ִϸ��̼� �������ϱ�!!
		{
			m_box2[i].tagRect_image->setFrameX(m_box2_index);
		}
	}
}
//2������ �����κ� ��� + �̵� �Լ�
void battle_scene::guideCalMove()
{
	for (int i = 0; i < 4; i++)
	{
		int angleCal = guideBullet[i].rc.left - main_Pika_rc.left;
		if (angleCal == 0)
		{
			angleCal = 1;
		}
		int cals = 3 * cos(atan((guideBullet[i].rc.top - main_Pika_rc.top) / (angleCal)));
		if (guideBullet[i].rc.left - main_Pika_rc.left >= 0)//���ʱ������� ������ ���󰡰Բ�
		{
			guideBullet[i].rc.left -= cals;
			guideBullet[i].rc.right -= cals;
		}
		if (guideBullet[i].rc.left - main_Pika_rc.left < 0)//������ �������� �������� ���󰡰Բ�
		{
			guideBullet[i].rc.left += cals;
			guideBullet[i].rc.right += cals;
		}
		guideBullet[i].rc.bottom += 3;
		guideBullet[i].rc.top += 3;
		if (guideBullet[3].rc.top >= WINSIZEY + 50)//�ٴڿ� ������
		{
			for (int i = 0; i < 4; i++)
			{
				if (i <= 1)guideBullet[i].rc = RectMakeCenter(i * 200 + 100, WINSIZEY / 2 - 100 - 50, 50, 50);//���� �̻��� ����� �����
				if (i >= 2)guideBullet[i].rc = RectMakeCenter((i - 2)* WINSIZEX, WINSIZEY / 2 - 50, 50, 50);//���� �̻��� ����� �����
			}
		}
	}
}
//�ڵ����� ���� ���� ��Բ� �����ϱ�
void battle_scene::bulletFire()
{
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (_bullet[i].fire == false)
		{
			_bullet[i].fire = true;
			_bullet[i].x = cosf(_cannon.angle) * (_cannon.cannon + 10) + _cannon.center.x;
			_bullet[i].y = -sinf(_cannon.angle) * (_cannon.cannon + 10) + _cannon.center.y;
			_bullet[i].angle = _cannon.angle;
			break;
		}
	}
}
//���� ���� �����°� �����
void battle_scene::bulletMove()
{
	float currentX;
	float currentY;
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (_bullet[i].fire)
		{
			currentX = (cosf(_bullet[i].angle) * (_bullet[i].speed));
			currentY = (-sinf(_bullet[i].angle) * (_bullet[i].speed));
			_bullet[i].x += (currentX);
			_bullet[i].y += (currentY);
			_bullet[i].rc = RectMake(_bullet[i].x, _bullet[i].y, 20, 20);
		}
		RECT temp4;//���� �Ŀ��� ���� �ӽ����� ��Ʈ 
		if (IntersectRect(&temp4, &main_Pika_rc, &_bullet[i].rc))
		{
			_bullet[i].touch = true;
			pikaHp -= 1;
		}
	}
}
void battle_scene::render(HDC hdc)
{
	m_bgImage->render(hdc);
	//������ ������
	//m_apple->render( memDC, m_rc.left, m_rc.top);
	//�ΰ� �׸���, �ٴڿ� ����� �Ǵϱ� �� �տ� �׷���
	logo->frameRender(hdc, logo->getX(), logo->getY(), logo->getFrameX(), logo->getFrameY());
	//m_rockman->frameRender(memDC,m_rockman->getX() - 120 ,m_rockman->getY()+ 120,m_rockman->getFrameX(),m_rockman->getFrameY());

	//�������̴°� 
	if (bossDeathCheck)
	{
		//�״°� ������
		death.tagRect_image->frameRender(hdc, death.rc.left - 100, death.rc.top);
		//if (death.tagRect_image->getFrameX() == 0)//ó���� ��� ã��
		//{
		//	string gameEnd = TEXT("���ӳ����� �Ӹ�");
		//	string gameMenu = TEXT("�������?");
		//	KillTimer(_hWnd, 1);
		//	if (MessageBox(_hWnd, gameEnd.c_str(), gameMenu.c_str(), MB_YESNO | MB_ICONHAND) == IDYES)
		//	{
		//		battle_scene::init();
		//	}
		//	else
		//	{
		//		exit(0);
		//	}
		//}
	}
	//���� ���� ������ �κ�
	if (boss.bossHp <= BOSS_HP_MAX * 0.9 && !bossDeathCheck)
	{
		//1������ �����°�
		for (int i = 0; i < 2; i++) //���ư��� �ִϸ��̼� �������ϱ�!!
		{
			m_box[i].tagRect_image->frameRender(hdc, m_box[i].rc.left, m_box[i].rc.top + 100, m_box[i].tagRect_image->getFrameX(), m_box[i].tagRect_image->getFrameY());
			m_box2[i].tagRect_image->frameRender(hdc, m_box2[i].rc.left + 65, m_box2[i].rc.top + 220, m_box2[i].tagRect_image->getFrameX(), m_box2[i].tagRect_image->getFrameY());
		}
		if (boss.bossHp <= BOSS_HP_MAX * 0.6)
		{
			//2������ ���� �κ�
			for (int i = 0; i < 4; i++)
			{
				//RectangleMake(memDC, guideBullet[i].rc.left, guideBullet[i].rc.top, guideBullet[i].rc.right - guideBullet[i].rc.left, guideBullet[i].rc.bottom - guideBullet[i].rc.top);
				guideBullet[i].tagRect_image->render(hdc, guideBullet[i].rc.left, guideBullet[i].rc.top);
			}
			if (boss.bossHp <= BOSS_HP_MAX * 0.3)
			{
				//3������ �ߵ��ÿ� ��������. �ϴ��� �ϼ�,
				for (int i = 0; i < BULLETMAX; i++)
				{
					if (!_bullet[i].fire)continue;
					_bullet[i].bulletImage->frameRender(hdc, _bullet[i].x, _bullet[i].y, _bullet[i].bulletImage->getFrameX(), _bullet[i].bulletImage->getFrameY());

				}
				if (boss.bossHp <= 0)
				{
					death.rc.left = (boss.bossPosition.left + boss.bossPosition.right) / 2;
					death.rc.right = death.rc.left + death.tagRect_image->getFrameWidth();
					death.rc.top = (boss.bossPosition.top + boss.bossPosition.bottom) / 2;
					death.rc.bottom = boss.bossPosition.top + death.tagRect_image->getFrameHeight();
					bossDeathCheck = true;
				}
			}
		}
	}
	//����ĳ���� ��ī�� �׸��� , �����̴ϱ� �� ����������
	//main_Pika->frameRender(memDC, main_Pika->getX(), main_Pika->getY(), main_Pika->getFrameX(), main_Pika->getFrameY());
	//�⺻����
	if (!leftPress && !rightPress)
	{
		main_Pika_up->frameRender(hdc, main_Pika_rc.left, main_Pika_rc.top, main_Pika_up->getFrameX(), main_Pika_up->getFrameY());
	}

	if (leftPress || rightPress)
	{
		main_Pika->frameRender(hdc, main_Pika_rc.left, main_Pika_rc.top, main_Pika->getFrameX(), main_Pika->getFrameY());
	}
	if (bulletCheck)
	{
		//�߻�ü �׷��ֱ� �����̽��� ����������
		pika_shot->frameRender(hdc, pika_shot_rc.rc.left, pika_shot_rc.rc.top, pika_shot->getFrameX(), pika_shot->getFrameY());
		//�߻�ü �׷��ִ°� üũ�� ��Ʈ�ڽ�
		//RectangleMake(memDC, pika_shot_rc.rc.left, pika_shot_rc.rc.top, pika_shot_rc.rc.right - pika_shot_rc.rc.left, pika_shot_rc.rc.bottom - pika_shot_rc.rc.top);
	}

	//������� ������ �κ�
	if (!bossDeathCheck)
	{
		boss.bossImage->render(hdc, boss.bossPosition.left, boss.bossPosition.top);
		//RectangleMake(memDC, boss.bossPosition.left, boss.bossPosition.top, boss.bossPosition.right - boss.bossPosition.left, boss.bossPosition.bottom - boss.bossPosition.top);//
	}

	//���� ����Ʈ �׷��ֱ�
	if (explosionCheck)
	{
		exp[0].explosion_Image->frameRender(hdc, explosionPosition.left, explosionPosition.top, exp[0].explosion_Image->getFrameX(), exp[0].explosion_Image->getFrameY());
		battle_scene::explosionRender();//���� ��º� ȣ���ϱ�
		if (exp[0].explosion_Image->getFrameX() == 11)
		{
			explosionCheck = false;//�ʱ�ȭ
		}
	}

	//������� ���� �׷��ֱ�
	float tempmodule = (float) (((double)(boss.bossHp / (double)(BOSS_HP_MAX)) * 100));

	//printf("%f\n", tempmodule);

	//100~ 87,86~74,73~61,60~48,47~35,34~22,21~9,19~0
	if (tempmodule == 100)
	{
		boss.bossHp_image[8]->render(hdc, boss.hpRect.left, boss.hpRect.top);
	}
	if (tempmodule < 100 && tempmodule >= 87)
	{
		boss.bossHp_image[7]->render(hdc, boss.hpRect.left, boss.hpRect.top);
	}
	if (tempmodule < 87 && tempmodule >= 74)
	{
		boss.bossHp_image[6]->render(hdc, boss.hpRect.left, boss.hpRect.top);
	}
	if (tempmodule < 74 && tempmodule >= 61)
	{
		boss.bossHp_image[5]->render(hdc, boss.hpRect.left, boss.hpRect.top);
	}
	if (tempmodule < 61 && tempmodule >= 48)
	{
		boss.bossHp_image[4]->render(hdc, boss.hpRect.left, boss.hpRect.top);
	}
	if (tempmodule < 48 && tempmodule >= 35)
	{
		boss.bossHp_image[3]->render(hdc, boss.hpRect.left, boss.hpRect.top);
	}
	if (tempmodule < 35 && tempmodule >= 22)
	{
		boss.bossHp_image[2]->render(hdc, boss.hpRect.left, boss.hpRect.top);
	}
	if (tempmodule < 22 && tempmodule >= 10)
	{
		boss.bossHp_image[1]->render(hdc, boss.hpRect.left, boss.hpRect.top);
	}
	if(tempmodule <10)
	{
		boss.bossHp_image[0]->render(hdc, boss.hpRect.left, boss.hpRect.top);
	}

	//��ī�� ���� �׷��ֱ�
	float tempmodule2 = (float)(((double)(pikaHp / (double)(PIKA_HP_MAX)) * 100));

	//100~ 87,86~74,73~61,60~48,47~35,34~22,21~9,19~0
	if (tempmodule2 == 100)
	{
		pika_hp_image[8]->render(hdc, pika_hp_rc.left, pika_hp_rc.top);
	}
	if (tempmodule2 < 100 && tempmodule2 >= 87)
	{
		pika_hp_image[7]->render(hdc, pika_hp_rc.left, pika_hp_rc.top);
	}
	if (tempmodule2 < 87 && tempmodule2 >= 74)
	{
		pika_hp_image[6]->render(hdc, pika_hp_rc.left, pika_hp_rc.top);
	}
	if (tempmodule2 < 74 && tempmodule2 >= 61)
	{
		pika_hp_image[5]->render(hdc, pika_hp_rc.left, pika_hp_rc.top);
	}
	if (tempmodule2 < 61 && tempmodule2 >= 48)
	{
		pika_hp_image[4]->render(hdc, pika_hp_rc.left, pika_hp_rc.top);
	}
	if (tempmodule2 < 48 && tempmodule2 >= 35)
	{
		pika_hp_image[3]->render(hdc, pika_hp_rc.left, pika_hp_rc.top);
	}
	if (tempmodule2 < 35 && tempmodule2 >= 22)
	{
		pika_hp_image[2]->render(hdc, pika_hp_rc.left, pika_hp_rc.top);
	}
	if (tempmodule2 < 22 && tempmodule2 >= 10)
	{
		pika_hp_image[1]->render(hdc, pika_hp_rc.left, pika_hp_rc.top);
	}
	if (tempmodule2 <10)
	{
		pika_hp_image[0]->render(hdc, pika_hp_rc.left, pika_hp_rc.top);
	}

	//3������ �׽�Ʈ��
	//3������ �ߵ��ÿ� ��������. �ϴ��� �ϼ�,
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!_bullet[i].fire)continue;
		_bullet[i].bulletImage->frameRender(hdc, _bullet[i].x, _bullet[i].y, _bullet[i].bulletImage->getFrameX(), _bullet[i].bulletImage->getFrameY());

	}

	//�״°� ������
	//death.tagRect_image->frameRender(memDC,death.rc.left, death.rc.top);
	//��ī�� �ǰ� ������
	//pikaHit.tagRect_image->frameRender(memDC, pikaHit.rc.left, pikaHit.rc.top);

	//��ī��� ���� ���� üũ Ȯ�ο�
	//string str1 = to_string(pikaHp);
	//TextOut(hdc, 0, 0, str1.c_str(), strlen(str1.c_str()));

	//string str2 = to_string(boss.bossHp);
	//TextOut(hdc, 0, 15, str2.c_str(), strlen(str2.c_str()));
}
