#include "MainForm.h"

#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"

#include "FormFiles/SettingsForm.h"

#define OUTPUT_BUFFER_SIZE 1024

namespace SK
{

//////////////////////////////////////////////////////////////////////////
MainForm::MainForm(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags),
	m_settingsForm(0)
{
	ui.setupUi(this);

	// Get access to the data model.
	m_dataModel = DataModel::GetInstance();
	assert(m_dataModel);

	// Default texts.
	ui.m_ipAddressLineEdit->setText(QString(m_dataModel->m_ipAddress.c_str()));
	ui.m_portLineEdit->setText(QString::number(m_dataModel->m_port));

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
	UdpTransmitSocket transmitSocket(IpEndpointName(m_dataModel->m_ipAddress.c_str(), m_dataModel->m_port));

	char buffer[OUTPUT_BUFFER_SIZE];
	osc::OutboundPacketStream p(buffer, OUTPUT_BUFFER_SIZE);

	p	<< osc::BeginBundleImmediate
			<< osc::BeginMessage("/1/fader1") 
				<< 0.56f
			<< osc::EndMessage
			<< osc::BeginMessage("/1/fader2") 
				<< 0.78f
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
	m_settingsForm = new SettingsForm(this);
	m_settingsForm->show();
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

} // namespace SK.