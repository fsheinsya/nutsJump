# include <Siv3D.hpp> // Siv3D v0.6.16

using namespace Scene;

void Player()
{ 
	const Texture player{ U"🥜"_emoji };

	const Vec2 playerPos{ 200.0,540.0 };


}

void enemy()
{
	const Texture enemy{ U"🐺"_emoji };

	const Vec2 enemyPos{ 600.0,540.0 };
}

void item()
{

}

void Main()
{
	const Texture emoji{ U"🥜"_emoji };

	const Texture enemy{ U"🐺"_emoji };

	double playerPosX = 200.0;

	double enemyPosX = 600.0;

	double playerPosY = 540.0;

	double enemyPosY = 540.0;

	double gravity = 0.0;

	double speed = 400.0;

	double JumpLimit = 400.0;

	bool isPlayerFacingRight = true;

	bool isPlayerJumping = false;

	while (System::Update())
	{

		if (KeyLeft.pressed() || KeyA.pressed())
		{
			//ブレイヤーが左に移動する
			playerPosX = Max((playerPosX - speed * DeltaTime()), 60.0);
			isPlayerFacingRight = false;
		}

		if (KeyRight.pressed() || KeyD.pressed())
		{
			// プレイヤーが右に移動する | Player moves right
			playerPosX = Min((playerPosX + speed * DeltaTime()), 740.0);
			isPlayerFacingRight = true;
		}

		if ((KeyUp.pressed() || KeyW.pressed()|| KeySpace.pressed())&& playerPosY == 540.0)
		{
			isPlayerJumping = true;
			gravity = playerPosY;
			playerPosY = playerPosY - 20;

		}

		if (isPlayerJumping == true)
		{
			gravity = -12.0f;

			playerPosY += gravity;
			gravity += 3.0f;

			if (playerPosY == JumpLimit) {
				isPlayerJumping = false;
			}
			
		}

		if (isPlayerJumping == false)
		{
			playerPosY -= gravity;
			gravity -= 3.0;

			playerPosY = Min(playerPosY, 540.0);

		}

		if (playerPosX < enemyPosX) {
			enemyPosX -= 0.5;
		}
		else {
			enemyPosX += 0.5;
		}

		emoji.scaled(0.75).mirrored(isPlayerFacingRight).drawAt(playerPosX, playerPosY);
		enemy.scaled(0.75).drawAt(enemyPosX,enemyPosY);

		if (playerPosX == enemyPosX) {
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
