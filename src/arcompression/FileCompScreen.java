/* FileCompScreen.java */
package arcompression;

import javax.swing.*;
import java.awt.*;

/*
 * Adam Reid
 * February 13, 2016
 */

public class FileCompScreen extends JFrame
{
    private static final long serialVersionUID = 1L;

    public static final int WIDTH = 300;
    public static final int HEIGHT = 225;

    /* Constructors */
    public FileCompScreen()
    {
        /* Set basic window settings */
        super();
        setSize(WIDTH, HEIGHT);
        setTitle("ARCompression");

        setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        addWindowListener(new ExitListener());
        
        JPanel totalPanel = new JPanel();
        JPanel mainPanel = new JPanel();
        JPanel contentsPanel = new JPanel();
        JPanel submitPanel = new JPanel();
        
        // Create Menu Bar 
        JMenuBar bar = new JMenuBar();
        JMenu file = new JMenu("File");

        JMenuItem quit = new JMenuItem("Quit");
        quit.addActionListener(new QuitListener()); 
        file.add(quit);
        bar.add(file);
        setJMenuBar(bar);

        // Setup total panel
        totalPanel.setBackground(Color.WHITE);
        totalPanel.setLayout(new BorderLayout());
        
        // Setup main panel
        mainPanel.setBackground(Color.WHITE);
        mainPanel.setLayout(new BorderLayout());

        JButton compress = new JButton("<html><b>Compress</b></html>");
        compress.setSelected(true);

        JButton decompress = new JButton("Decompress");
        decompress.setSelected(false);
        /** TODO: Enable decompression button when decompress feature becomes available **/
        decompress.setEnabled(false);
        
        // Submit button; will be used for the submit panel further down
        JButton submit = new JButton("<html><b>Compress File</b></html>");
        
        compress.addActionListener(new CompressListener(compress, decompress, submit));
        decompress.addActionListener(new CompressListener(decompress, compress, submit));
                
        // Setup top panel
        JPanel topPanel = new JPanel();
        topPanel.setBackground(Color.WHITE);
        topPanel.setLayout(new FlowLayout(FlowLayout.LEFT));
        topPanel.add(compress);
        topPanel.add(decompress);
        mainPanel.add(topPanel, BorderLayout.NORTH);
        
        mainPanel.add(new JSeparator(JSeparator.HORIZONTAL), BorderLayout.CENTER);

        // Setup contents panel
        contentsPanel.setBackground(Color.WHITE);
        contentsPanel.setLayout(new FlowLayout(FlowLayout.LEFT));

        JPanel centerPanel = new JPanel();
        centerPanel.setLayout(new BorderLayout());
        centerPanel.setBackground(Color.WHITE);
        JButton searchButton = new JButton("Browse...");
        centerPanel.add(searchButton, BorderLayout.WEST);

        JTextField fileField = new JTextField(13);
        centerPanel.add(fileField, BorderLayout.CENTER); 
        
        contentsPanel.add(centerPanel);

        mainPanel.add(contentsPanel, BorderLayout.SOUTH);
        totalPanel.add(mainPanel, BorderLayout.NORTH);
        
        // Setup submit panel
        submitPanel.setBackground(Color.WHITE);
        submitPanel.setLayout(new BorderLayout());
        
        JPanel southPanel1 = new JPanel();
        southPanel1.setBackground(Color.WHITE);
        southPanel1.setLayout(new FlowLayout(FlowLayout.LEFT));
        
        JTextArea statusArea = new JTextArea();
        statusArea.setLineWrap(true);
        statusArea.setEditable(false);
        JScrollPane scrollPane = new JScrollPane(statusArea);
        scrollPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
        scrollPane.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
        scrollPane.setPreferredSize(new Dimension(270, 36));
        southPanel1.add(scrollPane);
        
        JPanel southPanel2 = new JPanel();
        southPanel2.setBackground(Color.WHITE);
        southPanel2.setLayout(new FlowLayout(FlowLayout.LEFT));
        
        submit.addActionListener(new SubmitListener(statusArea, submit));
        southPanel2.add(submit);
        
        submitPanel.add(southPanel1, BorderLayout.NORTH);
        submitPanel.add(southPanel2, BorderLayout.SOUTH);

        totalPanel.add(submitPanel, BorderLayout.SOUTH);
        
        add(totalPanel);
    }
}
