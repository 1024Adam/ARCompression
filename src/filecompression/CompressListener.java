/* CompressListener.java */
package filecompression;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

/*
 * Adam Reid
 * November 26, 2015
 */

public class CompressListener implements ActionListener
{
    private JButton actionButton;
    private JButton listenButton;
    private JButton submit;

    public CompressListener(JButton actionButton, JButton listenButton, JButton submit)
    {
        this.actionButton = actionButton;
        this.listenButton = listenButton;
        this.submit = submit;
    }

    @Override
    public void actionPerformed(ActionEvent e) 
    {
    	if(this.actionButton.getText().equalsIgnoreCase("Compress") || this.actionButton.getText().equalsIgnoreCase("<html><b>Compress</b></html>"))
    	{
    	    this.actionButton.setText("<html><b>Compress</b></html>");
            this.actionButton.setSelected(true);	
            this.listenButton.setText("Decompress");
            this.listenButton.setSelected(false);

            this.submit.setText("<html><b>Compress File</b></html>");
    	}
    	else
    	{
    	    this.actionButton.setText("<html><b>Decompress</b></html>");
            this.actionButton.setSelected(true);	
            this.listenButton.setText("Compress");
            this.listenButton.setSelected(false);

            this.submit.setText("<html><b>Decompress File</b></html>");
    	}
    }
}
