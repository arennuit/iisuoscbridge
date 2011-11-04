#include "MainForm.h"

#include "DataBase/DataBase.h"
#include <iostream>
#include <ostream>
#include <sstream>
#include <streambuf>

namespace SK
{

// This class allows to send its content towards the log window.
class streamBufToLogEdit : public std::basic_streambuf<char, std::char_traits<char> >
{
typedef	std::basic_streambuf<char, std::char_traits<char> >::int_type int_type;

public:
	streamBufToLogEdit(QPlainTextEdit* targetEdit) :
		std::basic_streambuf<char, std::char_traits<char> >(),
		m_targetEdit(targetEdit) {}

protected:
	int_type overflow(int_type c)
	{
		assert(m_targetEdit);

		m_targetEdit->insertPlainText(QString(c));

		return c;
	}

	QPlainTextEdit* m_targetEdit;
};

//////////////////////////////////////////////////////////////////////////
MainForm::MainForm(QWidget *parent, Qt::WFlags flags) :
	QMainWindow(parent, flags)
{
	ui.setupUi(this);

	// Set input masks and validators.
	QRegExpValidator *validator = new QRegExpValidator(this);
	QRegExp regExp("((1{0,1}[0-9]{0,2}|2[0-4]{1,1}[0-9]{1,1}|25[0-5]{1,1})\\.){3,3}(1{0,1}[0-9]{0,2}|2[0-4]{1,1}[0-9]{1,1}|25[0-5]{1,1})");
	validator->setRegExp(regExp);
	ui.m_ipAddressEdit->setValidator(validator);

	// Get access to the DataController.
	m_dataController = DataController::GetInstance();
	assert(m_dataController);

	// Setup model.
	ui.m_pathsView->setModel(&m_mvdModel);

	m_mvdModel.update();

	ui.m_pathsView->expandAll();
	ui.m_pathsView->resizeColumnToContents(0);
	ui.m_pathsView->resizeColumnToContents(1);

	// UI setup.
	DataBase* dataBase = DataBase::GetInstance(); // We do not make this pointer a member of the class because the MainForm is not due to modify data, it only uses the data model to perform the initial ui setup.
	assert(dataBase);

	ui.m_ipAddressEdit->setText(QString(dataBase->getIpAddress().c_str()));
	ui.m_portEdit->setText(QString::number(dataBase->getPort()));

	if (dataBase->getIsObservationOn())
		ui.m_startStopToggleButton->setChecked(true);
	else
		ui.m_startStopToggleButton->setChecked(false);

	if (dataBase->getIsFoldAndNameJoints())
		ui.m_foldAndNameJointsCheckBox->setChecked(true);
	else
		ui.m_foldAndNameJointsCheckBox->setChecked(false);

	// Establish all connections.
	connect(ui.m_ipAddressEdit, SIGNAL(textChanged(const QString&)), this, SLOT(onIpAddressLineEditTextChanged(const QString&)));
	connect(ui.m_portEdit, SIGNAL(textChanged(const QString&)), this, SLOT(onPortLineEditTextChanged(const QString&)));

	connect(ui.m_startStopToggleButton, SIGNAL(clicked()), this, SLOT(onStartStopToggleButtonClicked()));

	connect(ui.m_foldAndNameJointsCheckBox, SIGNAL(clicked()), this, SLOT(onFoldAndNameJointsCheckBoxClicked()));

	// Redirect cerr, clog and cout to the log window.
	static streamBufToLogEdit coutStreamBuf(ui.m_logEdit);
	std::cout.rdbuf(&coutStreamBuf);

	//static streamBufToLogEdit clogStreamBuf(ui.m_logEdit);
	//std::clog.rdbuf(&clogStreamBuf);

	//static streamBufToLogEdit cerrStreamBuf(ui.m_logEdit);
	//std::cerr.rdbuf(&cerrStreamBuf);
}

//////////////////////////////////////////////////////////////////////////
MainForm::~MainForm()
{
	m_mvdModel.clear();
}

//////////////////////////////////////////////////////////////////////////
void MainForm::onIsObservationOnChanged(bool isObservationOn)
{
	ui.m_startStopToggleButton->setChecked(isObservationOn);
	ui.m_foldAndNameJointsCheckBox->setEnabled(!isObservationOn);
	ui.m_pathsView->setEnabled(!isObservationOn);
}

} // namespace SK.