import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;


public class Sha {//lee el encrypt y escribe en shash
	
    static void hashSha(String fileName,String fileName3) throws NoSuchAlgorithmException, IOException {
        MessageDigest digest = MessageDigest.getInstance("SHA-256");
        byte[] hash = digest.digest(Files.readAllBytes(Paths.get(fileName)));
		Files.write(Paths.get(fileName3),hash);
    }    

}
