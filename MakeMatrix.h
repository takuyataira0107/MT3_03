#pragma once
#include "MatrixCalc.h"
#include <assert.h>
#include <cmath>



//=================================== 平行移動行列の作成関数 ======================================

Matrix4x4 MakeTranslateMatrix(const Vector3& translate)
{
	Matrix4x4 result;

	result.m[0][0] = 1;             result.m[0][1] = 0;             result.m[0][2] = 0;             result.m[0][3] = 0;
	result.m[1][0] = 0;             result.m[1][1] = 1;             result.m[1][2] = 0;             result.m[1][3] = 0;
	result.m[2][0] = 0;             result.m[2][1] = 0;             result.m[2][2] = 1;             result.m[2][3] = 0;
	result.m[3][0] = translate.x;   result.m[3][1] = translate.y;   result.m[3][2] = translate.z;   result.m[3][3] = 1;

	return result;
}

//=================================================================================================


//=================================== 拡大縮小行列の作成関数 ======================================

Matrix4x4 MakeScaleMatrix(const Vector3& scale)
{
	Matrix4x4 result;

	result.m[0][0] = scale.x;        result.m[0][1] = 0;              result.m[0][2] = 0;            result.m[0][3] = 0;
	result.m[1][0] = 0;              result.m[1][1] = scale.y;        result.m[1][2] = 0;            result.m[1][3] = 0;
	result.m[2][0] = 0;              result.m[2][1] = 0;              result.m[2][2] = scale.z;      result.m[2][3] = 0;
	result.m[3][0] = 0;              result.m[3][1] = 0;              result.m[3][2] = 0;            result.m[3][3] = 1;

	return result;

}

//=================================================================================================


//======================================= 回転行列の作成関数 ======================================

Matrix4x4 MakeRotateXMatrix(float radian)
{
	Matrix4x4 result;

	result.m[0][0] = 1;                    result.m[0][1] = 0;                     result.m[0][2] = 0;                 result.m[0][3] = 0;
	result.m[1][0] = 0;                    result.m[1][1] = std::cos(radian);      result.m[1][2] = std::sin(radian);  result.m[1][3] = 0;
	result.m[2][0] = 0;                    result.m[2][1] = -std::sin(radian);     result.m[2][2] = std::cos(radian);  result.m[2][3] = 0;
	result.m[3][0] = 0;                    result.m[3][1] = 0;                     result.m[3][2] = 0;                 result.m[3][3] = 1;

	return result;

}


Matrix4x4 MakeRotateYMatrix(float radian)
{
	Matrix4x4 result;

	result.m[0][0] = std::cos(radian);     result.m[0][1] = 0;                     result.m[0][2] = -std::sin(radian); result.m[0][3] = 0;
	result.m[1][0] = 0;                    result.m[1][1] = 1;                     result.m[1][2] = 0;                 result.m[1][3] = 0;
	result.m[2][0] = std::sin(radian);     result.m[2][1] = 0;                     result.m[2][2] = std::cos(radian);  result.m[2][3] = 0;
	result.m[3][0] = 0;                    result.m[3][1] = 0;                     result.m[3][2] = 0;                 result.m[3][3] = 1;

	return result;

}


Matrix4x4 MakeRotateZMatrix(float radian)
{
	Matrix4x4 result;

	result.m[0][0] = std::cos(radian);      result.m[0][1] = std::sin(radian);     result.m[0][2] = 0;                 result.m[0][3] = 0;
	result.m[1][0] = -std::sin(radian);     result.m[1][1] = std::cos(radian);     result.m[1][2] = 0;                 result.m[1][3] = 0;
	result.m[2][0] = 0;                     result.m[2][1] = 0;                    result.m[2][2] = 1;                 result.m[2][3] = 0;
	result.m[3][0] = 0;                     result.m[3][1] = 0;                    result.m[3][2] = 0;                 result.m[3][3] = 1;

	return result;

}

//=================================================================================================


//===================================== affine行列の作成関数 ======================================

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 rotateMatrix = Multiply(Multiply(MakeRotateXMatrix(rotate.x), MakeRotateYMatrix(rotate.y)), MakeRotateZMatrix(rotate.z));
	return Multiply(Multiply(MakeScaleMatrix(scale), rotateMatrix), MakeTranslateMatrix(translate));
}

//=================================================================================================


//=========================== 3次元ベクトルを同次座標として変更する ===============================

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix)
{
	Vector3 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;
	return result;
}

//=================================================================================================


//======================================= 転置行列の作成関数 ======================================

Matrix4x4 Transpose(const Matrix4x4& m) {
	Matrix4x4 result = {};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m.m[j][i];
		}
	}

	return result;
}

//=================================================================================================


//======================================= 単位行列の作成関数 ======================================

Matrix4x4 MakeIdentity4x4() {
	Matrix4x4 result = {};
	for (int i = 0; i < 4; i++) {
		result.m[i][i] = 1;
	}

	return result;
}

//=================================================================================================


//====================================== 正射影行列の作成関数 =====================================

Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {
	Matrix4x4 result;

	result.m[0][0] = 2 / (right - left);                  result.m[0][1] = 0;                                    result.m[0][2] = 0;                                   result.m[0][3] = 0;
	result.m[1][0] = 0;                                   result.m[1][1] = 2 / (top - bottom);                   result.m[1][2] = 0;                                   result.m[1][3] = 0;
	result.m[2][0] = 0;                                   result.m[2][1] = 0;                                    result.m[2][2] = 1 / (farClip - nearClip);            result.m[2][3] = 0;
	result.m[3][0] = (left + right) / (left - right);     result.m[3][1] = (top + bottom) / (bottom - top);     result.m[3][2] = nearClip / (nearClip - farClip);     result.m[3][3] = 1;

	return result;
}

//=================================================================================================


//===================================== 透視投影行列の作成関数 ====================================

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
	Matrix4x4 result;
	result.m[0][0] = 1 / aspectRatio * (1 / std::tan(fovY / 2));   result.m[0][1] = 0;                        result.m[0][2] = 0;                                                               result.m[0][3] = 0;
	result.m[1][0] = 0;                                            result.m[1][1] = 1 / std::tan(fovY / 2);   result.m[1][2] = 0;                                                               result.m[1][3] = 0;
	result.m[2][0] = 0;                                            result.m[2][1] = 0;                        result.m[2][2] = farClip / (farClip - nearClip);                                  result.m[2][3] = 1;
	result.m[3][0] = 0;                                            result.m[3][1] = 0;                        result.m[3][2] = (-nearClip * farClip * std::cos(0.0f)) / (farClip - nearClip);   result.m[3][3] = 0;

	return result;
}

//=================================================================================================


//================================= ビューポート変換行列の作成関数 ================================

Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 result;
    result.m[0][0] = width / 2;            result.m[0][1] = 0;                    result.m[0][2] = 0;                       result.m[0][3] = 0;
	result.m[1][0] = 0;                    result.m[1][1] = -height / 2;          result.m[1][2] = 0;                       result.m[1][3] = 0;
	result.m[2][0] = 0;                    result.m[2][1] = 0;                    result.m[2][2] = maxDepth - minDepth;     result.m[2][3] = 0;
	result.m[3][0] = left + width / 2;     result.m[3][1] = top + height / 2;     result.m[3][2] = minDepth;                result.m[3][3] = 1;

	return result;
}

//=================================================================================================