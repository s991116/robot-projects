public class DataLogging {

	private final static int dataLength= 5;
	private final static int nrOfMeasurement = 300;

    private static int [][] databuffer = new int[nrOfMeasurement][dataLength];
    private static int dataIndex = 0;
    private static boolean dataWraparound = false;
   
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