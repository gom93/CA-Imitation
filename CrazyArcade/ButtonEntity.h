#pragma once

#include "DynamicEntity.h"

enum class CLICK_STATE
{
	Default,
	LButtonDown,
	RButtonDown,
};

class ButtonEntity : public DynamicEntity
{
public:
	ButtonEntity() = default;
	ButtonEntity(ENTITY_INDEX id, const VEC2& pos, const VEC2& size, HBITMAP bitmap, int cols, int rows);
	virtual ~ButtonEntity() = default;

	virtual void Input() override;
	virtual void Update() override;

private:
	CLICK_STATE _state = CLICK_STATE::Default;
	POINT		_cursor = {};
	bool		_isOverlapped = false;
	bool		_isPlayingAudio = false;
};

