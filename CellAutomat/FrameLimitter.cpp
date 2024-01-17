#include <chrono>
#include <thread>
#include "FrameLimitter.h"
#include <iostream>

FrameLimitter::FrameLimitter(int fps) {
	this->fps = fps;
	std::cout << "FPS: " << fps << "\n";
}

void FrameLimitter::wait() {

	if (fps <= 0) {
		return;
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(1000/fps));
}