#pragma once
int SceneState = 0;

const int LogoScene = 0;
const int MenuScene = 1;
const int InfoScene = 2;
const int ShopScene = 3;
const int MapScene = 4;
const int LoadScene = 5;
const int BattleScene = 6;
const int ExitScene = 7;

static int g_nScreenindex;;
static HANDLE g_hScreen[2];

int ShopMode = 0;

int LoadCount = 10;
int Loading = 0;


Object* Enemy[32] = { nullptr };

ULONGLONG EnemyTime = GetTickCount64();

Object* EnemyBullet[128] = { nullptr };

Vector3 EnemyBulletDirection[128];

Object* Item[32] = { nullptr };

Object* Boss[4] = { nullptr };

int Score = 0;

Object* Bullet[128] = { nullptr };
Object* BossBullet[128] = { nullptr };

Vector3 BossBulletDirection[128];
Vector3 ItemDirection[32];

bool Check = false;

int Countdown = 150;

bool crash = false;
bool crash2 = false;

// ** 초기화 함수 (디폴트 매개변수 : int _Value = 0)
void Initialize(Object* _Object, char* _Texture, float _PosX = 0.0f, float _PosY = 0.0f, float _PosZ = 0.0f, int _Hp = 1, int _Boom = 0, int _Mode = 1);

// ** 이름을 셋팅하는 함수
char* SetName();

// ** 커서의 위치를 변경
void SetCursorPosition(const float _x, const float _y);

// ** Text의 색을 변경함.
void SetTextColor(const int _Color);

// ** 출력할 Text의 위치와 색상을 변경해준다. [Color 값은 기본값 : 흰색(15)]
void OnDrawText(const char* _str, const float _x, const float _y, const int _Color = 15);

// ** 출력할 숫자의 위치와 색상을 변경해준다. [Color 값은 기본값 : 흰색(15)]
void OnDrawText(const int _Value, const float _x, const float _y, const int _Color = 15);

// ** 커서를 보이거나(true) / 안보이게(false) 만들어줌.
void HideCursor(const bool _Visible);

// ** 충돌처리를 함.
bool Collision(const Object* _ObjectA, const Object* _ObjectB);

Object* CreatBullet(const float _x, const float _y, const int _hp = 1);

Object* CreatEnemy(const float _x, const float _y, const int _hp = 1);

// ** 키입력 
void UpdateInput(Object* _Object);

// ** 거리를 구하는 함수
float GetDistance(const Object* _ObjectA, const Object* _ObjectB);

// ** 방향을 구하는 함수
Vector3 GetDirection(const Object* _ObjectA, const Object* _ObjectB);

Object* CreatBoss(const float _x, const float _y, const float _Scale_x, const int _hp);

Object* CreatItem(const float _x, const float _y, const int _mode);

void ScreenLint();

void ScreenFlipping();

void ScreenClear();

void ScreenRelease();

void ScreenPrint(const char* _Texture, const float _x, const float _y, const int _Color = 15);

void ScreenPrint(const int _Value, const float _x, const float _y, const int _Color = 15);

void SceneManager(Object* _Player, Object* _Cursor);

void LogoRender();

void SceneLogo();

void MenuRender(Object* _Cursor);

void SceneMenu(Object* _Player, Object* _Cursor);

void InfoRender(Object* _Player, Object* _Cursor);

void SceneInfo(Object* _Player, Object* _Cursor);

void ShopRender(Object* _Player, Object* _Cursor);

void ShopRender2(Object* _Player, Object* _Cursor);

void ShopRender3(Object* _Player, Object* _Cursor);

void ShopRender4(Object* _Player, Object* _Cursor);

void SceneShop(Object* _Player, Object* _Cursor);

void MapRender(Object* _Player, Object* _Cursor);

void SceneMap(Object* _Player, Object* _Cursor);

void LoadRender(Object* _Player, Object* _Cursor);

void LoadRender1(Object* _Player, Object* _Cursor);

void LoadRender2(Object* _Player, Object* _Cursor);

void LoadRender3(Object* _Player, Object* _Cursor);

void LoadRender4(Object* _Player, Object* _Cursor);

void LoadRender5(Object* _Player, Object* _Cursor);

void SceneLoad(Object* _Player, Object* _Cursor);

DrawTextInfo BackGroundInitialize(int _i);

void BattleRender(DrawTextInfo* _BackGround, Object* _Player, Object* _Cursor,
	Object* _Enemy[], Object* _Item[], Object* _Boss[],
	Object* _Bullet[], Object* _EnemyBullet[], Object* _BossBullet[],
	int _Countdown, int _Score);

void SceneBattle(Object* _Player, Object* _Cursorr);

// ** 함수 선언부
void Initialize(Object* _Object, char* _Texture, float _PosX, float _PosY, float _PosZ, int _Hp, int _Boom, int _Mode)
{
	// ** 3항 연상자. 
	// ** _Name 의 값이 nullptr 이라면  SetName() 함수를 실행하고 아니라면,
	// ** _Name의 값을 그대로 대입한다.
	_Object->Info.Texture = (_Texture == nullptr) ? SetName() : _Texture;

	// ** 이동속도 
	_Object->Speed = 0;

	// ** 좌표값
	_Object->TransInfo.Position = Vector3(_PosX, _PosY, _PosZ);

	// ** 회전값 (현재 사용되지 않음.)
	_Object->TransInfo.Rotation = Vector3(0, 0, 0);

	// ** 크기값
	_Object->TransInfo.Scale = Vector3(float(strlen(_Object->Info.Texture)), 1, 0);

	_Object->Time = GetTickCount64();

	_Object->Hp = _Hp;

	_Object->Boom = _Boom;

	_Object->Mode = _Mode;
}

char* SetName()
{
	// ** 문자열을 입력 받을 임시 변수를 배열로 생성한다. (포인터 변수에는 바로 입력받을수 없음.)
	char Buffer[128] = "";

	// ** 이름 입력
	cout << "입력 : "; cin >> Buffer;

	// ** 포인터 변수을 선언하여 입력받은 문자열의 길이만큼 크기를 할당함.
	//char* pName = (char*)malloc(strlen(Buffer) + 1);
	char* pName = new char[strlen(Buffer) + 1];

	// ** 입력받은 문자열의 내용을 복사함.
	strcpy(pName, Buffer);

	// ** 반환
	return pName;
}

