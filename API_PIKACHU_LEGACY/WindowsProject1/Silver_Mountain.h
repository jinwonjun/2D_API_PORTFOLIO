#pragma once
class Silver_Mountain
{
private:
	image * field_3_img;
	image * field_3_msk;//충돌 체크 넣어줄 마스킹 이미지 만들기
public:
	Silver_Mountain();
	~Silver_Mountain();
	//===================변수 관련====================
	bool silver_mountain_check;//최초 한번만 씬연출용 초기화 해주자
	RECT field_3_rc;//필드 충돌 체크 렉트
	RECT Boss_check_rc;//지우 충돌 체크 렉트
	RECT field_3_rc_msk;//마스킹이미지 렉트
	//===================함수 관련====================
	HRESULT init();
	void render(HDC hdc);
	//왼쪽 필드를 호출해보자
	void field_3_Render();
	//피카츄랑 충돌 체크
	bool bossColliderCheck(RECT PIKA_rc);//피카츄랑 충돌체크 처리, 메인함수에 리턴값 넘겨줘야됨
	bool field_3_pixel_Check(RECT PIKA_rc, int direction);
};

