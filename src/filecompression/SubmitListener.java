package filecompression;

import java.awt.event.*;
import javax.swing.*;

/*
 * Adam Reid
 * November 26, 2015
 */

public class SubmitListener implements ActionListener 
{
    private JTextArea textArea;

	public SubmitListener(JTextArea textArea)
    {
        this.textArea = textArea;
    }
	
	@Override
	public void actionPerformed(ActionEvent e) 
	{
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
