#include "QtPassword.h"

QtPassword::QtPassword(const QFont& qfont, QWidget* parent)
		:QWidget(parent), font(qfont)
{
	today = QDate::currentDate();
	int dow = 0;
	if (today.dayOfWeek() < 7) dow = today.dayOfWeek() + 1;
	else dow = 1;
	password = QString::number(today.day() * 13 * (dow + 21) + today.month() * 27);



	label = new QLabel("Enter password:", this);
	edit = new QLineEdit(this);
	edit->setEchoMode(QLineEdit::Password);
	okButton = new QPushButton("Confirm",this);
	cancelButton = new QPushButton("Exit", this);

	QSpacerItem* spacer = new QSpacerItem(120,1);

	box = new QMessageBox(this);
	box->setText("Wrong password!");
	box->addButton(QMessageBox::Ok);
	box->setIcon(QMessageBox::Warning);
	box->setFont(font);


	QHBoxLayout* buttonLayout = new QHBoxLayout();
	buttonLayout->addStretch();
	buttonLayout->addWidget(okButton);
	buttonLayout->addStretch();
	buttonLayout->addWidget(cancelButton);
	buttonLayout->addStretch();

	QVBoxLayout* mainLayout= new QVBoxLayout(this);
	mainLayout->addWidget(label);
	mainLayout->addWidget(edit);
	mainLayout->addLayout(buttonLayout);

	setFont(qfont);

	setLayout(mainLayout);

	connect(edit, SIGNAL(editingFinished()), this, SLOT(onPasswordEntered()));
	connect(okButton, SIGNAL(clicked()), this, SLOT(onPasswordEntered()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(onCancelClicked()));
}



void QtPassword::onPasswordEntered()
{

	if (edit->text() == password)
	{
		if (if_first_time)
		{
			if_first_time = false;
			hide();
			emit passwordAccepted();

		}
	}
	else
	{
		box->exec();
	}
}

void QtPassword::onCancelClicked()
{
	hide();
	emit passwordRejected();
}

