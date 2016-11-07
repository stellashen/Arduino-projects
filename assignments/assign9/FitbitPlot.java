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
	private int limit = 1806; //45s, read in 1806 values (count = 0 ~ 1805)
	private float readX, readY, readZ;
	private float temp;
	private int sleep;
	private int timestamp;
	private Font font;

	private float[] x = new float[limit];
	private float[] y = new float[limit];
	private float[] z = new float[limit];
	private int[] time = new int[limit];

	private int step = 0;
	private int stepPrevious = 0;
	private int[] isPeak = new int[limit];
	private boolean stepMode = true;

	private int stepResetTime = 0;

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
			readX = d.readFloat();
			System.out.print("x:");
			System.out.println(readX);
			state = State.idle;
			break;

		case y:
			readY = d.readFloat();
			System.out.print("y:");
			System.out.println(readY);
			state = State.idle;
			break;

		case z:
			readZ = d.readFloat();
			System.out.print("z:");
			System.out.println(readZ);
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
			temp = d.readFloat();
			System.out.println(temp);
			state = State.idle;
			break;

		case up3:
			stepMode = true;
			System.out.print("step counts:");
			step = d.readShort();
			System.out.println(step);
			state = State.idle;
			break;

		case up4:
			stepMode = false;
			System.out.print("time spent asleep:");
			sleep = d.readInt();
			System.out.println(sleep);
			state = State.idle;
			break;

		case up5:
			System.out.print("timestamp:");
			timestamp = d.readInt();
			System.out.println(timestamp);
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

	public void draw(){
		//clear the canvas
		StdDraw.clear();
		//***draw x and y axis
		axis(timestamp);
		//***draw x,y,z points
		if (count<limit-1){
			x[count] = readX;
			y[count] = readY;
			z[count] = readZ;
			time[count] = timestamp;
			//draw the plot (x,y,z)
			for(int i = 0; i < limit; i++){
				if(x[i]!=0){
					plot(x[i],y[i],z[i],time[i]);
				}
			}
		}
		else{
			//previous plots
			for(int i = 0; i < limit-1; i++){
				x[i] = x[i+1];
				y[i] = y[i+1];
				z[i] = z[i+1];
				time[i] = time[i+1];
			}
			//new points
			x[limit-1] = readX;
			y[limit-1] = readY;
			z[limit-1] = readZ;
			time[limit-1] = timestamp;
			//draw
			for(int i = 0; i < limit; i++){
				plot(x[i],y[i],z[i],time[i]);
			}
			count = count - 1;
		}

		//***update the time of step reset 
		if(stepPrevious>0 && step == 0){
			stepResetTime = timestamp;
		}
		
		if (stepMode){
			//***label peak of steps
			// 1) if count < limit
			if(count < limit){
				//detect if there is a new peak
				if (step > stepPrevious){
					isPeak[count] = 1;
				}

			}
			else{
				// 2) if count = limit
				//move previous labels to the left
				for(int i = 0; i<limit-1; i++){
					isPeak[i] = isPeak[i+1];
				}
				//detect if there is a new peak
				if (step > stepPrevious){
					isPeak[limit-1] = 1;
				}
				else{
					isPeak[limit-1] = 0;
				}
			}

			// 3) label peaks
			for(int i = 0; i<limit; i++){
				if(isPeak[i]==1){
					labelPeak(time[i]);
				}
			}

			stepPrevious = step;
		}
		else{
			//clear previous labels
			for(int i = 0; i<limit; i++){
				isPeak[i] = 0;
			}
		}

		//***draw text indicators
		indicators();

		StdDraw.show();
		count = count + 1;
	}

	int dy = 5000;//distance between y axis(x=0) and the left side of display window
	int dx = 5; // distance between x axis(y=0) and the bottom of display window
	int timeLabelStart = 0;
	public void axis(int t){
		//draw x axis
		StdDraw.setPenRadius(0.001);
		StdDraw.setPenColor(StdDraw.BLACK);
		StdDraw.line(dy, dx-3, dy+46000, dx-3);
		//draw y axis
		StdDraw.line(dy, dx-3, dy, dx+3.5);
		//draw tick marks & values
		if(t>45000){
			timeLabelStart=(t-45000)/1000;//change time labels when running time >=46 s
		}
		font = new Font("Arial", Font.BOLD, 12);
		StdDraw.setFont(font);
		for(int k = dy; k <= dy+45000; k = k+5000){
			if(k!=0){
				StdDraw.line(k, dx-3, k, dx-3.25);
				StdDraw.text(k, dx-3.5, Integer.toString(timeLabelStart+(k-dy)/1000));
			}
		}
		for(double j = -3.0; j < 3.1; j = j + 0.5){
			StdDraw.line(dy, dx+j , dy-300, dx+j);
			StdDraw.text(dy-1000, dx+j, String.format("%1$,.2f", j));
		}
		//add title and axis labels
		font = new Font("Arial", Font.BOLD, 20);
		StdDraw.text(27000, dx-4, "Total Run Time (second)");
		StdDraw.text(dy-3000,dx,  "values", 90);
		StdDraw.text(27000, dx+3.2, "blue: x    yellow: y    red: z");
		font = new Font("Arial", Font.BOLD, 28);
		StdDraw.setFont(font);
		StdDraw.text(27000, dx+4, "Fitbit Visualization: x,y,z values over time");
	}

	public void plot(float x,float y,float z,int i){
		if (i >= 1000*timeLabelStart){
			StdDraw.setPenRadius(0.005);
			StdDraw.setPenColor(StdDraw.BLUE);
			StdDraw.point(dy+i-1000*timeLabelStart,dx+x);
			StdDraw.setPenColor(StdDraw.ORANGE);
			StdDraw.point(dy+i-1000*timeLabelStart,dx+y);
			StdDraw.setPenColor(StdDraw.RED);
			StdDraw.point(dy+i-1000*timeLabelStart,dx+z);
		}
	}

	public void labelPeak(int t){
		if (t > 1000*timeLabelStart){
			font = new Font("Arial", Font.BOLD, 12);
			StdDraw.setFont(font);
			StdDraw.setPenColor(StdDraw.ORANGE);
			StdDraw.text(dy+t-1000*timeLabelStart, 7, "peak");
		}
	}

	double hour = 0.0;
	int hourSleep = 0;
	int minSleep = 0;
	int secSleep = 0;
	double stepText = 0;
	public void indicators(){
		font = new Font("Arial", Font.BOLD, 12);
		StdDraw.setFont(font);
		StdDraw.setPenColor(StdDraw.BLACK);
		StdDraw.text(50000, 8.5, "The current temperature: "+ String.format("%1$,.2f", temp) + " degrees");
		if(stepMode){
			StdDraw.text(50000, 8, "The number of steps taken since the last reset: "+Integer.toString(step));
			hour = (timestamp-stepResetTime)*0.1/3600;
			if (hour!=0){
				stepText = step*0.1/hour;
			}
			StdDraw.text(50000, 7.5, "The current rate of steps since the last reset: "+String.format("%1$,.2f", stepText)+" steps per hour");
		}
		else{
			hourSleep = sleep/3600000;
			minSleep = (sleep-hourSleep*3600000)/60000;
			secSleep = (sleep-hourSleep*3600000-minSleep*60000)/1000;
			//sleep time is updated every 10 seconds
			StdDraw.text(50000, 8, "The total amount of sleep: "+Integer.toString(hourSleep)+" h "
					+Integer.toString(minSleep)+" min "+Integer.toString(secSleep)+" s");
		}
	}

	public static void main(String[] args) {
		StdDraw.enableDoubleBuffering();
		//set size
		StdDraw.setCanvasSize(1400, 500);
		StdDraw.setXscale(0, 60000);
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
