#pragma once
class Pika_Comment
{
private:
	image * pika_move;
	image * comment;//��ǳ�� �̹��� �ε�

	int pika_move_count;
	int pika_move_index;
	int pika_move_frame_index;//�ΰ� y�� ������ ������ �ε���
public:
	Pika_Comment();
	~Pika_Comment();

	int timer;
	int comment_time;//��� ġ�°� �ð� ���� ����
	int comment_index;//��� ���� ���� �ε����� ����


	HRESULT init();
	void render(HDC hdc, int statement);
	void pika_Motion_Render();
};

