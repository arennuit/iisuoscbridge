#include "SettingsForm.h"

namespace SK
{

//////////////////////////////////////////////////////////////////////////
SettingsForm::SettingsForm(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	// Setup model.
	ui.m_pathsView->setModel(&m_mvdModel);
	m_mvdModel.update();
}

//////////////////////////////////////////////////////////////////////////
SettingsForm::~SettingsForm()
{
	m_mvdModel.clear();
}

} // namespace SK.