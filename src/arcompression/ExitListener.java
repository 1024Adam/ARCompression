/* ExitListener.java */
package arcompression;

import java.awt.event.*;

/*
 * Adam Reid
 * December 7, 2015
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
