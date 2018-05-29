import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;

import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.SecretKey;
import javax.crypto.spec.SecretKeySpec;

public class Aes {

	
	public static void encryptAes(String mensaje, String fileName) throws NoSuchAlgorithmException, NoSuchPaddingException, InvalidKeyException, IllegalBlockSizeException, BadPaddingException, IOException {
        byte[] encoded = "AsegurarAsegurar".getBytes();
        SecretKey secKey = new SecretKeySpec(encoded, "AES");        
        
        Cipher aesCipher = Cipher.getInstance("AES");
        byte[] byteText = mensaje.getBytes();
        
        aesCipher.init(Cipher.ENCRYPT_MODE, secKey);
        byte[] byteCipherText = aesCipher.doFinal(byteText);
        Files.write(Paths.get(fileName), byteCipherText);
	}
	
	public static void decryptAes(String fileName2, String fileName) throws NoSuchAlgorithmException, NoSuchPaddingException, IOException, InvalidKeyException, IllegalBlockSizeException, BadPaddingException {
        byte[] encoded = "AsegurarAsegurar".getBytes();
        SecretKey secKey = new SecretKeySpec(encoded, "AES");		
		
        Cipher aesCipher = Cipher.getInstance("AES");
		byte[] cipherText = Files.readAllBytes(Paths.get(fileName));
        aesCipher.init(Cipher.DECRYPT_MODE, secKey);
        byte[] bytePlainText = aesCipher.doFinal(cipherText);
        Files.write(Paths.get(fileName2),bytePlainText);		
	}
	
}
