package assign4;

import studio4.SerialComm;
import studio4.ViewInputStream;

import java.io.*;

// 1) data in hex goes through the ViewInputStream window 
// 2) print in the java console

public class MsgReceiver {

	final private ViewInputStream vis;
	private int header,key;

	public MsgReceiver(InputStream in) {
		vis = new ViewInputStream(in);
	}

	//FSM: each state represents different data types; 
	//an idle state for waiting for the magic number

	//	public enum State { idle,up0,up1,up2,up3,up4,up5,up6 }
	//	State counterState = State.idle;
	//	State nextState(State state) throws IOException {
	//		DataInputStream d = new DataInputStream(vis);
	//		switch (state){
	//		case idle:
	//			header = d.read();//read the next byte
	//			if (header==0x21){ 
	//				key = d.read();
	//				if (key==0x30){
	//					state = State.up0;
	//				}
	//				else if (key==0x31){
	//					state = State.up1;
	//				}
	//				else if (key==0x32){
	//					state = State.up2;
	//				}
	//				else if (key==0x33){
	//					state = State.up3;
	//				}
	//				else if (key==0x34){
	//					state = State.up4;
	//				}
	//				else if (key==0x35){
	//					state = State.up5;
	//				}
	//				else if (key==0x36){
	//					state = State.up6;
	//				}
	//				else {
	//					state = State.idle;
	//				}
	//			}
	//			else {
	//				state = State.idle;
	//			}
	//			break;
	//
	//		case up0:
	//			System.out.print("debugging string:");
	//			String debugMessage = d.readUTF();
	//			System.out.println(debugMessage);
	//			state = State.idle;
	//			break;
	//
	//		case up1:
	//			System.out.print("error string:");
	//			String errorMessage = d.readUTF();
	//			System.out.println(errorMessage);
	//			state = State.idle;
	//			break;
	//
	//		case up2:
	//			System.out.print("timestamp:");
	//			int t = d.readInt();
	//			System.out.println(t);
	//			state = State.idle;
	//			break;
	//
	//		case up3:
	//			System.out.print("potentiometer reading:");
	//			int pot = d.readShort();
	//			System.out.println(pot);
	//			state = State.idle;
	//			break;
	//
	//		case up4:
	//			System.out.print("raw unfiltered temperature reading:");
	//			int raw = d.readShort();
	//			System.out.println(raw);
	//			state = State.idle;
	//			break;
	//
	//		case up5:
	//			System.out.print("converted unfiltered temperature reading:");
	//			float temp = d.readFloat();
	//			System.out.println(temp);
	//			state = State.idle;
	//			break;
	//
	//		case up6:
	//			System.out.print("filtered temperature reading:");
	//			float temp2 = d.readFloat();
	//			System.out.println(temp2);
	//			state = State.idle;
	//			break;
	//		}
	//		return state;
	//	}

	public void run() {
		// insert code here
		// read from vis and write to console

		try
		{
			DataInputStream d = new DataInputStream(vis);
			while(true){
				if (vis.available()>0){
					//								int numBytes = vis.available();
					//								System.out.println(numBytes+" bytes can be read from this port.");
					//counterState = nextState(counterState);

					header = d.read();
					if (header==0x21){ 
						key = d.read();
						if (key==0x30){
							System.out.println();
							System.out.print("debugging string:");
							String debugMessage = d.readUTF();
							System.out.println(debugMessage);
						}
						else if (key==0x31){
							System.out.print("error string:");
							String errorMessage = d.readUTF();
							System.out.println(errorMessage);
						}
						else if (key==0x32){
							System.out.print("timestamp:");
							int t = d.readInt();
							System.out.println(t);
						}
						else if (key==0x33){
							System.out.print("potentiometer reading:");
							int pot = d.readShort();
							System.out.println(pot);
						}
						else if (key==0x34){
							System.out.print("raw unfiltered temperature reading:");
							int raw = d.readShort();
							System.out.println(raw);
						}
						else if (key==0x35){
							System.out.print("converted unfiltered temperature reading:");
							float temp = d.readFloat();
							System.out.println(temp);
						}
						else if (key==0x36){
							System.out.print("filtered temperature reading:");
							float temp2 = d.readFloat();
							System.out.println(temp2);
						}
					}
					
				}
			}
		}
		catch ( Exception e )
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		try
		{        	
			SerialComm s = new SerialComm();
			s.connect("/dev/cu.usbserial-DN01JD4W"); // Adjust this to be the right port for your machine
			InputStream in = s.getInputStream();
			MsgReceiver msgr = new MsgReceiver(in);
			msgr.run();

		}
		catch ( Exception e )
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}
}

//41 6c 61 72 6d
//Alarm
