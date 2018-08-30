#pragma once
class Game_Opening
{
private:
	//============== UI 관련 변수들=================
	//로고 부분 인덱스와 카운트
	//상단바에 표시될 로고 그리기
	image * up_logo;
	int logo_count;
	int logo_index;
	int logo_frame_index;//로고 y축 프레임 조절용 인덱스
	//하단바에 표시될 로고 그리기
	image * down_logo;
	int logo_down_count;
	int logo_down_index;
	int logo_down_frame_index;//로고 y축 프레임 조절용 인덱스

	//test image
	//잠만보 이미지선언!
	image * test;

public:
	Game_Opening();
	~Game_Opening();
	//===================변수 관련====================
	//게임 시작 화면(잠만보)
	bool GameStartSignal;
	int timer;//글자 찍어주기용 타이머
	int comment_time;//대사 치는거 시간 간격 조정
	int comment_index;//대사 글자 간격 인덱스값 조정
	//===================함수 관련====================
	HRESULT init();
	void Logo_Up_Render();
	void Logo_down_Render();
	void render(HDC hdc);
	void only_up_logo_render(HDC hdc);
};

