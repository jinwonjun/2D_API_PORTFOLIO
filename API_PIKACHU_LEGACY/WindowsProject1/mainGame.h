#pragma once
#include"gameNode.h"

/*
1. image * 타입 선언하기
2. int m_count;//록맨 프레임 돌릴 카운트 변수
	int m_index;//프레임 이미지 인덱스
	bool m_isLeft; //방향체크
3. init 부분 이미지 타입 new 로 생성
4. m_rockman->init("images/록맨2.bmp", WINSIZEX / 2, WINSIZEY / 2, 1440, 300, 10, 2, true, RGB(255, 0, 255));//맨오른쪽 파라미터는 마지막 마젠타 날릴거냐
5. 
*/
class mainGame :  public gameNode
{

private:
//==============시스템 관련 변수들==============


	//메인캐릭터(피카츄)동적 선언
	mainCharacter *pika;
	//게임 오프닝 동적선언
	Game_Opening *open;
	
	//========= 필드 동적 선언================
	//필드_1 동적선언
	Field_1 * field_1;
	//필드_2 동적선언
	Field_2 * field_2;
	//필드_3 동적선언
	Silver_Mountain * field_3;


	//========= 인벤토리 동적 선언============
	Inventory * Invent;


	//========= NPC 동적 선언=================
	npc_dr_o *DR_O;

	//=== 피카츄 코멘터리 모션 동적 선언======
	Pika_Comment *pika_comment;

	//======== 전투 페이즈 동적 선언==========
	battle_scene * battle;

public:
	mainGame();
	~mainGame();
	//===========변수 관련 부분================
	bool tree_collide_pika;//피카츄랑 나무랑 장애물 체크용(1번필드)
	bool tree_collide_pika_2;//피카츄랑 나무랑 장애물 체크용(2번필드)
	int map_check_signal;//몇번 맵인지 체크해보자
	bool pika_position_initialize_1;//피카츄 장면 넘어갈 시에 위치 초기화 체크용
	bool pika_position_initialize_2;//피카츄 장면 넘어갈 시에 위치 초기화 체크용
	bool pika_position_initialize_3;
	bool field_3_pixel_check;
	//===========함수 관련 부분================
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void pika_field_key_control();//필드 상에서의 피카츄 키보드 컨트롤
	void scene_position_initialize();//각 필드에 대한 피카츄 위치 초기화를 따로 빼주자

};

