#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Calculator;

enum class Operations{
    unknown, add, sub, mul, div
};

class State {
public:
    virtual void setState(Calculator* obj, State* new_state) = 0;
    virtual void getResult(Calculator* obj) = 0;
    virtual ~State() {

    }
};

class Addition : public State {
public:
    void setState(Calculator* obj, State* new_state);
    void getResult(Calculator* obj);
};

class Subtraction : public State {
public:
    void setState(Calculator* obj, State* new_state);
    void getResult(Calculator* obj);
};

class Multiplication : public State {
public:
    void setState(Calculator* obj, State* new_state);
    void getResult(Calculator* obj);
};

class Devision: public State {
public:
    void setState(Calculator* obj, State* new_state);
    void getResult(Calculator* obj);
};

class Initial: public State {
public:
    void setState(Calculator* obj, State* new_state);
    void getResult(Calculator* obj);
};

class Calculator : public QWidget
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

    void onNumpadClick();
    void onOperatorClick();
    void setState(State* state) {
        m_state = state;
    }
    float getNumberFromTextField();
    float getPreviousResult();
    void setPreviousResult(float);
    void resetTextField();
    void setTextField(QString);
signals:
    void onChangeOperation();

private:
    const int MAX_TEXT_FIELD = 12;

    Ui::Widget *ui;

    State* m_state;
    QString m_text;
    bool checkTextField(QString text);
    bool hasComma(QString text);
    float m_prev_result;
};
#endif // CALCULATOR_H
