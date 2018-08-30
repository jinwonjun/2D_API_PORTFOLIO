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

	//구리다 이거 지우자
	m_apple = new image;
	m_apple->init("images_b/poketball.bmp", 50, 50, true, RGB(255, 0, 255));//255, 0, 255 지울색상을 이걸로 한거구나!! 신기하다
	m_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 100, 100);

	//실습 내용 시작
	m_rockman = new image;
	//m_rockman->init("images/록맨2.bmp", WINSIZEX / 2, WINSIZEY / 2, 1440, 300, 10, 2, true, RGB(255, 0, 255));//맨오른쪽 파라미터는 마지막 마젠타 날릴거냐
	m_rockman->init("images_b/poketball4.bmp", WINSIZEX / 2, WINSIZEY / 2, 200, 50, 4, 1, true, RGB(255, 0, 255));//맨오른쪽 파라미터는 마지막 마젠타 날릴거냐
																												//예제 변수 초기화
	m_isLeft = false;
	m_count = 0;
	m_index = 0;
	//보스 지우새끼 초기화부분
	bossDeathCheck = false;
	boss.bossCheckL = false;
	boss.bossCheckR = false;
	boss.bossHp = BOSS_HP_MAX;//일단 임시로 해놓고 로직 돌릴땐 바꿔주기!!!
	boss.bossPosition = RectMakeCenter(WINSIZEX / 2 + WINSIZEX, 55, 200, 115);//지우새끼 렉트 삽입
	boss.bossImage = new image;
	boss.bossImage->init("images_b/boss1.bmp", 200, 115, true, RGB(255, 0, 255));
	boss.hpRect = RectMake(WINSIZEX - 100, 0, 100, 15);//100x15짜리 렉트 위치 초기화
	for (int i = 0; i < 9; i++)
	{
		string str = "images_b/" + to_string(i) + ".bmp";
		boss.bossHp_image[i] = new image; //피통을 출력할 이미지를 넣어주자
		boss.bossHp_image[i]->init(str.c_str(), 100, 15, true, RGB(255, 0, 255));
	}


	//피카츄 비트맵 크기 156x57
	//피카츄 무브먼트 그리기와 초기화,  피카츄의 렉트 부분은 아직 해주지 않았음! //위치초기화 //좌우 이미지 일단 
	main_Pika = new image;
	main_Pika->init("images_b/picka.bmp", WINSIZEX / 2, WINSIZEY - 50, 1560 / 10, 570 / 10, 4, 2, true, RGB(255, 0, 255)); //위치와 이미지 초기화
	main_Pika_up = new image;
	main_Pika_up->init("images_b/picka_up.bmp", WINSIZEX / 2, WINSIZEY - 50, 300 * 0.6, 50 * 0.6, 6, 1, true, RGB(255, 0, 255));
	main_Pika_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 50, 1560 / 10, 570 / 10);//주인공 렉트 위치 초기화

	pikaHp = PIKA_HP_MAX;
	pika_isLeft = false;
	pika_count = 0;
	pika_index = 0;
	pika_up_count = 0;
	pika_up_index = 0;

	//피카츄 미사일 쏘는 이미지 붙이기 , 발사체 렉트와 초기화 변수 선언부
	pika_shot = new image;
	pika_shot->init("images_b/shot.bmp", WINSIZEX / 2, WINSIZEY - 50, 1316, 96, 14, 1, true, RGB(255, 0, 255));
	//pika  렉트 받아오기
	pika_shot_index = 0;
	pika_shot_count = 0;
	pika_shot_rc.rc = RectMakeCenter((main_Pika_rc.left + main_Pika_rc.right) / 2, main_Pika_rc.top - pika_shot->getFrameHeight(), pika_shot->getFrameWidth(), pika_shot->getFrameHeight());//기본 총알은 캐릭터의 머리 위로 생성되게 구현
	pika_shot_rc.deathCheck = false;//초기화
	pika_shot_rc.touch = false;//초기화
	bulletCheck = false;//기본 미사일 체크
	bulletCnt = 0;//총알이 3번 발사 되면 밑에놈 트루값 줄생각
	doubleEngine = false;//두개 발싸준비 체크!
	doubleEngineLaunch = false;//두개 발싸!

	pika_hp_rc = RectMake(0, WINSIZEY - 15, 100, 15);//100x15짜리 렉트 위치 초기화
	pika_hp_image[9];
	for (int i = 0; i < 9; i++)
	{
		string str2 = "images_b/" + to_string(i) + ".bmp";
		pika_hp_image[i] = new image; //피통을 출력할 이미지를 넣어주자
		pika_hp_image[i]->init(str2.c_str(), 100, 15, true, RGB(255, 0, 255));
	}

	//피카츄가 피격됬을때 그리기 
	pikaHit.touch = false;
	pikaHit.rc = RectMake(WINSIZEX / 2, WINSIZEY / 2, 16, 18);
	pikaHit.tagRect_image = new image;
	pikaHit.tagRect_image->init("images_b/bulletHit.bmp", WINSIZEX / 2, WINSIZEY / 2, 352, 18, 22, 1, true, RGB(255, 0, 255));
	pika_hit_count = 0;
	pika_hit_index = 0;
	pika_hit_check = false;

	//로고 부분 초기화
	logo_count = 0;
	logo_index = 0;
	logo_frame_index = 0;
	//실마리
	//m_rockman->init("frame_0000.bmp", WINSIZEX / 2, WINSIZEY / 2, 460, 460, 1, 1, true, RGB(255, 0, 255));//맨오른쪽 파라미터는 마지막 마젠타 날릴거냐
	logo = new image;
	logo->init("images_b/logo_bmp2.bmp", WINSIZEX / 2, WINSIZEY / 2, 3009, 1239, 17, 7, true, RGB(255, 0, 255));
	//로고 인덱스 초기화 시켜서 물려주는 부분. initRender가 들어가자마자 증가하기 때문에, -1로 초기화하고 돌려줘야한다.
	logo->setFrameX(-1);
	logo->setFrameY(-1);

	//폭발 이미지 렌더링과 그외 잡다한 것들 초기화하기
	exp[0].explosion_count = 0;
	exp[0].explosion_index = 0;
	exp[0].explosion_check = false;//true로 바뀌면 애니매이션으로 출력하게 해주자
	exp[0].explosion_Image = new image;
	exp[0].explosion_Image->init("images_b/explosion1.bmp", WINSIZEX / 2, WINSIZEY / 2, 396 * 2, 32 * 2, 12, 1, true, RGB(255, 0, 255)); //일단 이미지 삽입

	explosionPosition = RectMakeCenter(WINSIZEX * 2, WINSIZEY * 2, 396, 32); //폭발 위치 일단 선언 에먼곳에다 생성만하고 불러오자
	explosionCheck = false;//맞을때 체크부분, 일단 펄스로 초기화

						   //죽음모션 렌더링이랑 그외 잡다한 것들 초기화
	death_count = 0;
	death_index = 0;
	death.tagRect_image = new image;
	death.tagRect_image->init("images_b/death.bmp", WINSIZEX / 2, WINSIZEY / 2, 708, 118, 6, 1, true, RGB(255, 0, 255)); // 708 118 6 1

																													   //=============================1페이즈 그냥 떨어지는거 초기화 해줄 부분=================================
	m_box_count = 0;
	m_box_index = 0;
	m_box2_count = 0;
	m_box2_index = 0;
	for (int i = 0; i < 2; i++) //장애물1 크기를 배열에 때려 넣지
	{
		m_box[i].touch = false;
		m_box[i].tagRect_image = new image; // 떨어지는 포켓볼 이미지 꽂아주기
		m_box[i].tagRect_image->init("images_b/poketball5.bmp", WINSIZEX / 2, WINSIZEY / 2, 1040 * 0.5, 129 * 0.5, 8, 1, true, RGB(255, 0, 255));
		m_box[i].rc = RectMakeCenter(50 + i * 280, 50, 50, 50); //일단 이거 보류 좌표값 제대로 받아야함

		m_box2[i].tagRect_image = new image; // 떨어지는 포켓볼 이미지 꽂아주기
		m_box2[i].tagRect_image->init("images_b/poketball5.bmp", WINSIZEX / 2, WINSIZEY / 2, 1040 * 0.5, 129 * 0.5, 8, 1, true, RGB(255, 0, 255));
		m_box2[i].touch = false;
		m_box2[i].rc = RectMakeCenter(50 + i * 150, 0, 50, 50);
	}
	//========================================2페이즈 유도 부분 ============================================
	guideBullet[4];
	guide_count = 0;
	guide_index = 0;

	for (int i = 0; i < 4; i++)
	{
		guideBullet[i].deathCheck = false;
		guideBullet[i].tagRect_image = new image;
		guideBullet[i].tagRect_image->init("images_b/poketball.bmp", 50, 50, true, RGB(255, 0, 255));
		guideBullet[i].touch = false;
		guideBullet[i].rc = RectMake(0, 0, 50, 50);//렉트 초기화
	}
	//======================================원형 파형 출력 부분 =============================================
	angleCheck = false;
	_cannon.angle = PI / 2;//최적의 각도다!
	_cannon.cannon = 80.0f;
	_cannon.center.x = WINSIZEX / 2;
	_cannon.center.y = 0;

	memset(_bullet, 0, sizeof(_bullet));

	for (int i = 0; i < BULLETMAX; i++) //돌아가는 애니매이션 렌더링하기!!
	{
		_bullet[i].speed = 3.0f;
		_bullet[i].fire = false;
		_bullet[i].radius = 10.0f;
		_bullet[i].touch = false;
		_bullet[i].rc = RectMakeCenter(_bullet[i].x, _bullet[i].y, 20, 20);
		_bullet[i].bulletImage = new image;
		_bullet[i].bulletImage->init("images_b/poketball4.bmp", WINSIZEX / 2, WINSIZEY / 2, 80, 20, 4, 1, true, RGB(255, 0, 255));
	}
	//==========================사용자 키입력 초기화 부분 ==============================
	leftPress = false;
	rightPress = false;
	invincible = false;

	battle_scene_check = false;//기본값 false로 바꿈

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
	bulletRender();//파형 프레임 출력 함수
	logoRender();//로고 그리기 렌더 함수
	pickaUpRender();//피카츄 앞으로 전진, idle상태 그려주는 렌더 함수
	pickaShotRender();//피카츄 발싸 할때 그려주는 함수
	normalRotateRender();//포켓볼 돌리는거 떨어지는거 그려주는 함수
	deathRender();//죽음 모션 일단 출력해보기
	pickaHitRender();//피카츄 피격 모션 일단 출력해보기

	m_rockrc = m_rockman->getBoundingBox(); //이미지의 rc값 가져오기

	if (boss.bossHp <= BOSS_HP_MAX * 0.9)
	{
		addBulletMove();

		if (boss.bossHp <= BOSS_HP_MAX * 0.6)
		{
			//========================보스 2페이즈 유도 미사일 부분==================================================
			//유도 미사일 1 만들기
			//플레이어를 따라온다!!!
			guideCalMove();
			addBulletMove2();
			if (boss.bossHp <= BOSS_HP_MAX * 0.3)
			{
				//======================보스 3페이즈 원형 파형 만드는 부분==============================================
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
				//=================================2페이즈 무한반복 시키기 ========================================== 	
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
	//======================================사용자 커맨드 부분===================================================
	//0x5A <-- z키
	//0x58 <-- x키
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) //왼쪽 커맨드
	{
		leftPress = true;
		pickaRender();//왼쪽방향키일때 애니매이션
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
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))//오른쪽 커맨드
	{
		rightPress = true;
		pickaRender();//오른쪽 방향일때 애니매이션
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
	if (KEYMANAGER->isStayKeyDown(VK_UP)) //위쪽 커맨드
	{
		main_Pika_rc.top -= 5.0f;
		main_Pika_rc.bottom -= 5.0f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))//아래쪽 커맨드
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
	if (bulletCheck == false)//발생할 시점에 대한 좌표값 준비하기
	{
		pika_shot_rc.rc.top = main_Pika_rc.top - pika_shot->getFrameHeight();
		pika_shot_rc.rc.bottom = main_Pika_rc.top;
		pika_shot_rc.rc.left = main_Pika_rc.left - pika_shot->getFrameWidth() / 2 + 20;
		pika_shot_rc.rc.right = main_Pika_rc.left + pika_shot->getFrameWidth() / 2 - 20; //pika_shot->getFrameWidth()
	}//좌표값 수정하기!!!
	if (bulletCheck)
	{
		pika_shot_rc.rc.top -= 30; //움직이는 속도
		pika_shot_rc.rc.bottom -= 30;

		if (pika_shot_rc.rc.top <= 0 || explosionCheck)
		{
			//꾹눌렀을때도 재생성위치 파악해주기
			pika_shot_rc.rc.top = main_Pika_rc.top - pika_shot->getFrameHeight();
			pika_shot_rc.rc.bottom = main_Pika_rc.top;
			pika_shot_rc.rc.left = main_Pika_rc.left - pika_shot->getFrameWidth() / 2 + 20;
			pika_shot_rc.rc.right = main_Pika_rc.left + pika_shot->getFrameWidth() / 2 - 20; //pika_shot->getFrameWidth()
			bulletCheck = false;
			bulletCnt++;
			if (bulletCnt == 3)
			{
				doubleEngine = true;//3개 누적되면 준비 완료!
				bulletCnt = 0;//총알 카운트 초기화
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown(0x5A))//미사일 두개 발싸!!! 일반 미사일이 3번 쏠때마다 쓸수 있게끔 해보자
	{
		if (doubleEngine)
		{
			doubleEngineLaunch = true;
		}
		invincible = true;
	}
	//==========================지우새끼 무브먼트 부분==========================================
	if (boss.bossCheckL == false && boss.bossCheckR == false) //지우새끼 왼쪽 이동
	{
		boss.bossPosition.left -= 2;
		boss.bossPosition.right -= 2;
		if (boss.bossPosition.left <= 10)
		{
			boss.bossCheckL = true;
		}
	}
	if (boss.bossCheckL == true && boss.bossCheckR == false) //지우새끼 오른쪽으로 이동
	{
		boss.bossPosition.left += 2;
		boss.bossPosition.right += 2;
		if (boss.bossPosition.right >= 390)
		{
			boss.bossCheckR = false;
			boss.bossCheckL = false;

		}
	}
	//======================================지우새끼 피격시 애니매이션 호출 및 충돌 체크===================================================
	RECT temp;//피격시 호출에 대한 임시값 저장용
	if (IntersectRect(&temp, &boss.bossPosition, &pika_shot_rc.rc))
	{
		explosionPosition.left = temp.left + 30;
		explosionPosition.right = temp.right + 30;//충돌했을 시에 좌표 넘겨주기
		explosionPosition.top = temp.top;
		explosionPosition.bottom = temp.bottom;
		explosionV.push_back(explosionPosition);
		//explosionPosition = temp;
		explosionCheck = true;
		boss.bossHp -= 3;
	}
	//======================================피카츄 피격시 애니매이션 호출 및 충돌 체크===================================================
	RECT temp2;//큰포켓볼 떨어지는거 임시 저장 렉트 
	for (int i = 0; i < 3; i++)//큰 포켓볼 떨어지는거 (보스 레이드 1페이즈로 쓸 생각)
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
	RECT temp3;//유도 미사일 충돌 부분 임시변수
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
	//logo->setFrameY(logo_frame_index);//일단 0 해줬지
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
//피카츄 무브먼트 부분
void battle_scene::pickaRender()
{
	if (pika_isLeft)
	{
		pika_count++;
		main_Pika->setFrameY(1);//두줄짜리 그림이니깐 y축에 대한 열을 이동시켜줌
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
//피카츄 발사체 렌더링
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
//피카츄 피격됬을때 애니메이션 함수
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
//죽음 모션 렌더링 애니매이션으로 해봅시다
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
//폭발 여러개로 두고 폭발구조체의 인덱스를 파라미터로 사용하는걸로 하자 0번 출력아주 잘됌
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
//파형 모양 렌더링 해주기
void battle_scene::bulletRender()
{
	bullet_count++;

	for (int i = 0; i < BULLETMAX; i++) //돌아가는 애니매이션 렌더링하기!!
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
		for (int i = 0; i < BULLETMAX; i++) //돌아가는 애니매이션 렌더링하기!!
		{
			_bullet[i].bulletImage->setFrameX(bullet_index);
		}
	}
}
//독특한 파형을 만들어보자
void battle_scene::addBulletMove()
{
	//======================보스 3페이즈 원형 파형 만드는 부분==============================================
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
	//=================================2페이즈 무한반복 시키기 ========================================== 	
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
	//=================================2페이즈 무한반복 시키기 ========================================== 	
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
//포켓볼 그냥 돌려서 기본 모델로 쓰자
void battle_scene::normalRotateRender()
{
	m_box_count++;
	//m_box2_count++;
	for (int i = 0; i < 2; i++) //돌아가는 애니매이션 렌더링하기!!
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
		for (int i = 0; i < 2; i++) //돌아가는 애니매이션 렌더링하기!!
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
		for (int i = 0; i < 2; i++) //돌아가는 애니매이션 렌더링하기!!
		{
			m_box2[i].tagRect_image->setFrameX(m_box2_index);
		}
	}
}
//2페이즈 유도부분 계산 + 이동 함수
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
		if (guideBullet[i].rc.left - main_Pika_rc.left >= 0)//왼쪽기준으로 왼쪽을 따라가게끔
		{
			guideBullet[i].rc.left -= cals;
			guideBullet[i].rc.right -= cals;
		}
		if (guideBullet[i].rc.left - main_Pika_rc.left < 0)//오른쪽 기준으로 오른쪽을 따라가게끔
		{
			guideBullet[i].rc.left += cals;
			guideBullet[i].rc.right += cals;
		}
		guideBullet[i].rc.bottom += 3;
		guideBullet[i].rc.top += 3;
		if (guideBullet[3].rc.top >= WINSIZEY + 50)//바닥에 닿으면
		{
			for (int i = 0; i < 4; i++)
			{
				if (i <= 1)guideBullet[i].rc = RectMakeCenter(i * 200 + 100, WINSIZEY / 2 - 100 - 50, 50, 50);//유도 미사일 만들기 재생성
				if (i >= 2)guideBullet[i].rc = RectMakeCenter((i - 2)* WINSIZEX, WINSIZEY / 2 - 50, 50, 50);//유도 미사일 만들기 재생성
			}
		}
	}
}
//자동으로 원형 파형 쏘게끔 연산하기
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
//원형 파형 돌리는거 연산부
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
		RECT temp4;//원형 파원에 대해 임시저장 렉트 
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
	//연습용 렌더링
	//m_apple->render( memDC, m_rc.left, m_rc.top);
	//로고 그리기, 바닥에 깔려야 되니깐 맨 앞에 그려줌
	logo->frameRender(hdc, logo->getX(), logo->getY(), logo->getFrameX(), logo->getFrameY());
	//m_rockman->frameRender(memDC,m_rockman->getX() - 120 ,m_rockman->getY()+ 120,m_rockman->getFrameX(),m_rockman->getFrameY());

	//보스죽이는거 
	if (bossDeathCheck)
	{
		//죽는거 렌더링
		death.tagRect_image->frameRender(hdc, death.rc.left - 100, death.rc.top);
		//if (death.tagRect_image->getFrameX() == 0)//처리할 방법 찾기
		//{
		//	string gameEnd = TEXT("게임끝났엉 임마");
		//	string gameMenu = TEXT("리겜허실?");
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
	//보스 패턴 렌더링 부분
	if (boss.bossHp <= BOSS_HP_MAX * 0.9 && !bossDeathCheck)
	{
		//1페이즈 돌리는거
		for (int i = 0; i < 2; i++) //돌아가는 애니매이션 렌더링하기!!
		{
			m_box[i].tagRect_image->frameRender(hdc, m_box[i].rc.left, m_box[i].rc.top + 100, m_box[i].tagRect_image->getFrameX(), m_box[i].tagRect_image->getFrameY());
			m_box2[i].tagRect_image->frameRender(hdc, m_box2[i].rc.left + 65, m_box2[i].rc.top + 220, m_box2[i].tagRect_image->getFrameX(), m_box2[i].tagRect_image->getFrameY());
		}
		if (boss.bossHp <= BOSS_HP_MAX * 0.6)
		{
			//2페이즈 유도 부분
			for (int i = 0; i < 4; i++)
			{
				//RectangleMake(memDC, guideBullet[i].rc.left, guideBullet[i].rc.top, guideBullet[i].rc.right - guideBullet[i].rc.left, guideBullet[i].rc.bottom - guideBullet[i].rc.top);
				guideBullet[i].tagRect_image->render(hdc, guideBullet[i].rc.left, guideBullet[i].rc.top);
			}
			if (boss.bossHp <= BOSS_HP_MAX * 0.3)
			{
				//3페이즈 발동시에 켜져야함. 일단은 완성,
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
	//메인캐릭터 피카츄 그리기 , 메인이니깐 맨 마지막으로
	//main_Pika->frameRender(memDC, main_Pika->getX(), main_Pika->getY(), main_Pika->getFrameX(), main_Pika->getFrameY());
	//기본상태
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
		//발사체 그려주기 스페이스바 누를때마다
		pika_shot->frameRender(hdc, pika_shot_rc.rc.left, pika_shot_rc.rc.top, pika_shot->getFrameX(), pika_shot->getFrameY());
		//발사체 그려주는거 체크용 히트박스
		//RectangleMake(memDC, pika_shot_rc.rc.left, pika_shot_rc.rc.top, pika_shot_rc.rc.right - pika_shot_rc.rc.left, pika_shot_rc.rc.bottom - pika_shot_rc.rc.top);
	}

	//지우새끼 렌더링 부분
	if (!bossDeathCheck)
	{
		boss.bossImage->render(hdc, boss.bossPosition.left, boss.bossPosition.top);
		//RectangleMake(memDC, boss.bossPosition.left, boss.bossPosition.top, boss.bossPosition.right - boss.bossPosition.left, boss.bossPosition.bottom - boss.bossPosition.top);//
	}

	//폭발 이펙트 그려주기
	if (explosionCheck)
	{
		exp[0].explosion_Image->frameRender(hdc, explosionPosition.left, explosionPosition.top, exp[0].explosion_Image->getFrameX(), exp[0].explosion_Image->getFrameY());
		battle_scene::explosionRender();//폭발 출력부 호출하기
		if (exp[0].explosion_Image->getFrameX() == 11)
		{
			explosionCheck = false;//초기화
		}
	}

	//지우새끼 피통 그려주기
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

	//피카츄 피통 그려주기
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

	//3페이즈 테스트용
	//3페이즈 발동시에 켜져야함. 일단은 완성,
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!_bullet[i].fire)continue;
		_bullet[i].bulletImage->frameRender(hdc, _bullet[i].x, _bullet[i].y, _bullet[i].bulletImage->getFrameX(), _bullet[i].bulletImage->getFrameY());

	}

	//죽는거 렌더링
	//death.tagRect_image->frameRender(memDC,death.rc.left, death.rc.top);
	//피카츄 피격 렌더링
	//pikaHit.tagRect_image->frameRender(memDC, pikaHit.rc.left, pikaHit.rc.top);

	//피카츄와 지우 피통 체크 확인용
	//string str1 = to_string(pikaHp);
	//TextOut(hdc, 0, 0, str1.c_str(), strlen(str1.c_str()));

	//string str2 = to_string(boss.bossHp);
	//TextOut(hdc, 0, 15, str2.c_str(), strlen(str2.c_str()));
}
