#ifndef EDITOR_DEBUG_H
#define EDITOR_DEBUG_H

void OnLeft();
void OnRight();
void OnUp();
void OnDown();
void Init(HWND hWnd);
void Deinit();
void Render(vec2 cursorPos);

#endif