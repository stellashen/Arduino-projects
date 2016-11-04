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

import sedgewick.StdDraw;
import java.awt.Font;

import studio4.SerialComm;

public class FitbitPlot {
	final private DataInputStream d;
	private int header,key;
	private int count = 0;
	private float[] readX = new float[45];
	private float[] readY = new float[45];
	private float[] readZ = new float[45];

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

		case x:
			// when point45 show up, replace the last point (point44 on the far right) with the newest point
			// count will always stay 44, so the new data will always be plotted on the right location
			if (count > 44){
				count = 44;
				//ignore the original point0,
				//and move the original point1-44 to the left so they become the new point0-43
				for (int i = 0; i < 44; i++){
					readX[i]=readX[i+1];
				}
				readX[count] = d.readFloat();
				System.out.print("x:");
				System.out.println(readX[count]);
				//set count to 45 again so it can be used by case y
				count = 45;
			}
			else{
				readX[count] = d.readFloat();
				System.out.print("x:");
				System.out.println(readX[count]);
			}
			state = State.idle;
			break;

		case y:
			if (count > 44){
				count = 44;
				for (int i = 0; i < 44; i++){
					readY[i]=readY[i+1];
				}
				readY[count] = d.readFloat();
				System.out.print("y:");
				System.out.println(readY[count]);
				//set count to 45 again so it can be used by case z
				count = 45;
			}
			else{
				readY[count] = d.readFloat();
				System.out.print("y:");
				System.out.println(readY[count]);
			}
			state = State.idle;
			break;

		case z:
			if (count > 44){
				count = 44;
				for (int i = 0; i < 44; i++){
					readZ[i]=readZ[i+1];
				}
			}
			readZ[count] = d.readFloat();
			System.out.print("z:");
			System.out.println(readZ[count]);
			state = State.idle;
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
			draw();
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

	//refresh the image every 1 second
	public void draw(){
		//clear the canvas
		StdDraw.clear();
		count = count + 1;
		
		for (int i = 0; i < count; i++){
			plot(readX[i],readY[i],readZ[i],i);
		}

		StdDraw.show();
	}

	public void plot(float x,float y,float z,int i){
		StdDraw.setPenRadius(0.01);
		StdDraw.setPenColor(StdDraw.BLUE);
		StdDraw.point(5+i,5+x);
		StdDraw.setPenColor(StdDraw.ORANGE);
		StdDraw.point(5+i,5+y);
		StdDraw.setPenColor(StdDraw.RED);
		StdDraw.point(5+i,5+z);
	}


	public static void main(String[] args) {
		StdDraw.enableDoubleBuffering();
		//set size
		StdDraw.setCanvasSize(800, 600);
		StdDraw.setXscale(0, 60);
		StdDraw.setYscale(0, 10);

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
