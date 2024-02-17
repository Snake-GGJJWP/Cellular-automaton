#include "Edit.h"
#include <set>

class FrameEdit : public Edit
{
public:
	FrameEdit(Window* win,
			  TTF_Font* font,
			  SDL_Rect container,
			  SDL_Color textColor,
			  std::string* pathToTexture);

	void setTextColorError();
	void setTextColorOK();

	// Symbols that are allowed to be in this edit field
	const std::set <char> ALLOWED_SYMBOLS = { '1','2','3','4','5','6','7','8','9','0','-','+' };

private:
	SDL_Color textColorOK;
	SDL_Color textColorError{255,0,0,255}; // red
};
