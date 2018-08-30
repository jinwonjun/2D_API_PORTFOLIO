#pragma once
class Field_1
{
private:
	image * field_1;//시작 필드 이미지 생성용
	image * pika_move;
	image * comment;//말풍선 이미지 로딩

	int pika_move_count;
	int pika_move_index;
	int pika_move_frame_index;//로고 y축 프레임 조절용 인덱스
	int timer;

	image * fountain;
	int fountain_count;
	int fountain_index;
	int fountain_frame_index;//로고 y축 프레임 조절용 인덱스
	
public:
	Field_1();
	~Field_1();

	//===================변수 관련====================
	bool pika_comment_check;//피카츄 대사 하는거 체크 변수, 메인 렌더에서 이걸 키값으로 플레이어 표시
	RECT trees[40];//장애물 구조 넣어주자
	RECT scene_check;//씬전환 확인용 렉트
	bool scene_check_left = false;//씬전환 확인용 bool값
	int comment_time;//대사 치는거 시간 간격 조정
	int comment_index;//대사 글자 간격 인덱스값 조정

	RECT battle_start_check;//앞으로 전진한 렉트 선언해주고 배틀 씬으로 넘기자
	bool battle_start;//rect에 닿으면, battle 시작 클래스 호출, 기본 false값으로 초기화

	RECT field_1_to_3;//필드 1과 3 체크용 렉트
	bool field_1_to_3_check;//필드 1과 3 체크용 bool변수
	//===================함수 관련====================
	HRESULT init();
	//시작 필드를 호출해보자
	void render(HDC hdc);
	void pika_Motion_Render();
	void fountain_Render();
	bool treeColliderCheck(RECT PIKA_rc);//피카츄랑 장애물(나무)이랑 충돌체크 처리, 메인함수에 리턴값 넘겨줘야됨
};

