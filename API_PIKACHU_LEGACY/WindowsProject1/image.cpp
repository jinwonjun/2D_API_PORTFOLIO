#include "stdafx.h"

//����

/*
	1.���� : ������ ������ ���ս� �������̹Ƿ� �ӵ��� ���� ����
	2.jpg : �ս� �����̹Ƿ� ���� ���� �̹����� �ս��� �Ͼ�� ��ſ�
	��� �˰��� ���� ������ �Ǿ� �뷮�� ����
	3.png : �� �γ�� �޸� ���İ��� ����.(alpha : ������)
*/

image::image()
	:m_imageInfo( nullptr )
	, m_fileName( nullptr )
	, m_isTrans( NULL )
	, m_transColor( RGB( 0, 0, 0 ) )
{
}


image::~image()
{
}

HRESULT image::init( int width, int height )
{
	//���ʱ�ȭ ������, �̹��� ������ ���� �ִٸ� ����� ���ٰ�.
	if ( m_imageInfo != nullptr )release();
	//DC��������(���� �����쿡 ���� ȭ�� DC�� �ӽ������� �޾ƿ�)
	HDC hdc = GetDC( _hWnd );
	//CreateCompatibleDC
	//��Ʈ���� ����ϱ� ���� �޸� dc�� ������ִ� �Լ�
	//CreateCompatibleBitmap
	//���� DC�� ȣȯ�Ǵ� ��Ʈ���� ������ �ִ� �Լ�
	//SelectObject
	//������ ��Ʈ�� �ڵ��� ��ȯ�ϰ� ���ο� ��Ʈ���� �޸� DC�� �����ϰ�
	//�޸� DC�� ��Ʈ���� �׷���/

	//�̹��� ������ ��������
	m_imageInfo = new IMAGE_INFO;
	m_imageInfo->loadType = LOAD_EMPTY;
	m_imageInfo->resID = 0;
	m_imageInfo->hMemDC = CreateCompatibleDC( hdc );
	m_imageInfo->hBit = ( HBITMAP ) CreateCompatibleBitmap( hdc, width, height );
	m_imageInfo->hOBit = ( HBITMAP ) SelectObject( m_imageInfo->hMemDC, m_imageInfo->hBit );
	m_imageInfo->width = width;
	m_imageInfo->height = height;
	//���� �̸�
	m_fileName = nullptr;

	//����Ű �÷�����
	m_isTrans = false;
	m_transColor = RGB( 0, 0, 0 );

	//���ҽ��� �����µ� ���� ������
	if ( m_imageInfo->hBit == 0 )
	{
		release();
		return E_FAIL;
	}


	//DC����
	ReleaseDC( _hWnd, hdc );

	return S_OK;
}

HRESULT image::init( const DWORD resID, int width, int height, bool isTrans, COLORREF transColor )
{
	if ( m_imageInfo != nullptr )release();
	//DC��������(���� �����쿡 ���� ȭ�� DC�� �ӽ������� �޾ƿ�)
	HDC hdc = GetDC( _hWnd );
	//CreateCompatibleDC
	//��Ʈ���� ����ϱ� ���� �޸� dc�� ������ִ� �Լ�
	//CreateCompatibleBitmap
	//���� DC�� ȣȯ�Ǵ� ��Ʈ���� ������ �ִ� �Լ�
	//SelectObject
	//������ ��Ʈ�� �ڵ��� ��ȯ�ϰ� ���ο� ��Ʈ���� �޸� DC�� �����ϰ�
	//�޸� DC�� ��Ʈ���� �׷���/

	//�̹��� ������ ��������
	m_imageInfo = new IMAGE_INFO;
	m_imageInfo->loadType = LOAD_RESOURCE;
	m_imageInfo->resID = resID;
	m_imageInfo->hMemDC = CreateCompatibleDC( hdc );
	m_imageInfo->hBit = ( HBITMAP ) LoadBitmap( _hInstance, MAKEINTRESOURCE( m_imageInfo->resID ) );//������ ��Ʈ�ʿ� �ø�
	m_imageInfo->hOBit = ( HBITMAP ) SelectObject( m_imageInfo->hMemDC, m_imageInfo->hBit );
	m_imageInfo->width = width;
	m_imageInfo->height = height;

	//���� �̸�
	m_fileName = nullptr;

	//����Ű �÷�����
	m_isTrans = isTrans;
	m_transColor = transColor;

	//���ҽ��� �����µ� ���� ������
	if ( m_imageInfo->hBit == 0 )
	{
		release();
		return E_FAIL;
	}
	//DC����
	ReleaseDC( _hWnd, hdc );

	return S_OK;
}

