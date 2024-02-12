#include "Edit.h"
#include <set>

class FrameEdit : public Edit
{
public:
	FrameEdit(Window* win, 
			  SDL_Rect container,
			  SDL_Color textColor,
			  std::string *ttfFile,
			  int fontSize,
		      std::string *pathToTexture,
			  std::string *startText);

	FrameEdit(Window* win,
			  SDL_Rect container,
			  SDL_Color textColor,
			  TTF_Font* font,
			  std::string* pathToTexture,
			  std::string* startText);

	void handleEvent(SDL_Event* event) override;
	void render() override;

	void printName() override { std::cout << "I'm frameEdit!\n"; }

	void setTextColorError() { textColorCurrent = textColorError; }
	void setTextColorOK() { textColorCurrent = textColorOK; }

	// Symbols that are allowed to be in this edit field
	const std::set <char> ALLOWED_SYMBOLS = { '1','2','3','4','5','6','7','8','9','0','-','+' };

private:
	void renderText();
	bool isCursorInField(int x, int y);

	bool isHovered = false;

	SDL_Color textColorCurrent;
	SDL_Color textColorOK;
	SDL_Color textColorError{255,0,0,255}; // red
	SDL_Rect container;
	SDL_Texture* texture = nullptr;
	SDL_Texture* textTexture = nullptr;
	SDL_Renderer* renderer;
};
