#ifndef _RENDER_H_
#define _RENDER_H_

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480

#include "camera.h"

namespace Render{
	int  Init(int* argc, char** argv);
	void Draw();
	void Resize(int width, int height);

	int  Draw_Callback_Add(void (*function)());
	void Draw_Callback_Delete(int function_id);

	int  GUI_Draw_Callback_Add(void (*function)());
	void GUI_Draw_Callback_Delete(int function_id);

	void Draw_Callbacks_Delete();

	Camera* Camera_Get();
};

#endif
