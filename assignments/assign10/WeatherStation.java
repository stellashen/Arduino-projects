package assign10;

import java.io.InputStream;
import java.io.OutputStream;
import java.io.DataInputStream;
import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.URL;

import studio4.SerialComm;

public class WeatherStation {
	private int header,key;
	final private DataInputStream d;

	public WeatherStation() {
		SerialComm port = new SerialComm(); 
		InputStream input = port.getInputStream();
		d = new DataInputStream(input);
	}

	public enum State { idle,up0,up1,up2,up3,up4,up5,up6 };
	State counterState = State.idle;
	State nextState(State state) throws IOException {
		switch (state){
		case idle:
			header = d.read();//read the next byte
			if (header==0x21){ 
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
				else if (key==0x36){
					state = State.up6;
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
			System.out.print("timestamp:");
			int t = d.readInt();
			System.out.println(t);
			state = State.idle;
			break;

		case up3:
			System.out.print("potentiometer reading:");
			int pot = d.readShort();
			System.out.println(pot);
			state = State.idle;
			break;

		case up4:
			System.out.print("raw unfiltered temperature reading:");
			int raw = d.readShort();
			System.out.println(raw);
			state = State.idle;
			break;

		case up5:
			System.out.print("converted unfiltered temperature reading:");
			float temp = d.readFloat();
			System.out.println(temp);
			state = State.idle;
			break;

		case up6:
			System.out.print("filtered temperature reading:");
			float temp2 = d.readFloat();
			System.out.println(temp2);
			state = State.idle;
			break;
		}
		return state;
	}

	public void run(){
		while(true){
			try {
				if(d.available()>0){
					counterState = nextState(counterState);
				}
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}


	public static void main(String[] args) throws Exception {
		// Create a new instance of WeatherStation
		WeatherStation location = new WeatherStation();

		// declare variable
		boolean display = false;

		// Code from assign5.SerialOutput.java
		SerialComm port = new SerialComm(); 
		port.connect("/dev/cu.usbserial-DN01JD4W");
		try {
			// Code from assign4.MsgReceiver.java
			location.run();
		} catch (Exception e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}

		if(display){
			// Based on the name of the instance created above, call xx.sendGet().
			// This will test to the function we'll be creating below.
			location.sendGet();
		}
	}





	// HTTP GET request
	private void sendGet() throws Exception {

		// Create a string that contains the URL you created for Lopata Hall in Studio 10
		// Use the URL that DOES NOT have the timestamp included.
		// Since we only need the current data (currently) you can use the API to exclude all of the excess blocks (REQUIRED).
		// Instructions to do that are here: https://darksky.net/dev/docs/forecast
		// Test this new URL by pasting it in your web browser. You should only see the information about the current weather.
		String lopata = "https://api.darksky.net/forecast/c49524f84b5f40867542b9e381c9cf80/38.649196,-90.306099?exclude=minutely,hourly,daily,alerts,flags";

		// Create a new URL object with the URL string you defined above. Reference: https://docs.oracle.com/javase/7/docs/api/java/net/URL.html
		URL url = new URL(lopata);

		// Follow the instructions in the URL API to open this connection.
		// Cast this to a HttpURLConnection and save it in a new HttpURLConnection object.
		HttpURLConnection connection = (HttpURLConnection)url.openConnection();

		// Use the HttpURLConnection API to setup the HttpURLConnection you defined above.
		// Reference: https://docs.oracle.com/javase/7/docs/api/java/net/HttpURLConnection.html
		// Set the request method.
		connection.getRequestMethod();

		// Set the request property "User-Agent" to the User-Agent you saw in Wireshark when you did the first exercise in studio.
		// Repeat the quick wireshark example if you've forgotten. It should be in the form "xxxxxxx/#.#"
		connection.setRequestProperty("User-Agent","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.12; rv:49.0) Gecko/2010010 Firefox/49.0");
		connection.connect();

		// To debug, get and print out the response code.
		System.out.println(connection.getResponseCode());
		// The output should be 200.

		// The rest of the code should be much more familiar.
		// Create an InputStream that gets the input stream from our HttpURLConnection object.
		InputStream in = connection.getInputStream();

		// Wrap it in a DataInputStream
		DataInputStream d = new DataInputStream(in);


		// Read a line and save it in a string
		String line = d.readLine();

		// Close the InputStream
		d.close();


		// Using string manipulation tools, pull out the string between quotes after "icon:"
		// For example: "summary":"Clear","icon":"clear-day","nearestStormDistance":27
		// You should pull out JUST "clear-day"
		int index = line.indexOf("\"icon\"");
		//		System.out.println(index);
		String subIcon = line.substring(index);
		//		System.out.println(subIcon);
		String subIcon2 = subIcon.substring(8);
		//		System.out.println(subIcon2);
		int indexLast = subIcon2.indexOf('"');
		String icon = subIcon2.substring(0, indexLast);
		System.out.println(icon);

		// You will set this char (in a switch statement) to one of the 5 types of weather. (Nothing TODO here)
		char weatherChar = '\0';

		// Create a switch statement based on the string that contains the description (ex. clear-day)
		// The switch statement should be able to handle all 10 of the icon values from the API: https://darksky.net/dev/docs/response
		// If the value is any of the cloudy ones, set weatherChar to C
		// If the value is fog, set it to F
		// If the value if wind, set it to W
		// If the value is any of the clear ones, set it to S
		// If the value is any type of precipitation, set it to P
		switch(icon){
		case "cloudy":
			weatherChar = 'C';
			break;
		case "partly-cloudy-day":
			weatherChar = 'C';
			break;
		case "partly-cloudy-night":
			weatherChar = 'C';
			break;
		case "fog":
			weatherChar = 'F';
			break;
		case "wind":
			weatherChar = 'W';
			break;
		case "clear-day":
			weatherChar = 'S';
			break;
		case "clear-night":
			weatherChar = 'S';
			break;
		case "rain":
			weatherChar = 'P';
			break;
		case "snow":
			weatherChar = 'P';
			break;
		case "sleet":
			weatherChar = 'P';
			break;
		default:
			weatherChar = 'I';//I for invalid
			break;
		}

		// Now you're ready to implement this into your past code to send it to the Arduino.
		// You also have to make a couple modifications to handle the switch location requests from Arduino.
		// Choose three locations or more, but make sure one is Lopata Hall.

		//send weatherChar to Arduino to display
		try {
			SerialComm port = new SerialComm(); 
			OutputStream out = port.getOutputStream();
			out.write(weatherChar);
			//				@SuppressWarnings("resource")
			//				ViewOutputStream v = new ViewOutputStream(out);
			//				v.write(weatherChar);
			//				v.flush();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}


	}
}