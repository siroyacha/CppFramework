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

// ������� �׽�Ʈ
static int g_nScreenindex;
static HANDLE g_hScreen[2];

clock_t CurTime, OldTime;
char* FPSTextInfo = new char[256];

// ** �ʱ�ȭ �Լ� (����Ʈ �Ű����� : int _Value = 0)
void Initialize(Object* _Object, char* _Texture, float _PosX = 0.0f, float _PosY = 0.0f, float _PosZ = 0.0f, int _Hp = 1, int _Boom = 0, int _Mode = 1);

// ** �̸��� �����ϴ� �Լ�
char* SetName();

// ** Ŀ���� ��ġ�� ����
void SetCursorPosition(const float _x, const float _y);

// ** Text�� ���� ������.
void SetTextColor(const int _Color);

// ** ����� Text�� ��ġ�� ������ �������ش�. [Color ���� �⺻�� : ���(15)]
void OnDrawText(const char* _str, const float _x, const float _y, const int _Color = 15);

// ** ����� ������ ��ġ�� ������ �������ش�. [Color ���� �⺻�� : ���(15)]
void OnDrawText(const int _Value, const float _x, const float _y, const int _Color = 15);

// ** Ŀ���� ���̰ų�(true) / �Ⱥ��̰�(false) �������.
void HideCursor(const bool _Visible);

// ** �浹ó���� ��.
bool Collision(const Object* _ObjectA, const Object* _ObjectB);

Object* CreatBullet(const float _x, const float _y, const int _hp = 1);

Object* CreatEnemy(const float _x, const float _y, const int _hp = 1);

// ** Ű�Է� 
void UpdateInput(Object* _Object);

// ** �Ÿ��� ���ϴ� �Լ�
float GetDistance(const Object* _ObjectA, const Object* _ObjectB);

// ** ������ ���ϴ� �Լ�
Vector3 GetDirection(const Object* _ObjectA, const Object* _ObjectB);

Object* CreatBoss(const float _x, const float _y, const float _Scale_x, const int _hp);

Object* CreatItem(const float _x, const float _y, const int _mode);

void ScreenLint();

void ScreenFlipping();

void ScreenClear();

void ScreenRelease();

/*
void ScreenPrint(int x, int y, char* string);

void Render();
*/

void Release();

DrawTextInfo BackGroundInitialize(int _i);

void SceneManager(Object* _Player, Object* _Cursor);

void SceneLogo();

void SceneMenu(Object* _Player, Object* _Cursor);

void SceneInfo(Object* _Player, Object* _Cursor);

void SceneShop(Object* _Player, Object* _Cursor);

void SceneMap(Object* _Player, Object* _Cursor);

void SceneLoad(Object* _Player, Object* _Cursor);

void SceneBattle(Object* _Player, Object* _Cursorr);

// ** �Լ� �����
void Initialize(Object* _Object, char* _Texture, float _PosX, float _PosY, float _PosZ, int _Hp, int _Boom, int _Mode)
{
	// ** 3�� ������. 
	// ** _Name �� ���� nullptr �̶��  SetName() �Լ��� �����ϰ� �ƴ϶��,
	// ** _Name�� ���� �״�� �����Ѵ�.
	_Object->Info.Texture = (_Texture == nullptr) ? SetName() : _Texture;

	// ** �̵��ӵ� 
	_Object->Speed = 0;

	// ** ��ǥ��
	_Object->TransInfo.Position = Vector3(_PosX, _PosY, _PosZ);

	// ** ȸ���� (���� ������ ����.)
	_Object->TransInfo.Rotation = Vector3(0, 0, 0);

	// ** ũ�Ⱚ
	_Object->TransInfo.Scale = Vector3(float(strlen(_Object->Info.Texture)), 1, 0);

	_Object->Time = GetTickCount64();

	_Object->Hp = _Hp;

	_Object->Boom = _Boom;

	_Object->Mode = _Mode;
}

