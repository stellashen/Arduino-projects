/* receiver & data visualization
 *  
 *  CSE 132 - Assignment 9
 *  
 *  Fill this out so we know whose assignment this is.
 *  
 *  Name: Yangchen Shen
 *  WUSTL Key: sheny
 *  
 */
package assign9;

import java.io.DataInputStream;
import java.io.IOException;
import java.io.InputStream;

import studio4.SerialComm;

public class FitbitPlot {
	final private DataInputStream d;
	private int header,key;

	public FitbitPlot(InputStream in){
		d = new DataInputStream(in);
	}
	
	//FSM: each state represents different data types; 
	//an idle state for waiting for the magic number

	public enum State { idle,up0,up1,up2,up3,up4,up5,x,y,z};
	State counterState = State.idle;
	State nextState(State state) throws IOException {
		switch (state){
		case idle:
			header = d.read();//read the next byte
			if (header==0x23){ 
				key = d.read();
				if (key==0x30){
					state = State.up0;
				}
				else if (key==0x31){
					state = State.up1;
				}
				else if (key==0x32){
					state = State.up2;
				}
				else if (key==0x33){
					state = State.up3;
				}
				else if (key==0x34){
					state = State.up4;
				}
				else if (key==0x35){
					state = State.up5;
				}
				else if (key==0x78){
					state = State.x;
				}
				else if (key==0x79){
					state = State.y;
				}
				else if (key==0x80){
					state = State.z;
				}
				else {
					state = State.idle;
				}
			}
			else {
				state = State.idle;
			}
			break;

		case up0:
			System.out.println();
			System.out.print("debugging string:");
			String debugMessage = d.readUTF();
			System.out.println(debugMessage);
			state = State.idle;
			break;

		case up1:
			System.out.print("error string:");
			String errorMessage = d.readUTF();
			System.out.println(errorMessage);
			state = State.idle;
			break;

		case up2:
			System.out.print("filtered temperature reading:");
			float temp2 = d.readFloat();
			System.out.println(temp2);
			state = State.idle;
			break;

		case up3:
			System.out.print("step counts:");
			int step = d.readShort();
			System.out.println(step);
			state = State.idle;
			break;

		case up4:
			System.out.print("time spent asleep:");
			int sleep = d.readInt();
			System.out.println(sleep);
			state = State.idle;
			break;

		case up5:
			System.out.print("timestamp:");
			int t = d.readInt();
			System.out.println(t);
			state = State.idle;
			break;
		case x:
			System.out.print("x:");
			float readX = d.readFloat();
			System.out.println(readX);
			state = State.idle;
			break;
		case y:
			System.out.print("y:");
			float readY = d.readFloat();
			System.out.println(readY);
			state = State.idle;
			break;
		case z:
			System.out.print("z:");
			float readZ = d.readFloat();
			System.out.println(readZ);
			state = State.idle;
			break;
		}
		return state;
	}

	public void run() {
		// insert code here
		// read from vis and write to console

		try
		{
			while(true){
				if (d.available()>0){
			counterState = nextState(counterState);
				}
			}
		}

		catch ( Exception e )
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}	
	}
	
	public static void main(String[] args) {
		try
		{        	
			SerialComm s = new SerialComm();
			s.connect("/dev/cu.usbserial-DN01JD4W"); // Adjust this to be the right port for your machine
			InputStream in = s.getInputStream();
			FitbitPlot receiver = new FitbitPlot(in);
			receiver.run();
		}
		catch ( Exception e )
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

}
