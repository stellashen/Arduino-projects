package studio4;

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

		try
		{
			SerialComm port = new SerialComm(); 
			port.connect("/dev/cu.usbserial-DN01JD4W");
			InputStream in = port.getInputStream();			
			// OutputStream out = port.getOutputStream();
			int i = in.available();
			System.out.println(i+" bytes can be read from this port.");
			while(true){
				if (in.available() > 0){
					char text = (char)in.read();
					System.out.print(text);
				}
			}

		}
		catch (Exception e)
		{
			e.printStackTrace();
		}

	}

}
