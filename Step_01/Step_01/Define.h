#pragma once

// ** 초기화 함수 (디폴트 매개변수 : int _Value = 0)
void Initialize(Object* _Object, char* _Texture, float _PosX = 0.0f, float _PosY = 0.0f, float _PosZ = 0.0f, int Hp = 1);

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

Object* CreatEnemy(const float _x, const float _y, const int _hp);

// ** 키입력 
void UpdateInput(Object* _Object);

// ** 거리를 구하는 함수
float GetDistance(const Object* _ObjectA, const Object* _ObjectB);

// ** 방향을 구하는 함수
Vector3 GetDirection(const Object* _ObjectA, const Object* _ObjectB);

Object* CreatBoss(const float _x, const float _y, const float _xScale, const float _yScale);

// ** 함수 선언부
void Initialize(Object* _Object, char* _Texture, float _PosX, float _PosY, float _PosZ, int _Hp)
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

	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void SetTextColor(const int _Color)
{
	SetConsoleTextAttribute(
		GetStdHandle(STD_OUTPUT_HANDLE), _Color);
}

void OnDrawText(const char* _str, const float _x, const float _y, const int _Color)
{
	SetCursorPosition(_x, _y);
	SetTextColor(_Color);
	cout << _str;
}

void OnDrawText(const int _Value, const float _x, const float _y, const int _Color)
{
	SetCursorPosition(_x, _y);
	SetTextColor(_Color);

	char* pText = new char[4];
	_itoa(_Value, pText, 10);
	cout << _Value;
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
		(_ObjectA->TransInfo.Position.y + _ObjectA->TransInfo.Scale.y) > _ObjectB->TransInfo.Position.y &&
		(_ObjectB->TransInfo.Position.y + _ObjectB->TransInfo.Scale.y) > _ObjectA->TransInfo.Position.y)
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
	Initialize(_Object, (char*)"훗", _x, _y, 0.0f, _hp);

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

Object* CreatBoss(const float _x, const float _y, const float _xScale, const float _yScale)
{
	Object* _Object = new Object;
	Initialize(_Object, (char*)"◆◆◆◆◆◆◆", _x, _y);
	/*
	_Object->TransInfo.Scale.x = _xScale;
	_Object->TransInfo.Scale.y = _yScale;
	*/

	return _Object;
}