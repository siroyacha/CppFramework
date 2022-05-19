// ** Framework v0.4.3
#include"Headers.h"

// ** ���Ϳ� ����ü�� �浹�ϴ°� �����

// ** ������.	
int main(void)
{
	// ** Ŀ���� �Ⱥ��̰� �������.
	HideCursor(false);


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
		BackGround[i].TransInfo.Position.x = rand() % 100 + 10;
		BackGround[i].TransInfo.Position.y = rand() % 26 + 1;

		// ** ������� ���� �ؽ�ó�� ����.
		BackGround[i].Info.Texture = (char*)"*";

		// ** ������� ���� �ؽ�ó�� ������ �������� ����.
		BackGround[i].Info.Color = rand() % 8 + 1;
	}


	// ** �÷��̾� ���� �� �����Ҵ�.
	Object* Player = new Object;

	// ** �÷��̾� �ʱ�ȭ
	Initialize(Player, (char*)"��/", 30, 10);

	// ** Enemy���� �� �����Ҵ�.
	Object* Enemy = new Object;

	// ** Enemy �ʱ�ȭ
	Initialize(Enemy, (char*)"Ȫ", 80, 10);

	// ** ���� �ð����� �ʱ�ȭ.
	ULONGLONG Time = GetTickCount64();

	int Score = 0;

	Object* Bullet[128] = { nullptr };
	int BulletCount = 0;

	// ** ���
	while (true)
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

			for (int i = 0; i < 128; ++i)
			{
				if (Bullet[i]!=nullptr)
				{
					if ((Bullet[i]->TransInfo.Position.x+Bullet[i]->TransInfo.Scale.x)>=120)
					{
						delete Bullet[i];
						Bullet[i] = nullptr;

						--BulletCount;
					}
				}
			}

			// ** [��] Ű�� �Է¹���.
			if (GetAsyncKeyState(VK_UP))
				Player->TransInfo.Position.y -= 1;

			// ** [��] Ű�� �Է¹���.
			if (GetAsyncKeyState(VK_DOWN))
				Player->TransInfo.Position.y += 1;

			// ** [��] Ű�� �Է¹���.
			if (GetAsyncKeyState(VK_LEFT))
				Player->TransInfo.Position.x -= 1;

			// ** [��] Ű�� �Է¹���.
			if (GetAsyncKeyState(VK_RIGHT))
				Player->TransInfo.Position.x += 1;

			Collision(Player, Enemy);

			if (GetAsyncKeyState(VK_SPACE))
				for (int i = 0; i < 128; ++i)
				{
					if (Bullet[i] == nullptr)
					{
						Bullet[i] = CreatBullet(
							Player->TransInfo.Position.x,
							Player->TransInfo.Position.y);
						++BulletCount;
						break;
					}
				}
	
			OnDrawText(Player->Info.Texture,
				Player->TransInfo.Position.x,
				Player->TransInfo.Position.y,
				10);

			OnDrawText(Enemy->Info.Texture,
				Enemy->TransInfo.Position.x,
				Enemy->TransInfo.Position.y,
				12);

			for (int i = 0; i < 128; ++i)
			{
				if (Bullet[i])
				{
					OnDrawText(Bullet[i]->Info.Texture,
						Bullet[i]->TransInfo.Position.x+=2,
						Bullet[i]->TransInfo.Position.y,
						14);
				}
			}

			OnDrawText((char*)"Bullet Count : ", 95, 1);
			OnDrawText(BulletCount, 95+strlen("Bullet Count : "), 1);

			OnDrawText((char*)"Score : ", 60 - strlen("Score : "), 1);
			OnDrawText(++Score, 60, 1);
		}
	}

	return 0;
}
