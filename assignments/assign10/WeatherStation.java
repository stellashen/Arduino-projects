package assign10;

import java.io.InputStream;
import java.io.DataInputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class WeatherStation {

	public static void main(String[] args) throws Exception {
		// Create a new instance of WeatherStation
		WeatherStation location = null;


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
		String lopata = "38.649196,-90.306099";


		// Create a new URL object with the URL string you defined above. Reference: https://docs.oracle.com/javase/7/docs/api/java/net/URL.html



		// Follow the instructions in the URL API to open this connection.
		// Cast this to a HttpURLConnection and save it in a new HttpURLConnection object.



		// Use the HttpURLConnection API to setup the HttpURLConnection you defined above.
		// Reference: https://docs.oracle.com/javase/7/docs/api/java/net/HttpURLConnection.html
		// Set the request method.



		// Set the request property "User-Agent" to the User-Agent you saw in Wireshark when you did the first exercise in studio.
		// Repeat the quick wireshark example if you've forgotten. It should be in the form "xxxxxxx/#.#"



		// To debug, get and print out the response code.



		// The rest of the code should be much more familiar.
		// Create an InputStream that gets the input stream from our HttpURLConnection object.



		// Wrap it in a DataInputStream



		// Read a line and save it in a string



		// Close the InputStream



		// Using string manipulation tools, pull out the string between quotes after "icon:"
		// For example: "summary":"Clear","icon":"clear-day","nearestStormDistance":27
		// You should pull out JUST "clear-day"



		// You will set this char (in a switch statement) to one of the 5 types of weather. (Nothing TODO here)
		char weatherChar = '\0';

		// Create a switch statement based on the string that contains the description (ex. clear-day)
		// The switch statement should be able to handle all 10 of the icon values from the API: https://darksky.net/dev/docs/response
		// If the value is any of the cloudy ones, set weatherChar to C
		// If the value is fog, set it to F
		// If the value if wind, set it to W
		// If the value is any of the clear ones, set it to S
		// If the value is any type of precipitation, set it to P



		// Now you're ready to implement this into your past code to send it to the Arduino.
		// You also have to make a couple modifications to handle the switch location requests from Arduino.
		// Choose three locations or more, but make sure one is Lopata Hall.
	}
}