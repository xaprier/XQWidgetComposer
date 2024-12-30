#include "XQWidgetComposer.hpp"

#include <QtAlgorithms>

namespace xaprier::qt::widgets {

XQWidgetComposer::XQWidgetComposer(QList<QWidget *> widgets, QWidget *parent) : QWidget(parent), m_Widgets(std::move(widgets)) {
    m_Layout = new QHBoxLayout(this);  // NOLINT
    m_Layout->setContentsMargins(0, 0, 0, 0);
    m_Layout->setSpacing(0);
    m_Layout->setAlignment(Qt::AlignCenter);
    if (!m_Widgets.isEmpty()) {
        m_Active = 0;
        this->SetItem(m_Active);
    }
    this->setLayout(m_Layout);
}

XQWidgetComposer::~XQWidgetComposer() {
    delete m_Layout;
    qDeleteAll(m_Widgets);
    m_Widgets.clear();
}

void XQWidgetComposer::SetWidgets(QList<QWidget *> widgets) {
    this->m_Widgets = widgets;
    if (!m_Widgets.isEmpty()) {
        m_Active = 0;
        this->SetItem(m_Active);
    }
}

void XQWidgetComposer::SetWidget(int index, QWidget *widget) {
    if (index < 0 || index >= m_Widgets.size()) {
        return;
    }

    m_Widgets.replace(index, widget);
    if (m_Active == index) {
        this->SetItem(m_Active);
    }
}

QWidget *XQWidgetComposer::GetWidget(int index) const {
    if (index < 0 || index >= m_Widgets.size()) {
        return nullptr;
    }

    return m_Widgets.at(index);
}

void XQWidgetComposer::Show(int index) {
    if (index < 0 || index >= m_Widgets.size()) {
        return;
    }

    m_Active = index;
    this->SetItem(m_Active);
}

void XQWidgetComposer::Show(QWidget *widget) {
    int index = m_Widgets.indexOf(widget);
    if (index == -1) {
        return;
    }

    m_Active = index;
    this->SetItem(m_Active);
}

void XQWidgetComposer::Previous() {
    m_Active = (m_Active - 1 + m_Widgets.size()) % m_Widgets.size();
    this->SetItem(m_Active);
}

void XQWidgetComposer::Next() {
    m_Active = (m_Active + 1) % m_Widgets.size();
    this->SetItem(m_Active);
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

void XQWidgetComposer::SetItem(int index) {
    if (index < 0 || index >= m_Widgets.size()) {
        return;
    }

    QLayoutItem *item;  // NOLINT
    while ((item = m_Layout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            item->widget()->setParent(nullptr);
        }
        delete item;  // NOLINT
    }

    m_Layout->addWidget(m_Widgets.at(index));
    this->update();
}
}  // namespace xaprier::qt::widgets