HRESULT image::init( const char * fileName, int width, int height, bool isTrans, COLORREF transColor )
{
	if ( m_imageInfo != nullptr )release();
	//DC��������(���� �����쿡 ���� ȭ�� DC�� �ӽ������� �޾ƿ�)
	HDC hdc = GetDC( _hWnd );
	//CreateCompatibleDC
	//��Ʈ���� ����ϱ� ���� �޸� dc�� ������ִ� �Լ�
	//CreateCompatibleBitmap
	//���� DC�� ȣȯ�Ǵ� ��Ʈ���� ������ �ִ� �Լ�
	//SelectObject
	//������ ��Ʈ�� �ڵ��� ��ȯ�ϰ� ���ο� ��Ʈ���� �޸� DC�� �����ϰ�
	//�޸� DC�� ��Ʈ���� �׷���/

	//�̹��� ������ ��������
	m_imageInfo = new IMAGE_INFO;
	m_imageInfo->loadType = LOAD_FILE;
	m_imageInfo->resID = 0;
	m_imageInfo->hMemDC = CreateCompatibleDC( hdc );
	m_imageInfo->hBit = ( HBITMAP ) LoadImage( _hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE );

	m_imageInfo->hOBit = ( HBITMAP ) SelectObject( m_imageInfo->hMemDC, m_imageInfo->hBit );
	m_imageInfo->width = width;
	m_imageInfo->height = height;

	//���� �̸�
	int len = strlen( fileName );
	m_fileName = new char[len + 1];
	strcpy_s( m_fileName, len + 1, fileName );


	//����Ű �÷�����
	m_isTrans = isTrans;
	m_transColor = transColor;

	//���ҽ��� �����µ� ���� ������
	if ( m_imageInfo->hBit == 0 )
	{
		release();
		return E_FAIL;
	}
	//DC����
	ReleaseDC( _hWnd, hdc );

	return S_OK;
}

HRESULT image::init(const char * fileName, int x, int y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	if (m_imageInfo != nullptr)release();
	//DC��������(���� �����쿡 ���� ȭ�� DC�� �ӽ������� �޾ƿ�)
	HDC hdc = GetDC(_hWnd);
	//CreateCompatibleDC
	//��Ʈ���� ����ϱ� ���� �޸� dc�� ������ִ� �Լ�
	//CreateCompatibleBitmap
	//���� DC�� ȣȯ�Ǵ� ��Ʈ���� ������ �ִ� �Լ�
	//SelectObject
	//������ ��Ʈ�� �ڵ��� ��ȯ�ϰ� ���ο� ��Ʈ���� �޸� DC�� �����ϰ�
	//�޸� DC�� ��Ʈ���� �׷���/

	//�̹��� ������ ��������
	m_imageInfo = new IMAGE_INFO;
	m_imageInfo->loadType = LOAD_FILE;
	m_imageInfo->resID = 0;
	m_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	m_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);

	m_imageInfo->hOBit = (HBITMAP)SelectObject(m_imageInfo->hMemDC, m_imageInfo->hBit);
	m_imageInfo->x = x - (width / frameX / 2);
	m_imageInfo->y = y - (height / frameY / 2);
	m_imageInfo->width = width;
	m_imageInfo->height = height;
	m_imageInfo->maxFrameX = frameX - 1;
	m_imageInfo->maxFrameY = frameY - 1;
	m_imageInfo->frameWidth = width / frameX;
	m_imageInfo->frameHeight = height / frameY;

	//���� �̸�
	int len = strlen(fileName);
	m_fileName = new char[len + 1];
	strcpy_s(m_fileName, len + 1, fileName);


	//����Ű �÷�����
	m_isTrans = isTrans;
	m_transColor = transColor;

	//���ҽ��� �����µ� ���� ������
	if (m_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}
	//DC����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	if (m_imageInfo != nullptr)release();
	//DC��������(���� �����쿡 ���� ȭ�� DC�� �ӽ������� �޾ƿ�)
	HDC hdc = GetDC(_hWnd);
	//CreateCompatibleDC
	//��Ʈ���� ����ϱ� ���� �޸� dc�� ������ִ� �Լ�
	//CreateCompatibleBitmap
	//���� DC�� ȣȯ�Ǵ� ��Ʈ���� ������ �ִ� �Լ�
	//SelectObject
	//������ ��Ʈ�� �ڵ��� ��ȯ�ϰ� ���ο� ��Ʈ���� �޸� DC�� �����ϰ�
	//�޸� DC�� ��Ʈ���� �׷���/

	//�̹��� ������ ��������
	m_imageInfo = new IMAGE_INFO;
	m_imageInfo->loadType = LOAD_FILE;
	m_imageInfo->resID = 0;
	m_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	m_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);

	m_imageInfo->hOBit = (HBITMAP)SelectObject(m_imageInfo->hMemDC, m_imageInfo->hBit);
	m_imageInfo->width = width;
	m_imageInfo->height = height;
	m_imageInfo->maxFrameX = frameX - 1;
	m_imageInfo->maxFrameY = frameY - 1;
	m_imageInfo->frameWidth = width / frameX;
	m_imageInfo->frameHeight = height / frameY;
	
	//���� �̸�
	int len = strlen(fileName);
	m_fileName = new char[len + 1];
	strcpy_s(m_fileName, len + 1, fileName);


	//����Ű �÷�����
	m_isTrans = isTrans;
	m_transColor = transColor;

	//���ҽ��� �����µ� ���� ������
	if (m_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}
	//DC����
	ReleaseDC(_hWnd, hdc);

	return S_OK;

}

