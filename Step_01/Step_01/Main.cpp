// ** Framework v0.9
#include"Headers.h"

// ** �浹, �Ÿ� ���ϱ� �ʼ��� �ֱ�
// ** 22�ϱ��� �ϼ����� �켱 ���

int main(void)
{
	// ** Ŀ���� �Ⱥ��̰� �������.
	HideCursor(false);

	system("mode con:cols=150 lines=60");

	Object* Player = new Object;

	Initialize(Player, (char*)"��/", 75.0f, 50.0f, 0.0f, 3, 3);

	Object* Cursor = new Object;

	Initialize(Cursor, (char*)"��", 63.0f, 20.0f);

	UI_Object* UIObject = new UI_Object;

	Initialize_UI(UIObject);

	ScreenLint();

	ULONGLONG Time = GetTickCount64();
	// ** ���
	while (true)
	{
		// ** �ʱ�ȭ�� �ð����κ��� +50 ��ŭ �����ϸ�...
		// ** (�����Ӱ� �����ӻ����� �ð� ������ 0.5�ʷ� ����)
		if (Time + 50 < GetTickCount64())
		{
			// ** ������ ����ŭ �ٽ� �ʱ�ȭ.
			Time = GetTickCount64();

			// ** �ܼ�â ���� ��ü ����
			system("cls");

			SceneManager(Player, Cursor, UIObject);
		}
	}
	delete Player;
	delete Cursor;			

	ScreenRelease();

	return 0;
}
