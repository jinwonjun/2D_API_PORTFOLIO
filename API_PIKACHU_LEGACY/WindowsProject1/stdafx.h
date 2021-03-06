// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include<iostream>


//자주 사용하는 STL
#include<string>
//#include<map>
//#include<vector>
//#include<list>
using namespace std;

//내가 만든 헤더는 요기에 추가/////
#include"commonMacroFunction.h"
#include"keyManager.h"
#include "randomFunction.h"
//====================================
//			싱글톤 요기에 ㅋㅋ
//====================================
#define KEYMANAGER keyManager::getSingleton()

#define  RND randomFunction::getSingleton()

//====================================
			//디파인문 선언
//====================================

#define WINNAME (LPTSTR)(TEXT("PIKACHU-CHRONICLE"))
#define WINSTARTX 100
#define WINSTARTY 30
#define WINSIZEX 400
#define WINSIZEY 650
#define WINSTYLE WS_CAPTION | WS_SYSMENU


#define SAFE_DELETE(p)				{if(p) {delete	 (p);   (p)=NULL;}}
#define SAFE_DELETE_ARRAY(p)		{if(p) {delete[] (p);   (p)=NULL;}}
#define SAFE_RELEASE(p)				{if(p)  {(p)->release();(p)=NULL;}}


//////////////////extern//////////////
extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT ptMouse;
// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
//========= 한글 부분헤더 ==========
#include <wchar.h>
//#include "atlbase.h"  
//#include "atlstr.h"  
//#include "comutil.h" 
//========= 이미지 부분헤더 ==========
#include "image.h"
//========= 씬 관련 부분헤더 ==========
#include "Game_Opening.h"//게임 오프닝 헤더
#include "Field_1.h"//필드_1 헤더
#include "Field_2.h"//필드_2 헤더
#include "Silver_Mountain.h"//필드_3 헤더
//========= 캐릭터 부분헤더 ==========
#include "mainCharacter.h"
#include "Pika_Comment.h"//피카츄 코멘트 부분을 클래스로 묶어서 필요할때마다 호출시키자
//========= NPC 부분헤더 ==========
#include "npc_dr_o.h"

//========= 전투처리 부분헤더 ==========
#include "battle_scene.h"
//========= 인벤토리 관련 헤더 =========
#include "Inventory.h"

#define BOSS_HP_MAX 80
#define PIKA_HP_MAX 5000
#define PIKA_SPEED 2.0f//피카츄 무브먼트 속도 컨트롤
#define SILVER_MOUNTAIN_SCROLL 5.0f//맵스크롤 조절용도
#define PIKA_COL_SPEED 6.0f//피카츄 끼임탈출용 컨트롤
#define PI 3.141592654//파이는 파이지 뭐야