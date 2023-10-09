#include <QApplication>
#include "Form.h"

int main(int argc, char* argv[])
{
	auto application = QApplication(argc, argv);
	auto mian_window = Form();
	mian_window.show();
	return QApplication::exec();
}
