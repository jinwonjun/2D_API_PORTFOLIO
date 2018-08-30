#pragma once
class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,	//리소스 로딩
		LOAD_FILE,			//파일로딩
		LOAD_EMPTY,			//빈 비트맵 파일
		LOAD_END		
	};

	typedef struct tagImage
	{
		DWORD		resID;		//리소스 아이디
		HDC			hMemDC;		//메모리 DC
		HBITMAP		hBit;		//비트맵(새로운 비트맵 핸들)
		HBITMAP		hOBit;		//올드 비트맵(기존 비트맵 핸들)

		float x;				//이미지의 x좌표
		float y;				//이미지의  y좌표
		int width;		//이미지 가로크기
		int	height;		//세로
		int currentFrameX;//현재 프레임 x
		int currentFrameY;//현재 프레임 y
		int maxFrameX;//최대 프레임 갯수
		int maxFrameY;//

		int frameWidth;//1프레임의 가로길이
		int frameHeight;//1프레임의 세로길이
		BYTE		loadType;		//타입


		tagImage()
		{
			resID = 0;
			hMemDC = nullptr;
			hBit = nullptr;
			hOBit = nullptr;

			x = 0; 
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}

	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO m_imageInfo;//이미지 정보
	char*		 m_fileName;//이미지 이름
	bool		 m_isTrans;//배경 날릴꺼냐
	COLORREF	 m_transColor;//배경색 없앨 RGB




public:
	image();
	~image();
	//빈 비트맵 초기화
	HRESULT init( int width, int height );
	//이미지 리소스 초기화
	HRESULT init( const DWORD resID, int width, int height, bool isTrans = false, COLORREF transColor = RGB( 255, 0, 255 ) );
	//이미지 파일 초기화
	HRESULT init( const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB( 255, 0, 255 ) );
	HRESULT init(const char* fileName, int x, int y, int width, int height, int frameX, int frameY, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	//프레임 이미지 파일로 초기화
	HRESULT init(const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));






	//투명키 세팅
	void setTransColor( bool isTrans, COLORREF transColor );

	//릴리즈
	void release();

	//그리는 녀석
	void render( HDC hdc );
	void render( HDC hdc, int destX, int destY );

	//프레임 렌더
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY , BYTE alpha);




	//DC를 얻어온다
	inline HDC getMemDC() { return m_imageInfo->hMemDC; }
	//이미지 좌표 x값 얻기
	inline float getX() { return m_imageInfo->x; }
	inline void setX(float x) { m_imageInfo->x = x; }

	inline float getY() { return m_imageInfo->y; }
	inline void setY(float y) { m_imageInfo->y = y; }
	//이미지 센터 좌표 셋팅
	inline void setCenter(float x, float y)
	{
		m_imageInfo->x = x - (m_imageInfo->width / 2);
		m_imageInfo->y = y - (m_imageInfo->height / 2);

	}
	//가로 세로 크기 얻기
	inline int getWidth() { return m_imageInfo->width; }
	inline int getHeight() { return m_imageInfo->height; }
	//바운딩 박스 (충돌용)
	inline RECT getBoundingBox()
	{
		RECT rc = RectMakeCenter(m_imageInfo->x, m_imageInfo->y, m_imageInfo->width, m_imageInfo->height);
			return rc;
	}

	//프레임 X셋팅하기
	inline int getFrameX() { return m_imageInfo->currentFrameX; }
	inline void setFrameX(int frameX)
	{
		m_imageInfo->currentFrameX = frameX;
		if (frameX > m_imageInfo->maxFrameX)
		{
			m_imageInfo->currentFrameX = m_imageInfo->maxFrameX;
		}
	}
	//프레임 Y 셋팅하기
	inline int getFrameY() { return m_imageInfo->currentFrameY; }
	inline void setFrameY(int frameY)
	{
		m_imageInfo->currentFrameY = frameY;
		if (frameY > m_imageInfo->maxFrameY)
		{
			m_imageInfo->currentFrameY = m_imageInfo->maxFrameY;
		}
	}
	//1프레임 가로 세로 크기
	inline int getFrameWidth() { return m_imageInfo->frameWidth; }
	inline int getFrameHeight() { return m_imageInfo->frameHeight; }
	//맥스 프레임
	inline int getMaxFrameX() { return m_imageInfo->maxFrameX; }
	inline int getMaxFrameY() { return m_imageInfo->maxFrameY; }

};

