#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

enum class Operations{
    unknown, add, sub, mul, div
};

class Calculator : public QWidget
{
    Q_OBJECT
    Q_ENUM(Operations)
    Q_PROPERTY(Operations m_currentOperation READ currentOperation WRITE setCurrentOperation NOTIFY onChangeOperation)

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

    void completeOperation();

    void resetTextField();
    bool checkTextField();

    void onOperationClick();
    void onNumpadClick();
signals:
    void onChangeOperation();

private:
    Ui::Widget *ui;
    Operations m_currentOperation;
};
#endif // CALCULATOR_H
