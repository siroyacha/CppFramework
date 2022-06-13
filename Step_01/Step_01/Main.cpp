// ** Framework v0.8.6.7
#include"Headers.h"

// ** 충돌, 거리 구하기 필수로 넣기
// ** 22일까지 완성으로 우선 계산

int main(void)
{

	// ** 커서를 안보이게 만들어줌.
	HideCursor(false);
	
	
	system("mode con:cols=150 lines=60");

	// ** 플레이어 선언 및 동적할당.
	Object* Player = new Object;

	// ** 플레이어 초기화
	Initialize(Player, (char*)"옷/", 50.0f, 50.0f, 0.0f, 3, 3);

	Object* Cursor = new Object;

	Initialize(Cursor, (char*)"◀", 63.0f, 7.0f);

	ScreenLint();

	// ** 현재 시간으로 초기화.
	ULONGLONG Time = GetTickCount64();
	// ** 출력
	while (true)
	{
		// ** 초기화된 시간으로부터 +50 만큼 증가하면...
		// ** (프레임과 프레임사이의 시간 간격을 0.5초로 셋팅)
		if (Time + 50 < GetTickCount64())
		{
			// ** 증가된 값만큼 다시 초기화.
			Time = GetTickCount64();

			// ** 콘솔창 버퍼 전체 삭제
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

// ** 키 입력

/*
if (!Check && GetAsyncKeyState(VK_SPACE) & 0x0001)
{
	Power = 0;
	test++;
	Check = true;
}

// ** 버튼을 누르고 있을때
if (GetAsyncKeyState(VK_SPACE) & 0x8000)
{
	if (Power < 10)
	{
		Power++;
	}
}

// ** 버튼을 누르지 않은 상태.
if (Check && !(GetAsyncKeyState(VK_SPACE) & 0x8000))
{
	Temp[test] = new Object;

	Temp[test]->TransInfo.Position.x = float(rand() % 100);
	Temp[test]->TransInfo.Position.y = 1;

	Temp[test]->Info.Texture = (char*)"★";

	Temp[test]->Speed = Power;

	// ** Temp가 Player로 이동하기 위해 방향을 받아옴.
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
	// ** Temp 출력
	if (Temp[i])
	{
		OnDrawText(Temp[i]->Info.Texture,
			Temp[i]->TransInfo.Position.x,
			Temp[i]->TransInfo.Position.y,
			12);

		// ** 해당 방향으로 이동함.
		Temp[i]->TransInfo.Position.x += Direction.x * Temp[i]->Speed;
		Temp[i]->TransInfo.Position.y += Direction.y * Temp[i]->Speed;

		// ** 거리를 출력.
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