char* SetName()
{
	// ** ���ڿ��� �Է� ���� �ӽ� ������ �迭�� �����Ѵ�. (������ �������� �ٷ� �Է¹����� ����.)
	char Buffer[128] = "";

	// ** �̸� �Է�
	cout << "�Է� : "; cin >> Buffer;

	// ** ������ ������ �����Ͽ� �Է¹��� ���ڿ��� ���̸�ŭ ũ�⸦ �Ҵ���.
	//char* pName = (char*)malloc(strlen(Buffer) + 1);
	char* pName = new char[strlen(Buffer) + 1];

	// ** �Է¹��� ���ڿ��� ������ ������.
	strcpy(pName, Buffer);

	// ** ��ȯ
	return pName;
}

void SetCursorPosition(const float _x, const float _y)
{
	COORD Pos = { (SHORT)_x, (SHORT)_y };

	SetConsoleCursorPosition(g_hScreen[g_nScreenindex], Pos);
}

void SetTextColor(const int _Color)
{
	SetConsoleTextAttribute(
		GetStdHandle(STD_OUTPUT_HANDLE), _Color);
}

void OnDrawText(const char* _str, const float _x, const float _y, const int _Color)
{
	DWORD dw;

	SetCursorPosition(_x, _y);
	SetTextColor(_Color);

	WriteFile(g_hScreen[g_nScreenindex], _str, strlen(_str), &dw, NULL);
}

void OnDrawText(const int _Value, const float _x, const float _y, const int _Color)
{
	DWORD dw;

	SetCursorPosition(_x, _y);
	SetTextColor(_Color);

	char* pText = new char[4];

	char* temp = _itoa(_Value, pText, 10);

	WriteFile(g_hScreen[g_nScreenindex], temp, strlen(temp), &dw, NULL);
}

/*
void Render()
{
	ScreenClear();
	if (CurTime - OldTime >= 1000)
	{
		sprintf(FPSTextInfo, "FPS : %d\n");
		OldTime = CurTime;
	}

	ScreenPrint(0, 0, FPSTextInfo);
	ScreenFlipping();
}

void ScreenPrint(int x, int y, char* string)
{
	DWORD dw;
	COORD CursorPosition = { x,y };
	SetConsoleCursorPosition(g_hScreen[g_nScreenindex], CursorPosition);
	WriteFile(g_hScreen[g_nScreenindex], string, strlen(string), &dw, NULL);
}
*/

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
	Initialize(pBullet, (char*)"��", _x, _y, 0.0f, _hp);

	return pBullet;
}

Object* CreatEnemy(const float _x, const float _y, const int _hp)
{
	Object* _Object = new Object;
	Initialize(_Object, (char*)"��", _x, _y, 0.0f, _hp, 0, (rand() % 4));

	return _Object;
}

void UpdateInput(Object* _Object)
{
	// ** [��] Ű�� �Է¹���.
	if (GetAsyncKeyState(VK_UP))
		_Object->TransInfo.Position.y -= 1;

	// ** [��] Ű�� �Է¹���.
	if (GetAsyncKeyState(VK_DOWN))
		_Object->TransInfo.Position.y += 1;

	// ** [��] Ű�� �Է¹���.
	if (GetAsyncKeyState(VK_LEFT))
		_Object->TransInfo.Position.x -= 1;

	// ** [��] Ű�� �Է¹���.
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
	Initialize(_Object, (char*)"������", _x, _y, 0.0f, _hp);
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
		Initialize(_Object, (char*)"��/", _x, _y);
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
	FillConsoleOutputCharacter(g_hScreen[g_nScreenindex], ' ', 120 * 60, Coor, &dw);
}
void ScreenRelease()
{
	CloseHandle(g_hScreen[0]);
	CloseHandle(g_hScreen[1]);
}
void Release()
{
	delete[] FPSTextInfo;
}

void SceneManager(Object* _Player, Object* _Cursor)
{
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
		system("mode con:cols=150 lines=60");
		SceneMap(_Player, _Cursor);
		break;
	case BattleScene:
		system("mode con:cols=100 lines=60");
		SceneLoad(_Player, _Cursor);
		break;
	case ExitScene:
		exit(NULL);
		break;
	}
}
void SceneLogo()
{
	OnDrawText((char*)"test", 55.0f, 15.0f, 11);

	SceneState++;
}