void SetCursorPosition(const float _x, const float _y)
{
	COORD Pos = { (SHORT)_x, (SHORT)_y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	//SetConsoleCursorPosition(g_hScreen[g_nScreenindex], Pos);
}

void SetTextColor(const int _Color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _Color);
	SetConsoleTextAttribute(g_hScreen[g_nScreenindex], _Color);
}

void OnDrawText(const char* _str, const float _x, const float _y, const int _Color)
{
	/*
	DWORD dw;
	ScreenClear();
	*/

	SetCursorPosition(_x, _y);
	SetTextColor(_Color);
	cout << _str;

	/*
	WriteFile(g_hScreen[g_nScreenindex], _str, strlen(_str), &dw, NULL);
	ScreenFlipping();
	*/
}

void OnDrawText(const int _Value, const float _x, const float _y, const int _Color)
{
	/*
	DWORD dw;
	ScreenClear();
	*/

	SetCursorPosition(_x, _y);
	SetTextColor(_Color);

	char* pText = new char[4];
	_itoa(_Value, pText, 10);
	cout << _Value;

	/*
	char* temp = _itoa(_Value, pText, 10);

	WriteFile(g_hScreen[g_nScreenindex], temp, strlen(temp), &dw, NULL);
	ScreenFlipping();

	*/
}

void HideCursor(const bool _Visible)
{
	CONSOLE_CURSOR_INFO CursorInfo;

	CursorInfo.bVisible = _Visible;
	CursorInfo.dwSize = 1;

	SetConsoleCursorInfo(
		GetStdHandle(STD_OUTPUT_HANDLE), &CursorInfo);
}

bool Collision(const Object* _ObjectA, const Object* _ObjectB)
{
	if ((_ObjectA->TransInfo.Position.x + _ObjectA->TransInfo.Scale.x) > _ObjectB->TransInfo.Position.x &&
		(_ObjectB->TransInfo.Position.x + _ObjectB->TransInfo.Scale.x) > _ObjectA->TransInfo.Position.x &&
		(_ObjectA->TransInfo.Position.y + _ObjectA->TransInfo.Scale.y) >= _ObjectB->TransInfo.Position.y &&
		(_ObjectB->TransInfo.Position.y + _ObjectB->TransInfo.Scale.y) >= _ObjectA->TransInfo.Position.y)
		return true;
	return false;
}

Object* CreatBullet(const float _x, const float _y, const int _hp)
{
	Object* pBullet = new Object;
	Initialize(pBullet, (char*)"※", _x, _y, 0.0f, _hp);

	return pBullet;
}

Object* CreatEnemy(const float _x, const float _y, const int _hp)
{
	Object* _Object = new Object;
	Initialize(_Object, (char*)"훗", _x, _y, 0.0f, _hp, 0, (rand() % 4));

	return _Object;
}

void UpdateInput(Object* _Object)
{
	// ** [상] 키를 입력받음.
	if (GetAsyncKeyState(VK_UP))
		_Object->TransInfo.Position.y -= 1;

	// ** [하] 키를 입력받음.
	if (GetAsyncKeyState(VK_DOWN))
		_Object->TransInfo.Position.y += 1;

	// ** [좌] 키를 입력받음.
	if (GetAsyncKeyState(VK_LEFT))
		_Object->TransInfo.Position.x -= 1;

		// ** [우] 키를 입력받음.
	if (GetAsyncKeyState(VK_RIGHT))
		_Object->TransInfo.Position.x += 1;
}

float GetDistance(const Object* _ObjectA, const Object* _ObjectB)
{
	float x = _ObjectA->TransInfo.Position.x - _ObjectB->TransInfo.Position.x;
	float y = _ObjectA->TransInfo.Position.y - _ObjectB->TransInfo.Position.y;

	return  sqrt((x * x) + (y * y));
}

Vector3 GetDirection(const Object* _ObjectA, const Object* _ObjectB)
{
	float x = _ObjectA->TransInfo.Position.x - _ObjectB->TransInfo.Position.x;
	float y = _ObjectA->TransInfo.Position.y - _ObjectB->TransInfo.Position.y;

	float Distance = sqrt((x * x) + (y * y));

	return Vector3(x / Distance, y / Distance);
}

Object* CreatBoss(const float _x, const float _y, const float _Scale_x, const int _hp)
{
	Object* _Object = new Object;
	Initialize(_Object, (char*)"■■■■■", _x, _y, 0.0f, _hp);
	_Object->TransInfo.Scale.x = _Scale_x;
	_Object->TransInfo.Scale.y = 3;

	return _Object;
}

Object* CreatItem(const float _x, const float _y, const int _mode)
{
	Object* _Object = new Object;
	
	switch (_mode)
	{
	case 1:
		Initialize(_Object, (char*)"Boom", _x, _y);
		break;
	case 2:
		Initialize(_Object, (char*)"Power", _x, _y);
		break;
	case 3:
		Initialize(_Object, (char*)"옷/", _x, _y);
		break;		
	default:
		Initialize(_Object, (char*)" ", _x, _y);
		break;
	}

	_Object->Time = GetTickCount64();

	return _Object;
}

void ScreenLint()
{
	CONSOLE_CURSOR_INFO cci;
	g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	cci.dwSize = 1;
	cci.bVisible = false;
	SetConsoleCursorInfo(g_hScreen[0], &cci);
	SetConsoleCursorInfo(g_hScreen[1], &cci);
}

void ScreenFlipping()
{
	SetConsoleActiveScreenBuffer(g_hScreen[g_nScreenindex]);

	g_nScreenindex = !g_nScreenindex;
}

void ScreenClear()
{
	COORD Coor = { 0,0 };
	DWORD dw;
	FillConsoleOutputCharacter(g_hScreen[g_nScreenindex], ' ', 150 * 70, Coor, &dw);
}

void ScreenRelease()
{
	CloseHandle(g_hScreen[0]);
	CloseHandle(g_hScreen[1]);
}


