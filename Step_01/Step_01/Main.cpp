// ** Framework v0.8.6.7
#include"Headers.h"

// ** �浹, �Ÿ� ���ϱ� �ʼ��� �ֱ�
// ** 22�ϱ��� �ϼ����� �켱 ���

int main(void)
{

	// ** Ŀ���� �Ⱥ��̰� �������.
	HideCursor(false);
	
	
	system("mode con:cols=150 lines=60");

	// ** �÷��̾� ���� �� �����Ҵ�.
	Object* Player = new Object;

	// ** �÷��̾� �ʱ�ȭ
	Initialize(Player, (char*)"��/", 50.0f, 50.0f, 0.0f, 3, 3);

	Object* Cursor = new Object;

	Initialize(Cursor, (char*)"��", 63.0f, 7.0f);

	ScreenLint();

	// ** ���� �ð����� �ʱ�ȭ.
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

			SceneManager(Player, Cursor);					
		}
	}
	delete Player;
	delete Cursor;			

	Release();
	ScreenRelease();

	return 0;
}

// ** Ű �Է�

/*
if (!Check && GetAsyncKeyState(VK_SPACE) & 0x0001)
{
	Power = 0;
	test++;
	Check = true;
}

// ** ��ư�� ������ ������
if (GetAsyncKeyState(VK_SPACE) & 0x8000)
{
	if (Power < 10)
	{
		Power++;
	}
}

// ** ��ư�� ������ ���� ����.
if (Check && !(GetAsyncKeyState(VK_SPACE) & 0x8000))
{
	Temp[test] = new Object;

	Temp[test]->TransInfo.Position.x = float(rand() % 100);
	Temp[test]->TransInfo.Position.y = 1;

	Temp[test]->Info.Texture = (char*)"��";

	Temp[test]->Speed = Power;

	// ** Temp�� Player�� �̵��ϱ� ���� ������ �޾ƿ�.
	Direction = GetDirection(Player, Temp[test]);

	Check = false;
}
*/

/*
OnDrawText((char*)"[          ]", 1.0f, 28.0f);

for (int i = 0; i < Power; ++i)
{
	OnDrawText((char*)"/", 2.0f + i, 28.0f);
}
*/

/*
for (int i = 0; i < 128; i++)
{
	// ** Temp ���
	if (Temp[i])
	{
		OnDrawText(Temp[i]->Info.Texture,
			Temp[i]->TransInfo.Position.x,
			Temp[i]->TransInfo.Position.y,
			12);

		// ** �ش� �������� �̵���.
		Temp[i]->TransInfo.Position.x += Direction.x * Temp[i]->Speed;
		Temp[i]->TransInfo.Position.y += Direction.y * Temp[i]->Speed;

		// ** �Ÿ��� ���.
		OnDrawText((char*)"Length : ", float(60 - strlen("Score : ")), 2.0f);
		OnDrawText((int)GetDistance(Player, Temp[i]), 60.0f, 2.0f);

		if (Temp[i]->TransInfo.Position.y >= 50)
		{
			--test;
			delete Temp[i];
			Temp[i] = nullptr;
		}
	}
}
*/