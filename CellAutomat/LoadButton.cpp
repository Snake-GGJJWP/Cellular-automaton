#include "LoadButton.h"
#include "tinyfiledialogs.h"

LoadButton::LoadButton(Window* win,
					   Field* field,
					   PresetController* presetController,
					   SDL_Rect cont, 
					   char* pathToTexture,
					   char* pathToTextureHover) : 
	Button(win, cont),
	field(field),
	presetController(presetController)
{
	setTexture(pathToTexture);
	setTextureHover(pathToTextureHover);
}

void LoadButton::onClick() {
	char const* patterns[1] = { "*.json" };
	const char* s = tinyfd_openFileDialog("TESTING",
									"../presets/",
									1,
									patterns,
									"presets",
									0);
	//char* s = tinyfd_selectFolderDialog("TESTING",
	//									"");
	/*char* s = tinyfd_saveFileDialog("TESTING",
									"",
									1,
									patterns,
									"presets");*/
	if (s == NULL) {
		std::cout << "NOTHING PICKED\n";
		return;
	}

	int k = 0;
	while (s[k] != '\0') {
		std::cout << s[k];
		k++;
	}
	std::cout << "\n";

	PresetDTO* preset = presetController->load(s);

	if (preset == NULL) {
		return;
	}

	field->loadField(preset->height, preset->width, preset->field);


	
}

// ## DEPRECATED CODE THAT I CAN'T DELETE FOR SOME REASON ##

//void printMat2(bool** mat, int n, int m) {
//	// system("CLS");
//	for (int i = 0; i < n; i++) {
//		for (int j = 0; j < m; j++) {
//			std::cout << (mat[i][j] ? "1" : "0") << " ";
//		}
//		std::cout << std::endl;
//	}
//}

//int k = 0;
	//while (s[k] != '\0') {
	//	std::cout << s[k];
	//	k++;
	//}
	//std::cout << "\n";

	//std::ifstream file(s); // For now we'll read from file

	//if (!file) {
	//	std::cout << "File is not opened" << std::endl;
	//}

	//int n;
	//file >> n;

	//int m;
	//file >> m;

	//float scaleX;
	//file >> scaleX;

	//float scaleY;
	//file >> scaleY;

	//bool** field = new bool* [n];
	//for (int i = 0; i < n; i++) {
	//	field[i] = new bool[m];
	//}

	//int p;
	//int i = 0;
	//for (file >> p; !file.eof(); file >> p) {
	//	if (i >= n * m) {
	//		std::cout << "Fuck" << std::endl;
	//	}
	//	field[i / m][i % m] = (p ? true : false);
	//	i++;
	//}

	//printMat2(field, n, m);