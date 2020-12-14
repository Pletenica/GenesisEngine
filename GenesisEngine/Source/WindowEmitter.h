#pragma once

#include "EditorWindow.h"

class WindowEmitter : public EditorWindow {
public:
	WindowEmitter();
	~WindowEmitter();
	void Draw() override;
};