#pragma once
class Pika_Comment
{
private:
	image * pika_move;
	image * comment;//말풍선 이미지 로딩

	int pika_move_count;
	int pika_move_index;
	int pika_move_frame_index;//로고 y축 프레임 조절용 인덱스
public:
	Pika_Comment();
	~Pika_Comment();

	int timer;
	int comment_time;//대사 치는거 시간 간격 조정
	int comment_index;//대사 글자 간격 인덱스값 조정


	HRESULT init();
	void render(HDC hdc, int statement);
	void pika_Motion_Render();
};

