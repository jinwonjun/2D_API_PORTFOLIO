#pragma once
class mainCharacter
{
private:
	//메인캐릭터 인덱스와 카운트, 렉트 
	int pika_count;//록맨 프레임 돌릴 카운트 변수
	int pika_index;//프레임 이미지 인덱스
	int pika_up_count;//프레임 돌릴 카운트 변수
	int pika_up_index;//프레임 이미지 인덱스
	int pika_down_count;//프레임 돌릴 카운트 변수
	int pika_down_index;//프레임 이미지 인덱스

//	int pikaHp;//피카츄 피통수치화
//	image * pika_hp_image[9];//피카츄 이미지랑 피통이랑 연동하기
//	RECT pika_hp_rc;
public:
	mainCharacter();
	~mainCharacter();

	image * main_Pika;//피카츄 이미지 가져오기
	image * main_Pika_up;//피카츄 윗방향 무브먼트이미지
	image * main_Pika_down;//피카츄 윗방향 무브먼트이미지
	RECT main_Pika_rc;//피카츄의 렉트값선언
	bool pika_isLeft; //방향체크
	bool leftPress;//왼쪽 방향키 체크
	bool rightPress;//오른쪽 방향키 체크
	bool downPress;//아래쪽 방향키 체크


	HRESULT init();
	void pickaRender();//피카츄 무브먼트 관리 함수
	void pickaUpRender();//피카츄 앞으로 누를때 무브먼트 함수
	void pickaDownRender();//피카츄 밑으로 누를때 무브먼트 함수
	void render(HDC hdc);
};
