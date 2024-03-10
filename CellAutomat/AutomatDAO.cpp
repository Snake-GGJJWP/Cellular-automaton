#include <fstream>
#include <filesystem>

#include "AutomatDAO.h"

Automat* AutomatDAO::load(const char* pathToFile) {
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

	Automat* automat = new Automat();

	try {
		automat->width = out["width"];
		automat->height = out["height"];
		automat->rule = out["rule"];

		std::vector<size_t> arr = out["rleField"];
		automat->rleField = arr;
	}
	catch (json::type_error& ex) {
		std::cout << "Invalid types or field names" << ex.what();
		return NULL;
	}

	return automat;
}

void AutomatDAO::save(const char* pathToFile, Automat* automat) {
	std::filesystem::path s = pathToFile;

	if (s.extension() != ".json") {
		std::cout << "Wrong file type\n";
		return;
	}

	std::ofstream file(pathToFile);
	if (!file.is_open()) {
		std::cout << "Failed to open file\n";
		return;
	}

	json in;

	in["width"] = automat->width;
	in["height"] = automat->height;
	in["rule"] = automat->rule;
	in["rleField"] = automat->rleField;

	file << in.dump(4);
}