void image::setTransColor( bool isTrans, COLORREF transColor )
{
	m_isTrans = isTrans;
	m_transColor = transColor;
}

void image::release()
{
	//�̹��� ������ ���� �ִٸ� ����� ����
	if ( m_imageInfo )
	{
		SelectObject( m_imageInfo->hMemDC, m_imageInfo->hBit );
		DeleteObject( m_imageInfo->hOBit );
		DeleteDC( m_imageInfo->hMemDC );

		SAFE_DELETE( m_imageInfo );
		SAFE_DELETE( m_fileName );

		m_isTrans = false;
		m_transColor = RGB( 0, 0, 0 );

	}
}

void image::render( HDC hdc )
{
	//���� ���ٲ���
	if ( m_isTrans )
	{
		//GdiTransparentBlt :��Ʈ���� �ҷ��ö� Ư������ �����ϰ� �����ϴ� �Լ�
		GdiTransparentBlt(
			hdc,				//����� ����� DC
			0,					//����� ��ǥ�� ������ X
			0,					//����� ��ǥ�� ������ Y
			m_imageInfo->width, //����� �̹����� ����ũ��
			m_imageInfo->height,//����� �̹����� ����ũ��
			m_imageInfo->hMemDC,//����� ��� DC
			0,					//���� �������� X
			0,					//���� �������� Y
			m_imageInfo->width,	//���� ���� ����ũ��
			m_imageInfo->height,//���� ���� ����ũ��
			m_transColor);		//�����Ҷ� ������ ����
	}
	//�����̹��� �״�� �̾Ƴ�����
	else
	{
		//SRCCOPY : �������ִ� ��, ���μ��θ� ������ �ؼ� ������.
		//DC�� �������� ��Ӻ��� �ϴ� �༮
		BitBlt( hdc, 0, 0, m_imageInfo->width, m_imageInfo->height,
			m_imageInfo->hMemDC, 0, 0, SRCCOPY );
	}
}

void image::render( HDC hdc, int destX, int destY )
{
	//���� ���ٲ���
	if ( m_isTrans )
	{
		//GdiTransparentBlt :��Ʈ���� �ҷ��ö� Ư������ �����ϰ� �����ϴ� �Լ�
		GdiTransparentBlt(
			hdc,				//����� ����� DC
			destX,					//����� ��ǥ�� ������ X
			destY,					//����� ��ǥ�� ������ Y
			m_imageInfo->width, //����� �̹����� ����ũ��
			m_imageInfo->height,//����� �̹����� ����ũ��
			m_imageInfo->hMemDC,//����� ��� DC
			0,					//���� �������� X
			0,					//���� �������� Y
			m_imageInfo->width,	//���� ���� ����ũ��
			m_imageInfo->height,//���� ���� ����ũ��
			m_transColor );		//�����Ҷ� ������ ����
	}
	//�����̹��� �״�� �̾Ƴ�����
	else
	{
		//SRCCOPY : �������ִ� ��, ���μ��θ� ������ �ؼ� ������.
		//DC�� �������� ��Ӻ��� �ϴ� �༮
		BitBlt( hdc, destX, destY, m_imageInfo->width, m_imageInfo->height,
			m_imageInfo->hMemDC, 0, 0, SRCCOPY );
	}
}

