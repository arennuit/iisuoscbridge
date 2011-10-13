#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include <QWidget>
#include "ui_SettingsForm.h"

class SettingsForm : public QWidget
{
	Q_OBJECT

public:
	SettingsForm(QWidget *parent = 0);
	~SettingsForm();

private:
	Ui::SettingsForm ui;
};

#endif // SETTINGSFORM_H
