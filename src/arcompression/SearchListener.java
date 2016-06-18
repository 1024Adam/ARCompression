/* SearchListener.java */
package arcompression;

import java.awt.event.*;
import java.io.File;

import javax.swing.*;
import javax.swing.filechooser.FileFilter;

/*
 * Adam Reid
 * June 18, 2016
 */

public class SearchListener implements ActionListener 
{
    private JTextField file;
    private JPanel mainPanel;
    
    //private native void compressFile();
    //private native void decompressFile();
    //static { System.loadLibrary("javahuffman"); }
    
    /* Constructors */
    public SearchListener(JTextField file, JPanel mainPanel)
    {
        this.file = file;
        this.mainPanel = mainPanel;
    }
	
    @Override
    public void actionPerformed(ActionEvent e) 
    {
        JFileChooser fc = new JFileChooser();
        int returnVal = fc.showOpenDialog(this.mainPanel);
        if(returnVal == JFileChooser.APPROVE_OPTION)
        {
            File fileChosen = fc.getSelectedFile();
            file.setText(fileChosen.getAbsolutePath());
        }
    }
}
