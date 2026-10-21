#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPointer>
#include <QVBoxLayout>
#include "widgets.h" // Подключаем наши логирующие классы

class MainWindow : public QWidget
{
    Q_OBJECT // необходимо прописывать для работы с сигналами и слотами

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void moveMovableWidget(); // Смена родителя
    void deletePanel();       // Удаление панели
    void demoDetaching();     // Отвязка setParent(nullptr)

private:
    void setupUi();
    void setStatus(const QString &text);

    // QPointer безопасно обнуляется, если объект удален
    QPointer<QVBoxLayout> m_rootLayout; // QVBoxLayout -  вертикальный layout (компоновщик) из Qt. Он расставляет дочерние виджеты сверху вниз.
    QPointer<QVBoxLayout> m_panelLayout; // в m_rootLayout и m_panelLayout мы потом будем добавлять виджеты

    QPointer<LogLabel> m_title;
    QPointer<LogLineEdit> m_input;
    QPointer<LogLabel> m_status;

    QPointer<LogPanel> m_panel;          // Панель, которую будем удалять
    QPointer<LogButton> m_movable;       // Кнопка, которую будем перемещать
    QPointer<LogButton> m_moveButton;
    QPointer<LogButton> m_deleteButton;
};

#endif // MAINWINDOW_H