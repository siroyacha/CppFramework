// ** Framework v0.9
#include"Headers.h"

// ** 충돌, 거리 구하기 필수로 넣기
// ** 22일까지 완성으로 우선 계산

int main(void)
{
	// ** 커서를 안보이게 만들어줌.
	HideCursor(false);

	system("mode con:cols=150 lines=60");

	Object* Player = new Object;

	Initialize(Player, (char*)"옷/", 75.0f, 50.0f, 0.0f, 3, 3);

	Object* Cursor = new Object;

	Initialize(Cursor, (char*)"▶", 63.0f, 20.0f);

	UI_Object* UIObject = new UI_Object;

	Initialize_UI(UIObject);

	ScreenLint();

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

			SceneManager(Player, Cursor, UIObject);
		}
	}
	delete Player;
	delete Cursor;			

	ScreenRelease();

	return 0;
}
