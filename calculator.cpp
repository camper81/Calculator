#include "calculator.h"
#include "ui_calculator.h"
#include <QDebug>

Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    for(auto&& child : ui->gOperaions->children()) {
        connect(qobject_cast<QPushButton*>(child), &QPushButton::clicked, this, &Calculator::onOperationClick);
    }

    for(auto child : ui->gNumpad->children()) {
        connect(qobject_cast<QPushButton*>(child), &QPushButton::clicked, this, &Calculator::onNumpadClick);
    }
}


void Calculator::onNumpadClick() {
    if(checkTextField()) {

    }
}


Calculator::~Calculator()
{
    delete ui;
}
