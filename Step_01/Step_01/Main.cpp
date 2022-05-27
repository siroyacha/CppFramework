// ** Framework v0.7.3
#include"Headers.h"

// ** �浹, �Ÿ� ���ϱ� �ʼ��� �ֱ�

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
	Initialize(Player, (char*)"��/", 50.0f, 50.0f, 0.0f, 3, 3);

	// ** Enemy���� �� �����Ҵ�.
	Object* Enemy[32];	// = new Object;
	Object* Boss[4];

	for (int i = 0; i < 4; ++i)
		Boss[i] = nullptr;

	for (int i = 0; i < 32; ++i)
		Enemy[i] = nullptr;
		
	// ** ���� �ð����� �ʱ�ȭ.
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

	bool Check = false;

	int Power = 0;
	
	int test = 0;
	int Playerdietest=1;
	int Countdown = 150;
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

			if (Countdown == 140)
			{
				for (int i = 0; i < 4; ++i)
					Boss[i] = CreatBoss(50.0f, 10.0f, 10 * (i + 1));;				
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
									delete Enemy[j];
									Enemy[j] = nullptr;

									++Score;
								}
									break;
							}
						}
					}

					if (Bullet[i] != nullptr)
						if (Boss[0] != nullptr)
						{
							if (Collision(Boss[0], Bullet[i]))
							{
								delete Bullet[i];
								Bullet[i] = nullptr;
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
			/*
			for (int i = 0; i < Power; ++i)
			{
				OnDrawText((char*)"/", 2.0f + i, 28.0f);
			}
			*/
			
			if (GetAsyncKeyState(VK_SPACE))
			{
				
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
				/*
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
				
				for (int i = 0; i < 32; ++i)
				{
					if (Bullet[i] == nullptr && Bullet[i + 1] == nullptr &&
						Bullet[i + 2] == nullptr && Bullet[i + 3] == nullptr)
					{
						Bullet[i] = CreatBullet(
							Player->TransInfo.Position.x - 1.0f,
							Player->TransInfo.Position.y - 1.0f);
						Bullet[i + 1] = CreatBullet(
							Player->TransInfo.Position.x + 1.0f,
							Player->TransInfo.Position.y - 1.0f);
						Bullet[i + 2] = CreatBullet(
							Player->TransInfo.Position.x - 2.0f,
							Player->TransInfo.Position.y+2.0f);
						Bullet[i + 3] = CreatBullet(
							Player->TransInfo.Position.x + 2.0f,
							Player->TransInfo.Position.y+2.0f);
						break;
					}
				}
				*/
			}
			if (Player->Boom)
			{

				if (GetAsyncKeyState(0x58))
				{
					--Player->Boom;
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

					for (int i = 0; i < 128; ++i)
					{
						if (BossBullet[i])
						{
							delete BossBullet[i];
							BossBullet[i] = nullptr;
						}
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

				OnDrawText((char*)"[", 50.0f, 4.0f, 3);
				OnDrawText((char*)"]", 52.0f + Boss[0]->Hp, 4.0f, 3);

				for (int i = 0; i < Boss[0]->Hp; ++i)
				{
					OnDrawText((char*)"/", 51.0f + i, 4.0f, 12);
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
				OnDrawText(Player->Info.Texture, 2.0f * i, 59.0f);
			}
			for (int i = 0; i < Player->Boom; ++i)
			{
				OnDrawText((char*)"Boom", 4.0f * i , 58.0f);
			}
		}
	}

	return 0;
}
