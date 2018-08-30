#pragma once

//사용자 환경(전투씬을 제외하고, 탭 키를 누르면 호출 하도록 하자.)

class Inventory
{
private:
	image * inven;//인벤토리 이미지 불러오기
	image * arrow;//화살표 방향 불러오기
	RECT arrow_rc;//인벤토리 아이템 컨트롤 용 렉트 값 선언
public:
	Inventory();
	~Inventory();

	//===================변수 관련====================
	bool tab_key_check;//기본 false로 초기화 하고, true 일때만 보여주기
	int tab_key_cnt;//기본 0으로 초기화 해주고, 홀 수 번째 일때만 출력해주기

	//===================함수 관련====================
	HRESULT init();
	//인벤토리 이미지를 호출해보자
	void render(HDC hdc);
	void tab_key_control();//키값 판별을 여기서 해주자
};

