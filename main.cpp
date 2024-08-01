#include "MyMath.h"
#include <imgui.h>

const char kWindowTitle[] = "LC1C_19_タイラタクヤ_タイトル";



// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// カメラの座標
	Vector3 cameraScale = { 1.0f, 1.0f, 1.0f };
	Vector3 cameraRotate = { 0.26f, 0.0f, 0.0f };
	Vector3 cameraTranslate = { 0.0f, 1.9f, -6.49f };
	const int kWindowWidth = 1280;
	const int kWindowHeight = 720;

	// 各点
	Vector3 controlPoint[3] = {
		{-0.8f, 0.58f, 1.0f},
		{1.76f, 1.0f, -0.3f},
		{0.94f, -0.7f, 2.3f},
	};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		/// 


		//========================================  ビュー関連  ===========================================

		// カメラ
		Matrix4x4 cameraMatrix = MakeAffineMatrix(cameraScale, cameraRotate, cameraTranslate);
		// ビュー
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		// 透視投影
		Matrix4x4 projectMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 viewProjectionMatrix = Multiply(viewMatrix, projectMatrix);
		// ビューポート変換
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		//=================================================================================================

	
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///


		// グリッド線の描画
		DrawGrid(viewProjectionMatrix, viewportMatrix);

		// ベジェ曲線の描画
		DrawBezier(controlPoint[0], controlPoint[1], controlPoint[2], viewProjectionMatrix, viewportMatrix, BLUE);

		// ベジェ曲線の各点の描画
		DrawSphere(Sphere{ controlPoint[0], 0.01f }, viewProjectionMatrix, viewportMatrix, BLACK);
		DrawSphere(Sphere{ controlPoint[1], 0.01f }, viewProjectionMatrix, viewportMatrix, BLACK);
		DrawSphere(Sphere{ controlPoint[2], 0.01f }, viewProjectionMatrix, viewportMatrix, BLACK);


		// ImGui
		ImGui::Begin("Window");
		if (ImGui::CollapsingHeader("camera")) {
			ImGui::DragFloat3("cameraScale", &cameraScale.x, 0.01f);
			ImGui::DragFloat3("cameraRotate", &cameraRotate.x, 0.01f);
			ImGui::DragFloat3("cameraTranslate", &cameraTranslate.x, 0.01f);
		}
		if (ImGui::CollapsingHeader("Bezier")) {
			ImGui::DragFloat3("controlPoint[0]", &controlPoint[0].x, 0.01f);
			ImGui::DragFloat3("controlPoint[1]", &controlPoint[1].x, 0.01f);
			ImGui::DragFloat3("controlPoint[2]", &controlPoint[2].x, 0.01f);
		}
		ImGui::End();

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
