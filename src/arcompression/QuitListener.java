/* QuitListener.java */
package arcompression;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/*
 * Adam Reid
 * December 7, 2015
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
