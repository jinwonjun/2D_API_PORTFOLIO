#include "stdafx.h"

Field_1::Field_1()
{
}

Field_1::~Field_1()
{
}

HRESULT Field_1::init()
{
	//필드 이미지 호출하기
	field_1 = new image;
	field_1->init("images/map1.bmp", WINSIZEX / 2, 0, 400, 340, 1, 1, true, RGB(255, 0, 255));

	pika_move = new image;
	pika_move->init("images/PikaAtk56_1.bmp", WINSIZEX / 2 + 100, WINSIZEY/2 +100, 4368, 135, 56, 1, true, RGB(255, 0, 255));

	comment = new image;
	comment->init("images/dialogue1.bmp", WINSIZEX / 2, 0, 400, 100, 1, 1, true, RGB(255, 0, 255));
	pika_move_count = 0;
	pika_move_index = 0;
	pika_move_frame_index = 0;

	pika_comment_check = false;
	timer = 0;

	fountain = new image;
	fountain->init("images/fountain.bmp", WINSIZEX / 2 - 100, WINSIZEY / 2 + 80, 600, 104, 5, 1, true, RGB(255, 0, 255));
	trees[39] = RectMake(40, WINSIZEY / 2 + 25 , 600 /5 , 104);

	fountain_count = 0;
	fountain_index = 0;
	fountain_frame_index = 0;//로고 y축 프레임 조절용 인덱스

	//나무모양에 장애물 체크 해줄 가상의 렉트 값 박아주자
	for (int i = 0; i < 4; i++)
	{
		trees[i] = RectMake(0 + 40 * i, WINSIZEY / 2 - 15, 40, 30);
	}
	trees[4] = RectMake(0 , WINSIZEY / 2 - 15 + 30, 40, 30);
	for (int i = 5; i < 9; i++)
	{
		trees[i] = RectMake(WINSIZEX - (40 * (9-i)), WINSIZEY / 2 - 15, 40, 30);
	}
	for (int i = 9; i < 11; i++)
	{
		trees[i] = RectMake(WINSIZEX - (40 * (11 - i)), WINSIZEY / 2 - 15 + 30, 40, 30);
	}
	trees[11] = RectMake(WINSIZEX - 40, WINSIZEY / 2 - 15 + 30 + 30, 40, 30);
	for (int i = 12; i < 16; i++)
	{
		trees[i] = RectMake(0, (WINSIZEY / 2 - 15) + ((i-12) * 30) + 110, 40, 30);
	}
	for (int i = 16; i < 18; i++)
	{
		trees[i] = RectMake(0 + 40, (WINSIZEY / 2 - 15) + ((i - 16) * 30) + 150, 40, 30);
	}
	for (int i = 18; i < 20; i++)
	{
		trees[i] = RectMake(WINSIZEX - 180, (WINSIZEY / 2 - 15) + ((i - 18) * 30) + 100, 40, 30);
	}
	trees[20] = RectMake(WINSIZEX - 180 + 40, (WINSIZEY / 2 - 15) + 20 + 100, 40, 30);
	trees[21] = RectMake(0, WINSIZEY - 60, 40, 30);
	for (int i = 22; i < 27; i++)
	{
		trees[i] = RectMake(0 + (i-22)*40 , WINSIZEY-30, 40, 30);
	}
	for (int i = 27; i < 30; i++)
	{
		trees[i] = RectMake(WINSIZEX - 160, WINSIZEY - (30-i)*30, 40, 30);
	}
	for (int i = 30; i < 36; i++)
	{
		if(i <= 32)
		trees[i] = RectMake(WINSIZEX - 40 * (33-i), WINSIZEY - 60, 40, 30);
		else
			trees[i] = RectMake(WINSIZEX - 40 * (36-i), WINSIZEY - 30, 40, 30);
	}
	trees[36] = RectMake(WINSIZEX - 40, WINSIZEY - 90, 40, 30);
	trees[37] = RectMake(WINSIZEX - 40, WINSIZEY - 120, 40, 30);
	trees[38] = RectMake(WINSIZEX - 160, WINSIZEY - 120, 40, 30);

	scene_check = RectMake(0,WINSIZEY - 100,30,30);
	//화면 체크용 장판 만들기
	//battle_start_check = RectMake(170, WINSIZEY/2 - 15, 60, 30);
	//battle_start = false;

	field_1_to_3 = RectMake(170, WINSIZEY / 2 - 15, 60, 30);//필드 1과 3 체크용 렉트
	field_1_to_3_check = false;
	//대사 치는 부분 초기화
	comment_time = 0;
	comment_index = 1;

	return S_OK;
}

