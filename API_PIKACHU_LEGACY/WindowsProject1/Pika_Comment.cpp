#include "stdafx.h"

Pika_Comment::Pika_Comment()
{
}


Pika_Comment::~Pika_Comment()
{
}

HRESULT Pika_Comment::init()
{
	pika_move = new image;
	pika_move->init("images/PikaAtk56_1.bmp", WINSIZEX / 2 + 100, WINSIZEY / 2 + 100, 4368, 135, 56, 1, true, RGB(255, 0, 255));

	comment = new image;
	comment->init("images/dialogue1.bmp", WINSIZEX / 2, 0, 400, 100, 1, 1, true, RGB(255, 0, 255));
	pika_move_count = 0;
	pika_move_index = 0;
	pika_move_frame_index = 0;

	
	timer = 0;

	comment_time = 0;//대사 치는거 시간 간격 조정
	comment_index = 1;//대사 글자 간격 인덱스값 조정

	return S_OK;
}

void Pika_Comment::pika_Motion_Render()
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

//두 번째 매개변수에 커맨터리 값을 줘서 상태 값을 변화하게 해주자
void Pika_Comment::render(HDC hdc, int statement)
{
	//모든 case에 대한 변수 초기화 물려주기
	//comment_index = 1;
	//comment_time = 0;
	//처리 구문에 대한 코멘터리 값을 statement 매개변수에 넘겨주기(mainGame.cpp 의 렌더에서 조절함.)
	switch (statement)
	{
	case 1:
	{
		pika_move->frameRender(hdc, pika_move->getX(), pika_move->getY(), pika_move->getFrameX(), pika_move->getFrameY());
		comment->render(hdc, 0, WINSIZEY - 110);
		HFONT font, oldfont;
		font = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "PokemonGSC");
		oldfont = (HFONT)SelectObject(hdc, font);
		//대화상자 위치 렉트
		RECT rt = { 15,WINSIZEY - 90,WINSIZEX - 15,WINSIZEY };
		wstring str1 = L"뭐야 저 아저씨... 풀숲을 헤쳐 친구들을 만나보자! 모험을 떠나자구!";
		//char str[] = "뭐야 저 아저씨... 풀숲을 헤쳐 친구들을 만나보자! 모험을 떠나자구!";
		//DrawText(hdc, str, -1, &rt, DT_WORDBREAK);
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
	break;
	case 2:
	{
		//printf("코멘트 인덱스 : %d, 코멘트 타임 : %d\n", comment_index, comment_time);
		pika_move->frameRender(hdc, pika_move->getX(), pika_move->getY(), pika_move->getFrameX(), pika_move->getFrameY());
		comment->render(hdc, 0, WINSIZEY - 110);
		HFONT font, oldfont;
		font = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "PokemonGSC");
		oldfont = (HFONT)SelectObject(hdc, font);
		//대화상자 위치 렉트
		RECT rt = { 15,WINSIZEY - 90,WINSIZEX - 15,WINSIZEY };
		timer++;
		if (timer < 150)
		{
			//char str[] = "기본 전투 방식은 슈팅이야! 회복 아이템은 필드에 존재해!";
			//DrawText(hdc, str, -1, &rt, DT_WORDBREAK);
			wstring str2 = L"기본 전투 방식은 슈팅이야! 회복 아이템은 필드에 존재해!";
			if (comment_time % 100 && comment_index < str2.size())
			{
				comment_index++;
			}
			wstring temp(str2.begin(), str2.begin() + comment_index);
			DrawTextW(hdc, temp.c_str(), -1, &rt, DT_WORDBREAK);
			comment_time++;
			if (timer == 149)
			{
				comment_index = 1;
				comment_time = 0;
			}
		}
		else if (timer >= 150 && timer < 300)
		{
			wstring str3 = L"모험을 통해서 여러가지 아이템을 얻어보도록 해보자!";
			if (comment_time % 100 && comment_index < str3.size())
			{
				comment_index++;
			}
			wstring temp(str3.begin(), str3.begin() + comment_index);
			DrawTextW(hdc, temp.c_str(), -1, &rt, DT_WORDBREAK);
			comment_time++;
			if (timer == 299)
			{
				comment_time = 0;
				comment_index = 1;
			}
		}
		else
			timer = 300;//초기화가 이상해
		//이전폰트 가져오기 및 삭제
		SelectObject(hdc, oldfont);
		DeleteObject(font);
	}
	break;
	case 3:
	{
		pika_move->frameRender(hdc, pika_move->getX(), pika_move->getY(), pika_move->getFrameX(), pika_move->getFrameY());
		comment->render(hdc, 0, WINSIZEY - 110);
		HFONT font, oldfont;
		font = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "PokemonGSC");
		oldfont = (HFONT)SelectObject(hdc, font);
		//대화상자 위치 렉트
		RECT rt = { 15,WINSIZEY - 90,WINSIZEX - 15,WINSIZEY };
		timer++;
		if (timer < 150)
		{
			wstring str1 = L"잘하고 있어! RPG의 기본은 일단 들이대보는거지!";
			if (comment_time % 100 && comment_index < str1.size())
			{
				comment_index++;
			}
			wstring temp(str1.begin(), str1.begin() + comment_index);
			DrawTextW(hdc, temp.c_str(), -1, &rt, DT_WORDBREAK);
			comment_time++;
			if (timer == 149)
			{
				comment_time = 0;
				comment_index = 1;
			}
		}
		else if (timer >= 150 && timer < 300)
		{
			wstring str2 = L"그렇다면 TAB키를 한번 눌러볼까!\n모르면 일단 해봐 임마!!!";
			if (comment_time % 100 && comment_index < str2.size())
			{
				comment_index++;
			}
			wstring temp(str2.begin(), str2.begin() + comment_index);
			DrawTextW(hdc, temp.c_str(), -1, &rt, DT_WORDBREAK);
			comment_time++;
			if (timer == 299)
			{
				comment_time = 0;
				comment_index = 1;
			}
		}
		else if (timer >= 300 && timer < 450)
		{
			wstring str3 = L"아직은 미구현(STL 벡터를 사용해야돼...ㅠ)...이지만 뭔소린지 모르지?";
			if (comment_time % 100 && comment_index < str3.size())
			{
				comment_index++;
			}
			wstring temp(str3.begin(), str3.begin() + comment_index);
			DrawTextW(hdc, temp.c_str(), -1, &rt, DT_WORDBREAK);
			comment_time++;
			if (timer == 449)
			{
				comment_time = 0;
				comment_index = 1;
			}
		}
		else if (timer >= 450 && timer < 600)
		{
			wstring str4 = L"아이템을 통해서 더 강해질 수 있어!\n자! 그렇다면 모험을 계속 진행해볼까?";
			if (comment_time % 100 && comment_index < str4.size())
			{
				comment_index++;
			}
			wstring temp(str4.begin(), str4.begin() + comment_index);
			DrawTextW(hdc, temp.c_str(), -1, &rt, DT_WORDBREAK);
			comment_time++;
			if (timer == 599)
			{
				comment_time = 0;
				comment_index = 1;
			}
		}
		else
			timer = 600;//초기화가 이상해
						//이전폰트 가져오기 및 삭제
		SelectObject(hdc, oldfont);
		DeleteObject(font);
	}
	break;
	default:

		break;
	}
}