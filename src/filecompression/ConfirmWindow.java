package filecompression;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/*
 * Adam Reid
 * November 26, 2015
 */

public class ConfirmWindow extends JFrame
{
    private static final long serialVersionUID = 1L;

    public ConfirmWindow()
    {
        setSize(210, 100);
        setTitle("Quit?");
        setLayout(new BorderLayout());
        
        JLabel confirmLabel = new JLabel("  Are you sure you want to quit?");
        add(confirmLabel, BorderLayout.CENTER);
        
        /* Add panel contents */
        JPanel confirmPanel = new JPanel();
        confirmPanel.setLayout(new FlowLayout());
        
        JButton yes = new JButton("Quit");
        yes.addActionListener(new QuitListener()); /* Quit when clicked */
        
        JButton no = new JButton("Cancel");
        no.addActionListener(new CancelListener()); /* Close window when clicked */
        
        confirmPanel.add(yes);
        confirmPanel.add(no);
        
        add(confirmPanel, BorderLayout.SOUTH);
    }
    
    /** Quit when clicked, listener */
    private class QuitListener implements ActionListener
    {
        @Override
        public void actionPerformed(ActionEvent e)
        {
            System.exit(0);
        }
    }
    
    /** Close window when clicked, listener */
    private class CancelListener implements ActionListener
    {
        @Override
        public void actionPerformed(ActionEvent e)
        {
            dispose();
        }
    }
}
