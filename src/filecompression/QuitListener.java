package filecompression;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/*
 * Adam Reid
 * November 26, 2015
 */

public class QuitListener implements ActionListener 
{
    @Override
    public void actionPerformed(ActionEvent e)
    {
        ConfirmWindow confirm = new ConfirmWindow();
        confirm.setVisible(true);
    }
}
