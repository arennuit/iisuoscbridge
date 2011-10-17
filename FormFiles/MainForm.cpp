#include "MainForm.h"

#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"

#include "DataBase/DataBase.h"

namespace SK
{

//////////////////////////////////////////////////////////////////////////
MainForm::MainForm(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags),
	m_settingsForm(this)
{
	ui.setupUi(this);

	// Get access to the MvdController.
	m_mvdController = MvdController::GetInstance();
	assert(m_mvdController);

	// Default texts.
	DataBase* dataBase = DataBase::GetInstance();
	assert(dataBase);

	ui.m_ipAddressLineEdit->setText(QString(dataBase->getIpAddress().c_str()));
	ui.m_portLineEdit->setText(QString::number(dataBase->getPort()));

	// Establish all connections.
	connect(ui.m_ipAddressLineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(onIpAddressLineEditTextChanged(const QString&)));
	connect(ui.m_portLineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(onPortLineEditTextChanged(const QString&)));

	connect(ui.m_startButton, SIGNAL(clicked()), this, SLOT(onStartButtonClicked()));
	connect(ui.m_stopButton, SIGNAL(clicked()), this, SLOT(onStopButtonClicked()));
	connect(ui.m_settingsButton, SIGNAL(clicked()), this, SLOT(onSettingsButtonClicked()));
}

////////////////////////////////////////////////////////////////////////////
//void MainForm::onStartButtonClicked()
//{
//	UdpTransmitSocket transmitSocket(IpEndpointName(m_dataModel->getIpAddress().c_str(), m_dataModel->getPort()));
//
//	char buffer[OUTPUT_BUFFER_SIZE];
//	osc::OutboundPacketStream p(buffer, OUTPUT_BUFFER_SIZE);
//
//	p	<< osc::BeginBundleImmediate
//		<< osc::BeginMessage("/1/fader1") 
//		<< 0.56f
//		<< osc::EndMessage
//		<< osc::BeginMessage("/1/fader2") 
//		<< 0.78f
//		<< osc::EndMessage
//		<< osc::EndBundle;
//
//	transmitSocket.Send(p.Data(), p.Size());
//}

//////////////////////////////////////////////////////////////////////////
void MainForm::onStopButtonClicked()
{
	QMessageBox::information(NULL, "Stop", "Stop button clicked.");
}

//////////////////////////////////////////////////////////////////////////
void MainForm::onSettingsButtonClicked()
{
	m_settingsForm.show();
}

} // namespace SK.