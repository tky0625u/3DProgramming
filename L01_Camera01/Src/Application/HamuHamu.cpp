﻿#include"HamuHamu.h"

HamuHamu::HamuHamu()
{

}

HamuHamu::~HamuHamu()
{

}

void HamuHamu::Init()
{
	m_spPoly = std::make_shared<KdSquarePolygon>();
	m_spPoly->SetMaterial("Asset/Data/LessonData/Character/hamu.png");
	m_spPoly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
}

void HamuHamu::Update()
{
	//キャラクターの移動速度（マネしちゃだめですよ）
	float moveSpd = 0.05f;
	Math::Vector3 nowPos = m_mWorld.Translation();

	//移動したい「方向ベクトル」=絶対に長さが「１」でなければならない！！
	Math::Vector3 moveVec = Math::Vector3::Zero;
	if (GetAsyncKeyState('W') & 0x8000) { moveVec.z = 1.0f; }
	if (GetAsyncKeyState('A') & 0x8000) { moveVec.x = -1.0f; }
	if (GetAsyncKeyState('S') & 0x8000) { moveVec.z = -1.0f; }
	if (GetAsyncKeyState('D') & 0x8000) { moveVec.x = 1.0f; }

	//正規化（ノーマライズ）
	moveVec.Normalize();

	moveVec *= moveSpd;
	nowPos += moveVec;

	//キャラクターのワールド行列を創る処理
	m_mWorld = Math::Matrix::CreateTranslation(nowPos);
}

void HamuHamu::DrawLit()
{
	//Math::Matrix _mat = Math::Matrix::CreateTranslation(m_pos.x,m_pos.y,m_pos.z);
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
}