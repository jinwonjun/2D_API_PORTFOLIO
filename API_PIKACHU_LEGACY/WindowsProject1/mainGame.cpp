#include "stdafx.h"
#include "mainGame.h"

//2주 분량의 API 포트폴리오 나이스하게 만들기

mainGame::mainGame()
{
}

mainGame::~mainGame()
{
} 

HRESULT mainGame::init()
{
	gameNode::init();
	//오프닝 씬 동적선언 및 초기화
	open = new Game_Opening;
	open->init();
	//필드1 동적선언 및 초기화
	field_1 = new Field_1;
	field_1->init();
	//필드2 동적선언 및 초기화
	field_2 = new Field_2;
	field_2->init();
	//필드3 동적선언 및 초기화
	field_3 = new Silver_Mountain;
	field_3->init();
	field_3_pixel_check = false;

	//메인 캐릭터 동적 선언 및 초기화
	pika = new mainCharacter;
	pika->init();

	//npc 동적 선언 및 초기화
	DR_O = new npc_dr_o;
	DR_O->init();

	//피카츄 코멘터리 동적선언 및 초기화
	pika_comment = new Pika_Comment;
	pika_comment->init();

	//인벤토리 동적선언 및 초기화
	Invent = new Inventory;
	Invent->init();

	//전투 페이즈 동적 선언 및 초기화
	battle = new battle_scene;
	battle->init();
	//충돌 체크 bool값 초기화
	tree_collide_pika = false;
	tree_collide_pika_2 = false;
	//각 씬에 대한 조건값 초기화(1번 필드면 1, 2번 필드면 2, 이런식)
	map_check_signal = 0;
	//씬에 대한 피카츄 초기화 검사용 bool값 초기화
	pika_position_initialize_1 = false;
	pika_position_initialize_2 = false;
	pika_position_initialize_3 = false;

	return S_OK; // 함수가 성공적으로 돌아감을 의미함.
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
	//로고 그리기 업데이트
	open->Logo_Up_Render();
	open->Logo_down_Render();

	//각 씬에 따른 피카츄 위치 초기화
	scene_position_initialize();

	//필드 부분
	//필드1 렌더 함수 호출
	field_1->pika_Motion_Render();
	field_1->fountain_Render();
	//충돌처리 체크값 계속 받아옴
	tree_collide_pika = false;
	tree_collide_pika_2 = false;
	//필드2 렌더 함수 호출
	field_2->field_2_Render();
	//필드3 렌더 함수 호출
	//항시 초기화
	field_3_pixel_check = false;

	if (field_1->field_1_to_3_check)
	{
		field_3->field_3_Render();
		//field_3_pixel_check = field_3->field_3_pixel_Check(pika->main_Pika_rc);
		//필드3에서 보스와 충돌 체크 및 배틀 씬 호출
		if (field_3->bossColliderCheck(pika->main_Pika_rc))
		{
			battle->battle_scene_check = true;
			
			pika->main_Pika_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 80, 1560 / 10 / 4 * 0.8, 570 / 10 / 2 * 0.8);//주인공 렉트 위치 초기화
		}
	}

	//피카츄 코멘터리 애니매이션처리
	pika_comment->pika_Motion_Render();

	//NPC 컨트롤
	DR_O->DR_O_Render(pika->main_Pika_rc);

	//피카츄(플레이어)컨트롤 변수 기본값 초기화 및 렌더
	pika->leftPress = false;
	pika->rightPress = false;
	pika->downPress = false;
	pika->pickaDownRender();//피카츄 앞 모습, idle상태 그려주는 렌더 함수

	//인벤토리 렌더에 대한 조건값 주는 함수 호출
	Invent->tab_key_control();

	//배틀씬 호출
	if (battle->battle_scene_check)
	{
		battle->update();
	}

	//배틀이 아닌 통상 경우일때만 호출하도록 변경
	if (! battle->battle_scene_check)
	{
		//필드 상에서 키 입력 값을 main 함수에서 처리함.(캐릭터 컨트롤이라 메인 함수에서 처리.)
		pika_field_key_control();
	}
	
	//기본 게임 조작키, 아이템 습득 키 값도 이걸로 함.
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		//오프닝 화면에 스페이스바 키 입력후에, 설명화면으로 전환(한번만 해줘야됨)
		open->GameStartSignal = true;
	}
}

