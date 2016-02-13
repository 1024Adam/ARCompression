/* SubmitListener.java */
package arcompression;

import java.awt.event.*;

import javax.swing.*;

/*
 * Adam Reid
 * February 13, 2016
 */

public class SubmitListener implements ActionListener 
{
    private JTextArea textArea;
    private JButton submit;
    
    native void compressFile();
    native void decompressFile();
    static { System.loadLibrary("javahuffman"); }
    
    /* Constructors */
    public SubmitListener(JTextArea textArea, JButton submit)
    {
        this.textArea = textArea;
        this.submit = submit;
    }
	
    @Override
    public void actionPerformed(ActionEvent e) 
    {
        /* TODO: Action the compress/decompress feature */
    	if(this.submit.getText().equalsIgnoreCase("<html><b>Compress File</b></html>"))
        {
        	compressFile();
        }
    	if(this.submit.getText().equalsIgnoreCase("<html><b>Decompress File</b></html>"))
        {
        	decompressFile();
        }
        if(textArea.getText().equalsIgnoreCase(""))
        {
            textArea.setText("You pressed the button");
        }
        else
        {
            textArea.setText(textArea.getText() + "\nYou pressed the button");
        }
    }
}
