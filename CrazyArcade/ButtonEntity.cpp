#include "pch.h"
#include "ButtonEntity.h"

ButtonEntity::ButtonEntity(ENTITY_INDEX id, const VEC2& pos, const VEC2& size, HBITMAP bitmap, int cols, int rows)
	: DynamicEntity(id, pos, size, bitmap, cols, rows)
{
}

void ButtonEntity::Input()
{
	// Sprite 이미지일 경우 적용
	if (_cols * _rows <= 1)
	{
		return;
	}

	GetCursorPos(&_cursor);
	ScreenToClient(Game::Get().GetHwnd(), &_cursor);

	// 커서가 이미지위에 있을 경우 이미지를 변환시킨다
	if ((_pos.x <= _cursor.x && _cursor.x <= _pos.x + _imageWidth)
		&& (_pos.y <= _cursor.y && _cursor.y <= _pos.y + _imageHeight))
	{
		_isOverlapped = true;

		if (_isPlayingAudio == false)
		{
			AudioManager::Get().PlayEffectSound(EFFECT_SOUND::OverlappedButton);
			_isPlayingAudio = true;
		}
	}
	else
	{
		_isOverlapped = false;
		_isPlayingAudio = false;
	}

	if (_isOverlapped == false)
	{
		return;
	}

	if (GetAsyncKeyState(MK_LBUTTON) & 0x8000)
	{
		_state = CLICK_STATE::LButtonDown;
	}
	else if (GetAsyncKeyState(MK_RBUTTON) & 0x8000)
	{
		_state = CLICK_STATE::RButtonDown;
	}

	if (CLICK_STATE::LButtonDown == _state)
	{
		if (!(GetAsyncKeyState(MK_LBUTTON) & 0x8000))
		{
			MessageQueue::AddEvent({ _id, false });
			_state = CLICK_STATE::Default;
		}
	}
	else if (CLICK_STATE::RButtonDown == _state)
	{
		if (!(GetAsyncKeyState(MK_RBUTTON) & 0x8000))
		{
			MessageQueue::AddEvent({ _id, true });
			_state = CLICK_STATE::Default;
		}
	}
}

void ButtonEntity::Update()
{
	if (_isOverlapped == false)
	{
		_imageIndex = 0;
	}
	else
	{
		_imageIndex = 1;
	}
}
