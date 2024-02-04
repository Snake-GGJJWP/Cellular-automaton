#include "Edit.h"

class FrameEdit : public Edit
{
public:
	FrameEdit(Window* win, 
			  SDL_Rect container,
			  SDL_Color textColor,
			  std::string *ttfFile,
			  int fontSize,
		      std::string* pathToTexture,
			  std::string* startText);

	void handleEvent(SDL_Event* event) override;
	void render() override;

	/*int getFrames() {
		return std::stoi(*editString);
	}

	void setTextColor(SDL_Color color) {
		textColor = color;
	}*/

private:
	void renderText();
	bool isCursorInField(int x, int y);

	bool focus = false;
	bool isHovered = false;

	SDL_Color textColor;
	SDL_Rect container;
	SDL_Texture* texture;
	SDL_Renderer* renderer;
};
