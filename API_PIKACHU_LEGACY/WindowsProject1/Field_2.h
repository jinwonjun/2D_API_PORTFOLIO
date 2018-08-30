#pragma once
class Field_2
{
private:
	image * field_2_img;
	int field_2_count;
	int field_2_index;
	int field_2_frame_index;//로고 y축 프레임 조절용 인덱스
	RECT field_2_rc;//필드 충돌 체크 렉트

	image * huioong;//접근 했을 시에 휘웅이 이미지 띄워주기
	image * feel;//느낌표 이미지
	image * question;//물음표 이미지

public:
	Field_2();
	~Field_2();

	
	//===================변수 관련====================
	RECT huioong_rc;//충돌 체크용 rc
	RECT pika_rc_copy;//피카츄 렉트값 카피
	bool CollideSignal;//충돌 체크 했을 때 휘웅 이미지 올려주기
	int timer;//글자 찍어주기용 타이머

	int comment_time;//대사 치는거 시간 간격 조정
	int comment_index;//대사 글자 간격 인덱스값 조정

	//===================함수 관련====================
	HRESULT init();
	void render(HDC hdc);
	//왼쪽 필드를 호출해보자
	void field_2_Render();
	//피카츄랑 충돌 체크
	bool treeColliderCheck(RECT PIKA_rc);
};

