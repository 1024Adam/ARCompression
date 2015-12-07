/* SubmitListener.java */
package arcompression;

import java.awt.event.*;
import javax.swing.*;

/*
 * Adam Reid
 * December 7, 2015
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
