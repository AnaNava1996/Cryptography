import java.io.*;

public class ReadBytes {

	private String arch;

	public String getArch() {
		return arch;
	}

	public void setArch(String arch) {
		this.arch = arch;
	}
	
	public ReadBytes(String arch) {
		this.arch=arch;
	}
	
	public void LeerBytes(String arch) {
		try {
	        // Use this for reading the data.
	        byte[] buffer = new byte[1000];
	
	        FileInputStream inputStream = 
	            new FileInputStream(arch);
	        // read fills buffer with data and returns
	        // the number of bytes read (which of course
	        // may be less than the buffer size, but
	        // it will never be more).
	        int total = 0;
	        int nRead = 0;
	        while((nRead = inputStream.read(buffer)) != -1) {
	            // Convert to String so we can display it.
	            // Of course you wouldn't want to do this with
	            // a 'real' binary file.
	            //System.out.println(new String(buffer));
	            System.out.println(new String(buffer));
	            total += nRead;
	        }   
	        // Always close files.
	        inputStream.close();        
	
	        System.out.println("Read " + total + " bytes");
	    }
	    catch(FileNotFoundException ex) {
	        System.out.println(
	            "Unable to open file '" + 
	            arch + "'");                
	    }
	    catch(IOException ex1) {
	        System.out.println(
	            "Error reading file '" 
	            + arch + "'");                  
	        // Or we could just do this: 
	        // ex.printStackTrace();
	    }     
	        
	}    
        
}
