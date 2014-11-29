import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintStream;

import lejos.hardware.Button;

public class DataLogging {

	private final static int dataLength= 5;
	private final static int nrOfMeasurement = 300;

    private static int [][] databuffer = new int[nrOfMeasurement][dataLength];
    private static int dataIndex = 0;
    private static int pCorr = 0;
    private static int iCorr = 0;
    private static int dCorr = 0;

    private static boolean dataWraparound = false;
   
    public static void addSetting(int p, int i, int d)
    {
    	pCorr = p;
    	iCorr = i;
    	dCorr = d;
    }
    
    public static void addData(int[] data)
    {
    	for(int i=0;i<dataLength; i++)
    		databuffer[dataIndex][i] = data[i];
    	
    	if(dataIndex < nrOfMeasurement-1)
    	{
        	dataIndex++;    		
    	}
    	else
    	{
        	dataIndex = 0;
        	dataWraparound = true;
    	}
    }
        
    public static void printLog()
    {
    	if(dataWraparound) {
        	for(int measureNr = dataIndex; measureNr < nrOfMeasurement; measureNr++)
        	{
        		String output = dataToString(databuffer[measureNr]);
                System.out.println(output);    		
        	}    		
    	}
    	for(int measureNr = 0; measureNr < dataIndex; measureNr++)
    	{
    		String output = dataToString(databuffer[measureNr]);
            System.out.println(output);    		
    	}
    	dataIndex = 0;
    	dataWraparound = false;
    }
    
    public static void WriteLogToFile(String filename)
    {    	
    	final PrintStream dataStream;

        try {
        	File dataFile = new File(filename);
        	FileOutputStream out = new FileOutputStream(dataFile);
            dataStream = new PrintStream(out);
            dataStream.println("Angle,Angle rate,Position,Speed,Calc time, P corr, I corr, D corr");
            dataStream.println(" , , , , , " + pCorr + "," + iCorr + "," + dCorr);
            if(dataWraparound) {
            	for(int measureNr = dataIndex; measureNr < nrOfMeasurement; measureNr++)
            	{
            		String output = dataToString(databuffer[measureNr]);
                    dataStream.println(output);    		
            	}    		
        	}
        	for(int measureNr = 0; measureNr < dataIndex; measureNr++)
        	{
        		String output = dataToString(databuffer[measureNr]);
                dataStream.println(output);    		
        	}
        	dataIndex = 0;
        	dataWraparound = false;
        	
        	out.close(); // flush the buffer and write the file
        } catch(IOException e) {
            System.err.println("Failed to create write datafile");
            Button.waitForAnyPress();
            System.exit(1);
         }
    }
    
    private static String dataToString(int[] measureData)
    {
    	String dataStr = "";
    	for(int i=0; i<dataLength; i++)
    	{
    		dataStr += measureData[i] + ",";
    	}
    	return dataStr;
    }
}