void SceneMenu(Object* _Player, Object* _Cursor)
{
	OnDrawText((char*)"��������������������������������������", 36.0f, 4.0f);
	OnDrawText((char*)"��                                  ��", 36.0f, 5.0f);
	OnDrawText((char*)"��                                  ��", 36.0f, 6.0f);
	OnDrawText((char*)"��                                  ��", 36.0f, 7.0f);
	OnDrawText((char*)"��                                  ��", 36.0f, 8.0f);
	OnDrawText((char*)"��                                  ��", 36.0f, 9.0f);
	OnDrawText((char*)"��                                  ��", 36.0f, 10.0f);
	OnDrawText((char*)"��                                  ��", 36.0f, 11.0f);
	OnDrawText((char*)"��                                  ��", 36.0f, 12.0f);
	OnDrawText((char*)"��                                  ��", 36.0f, 13.0f);
	OnDrawText((char*)"��                                  ��", 36.0f, 14.0f);
	OnDrawText((char*)"��                                  ��", 36.0f, 15.0f);
	OnDrawText((char*)"��                                  ��", 36.0f, 16.0f);
	OnDrawText((char*)"��                                  ��", 36.0f, 17.0f);
	OnDrawText((char*)"��                                  ��", 36.0f, 18.0f);
	OnDrawText((char*)"��������������������������������������", 36.0f, 19.0f);

	OnDrawText((char*)"1. ���� ����", float(60 - strlen("1. ���� ����")), 7.0f);
	OnDrawText((char*)"2. �����ϱ�", float(60 - strlen("1. ���� ����")), 10.0f);
	OnDrawText((char*)"3. �ҷ�����", float(60 - strlen("1. ���� ����")), 13.0f);
	OnDrawText((char*)"4. ���� ����", float(60 - strlen("1. ���� ����")), 16.0f);

	// ** [��] Ű�� �Է¹���.
	if (GetAsyncKeyState(VK_UP) && _Cursor->TransInfo.Position.y > 7.0f)
		_Cursor->TransInfo.Position.y -= 3;

	// ** [��] Ű�� �Է¹���.
	if (GetAsyncKeyState(VK_DOWN) && _Cursor->TransInfo.Position.y < 16.0f)
		_Cursor->TransInfo.Position.y += 3;

	OnDrawText(_Cursor->Info.Texture, _Cursor->TransInfo.Position.x, _Cursor->TransInfo.Position.y);

	if (GetAsyncKeyState(VK_RETURN))
	{
		switch (int(_Cursor->TransInfo.Position.y))
		{
		case 7:
			Initialize(_Cursor, (char*)"��", 33.5f, 22.0f);
			SceneState = InfoScene;
			break;
		case 10:
			break;
		case 13:
			break;
		case 16:
			SceneState = ExitScene;
			break;
		}
	}
}

void SceneInfo(Object* _Player, Object* _Cursor)
{
	for (int i = 0; i < 60; ++i)
	{
		OnDrawText((char*)"��", float(0 + strlen("��")) * i + 0.5f, 20.0f);
	}
	/*
	�÷��̾� ����
	*/
	OnDrawText((char*)"���� ����", 25.0f, 21.0f);
	OnDrawText((char*)"��� �ϱ�", 55.0f, 21.0f);
	OnDrawText((char*)"�޴� ����", 85.0f, 21.0f);

	OnDrawText(_Cursor->Info.Texture, _Cursor->TransInfo.Position.x, _Cursor->TransInfo.Position.y);

	if (GetAsyncKeyState(VK_LEFT) && _Cursor->TransInfo.Position.x > 33.5f)
		_Cursor->TransInfo.Position.x -= 30.0f;

	if (GetAsyncKeyState(VK_RIGHT) && _Cursor->TransInfo.Position.x < 93.5f)
		_Cursor->TransInfo.Position.x += 30.0f;

	if (GetAsyncKeyState(VK_RETURN))
	{
		switch (int(_Cursor->TransInfo.Position.x))
		{
		case 33:
			Initialize(_Cursor, (char*)"��", 60.0f, 15.0f);
			SceneState = ShopScene;
			break;
		case 63:
			SceneState = MapScene;
			break;
		case 93:
			Initialize(_Cursor, (char*)"��", 63.0f, 7.0f);
			SceneState = MenuScene;
			break;
		}
	}
}