void ScreenPrint(const char* _Texture, const float _x, const float _y, const int _Color)
{
	DWORD dw;
	COORD CursorPosition = { _x,_y };
	SetConsoleCursorPosition(g_hScreen[g_nScreenindex], CursorPosition);
	SetConsoleTextAttribute(g_hScreen[g_nScreenindex], _Color);
	WriteFile(g_hScreen[g_nScreenindex], _Texture, strlen(_Texture), &dw, NULL);
}

void ScreenPrint(const int _Value, const float _x, const float _y, const int _Color)
{
	DWORD dw;
	COORD CursorPosition = { _x,_y };
	char* pText = new char[4];
	SetConsoleCursorPosition(g_hScreen[g_nScreenindex], CursorPosition);
	SetConsoleTextAttribute(g_hScreen[g_nScreenindex], _Color);
	WriteFile(g_hScreen[g_nScreenindex], _itoa(_Value, pText, 10),
		strlen(_itoa(_Value, pText, 10)), &dw, NULL);
}

void SceneManager(Object* _Player, Object* _Cursor)
{
	ScreenFlipping();

	switch (SceneState)
	{
	case LogoScene:
		SceneLogo();
		break;
	case MenuScene:
		SceneMenu(_Player, _Cursor);
		break;
	case InfoScene:
		SceneInfo(_Player, _Cursor);
		break;
	case ShopScene:
		SceneShop(_Player, _Cursor);
		break;
	case MapScene:
		SceneMap(_Player, _Cursor);
		break;
	case LoadScene:
		SceneLoad(_Player, _Cursor);
		break;
	case BattleScene:
		SceneBattle(_Player, _Cursor);
		break;
	case ExitScene:
		exit(NULL);
		break;
	}
}
void LogoRender()
{
	ScreenClear();
	ScreenPrint((char*)"로고 들어갈 곳", 65.0f, 30.0f, 11);
	ScreenPrint((char*)"Space Bar를 눌러 시작", 60.0f, 55.0f);
}

void SceneLogo()
{
	LogoRender();
	if (GetAsyncKeyState(VK_SPACE))
		SceneState++;
}

void MenuRender(Object* _Cursor)
{
	ScreenClear();

	ScreenPrint((char*)"┌─────────────────┐", 50.0f, 17.0f);
	for (int i = 0; i < 14; i++)
	{
		ScreenPrint((char*)"│", 50.0f, float(18.0f + i));
		ScreenPrint((char*)"│", 86.0f, float(18.0f + i));
	}
	ScreenPrint((char*)"└─────────────────┘", 50.0f, 32.0f);

	ScreenPrint((char*)"1. 게임 시작", float(75 - strlen("1. 게임 시작")), 20.0f);
	ScreenPrint((char*)"2. 저장하기", float(75 - strlen("1. 게임 시작")), 23.0f);
	ScreenPrint((char*)"3. 불러오기", float(75 - strlen("1. 게임 시작")), 26.0f);
	ScreenPrint((char*)"4. 게임 종료", float(75 - strlen("1. 게임 시작")), 29.0f);
	ScreenPrint(_Cursor->Info.Texture, _Cursor->TransInfo.Position.x, _Cursor->TransInfo.Position.y);
}

void SceneMenu(Object* _Player, Object* _Cursor)
{	
	if (GetAsyncKeyState(VK_UP) && _Cursor->TransInfo.Position.y > 20.0f)
		_Cursor->TransInfo.Position.y -= 3;

	if (GetAsyncKeyState(VK_DOWN) && _Cursor->TransInfo.Position.y < 29.0f)
		_Cursor->TransInfo.Position.y += 3;

	if (GetAsyncKeyState(VK_RETURN))
	{
		switch (int(_Cursor->TransInfo.Position.y))
		{
		case 20:
			Initialize(_Cursor, (char*)"↖", 49.0f, 43.0f);
			SceneState = InfoScene;
			break;
		case 23:
			break;
		case 26:
			break;
		case 29:
			SceneState = ExitScene;
			break;
		}
	}
	MenuRender(_Cursor);
}

void InfoRender(Object* _Player, Object* _Cursor)
{
	ScreenClear();

	/*
	플레이어 정보
	*/

	for (int i = 0; i < 75; ++i)
	{
		ScreenPrint((char*)"─", float(0 + strlen("─")) * i + 0.5f, 40.0f);
	}
	ScreenPrint((char*)"상점 열기", 40.0f, 42.0f);
	ScreenPrint((char*)"출격 하기", 70.0f, 42.0f);
	ScreenPrint((char*)"메뉴 열기", 100.0f, 42.0f);

	ScreenPrint(_Cursor->Info.Texture, _Cursor->TransInfo.Position.x, _Cursor->TransInfo.Position.y);
}

void SceneInfo(Object* _Player, Object* _Cursor)
{
	if (GetAsyncKeyState(VK_LEFT) && _Cursor->TransInfo.Position.x > 49.0f)
		_Cursor->TransInfo.Position.x -= 30.0f;

	if (GetAsyncKeyState(VK_RIGHT) && _Cursor->TransInfo.Position.x < 109.0f)
		_Cursor->TransInfo.Position.x += 30.0f;

	if (GetAsyncKeyState(VK_RETURN))
	{
		switch (int(_Cursor->TransInfo.Position.x))
		{
		case 49:
			Initialize(_Cursor, (char*)"◁", 75.0f, 11.0f);
			ShopMode = 0;
			SceneState = ShopScene;
			break;
		case 79:
			SceneState = MapScene;
			break;
		case 109:
			Initialize(_Cursor, (char*)"▶", 63.0f, 20.0f);
			SceneState = MenuScene;
			break;
		}
	}
	InfoRender(_Player, _Cursor);
}

