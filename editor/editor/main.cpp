#include "editor.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	Editor editorWindow;
	editorWindow.show();
	return app.exec();
}