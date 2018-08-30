#include "stdafx.h"


Game_Opening::Game_Opening()
{
}

Game_Opening::~Game_Opening()
{
	//SAFE_DELETE(down_logo);
}

HRESULT Game_Opening::init()
{
	//로고 상단 이미지 불러오기
	//상단 로고 부분 초기화
	logo_count = 0;
	logo_index = 0;
	logo_frame_index = 0;
	up_logo = new image;
	up_logo->init("images/logo_1.bmp", WINSIZEX / 2, WINSIZEY / 2 - 180, 7968 * 1.2, 840 * 1.2, 16, 3, true, RGB(255, 0, 255));
	up_logo->setFrameX(-1);
	up_logo->setFrameY(-1);

	//하단 로고 부분 초기화
	logo_down_count = 55;
	logo_down_index = 0;
	logo_down_frame_index = 0;//로고 y축 프레임 조절용 인덱스
	down_logo = new image;
	down_logo->init("images/logo_2.bmp", WINSIZEX / 2, WINSIZEY / 2 + 160, 1762 * 0.7, 398 * 0.7, 2, 1, true, RGB(255, 0, 255));
	down_logo->setFrameX(-1);
	down_logo->setFrameY(-1);

	//============== 시스템 관련 변수들 ==============
	GameStartSignal = false;//스타트키 확인 시그널
	timer = 0;//타이머 초기화

	//============== UI 관련 초기화 영역 =============
	//잠만보그림
	test = new image;
	test->init("images/test_2.bmp", WINSIZEX / 2, 0, 400, 330, 1, 1, true, RGB(255, 0, 255));

	//대사 치는 부분 초기화
	comment_time = 0;
	comment_index = 1;

	return S_OK;
}

//상단 로고
void Game_Opening::Logo_Up_Render()
{
	logo_count++;
	if (logo_count % 5 == 0)//숫자는 타이머, 일괄적으로 빠르고 느리게 조정
	{
		logo_count = 0;
		int frameX = (up_logo->getFrameX() + 1) % 16;
		up_logo->setFrameX(frameX);

		if (frameX == 0)
		{
			up_logo->setFrameY((up_logo->getFrameY() + 1) % 3);
		}
		if (up_logo->getFrameY() == 2)//끝까지 표시 했으면 되돌리기
		{
			up_logo->setFrameX(0);
			up_logo->setFrameY(0);
		}
	}
}
//하단 로고
void Game_Opening::Logo_down_Render()
{
	logo_down_count++;
	if (logo_down_count % 30 == 0)//숫자는 타이머, 일괄적으로 빠르고 느리게 조정
	{
		logo_down_count = 0;
		int frameX = (down_logo->getFrameX() + 1) % 2;
		down_logo->setFrameX(frameX);

		if (frameX == 0)
		{
			down_logo->setFrameY((down_logo->getFrameY() + 1) % 1);
		}
	}
}

void Game_Opening::render(HDC hdc)
{
	down_logo->frameRender(hdc, down_logo->getX(), down_logo->getY(), down_logo->getFrameX(), down_logo->getFrameY());
	up_logo->frameRender(hdc, up_logo->getX(), up_logo->getY(), up_logo->getFrameX(), up_logo->getFrameY());

	//상단 영역(인벤토리)을 대체할 상황을 만들어주기 위한 bool값이 필요함!
	if (GameStartSignal)
	{
		//이미지 추가
		test->render(hdc, 0, WINSIZEY / 2);
		//폰트 열기
		HFONT font, oldfont;
		font = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "PokemonGSC");
		oldfont = (HFONT)SelectObject(hdc, font);
		//대화상자 위치 렉트
		RECT rt = { 15,WINSIZEY - 90,WINSIZEX - 15,WINSIZEY };
		timer++;
		if (timer < 100)
		{
			wstring str1 = L"피카츄 성님 또 뭔일이당가! 포켓몬트레이너 양반 거거 놀러나가서 없쓰야!";
			if (comment_time % 100 && comment_index < str1.size())
			{
				comment_index++;
			}
			wstring temp(str1.begin(), str1.begin() + comment_index);
			DrawTextW(hdc, temp.c_str(), -1, &rt, DT_WORDBREAK);
			comment_time++;
			//다음 멘트 출력해주기 위해 인덱스 초기화 시키기
			if (timer == 99)
			{
				comment_index = 1;
				comment_time = 0;
			}
		}
		else if (timer >= 100 && timer < 200)
		{
			wstring str2 = L"밖에 추우니깐 후딱 싸돌아 댕기다 드가소! 난 들어가서 한 잠 때리러 이만!";
			if (comment_time % 100 && comment_index < str2.size())
			{
				comment_index++;
			}
			wstring temp(str2.begin(), str2.begin() + comment_index);
			DrawTextW(hdc, temp.c_str(), -1, &rt, DT_WORDBREAK);
			comment_time++;
		}
		else
			GameStartSignal = false;
		//이전폰트 가져오기 및 삭제
		SelectObject(hdc, oldfont);
		DeleteObject(font);
	}
}

void Game_Opening::only_up_logo_render(HDC hdc)
{
	up_logo->frameRender(hdc, up_logo->getX(), up_logo->getY(), up_logo->getFrameX(), up_logo->getFrameY());
}
