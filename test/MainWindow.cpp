#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    this->_CreateLayouts();
    this->_CreateWidgets();
    this->_CreateConnections();
}

MainWindow::~MainWindow() {
    delete m_Composer;
    delete m_NextButton;
    delete m_PreviousButton;
    delete m_Layout;
}

void MainWindow::_CreateLayouts() {
    m_Layout = new QGridLayout();  // NOLINT

    this->setCentralWidget(new QWidget(this));  // NOLINT
    this->centralWidget()->setLayout(m_Layout);
}

void MainWindow::_CreateWidgets() {
    QList<QWidget *> widgets;
    for (int i = 0; i < 5; i++) {
        m_Buttons.append(new QPushButton("Button " + QString::number(i)));    // NOLINT
        m_Checkboxs.append(new QCheckBox("Checkbox " + QString::number(i)));  // NOLINT
        widgets.append(m_Buttons[i]);
        widgets.append(m_Checkboxs[i]);
    }
    m_NextButton = new QPushButton("Next", this);          // NOLINT
    m_PreviousButton = new QPushButton("Previous", this);  // NOLINT
    m_Layout->addWidget(m_NextButton, 0, 0);
    m_Layout->addWidget(m_PreviousButton, 1, 0);

    m_Composer = new xaprier::qt::widgets::XQWidgetComposer(widgets, this);  // NOLINT
    m_Layout->addWidget(m_Composer, 0, 1, 2, 1);
}

void MainWindow::_CreateConnections() {
    QObject::connect(m_NextButton, &QPushButton::clicked, m_Composer, &xaprier::qt::widgets::XQWidgetComposer::sl_Next);
    QObject::connect(m_PreviousButton, &QCheckBox::clicked, m_Composer, &xaprier::qt::widgets::XQWidgetComposer::sl_Previous);
}