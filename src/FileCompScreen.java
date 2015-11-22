import javax.swing.*;
import java.awt.*;

/*
 * Adam Reid
 * November 22, 2015
 */

public class FileCompScreen extends JFrame
{
    private static final long serialVersionUID = 1L;

    public static final int WIDTH = 300;
    public static final int HEIGHT = 165;

    public FileCompScreen()
    {
        super();
        setSize(WIDTH, HEIGHT);
        setTitle("File Compressor");

        setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        //addWindowListener(); // need to add a WindowListener

        JPanel totalPanel = new JPanel();
        JPanel mainPanel = new JPanel();
        JPanel contentsPanel = new JPanel();
        JPanel submitPanel = new JPanel();
        
        // Create Menu Bar 
        JMenuBar bar = new JMenuBar();
        JMenu file = new JMenu("File");

        JMenuItem quit = new JMenuItem("Quit");
        //quit.addActionListener(new QuitListener()); // need to add a quit listener
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
        
        // Submit button; will be used for the submit panel further down
        JButton submit = new JButton("<html><b>Compress File</b></html>");
        
        compress.addActionListener(new CompressListener(compress, decompress, submit));
        decompress.addActionListener(new DecompressListener(decompress, compress, submit));
                
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

        JLabel fileLabel = new JLabel("<html><font size = 5>hello</font></html>");
        centerPanel.add(fileLabel, BorderLayout.CENTER); 
        
        contentsPanel.add(centerPanel);

        mainPanel.add(contentsPanel, BorderLayout.SOUTH);
        totalPanel.add(mainPanel, BorderLayout.NORTH);
        
        // Setup submit panel
        submitPanel.setBackground(Color.WHITE);
        submitPanel.setLayout(new FlowLayout(FlowLayout.LEFT));
        
        submitPanel.add(submit);
        
        totalPanel.add(submitPanel, BorderLayout.SOUTH);
        
        add(totalPanel);
    }
}
