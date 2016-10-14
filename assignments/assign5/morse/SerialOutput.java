package assign5.morse;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;

import studio4.SerialComm;

public class SerialOutput {

	public static void main(String[] args) {
		SerialComm port = new SerialComm(); 
		try {
			port.connect("/dev/cu.usbserial-DN01JD4W");
		} catch (Exception e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}

		//System.out.println(inputVal);
		while(true){
			BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
			String inputVal = "";
			try {
				inputVal = in.readLine();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}

			try {
				OutputStream out = port.getOutputStream();
				@SuppressWarnings("resource")
				ViewOutputStream v = new ViewOutputStream(out);
				for (int i=0; i<inputVal.length(); i++){
					//System.out.println(inputVal.charAt(i));
					v.write(inputVal.charAt(i));
					v.flush();
				}
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

}
