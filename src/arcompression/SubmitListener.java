/* SubmitListener.java */
package arcompression;

import java.awt.event.*;

import javax.swing.*;

/*
 * Adam Reid
 * June 18, 2016
 */

public class SubmitListener implements ActionListener 
{
    private JTextArea textArea;
    private JButton submit;
    private JTextField file;
    
    private native void compressFile(String path);
    private native void decompressFile(String path);
    static { System.loadLibrary("SubmitListener"); }
    
    /* Constructors */
    public SubmitListener(JTextArea textArea, JButton submit, JTextField file)
    {
        this.textArea = textArea;
        this.submit = submit;
        this.file = file;
    }
	
    @Override
    public void actionPerformed(ActionEvent e) 
    {
        /* TODO: Action the compress/decompress feature */
    	if(this.submit.getText().equalsIgnoreCase("<html><b>Compress File</b></html>"))
        {
            compressFile(file.getText());
        }
    	if(this.submit.getText().equalsIgnoreCase("<html><b>Decompress File</b></html>"))
        {
            decompressFile(file.getText());
        }
        if(textArea.getText().equalsIgnoreCase(""))
        {
            textArea.setText("You pressed the button\n" + this.file.getText());
        }
        else
        {
            textArea.setText(textArea.getText() + "\nYou pressed the button\n" + this.file.getText());
        }
    }
}
