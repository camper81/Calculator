#include "calculator.h"
#include "ui_calculator.h"
#include <QDebug>

Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);    
    m_state = new Initial();
    for(auto&& child : ui->gOperaions->children()) {
        connect(qobject_cast<QPushButton*>(child), &QPushButton::clicked, this, &Calculator::onOperatorClick);
    }

    for(auto child : ui->gNumpad->children()) {
        connect(qobject_cast<QPushButton*>(child), &QPushButton::clicked, this, &Calculator::onNumpadClick);
    }
}

void Calculator::onOperatorClick() {
    QString text = qobject_cast<QPushButton*>(sender())->text();
    if(text == "+") {
        m_state->setState(this, new Addition());
    } else if (text == "-") {
        m_state->setState(this, new Subtraction());
    } else if (text == "=") {
        ui->eMain->setText(QString::number(m_prev_result));
        m_state->getResult(this);
    }
}

void Calculator::onNumpadClick() {    
    if(!checkTextField(m_text))
        return;

    QString sym = qobject_cast<QPushButton*>(sender())->text();

    if(hasComma(m_text) && sym == ".")
        return;

    m_text.append(sym);
    ui->eMain->setText(m_text);
}

float Calculator::getNumberFromTextField() {
    return m_text.toFloat();
}

float Calculator::getPreviousResult() {
    return m_prev_result;
}

void Calculator::setPreviousResult(float prev_result) {
    m_prev_result = prev_result;
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::setTextField(QString text) {
    ui->eMain->setText(text);
}

void Calculator::resetTextField() {
    m_text.clear();
}

bool Calculator::checkTextField(QString text)
{
    if(text.size() > MAX_TEXT_FIELD)
        return false;

    return true;
}

bool Calculator::hasComma(QString text)
{
    return text.contains('.');
}

void Initial::setState(Calculator* calculator, State* new_state) {
    calculator->setPreviousResult(calculator->getNumberFromTextField());
    calculator->setState(new_state);
    calculator->resetTextField();
    delete this;
}

void Initial::getResult(Calculator *calculator) {
    calculator->resetTextField();
}

void Addition::getResult(Calculator *calculator) {
    float result = calculator->getPreviousResult() + calculator->getNumberFromTextField();
    calculator->setPreviousResult(result);
    calculator->setTextField(QString::number(result));
}

void Subtraction::getResult(Calculator *calculator) {
    float result = calculator->getPreviousResult() - calculator->getNumberFromTextField();
    calculator->setTextField(QString::number(result));
    calculator->setState(new Initial());
    delete this;
}

void Addition::setState(Calculator* calculator, State* new_state) {
    float result = calculator->getPreviousResult() + calculator->getNumberFromTextField();
    calculator->setPreviousResult(result);
    calculator->setState(new_state);
    calculator->resetTextField();
    delete this;
}

void Subtraction::setState(Calculator* calculator, State* new_state) {
    float result = calculator->getPreviousResult() - calculator->getNumberFromTextField();
    calculator->setPreviousResult(result);
    calculator->setState(new_state);
    calculator->resetTextField();
    delete this;
}
