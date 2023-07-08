#pragma once

#include <QWidget>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Calculator;

enum class Operations{
    AfterResult, Initialization, Addition, Subtraction, Multiplication, Division
};

class IState {
public:
    virtual void setState(Calculator* obj, std::shared_ptr<IState> new_state) = 0;
    virtual void getResult(Calculator*);
    virtual ~IState() = default;
};

class Addition : public IState {
public:
    void setState(Calculator* obj, std::shared_ptr<IState> new_state) override;
};

class Subtraction : public IState {
public:
    void setState(Calculator* obj, std::shared_ptr<IState> new_state) override;
};

class Multiplication : public IState {
public:
    void setState(Calculator* obj, std::shared_ptr<IState> new_state) override;
};

class Division: public IState {
public:
    void setState(Calculator* obj, std::shared_ptr<IState> new_state) override;
};

class Initial: public IState {
public:
    void setState(Calculator* obj, std::shared_ptr<IState> new_state) override;
    void getResult(Calculator* obj) override;
};

class AfterResult: public IState {
public:
    void setState(Calculator* obj, std::shared_ptr<IState> new_state) override;
    void getResult(Calculator* obj) override;
};

class Calculator : public QWidget
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

    void setState(std::shared_ptr<IState> state) {
        m_state = state;
    }
    void onNumpadClick();
    void onOperatorClick();
    float getNumberFromTextField();
    float getMidterm() const;
    void setMidterm(float);
    void resetNumberField();
    void setTextField(QString);
private:
    Ui::Widget *ui;

    const int MAX_TEXT_FIELD = 12;
    std::shared_ptr<IState> m_state;
    QString m_number_field;
    float m_midterm;

    bool checkTextField(QString text);
    bool hasComma(QString text);
};
