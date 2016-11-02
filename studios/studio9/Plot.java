package studio9;

import java.awt.Font;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

import sedgewick.StdDraw;

public class Plot {

	public static void main(String[] args) throws FileNotFoundException{
		File file = new File("studios/studio8/data/steps.csv");
		FileReader fr = new FileReader(file);
		@SuppressWarnings("resource")
		BufferedReader br = new BufferedReader(fr);

		String data;
		String[] parts;
		String[] yVal = new String[695];
		float[] y = new float[695];
		int i = 0;

		//set size
		StdDraw.setCanvasSize(600, 200);
		StdDraw.setXscale(0, 800);
		StdDraw.setYscale(0, 3);
		//draw x axis
		StdDraw.setPenRadius(0.001);
		StdDraw.setPenColor(StdDraw.BLACK);
		StdDraw.line(60, 0.5, 770, 0.5);
		//draw y axis
		StdDraw.line(50, 0.5, 50, 2.2);
		//draw tick marks & values
		Font font = new Font("Arial", Font.BOLD, 10);
		StdDraw.setFont(font);
		for(int t = 60; t < 770; t = t+50){
			StdDraw.line(t, 0.5, t, 0.45);
			StdDraw.text(t, 0.3, Integer.toString(t-60));
		}
		for(double j = 0.7; j < 2.2; j = j + 0.2){
			StdDraw.line(50, j , 45, j);
			StdDraw.text(30, j, String.format("%1$,.2f", j-0.5));
		}
		//add title and axis labels
		StdDraw.text(400, 0.1, "Time(ms)");
		StdDraw.text(5, 1.5, "y", 90);
		font = new Font("Arial", Font.BOLD, 20);
		StdDraw.setFont(font);
		StdDraw.text(400, 2.5, "y values over time (y is pointing down)");

		// read and draw y values
		StdDraw.setPenRadius(0.01);
		StdDraw.setPenColor(StdDraw.ORANGE);
		try {
			while(br.ready()){
				data = br.readLine( );
				parts = data.split(",");
				yVal[i] = parts[1];
				y[i] = Float.valueOf(yVal[i]);
				StdDraw.point(60+i,0.5+y[i]);
				i = i + 1;
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}
}