void ShopRender(Object* _Player, Object* _Cursor)
{
	ScreenClear();

	ScreenPrint((char*)"업그레이드 목록", 50.0f, 3.0f);

	ScreenPrint((char*)"┌────────────────────────────────┐", 20.0f, 7.0f);

	for (int i = 0; i < 44; i++)
	{
		ScreenPrint((char*)"│", 20.0f, float(8.0f + i));
		ScreenPrint((char*)"│", 86.0f, float(8.0f + i));
	}
	ScreenPrint((char*)"└────────────────────────────────┘", 20.0f, 52.0f);

	ScreenPrint((char*)"┌───┐", 23.0f, 5.0f);
	ScreenPrint((char*)"기지", 26.0f, 6.0f);
	ScreenPrint((char*)"│", 23.0f, 6.0f);
	ScreenPrint((char*)"│", 31.0f, 6.0f);
	ScreenPrint((char*)"┌───┐", 33.0f, 6.0f);
	ScreenPrint((char*)"┌───┐", 43.0f, 6.0f);

	ScreenPrint((char*)"업그레이드 1", 30.0f, 11.0f);
	ScreenPrint((char*)"업그레이드 2", 30.0f, 14.0f);
	ScreenPrint((char*)"업그레이드 3", 30.0f, 17.0f);
	ScreenPrint((char*)"업그레이드 4", 30.0f, 20.0f);
	ScreenPrint((char*)"업그레이드 5", 30.0f, 23.0f);
	ScreenPrint((char*)"업그레이드 6", 30.0f, 26.0f);
	ScreenPrint((char*)"업그레이드 7", 30.0f, 29.0f);
	ScreenPrint((char*)"업그레이드 8", 30.0f, 32.0f);
	ScreenPrint((char*)"업그레이드 9", 30.0f, 35.0f);

	ScreenPrint(_Cursor->Info.Texture, _Cursor->TransInfo.Position.x, _Cursor->TransInfo.Position.y);
}

void ShopRender2(Object* _Player, Object* _Cursor)
{
	ScreenClear();

	ScreenPrint((char*)"업그레이드 목록", 50.0f, 3.0f);

	ScreenPrint((char*)"┌────────────────────────────────┐", 20.0f, 7.0f);

	for (int i = 0; i < 44; i++)
	{
		ScreenPrint((char*)"│", 20.0f, float(8.0f + i));
		ScreenPrint((char*)"│", 86.0f, float(8.0f + i));
	}
	ScreenPrint((char*)"└────────────────────────────────┘", 20.0f, 52.0f);

	ScreenPrint((char*)"┌───┐", 23.0f, 6.0f);
	ScreenPrint((char*)"┌───┐", 33.0f, 5.0f);
	ScreenPrint((char*)"기체", 36.0f, 6.0f);
	ScreenPrint((char*)"│", 33.0f, 6.0f);
	ScreenPrint((char*)"│", 41.0f, 6.0f);
	ScreenPrint((char*)"┌───┐", 43.0f, 6.0f);

	ScreenPrint((char*)"업그레이드 1", 30.0f, 11.0f);
	ScreenPrint((char*)"업그레이드 2", 30.0f, 14.0f);
	ScreenPrint((char*)"업그레이드 3", 30.0f, 17.0f);
	ScreenPrint((char*)"업그레이드 4", 30.0f, 20.0f);
	ScreenPrint((char*)"업그레이드 5", 30.0f, 23.0f);
	ScreenPrint((char*)"업그레이드 6", 30.0f, 26.0f);
	ScreenPrint((char*)"업그레이드 7", 30.0f, 29.0f);
	ScreenPrint((char*)"업그레이드 8", 30.0f, 32.0f);
	ScreenPrint((char*)"업그레이드 9", 30.0f, 35.0f);

	ScreenPrint(_Cursor->Info.Texture, _Cursor->TransInfo.Position.x, _Cursor->TransInfo.Position.y);
}

void ShopRender3(Object* _Player, Object* _Cursor)
{
	ScreenClear();

	ScreenPrint((char*)"업그레이드 목록", 50.0f, 3.0f);

	ScreenPrint((char*)"┌────────────────────────────────┐", 20.0f, 7.0f);

	for (int i = 0; i < 44; i++)
	{
		ScreenPrint((char*)"│", 20.0f, float(8.0f + i));
		ScreenPrint((char*)"│", 86.0f, float(8.0f + i));
	}
	ScreenPrint((char*)"└────────────────────────────────┘", 20.0f, 52.0f);

	ScreenPrint((char*)"┌───┐", 23.0f, 6.0f);
	ScreenPrint((char*)"┌───┐", 33.0f, 6.0f);
	ScreenPrint((char*)"┌────┐", 43.0f, 5.0f);
	ScreenPrint((char*)"파일럿", 46.5f, 6.0f);
	ScreenPrint((char*)"│", 43.0f, 6.0f);
	ScreenPrint((char*)"│", 53.0f, 6.0f);

	ScreenPrint((char*)"업그레이드 1", 30.0f, 11.0f);
	ScreenPrint((char*)"업그레이드 2", 30.0f, 14.0f);
	ScreenPrint((char*)"업그레이드 3", 30.0f, 17.0f);
	ScreenPrint((char*)"업그레이드 4", 30.0f, 20.0f);
	ScreenPrint((char*)"업그레이드 5", 30.0f, 23.0f);
	ScreenPrint((char*)"업그레이드 6", 30.0f, 26.0f);
	ScreenPrint((char*)"업그레이드 7", 30.0f, 29.0f);
	ScreenPrint((char*)"업그레이드 8", 30.0f, 32.0f);
	ScreenPrint((char*)"업그레이드 9", 30.0f, 35.0f);

	ScreenPrint(_Cursor->Info.Texture, _Cursor->TransInfo.Position.x, _Cursor->TransInfo.Position.y);
}

