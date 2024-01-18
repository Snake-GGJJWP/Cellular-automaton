#pragma once

class FrameLimitter
{
public:
	FrameLimitter(int fps);
	
	// if fps < 0 - don't limit framerate
	void setFPS(int fps) { this->fps = fps; }
	int getFPS() { return fps;  }
	
	void wait();

private:
	int fps; // if <0, don't limit the framrate
};
