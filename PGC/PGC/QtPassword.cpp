#include "QtPassword.h"

extern QFont workingFont;

QtPassword::QtPassword(const QFont& qfont, const int& bHeight, QWidget* parent)
		:QWidget(parent), font(qfont), buttonHeight(bHeight)
{
	this->setFont(workingFont);
	label = new QLabel("Enter password:", this);
	edit = new QLineEdit(this);
	okButton = new QPushButton("Conform", this);
	cancelButton = new QPushButton("Exit", this);

	box = new QMessageBox(this);
	box->setText("Wrong password!");
	box->addButton(QMessageBox::Ok);
	box->setIcon(QMessageBox::Warning);
	box->setFont(font);
//	box->resize(200,200);

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
	setWindowTitle(tr("OASIS PGC Data Extractor"));
//	move(800, 400);

//	QPoint global_geometry = this->mapToGlobal(this->rect().center());
//	box->move(global_geometry.x() - 75, global_geometry.y() - 50);

	connect(edit, SIGNAL(editingFinished()), this, SLOT(onPasswordEntered()));
	connect(okButton, SIGNAL(clicked()), this, SLOT(onPasswordEntered()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(onCancelClicked()));
}



void QtPassword::onPasswordEntered()
{
//	edit->setText("Enter");
	if (edit->text() == "123")
	{
		hide();
		emit passwordAccepted();
	}
	else
	{
//		QPoint global_geometry = this->mapToGlobal(this->rect().center());
//		box->move(global_geometry.x() - 75, global_geometry.y() - 50);
		box->exec();
	}
}

void QtPassword::onCancelClicked()
{
	hide();
	emit passwordRejected();
}

