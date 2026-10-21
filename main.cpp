#include "mainwindow.h"     // ← заголовок главного окна
#include <QApplication>     // ← GUI-приложение (не QCoreApplication!)

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);   // 1. Создаём приложение

    MainWindow w;                 // 2. Создаём главное окно
    w.show();                     // 3. Показываем его

    return a.exec();              // 4. Запускаем цикл событий
}