void image::frameRender(HDC hdc, int destX, int destY)
{
	//���� ���ٲ���
	if (m_isTrans)
	{
		//GdiTransparentBlt :��Ʈ���� �ҷ��ö� Ư������ �����ϰ� �����ϴ� �Լ�
		GdiTransparentBlt(
			hdc,				//����� ����� DC
			destX,					//����� ��ǥ�� ������ X
			destY,					//����� ��ǥ�� ������ Y
			m_imageInfo->frameWidth, //����� �̹����� ����ũ��
			m_imageInfo->frameHeight, //����� �̹����� ����ũ��
			m_imageInfo->hMemDC,//����� ��� DC
			m_imageInfo->currentFrameX * m_imageInfo->frameWidth,	//���� �������� X
			m_imageInfo->currentFrameY * m_imageInfo->frameHeight,	//���� �������� Y
			m_imageInfo->frameWidth,	//���� ���� ����ũ��
			m_imageInfo->frameHeight,//���� ���� ����ũ��
			m_transColor);		//�����Ҷ� ������ ����
	}
	//�����̹��� �״�� �̾Ƴ�����
	else
	{
		//SRCCOPY : �������ִ� ��, ���μ��θ� ������ �ؼ� ������.
		//DC�� �������� ��Ӻ��� �ϴ� �༮
		BitBlt(hdc, destX, destY, m_imageInfo->frameWidth, m_imageInfo->frameHeight,
			m_imageInfo->hMemDC, m_imageInfo->currentFrameX * m_imageInfo->frameWidth, m_imageInfo->currentFrameY * m_imageInfo->frameHeight,  SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{

	m_imageInfo->currentFrameX = currentFrameX;
	m_imageInfo->currentFrameY = currentFrameY;
	//�ʱ�ȭ�κ�
	if (currentFrameX > m_imageInfo->maxFrameX)
	{
		m_imageInfo->currentFrameX = m_imageInfo->maxFrameX;
	}
	if (currentFrameY > m_imageInfo->maxFrameY)
	{
		m_imageInfo->currentFrameY = m_imageInfo->maxFrameY;
	}

	//���� ���ٲ���
	if (m_isTrans)
	{
		//GdiTransparentBlt :��Ʈ���� �ҷ��ö� Ư������ �����ϰ� �����ϴ� �Լ�
		GdiTransparentBlt(
			hdc,				//����� ����� DC
			destX,					//����� ��ǥ�� ������ X
			destY,					//����� ��ǥ�� ������ Y
			m_imageInfo->frameWidth, //����� �̹����� ����ũ��
			m_imageInfo->frameHeight, //����� �̹����� ����ũ��
			m_imageInfo->hMemDC,//����� ��� DC
			currentFrameX * m_imageInfo->frameWidth,	//���� �������� X
			currentFrameY * m_imageInfo->frameHeight,	//���� �������� Y
			m_imageInfo->frameWidth,	//���� ���� ����ũ��
			m_imageInfo->frameHeight,//���� ���� ����ũ��
			m_transColor);		//�����Ҷ� ������ ����
	}
	//�����̹��� �״�� �̾Ƴ�����
	else
	{
		//SRCCOPY : �������ִ� ��, ���μ��θ� ������ �ؼ� ������.
		//DC�� �������� ��Ӻ��� �ϴ� �༮
		BitBlt(hdc, destX, destY, m_imageInfo->frameWidth, m_imageInfo->frameHeight,
			m_imageInfo->hMemDC, currentFrameX * m_imageInfo->frameWidth, currentFrameY * m_imageInfo->frameHeight, SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	m_imageInfo->currentFrameX = currentFrameX;
	m_imageInfo->currentFrameY = currentFrameY;
	//�ʱ�ȭ�κ�
	if (currentFrameX > m_imageInfo->maxFrameX)
	{
		m_imageInfo->currentFrameX = m_imageInfo->maxFrameX;
	}
	if (currentFrameY > m_imageInfo->maxFrameY)
	{
		m_imageInfo->currentFrameY = m_imageInfo->maxFrameY;
	}



}
