#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QCheckBox>
#include <QGridLayout>
#include <QMainWindow>
#include <QPushButton>

#include "XQWidgetComposer.hpp"

class MainWindow : public QMainWindow {  // NOLINT
    Q_OBJECT
  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

  protected:
    void _CreateWidgets();
    void _CreateLayouts();
    void _CreateConnections();

  private:
    xaprier::qt::widgets::XQWidgetComposer *m_Composer;
    QPushButton *m_NextButton, *m_PreviousButton;
    QGridLayout *m_Layout;
    QList<QPushButton *> m_Buttons;
    QList<QCheckBox *> m_Checkboxs;
};

#endif  // MAINWINDOW_HPP