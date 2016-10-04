package studio4;

import java.io.BufferedInputStream;
import java.io.InputStream;
//import java.io.OutputStream;

//On a mac, to fix problems:
//Open up Terminal
//Type sudo mkdir /var/lock (without the quotes) and press enter. 
//Type sudo chmod go+rwx /var/lock (without the quotes) and press enter.

//My port name is "/dev/cu.usbserial-DN01JD4W"
//Native library location: CSE132-sheny/jars/jars

public class SerialTestInput {

	public static void main(String[] args) {
		// 2.reimplement: added ViewInputStream window where data stream in hex

		try {
			SerialComm port = new SerialComm(); 
			port.connect("/dev/cu.usbserial-DN01JD4W");
			// wrapping
			InputStream in = port.getInputStream();	
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
		} catch (Exception e) {
			e.printStackTrace();
		}


		//1.
		//		try
		//		{
		//			SerialComm port = new SerialComm(); 
		//			port.connect("/dev/cu.usbserial-DN01JD4W");
		//			InputStream in = port.getInputStream();			
		//			int i = in.available();
		//			System.out.println(i+" bytes can be read from this port.");
		//			
		//			while(true){
		//				if (in.available()>0){
		//					// print ASCII value in Java console
		//					// System.out.println(in.read());
		//					
		//					// show the same text as in serial monitor
		//					char text = (char)in.read();
		//					System.out.print(text);
		//				}
		//			}
		//		}
		//		catch (Exception e)
		//		{
		//			e.printStackTrace();
		//		}
	}
}
