#include "calculator.h"
#include "ui_calculator.h"
#include <QDebug>
#include <unordered_map>

std::unordered_map<Operations, std::shared_ptr<State>> states {
  { Operations::initial, std::make_shared<Initial>() },
  { Operations::add, std::make_shared<Addition>() },
  { Operations::sub, std::make_shared<Subtraction>() },
  { Operations::div, std::make_shared<Devision>() },
  { Operations::mul, std::make_shared<Multiplication>() },
  { Operations::unknown, std::make_shared<Unknown>() }
};

Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);    
    m_state = states[Operations::initial];
    for(auto&& child : ui->gOperaions->children()) {
        connect(qobject_cast<QPushButton*>(child), &QPushButton::clicked, this, &Calculator::onOperatorClick);
    }

    for(auto child : ui->gNumpad->children()) {
        connect(qobject_cast<QPushButton*>(child), &QPushButton::clicked, this, &Calculator::onNumpadClick);
    }
}

void Calculator::onOperatorClick() {
    if(ui->eMain->text().isEmpty())
        return;

    QString text = qobject_cast<QPushButton*>(sender())->text();
    if(text == "+") {
        m_state->setState(this, states[Operations::add]);
    } else if (text == "-") {
        m_state->setState(this, states[Operations::sub]);
    } else if (text == "*") {
        m_state->setState(this, states[Operations::mul]);
    } else if (text == "/") {
        m_state->setState(this, states[Operations::div]);
    } else if (text == "=") {
        ui->eMain->setText(QString::number(m_prev_result));
        m_state->getResult(this);
    }

    resetTextField();
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
    if(m_text.isEmpty())
        return 0;
    return m_text.toFloat();
}

float Calculator::getPreviousResult() {
    return m_prev_result;
}

void Calculator::setPreviousResult(float number) {
    m_prev_result = number;
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

void Initial::setState(Calculator* calculator, std::shared_ptr<State> new_state) {
    calculator->setPreviousResult(calculator->getNumberFromTextField());
    calculator->setState(new_state);
    calculator->resetTextField();
}

void Initial::getResult(Calculator *calculator) {
    calculator->resetTextField();

}

void Unknown::setState(Calculator* calculator, std::shared_ptr<State> new_state) {
    calculator->setState(new_state);
    calculator->resetTextField();
}

void Unknown::getResult(Calculator* ) {

}

void State::getResult(Calculator* calculator)
{
    setState(calculator, states[Operations::unknown]);
    calculator->setTextField(QString::number(calculator->getPreviousResult()));
}

void Addition::setState(Calculator* calculator, std::shared_ptr<State> new_state) {
    float result = calculator->getPreviousResult() + calculator->getNumberFromTextField();
    calculator->setPreviousResult(result);
    calculator->setState(new_state);
}

void Subtraction::setState(Calculator* calculator, std::shared_ptr<State> new_state) {
    float result = calculator->getPreviousResult() - calculator->getNumberFromTextField();
    calculator->setPreviousResult(result);
    calculator->setState(new_state);
}

void Devision::setState(Calculator* calculator, std::shared_ptr<State> new_state) {
    float result = calculator->getPreviousResult() / calculator->getNumberFromTextField();
    calculator->setPreviousResult(result);
    calculator->setState(new_state);
}

void Multiplication::setState(Calculator* calculator, std::shared_ptr<State> new_state) {
    float result = calculator->getPreviousResult() * calculator->getNumberFromTextField();
    calculator->setPreviousResult(result);
    calculator->setState(new_state);
}
