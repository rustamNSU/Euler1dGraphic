//
// Created by rustam on 27.05.2020.
//

#include "InitialData.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDoubleValidator>
#include <QIntValidator>
#include <QLabel>
#include <QFormLayout>

InitialDataWindow::InitialDataWindow(QWidget* parent) :
        QWidget(parent)
{
    this->setWindowTitle("Initial data manager");

    auto main_vbox = new QVBoxLayout(this);
    main_vbox->setSpacing(30);

    // Initial data block
    auto init = new QGridLayout;
    init->setVerticalSpacing(3);

    auto init_title = new QLabel("Initial data for Riemann Problem (Euler 1D)", this);
    init->addWidget(init_title, 0, 0, 1, 2);
    init_title->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    init_title->setFrameStyle(QFrame::Panel | QFrame::Plain);
    init_title->setLineWidth(2);

    auto leftForm = new QFormLayout;
    leftForm->setLabelAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    line_p1 = new QLineEdit(this);
    line_u1 = new QLineEdit(this);
    line_rho1 = new QLineEdit(this);
    leftForm->addRow("p1", line_p1);
    leftForm->addRow("u1", line_u1);
    leftForm->addRow("rho1", line_rho1);

    auto rightForm = new QFormLayout;
    rightForm->setLabelAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    line_p2 = new QLineEdit(this);
    line_u2 = new QLineEdit(this);
    line_rho2 = new QLineEdit(this);
    rightForm->addRow("p2", line_p2);
    rightForm->addRow("u2", line_u2);
    rightForm->addRow("rho2", line_rho2);

    init->addLayout(leftForm, 1, 0, 1, 1);
    init->addLayout(rightForm, 1, 1, 1, 1);
    main_vbox->addLayout(init, 1);

    // mesh initialization block
    auto region = new QVBoxLayout;
    region->setSpacing(3);

    auto region_title = new QLabel("Initialization of calculation area", this);
    region->addWidget(region_title, 1);
    region_title->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    region_title->setFrameStyle(QFrame::Panel | QFrame::Plain);
    region_title->setLineWidth(2);

    auto form = new QFormLayout;
    form->setLabelAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    line_Xmin = new QLineEdit(this);
    line_Xmax = new QLineEdit(this);
    line_N = new QLineEdit(this);
    form->addRow("Xmin", line_Xmin);
    form->addRow("Xmax", line_Xmax);
    form->addRow("Nodes number", line_N);
    region->addLayout(form, 1);

    main_vbox->addLayout(region, 1);

    // Addition parameters
    auto parameters = new QVBoxLayout;
    parameters->setSpacing(3);

    auto parameters_title = new QLabel("Initialization of physical parameters", this);
    parameters->addWidget(parameters_title, 1);
    parameters_title->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    parameters_title->setFrameStyle(QFrame::Panel | QFrame::Plain);
    parameters_title->setLineWidth(2);

    auto form_parameters = new QFormLayout;
    form_parameters->setLabelAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    line_gamma = new QLineEdit(this);
    line_endTime = new QLineEdit(this);
    form_parameters->addRow("Gamma", line_gamma);
    form_parameters->addRow("End time", line_endTime);
    parameters->addLayout(form_parameters, 1);

    main_vbox->addLayout(parameters, 1);

    QValidator* double_valid = new QDoubleValidator();
    double_valid->setLocale(QLocale(QLocale::English));
    line_p1->setValidator(double_valid);
    line_p2->setValidator(double_valid);
    line_u1->setValidator(double_valid);
    line_u2->setValidator(double_valid);
    line_rho1->setValidator(double_valid);
    line_rho2->setValidator(double_valid);
    line_Xmin->setValidator(double_valid);
    line_Xmax->setValidator(double_valid);
    line_endTime->setValidator(double_valid);
    line_gamma->setValidator(double_valid);

    QValidator* int_valid = new QIntValidator();
    line_N->setValidator(int_valid);

    line_p1->setText(QString::number(initialData.pl));
    line_p2->setText(QString::number(initialData.pr));
    line_u1->setText(QString::number(initialData.ul));
    line_u2->setText(QString::number(initialData.ur));
    line_rho1->setText(QString::number(initialData.rhol));
    line_rho2->setText(QString::number(initialData.rhor));
    line_Xmin->setText(QString::number(initialData.left));
    line_Xmax->setText(QString::number(initialData.right));
    line_endTime->setText(QString::number(initialData.endTime));
    line_gamma->setText(QString::number(initialData.gamma));
    line_N->setText(QString::number(initialData.nodesNumber));


    setLayout(main_vbox);
}

const InitialData& InitialDataWindow::getInitialData() const
{
    return initialData;
}

void InitialDataWindow::updateInitialData()
{
    transform_QLineEdit_to_qreal(line_p1, initialData.pl, initialData.pl);
    transform_QLineEdit_to_qreal(line_p2, initialData.pr, initialData.pr);
    transform_QLineEdit_to_qreal(line_u1, initialData.ul, initialData.ul);
    transform_QLineEdit_to_qreal(line_u2, initialData.ur, initialData.ur);
    transform_QLineEdit_to_qreal(line_rho1, initialData.rhol, initialData.rhol);
    transform_QLineEdit_to_qreal(line_rho2, initialData.rhor, initialData.rhor);

    transform_QLineEdit_to_qreal(line_Xmin, initialData.left, initialData.left);
    transform_QLineEdit_to_qreal(line_Xmax, initialData.right, initialData.right);
    transform_QLineEdit_to_qreal(line_gamma, initialData.gamma, initialData.gamma);
    transform_QLineEdit_to_qreal(line_endTime, initialData.endTime, initialData.pl);

    transform_QLineEdit_to_int(line_N, initialData.nodesNumber, initialData.nodesNumber);
}

InitialDataWindow::~InitialDataWindow() noexcept {}

void transform_QLineEdit_to_qreal(QLineEdit* edit, qreal& item, qreal default_value)
{
    if (edit->text().isEmpty())
    {
        item = default_value;
        edit->setText(QString::number(default_value));
    }
    else
    {
        item = edit->text().toDouble();
    }
}

void transform_QLineEdit_to_int(QLineEdit* edit, int& item, int default_value)
{
    if (edit->text().isEmpty())
    {
        item = default_value;
        edit->setText(QString::number(default_value));
    }
    else
    {
        item = edit->text().toInt();
    }
}
