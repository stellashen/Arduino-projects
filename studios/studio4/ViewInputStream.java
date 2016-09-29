package studio4;

import java.io.*;

import javax.swing.JFrame;

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

	public int read() throws IOException {
		int character = super.read();
		// TODO
		// use super.read() to access the next byte from the InputStream
		// also, you can use ps like System.out to print to the new window
		String thisString = Integer.toHexString(character);
		ps.print(thisString);
		return character;
	}



}
