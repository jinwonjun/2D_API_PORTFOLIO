#pragma once
class mainCharacter
{
private:
	//����ĳ���� �ε����� ī��Ʈ, ��Ʈ 
	int pika_count;//�ϸ� ������ ���� ī��Ʈ ����
	int pika_index;//������ �̹��� �ε���
	int pika_up_count;//������ ���� ī��Ʈ ����
	int pika_up_index;//������ �̹��� �ε���
	int pika_down_count;//������ ���� ī��Ʈ ����
	int pika_down_index;//������ �̹��� �ε���

//	int pikaHp;//��ī�� �����ġȭ
//	image * pika_hp_image[9];//��ī�� �̹����� �����̶� �����ϱ�
//	RECT pika_hp_rc;
public:
	mainCharacter();
	~mainCharacter();

	image * main_Pika;//��ī�� �̹��� ��������
	image * main_Pika_up;//��ī�� ������ �����Ʈ�̹���
	image * main_Pika_down;//��ī�� ������ �����Ʈ�̹���
	RECT main_Pika_rc;//��ī���� ��Ʈ������
	bool pika_isLeft; //����üũ
	bool leftPress;//���� ����Ű üũ
	bool rightPress;//������ ����Ű üũ
	bool downPress;//�Ʒ��� ����Ű üũ


	HRESULT init();
	void pickaRender();//��ī�� �����Ʈ ���� �Լ�
	void pickaUpRender();//��ī�� ������ ������ �����Ʈ �Լ�
	void pickaDownRender();//��ī�� ������ ������ �����Ʈ �Լ�
	void render(HDC hdc);
};
