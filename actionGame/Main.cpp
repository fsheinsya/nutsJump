# include <Siv3D.hpp> // Siv3D v0.6.16

using namespace Scene;

class Player
{
public:

	Player() : playerPos(200.0, 540.0) {};

	void update()
	{
		if (KeyLeft.pressed() || KeyA.pressed()) playerPos.x -= 10.0;

		if (KeyRight.pressed() || KeyD.pressed()) playerPos.x += 10.0;

		if ((KeyUp.pressed() || KeyW.pressed() || KeySpace.pressed()) && isPlayerJumping == false) isPlayerJumping = true;

		if (isPlayerJumping == true)
		{
			isWhileJumping += 0.5;

			gravity = -12.0;

			playerPos.y += gravity;
			gravity += 3.0;

			if (isWhileJumping == 3.0) isPlayerJumping = false;

		}

		if (isPlayerJumping == false)
		{
			isWhileJumping = 0.0;
			playerPos.y -= gravity;
			gravity -= 3.0;

			playerPos.y = Min(playerPos.y, 540.0);

		}
	}
	
	void draw()
	{
		player
		.scaled(0.75)
		.mirrored(isPlayerFacingRight)
		.drawAt(playerPos.x,playerPos.y);

		collider
		.setCenter(playerPos)
		.drawFrame(3,Palette::Green);
	}


	Circle collider{ playerPos, 60.0 };

protected:
	Vec2 playerPos;

private:

	Texture player{ U"🥜"_emoji };

	bool isPlayerFacingRight = true;

	bool isPlayerJumping = false;

	double isWhileJumping = 0.0;

	double gravity = 0.0;
};

class Enemy:Player
{
public:

	Enemy() : enemyPos(600.0, 540.0) {};

	void update()
	{
		if(enemyPos.x > playerPos.x) enemyPos.x -= 2.0;
		if(enemyPos.x < playerPos.x) enemyPos.x += 2.0;
	}

	void draw() {
		enemy
		.drawAt(enemyPos.x, enemyPos.y);

		collider
		.setCenter(enemyPos)
		.drawFrame(3, Palette::Red);
	}

	Circle collider{ enemyPos, 60.0 };

private:

	Texture enemy{ U"🐺"_emoji };

	Vec2 enemyPos;
};

void Main()
{
	Player player;

	Enemy enemy;

	while (System::Update())
	{
		player.update();

		player.draw();

		enemy.update();

		enemy.draw();

		if (player.collider == enemy.collider) {
			System::Exit();
		}
	}
}

//
// - Debug ビルド: プログラムの最適化を減らす代わりに、エラーやクラッシュ時に詳細な情報を得られます。
//
// - Release ビルド: 最大限の最適化でビルドします。
//
// - [デバッグ] メニュー → [デバッグの開始] でプログラムを実行すると、[出力] ウィンドウに詳細なログが表示され、エラーの原因を探せます。
//
// - Visual Studio を更新した直後は、プログラムのリビルド（[ビルド]メニュー → [ソリューションのリビルド]）が必要な場合があります。
//
