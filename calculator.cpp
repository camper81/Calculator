#include "calculator.h"
#include "ui_calculator.h"
#include <QDebug>
#include <unordered_map>

std::unordered_map<Operations, std::shared_ptr<IState>> states {
  { Operations::Initialization, std::make_shared<Initial>() },
  { Operations::Addition,       std::make_shared<Addition>() },
  { Operations::Subtraction,    std::make_shared<Subtraction>() },
  { Operations::Division,       std::make_shared<Division>() },
  { Operations::Multiplication, std::make_shared<Multiplication>() },
  { Operations::AfterResult,    std::make_shared<AfterResult>() }
};

Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget), m_state(states[Operations::Initialization])
{
    ui->setupUi(this);
    for(auto&& child : ui->gOperations->children()) {
        connect(qobject_cast<QPushButton*>(child), &QPushButton::clicked, this, &Calculator::onOperatorClick);
    }

    for(auto child : ui->gNumpad->children()) {
        connect(qobject_cast<QPushButton*>(child), &QPushButton::clicked, this, &Calculator::onNumpadClick);
    }
}

void Calculator::onOperatorClick() {
    if(ui->tNumberField->text().isEmpty())
        return;

    QString text = qobject_cast<QPushButton*>(sender())->text();
    if(text == "+") {
        m_state->setState(this, states[Operations::Addition]);
    } else if (text == "-") {
        m_state->setState(this, states[Operations::Subtraction]);
    } else if (text == "*") {
        m_state->setState(this, states[Operations::Multiplication]);
    } else if (text == "/") {
        m_state->setState(this, states[Operations::Division]);
    } else if (text == "=") {
        ui->tNumberField->setText(QString::number(m_midterm));
        m_state->getResult(this);
    } else if (text == "AC") {
        ui->tNumberField->setText("0");
        setMidterm(0);
        m_state->setState(this, states[Operations::Initialization]);
    }

    resetNumberField();
}

void Calculator::onNumpadClick() {    
    if(!checkTextField(m_number_field))
        return;

    QString sym = qobject_cast<QPushButton*>(sender())->text();

    if(hasComma(m_number_field) && sym == ".")
        return;

    m_number_field.append(sym);
    ui->tNumberField->setText(m_number_field);
}

float Calculator::getNumberFromTextField() {
    if(m_number_field.isEmpty())
        return 0;
    return m_number_field.toFloat();
}

float Calculator::getMidterm() const {
    return m_midterm;
}

void Calculator::setMidterm(float number) {
    m_midterm = number;
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::setTextField(QString text) {
    ui->tNumberField->setText(text);
}

void Calculator::resetNumberField() {
    m_number_field.clear();
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

void Initial::setState(Calculator* calculator, std::shared_ptr<IState> new_state) {
    calculator->setMidterm(calculator->getNumberFromTextField());
    calculator->setState(new_state);
    calculator->resetNumberField();
}

void Initial::getResult(Calculator *calculator) {
    calculator->resetNumberField();

}

void AfterResult::setState(Calculator* calculator, std::shared_ptr<IState> new_state) {
    calculator->setState(new_state);
    calculator->resetNumberField();
}

void AfterResult::getResult(Calculator* ) {
    // Empty method
}

void IState::getResult(Calculator* calculator)
{
    setState(calculator, states[Operations::AfterResult]);
    calculator->setTextField(QString::number(calculator->getMidterm()));
}

void Addition::setState(Calculator* calculator, std::shared_ptr<IState> new_state) {
    calculator->setMidterm(calculator->getMidterm() + calculator->getNumberFromTextField());
    calculator->setState(new_state);
}

void Subtraction::setState(Calculator* calculator, std::shared_ptr<IState> new_state) {
    calculator->setMidterm(calculator->getMidterm() - calculator->getNumberFromTextField());
    calculator->setState(new_state);
}

void Division::setState(Calculator* calculator, std::shared_ptr<IState> new_state) {
    calculator->setMidterm(calculator->getMidterm() / calculator->getNumberFromTextField());
    calculator->setState(new_state);
}

void Multiplication::setState(Calculator* calculator, std::shared_ptr<IState> new_state) {
    calculator->setMidterm(calculator->getMidterm() * calculator->getNumberFromTextField());
    calculator->setState(new_state);
}
