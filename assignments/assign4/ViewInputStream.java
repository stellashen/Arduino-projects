package assign4;

import java.io.*;

import javax.swing.JFrame;
import studio4.PrintStreamPanel;

public class ViewInputStream extends FilterInputStream {

    final private PrintStreamPanel psp;
    final private PrintStream ps;

    public ViewInputStream(InputStream in) {
        super(in);
        JFrame f = new JFrame("ViewInputStream");
		f.setBounds(100,100,225,300);
        psp = new PrintStreamPanel();
		f.getContentPane().add(psp);
		f.setVisible(true);
        ps = psp.getPrintStream(); 
    }
    
	private int num1, num2;
	private String numString1, numString2;
    
	public int read() throws IOException{
        // TODO
        // use super.read() to access the next byte from the InputStream
        // also, you can use ps like System.out to print to the new window
    	// convert decimal ASCII values to hex 
    			int originValue = super.read();
    			num1 = originValue/16;
    			num2 = originValue%16;
    			if (num1 == 10){
    				numString1 = "a";
    			}
    			else if (num1 == 11){
    				numString1 = "b";
    			}
    			else if (num1 == 12){
    				numString1 = "c";	
    			}
    			else if (num1 == 13){
    				numString1 = "d";	
    			}
    			else if (num1 == 14){
    				numString1 = "e";	
    			}
    			else if (num1 == 15){
    				numString1 = "f";	
    			}
    			// else: num1 is 0-9
    			else{
    				numString1 = Integer.toString(num1);
    			}
    			
    			if (num2 == 10){
    				numString2 = "a";
    			}
    			else if (num2 == 11){
    				numString2 = "b";
    			}
    			else if (num2 == 12){
    				numString2 = "c";	
    			}
    			else if (num2 == 13){
    				numString2 = "d";	
    			}
    			else if (num2 == 14){
    				numString2 = "e";	
    			}
    			else if (num2 == 15){
    				numString2 = "f";	
    			}
    			else{
    				numString2 = Integer.toString(num2);
    			}

    			String hexString = " "+numString1+numString2;
    			ps.print(hexString);
    			return originValue;
    }
    
}
