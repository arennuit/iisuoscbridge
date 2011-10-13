#include "MainForm.h"
// DEBUG.
#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"

#define OUTPUT_BUFFER_SIZE 1024

QString MainForm::sm_defaultIpAddress = "127.0.0.1";
int MainForm::sm_defaultPort = 8000;

//////////////////////////////////////////////////////////////////////////
MainForm::MainForm(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	// Default values;
	m_ipAddress = sm_defaultIpAddress;
	m_port = sm_defaultPort;

	ui.m_ipAddressLineEdit->setText(m_ipAddress);
	ui.m_portLineEdit->setText(QString::number(m_port));

	// Establish all connections.
	connect(ui.m_ipAddressLineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(onIpAddressLineEditTextChanged(const QString&)));
	connect(ui.m_portLineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(onPortLineEditTextChanged(const QString&)));

	connect(ui.m_startButton, SIGNAL(clicked()), this, SLOT(onStartButtonClicked()));
	connect(ui.m_stopButton, SIGNAL(clicked()), this, SLOT(onStopButtonClicked()));
	connect(ui.m_settingsButton, SIGNAL(clicked()), this, SLOT(onSettingsButtonClicked()));
}

//////////////////////////////////////////////////////////////////////////
void MainForm::onStartButtonClicked()
{
	UdpTransmitSocket transmitSocket(IpEndpointName(m_ipAddress.toStdString().c_str(), m_port));

	char buffer[OUTPUT_BUFFER_SIZE];
	osc::OutboundPacketStream p(buffer, OUTPUT_BUFFER_SIZE);

	//p << osc::BeginBundleImmediate
	//	<< osc::BeginMessage( "/test1" ) 
	//	<< true << 23 << (float)3.1415 << "hello" << osc::EndMessage
	//	<< osc::BeginMessage( "/test2" ) 
	//	<< true << 24 << (float)10.8 << "world" << osc::EndMessage
	//	<< osc::EndBundle;
	p	<< osc::BeginBundleImmediate
		<< osc::BeginMessage("/1/fader1") 
		<< 0.56f
		<< osc::EndMessage
		<< osc::EndBundle;

	transmitSocket.Send(p.Data(), p.Size());
}

//////////////////////////////////////////////////////////////////////////
void MainForm::onStopButtonClicked()
{
	QMessageBox::information(NULL, "Stop", "Stop button clicked.");
}

//////////////////////////////////////////////////////////////////////////
void MainForm::onSettingsButtonClicked()
{
	QMessageBox::information(NULL, "Settings", "Settings button clicked.");
}

//////////////////////////////////////////////////////////////////////////
MainForm::~MainForm()
{
	if(NULL != m_device)
	{
		SK::Context::Instance().finalize();
	}
}

//////////////////////////////////////////////////////////////////////////
bool MainForm::initIisu()
{
	SK::Context& context = SK::Context::Instance();

	SK::Return<SK::IisuHandle*> ret = context.createHandle(SK::IisuHandle::Configuration());

	if(ret.failed()) return false;

	SK::IisuHandle* handle = ret.get();

	SK::Return<SK::Device*> retDev = handle->initializeDevice(SK::Device::Configuration());

	if(ret.failed())
	{
		std::cout << ret.getDescription() << std::endl;
		SK::Result result = context.destroyHandle(*handle);
		if(result.failed())
		{
			std::cout << result.getDescription() << std::endl;
		}
		return false;
	}


	m_device = retDev.get();

	m_skeleton = m_device->registerDataHandle< SK::Array<SK::Vector3> >("...");

	m_device->getEventManager().registerEventListener("DEVICE.DataFrame",*this,&MainForm::newFrameListener);

	SK::GetVersionCommand cmd(m_device->getCommandManager());

	//	SK::CommandHandle<SK::Return<SK::String>()> cmd2(m_device->getCommandManager(), "SYSTEM.GetVersion");

	SK::Return<SK::String> retCmd = cmd();

	if(retCmd.succeeded())
	{
		std::cout << retCmd.get() << std::endl;
	}

	m_device->start();

	return true;
}

//////////////////////////////////////////////////////////////////////////
bool MainForm::update()
{
	m_device->lockFrame();

	const SK::Array<SK::Vector3>& keyPoints = m_skeleton.get();

	m_device->releaseFrame();

	return true;
}

//////////////////////////////////////////////////////////////////////////
void MainForm::newFrameListener( const SK::DataFrameEvent& event )
{
	m_device->updateFrame(true);
	std::cout << event.getFrameID() << std::endl;
}
