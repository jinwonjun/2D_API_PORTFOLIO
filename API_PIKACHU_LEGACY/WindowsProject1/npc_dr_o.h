#pragma once
class npc_dr_o
{
private:
	image * dr_o;//프레임 렌더링용 이미지
	int dr_o_count;
	int dr_o_index;
	int dr_o_frame_index;//로고 y축 프레임 조절용 인덱스
	//오박사쪽
	image *  dr_o_comment;//코멘트 출력용 이미지
	image * feel;//느낌표 이미지
	image * question;//물음표 이미지
	//피카츄쪽
	image * angry;

public:
	npc_dr_o();
	~npc_dr_o();

	//===================변수 관련====================
	RECT dr_o_rc;//npc 렉트 선언
	RECT pika_rc_copy;//피카츄 렉트값 카피

	bool CollideSignal;//충돌 체크 했을 때 오박사 이미지 올려주기
	int timer;//글자 찍어주기용 타이머

	int comment_time;//대사 치는거 시간 간격 조정
	int comment_index;//대사 글자 간격 인덱스값 조정
	//===================함수 관련====================
	HRESULT init();
	void DR_O_Render(RECT pika_rc);
	void render(HDC hdc);

	float getAngle(float x1, float y1, float x2, float y2);
};

