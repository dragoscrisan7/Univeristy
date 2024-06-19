#include <QApplication>
#include <QPushButton>
#include "repository/CodeRepository.h"
#include "ui/ProgrammerWindow.h"


int main(int argc, char *argv[]) {
    CodeRepository codeRepository;
    vector<ProgrammerWindow*> windows;
    
    QApplication a(argc, argv);
    for (const auto &programmer: codeRepository.getProgrammers()) {
        auto window = new ProgrammerWindow(nullptr, codeRepository, programmer);
        window->show();
        windows.push_back(window);
    }

    const auto execResult = QApplication::exec();

    for (const auto &window: windows) delete window;

    return execResult;
}
