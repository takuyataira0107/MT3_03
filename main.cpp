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


	Vector3 scales[3] = {
		{1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f}
	};

	Vector3 rotates[3] = {
		{0.0f, 0.0f, -6.8f},
		{0.0f, 0.0f, -1.4f},
		{0.0f, 0.0f, 0.0f},
	};

	Vector3 translates[3] = {
		{0.2f, 1.0f, 0.0f},
		{0.4f, 0.0f, 0.0f},
		{0.3f, 0.0f, 0.0f},
	};

	Matrix4x4 localMatrix[3] = {};
	Matrix4x4 worldMatrix[3] = {};

	Vector3 screenLine[3] = {};

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

		for (int i = 0; i < 3; i++) {
			localMatrix[i] = MakeAffineMatrix(scales[i], rotates[i], translates[i]);
		}

		worldMatrix[0] = localMatrix[0];
		worldMatrix[1] = Multiply(localMatrix[1], localMatrix[0]);
		worldMatrix[2] = Multiply(Multiply(localMatrix[2], localMatrix[1]), localMatrix[0]);

		// 線の座標をスクリーン座標に変換
		for (int i = 0; i < 3; i++) {
			screenLine[i] = Transform(Transform(Vector3{ worldMatrix[i].m[3][0], worldMatrix[i].m[3][1], worldMatrix[i].m[3][2] }, viewProjectionMatrix), viewportMatrix);
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///


		// グリッド線の描画
		DrawGrid(viewProjectionMatrix, viewportMatrix);

		// 線の描画
		Novice::DrawLine(int(screenLine[0].x), int(screenLine[0].y), int(screenLine[1].x), int(screenLine[1].y), WHITE);
		Novice::DrawLine(int(screenLine[1].x), int(screenLine[1].y), int(screenLine[2].x), int(screenLine[2].y), WHITE);

		// 肩
		DrawSphere(Sphere{ Vector3{worldMatrix[0].m[3][0], worldMatrix[0].m[3][1], worldMatrix[0].m[3][2]}, 0.05f }, viewProjectionMatrix, viewportMatrix, RED);
		// 肘
		DrawSphere(Sphere{ Vector3{worldMatrix[1].m[3][0], worldMatrix[1].m[3][1], worldMatrix[1].m[3][2]}, 0.05f }, viewProjectionMatrix, viewportMatrix, GREEN);
		// 手
		DrawSphere(Sphere{ Vector3{worldMatrix[2].m[3][0], worldMatrix[2].m[3][1], worldMatrix[2].m[3][2]}, 0.05f }, viewProjectionMatrix, viewportMatrix, BLUE);


		// ImGui
		ImGui::Begin("Window");
		if (ImGui::CollapsingHeader("Camera")) {
			ImGui::DragFloat3("cameraScale", &cameraScale.x, 0.01f);
			ImGui::DragFloat3("cameraRotate", &cameraRotate.x, 0.01f);
			ImGui::DragFloat3("cameraTranslate", &cameraTranslate.x, 0.01f);
		}
		if (ImGui::CollapsingHeader("Sphere")) {
			ImGui::DragFloat3("translates[0]", &translates[0].x, 0.01f);
			ImGui::DragFloat3("rotates[0]", &rotates[0].x, 0.01f);
			ImGui::DragFloat3("scales[0]", &scales[0].x, 0.01f);
			ImGui::DragFloat3("translates[1]", &translates[1].x, 0.01f);
			ImGui::DragFloat3("rotates[1]", &rotates[1].x, 0.01f);
			ImGui::DragFloat3("scales[1]", &scales[1].x, 0.01f);
			ImGui::DragFloat3("translates[2]", &translates[2].x, 0.01f);
			ImGui::DragFloat3("rotates[2]", &rotates[2].x, 0.01f);
			ImGui::DragFloat3("scales[2]", &scales[2].x, 0.01f);
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