void SceneShop(Object* _Player, Object* _Cursor)
{
	/*
for (int j = 0; j < 20; ++j)
{
	for (int i = 0; i < 60; ++i)
	{
		OnDrawText((char*)"��", 20.0f + (float)i, 5.0f + (float)j);
		if (0 < i < 60)
			OnDrawText((char*)"��", 20.0f + (float)i, 5.0f + (float)j);
		if (i == 59 && j == 0)
			OnDrawText((char*)"��", 21.0f + (float)i, 5.0f + (float)j);
		if (0 < j < 60)
			OnDrawText((char*)"��", 20.0f + (float)i, 5.0f + (float)j);
		if (1 < i < 59 && 1 < j < 19)
			OnDrawText((char*)" ", 20.0f + (float)i, 5.0f + (float)j);
		if (j == 19)
			OnDrawText((char*)"��", 20.0f + (float)i, 5.0f + (float)j);
		if (j == 19 && i == 59)
			OnDrawText((char*)"��", 20.0f + (float)i, 5.0f + (float)j);
	}
}
		*/

	// ** ������� ���� �˾ƾ� �ذ� ����

	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 60; ++j)
		{
			OnDrawText((char*)"��", 20.0f + (float)j, 5.0f + (float)i);
		}
	}

	OnDrawText((char*)"��ǰ ���", 55.0f, 6.0f);

	OnDrawText(_Cursor->Info.Texture, _Cursor->TransInfo.Position.x, _Cursor->TransInfo.Position.y);
}

DrawTextInfo BackGroundInitialize(int _i)
{
	// ** ��� �ʱ�ȭ.
	DrawTextInfo BackGround;

	// ** �������� �ʱ�ȭ ����. ū ���� ���ü� �ֵ��� Time������ ������ ��������, 
	// ** for���� ������ ���ԵǸ� Time�� ���������� ������ �ֱ⶧����,
	// ** �������̶�� �ϴ��� �������� ���� ���� ���ü� ����.
	// ** i�� ���� ���ϰ� ���������ν� ���� ���� ������ �ʵ��� ����.
	srand((GetTickCount() + _i * _i) * GetTickCount());

	// ** ���� ��� ������� ������ �ʾ�����, ���� ���� �Ѿ��� �������� �÷��̾ ���� �پ��������� �浹���� �ʰ�,
	// ** �Ѿ˰� �پ��� ������ �浹������ �ǵ��� �������� ����.
	BackGround.Info.Option = 0;

	// ** ��ǥ�� �������� ������.
	BackGround.TransInfo.Position.x = float(rand() % 100 + 10);
	BackGround.TransInfo.Position.y = float(rand() % 50 + 1);

	// ** ������� ���� �ؽ�ó�� ����.
	BackGround.Info.Texture = (char*)"*";

	// ** ������� ���� �ؽ�ó�� ������ �������� ����.
	BackGround.Info.Color = rand() % 8 + 1;

	return BackGround;
}

void SceneMap(Object* _Player, Object* _Cursor)
{
	for (int i = 0; i < 50; ++i)
	{
		for (int j = 0; j < 130; ++j)
		{
			OnDrawText((char*)"/", 10.0f + (float)j, 5.0f + (float)i, 10);
		}		
	}

	for (int i = 0; i < 30; ++i)
	{
		for (int j = 0; j < 120; ++j)
		{
			OnDrawText((char*)"/", 15.0f + (float)j, 10.0f + (float)i, 6);
		}
	}

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			OnDrawText((char*)"/", 68.0f + (float)j, 28.0f + (float)i, 7);
			OnDrawText((char*)"/", 66.0f, 29.0f, 7);
			OnDrawText((char*)"/", 66.0f, 30.0f, 7);
			OnDrawText((char*)"/", 67.0f, 29.0f, 7);
			OnDrawText((char*)"/", 67.0f, 30.0f, 7);
			OnDrawText((char*)"/", 76.0f, 29.0f, 7);
			OnDrawText((char*)"/", 76.0f, 30.0f, 7);
			OnDrawText((char*)"/", 77.0f, 29.0f, 7);
			OnDrawText((char*)"/", 77.0f, 30.0f, 7);
		}
	}
	Sleep(5000);
	SceneState = BattleScene;
}


