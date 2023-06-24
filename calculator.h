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
    Q_PROPERTY(Operations lastOper READ getOper WRITE setOper NOTIFY changeOper)

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

    void addition();
    void result();
    void reset();

    const Operations &getOper() const;
    void setOper(const Operations &newLastOper);

signals:
    void changeOper();

private:
    Ui::Widget *ui;
    bool hasComma;
    int numbersCount;
    double preResult;

    static const int maxNumbers = 12;
    Operations m_lastOper;
    void updateLineText();
};
#endif // CALCULATOR_H
