# XQWidgetComposer

`XQWidgetComposer` is a Qt-based widget manager for composing and managing a list of `QWidget` objects. It allows you to navigate through a collection of widgets, displaying one at a time, and provides functionality for switching widgets programmatically or through signals and slots.

## Features

- **Widget Navigation**: Easily navigate between widgets using `Previous()` and `Next()` functions.
- **Dynamic Widget Management**: Add, replace, or remove widgets dynamically.
- **Signal-Slot Integration**: Slots for showing widgets by index or pointer, as well as for navigating forward and backward.

## Class Overview
### Constructor
```cpp
XQWidgetComposer(QList<QWidget *> widgets, QWidget *parent = nullptr);
```
- **widgets**: Initial list of widgets to manage.
- **parent**: Parent widget.

### Destructor
```cpp
~XQWidgetComposer();
```
- Cleans up all dynamically allocated widgets and layout.

### Public Methods
- `void SetWidgets(QList<QWidget *> widgets);`
  - Replaces the current widget list with a new one.

- `void SetWidget(int index, QWidget *widget);`
  - Replaces the widget at the specified index.

- `QWidget *GetWidget(int index) const;`
  - Returns the widget at the specified index.

- `void Show(int index);`
  - Displays the widget at the given index.

- `void Show(QWidget *widget);`
  - Displays the specified widget if it exists in the list.

- `void Previous();`
  - Displays the previous widget in the list.

- `void Next();`
  - Displays the next widget in the list.

### Slots
- `void sl_ShowWidget(int index);`
  - Slot to show a widget by index.

- `void sl_ShowWidget(QWidget *widget);`
  - Slot to show a widget by pointer.

- `void sl_Previous();`
  - Slot to navigate to the previous widget.

- `void sl_Next();`
  - Slot to navigate to the next widget.

### Private Methods
- `void SetItem(int index);`
  - Internally handles the layout update to show the specified widget.

## Example Usage

```cpp
#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QObject>
#include <QPushButton>
#include <QWidget>

#include "XQWidgetComposer.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QList<QWidget *> widgets;
    widgets.append(new QLabel("Widget 1"));
    widgets.append(new QLabel("Widget 2"));
    widgets.append(new QLabel("Widget 3"));

    QPushButton *nextButton = new QPushButton("Next Widget");
    QWidget *parentWidget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(parentWidget);
    parentWidget->setLayout(layout);
    xaprier::Qt::Widgets::XQWidgetComposer composer(widgets);
    layout->addWidget(nextButton);
    layout->addWidget(&composer);

    QObject::connect(nextButton, &QPushButton::clicked, &composer, &xaprier::Qt::Widgets::XQWidgetComposer::sl_Next);

    parentWidget->resize(400, 300);
    parentWidget->show();

    return app.exec();
}
```

## Signals and Slots

Connect `XQWidgetComposer` slots to your signals to control widget navigation and display programmatically. Example:

```cpp
connect(buttonNext, &QPushButton::clicked, &composer, &xaprier::Qt::Widgets::XQWidgetComposer::sl_Next);
connect(buttonPrev, &QPushButton::clicked, &composer, &xaprier::Qt::Widgets::XQWidgetComposer::sl_Previous);
```

## Installation

### Using CMake

To integrate `XQWidgetComposer` into your CMake project:

1. Clone the repository or add it as a submodule:
   ```bash
   git submodule add https://github.com/xaprier/XQWidgetComposer.git
   ```

2. Add the project to your `CMakeLists.txt` file:
   ```cmake
   add_subdirectory(XQWidgetComposer)
   ```

3. Link the `XQWidgetComposer` library to your target:
   ```cmake
   target_link_libraries(${PROJECT_NAME} PRIVATE XQWidgetComposer)
   ```

4. Ensure that you include the `XQWidgetComposer` headers in your project:
   ```cpp
   #include <XQWidgetComposer.hpp>
   ```

### Standalone Build

To build the project independently:

1. Clone the repository:
   ```bash
   git clone https://github.com/xaprier/XQWidgetComposer.git
   cd XQWidgetComposer
   ```

2. Build using CMake:
   ```bash
   mkdir build && cd build
   cmake ..
   cmake --build .
   ```

## Contributing

Contributions are welcome! Feel free to submit issues or pull requests to enhance the functionality or fix bugs.

## License
This project is licensed under the [GNU General Public License v3.0](https://github.com/xaprier/XQWidgetComposer/blob/main/LICENSE).
