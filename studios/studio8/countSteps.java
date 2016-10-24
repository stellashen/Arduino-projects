package studio8;
// references: 
// https://coderanch.com/t/527038/java/Reading-text-file-FileReader-BufferedReader
// http://alvinalexander.com/blog/post/java/how-open-read-file-java-string-array-list
// http://stackoverflow.com/questions/3481828/how-to-split-a-string-in-java

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class countSteps {

	public static void main(String[] args) throws FileNotFoundException {
		File file = new File("studios/studio8/data/steps.csv");
		FileReader fr = new FileReader(file);
		@SuppressWarnings("resource")
		BufferedReader br = new BufferedReader(fr);

		String data;
		String[] parts;
		String[] xVal = new String[695];
		String[] yVal = new String[695];
		String[] zVal = new String[695];
		int i = 0;

		// read and print x, y, z values
		try {
			// cannot use readLine() here because this line will disappear after being read
			//			while(br.readLine( ) != null) 
			while(br.ready())
			{
				data = br.readLine( );
				parts = data.split(",");
				xVal[i] = parts[0];
				yVal[i] = parts[1];
				zVal[i] = parts[2];
				System.out.print("x:"+parts[0]+" ");
				System.out.print("y:"+parts[1]+" ");
				System.out.print("z:"+parts[2]);
				System.out.println();
				//				System.out.println(data);

				i = i + 1;
				//				System.out.println("i is "+i);
			}
			System.out.println("i is "+i);

			// calculate the mean of y values
			float y = 0;
			float sumY = 0;
			for (int j = 0; j < 100; j++){
				//				y = Float.parseFloat(yVal[j]);
				y = Float.valueOf(yVal[j]);
				sumY = sumY + y;
			}
			float avgY = sumY/yVal.length;
			System.out.println("average y value is: "+avgY);

		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}


	}
}
