#pragma once

// ** �ʱ�ȭ �Լ� (����Ʈ �Ű����� : int _Value = 0)
void Initialize(Object* _Object, char* _Texture, float _PosX = 0.0f, float _PosY = 0.0f, float _PosZ = 0.0f, int Hp = 1);

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

Object* CreatEnemy(const float _x, const float _y, const int _hp);

// ** Ű�Է� 
void UpdateInput(Object* _Object);

// ** �Ÿ��� ���ϴ� �Լ�
float GetDistance(const Object* _ObjectA, const Object* _ObjectB);

// ** ������ ���ϴ� �Լ�
Vector3 GetDirection(const Object* _ObjectA, const Object* _ObjectB);

Object* CreatBoss(const float _x, const float _y, const float _xScale, const float _yScale);

// ** �Լ� �����
void Initialize(Object* _Object, char* _Texture, float _PosX, float _PosY, float _PosZ, int _Hp)
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
	Initialize(pBullet, (char*)"��", _x, _y, 0.0f, _hp);

	return pBullet;
}

Object* CreatEnemy(const float _x, const float _y, const int _hp)
{
	Object* _Object = new Object;
	Initialize(_Object, (char*)"��", _x, _y, 0.0f, _hp);

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

Object* CreatBoss(const float _x, const float _y, const float _xScale, const float _yScale)
{
	Object* _Object = new Object;
	Initialize(_Object, (char*)"�ߡߡߡߡߡߡ�", _x, _y);
	/*
	_Object->TransInfo.Scale.x = _xScale;
	_Object->TransInfo.Scale.y = _yScale;
	*/

	return _Object;
}