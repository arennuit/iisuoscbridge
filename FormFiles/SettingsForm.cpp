#include "SettingsForm.h"

namespace SK
{

//////////////////////////////////////////////////////////////////////////
SettingsForm::SettingsForm(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	// Setup model.
	ui.m_pathsView->setModel(&m_model);
}

//////////////////////////////////////////////////////////////////////////
SettingsForm::~SettingsForm()
{
	m_model.clear();
}

} // namespace SK.