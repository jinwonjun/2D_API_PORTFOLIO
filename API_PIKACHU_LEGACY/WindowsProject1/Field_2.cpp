#include "stdafx.h"

Field_2::Field_2()
{
}


Field_2::~Field_2()
{
}

HRESULT Field_2::init()
{
	field_2_img = new image;
	field_2_img->init("images/field_2_4_19.bmp",WINSIZEX/2,WINSIZEY/2+155,2000,6327,4,19,true, RGB(255, 0, 255));
	field_2_count=0;
	field_2_index=0;
	field_2_frame_index=0;//로고 y축 프레임 조절용 인덱스
	field_2_img->setFrameX(-1);
	field_2_img->setFrameY(-1);

	field_2_rc = RectMake(0,WINSIZEY/2-13,115,WINSIZEY/2 +20);

	huioong = new image;
	huioong->init("images/huioong_meet.bmp", WINSIZEX / 2, 0, 400, 340, 1, 1, true, RGB(255, 0, 255));
	huioong_rc = RectMake(180,WINSIZEY/2 + 122, 40,50);//충돌 체크용 rc

	//물음표 이미지
	question = new image;
	question->init("images/question.bmp", WINSIZEX / 2, WINSIZEY / 2 + 100 - 68, 68, 62, 1, 1, true, RGB(255, 0, 255));
	//느낌표 이미지
	feel = new image;
	feel->init("images/feel.bmp", WINSIZEX / 2, WINSIZEY / 2 + 100 - 68, 68, 62, 1, 1, true, RGB(255, 0, 255));

	comment_time = 0;
	comment_index = 1;

	return S_OK;
}

void Field_2::field_2_Render()
{
	field_2_count++;
	if (field_2_count % 2 == 0)//숫자는 타이머, 일괄적으로 빠르고 느리게 조정
	{
		field_2_count = 0;
		int frameX = (field_2_img->getFrameX() + 1) % 4;
		field_2_img->setFrameX(frameX);

		if (frameX == 0)
		{
			field_2_img->setFrameY((field_2_img->getFrameY() + 1) % 19);
		}
	}
}

bool Field_2::treeColliderCheck(RECT PIKA_rc)
{
	pika_rc_copy = PIKA_rc;//피카츄 위치값 복사

	//피카츄랑 충돌체크 시그널 만들기
	RECT tempRC;
	if (IntersectRect(&tempRC, &huioong_rc, &PIKA_rc))
	{
		CollideSignal = true;
	}

	RECT temp;//검출 임시 변수값 생성
	if (IntersectRect(&temp, &field_2_rc, &PIKA_rc))
	{
		return true;
	}

	return false;
}

void Field_2::render(HDC hdc)
{
	field_2_img->frameRender(hdc, field_2_img->getX(), field_2_img->getY(), field_2_img->getFrameX(), field_2_img->getFrameY());
	//RectangleMake(hdc, huioong_rc.left, huioong_rc.top, huioong_rc.right - huioong_rc.left, huioong_rc.bottom - huioong_rc.top);
	//RectangleMake(hdc, field_2_rc.left, field_2_rc.top, field_2_rc.right- field_2_rc.left, field_2_rc.bottom- field_2_rc.top);

	//휘웅이랑 피카츄 렉트 충돌 체크 걸어서 true일때 표시해주기
	if (CollideSignal)
	{
		//폰트 열기
		HFONT font, oldfont;
		font = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "PokemonGSC");
		oldfont = (HFONT)SelectObject(hdc, font);
		//대화상자 위치 렉트
		RECT rt = { 15,WINSIZEY - 90,WINSIZEX - 15,WINSIZEY };
		timer++;
		if (timer < 50)
		{
			//물음표
			question->render(hdc, huioong_rc.left, huioong_rc.top - 40);
		}
		else if (timer >= 50 && timer < 100)
		{
			//느낌표
			feel->render(hdc, huioong_rc.left, huioong_rc.top - 40);
		}
		else if (timer >= 100 && timer < 200)
		{
			//이미지 추가
			huioong->render(hdc, 0, WINSIZEY / 2 - 15);
			wstring str1 = L"여어?!?! 난 해치지 않아 걱정마 친구야 괜찮아! 모험을 하는 중이구나?";
			if (comment_time % 100 && comment_index < str1.size())
			{
				comment_index++;
			}
			wstring temp(str1.begin(), str1.begin() + comment_index);
			DrawTextW(hdc, temp.c_str(), -1, &rt, DT_WORDBREAK);
			comment_time++;
			//다음 멘트 출력해주기 위해 인덱스 초기화 시키기
			if (timer == 199)
			{
				comment_index = 1;
				comment_time = 0;
			}
		}
		else if (timer >= 200 && timer < 300)
		{
			//이미지 추가
			huioong->render(hdc, 0, WINSIZEY / 2 - 15);
			wstring str2 = L"모든 사람이 포켓몬을 탐하는 건 아니란다! 그래도 항상 조심하렴!";
			if (comment_time % 100 && comment_index < str2.size())
			{
				comment_index++;
			}
			wstring temp(str2.begin(), str2.begin() + comment_index);
			DrawTextW(hdc, temp.c_str(), -1, &rt, DT_WORDBREAK);
			comment_time++;
			//다음 멘트 출력해주기 위해 인덱스 초기화 시키기
			if (timer == 299)
			{
				comment_index = 1;
				comment_time = 0;
			}
		}
		//초기화
		else
		{
			//전체 타이머는 900일때 초기화 시키기
			//피카츄 멘트가 이어져야해서 강제로 시간을 늘림.
			if (timer >= 900)
			{
				//발동조건은 true일때임!
				CollideSignal = false;
				timer = 0;
			}
		}
		//이전폰트 가져오기 및 삭제
		SelectObject(hdc, oldfont);
		DeleteObject(font);
	}

}