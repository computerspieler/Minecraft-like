#ifndef _RENDER_H_
#define _RENDER_H_

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480

namespace Render{
	int  Init(int* argc, char** argv);
	void Draw();

	int  Add_Render_Function(void (*function)());
	void Delete_Render_Funtion(int function_id);
};

#endif
