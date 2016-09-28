package assignment4;

import studio4.SerialComm;
import java.io.*;

public class MsgReceiver {

	final private ViewInputStream vis;
	
	public MsgReceiver(InputStream in) {
		vis = new ViewInputStream(in);
	}
	
	public void run() {
		// insert code here
		// read from vis and write to console
		
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
        try
        {        	
            SerialComm s = new SerialComm();
            s.connect("COM4"); // Adjust this to be the right port for your machine
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
