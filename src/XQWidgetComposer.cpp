#include "XQWidgetComposer.hpp"

#include <QtAlgorithms>

namespace xaprier::Qt::Widgets {

XQWidgetComposer::XQWidgetComposer(QList<QWidget *> widgets, QWidget *parent) : QWidget(parent), m_Widgets(std::move(widgets)) {
    m_StackedWidget = new QStackedWidget(this);
    m_Layout = new QHBoxLayout(this);
    m_Layout->addWidget(m_StackedWidget);
    m_Layout->setContentsMargins(0, 0, 0, 0);
    m_Layout->setSpacing(0);
    this->setLayout(m_Layout);

    SetWidgets(m_Widgets);
}

XQWidgetComposer::~XQWidgetComposer() {
    delete m_Layout;
    qDeleteAll(m_Widgets);
    m_Widgets.clear();
}

void XQWidgetComposer::SetWidgets(QList<QWidget *> widgets) {
    if (m_StackedWidget) {
        m_Layout->removeWidget(m_StackedWidget);
        delete m_StackedWidget;

        m_StackedWidget = new QStackedWidget(this);
        m_Layout->addWidget(m_StackedWidget);
    }

    for (QWidget *widget : widgets) {
        m_StackedWidget->addWidget(widget);
    }

    if (!widgets.isEmpty()) {
        m_StackedWidget->setCurrentIndex(0);
    }
}

void XQWidgetComposer::Show(int index) {
    if (index >= 0 && index < m_StackedWidget->count()) {
        m_StackedWidget->setCurrentIndex(index);
    }
}

void XQWidgetComposer::Show(QWidget *widget) {
    int index = m_StackedWidget->indexOf(widget);
    if (index != -1) {
        m_StackedWidget->setCurrentIndex(index);
    }
}

void XQWidgetComposer::Previous() {
    int index = m_StackedWidget->currentIndex();
    if (index > 0 && index < m_StackedWidget->count()) {
        m_StackedWidget->setCurrentIndex(index - 1);
    }
}

void XQWidgetComposer::Next() {
    int index = m_StackedWidget->currentIndex();
    if (index >= 0 && index < m_StackedWidget->count() - 1) {
        m_StackedWidget->setCurrentIndex(index + 1);
    }
}

void XQWidgetComposer::sl_ShowWidget(int index) {
    this->Show(index);
}

void XQWidgetComposer::sl_ShowWidget(QWidget *widget) {
    this->Show(widget);
}

void XQWidgetComposer::sl_Previous() {
    this->Previous();
}

void XQWidgetComposer::sl_Next() {
    this->Next();
}

}  // namespace xaprier::Qt::Widgets