void ShopRender4(Object* _Player, Object* _Cursor)
{
	ScreenClear();

	ScreenPrint((char*)"업그레이드 목록", 50.0f, 3.0f);

	ScreenPrint((char*)"┌────────────────────────────────┐", 20.0f, 7.0f);

	for (int i = 0; i < 44; i++)
	{
		ScreenPrint((char*)"│", 20.0f, float(8.0f + i));
		ScreenPrint((char*)"│", 86.0f, float(8.0f + i));
	}
	ScreenPrint((char*)"└────────────────────────────────┘", 20.0f, 52.0f);

	ScreenPrint((char*)"┌───┐", 23.0f, 6.0f);
	ScreenPrint((char*)"┌───┐", 33.0f, 6.0f);
	ScreenPrint((char*)"┌────┐", 43.0f, 5.0f);
	ScreenPrint((char*)"파일럿", 46.5f, 6.0f);
	ScreenPrint((char*)"│", 43.0f, 6.0f);
	ScreenPrint((char*)"│", 53.0f, 6.0f);

	ScreenPrint((char*)"업그레이드 1", 30.0f, 11.0f);
	ScreenPrint((char*)"업그레이드 2", 30.0f, 14.0f);
	ScreenPrint((char*)"업그레이드 3", 30.0f, 17.0f);
	ScreenPrint((char*)"업그레이드 4", 30.0f, 20.0f);
	ScreenPrint((char*)"업그레이드 5", 30.0f, 23.0f);
	ScreenPrint((char*)"업그레이드 6", 30.0f, 26.0f);
	ScreenPrint((char*)"업그레이드 7", 30.0f, 29.0f);
	ScreenPrint((char*)"업그레이드 8", 30.0f, 32.0f);
	ScreenPrint((char*)"업그레이드 9", 30.0f, 35.0f);

	ScreenPrint((char*)"종료", 120.0f, 50.0f);

	ScreenPrint(_Cursor->Info.Texture, _Cursor->TransInfo.Position.x, _Cursor->TransInfo.Position.y);
}
void SceneShop(Object* _Player, Object* _Cursor)
{
	if (GetAsyncKeyState(VK_UP) && _Cursor->TransInfo.Position.y > 11.0f)
		_Cursor->TransInfo.Position.y -= 3;

	if (GetAsyncKeyState(VK_DOWN) && _Cursor->TransInfo.Position.y < 35.0f)
		_Cursor->TransInfo.Position.y += 3;

	if (GetAsyncKeyState(VK_RIGHT) && ShopMode != 3)	
		++ShopMode;

	if (GetAsyncKeyState(VK_LEFT) && ShopMode != 0)
	{
		if (ShopMode == 3)
		{
			Initialize(_Cursor, (char*)"◁", 75.0f, 11.0f);
			--ShopMode;
		}
		else
			--ShopMode;
	}

	switch (ShopMode)
	{
	case 0:
		ShopRender(_Player, _Cursor);
		break;
	case 1:
		ShopRender2(_Player, _Cursor);
		break;
	case 2:
		ShopRender3(_Player, _Cursor);
		break;
	case 3:
		Initialize(_Cursor, (char*)"◁", 124.0f, 50.0f);
		ShopRender4(_Player, _Cursor);
		break;
	}

	if (GetAsyncKeyState(VK_RETURN) && ShopMode == 3)
	{
		Initialize(_Cursor, (char*)"↖", 49.0f, 43.0f);
		SceneState = InfoScene;
	}

}

void MapRender(Object* _Player, Object* _Cursor)
{
	ScreenClear();

	for (int i = 0; i < 50; ++i)
	{
		for (int j = 0; j < 130; ++j)
		{
			ScreenPrint((char*)"/", 10.0f + (float)j, 5.0f + (float)i, 10);
		}
	}

	for (int i = 0; i < 30; ++i)
	{
		for (int j = 0; j < 120; ++j)
		{
			ScreenPrint((char*)"/", 15.0f + (float)j, 10.0f + (float)i, 6);
		}
	}

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			ScreenPrint((char*)"/", 68.0f + (float)j, 28.0f + (float)i, 7);
			ScreenPrint((char*)"/", 66.0f, 29.0f, 7);
			ScreenPrint((char*)"/", 66.0f, 30.0f, 7);
			ScreenPrint((char*)"/", 67.0f, 29.0f, 7);
			ScreenPrint((char*)"/", 67.0f, 30.0f, 7);
			ScreenPrint((char*)"/", 76.0f, 29.0f, 7);
			ScreenPrint((char*)"/", 76.0f, 30.0f, 7);
			ScreenPrint((char*)"/", 77.0f, 29.0f, 7);
			ScreenPrint((char*)"/", 77.0f, 30.0f, 7);
		}
	}
	//ScreenPrint(_Cursor->Info.Texture, _Cursor->TransInfo.Position.x, _Cursor->TransInfo.Position.y);
}
void SceneMap(Object* _Player, Object* _Cursor)
{
	MapRender(_Player, _Cursor);
	if (GetAsyncKeyState(VK_SPACE))
		SceneState = LoadScene;
}

void LoadRender(Object* _Player, Object* _Cursor)
{
	ScreenClear();
	ScreenPrint((char*)"출격중", 74.0f, 25.0f);

	ScreenPrint((char*)"▷", 66.0f, 40.0f);
}

void LoadRender1(Object* _Player, Object* _Cursor)
{
	ScreenClear();
	ScreenPrint((char*)"출격중.", 74.0f, 25.0f);

	ScreenPrint((char*)"▷", 70.0f, 40.0f);
}

void LoadRender2(Object* _Player, Object* _Cursor)
{
	ScreenClear();
	ScreenPrint((char*)"출격중..", 74.0f, 25.0f);

	ScreenPrint((char*)"▷", 74.0f, 40.0f);
}

void LoadRender3(Object* _Player, Object* _Cursor)
{
	ScreenClear();
	ScreenPrint((char*)"출격중...", 74.0f, 25.0f);

	ScreenPrint((char*)"▷", 78.0f, 40.0f);
}

void LoadRender4(Object* _Player, Object* _Cursor)
{
	ScreenClear();
	ScreenPrint((char*)"출격중", 74.0f, 25.0f);

	ScreenPrint((char*)"▷", 82.0f, 40.0f);
}

void LoadRender5(Object* _Player, Object* _Cursor)
{
	ScreenClear();
	ScreenPrint((char*)"출격중", 74.0f, 25.0f);

	ScreenPrint((char*)"▷", 86.0f, 40.0f);
}

void SceneLoad(Object* _Player, Object* _Cursor)
{
	if (_Player->Time + 200 < GetTickCount64())
	{
		_Player->Time = GetTickCount64();
		--LoadCount;
		++Loading;
		if (Loading == 6)
			Loading = 0;
	}
	if (LoadCount == 0)
		SceneState = BattleScene;

	switch (Loading)
	{
	case 0:
		LoadRender(_Player, _Cursor);
		break;
	case 1:
		LoadRender1(_Player, _Cursor);
		break;
	case 2:
		LoadRender2(_Player, _Cursor);
		break;
	case 3:
		LoadRender3(_Player, _Cursor);
		break;
	case 4:
		LoadRender4(_Player, _Cursor);
		break;
	case 5:
		LoadRender5(_Player, _Cursor);
		break;
	}
}

