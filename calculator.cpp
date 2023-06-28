#include "calculator.h"
#include "ui_calculator.h"
#include <QDebug>

Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget), hasComma(false), numbersCount(0), preResult(0), m_lastOper(Operations::unknown)
{
    ui->setupUi(this);

    connect(ui->b_add, &QPushButton::clicked, this, &Calculator::addition);
    connect(ui->b_eql, &QPushButton::clicked, this, &Calculator::result);
    connect(this, &Calculator::changeOper, this, &Calculator::result);

    for(auto child : ui->numpad->children()) {
        QPushButton* button = qobject_cast<QPushButton*>(child);
        connect(button, &QPushButton::clicked, this, [&](){
            if(numbersCount > maxNumbers)
                return;

            if(qobject_cast<QPushButton*>(sender())->text() == ".") {
                if(!hasComma) {
                    ui->l_calculation->setText(ui->l_calculation->text() + qobject_cast<QPushButton*>(sender())->text());
                    hasComma = true;
                }
                return;
            }

            if(numbersCount == 0)
                ui->l_calculation->setText(qobject_cast<QPushButton*>(sender())->text());
            else
                ui->l_calculation->setText(ui->l_calculation->text() + qobject_cast<QPushButton*>(sender())->text());

            ++numbersCount;
        });
    }
}



Calculator::~Calculator()
{
    delete ui;
}

void Calculator::addition()
{
    completePrevOperation();
    setOper(Operations::add);
    result();
    reset();
}

void Calculator::completePrevOperation() {
    switch (m_lastOper) {
        case Operations::add:
            preResult += ui->l_calculation->text().toDouble();
            break;
        default:
            break;
    }
}

void Calculator::result()
{
    ui->l_calculation->setText(QString::number(preResult));
    reset();
}

void Calculator::reset()
{
    hasComma = false;
    numbersCount = 0;
}


const Operations &Calculator::getOper() const
{
    return m_lastOper;
}

void Calculator::setOper(const Operations &newLastOper)
{
    if (m_lastOper == newLastOper)
        return;
    m_lastOper = newLastOper;
    emit changeOper();
}
