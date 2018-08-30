#include "stdafx.h"

npc_dr_o::npc_dr_o()
{
}

npc_dr_o::~npc_dr_o()
{
}

HRESULT npc_dr_o::init()
{
	dr_o_count = 0;
	dr_o_index = 0;
	dr_o_frame_index = 0;
	dr_o = new image;
	dr_o->init("images/sprite13m.bmp", WINSIZEX / 2, WINSIZEY / 2 +100, 144 * 0.8 , 256 * 0.8, 3, 4, true, RGB(255, 0, 255));

	dr_o_comment = new image;
	dr_o_comment->init("images/dr_o_meet_m.bmp", WINSIZEX / 2, 0, 400, 340, 1, 1, true, RGB(255, 0, 255));

	dr_o_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 100, 144 / 3 * 0.8 , 256 / 4 * 0.8);//주인공 렉트 위치 초기화
	//프레임 기본값 초기화
	dr_o->setFrameX(-1);
	dr_o->setFrameY(-1);
	//물음표 이미지
	question = new image;
	question->init("images/question.bmp", WINSIZEX / 2, WINSIZEY / 2 + 100 - 68, 68, 62, 1, 1, true, RGB(255, 0, 255));
	//느낌표 이미지
	feel = new image;
	feel->init("images/feel.bmp", WINSIZEX / 2, WINSIZEY / 2 + 100 - 68, 68, 62, 1, 1, true, RGB(255, 0, 255));
	//화난 이미지
	angry = new image;
	angry->init("images/angry.bmp", WINSIZEX / 2, WINSIZEY / 2 + 100 - 68, 68, 62, 1, 1, true, RGB(255, 0, 255));

	//충돌 체크 시그널
	CollideSignal = false;
	//멘트 시간차 체크 변수
	timer = 0;

	comment_time = 0;
	comment_index = 1;

	return S_OK;
}

//프레임 렌더링(NPC 기본방향은 캐릭터 위치값에 기반한 방향설정)
//일단 출력먼저(피카츄의 렉트 값을 매개변수로 줘서 프레임 위치를 식별해주자)
void npc_dr_o::DR_O_Render(RECT pika_rc)
{
	pika_rc_copy = pika_rc;//피카츄 위치값 복사
	//박사님이랑 피카츄 사이의 각도를 구해서 랜더링 해보즈아아아
	float temp;
	temp = getAngle((pika_rc.right + pika_rc.left) / 2, (pika_rc.bottom + pika_rc.top) / 2, (dr_o_rc.right + dr_o_rc.left) / 2, (dr_o_rc.bottom + dr_o_rc.top) / 2);
	//printf("%f\n", temp);

	dr_o_count++;
	if (dr_o_count % 10 == 0)//숫자는 타이머, 일괄적으로 빠르고 느리게 조정
	{
		dr_o_count = 0;
		int frameX = (dr_o->getFrameX() + 1) % 3;
		dr_o->setFrameX(frameX);

		//위쪽(뒤통수)
		if (-3.0f < temp && -0.4f > temp)
		{
			dr_o->setFrameY(0);
		}
		//오른쪽(오른쪽 방향)
		if (2.0f < temp && 4.0f > temp)
		{
			dr_o->setFrameY(1);
		}
		//아래쪽(앞면)
		if (0.8f < temp && 2.0f > temp)
		{
			dr_o->setFrameY(2);
		}
		//왼쪽(왼쪽 방향)
		if (-0.4f < temp && 0.8f > temp)
		{
			dr_o->setFrameY(3);
		}
	}
	
	//피카츄랑 충돌체크 시그널 만들기
	RECT tempRC;
	if (IntersectRect(&tempRC, &dr_o_rc, &pika_rc))
	{
		CollideSignal = true;
	}
}

//렌더 한거 그려주기
void npc_dr_o::render(HDC hdc)
{
	dr_o->frameRender(hdc, dr_o->getX(), dr_o->getY(), dr_o->getFrameX(), dr_o->getFrameY());
	
	//렉트 위치값 확인용
	//RectangleMake(hdc, dr_o_rc.left, dr_o_rc.top, dr_o_rc.right - dr_o_rc.left, dr_o_rc.bottom - dr_o_rc.top);

	//오박사랑 피카츄 렉트 충돌 체크 걸어서 true일때 표시해주기
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
			question->render(hdc, dr_o_rc.left, dr_o_rc.top - 40);
		}
		else if (timer >= 50 && timer < 100)
		{
			//느낌표
			feel->render(hdc, dr_o_rc.left, dr_o_rc.top - 40);
		}
		else if (timer >= 100 && timer < 200)
		{
			//이미지 추가
			dr_o_comment->render(hdc, 0, WINSIZEY / 2-15);
			wstring str1 = L"왐마?!?!!! 야생의 피카츄가 이런 귀한 곳에 누추한 생물이?!";
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
			dr_o_comment->render(hdc, 0, WINSIZEY / 2-15);
			wstring str2 = L"거기!!! 드....등짝을 보자!";
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
			//화난 표시
			angry->render(hdc, pika_rc_copy.left, pika_rc_copy.top - 40);
			if (timer > 500)
			{
				CollideSignal = false;
				timer = 0;
			}
		}
		//이전폰트 가져오기 및 삭제
		SelectObject(hdc, oldfont);
		DeleteObject(font);
	}
}

float npc_dr_o::getAngle(float x1, float y1, float x2, float y2)
{

	float x = x2 - x1;
	float y = y2 - y1;
	//두점 사이의 거리를 구하는 공식
	float distance = sqrtf(x * x + y *y);
	//두점 사이의 각도 구하는 공식
	float angle = acosf(x / distance);

	if (y2 > y1)
	{
		angle = -angle;

		if (angle >= 2 * PI) angle -= 2 * PI;
	}
	//_cannon.cannonEnd.x = cosf(_cannon.angle) * _cannon.cannon + _cannon.center.x;
	//_cannon.cannonEnd.y = -sinf(_cannon.angle) * _cannon.cannon + _cannon.center.y;
	return angle;
}