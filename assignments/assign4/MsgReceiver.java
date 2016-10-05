package assign4;

import studio4.SerialComm;
import studio4.ViewInputStream;

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
            s.connect("/dev/cu.usbserial-DN01JD4W"); // Adjust this to be the right port for your machine
            InputStream in = s.getInputStream();
//            MsgReceiver msgr = new MsgReceiver(in);
//            msgr.run();
            
			BufferedInputStream newChar = new BufferedInputStream(in);
			@SuppressWarnings("resource")
			ViewInputStream v = new ViewInputStream(newChar);
			int numBytes = in.available();
			System.out.println(numBytes+" bytes can be read from this port.");
			while(true){
				if(in.available()>0){
					// 1) data in hex goes through the ViewInputStream window 
					//...while v.read() is executed 
					// 2) store sourceVal and convert it to char, and print in the java console
					int sourceVal= v.read();
					char outVal = (char)sourceVal;
					System.out.print(outVal);
				}
			}
            
        }
        catch ( Exception e )
        {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

	}

}