void mainGame::render(HDC hdc)
{
	//gameNode::render(hdc);
	//백버퍼에 뿌려줌(렌더에 걍 냅둠 건들지마)
	HDC memDC = this->getBackBuffer()->getMemDC();
	//흰색 빈 비트맵
	PatBlt( memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS );
	//========================================//
	//게임 시작 오프닝 출력
	open->render(memDC);
	//이제 기본 RPG를 만들어보자!!!
	if (open->GameStartSignal == false && open->timer >= 200)
	{
		//필드 그리기
		//field_1->render(memDC);
		// 필드를 넘어가보자!
		//field_1->scene_check_left 조건값 체크 부분은 하단의 pika_field_key_control(); 함수가 update()에서 계속 돌기 때문에 체크 가능함.
		if (field_1->scene_check_left)
		{
			map_check_signal = 2;
			field_1->scene_check = RectMake(WINSIZEX - 30, WINSIZEY - 130, 30, 30);
			field_2->render(memDC);

			//피카츄 위치 초기화용 시그널, 2맵에서 1시그널을 초기화
			pika_position_initialize_1 = false;

			DR_O->CollideSignal = false;//오박사랑 충돌체크 꺼놓기
			field_1->battle_start = false;//전투 시작 충돌체크 꺼놓기
			field_1->field_1_to_3_check = false;//1번씬에서 3번으로 넘어가는 충돌체크 끄기

			//피카츄 그리기, 휘웅이 멘트 나올땐 그리지 말자
			if (field_1->pika_comment_check && field_2->timer<100)//피카츄 대사 끝나면 피카츄 모습 그리기
			{
				pika->render(memDC);
			}
			if (field_2->timer >= 300 && field_2->CollideSignal)//피카츄 코멘트 호출
			{
				pika_comment->render(memDC, 3);
				//다 했으면 초기화
				if (field_2->timer == 899)
				{
					field_2->timer = 0;
					pika_comment->timer = 0;
					field_2->CollideSignal = false;
				}
			}
			//검사용 렉트 그리기
			//맵넘어가는 검사 렉트
			//RectangleMake(memDC, field_1->scene_check.left, field_1->scene_check.top, field_1->scene_check.right - field_1->scene_check.left, field_1->scene_check.bottom - field_1->scene_check.top);
			//피카츄 렉트
			//RectangleMake(memDC, pika->main_Pika_rc.left, pika->main_Pika_rc.top, pika->main_Pika_rc.right - pika->main_Pika_rc.left, pika->main_Pika_rc.bottom - pika->main_Pika_rc.top);
		}
		else
		{
			map_check_signal = 1; //맵 장면 값 할당(충돌 검사 조건 추가용도)

			field_1->scene_check = RectMake(0, WINSIZEY - 100, 30, 30);
			field_1->render(memDC);

			//피카츄 위치 초기화용 시그널, 1맵에서 2시그널을 초기화
			pika_position_initialize_2 = false;

			field_2->CollideSignal = false;//휘웅이랑 충돌 체크 꺼놓기

			//피카츄 그리기
			if (field_1->pika_comment_check)//피카츄 대사 끝나면 피카츄 모습 그리기
			{
				pika->render(memDC);
			}

			//필드 1에서만 오박사를 그려주자
			DR_O->render(memDC);
			if (DR_O->timer > 350)
			{
				pika_comment->render(memDC, 1);
				if (DR_O->timer == 500)
				{
					//전투씬 시작 전에 인덱스 및 타이머 초기화
					pika_comment->comment_index = 1;
					pika_comment->comment_time = 0;
				}
			}
			//3번 필드그리기
			if (field_1->field_1_to_3_check)
			{
				//필드 앞으로 전진하면 전투 씬으로 바꾸자
				//battle->battle_scene_check = true;
				map_check_signal = 3;
				DR_O->CollideSignal = false;//오박사랑 충돌체크 꺼놓기
				field_3->render(memDC);//필드 그려주기
				open->only_up_logo_render(memDC);//상단 로고만 그리기

				//3번 씬에서 1번 씬 전환 장판 체크용
				//field_1->field_1_to_3 = RectMake(170, WINSIZEY - 30, 60, 30);//필드 1과 3 체크용 렉트
				//RectangleMake(memDC, field_1->field_1_to_3.left, field_1->field_1_to_3.top, field_1->field_1_to_3.right - field_1->field_1_to_3.left, field_1->field_1_to_3.bottom - field_1->field_1_to_3.top);

				if (pika_position_initialize_3 && field_3->silver_mountain_check)//초기화 조건 걸기
				{
					pika->render(memDC);//피카츄 그리기
				}
			}
			//검사용 렉트 그리기
			//RectangleMake(memDC, field_1->scene_check.left, field_1->scene_check.top, field_1->scene_check.right - field_1->scene_check.left, field_1->scene_check.bottom - field_1->scene_check.top);
		}
	}

	//필드에서만 호출 해야되니깐 인벤토리 조건 걸어주자
	if (map_check_signal==1 || map_check_signal == 2 || map_check_signal == 3)
	{
		Invent->render(memDC);
	}
	//전투 페이즈로 이동
	if (battle->battle_scene_check)
	{
		map_check_signal = 0;
		battle->render(memDC);
		//전투방식 설명 및 피카츄 코멘터리
		if (battle->pikaHp <= 0 || battle->boss.bossHp <= 0)
		{
			//전투방식 설명할 코멘터리 알려주기, 코멘트 렌더 호출전에 변수 초기화
			pika_comment->render(memDC, 2);
			//초기화 및 재설정
			if (pika_comment->timer == 300)
			{
				battle->init();//코멘터리 끝나면 초기화시키기
				pika_comment->timer = 0;//타이머 초기화
				pika_position_initialize_1 = false;
				battle->battle_scene_check = false;
				//map_check_signal = 3;
				scene_position_initialize();//피카츄 위치 초기화
			}
		}
	}

	//printf("필드 맵 체크 변수 : %d\n", map_check_signal);

	//========================================//
	//백버퍼에 내용을 HDC에 그린다.(이것도 지우지마 제발)
	this->getBackBuffer()->render( hdc, 0, 0 );
	
}

