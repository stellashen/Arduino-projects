package assign10;

import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.URL;

import assign5.morse.ViewOutputStream;
import studio4.SerialComm;

public class WeatherStation {

	public static void main(String[] args) throws Exception {
		// Create a new instance of WeatherStation
		WeatherStation location = new WeatherStation();


		// Based on the name of the instance created above, call xx.sendGet().
		// This will test to the function we'll be creating below.
		location.sendGet();

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
		SerialComm port = new SerialComm(); 
		try {
			port.connect("/dev/cu.usbserial-DN01JD4W");
		} catch (Exception e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		while(true){
			try {
				OutputStream out = port.getOutputStream();
				@SuppressWarnings("resource")
				ViewOutputStream v = new ViewOutputStream(out);
					v.write(weatherChar);
					v.flush();
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
}