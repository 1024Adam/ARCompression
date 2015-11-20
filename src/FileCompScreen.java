import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import java.awt.event.*;
import java.awt.*;
import java.io.*;
import java.util.*;

/*
 * Adam Reid
 * November 19, 2015
 */


public class FileCompScreen extends JFrame
{
	private static final long serialVersionUID = 1L;

	public static final int WIDTH = 600;
    public static final int HEIGHT = 500;
    
    private static JPanel mainPanel = new JPanel();
    private static JPanel contentsPanel = new JPanel();
    private static JPanel compPanel = new JPanel();
    private static JPanel decompPanel = new JPanel();
	
	public FileCompScreen()
	{
		super();
		setSize(WIDTH, HEIGHT);
		setTitle("File Compressor");
	
		setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        //addWindowListener(); // need to add a WindowListener
		
		// Create Menu Bar 
		JMenuBar bar = new JMenuBar();
		JMenu file = new JMenu("File");
		
		JMenuItem quit = new JMenuItem("Quit");
		//quit.addActionListener(new QuitListener());
		file.add(quit);
		bar.add(file);
		
		setJMenuBar(bar);
		
		// Setup main panel
		mainPanel.setBackground(Color.WHITE);
		mainPanel.setLayout(new BorderLayout());
		
		JToggleButton toggle = new JToggleButton("Compress", false);
		toggle.addChangeListener(new ChangeListener()
		{
			@Override
			public void stateChanged(ChangeEvent event) 
			{
				if (!toggle.isSelected())
				{
					toggle.setText("Compress");
				} 
				else 
				{
					toggle.setText("Decompress");
				}
	        }
		});
		mainPanel.add(toggle, BorderLayout.NORTH);
		
		// Setup contents panel
		contentsPanel.setBackground(Color.WHITE);
		contentsPanel.setLayout(new BoxLayout(getContentPane(), BoxLayout.X_AXIS));
		
		
		
		add(mainPanel);
		
		
	}
}
