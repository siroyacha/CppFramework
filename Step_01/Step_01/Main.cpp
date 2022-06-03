// ** Framework v0.8.3
#include"Headers.h"

// ** 충돌, 거리 구하기 필수로 넣기

int main(void)
{
	// ** 커서를 안보이게 만들어줌.
	HideCursor(false);

	system("mode con:cols=100 lines=60");

	// ** 배경 초기화.
	DrawTextInfo BackGround[30];

	for (int i = 0; i < 30; ++i)
	{
		// ** 랜덤값을 초기화 해줌. 큰 값이 나올수 있도록 Time값끼리 곱해줄 것이지만, 
		// ** for문이 빠르게 돌게되면 Time의 증가값보다 빠를수 있기때문에,
		// ** 랜덤값이라고 하더라도 연속으로 같은 값이 나올수 있음.
		// ** i의 값을 곱하고 더해줌으로써 같은 값이 나오지 않도록 해줌.
		srand((GetTickCount() + i * i) * GetTickCount());

		// ** 현재 어떻게 사용할지 정하지 않았지만, 추후 배경과 총알을 구분지어 플레이어가 배경과 다았을때에는 충돌하지 않고,
		// ** 총알과 다았을 때에만 충돌판정이 되도록 설정해줄 것임.
		BackGround[i].Info.Option = 0;

		// ** 좌표를 랜덤으로 설정함.
		BackGround[i].TransInfo.Position.x = float(rand() % 100 + 10);
		BackGround[i].TransInfo.Position.y = float(rand() % 50 + 1);

		// ** 배경으로 사용될 텍스처를 설정.
		BackGround[i].Info.Texture = (char*)"*";

		// ** 배경으로 사용될 텍스처의 색상을 랜덤으로 설정.
		BackGround[i].Info.Color = rand() % 8 + 1;
	}

	// ** 플레이어 선언 및 동적할당.
	Object* Player = new Object;

	Object* Item[32];

	for (int i = 0; i < 32; ++i)
		Item[i] = nullptr;

	// ** 플레이어 초기화
	Initialize(Player, (char*)"옷/", 50.0f, 50.0f, 0.0f, 3, 3);

	// ** Enemy선언 및 동적할당.
	Object* Enemy[32];	// = new Object;
	Object* Boss[4];

	for (int i = 0; i < 4; ++i)
		Boss[i] = nullptr;

	for (int i = 0; i < 32; ++i)
		Enemy[i] = nullptr;
		
	// ** 현재 시간으로 초기화.
	ULONGLONG Time = GetTickCount64();
	ULONGLONG EnemyTime = GetTickCount64();
	ULONGLONG CountdownTime = GetTickCount64();

	int Score = 0;

	Object* Bullet[128] = { nullptr };
	Object* BossBullet[128] = { nullptr };
	Object* EnemyBullet[128] = { nullptr };

	Object* Temp[128] = { nullptr };

	Vector3 EnemyBulletDirection[128];
	Vector3 BossBulletDirection[128];
	Vector3 ItemDirection[32];

	bool Check = false;

	int Power = 0;

	int Playerdietest=1;
	int Countdown = 150;

	bool crash = false;
	bool crash2 = false;

	// ** 출력
	while (Playerdietest)
	{
		// ** 초기화된 시간으로부터 +50 만큼 증가하면...
		// ** (프레임과 프레임사이의 시간 간격을 0.5초로 셋팅)
		if (Time + 80 < GetTickCount64())
		{
			// ** 증가된 값만큼 다시 초기화.
			Time = GetTickCount64();

			// ** 콘솔창 버퍼 전체 삭제
			system("cls");

			// ** 배경 출력
			for (int i = 0; i < 30; ++i)
			{
				OnDrawText(
					BackGround[i].Info.Texture,
					BackGround[i].TransInfo.Position.x,
					BackGround[i].TransInfo.Position.y,
					BackGround[i].Info.Color);

				// ** 배경으로 사용될 텍스처의 색상을 랜덤으로 설정.
				BackGround[i].Info.Color = rand() % 8 + 1;
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

							EnemyBulletDirection[j] = GetDirection(Player, Enemy[i]);
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

						BossBulletDirection[i] = GetDirection(Player, Boss[0]);
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
										ItemDirection[j] = GetDirection(Player, Item[j]);
									}
								}

								delete Enemy[j];
								Enemy[j] = nullptr;

								++Score;

								break;
							}
						}
					}

					if (Bullet[i] != nullptr)
						if (Boss[0] != nullptr)
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

									Playerdietest = 0;
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
					if (Collision(EnemyBullet[i], Player))
					{
						delete EnemyBullet[i];
						EnemyBullet[i] = nullptr;

						--Player->Hp;

						if (Player->Hp == 0)
							Playerdietest = 0;

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
					if (Collision(BossBullet[i], Player))
					{
						delete BossBullet[i];
						BossBullet[i] = nullptr;

						--Player->Hp;

						if (Player->Hp == 0)
							Playerdietest = 0;

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
					if (Collision(Item[i], Player))
					{
						if (Item[i]->Info.Texture == (char*)"Boom")
						{
							if (Player->Boom < 3)
								++Player->Boom;
						}
						if (Item[i]->Info.Texture == (char*)"Power")
						{
							if (Player->Mode < 3)
								++Player->Mode;
						}
						if (Item[i]->Info.Texture == (char*)"옷/")
						{
							if (Player->Hp < 3)
								++Player->Hp;
						}
						delete Item[i];
						Item[i] = nullptr;

						crash = false;
						crash2 = false;
					}

					if (Item[i] != nullptr)
						if (Item[i]->Time + 3000 == GetTickCount64())
						{
							delete Item[i];
							Item[i] = nullptr;

							crash = false;
							crash2 = false;
						}						
				}
			}

			// ** 키 입력
			UpdateInput(Player);

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

			//OnDrawText((char*)"[          ]", 1.0f, 28.0f);
			/*
			for (int i = 0; i < Power; ++i)
			{
				OnDrawText((char*)"/", 2.0f + i, 28.0f);
			}
			*/
			
			if (GetAsyncKeyState(VK_SPACE))
			{
				switch (Player->Mode)
				{
				case 1:

					for (int i = 0; i < 128; ++i)
					{
						if (Bullet[i] == nullptr)
						{
							Bullet[i] = CreatBullet(
								Player->TransInfo.Position.x,
								Player->TransInfo.Position.y - 1.0f);

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
								Player->TransInfo.Position.x - 1.0f,
								Player->TransInfo.Position.y - 1.0f);
							Bullet[i + 1] = CreatBullet(
								Player->TransInfo.Position.x + 1.0f,
								Player->TransInfo.Position.y - 1.0f);
							break;
						}
					}
					break;
										
				// ** 총알 수정 좀 필요
				case 3:
					for (int i = 0; i < 32; ++i)
					{
						if (Bullet[i] == nullptr && Bullet[i + 1] == nullptr &&
							Bullet[i + 2] == nullptr && Bullet[i + 3] == nullptr)
						{
							Bullet[i] = CreatBullet(
								Player->TransInfo.Position.x - 1.0f,
								Player->TransInfo.Position.y - 2.0f);
							Bullet[i + 1] = CreatBullet(
								Player->TransInfo.Position.x + 1.0f,
								Player->TransInfo.Position.y - 2.0f);
							Bullet[i + 2] = CreatBullet(
								Player->TransInfo.Position.x - 2.0f,
								Player->TransInfo.Position.y + 2.0f);
							Bullet[i + 3] = CreatBullet(
								Player->TransInfo.Position.x + 2.0f,
								Player->TransInfo.Position.y + 2.0f);
							break;
						}
					}
					break;
				}
			}

			if (Player->Boom)
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
								ItemDirection[i] = GetDirection(Player, Item[i]);
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

							Playerdietest = 0;
						}
					}

					--Player->Boom;
					Check = false;
				}
			}

			OnDrawText(Player->Info.Texture,
				Player->TransInfo.Position.x,
				Player->TransInfo.Position.y,
				10);
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
			

			OnDrawText((char*)"남은 시간 : ", float(60 - strlen("남은 시간 : ")), 1.0f);
			if (CountdownTime + 1000 < GetTickCount64())
			{
				CountdownTime = GetTickCount64();
				--Countdown;
			}
			OnDrawText(Countdown, 60.0f, 1.0f);

			OnDrawText((char*)"Score : ", float(60 - strlen("Score : ")), 2.0f);
			OnDrawText(Score, 60.0f, 2.0f);

			for (int i = 0; i < Player->Hp; ++i)
			{
				OnDrawText(Player->Info.Texture, (2.0f * i) + 0.5f, 59.0f);
			}
			for (int i = 0; i < Player->Boom; ++i)
			{
				OnDrawText((char*)"Boom", (4.0f * i) + 0.5f, 58.0f);
			}
		}
	}
	delete Player;


	system("mode con:cols=120 lines=30");

	system("cls");


	return 0;
}
