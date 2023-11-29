#pragma once
#include "Math_Structs.h"
#include "CollisionConfig.h"
#include "Base/WorldTransform.h"
#include <cstdint>

class Collider {
public:

	virtual ~Collider(){};
	//衝突時に呼ばれる関数
	virtual void OnCollision(Collider* collider) = 0;
	float GetRadius() { return Radius_; }

	uint32_t GetcollitionAttribute() const { return collisionAttribute_; }
	/// <summary>
	/// 衝突属性
	/// </summary>
	/// <param name="collisionAttribute"></param>
	void SetcollitionAttribute(uint32_t collisionAttribute) {
		collisionAttribute_ = collisionAttribute;
	}
	uint32_t GetcollisionMask() const { return collisionMask_; }
	/// <summary>
	/// 衝突マスク
	/// </summary>
	/// <param name="collisionMask">基本はSetcollitionAttributeに入れたものに~を付けてビット反転</param>
	void SetcollisionMask(uint32_t collisionMask){

		collisionMask_ = collisionMask;
	}

	int GetId() { return Id_; }

	Vector3 GetWorldPosition() { return { world_.matWorld_.m[3][0],world_.matWorld_.m[3][1] ,world_.matWorld_.m[3][2] }; }

protected:

	void SetId(int Type) { Id_ = Type; }
	/// <summary>
	/// 原点
	/// </summary>
	WorldTransform world_;
private:

	uint32_t Id_ = 0xffffffff;


	/// <summary>
	/// 衝突属性(自分)
	/// </summary>
	uint32_t collisionAttribute_ = 0xffffffff;
	/// <summary>
	/// 衝突マスク(相手)
	/// </summary>
	uint32_t collisionMask_ = 0xffffffff;

	float Radius_;


};
