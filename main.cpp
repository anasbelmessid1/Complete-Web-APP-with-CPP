#include <QApplication>
#include "hexgame.h"

hexgame* game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game = new hexgame();
    game->show();
    game->displayMainMenu();

    return a.exec();
}