void Field_1::pika_Motion_Render()
{
	pika_move_count++;
	if (pika_move_count % 3 == 0)//숫자는 타이머, 일괄적으로 빠르고 느리게 조정
	{
		pika_move_count = 0;
		int frameX = (pika_move->getFrameX() + 1) % 56;
		pika_move->setFrameX(frameX);

		if (frameX == 0)
		{
			pika_move->setFrameY((pika_move->getFrameY() + 1) % 1);
		}
	}
}

void Field_1::fountain_Render()
{
	fountain_count++;
	if (fountain_count % 5 == 0)//숫자는 타이머, 일괄적으로 빠르고 느리게 조정
	{
		fountain_count = 0;
		int frameX = (fountain->getFrameX() + 1) % 5;
		fountain->setFrameX(frameX);

		if (frameX == 0)
		{
			fountain->setFrameY((fountain->getFrameY() + 1) % 1);
		}
	}
}

bool Field_1::treeColliderCheck(RECT PIKA_rc)
{
	RECT temp;//검출 임시 변수값 생성
	for (int i = 0; i < 40; i++)
	{
		if (IntersectRect(&temp, &trees[i], &PIKA_rc))
		{
			return true;
		}
	}
	if (IntersectRect(&temp, &scene_check, &PIKA_rc))
	{
		scene_check_left = true;
		return false;
	}
	if (IntersectRect(&temp, &field_1_to_3, &PIKA_rc))
	{
		field_1_to_3_check = true;
		return false;
	}
	return false;
}

void Field_1::render(HDC hdc)
{
	timer++;
	//필드 이미지 그리기
	field_1->render(hdc, 0, WINSIZEY / 2-15);
	fountain->frameRender(hdc, fountain->getX(), fountain->getY(), fountain->getFrameX(), fountain->getFrameY());
	/*for (int i = 0; i < 40; i++)
	{
		RectangleMake(hdc, trees[i].left, trees[i].top, trees[i].right - trees[i].left, trees[i].bottom - trees[i].top);
	}*/
	//씬전환 장판 체크용
	//RectangleMake(hdc, scene_check.left, scene_check.top, scene_check.right - scene_check.left, scene_check.bottom - scene_check.top);
	//전투 전환 장판 체크용
	//RectangleMake(hdc, field_1_to_3.left, field_1_to_3.top, field_1_to_3.right - field_1_to_3.left, field_1_to_3.bottom - field_1_to_3.top);

	if (timer < 300)
	{
		pika_move->frameRender(hdc, pika_move->getX(), pika_move->getY(), pika_move->getFrameX(), pika_move->getFrameY());
		comment->render(hdc, 0, WINSIZEY - 110);
		HFONT font, oldfont;
		font = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "PokemonGSC");
		oldfont = (HFONT)SelectObject(hdc, font);
		//대화상자 위치 렉트
		RECT rt = { 15,WINSIZEY - 90,WINSIZEX - 15,WINSIZEY };

		wstring str1 = L"모험을 시작하러 가즈아!!!\n너가 어디있든 도와줄게!!!";

		if (comment_time % 100 && comment_index < str1.size())
		{
			comment_index++;
		}
		wstring temp(str1.begin(), str1.begin() + comment_index);
		DrawTextW(hdc, temp.c_str(), -1, &rt, DT_WORDBREAK);
		comment_time++;
		
		//이전폰트 가져오기 및 삭제
		SelectObject(hdc, oldfont);
		DeleteObject(font);
	}
	else
	{
		pika_comment_check = true;
	}
}