void SceneLoad(Object* _Player, Object* _Cursor)
{
	int LoadCount = 20;
	int Loading = 0;
	while (LoadCount)
	{

		if (_Player->Time + 200 < GetTickCount64())
		{
			_Player->Time = GetTickCount64();
			system("cls");
			OnDrawText((char*)"�����...", 44.0f, 25.0f);

			--LoadCount;
			++Loading;

			for (int i = 0; i < 10; ++i)
			{
				OnDrawText((char*)"��", 2.0f + (float)Loading, 58.0f);
				if (Loading == 10)
					Loading = 0;

			}
		}
	}
	SceneBattle(_Player, _Cursor);
}

void SceneBattle(Object* _Player, Object* _Cursor)
{
	DrawTextInfo BackGround[30];
	for (int i = 0; i < 30; ++i)
	{
		BackGround[i] = BackGroundInitialize(i);
	}

	// ** Enemy���� �� �����Ҵ�.
	Object* Enemy[32];	// = new Object;

	for (int i = 0; i < 32; ++i)
		Enemy[i] = nullptr;

	ULONGLONG EnemyTime = GetTickCount64();

	Object* EnemyBullet[128] = { nullptr };

	Vector3 EnemyBulletDirection[128];

	Object* Item[32];

	for (int i = 0; i < 32; ++i)
		Item[i] = nullptr;

	Object* Boss[4];

	for (int i = 0; i < 4; ++i)
		Boss[i] = nullptr;

	int Score = 0;

	Object* Bullet[128] = { nullptr };
	Object* BossBullet[128] = { nullptr };

	Vector3 BossBulletDirection[128];
	Vector3 ItemDirection[32];

	bool Check = false;

	int Countdown = 150;

	bool crash = false;
	bool crash2 = false;

	int BattleHelper = 1;

	while (BattleHelper)
	{
		if (_Cursor->Time + 80 < GetTickCount64())
		{
			_Cursor->Time = GetTickCount64();
			system("cls");
			// ** ��� ���
			for (int i = 0; i < 30; ++i)
			{
				OnDrawText(
					BackGround[i].Info.Texture,
					BackGround[i].TransInfo.Position.x,
					BackGround[i].TransInfo.Position.y,
					BackGround[i].Info.Color);
			}

			if (EnemyTime + 1500 < GetTickCount64())
			{
				EnemyTime = GetTickCount64();

				for (int i = 0; i < 32; ++i)
				{
					if (Enemy[i] == nullptr)
					{
						srand((GetTickCount() + i * i) * GetTickCount());

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
									OnDrawText((char*)"Ŭ����!!", 50, 30, 10);

									system("mode con:cols=120 lines=30");
									Initialize(_Cursor, (char*)"��", 63.0f, 7.0f);
									SceneState = MenuScene;
									BattleHelper = 0;
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
							system("mode con:cols=120 lines=30");
							Initialize(_Cursor, (char*)"��", 63.0f, 7.0f);
							SceneState = MenuScene;
							BattleHelper = 0;
						}
						break;
					}

					if (EnemyBullet[i] != nullptr)
						if (EnemyBullet[i]->TransInfo.Position.y >= 50 || EnemyBullet[i]->TransInfo.Position.y <= 0 ||
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
							system("mode con:cols=120 lines=30");
							Initialize(_Cursor, (char*)"��", 63.0f, 7.0f);
							SceneState = MenuScene;
							BattleHelper = 0;
						}

						break;
					}

					if (BossBullet[i] != nullptr)
						if (BossBullet[i]->TransInfo.Position.y >= 50 || BossBullet[i]->TransInfo.Position.y <= 0 ||
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
						if (Item[i]->Info.Texture == (char*)"��/")
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
							OnDrawText((char*)"Ŭ����!!", 50, 30, 10);

							SceneState = MenuScene;
						}
					}

					--_Player->Boom;
					Check = false;
				}
			}

			OnDrawText(_Player->Info.Texture,
				_Player->TransInfo.Position.x,
				_Player->TransInfo.Position.y,
				10);

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

					OnDrawText(Item[i]->Info.Texture, Item[i]->TransInfo.Position.x, Item[i]->TransInfo.Position.y, 13);
				}
			}

			for (int i = 0; i < 128; ++i)
			{
				if (EnemyBullet[i])
				{
					OnDrawText(EnemyBullet[i]->Info.Texture,
						EnemyBullet[i]->TransInfo.Position.x,
						EnemyBullet[i]->TransInfo.Position.y);

					EnemyBullet[i]->TransInfo.Position.x += EnemyBulletDirection[i].x * 2.0f;
					EnemyBullet[i]->TransInfo.Position.y += EnemyBulletDirection[i].y * 1.5f;
				}
			}

			for (int i = 0; i < 32; ++i)
			{
				if (Enemy[i])
				{
					OnDrawText(Enemy[i]->Info.Texture,
						Enemy[i]->TransInfo.Position.x,
						Enemy[i]->TransInfo.Position.y,
						12);

					Enemy[i]->TransInfo.Position.y += 0.5f;

					if (Enemy[i]->TransInfo.Position.y >= 50)
					{
						delete Enemy[i];
						Enemy[i] = nullptr;
					}
				}
			}

			if (Boss[0])
			{
				for (int i = 0; i < 128; ++i)
				{
					if (BossBullet[i])
					{
						OnDrawText(BossBullet[i]->Info.Texture,
							BossBullet[i]->TransInfo.Position.x,
							BossBullet[i]->TransInfo.Position.y);

						BossBullet[i]->TransInfo.Position.x += BossBulletDirection[i].x * 2.0f;
						BossBullet[i]->TransInfo.Position.y += BossBulletDirection[i].y * 1.5f;
					}
				}

				OnDrawText((char*)"[", 10.0f, 4.0f, 3);
				OnDrawText((char*)"]", 12.0f + Boss[0]->Hp, 4.0f, 3);

				for (int i = 0; i < Boss[0]->Hp; ++i)
				{
					OnDrawText((char*)"/", 11.0f + i, 4.0f, 12);
				}

				OnDrawText(Boss[0]->Info.Texture, Boss[0]->TransInfo.Position.x - 3.0f, Boss[0]->TransInfo.Position.y - 1.0f, 11);
				OnDrawText(Boss[0]->Info.Texture, Boss[0]->TransInfo.Position.x - 3.0f, Boss[0]->TransInfo.Position.y, 11);
				OnDrawText(Boss[0]->Info.Texture, Boss[0]->TransInfo.Position.x - 3.0f, Boss[0]->TransInfo.Position.y + 1.0f, 11);
				OnDrawText(Boss[0]->Info.Texture, Boss[0]->TransInfo.Position.x - 3.0f, Boss[0]->TransInfo.Position.y + 2.0f, 11);
			}

			for (int i = 0; i < 128; ++i)
			{
				if (Bullet[i])
				{
					Bullet[i]->TransInfo.Position.y -= 2;
					OnDrawText(Bullet[i]->Info.Texture,
						Bullet[i]->TransInfo.Position.x,
						Bullet[i]->TransInfo.Position.y);
				}
			}


			OnDrawText((char*)"���� �ð� : ", float(60 - strlen("���� �ð� : ")), 1.0f);
			if (_Player->Time + 1000 < GetTickCount64())
			{
				_Player->Time = GetTickCount64();
				--Countdown;
			}
			OnDrawText(Countdown, 60.0f, 1.0f);

			OnDrawText((char*)"Score : ", float(60 - strlen("Score : ")), 2.0f);
			OnDrawText(Score, 60.0f, 2.0f);

			for (int i = 0; i < _Player->Hp; ++i)
			{
				OnDrawText(_Player->Info.Texture, (2.0f * i) + 0.5f, 59.0f);
			}
			for (int i = 0; i < _Player->Boom; ++i)
			{
				OnDrawText((char*)"Boom", (4.0f * i) + 0.5f, 58.0f);
			}
		}
	}
}