// Import libraries.
import oscP5.*;
import netP5.*;
import themidibus.*;

// Globals.
MidiBus myBus;

OscP5 oscP5;
NetAddress myRemoteLocation;

float isEnabled = 0.0f; // Used as a boolean (because IID streams its bools as booleans as well).

int channel_Kick = 0;
int channel_HiHat = 1;
int channel_Lead = 2;

int pitch_Kick = 70;
int pitch_HiHat = 49;

int velocity = 127;
int noteDuration = 320;

float noteHeight_km1 = 0;

//////////////////////////////////////////////////////////////////
void setup()
{
	// Create a window.
	size(400, 400);
	background(0);
	
	// List all available Midi devices on stdout and create a MidiBus with no input and 'LoopBe' as output Midi device.
	MidiBus.list(); 

	myBus = new MidiBus(this, -1, "LoopBe Internal MIDI");
	
	// Start oscP5, listening for incoming messages at port 8000 */
	oscP5 = new OscP5(this, 8000);
  
  /* myRemoteLocation is a NetAddress. a NetAddress takes 2 parameters,
   * an ip address and a port number. myRemoteLocation is used as parameter in
   * oscP5.send() when sending osc packets to another computer, device, 
   * application. usage see below. for testing purposes the listening port
   * and the port of the remote location address are the same, hence you will
   * send messages back to this sketch.
   */
  myRemoteLocation = new NetAddress("127.0.0.1", 8000);
  
  /* osc plug service
   * osc messages with a specific address pattern can be automatically
   * forwarded to a specific method of an object. in this example 
   * a message with address pattern /test will be forwarded to a method
   * test(). below the method test takes 2 arguments - 2 ints. therefore each
   * message with address pattern /test and typetag ii will be forwarded to
   * the method test(int theA, int theB)
   */
  oscP5.plug(this, "HandleKick", "/iisu/user1/Kick");
  oscP5.plug(this, "HandleHiHat", "/iisu/user1/HiHat");
  oscP5.plug(this, "HandleNoteHeight", "/iisu/user1/NoteHeight");
  oscP5.plug(this, "HandleEnable", "/iisu/user1/Enable");
}

//////////////////////////////////////////////////////////////////
void draw()
{

}

//////////////////////////////////////////////////////////////////
public void HandleKick(float kick)
{	
	if (kick == 0.0f || isEnabled == 0.0f)
		return;

	println("Kick!");

	myBus.sendNoteOn(channel_Kick, pitch_Kick, velocity);
	delay(noteDuration);
	myBus.sendNoteOff(channel_Kick, pitch_Kick, velocity);
}

//////////////////////////////////////////////////////////////////
public void HandleHiHat(float hiHat)
{
	if (hiHat == 0.0f || isEnabled == 0.0f)
		return;

	println("HiHat!");

	myBus.sendNoteOn(channel_HiHat, pitch_HiHat, velocity);
	delay(noteDuration);
	myBus.sendNoteOff(channel_HiHat, pitch_HiHat, velocity);
}

//////////////////////////////////////////////////////////////////
public void HandleNoteHeight(float noteHeight)
{
	if (isEnabled == 0.0f)
		return;
		
	// Only send the Midi on height changed.
	if (noteHeight_km1 != noteHeight)
	{
		println("NoteHeight: " + noteHeight);
		
		// Old note off, new note on.
		myBus.sendNoteOff(channel_Lead, (int)noteHeight_km1, velocity);
		myBus.sendNoteOn(channel_Lead, (int)noteHeight, velocity);
	}
	
	noteHeight_km1 = noteHeight;
}

//////////////////////////////////////////////////////////////////
public void HandleEnable(float enable)
{
	if (enable == 0.0f)
		return;

	if (isEnabled == 0.0f)
	{
		isEnabled = 1.0f;
		
		println("Enable!");
	}
	else
	{
		isEnabled = 0.0f;
		
		println("Disable!");
		
		myBus.sendNoteOff(channel_Lead, (int)noteHeight_km1, velocity);
	}
}

//////////////////////////////////////////////////////////////////
void delay(int time)
{
	int current = millis();
	while (millis() < current + time)
		Thread.yield();
}

//////////////////////////////////////////////////////////////////
// Incoming osc message are forwarded to the oscEvent method.
void oscEvent(OscMessage theOscMessage)
{
	// // With theOscMessage.isPlugged() you check if the osc message has already been
	// // forwarded to a plugged method. if theOscMessage.isPlugged()==true, it has already 
	// // been forwared to another method in your sketch. theOscMessage.isPlugged() can 
	// // be used for double posting but is not required.  
	// if (theOscMessage.isPlugged() == false)
	// {
		// // Print the address pattern and the typetag of the received OscMessage.
		// println("### received an osc message.");
		// println("### addrpattern\t" + theOscMessage.addrPattern());
		// println("### typetag\t" + theOscMessage.typetag());
	// }

	// if (theOscMessage.checkAddrPattern("/iisu"))
	// {
		// if (theOscMessage.checkTypetag("T"))
		// {
			// userActivated = true;
		// }
		// else
		// {
			// userActivated = false;
		// }
		// println(" user active: " + userActivated);
	// }
}