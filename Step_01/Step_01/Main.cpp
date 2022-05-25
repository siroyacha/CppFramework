// ** Framework v0.7.1
#include"Headers.h"

// ** �浹, �Ÿ� ���ϱ� �ʼ��� �ֱ�

// ** ������.	
int main(void)
{
	// ** Ŀ���� �Ⱥ��̰� �������.
	HideCursor(false);

	system("mode con:cols=100 lines=60");

	// ** ��� �ʱ�ȭ.
	DrawTextInfo BackGround[30];

	for (int i = 0; i < 30; ++i)
	{
		// ** �������� �ʱ�ȭ ����. ū ���� ���ü� �ֵ��� Time������ ������ ��������, 
		// ** for���� ������ ���ԵǸ� Time�� ���������� ������ �ֱ⶧����,
		// ** �������̶�� �ϴ��� �������� ���� ���� ���ü� ����.
		// ** i�� ���� ���ϰ� ���������ν� ���� ���� ������ �ʵ��� ����.
		srand((GetTickCount() + i * i) * GetTickCount());

		// ** ���� ��� ������� ������ �ʾ�����, ���� ���� �Ѿ��� �������� �÷��̾ ���� �پ��������� �浹���� �ʰ�,
		// ** �Ѿ˰� �پ��� ������ �浹������ �ǵ��� �������� ����.
		BackGround[i].Info.Option = 0;

		// ** ��ǥ�� �������� ������.
		BackGround[i].TransInfo.Position.x = float(rand() % 100 + 10);
		BackGround[i].TransInfo.Position.y = float(rand() % 50 + 1);

		// ** ������� ���� �ؽ�ó�� ����.
		BackGround[i].Info.Texture = (char*)"*";

		// ** ������� ���� �ؽ�ó�� ������ �������� ����.
		BackGround[i].Info.Color = rand() % 8 + 1;
	}

	// ** �÷��̾� ���� �� �����Ҵ�.
	Object* Player = new Object;

	// ** �÷��̾� �ʱ�ȭ
	Initialize(Player, (char*)"��/", 50, 50);

	// ** Enemy���� �� �����Ҵ�.
	Object* Enemy[32];	// = new Object;
	Object* Boss;

	for (int i = 0; i < 32; ++i)
		Enemy[i] = nullptr;
		
	// ** ���� �ð����� �ʱ�ȭ.
	ULONGLONG Time = GetTickCount64();
	ULONGLONG EnemyTime = GetTickCount64();
	ULONGLONG CountdownTime = GetTickCount64();

	int Score = 0;

	Object* Bullet[128] = { nullptr };
	Object* EnemyBullet[128] = { nullptr };

	Object* Temp[128] = { nullptr };

	Vector3 EnemyBulletDirection[128];

	bool Check = false;

	int Power = 0;
	
	int test = 0;
	int Playerdietest=1;
	int Countdown = 60;
	// ** ���
	while (Playerdietest)
	{
		// ** �ʱ�ȭ�� �ð����κ��� +50 ��ŭ �����ϸ�...
		// ** (�����Ӱ� �����ӻ����� �ð� ������ 0.5�ʷ� ����)
		if (Time + 80 < GetTickCount64())
		{
			// ** ������ ����ŭ �ٽ� �ʱ�ȭ.
			Time = GetTickCount64();

			// ** �ܼ�â ���� ��ü ����
			system("cls");

			// ** ��� ���
			for (int i = 0; i < 30; ++i)
			{
				OnDrawText(
					BackGround[i].Info.Texture,
					BackGround[i].TransInfo.Position.x,
					BackGround[i].TransInfo.Position.y,
					BackGround[i].Info.Color);

				// ** ������� ���� �ؽ�ó�� ������ �������� ����.
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
						if (EnemyBullet[j] == nullptr)
						{
							if (Enemy[i]->Time + 2000 < GetTickCount64())
								Enemy[i]->Time = GetTickCount64();

							EnemyBullet[j] = CreatBullet(
								Enemy[i]->TransInfo.Position.x,
								Enemy[i]->TransInfo.Position.y + 1.0f);

							EnemyBulletDirection[j] = GetDirection(Player, Enemy[i]);

							break;
						}
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
							if (Collision(Enemy[j], Bullet[i]))
							{
								delete Enemy[j];
								Enemy[j] = nullptr;

								delete Bullet[i];
								Bullet[i] = nullptr;

								++Score;

								break;
							}
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
						//Playerdietest = 0;

						delete EnemyBullet[i];
						EnemyBullet[i] = nullptr;
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
			}

			// ** Ű �Է�
			UpdateInput(Player);

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

			//OnDrawText((char*)"[          ]", 1.0f, 28.0f);

			for (int i = 0; i < Power; ++i)
			{
				OnDrawText((char*)"/", 2.0f + i, 28.0f);
			}
			
			if (GetAsyncKeyState(VK_SPACE))
			{
				for (int i = 0; i < 128; ++i)
				{
					if (Bullet[i] == nullptr)
					{
						Bullet[i] = CreatBullet(
							Player->TransInfo.Position.x,
							Player->TransInfo.Position.y - 1);
						break;
					}
				}
			}

			if (GetAsyncKeyState(0x58))
			{
				for (int i = 0; i < 32; ++i)
				{
					if (Enemy[i])
					{
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
			}
			
			OnDrawText(Player->Info.Texture,
				Player->TransInfo.Position.x,
				Player->TransInfo.Position.y,
				10);
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
			
			for (int j = 0; j < 128; ++j)
			{
				if (EnemyBullet[j])
				{
					OnDrawText(EnemyBullet[j]->Info.Texture,
						EnemyBullet[j]->TransInfo.Position.x,
						EnemyBullet[j]->TransInfo.Position.y);

					EnemyBullet[j]->TransInfo.Position.x += EnemyBulletDirection[j].x * 2.0f;
					EnemyBullet[j]->TransInfo.Position.y += EnemyBulletDirection[j].y * 1.5f;
				}
			}

			OnDrawText((char*)"���� �ð� : ", float(60 - strlen("���� �ð� : ")), 1.0f);
			if (CountdownTime + 1000 < GetTickCount64())
			{
				CountdownTime = GetTickCount64();
				--Countdown;
			}
			OnDrawText(Countdown, 60.0f, 1.0f);

			OnDrawText((char*)"Score : ", float(60 - strlen("Score : ")), 2.0f);
			OnDrawText(Score, 60.0f, 2.0f);
		}
	}

	return 0;
}
