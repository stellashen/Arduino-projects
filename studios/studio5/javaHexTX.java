package studio5;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;

import studio4.SerialComm;

public class javaHexTX {
	//6.1 Get User Input
	public static void main(String[] args) {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		String inputVal = "000";
		try {
			inputVal = in.readLine();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		while (inputVal.length()>1){
			System.out.println("You have entered more than 1 characters. "
					+ "Please only enter one character at a time.");	
			try {
				inputVal = in.readLine();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
		// https://docs.oracle.com/javase/7/docs/api/java/lang/String.html#charAt(int)
		int myVar=inputVal.charAt(0);
		//System.out.println(myVar);
		
		while (myVar < 48 || (myVar > 57 && myVar < 65) 
				|| (myVar > 90 && myVar < 97) || myVar > 122){
			System.out.println("What you entered is not a number or letter. "
					+ "Please try again.");
			try {
				inputVal = in.readLine();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			myVar=inputVal.charAt(1);
		}
		
		System.out.print(inputVal);
		
		// 6.2
		SerialComm port = new SerialComm(); 
		try {
			port.connect("/dev/cu.usbserial-DN01JD4W");
			OutputStream out = port.getOutputStream();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}

}
