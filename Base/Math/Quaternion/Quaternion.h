#pragma once

#include "Base/Math/VectorCalc.h"
#include "Base/Math/MatrixCalc.h"

struct Quaternion {
	float x;
	float y;
	float z;
	float w;
};
//Quaternionの積
Quaternion Multiply(const Quaternion& lhs, const Quaternion&rhs);
//単位Quaternionを返す
Quaternion IdentityQuaternion();
//共役Quaternionを返す
Quaternion Conjugate(const Quaternion& quaternion);
//Quaternionのnormを返す
float Norm(const Quaternion& quaternion);
//正規化したQuaternionを返す
Quaternion Normalize(const Quaternion& quaternion);
//逆Quaternionを返す
Quaternion Inverse(const Quaternion& quaternion);
//任意軸回転を表すQuaternionの生成
Quaternion MakeRotateAxisAngleQuaternion(const Vector3& axis, float angle);
//ベクトルをQuaternionで回転させた結果のベクトルを求める
Vector3 RotateVector(const Vector3& vector,const Quaternion& quaternion);
//Quaternionから回転行列を求める
Matrix4x4 MakeRotateMatrix(const Quaternion& quaternion);