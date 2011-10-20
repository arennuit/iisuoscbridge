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

	ui.m_pathsView->expandAll();
	ui.m_pathsView->resizeColumnToContents(0);
}

//////////////////////////////////////////////////////////////////////////
SettingsForm::~SettingsForm()
{
	m_mvdModel.clear();
}

} // namespace SK.