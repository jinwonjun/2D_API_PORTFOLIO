#pragma once
#include <vector>
#define BULLETMAX 140//��Ʋ ������ �Ѿ� ũ��
//����ĳ���� Ư�� ����뵵, �� ����ü, ����ĳ���� �Ѿ�, ���� ��� ���� �̻���, ���� ��� �⺻�̻���
struct tagRect
{
	RECT rc;
	bool touch;
	bool deathCheck;
	image* tagRect_image;//���� ���� ���� �Ÿ� �̷��� �ؼ� ���� ��Ű��
};

//�Ѿ� ����ü
struct tagBullet
{
	float x, y;
	float speed;
	float angle;
	float radius;
	float gravity;
	bool fire;
	RECT rc;
	bool touch;
	image * bulletImage;
};

//ĳ�� ����ü
struct tagCannon
{
	POINT center;
	POINT cannonEnd;
	float radius;
	float cannon;
	float angle;
};
//���� ����ü ��
struct exPlosion
{
	RECT explosion_position;//���߻�����ġ
	image * explosion_Image;//���߱׸��̹��� ����
	int explosion_count;//���߷����� ī��Ʈ
	int explosion_index;//���߷����� �ε���
	bool explosion_check;//�����ߴ��� ���ߴ��� üũ����
};

struct BossSet //������� ����ü�����
{
	image * bossImage; // ������� �̹��� �ٿ��ֱ�
	bool bossCheckL;//������� ���� ��ġ ���� �̵�üũ
	bool bossCheckR;//������� ������ ��ġ ���� �̵�üũ
	RECT bossPosition;//������� ��ġ
	int bossHp;// ���� ����
	image * bossHp_image[9];//������� ���� �̹��� ���������
	RECT hpRect;//���� ������� ��Ʈ ��ġ ����
};


class battle_scene
{
private:

	image* m_bgImage;	//��׶���
	image* m_apple;		//����̹���
	RECT   m_rc;		//��������� ��Ʈ
	image * m_rockman;//�ϸ� �̹��� ��������
	RECT m_rockrc;
	int m_count;//�ϸ� ������ ���� ī��Ʈ ����
	int m_index;//������ �̹��� �ε���
	bool m_isLeft; //����üũ

	//������1
	//�׳� �������� ���Ϻ� ���
	tagRect m_box[2];//����ü�� �迭�� ��������, ù�� ��ֹ�
	tagRect m_box2[2];// ��°�� ��ֹ� 
	int m_box_count;
	int m_box_index;
	int m_box2_count;
	int m_box2_index;
	//������2 
	//���� �κ� �ʿ��� ����
	tagRect guideBullet[4];
	int guide_count;
	int guide_index;
	//������3
	//���� ���� ����
	tagCannon _cannon;
	tagBullet _bullet[BULLETMAX];//���� ������ ���� ����ü �迭 ����
	bool angleCheck;
	int bullet_count;//���̽�� ���� �Ŀ� ī��Ʈ
	int bullet_index;//���̽�� ���� �Ŀ� �ε���

					 //����ĳ���� �ε����� ī��Ʈ, ��Ʈ 
	image * main_Pika;//��ī�� �̹��� ��������
	image * main_Pika_up;//��ī�� ������ �����Ʈ�̹���
	RECT main_Pika_rc;//��ī���� ��Ʈ������
	int pika_count;//�ϸ� ������ ���� ī��Ʈ ����
	int pika_index;//������ �̹��� �ε���
	bool pika_isLeft; //����üũ
	int pika_up_count;//�ϸ� ������ ���� ī��Ʈ ����
	int pika_up_index;//������ �̹��� �ε���
	image * pika_hp_image[9];//��ī�� �̹����� �����̶� �����ϱ�
	RECT pika_hp_rc;

	//����ĳ���� �߻�ü �����ϱ�
	image * pika_shot;//��ī�� �̻��ϱ׸���
	tagRect pika_shot_rc;//��ī�� ���� ����� ��Ʈ
	int pika_shot_count;//�ϸ� ������ ���� ī��Ʈ ����
	int pika_shot_index;//������ �̹��� �ε���

	bool bulletCheck;//�⺻ �̻��� üũ
	int bulletCnt;//�Ѿ��� 3�� �߻� �Ǹ� �ؿ��� Ʈ�簪 �ٻ���
	bool doubleEngine;//�ΰ� �߽��غ� üũ!
	bool doubleEngineLaunch;//�ΰ� �߽�!

	RECT pika_laser_rc;

	//�ΰ� �κ� �ε����� ī��Ʈ
	image * logo; // �̹��� �����ϱ�
	int logo_count;
	int logo_index;
	int logo_frame_index;//�ΰ� y�� ������ ������ �ε���

						 //���� ��� �����ϱ�
	tagRect death;//�׷��ϴ�
	int death_count;
	int death_index;

	//��ī�� �ǰ݉����� �����ϱ�
	tagRect pikaHit;
	int pika_hit_count;
	int pika_hit_index;
	bool pika_hit_check;
	RECT hitPosition;//������ �¾����� ��ǥ�� �����ؾߵǴϱ�


	//���� ǥ�� ����
	RECT explosionPosition;//�̻��� ������ ���� ��ų ��ġ���� �����ؼ� �ִϸ��̼� ���
	bool explosionCheck;//�¾Ҵٰ� üũ�� ���ָ� �׶� �׸��� ����
	exPlosion exp[1];//�ϴ� �غ��� ũ�⸦ �ø��� ���̴� �غ���
	vector <RECT> explosionV;

	//����� �Էº� ����
	bool leftPress;//���� ����Ű üũ
	bool rightPress;//������ ����Ű üũ
	bool invincible;//zŰ�� �������� ����

public:
	
	battle_scene();
	~battle_scene();

	//=======================���� ���� �κ�===========================
	bool battle_scene_check;//��Ʋ ������ ȣ�� üũ��, ����� Ű�Է� ���ǰ� �ɾ���ߵ�
	int pikaHp;//��ī�� �����ġȭ
	bool bossDeathCheck;//���� �κп��� �׸��°� Ȯ���ϴ� �뵵
	//���� ����ü ��������
	BossSet boss;
	//=======================�Լ� ���� �κ�===========================
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	//�ΰ�
	void logoRender();//�ΰ�κ� �ִϸ��̼� ������
	//���� ĳ����
	void pickaRender();//��ī�� �����Ʈ ���� �Լ�
	void pickaUpRender();//��ī�� ������ ������ �����Ʈ �Լ�
	void pickaShotRender();//��ī�� ���� �� �����Ʈ �Լ�
	void pickaHitRender();//��ī�� �ǰ� ���� �� �����Ʈ �Լ�
	//1������ �Լ�
	void normalRotateRender();//���Ϻ� �׳� ������ �����Ʈ �Լ�
	//2������ ���� �Լ�
	void guideCalMove();
	//3������ ���� ���� ���� �Լ�
	void bulletFire();//���� ���� ���� �Լ�1
	void bulletMove();//���� ���� ���� �Լ�2
	void bulletRender();//���� �Ŀ� �ִϸ��̼� ������(���� ���Ϻ��� ����)
	void addBulletMove();//�پ��� ���� �Ŀ����� #1
	void addBulletMove2();//�پ��� ���� �Ŀ����� #2
	//��Ÿ �Լ�
	void deathRender();//��� ����Ʈ �����
	void explosionRender();//���� ������ �Լ������
};

