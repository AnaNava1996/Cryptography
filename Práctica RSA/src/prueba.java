import java.nio.file.Files;
import java.nio.file.Paths;
import java.security.KeyPair;
import java.security.KeyPairGenerator;
import java.security.NoSuchAlgorithmException;
import java.security.PrivateKey;
import java.security.PublicKey;

import javax.crypto.Cipher;

public class prueba {
	
	
	public static void main(String[] args)throws Exception {

        String fileName = "D:/Users/ana_n/Documents/IPN n.n/6to Semestre/Cryptography/Perfil/encryptedAES.txt";
        String fileName2 = "D:/Users/ana_n/Documents/IPN n.n/6to Semestre/Cryptography/Perfil/decryptedAES.txt";
        String fileName3 = "D:/Users/ana_n/Documents/IPN n.n/6to Semestre/Cryptography/Perfil/shash.txt";
        String fileName4 = "D:/Users/ana_n/Documents/IPN n.n/6to Semestre/Cryptography/Perfil/RSAencrypt.txt";
        String fileName5 = "D:/Users/ana_n/Documents/IPN n.n/6to Semestre/Cryptography/Perfil/RSAdecrypt.txt";
        String mensaje = "Cosita hermoxita";
             
        Aes.encryptAes(mensaje, fileName);
        Aes.decryptAes(fileName2, fileName);
	
        Sha.hashSha(fileName,fileName3);

        // generate public and private keys
        KeyPair keyPair = buildKeyPair();
        PublicKey pubKey = keyPair.getPublic();
        PrivateKey privateKey = keyPair.getPrivate();
        
        // encrypt the message
        byte [] RSAencrypted = RSAencrypt(privateKey,Files.readAllBytes(Paths.get(fileName3)));//encrypt(privateKey, "This is a secret message");     
        Files.write(Paths.get(fileName4),RSAencrypted);//System.out.println(new String(encrypted));  // <<encrypted message>>
        
        // decrypt the message
        byte[] RSAdecrypted = RSAdecrypt(pubKey, RSAencrypted);                                 
        Files.write(Paths.get(fileName5),RSAdecrypted);//System.out.println(new String(RSAdecrypted));     // This is a secret message        
		
	}
	

    public static KeyPair buildKeyPair() throws NoSuchAlgorithmException {
        final int keySize = 2048;
        KeyPairGenerator keyPairGenerator = KeyPairGenerator.getInstance("RSA");
        keyPairGenerator.initialize(keySize);      
        return keyPairGenerator.genKeyPair();
    }

    public static byte[] RSAencrypt(PrivateKey privateKey,byte[] message) throws Exception {
        Cipher cipher = Cipher.getInstance("RSA");  
        cipher.init(Cipher.ENCRYPT_MODE, privateKey);  

        return cipher.doFinal(message);  
    }
    
    public static byte[] RSAdecrypt(PublicKey publicKey, byte [] RSAencrypted) throws Exception {
        Cipher cipher = Cipher.getInstance("RSA");  
        cipher.init(Cipher.DECRYPT_MODE, publicKey);
        
        return cipher.doFinal(RSAencrypted);
    }	
	
	
	
}
