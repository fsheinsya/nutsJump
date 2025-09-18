# include <Siv3D.hpp> // Siv3D v0.6.16

using namespace Scene;

using namespace System;

class Player
{
public:

	Player() : playerPos(200.0, 500.0) {};

	void update()
	{
		if (KeyLeft.pressed() || KeyA.pressed()) playerPos.x -= 10.0;

		if (KeyRight.pressed() || KeyD.pressed()) playerPos.x += 10.0;

		if ((KeyUp.down() || KeyW.down() || KeySpace.down()) && isPlayerJumping != true) isPlayerJumping = true;

		if (isPlayerJumping == true)
		{
			isWhileJumping += 0.5;

			gravity = -12.0;

			playerPos.y += gravity;
			gravity += 3.0;

			if (isWhileJumping == 10.0) isPlayerJumping = false;

		}

		if (isPlayerJumping == false)
		{
			isWhileJumping = 0.0;
			playerPos.y -= gravity;
			gravity -= 3.0;

			playerPos.y = Min(playerPos.y, 500.0);

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

	Enemy() : enemyPos(600.0, 500.0) {};

	void update()
	{
		if(enemyPos.x > playerPos.x) enemyPos.x -= 2.0;
		else if(enemyPos.x < playerPos.x) enemyPos.x += 2.0;
	}

	void draw() {
		if (!isAlive) return;

		else
		{
			enemy
				.drawAt(enemyPos.x, enemyPos.y);

			collider
				.setCenter(enemyPos)
				.drawFrame(3, Palette::Red);

			weakCollider
				.setCenter(enemyPos.x, enemyPos.y - 80.0)
				.drawFrame(3, Palette::Magenta);
		}
	}

	Circle collider{ enemyPos, 60.0 };

	Circle weakCollider{ enemyPos, 60.0};

	bool isAlive = true;

private:

	Texture enemy{ U"🐺"_emoji };

	Vec2 enemyPos;
};

class ItemBox
{
public:
	ItemBox() : ItemBoxPos(400.0, 400.0) {};
	void draw() {
		if(!isHaveItem) return;

		itemBox
		.scaled(0.5)
		.drawAt(ItemBoxPos.x, ItemBoxPos.y);

		rectcollider
		.setCenter(ItemBoxPos.x, ItemBoxPos.y)
		.drawFrame(3,Palette::Yellow);
	}
private:
	Texture itemBox{ U"🎁"_emoji };

	Vec2 ItemBoxPos;

	RectF rectcollider;

	bool isHaveItem = true;
};

class Ground
{
public:
	Ground() {};
	void draw() {
		ground
		.draw(Palette::Green);
	}
private:
	RectF ground{0.0,550.0,800.0,50.0};
};

void Main()
{
	Player player;

	Enemy enemy;

	ItemBox itemBox;

	Ground ground;

	while (System::Update())
	{
		SetBackground(Palette::Skyblue);

		player.update();

		player.draw();

		enemy.update();

		enemy.draw();

		ground.draw();

		itemBox.draw();

		if (player.collider.intersects(enemy.weakCollider)) {
			enemy.isAlive = false;
		}

		else if (player.collider.intersects(enemy.collider)) {
			MessageBoxOK(U"やられちゃった！！！",U"ゲームオーバーwww");
			break;
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
