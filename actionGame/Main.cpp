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

		if (KeyUp.pressed() || KeyW.pressed() || KeySpace.pressed()) isPlayerJumping = true;

		if (isPlayerJumping == true)
		{
			isWhileJumping += 0.5;

			gravity = -12.0f;

			playerPos.y += gravity;
			gravity += 3.0f;

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

protected:
	Vec2 playerPos;

private:

	Texture player{ U"🥜"_emoji };

	Circle collider{ playerPos, 50.0 };

	bool isPlayerFacingRight = true;

	bool isPlayerJumping;

	double isWhileJumping = 0.0;

	double gravity = 0.0;
};

class Enemy:Player
{
public:

	Enemy() : enemyPos(600.0, 540.0) {};

	void update()
	{
		if(enemyPos.x > playerPos.x) enemyPos.x -= 5.0;
		else if(enemyPos.x < playerPos.x) enemyPos.x += 5.0;
	}

	void draw() {
		enemy
		.drawAt(enemyPos.x, enemyPos.y);

		collider
		.setCenter(enemyPos)
		.drawFrame(3, Palette::Red);
	}

private:

	Texture enemy{ U"🐺"_emoji };

	Circle collider{ enemyPos, 50.0 };

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
