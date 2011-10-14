#pragma once

#include <QDialog>
#include "ui_SettingsForm.h"
#include "Widgets/MvdDataModel.h"

namespace SK
{

//////////////////////////////////////////////////////////////////////////
/// \name This class is the paths settings or configuration window for the application.
class SettingsForm : public QDialog
{
	Q_OBJECT

public:
	SettingsForm(QWidget *parent = 0);
	~SettingsForm();

private:
	Ui::SettingsForm ui;

	MvdDataModel m_mvdModel;
};

} // namespace SK.
