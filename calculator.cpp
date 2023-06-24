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
    connect(this, &Calculator::changeOper, this, &Calculator::updateLineText);
    connect(this, &Calculator::changeOper, this, &Calculator::result);

    for(auto child : ui->numpad->children()) {
        QPushButton* button = qobject_cast<QPushButton*>(child);
        connect(button, &QPushButton::clicked, this, [&](){
            if(numbersCount > maxNumbers)
                return;

            if(qobject_cast<QPushButton*>(sender())->text() == ".") {
                if(hasComma)
                    return;

                hasComma = true;
            } else
                ++numbersCount;
            if(ui->l_calculation->text() == "0")
                ui->l_calculation->setText(qobject_cast<QPushButton*>(sender())->text());
            else
                ui->l_calculation->setText(ui->l_calculation->text() + qobject_cast<QPushButton*>(sender())->text());
        });
    }
}



Calculator::~Calculator()
{
    delete ui;
}

void Calculator::addition()
{
    setOper(Operations::add);

//    QString lineText = ui->lineEdit->text();
//    if(!lineText.isEmpty())
//        lineText += '+';

//    preResult += ui->l_calculation->text().toDouble();
//    reset();

//    if(!lineText.isEmpty())
//        lineText += '+';
//    lineText += ui->l_calculation->text();
//    ui->lineEdit->setText(lineText);

}

void Calculator::updateLineText() {
    QString lineText = ui->lineEdit->text();
    if(!lineText.isEmpty()) {
        switch(m_lastOper) {
            case Operations::add:
                lineText += '+';
                break;
            case Operations::sub:
                lineText += '-';
                break;
            case Operations::div:
                lineText += '/';
                break;
            case Operations::mul:
                lineText += '*';
                break;
        }
    }
    lineText += ui->l_calculation->text();
    ui->lineEdit->setText(lineText);
}

void Calculator::result()
{

    auto curNumber = ui->l_calculation->text().toDouble();
    switch(m_lastOper) {
        case Operations::add:
            preResult += curNumber;
            break;
        case Operations::sub:
            preResult -= curNumber;
            break;
        case Operations::div:
            preResult /= curNumber;
            break;
        case Operations::mul:
            preResult *= curNumber;
            break;
        default:
            break;
    }

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
