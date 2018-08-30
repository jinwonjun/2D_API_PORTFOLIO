#pragma once
class Game_Opening
{
private:
	//============== UI ���� ������=================
	//�ΰ� �κ� �ε����� ī��Ʈ
	//��ܹٿ� ǥ�õ� �ΰ� �׸���
	image * up_logo;
	int logo_count;
	int logo_index;
	int logo_frame_index;//�ΰ� y�� ������ ������ �ε���
	//�ϴܹٿ� ǥ�õ� �ΰ� �׸���
	image * down_logo;
	int logo_down_count;
	int logo_down_index;
	int logo_down_frame_index;//�ΰ� y�� ������ ������ �ε���

	//test image
	//�Ḹ�� �̹�������!
	image * test;

public:
	Game_Opening();
	~Game_Opening();
	//===================���� ����====================
	//���� ���� ȭ��(�Ḹ��)
	bool GameStartSignal;
	int timer;//���� ����ֱ�� Ÿ�̸�
	int comment_time;//��� ġ�°� �ð� ���� ����
	int comment_index;//��� ���� ���� �ε����� ����
	//===================�Լ� ����====================
	HRESULT init();
	void Logo_Up_Render();
	void Logo_down_Render();
	void render(HDC hdc);
	void only_up_logo_render(HDC hdc);
};

