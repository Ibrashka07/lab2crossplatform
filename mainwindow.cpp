#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setupUi();
}

MainWindow::~MainWindow()
{
    qDebug() << "[DESTROY] MainWindow";
}

void MainWindow::setupUi()
{
    setWindowTitle("Qt Object Tree Demo"); // заголовок окна (синяя полоска сверху).
    resize(500, 600); // размер окна (ширина 500, высота 600).
    setObjectName("MainWindow");  // задаём имя объекту

    m_rootLayout = new QVBoxLayout(this); // this — это указатель на текущий объект. В данном случае — на сам MainWindow (наше окно).

    // --- 1. Создаем виджеты с родителем (this) ---
    m_title = new LogLabel("Дерево объектов Qt", this);
    m_rootLayout->addWidget(m_title.data()); // addWidget— метод компоновщика, который означает «добавь виджет» .data возвращает обычныый указатель из

    m_input = new LogLineEdit(this);
    m_input->setPlaceholderText("Введите текст...");
    m_rootLayout->addWidget(m_input.data());

    m_status = new LogLabel("Статус: окно создано", this);
    m_status->setWordWrap(true);
    m_rootLayout->addWidget(m_status.data());

    // --- 2. Создаем панель (родитель - окно) ---
    m_panel = new LogPanel("Панель-владелец", this);
    m_rootLayout->addWidget(m_panel.data());

    // Внутри панели создаем свой Layout
    m_panelLayout = new QVBoxLayout(m_panel.data());

    // Дети панели (родитель - m_panel)
    LogButton *staticBtn = new LogButton("Статическая кнопка в панели", m_panel.data());
    m_panelLayout->addWidget(staticBtn);

    m_movable = new LogButton("Перемещаемый виджет (в панели)", m_panel.data());
    m_panelLayout->addWidget(m_movable.data());

    // --- 3. Кнопки управления (родитель - окно) ---
    m_moveButton = new LogButton("Переместить: панель <-> окно", this);
    connect(m_moveButton.data(), &QPushButton::clicked, this, &MainWindow::moveMovableWidget);
    m_rootLayout->addWidget(m_moveButton.data());

    m_deleteButton = new LogButton("Удалить панель (deleteLater)", this);
    connect(m_deleteButton.data(), &QPushButton::clicked, this, &MainWindow::deletePanel);
    m_rootLayout->addWidget(m_deleteButton.data());

    LogButton *detachBtn = new LogButton("Демо setParent(nullptr)", this);
    connect(detachBtn, &QPushButton::clicked, this, &MainWindow::demoDetaching);
    m_rootLayout->addWidget(detachBtn);

    m_rootLayout->addStretch(); // Прижимаем всё наверх

    setStatus("Готово. Все объекты имеют родителей.");
}

void MainWindow::setStatus(const QString &text)
{
    if (!m_status.isNull()) {
        m_status->setText(text);
    }
}

// Смена родителя
void MainWindow::moveMovableWidget()
{
    if (m_movable.isNull()) {
        setStatus("Виджет уже уничтожен.");
        return;
    }
    if (m_panel.isNull()) {
        setStatus("Панель удалена, вернуть виджет некуда.");
        return;
    }

    if (m_movable->parentWidget() == m_panel.data()) {
        // Двигаем ИЗ панели В окно
        m_panelLayout->removeWidget(m_movable.data()); // Сначала убираем из Layout
        m_movable->setParent(this);                    // Меняем родителя
        m_rootLayout->addWidget(m_movable.data());     // Добавляем в новый Layout
        m_movable->setText("Перемещаемый виджет (в окне)");
        setStatus("setParent(this): панель больше не удалит этот виджет.");
    } else {
        // Двигаем ИЗ окна В панель
        m_rootLayout->removeWidget(m_movable.data());
        m_movable->setParent(m_panel.data());
        m_panelLayout->addWidget(m_movable.data());
        m_movable->setText("Перемещаемый виджет (в панели)");
        setStatus("Виджет снова в панели. Удалится вместе с ней.");
    }
    m_movable->show(); // Обязательно перепоказать после смены родителя
}

// Удаление панели
void MainWindow::deletePanel()
{
    if (m_panel.isNull()) return;

    if (!m_movable.isNull() && m_movable->parentWidget() == m_panel.data()) {
        setStatus("Панель удаляется. Перемещаемый виджет умрет вместе с ней.");
    } else {
        setStatus("Панель удаляется. Виджет вне панели выживет.");
    }

    m_deleteButton->setEnabled(false);
    m_moveButton->setEnabled(false);

    // Безопасное удаление
    m_panel->deleteLater();
}

// Отвязка (демонстрация утечки/ручного удаления)
void MainWindow::demoDetaching()
{
    // Создаем временную панель с двумя детьми
    LogPanel *tempOwner = new LogPanel("TempOwner", this);

    // Стек (!) - это ошибка, но для демо сойдет, мы не будем удалять tempOwner через delete
    // На самом деле создадим в куче, чтобы не упасть
    LogLabel *child1 = new LogLabel("Ребенок TempOwner", tempOwner);
    LogLabel *child2 = new LogLabel("Отвязанный ребенок TempOwner", tempOwner);

    qDebug() << "DEMO: Детей до detach:" << tempOwner->children().size();

    // Отвязываем child2
    child2->setParent(nullptr);
    qDebug() << "DEMO: Детей после detach:" << tempOwner->children().size();

    // Удаляем родителя (child1 умрет, child2 останется висеть в памяти)
    tempOwner->deleteLater();

    // Чтобы не было утечки, child2 нужно удалить вручную
    child2->deleteLater(); // Закомментируйте это, чтобы увидеть ошибку утечки (объект останется жив после закрытия)

    setStatus("Создан TempOwner, child2 отвязан и удален вручную.");
}