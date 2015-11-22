import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

/*
 * Adam Reid
 * November 22, 2015
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
        this.actionButton.setText("<html><b>Compress</b></html>");
        this.actionButton.setSelected(true);	
        this.listenButton.setText("Decompress");
        this.listenButton.setSelected(false);

        this.submit.setText("<html><b>Compress File</b></html>");
    }
}