DrawTextInfo BackGroundInitialize(int _i)
{
	// ** 배경 초기화.
	DrawTextInfo BackGround;

	// ** 랜덤값을 초기화 해줌. 큰 값이 나올수 있도록 Time값끼리 곱해줄 것이지만, 
	// ** for문이 빠르게 돌게되면 Time의 증가값보다 빠를수 있기때문에,
	// ** 랜덤값이라고 하더라도 연속으로 같은 값이 나올수 있음.
	// ** i의 값을 곱하고 더해줌으로써 같은 값이 나오지 않도록 해줌.
	srand((GetTickCount() + _i * _i) * GetTickCount());

	// ** 현재 어떻게 사용할지 정하지 않았지만, 추후 배경과 총알을 구분지어 플레이어가 배경과 다았을때에는 충돌하지 않고,
	// ** 총알과 다았을 때에만 충돌판정이 되도록 설정해줄 것임.
	BackGround.Info.Option = 0;

	// ** 좌표를 랜덤으로 설정함.
	BackGround.TransInfo.Position.x = float(rand() % 100 + 10);
	BackGround.TransInfo.Position.y = float(rand() % 50 + 1);

	// ** 배경으로 사용될 텍스처를 설정.
	BackGround.Info.Texture = (char*)"*";

	// ** 배경으로 사용될 텍스처의 색상을 랜덤으로 설정.
	BackGround.Info.Color = rand() % 8 + 1;

	return BackGround;
}

void BattleRender(DrawTextInfo* _BackGround, Object* _Player, Object* _Cursor,
	Object* _Enemy[], Object* _Item[], Object* _Boss[],
	Object* _Bullet[], Object* _EnemyBullet[], Object* _BossBullet[],
	int _Countdown, int _Score)
{
	ScreenClear();

	// ** 배경 출력
	for (int i = 0; i < 30; ++i)
	{
		ScreenPrint(
			_BackGround[i].Info.Texture,
			_BackGround[i].TransInfo.Position.x,
			_BackGround[i].TransInfo.Position.y,
			_BackGround[i].Info.Color);
	}

	for (int i = 0; i < 32; ++i)
	{
		if (_Enemy[i] != nullptr)
		{
			ScreenPrint(_Enemy[i]->Info.Texture,
				_Enemy[i]->TransInfo.Position.x,
				_Enemy[i]->TransInfo.Position.y,
				12);
		}
	}

	for (int i = 0; i < 128; ++i)
	{
		if (_EnemyBullet[i] != nullptr)
		{
			ScreenPrint(_EnemyBullet[i]->Info.Texture,
				_EnemyBullet[i]->TransInfo.Position.x,
				_EnemyBullet[i]->TransInfo.Position.y);
		}
	}
	for (int i = 0; i < 128; ++i)
	{
		if (_Bullet[i] != nullptr)
		{
			ScreenPrint(_Bullet[i]->Info.Texture,
				_Bullet[i]->TransInfo.Position.x,
				_Bullet[i]->TransInfo.Position.y);
		}
	}

	if (_Boss[0]!= nullptr)
	{
		for (int i = 0; i < 128; ++i)
		{
			if (_BossBullet[i] != nullptr)
			{
				ScreenPrint(_BossBullet[i]->Info.Texture,
					_BossBullet[i]->TransInfo.Position.x,
					_BossBullet[i]->TransInfo.Position.y);
			}
		}

		ScreenPrint((char*)"[", 10.0f, 4.0f, 3);
		ScreenPrint((char*)"]", 12.0f + _Boss[0]->Hp, 4.0f, 3);

		for (int i = 0; i < _Boss[0]->Hp; ++i)
		{
			ScreenPrint((char*)"/", 11.0f + i, 4.0f, 12);
		}

		ScreenPrint(_Boss[0]->Info.Texture, _Boss[0]->TransInfo.Position.x - 3.0f, _Boss[0]->TransInfo.Position.y - 1.0f, 11);
		ScreenPrint(_Boss[0]->Info.Texture, _Boss[0]->TransInfo.Position.x - 3.0f, _Boss[0]->TransInfo.Position.y, 11);
		ScreenPrint(_Boss[0]->Info.Texture, _Boss[0]->TransInfo.Position.x - 3.0f, _Boss[0]->TransInfo.Position.y + 1.0f, 11);
		ScreenPrint(_Boss[0]->Info.Texture, _Boss[0]->TransInfo.Position.x - 3.0f, _Boss[0]->TransInfo.Position.y + 2.0f, 11);
	}

	for (int i = 0; i < 32; i++)
	{

		if (_Item[i]!= nullptr)
		{
			ScreenPrint(_Item[i]->Info.Texture, _Item[i]->TransInfo.Position.x, _Item[i]->TransInfo.Position.y, 13);
		}
	}

	ScreenPrint(_Player->Info.Texture,
		_Player->TransInfo.Position.x,
		_Player->TransInfo.Position.y,
		10);

	ScreenPrint((char*)"남은 시간 : ", float(60 - strlen("남은 시간 : ")), 1.0f);
	ScreenPrint(_Countdown, 60.0f, 1.0f);

	ScreenPrint((char*)"Score : ", float(60 - strlen("Score : ")), 2.0f);
	ScreenPrint(_Score, 60.0f, 2.0f);

	for (int i = 0; i < _Player->Hp; ++i)
	{
		ScreenPrint(_Player->Info.Texture, (2.0f * i) + 0.5f, 59.0f);
	}
	for (int i = 0; i < _Player->Boom; ++i)
	{
		ScreenPrint((char*)"Boom", (4.0f * i) + 0.5f, 58.0f);
	}
}

