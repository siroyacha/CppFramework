// ** Framework v0.3
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<Windows.h>

using namespace std;


typedef struct tagVector3
{
	int x = 0, y = 0, z = 0;

	tagVector3() {};

	tagVector3(int _x, int _y)
		: x(_x), y(_y), z(0) {};

	tagVector3(int _x, int _y, int _z)
		: x(_x), y(_y), z(_z) {};

}Vector3;

struct Transform
{
	Vector3 Position;
	Vector3 Rotation;
	Vector3 Scale;
};

struct Info
{
	char* Texture;
	int Color;
	int Option;
};

struct Object
{
	char* Name;
	int Speed;

	Info Info;
	Transform TransInfo;
};

struct DrawTextInfo
{
	Info Info;
	Transform TransInfo;

};

// ** �ʱ�ȭ �Լ�
void Initialize(Object* _Object, char* _Texture, int _PosX = 0, int _PosY = 0, int _PosZ = 0);

// ** �̸� ���� �Լ�
char* SetName();

// ** Ŀ�� ��ġ ����
void SetCursorPosition(int _x, int _y);

// ** Text�� ����
void SetTextColor(int _Color);

// ** ����� Text�� ��ġ�� ���� ����. [Color�� �⺻���� ���:15]
void OnDrawText(char* _str, int _x, int _y, int _Color = 15);

// ** ����� ������ ��ġ�� ���� ����. [Color�� �⺻���� ���:15]
void OnDrawText(int _Value, int _x, int _y, int _Color = 15);

// ** Ŀ���� ���̰ų�(true)/�Ⱥ��̰�(false) �������
void HideCursor(bool _Visivle);

// ** ��� �Լ�
void Output(Object* _Obj);

int main(void)
{
	HideCursor(false);

	DrawTextInfo BackGround[30];

	for (int i = 0; i < 30; i++)
	{
		srand((GetTickCount() + i * i) * GetTickCount());

		BackGround[i].Info.Option = 0;

		BackGround[i].TransInfo.Position.x = rand() % 100 + 10;
		BackGround[i].TransInfo.Position.y = rand() % 26 + 1;

		BackGround[i].Info.Texture = (char*)"*";
		BackGround[i].Info.Color = rand() % 8 + 9;		
	}

	Object* Player = new Object;
	Initialize(Player, (char*)"��", 30, 10);

	Object* Enemy = new Object;
	Initialize(Enemy, (char*)"��", 80, 10);

	ULONGLONG Time = GetTickCount64();
	int Score = 0;
	while (true)
	{
		if (Time + 100 < GetTickCount64())
		{
			Time = GetTickCount64();

			system("cls");
			
			for (int i = 0; i < 30; i++)
			{
				for (int j = 0; j < 30; j++)
				{
					OnDrawText(BackGround[i].Info.Texture,
						BackGround[i].TransInfo.Position.x,
						BackGround[i].TransInfo.Position.y,
						BackGround[i].Info.Color);
				
					BackGround[i].Info.Color = rand() % 8 + 9;
				}
			}

			if (GetAsyncKeyState(VK_UP))
				Player->TransInfo.Position.y -= 1;

			if (GetAsyncKeyState(VK_DOWN))
				Player->TransInfo.Position.y += 1;

			if (GetAsyncKeyState(VK_LEFT))
				Player->TransInfo.Position.x -= 1;

			if (GetAsyncKeyState(VK_RIGHT))
				Player->TransInfo.Position.x += 1;

			if (GetAsyncKeyState(VK_SPACE))
			{
				OnDrawText((char*)"��ǳ!!",
					Player->TransInfo.Position.x + strlen(Player->Info.Texture) + 1,
					Player->TransInfo.Position.y,
					13);
			}

			OnDrawText(Player->Info.Texture,
				Player->TransInfo.Position.x,
				Player->TransInfo.Position.y,
				10);


			OnDrawText(Enemy->Info.Texture,
				Enemy->TransInfo.Position.x,
				Enemy->TransInfo.Position.y,
				12);

			int ix = 60 - strlen("Score : ");
			OnDrawText((char*)"Score : ", ix, 1);
			OnDrawText(++Score, ix + strlen("Score : "), 1);

		}
	}


	return 0;
}

// ** �Լ� ���Ǻ�

void Initialize(Object* _Object, char* _Texture, int _PosX, int _PosY, int _PosZ)
{
	_Object->Info.Texture = (_Texture == nullptr) ? SetName() : _Texture;
	_Object->Speed = 0;
	_Object->TransInfo.Position = Vector3(_PosX, _PosY, _PosZ);
	_Object->TransInfo.Rotation = Vector3(0, 0, 0);
	_Object->TransInfo.Scale = Vector3(0, 0, 0);
}

char* SetName()
{
	char Buffer[128]="";
	
	cout << "�Է� : "; cin >> Buffer;
	
	//char pName = (char*)malloc(strlen(Buffer) + 1);
	char* pName = new char[strlen(Buffer) + 1];

	strcpy(pName, Buffer);

	return pName;
}

void SetCursorPosition(int _x, int _y)
{
	COORD Pos = { (SHORT)_x,(SHORT)_y };

	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void SetTextColor(int _Color)
{
	SetConsoleTextAttribute(
		GetStdHandle(STD_OUTPUT_HANDLE), _Color);
}

void OnDrawText(char* _str, int _x, int _y, int _Color)
{
	SetCursorPosition(_x, _y);
	SetTextColor(_Color);
	cout << _str;
}

void OnDrawText(int _Value, int _x, int _y, int _Color)
{
	SetCursorPosition(_x, _y);
	SetTextColor(_Color);

	char* pText = new char[4];
	_itoa(_Value, pText, 10);

	cout << _Value;
}

void HideCursor(bool _Visivle)
{
	CONSOLE_CURSOR_INFO CursorInfo;
	
	CursorInfo.bVisible = _Visivle;
	CursorInfo.dwSize = 1;

	SetConsoleCursorInfo(
		GetStdHandle(STD_OUTPUT_HANDLE), &CursorInfo);
}

void Output(Object* _Obj)
{
}