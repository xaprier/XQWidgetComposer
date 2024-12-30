#ifndef XQWIDGETCOMPOSER_HPP
#define XQWIDGETCOMPOSER_HPP

#include <QHBoxLayout>
#include <QList>
#include <QWidget>

namespace xaprier::qt::widgets {

class XQWidgetComposer : public QWidget {
    Q_OBJECT
  public:
    XQWidgetComposer(QList<QWidget *> widgets = {}, QWidget *parent = nullptr);
    ~XQWidgetComposer() override;

    XQWidgetComposer(const XQWidgetComposer &other) = delete;
    XQWidgetComposer &operator=(const XQWidgetComposer &other) = delete;
    XQWidgetComposer(XQWidgetComposer &&other) noexcept = delete;
    XQWidgetComposer &operator=(XQWidgetComposer &&other) noexcept = delete;

    [[nodiscard]] QHBoxLayout *GetLayout() const { return m_Layout; }
    [[nodiscard]] int GetActive() const { return m_Active; }
    [[nodiscard]] QWidget *GetWidget(int index) const;
    [[nodiscard]] QList<QWidget *> GetWidgets() const;

    void SetWidgets(QList<QWidget *> widgets = {});
    void SetWidget(int index = 0, QWidget *widget = nullptr);

    void Show(int index);
    void Show(QWidget *widget);
    void Previous();
    void Next();

  public slots:
    void sl_ShowWidget(int index);
    void sl_ShowWidget(QWidget *widget);
    void sl_Previous();
    void sl_Next();

  protected:
    virtual void SetItem(int index);

  private:
    int m_Active;
    QList<QWidget *> m_Widgets;
    QHBoxLayout *m_Layout;
};

}  // namespace xaprier::qt::widgets

#endif  // XQWIDGETCOMPOSER_HPP