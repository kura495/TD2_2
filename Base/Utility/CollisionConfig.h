#pragma once
#include<cstdint>

//プレイヤー陣営
const uint32_t kCollitionAttributePlayer = 0b1;
//敵陣営
const uint32_t kCollitionAttributeEnemy = 0b1 << 1;
//地面
const uint32_t kCollitionAttributeGround = 0b1 << 2;
const uint32_t kCollitionAttributeMoveGround = 0b1 << 3;
//ゴール
const uint32_t kCollitionAttributeGoal = 0b1 <<4;
//武器
const uint32_t kCollitionAttributeWeapon = 0b1 << 5;
//壁
const uint32_t kCollitionAttributeWall = 0b1 << 6;
//バフアイテム
const uint32_t kCollitionAttributeBuffItem = 0b1 << 7;



enum ColliderType {
	Circle,
	Box,
	OBBox,
};