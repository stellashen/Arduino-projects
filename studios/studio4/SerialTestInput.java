package studio4;

import java.io.InputStream;
//import java.io.OutputStream;

public class SerialTestInput {

	public static void main(String[] args) {
		
		try
		{
			SerialComm port = new SerialComm(); 
			port.connect("/dev/cu.usbserial-DN01JD4W");
			InputStream in = port.getInputStream();
//            OutputStream out = port.getOutputStream();
            int i = in.available();
            System.out.println(i+" bytes can be read from this port.");
            // when use heartbeat.ino, 62 bytes
            // read(): -1 is returned in the end of the stream
            while (in.read() > -1){
            System.out.println(in.read());
            }
		}
		catch (Exception e)
		{
			 e.printStackTrace();
		}

	}

}