void SceneBattle(Object* _Player, Object* _Cursor)
{
	DrawTextInfo BackGround[30];
	for (int i = 0; i < 30; ++i)
	{
		BackGround[i] = BackGroundInitialize(i);
	}

	int BattleHelper = 1;

	if (EnemyTime + 1500 < GetTickCount64())
	{
		EnemyTime = GetTickCount64();

		for (int i = 0; i < 32; ++i)
		{
			if (Enemy[i] == nullptr)
			{
				srand((GetTickCount64() + i * i) * GetTickCount64());

				Enemy[i] = CreatEnemy(float(rand() % 100), 1.0f);

				break;
			}

			for (int j = 0; j < 128; ++j)
			{
				if (EnemyBullet[j] == nullptr && (Enemy[i]->Time + ((rand() % 15) * 100)) < GetTickCount64())
				{
					EnemyBullet[j] = CreatBullet(
						Enemy[i]->TransInfo.Position.x,
						Enemy[i]->TransInfo.Position.y + 1.0f);

					EnemyBulletDirection[j] = GetDirection(_Player, Enemy[i]);
					Enemy[i]->Time = GetTickCount64();

					break;
				}
			}
		}
	}

	if (Countdown == 120)
	{
		for (int i = 0; i < 4; ++i)
			Boss[i] = CreatBoss(50.0f, 10.0f, 5.0f, 100 * (i + 1));;
	}
	if (Boss[0])
	{
		for (int i = 0; i < 128; ++i)
		{
			if (BossBullet[i] == nullptr && Boss[0]->Time + 1000 < GetTickCount64())
			{
				BossBullet[i] = CreatBullet(
					Boss[0]->TransInfo.Position.x + (float)(rand() % 6),
					Boss[0]->TransInfo.Position.y + 2.0f);

				BossBulletDirection[i] = GetDirection(_Player, Boss[0]);
				Boss[0]->Time = GetTickCount64();

				break;
			}
		}
	}

	for (int i = 0; i < 128; ++i)
	{
		if (Bullet[i] != nullptr)
		{
			for (int j = 0; j < 32; ++j)
			{
				if (Enemy[j] != nullptr)
				{

					if (Collision(Bullet[i], Enemy[j]))
					{
						Enemy[j]->Hp = Enemy[j]->Hp - Bullet[i]->Hp;
						delete Bullet[i];
						Bullet[i] = nullptr;

						if (Enemy[j]->Hp <= 0)
						{
							if (Item[j] == nullptr)
							{
								Item[j] = CreatItem(Enemy[j]->TransInfo.Position.x,
									Enemy[j]->TransInfo.Position.y, Enemy[j]->Mode);
								ItemDirection[j] = GetDirection(_Player, Item[j]);
							}
						}

						delete Enemy[j];
						Enemy[j] = nullptr;

						++Score;

						break;
					}
				}

			}

			if (Boss[0] != nullptr)
				if (Bullet[i] != nullptr)
				{
					if (Collision(Bullet[i], Boss[0]))
					{
						delete Bullet[i];
						Bullet[i] = nullptr;

						--Boss[0]->Hp;
						if (Boss[0]->Hp <= 0)
						{
							delete Boss[0];
							Boss[0] = nullptr;

							system("cls");
							OnDrawText((char*)"클리어!!", 50, 30, 10);

							Initialize(_Cursor, (char*)"◀", 63.0f, 7.0f);
							SceneState = MenuScene;
						}
						break;
					}
				}

			if (Bullet[i] != nullptr)
				if (Bullet[i]->TransInfo.Position.y < 0)
				{
					delete Bullet[i];
					Bullet[i] = nullptr;
				}
		}

		if (EnemyBullet[i] != nullptr)
		{
			if (Collision(EnemyBullet[i], _Player))
			{
				delete EnemyBullet[i];
				EnemyBullet[i] = nullptr;

				--_Player->Hp;

				if (_Player->Hp == 0)
				{
					Initialize(_Cursor, (char*)"◀", 63.0f, 7.0f);
					SceneState = MenuScene;
					BattleHelper = 0;
				}
				break;
			}

			if (EnemyBullet[i] != nullptr)
				if (EnemyBullet[i]->TransInfo.Position.y >= 60 || EnemyBullet[i]->TransInfo.Position.y <= 0 ||
					EnemyBullet[i]->TransInfo.Position.x >= 98 || EnemyBullet[i]->TransInfo.Position.x < 0)
				{
					delete EnemyBullet[i];
					EnemyBullet[i] = nullptr;
				}
		}

		if (BossBullet[i] != nullptr)
		{
			if (Collision(BossBullet[i], _Player))
			{
				delete BossBullet[i];
				BossBullet[i] = nullptr;

				--_Player->Hp;

				if (_Player->Hp == 0)
				{
					Initialize(_Cursor, (char*)"◀", 63.0f, 7.0f);
					SceneState = MenuScene;
					BattleHelper = 0;
				}

				break;
			}

			if (BossBullet[i] != nullptr)
				if (BossBullet[i]->TransInfo.Position.y >= 60 || BossBullet[i]->TransInfo.Position.y <= 0 ||
					BossBullet[i]->TransInfo.Position.x >= 98 || BossBullet[i]->TransInfo.Position.x < 0)
				{
					delete BossBullet[i];
					BossBullet[i] = nullptr;
				}
		}
	}

	for (int i = 0; i < 32; ++i)
	{
		if (Item[i] != nullptr)
		{
			if (Collision(Item[i], _Player))
			{
				if (Item[i]->Info.Texture == (char*)"Boom")
				{
					if (_Player->Boom < 3)
						++_Player->Boom;
				}
				if (Item[i]->Info.Texture == (char*)"Power")
				{
					if (_Player->Mode < 3)
						++_Player->Mode;
				}
				if (Item[i]->Info.Texture == (char*)"옷/")
				{
					if (_Player->Hp < 3)
						++_Player->Hp;
				}
				delete Item[i];
				Item[i] = nullptr;

				crash = false;
				crash2 = false;
			}
			if (Item[i] != nullptr)
			{
				if (Item[i]->TransInfo.Position.y > 60 || Item[i]->TransInfo.Position.y < 0 ||
					Item[i]->TransInfo.Position.x > 100 || Item[i]->TransInfo.Position.x < 0)
				{
					delete Item[i];
					Item[i] = nullptr;

					crash = false;
					crash2 = false;
				}
			}
		}
	}

	UpdateInput(_Player);

	if (GetAsyncKeyState(VK_SPACE))
	{
		if (_Cursor->Time + 200 < GetTickCount64())
		{
			_Cursor->Time = GetTickCount64();
			switch (_Player->Mode)
			{
			case 1:

				for (int i = 0; i < 128; ++i)
				{
					if (Bullet[i] == nullptr)
					{
						Bullet[i] = CreatBullet(
							_Player->TransInfo.Position.x,
							_Player->TransInfo.Position.y - 1.0f);

						break;
					}
				}
				break;
			case 2:

				for (int i = 0; i < 64; ++i)
				{
					if (Bullet[i] == nullptr && Bullet[i + 1] == nullptr)
					{
						Bullet[i] = CreatBullet(
							_Player->TransInfo.Position.x - 1.0f,
							_Player->TransInfo.Position.y - 1.0f);
						Bullet[i + 1] = CreatBullet(
							_Player->TransInfo.Position.x + 1.0f,
							_Player->TransInfo.Position.y - 1.0f);
						break;
					}
				}
				break;
			case 3:
				for (int i = 0; i < 32; ++i)
				{
					if (Bullet[i] == nullptr && Bullet[i + 1] == nullptr &&
						Bullet[i + 2] == nullptr && Bullet[i + 3] == nullptr)

					{
						Bullet[i] = CreatBullet(
							_Player->TransInfo.Position.x - 1.0f,
							_Player->TransInfo.Position.y + 2.0f);
						Bullet[i + 1] = CreatBullet(
							_Player->TransInfo.Position.x + 1.0f,
							_Player->TransInfo.Position.y + 2.0f);
						Bullet[i + 2] = CreatBullet(
							_Player->TransInfo.Position.x - 3.0f,
							_Player->TransInfo.Position.y + 2.0f);
						Bullet[i + 3] = CreatBullet(
							_Player->TransInfo.Position.x + 3.0f,
							_Player->TransInfo.Position.y + 2.0f);
						break;
					}
				}
				break;
			}
		}
	}

	if (_Player->Boom)
	{
		if (!Check && GetAsyncKeyState(0x58) & 0x0001)
		{
			Check = true;
		}

		if (Check && !(GetAsyncKeyState(0x58) & 0x8000))
		{

			for (int i = 0; i < 32; ++i)
			{
				if (Enemy[i])
				{
					if (Item[i] == nullptr)
					{
						Item[i] = CreatItem(Enemy[i]->TransInfo.Position.x,
							Enemy[i]->TransInfo.Position.y, Enemy[i]->Mode);
						ItemDirection[i] = GetDirection(_Player, Item[i]);
					}

					delete Enemy[i];
					Enemy[i] = nullptr;
					++Score;
				}
			}

			for (int i = 0; i < 128; ++i)
			{
				if (EnemyBullet[i])
				{
					delete EnemyBullet[i];
					EnemyBullet[i] = nullptr;
				}
			}

			for (int i = 0; i < 128; ++i)
			{
				if (BossBullet[i])
				{
					delete BossBullet[i];
					BossBullet[i] = nullptr;

				}
			}

			if (Boss[0])
			{
				Boss[0]->Hp -= 10;

				if (Boss[0]->Hp <= 0)
				{
					delete Boss[0];
					Boss[0] = nullptr;

					system("cls");
					OnDrawText((char*)"클리어!!", 50, 30, 10);

					SceneState = MenuScene;
					BattleHelper = 0;

				}
			}

			--_Player->Boom;
			Check = false;
		}
	}

	for (int i = 0; i < 128; ++i)
	{
		if (Bullet[i] != nullptr)
		{
			Bullet[i]->TransInfo.Position.y -= 2;
		}
	}
	for (int i = 0; i < 128; ++i)
	{
		if (BossBullet[i] != nullptr)
		{
			BossBullet[i]->TransInfo.Position.x += BossBulletDirection[i].x * 2.0f;
			BossBullet[i]->TransInfo.Position.y += BossBulletDirection[i].y * 1.5f;
		}
	}
	for (int i = 0; i < 32; ++i)
	{
		if (Enemy[i] != nullptr)
		{
			Enemy[i]->TransInfo.Position.y += 0.5f;

			if (Enemy[i]->TransInfo.Position.y >= 60)
			{
				delete Enemy[i];
				Enemy[i] = nullptr;
			}
		}
	}
	for (int i = 0; i < 128; ++i)
	{
		if (EnemyBullet[i])
		{
			EnemyBullet[i]->TransInfo.Position.x += EnemyBulletDirection[i].x * 2.0f;
			EnemyBullet[i]->TransInfo.Position.y += EnemyBulletDirection[i].y * 1.5f;
		}
	}

	for (int i = 0; i < 32; i++)
	{
		if (Item[i])
		{
			if (Item[i]->TransInfo.Position.y <= 3 || Item[i]->TransInfo.Position.y >= 57)
				crash = !crash;

			if (Item[i]->TransInfo.Position.x <= 3 || Item[i]->TransInfo.Position.x >= 97)
				crash2 = !crash2;

			if (crash == true)
			{
				Item[i]->TransInfo.Position.x += ItemDirection[i].x * 3.0f;
				Item[i]->TransInfo.Position.y += ItemDirection[i].y * -1.5f;
			}
			if (crash2 == true)
			{
				Item[i]->TransInfo.Position.x += ItemDirection[i].x * -3.0f;
				Item[i]->TransInfo.Position.y += ItemDirection[i].y * 1.5f;
			}
			if (crash == false && crash2 == false)
			{
				Item[i]->TransInfo.Position.x += ItemDirection[i].x * 3.0f;
				Item[i]->TransInfo.Position.y += ItemDirection[i].y * 1.5f;
			}
		}
	}

	if (_Player->Time + 1000 < GetTickCount64())
	{
		_Player->Time = GetTickCount64();
		--Countdown;
	}

	BattleRender(BackGround, _Player, _Cursor, Enemy, Item, Boss,
		Bullet, EnemyBullet, BossBullet, Countdown, Score);

}