// ** Framework v0.2

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>

using namespace std;


typedef struct tagVector3
{
	float x = 0, y = 0, z = 0;

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

struct Object
{
	char* Name;
	int Speed;
	Transform TransInfo;
};


// ** 초기화 함수
void Initialize(Object* _Object, char* _Name, int _PosX = 0, int _PosY = 0, int _PosZ = 0);

// ** 이름 설정 함수
char* SetName();

// ** 출력 함수
void Output(Object* _Obj);

int main(void)
{
	/*
	Vector3 vPosition = Vector3(10, 20);
	Vector3 vPosition2 = Vector3(10, 20,30);

	cout << vPosition.x << ", " << vPosition.y << ", " << vPosition.z << endl;
	cout << vPosition2.x << ", " << vPosition2.y << ", " << vPosition2.z << endl;
	*/

	Object* Player = new Object;
	Initialize(Player, nullptr, 10, 20, 30);

	Object* Enemy = new Object;
	Initialize(Enemy, (char*)"Enemy", 100, 200, 300);

	Output(Player);
	Output(Enemy);

	return 0;
}

// ** 함수 정의부

void Initialize(Object* _Object, char* _Name, int _PosX, int _PosY, int _PosZ)
{
	_Object->Name = (_Name == nullptr) ? SetName() : _Name;
	_Object->Speed = 0;
	_Object->TransInfo.Position = Vector3(_PosX, _PosY, _PosZ);
	_Object->TransInfo.Rotation = Vector3(0, 0, 0);
	_Object->TransInfo.Scale = Vector3(0, 0, 0);
}

char* SetName()
{
	char Buffer[128]="";
	
	cout << "입력 : "; cin >> Buffer;
	
	//char pName = (char*)malloc(strlen(Buffer) + 1);
	char* pName = new char[strlen(Buffer) + 1];

	strcpy(pName, Buffer);

	return pName;
}

void Output(Object* _Obj)
{
	if (_Obj->Name != nullptr)
		cout << "Name : " << _Obj->Name << endl;

	cout << "Speed : " << _Obj->Speed << endl;
	cout << "X : " << _Obj->TransInfo.Position.x << ", Y : " << _Obj->TransInfo.Position.y << ", Z : " << _Obj->TransInfo.Position.z << endl;
}