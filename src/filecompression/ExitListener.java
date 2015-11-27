package filecompression;

import java.awt.event.*;

/*
 * Adam Reid
 * November 26, 2015
 */

public class ExitListener extends WindowAdapter
{
    @Override
    public void windowClosing(WindowEvent e)
    {
        ConfirmWindow check = new ConfirmWindow();
        check.setVisible(true);
    }
}