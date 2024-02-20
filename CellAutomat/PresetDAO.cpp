#include <fstream>
#include <filesystem>

#include "PresetDAO.h"

Preset* PresetDAO::load(const char* pathToFile) {
	std::filesystem::path s = pathToFile;

	if (s.extension() != ".json") {
		std::cout << "Wrong file type\n";
		return NULL;
	}

	std::ifstream file(pathToFile);
	if (!file.is_open()) {
		std::cout << "Failed to open file\n";
		return NULL;
	}

	json out;

	try {
		out = json::parse(file);
	}
	catch (const json::parse_error& ex) {
		std::cout << "Parse error: " << ex.what();
		return NULL;
	}

	Preset* preset = new Preset();

	try {
		preset->width = out["width"];
		preset->height = out["height"];
		preset->rule = out["rule"];

		std::vector<size_t> arr = out["rleField"];
		preset->rleField = arr;
	}
	catch (json::type_error& ex) {
		std::cout << "Invalid types or field names" << ex.what();
		return NULL;
	}

	return preset;
}

void PresetDAO::save(const char* pathToFile, Preset* preset) {
}