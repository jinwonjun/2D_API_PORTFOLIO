#pragma once
#include <vector>
#define BULLETMAX 140//배틀 페이즈 총알 크기
//메인캐릭터 특수 무기용도, 적 구조체, 메인캐릭터 총알, 적이 쏘는 유도 미사일, 적이 쏘는 기본미사일
struct tagRect
{
	RECT rc;
	bool touch;
	bool deathCheck;
	image* tagRect_image;//각각 따로 넣을 거면 이렇게 해서 접근 시키자
};

//총알 구조체
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

//캐논 구조체
struct tagCannon
{
	POINT center;
	POINT cannonEnd;
	float radius;
	float cannon;
	float angle;
};
//폭발 구조체 셋
struct exPlosion
{
	RECT explosion_position;//폭발생성위치
	image * explosion_Image;//폭발그림이미지 삽입
	int explosion_count;//폭발렌더링 카운트
	int explosion_index;//폭발렌덜이 인덱스
	bool explosion_check;//폭발했는지 안했는지 체크해줌
};

struct BossSet //지우새끼 구조체만들기
{
	image * bossImage; // 지우새끼 이미지 붙여주기
	bool bossCheckL;//지우새끼 왼쪽 역치 까지 이동체크
	bool bossCheckR;//지우새끼 오른쪽 역치 까지 이동체크
	RECT bossPosition;//지우새끼 위치
	int bossHp;// 보스 피통
	image * bossHp_image[9];//지우새끼 피통 이미지 출력해주자
	RECT hpRect;//피통 출력해줄 렉트 위치 저장
};


class battle_scene
{
private:

	image* m_bgImage;	//백그라운드
	image* m_apple;		//사과이미지
	RECT   m_rc;		//사과움직일 렉트
	image * m_rockman;//록맨 이미지 가져오기
	RECT m_rockrc;
	int m_count;//록맨 프레임 돌릴 카운트 변수
	int m_index;//프레임 이미지 인덱스
	bool m_isLeft; //방향체크

	//페이즈1
	//그냥 떨어지는 포켓볼 재료
	tagRect m_box[2];//구조체를 배열에 담은거지, 첫줄 장애물
	tagRect m_box2[2];// 두째줄 장애물 
	int m_box_count;
	int m_box_index;
	int m_box2_count;
	int m_box2_index;
	//페이즈2 
	//유도 부분 필요한 재료들
	tagRect guideBullet[4];
	int guide_count;
	int guide_index;
	//페이즈3
	//원형 파형 재료들
	tagCannon _cannon;
	tagBullet _bullet[BULLETMAX];//원형 파형에 대한 구조체 배열 생성
	bool angleCheck;
	int bullet_count;//적이쏘는 원형 파원 카운트
	int bullet_index;//적이쏘는 원형 파원 인덱스

					 //메인캐릭터 인덱스와 카운트, 렉트 
	image * main_Pika;//피카츄 이미지 가져오기
	image * main_Pika_up;//피카츄 윗방향 무브먼트이미지
	RECT main_Pika_rc;//피카츄의 렉트값선언
	int pika_count;//록맨 프레임 돌릴 카운트 변수
	int pika_index;//프레임 이미지 인덱스
	bool pika_isLeft; //방향체크
	int pika_up_count;//록맨 프레임 돌릴 카운트 변수
	int pika_up_index;//프레임 이미지 인덱스
	image * pika_hp_image[9];//피카츄 이미지랑 피통이랑 연동하기
	RECT pika_hp_rc;

	//메인캐릭터 발사체 구현하기
	image * pika_shot;//피카츄 미사일그리기
	tagRect pika_shot_rc;//피카츄 번개 저장용 렉트
	int pika_shot_count;//록맨 프레임 돌릴 카운트 변수
	int pika_shot_index;//프레임 이미지 인덱스

	bool bulletCheck;//기본 미사일 체크
	int bulletCnt;//총알이 3번 발사 되면 밑에놈 트루값 줄생각
	bool doubleEngine;//두개 발싸준비 체크!
	bool doubleEngineLaunch;//두개 발싸!

	RECT pika_laser_rc;

	//로고 부분 인덱스와 카운트
	image * logo; // 이미지 연결하기
	int logo_count;
	int logo_index;
	int logo_frame_index;//로고 y축 프레임 조절용 인덱스

						 //죽음 모션 구현하기
	tagRect death;//그러하다
	int death_count;
	int death_index;

	//피카츄가 피격됬을때 구현하기
	tagRect pikaHit;
	int pika_hit_count;
	int pika_hit_index;
	bool pika_hit_check;
	RECT hitPosition;//적꺼에 맞았을때 좌표값 저장해야되니깐


	//폭발 표현 재료들
	RECT explosionPosition;//미사일 맞으면 폭발 시킬 위치값을 저장해서 애니메이션 출력
	bool explosionCheck;//맞았다고 체크를 해주면 그때 그리게 하자
	exPlosion exp[1];//일단 해보고 크기를 늘리던 줄이던 해보자
	vector <RECT> explosionV;

	//사용자 입력부 변수
	bool leftPress;//왼쪽 방향키 체크
	bool rightPress;//오른쪽 방향키 체크
	bool invincible;//z키를 무적으로 쓰자

public:
	
	battle_scene();
	~battle_scene();

	//=======================변수 관련 부분===========================
	bool battle_scene_check;//배틀 페이지 호출 체크용, 사용자 키입력 조건값 걸어줘야됨
	int pikaHp;//피카츄 피통수치화
	bool bossDeathCheck;//렌더 부분에서 그리는거 확인하는 용도
	//보스 구조체 꺼내오기
	BossSet boss;
	//=======================함수 관련 부분===========================
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	//로고
	void logoRender();//로고부분 애니매이션 돌리기
	//메인 캐릭터
	void pickaRender();//피카츄 무브먼트 관리 함수
	void pickaUpRender();//피카츄 앞으로 누를때 무브먼트 함수
	void pickaShotRender();//피카츄 보통 샷 무브먼트 함수
	void pickaHitRender();//피카츄 피격 됬을 때 무브먼트 함수
	//1페이즈 함수
	void normalRotateRender();//포켓볼 그냥 돌리는 무브먼트 함수
	//2페이즈 유도 함수
	void guideCalMove();
	//3페이즈 원형 파형 관련 함수
	void bulletFire();//원형 파형 연산 함수1
	void bulletMove();//원형 파형 연산 함수2
	void bulletRender();//원형 파원 애니매이션 돌리기(작은 포켓볼이 돈다)
	void addBulletMove();//다양한 원형 파원형태 #1
	void addBulletMove2();//다양한 원형 파원형태 #2
	//기타 함수
	void deathRender();//사망 이펙트 만들기
	void explosionRender();//폭발 렌더링 함수만들기
};