void mainGame::pika_field_key_control()
{
	//맵 이동 렉트 체크해서 조건값 바꾸기
	RECT temp;
	if (IntersectRect(&temp, &field_1->scene_check, &pika->main_Pika_rc))
	{
		field_1->scene_check_left = false;
	}

	//키입력 부분
	//인벤토리 켜져 있을 때는 피카츄 무브먼트 끄기
	if (Invent->tab_key_cnt % 2 == 0)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			//충돌 체크
			tree_collide_pika = field_1->treeColliderCheck(pika->main_Pika_rc);
			tree_collide_pika_2 = field_2->treeColliderCheck(pika->main_Pika_rc);

			pika->leftPress = true;
			pika->pickaRender();//왼쪽방향키일때 애니매이션
			pika->pika_isLeft = true;
			pika->main_Pika->setX(pika->main_Pika->getX() - 5.0f);

			pika->main_Pika_rc.left -= PIKA_SPEED;
			pika->main_Pika_rc.right -= PIKA_SPEED;
			if (pika->main_Pika_rc.left <= 0)
			{
				pika->main_Pika_rc.left += PIKA_SPEED;
				pika->main_Pika_rc.right += PIKA_SPEED;
			}
			//1씬 충돌 체크
			if (tree_collide_pika && map_check_signal == 1)
			{
				pika->main_Pika_rc.left += PIKA_COL_SPEED;
				pika->main_Pika_rc.right += PIKA_COL_SPEED;
			}
			//2씬 충돌 체크
			if (tree_collide_pika_2 && map_check_signal == 2)
			{
				pika->main_Pika_rc.left += (PIKA_COL_SPEED);
				pika->main_Pika_rc.right += (PIKA_COL_SPEED);
			}
			//3씬 충돌 체크
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
			pika->pickaRender();//오른쪽 방향일때 애니매이션
			pika->main_Pika_rc.left += PIKA_SPEED;
			pika->main_Pika_rc.right += PIKA_SPEED;
			if (pika->main_Pika_rc.right >= WINSIZEX)
			{
				pika->main_Pika_rc.left -= PIKA_SPEED;
				pika->main_Pika_rc.right -= PIKA_SPEED;
			}
			//1씬 충돌 체크
			if (tree_collide_pika && map_check_signal == 1)
			{
				pika->main_Pika_rc.left -= PIKA_COL_SPEED;
				pika->main_Pika_rc.right -= PIKA_COL_SPEED;
			}
			//2씬 충돌 체크
			if (tree_collide_pika_2 && map_check_signal == 2)
			{
				pika->main_Pika_rc.left -= (PIKA_COL_SPEED);
				pika->main_Pika_rc.right -= (PIKA_COL_SPEED);
			}
			//3씬 충돌 체크
			field_3_pixel_check = field_3->field_3_pixel_Check(pika->main_Pika_rc,2);
			if (map_check_signal == 3 && field_3_pixel_check)
			{
				pika->main_Pika_rc.left -= (PIKA_COL_SPEED);
				pika->main_Pika_rc.right -= (PIKA_COL_SPEED);
			}
			pika->pika_isLeft = false;
			pika->main_Pika->setX(pika->main_Pika->getX() + 5.0f);
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP)) //위쪽 커맨드
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
			//1씬 충돌 체크
			if (tree_collide_pika && map_check_signal == 1)
			{
				pika->main_Pika_rc.top += PIKA_COL_SPEED;
				pika->main_Pika_rc.bottom += PIKA_COL_SPEED;
			}
			//2씬 충돌 체크
			if (tree_collide_pika_2 && map_check_signal == 2)
			{
				pika->main_Pika_rc.top += (PIKA_COL_SPEED);
				pika->main_Pika_rc.bottom += (PIKA_COL_SPEED);
			}
			//3씬 맵 컨트롤 및 충돌체크 방향 조정
			if (map_check_signal == 3 && field_3->silver_mountain_check && field_3->field_3_rc.bottom < 1073)
			{
				field_3->field_3_rc.top += SILVER_MOUNTAIN_SCROLL;
				field_3->field_3_rc.bottom += SILVER_MOUNTAIN_SCROLL;

				field_3->field_3_rc_msk.top += SILVER_MOUNTAIN_SCROLL;
				field_3->field_3_rc_msk.bottom += SILVER_MOUNTAIN_SCROLL;

				field_3->Boss_check_rc.top += SILVER_MOUNTAIN_SCROLL;
				field_3->Boss_check_rc.bottom += SILVER_MOUNTAIN_SCROLL;
			}
			//3씬 충돌 체크
			field_3_pixel_check = field_3->field_3_pixel_Check(pika->main_Pika_rc,3);
			if (map_check_signal == 3 && field_3_pixel_check)
			{
				pika->main_Pika_rc.top += (PIKA_COL_SPEED);
				pika->main_Pika_rc.bottom += (PIKA_COL_SPEED);
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))//아래쪽 커맨드
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
			//1씬 충돌 체크
			if (tree_collide_pika && map_check_signal == 1)
			{
				pika->main_Pika_rc.top -= (SILVER_MOUNTAIN_SCROLL);
				pika->main_Pika_rc.bottom -= (SILVER_MOUNTAIN_SCROLL);
			}
			//2씬 충돌 체크
			if (tree_collide_pika_2 && map_check_signal == 2)
			{
				pika->main_Pika_rc.top -= (PIKA_COL_SPEED);
				pika->main_Pika_rc.bottom -= (PIKA_COL_SPEED);
			}

			//3씬 맵 컨트롤 및 충돌체크 방향 조정
			if (map_check_signal == 3 && field_3->silver_mountain_check && field_3->field_3_rc.bottom > 348)
			{
				field_3->field_3_rc.top -= SILVER_MOUNTAIN_SCROLL;
				field_3->field_3_rc.bottom -= SILVER_MOUNTAIN_SCROLL;

				field_3->field_3_rc_msk.top -= SILVER_MOUNTAIN_SCROLL;
				field_3->field_3_rc_msk.bottom -= SILVER_MOUNTAIN_SCROLL;

				field_3->Boss_check_rc.top -= SILVER_MOUNTAIN_SCROLL;
				field_3->Boss_check_rc.bottom -= SILVER_MOUNTAIN_SCROLL;

			}
			//3씬 충돌 체크
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
	//씬 넘어 갈시에 위치 초기화 하기
	//1->2 번씬으로 넘어갈 때
	if (field_1->scene_check_left && map_check_signal == 2 && pika_position_initialize_2 == false)
	{
		pika->main_Pika_rc = RectMakeCenter(WINSIZEX - 60, WINSIZEY - 130, 1560 / 10 / 4 * 0.8, 570 / 10 / 2 * 0.8);//주인공 렉트 위치 초기화
		pika_position_initialize_2 = true;
	}
	//2->1번씬으로 넘어갈 때
	if (!field_1->scene_check_left && map_check_signal == 1 && pika_position_initialize_1 == false)
	{
		//pika->main_Pika_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 60, 1560 / 10 / 4 * 0.8, 570 / 10 / 2 * 0.8);//주인공 렉트 위치 초기화

		pika->main_Pika_rc = RectMakeCenter(80, WINSIZEY - 80, 1560 / 10 / 4 * 0.8, 570 / 10 / 2 * 0.8);//주인공 렉트 위치 초기화

		pika_position_initialize_1 = true;
	}
	//1->3번씬으로 넘어갈 때 
	if (map_check_signal == 3 && pika_position_initialize_3 == false)
	{
		//pika->main_Pika_rc = RectMakeCenter(80, WINSIZEY - 80, 1560 / 10 / 4 * 0.8, 570 / 10 / 2 * 0.8);//주인공 렉트 위치 초기화
		pika->main_Pika_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 80, 1560 / 10 / 4 * 0.8, 570 / 10 / 2 * 0.8);//주인공 렉트 위치 초기화
		pika_position_initialize_3 = true;
	}
}


