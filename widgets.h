#ifndef WIDGETS_H
#define WIDGETS_H

#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFrame>

// 1. Метка
class LogLabel : public QLabel { // QLabel — это виджет Qt для отображения текста (или картинки)
public:
    explicit LogLabel(const QString &text, QWidget *parent = nullptr) // explicit - защита от случайного вызова конструктора. Первый параметр это текст а второй параметр это родитель
        : QLabel(text, parent) // Перед тем как выполнить тело моего конструктора, сначала вызови конструктор родителя QLabel с параметрами text и parent
    {
        qDebug() << "[CREATE] LogLabel" << text; // вывод в консоль
    }
    ~LogLabel() override { // override: проверка на этапе компиляции — если в QLabel нет виртуального деструктора (а он есть) — ошибка.
        qDebug() << "[DESTROY] LogLabel" << text();
    }
};

// 2. Поле ввода
class LogLineEdit : public QLineEdit { // QLineEdit - поле ввода
public:
    explicit LogLineEdit(QWidget *parent = nullptr)
        : QLineEdit(parent)
    {
        qDebug() << "[CREATE] LogLineEdit";
    }
    ~LogLineEdit() override {
        qDebug() << "[DESTROY] LogLineEdit";
    }
};

// 3. Кнопка
class LogButton : public QPushButton { //QPushButton - кнопка
public:
    explicit LogButton(const QString &text, QWidget *parent = nullptr)
        : QPushButton(text, parent)
    {
        qDebug() << "[CREATE] LogButton" << text;
    }
    ~LogButton() override {
        qDebug() << "[DESTROY] LogButton" << text();
    }
};

// 4. Панель (контейнер)
class LogPanel : public QFrame { // QFrame — это коробка или панель, внутри которой лежат другие элементы.
public:
    explicit LogPanel(const QString &name, QWidget *parent = nullptr) // name - имя панели
        : QFrame(parent)
    {
        setObjectName(name);//устанавливаем имя панели
        qDebug() << "[CREATE] LogPanel" << name;
    }
    ~LogPanel() override {
        qDebug() << "[DESTROY] LogPanel" << objectName(); // objectName - возвращает имя объекта
    }
};

#endif // WIDGETS_H