#pragma once

//����� ȯ��(�������� �����ϰ�, �� Ű�� ������ ȣ�� �ϵ��� ����.)

class Inventory
{
private:
	image * inven;//�κ��丮 �̹��� �ҷ�����
	image * arrow;//ȭ��ǥ ���� �ҷ�����
	RECT arrow_rc;//�κ��丮 ������ ��Ʈ�� �� ��Ʈ �� ����
public:
	Inventory();
	~Inventory();

	//===================���� ����====================
	bool tab_key_check;//�⺻ false�� �ʱ�ȭ �ϰ�, true �϶��� �����ֱ�
	int tab_key_cnt;//�⺻ 0���� �ʱ�ȭ ���ְ�, Ȧ �� ��° �϶��� ������ֱ�

	//===================�Լ� ����====================
	HRESULT init();
	//�κ��丮 �̹����� ȣ���غ���
	void render(HDC hdc);
	void tab_key_control();//Ű�� �Ǻ��� ���⼭ ������
};

