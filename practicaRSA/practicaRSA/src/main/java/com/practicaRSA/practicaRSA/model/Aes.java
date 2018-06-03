package com.practicaRSA.practicaRSA.model;
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

import org.apache.tomcat.jni.File;
import org.apache.tomcat.util.codec.binary.Base64;

public class Aes {

	private String message;
	private String puk;
	private String sha;
	private String aes;
	private String rsa;
	
	public String getRsa() {
		return rsa;
	}

	public void setRsa(String rsa) {
		this.rsa = rsa;
	}

	public String getSha() {
		return sha;
	}

	public void setSha(String sha) {
		this.sha = sha;
	}

	public String getAes() {
		return aes;
	}

	public void setAes(String aes) {
		this.aes = aes;
	}
	
	public String getPuk() {
		return puk;
	}

	public void setPuk(String puk) {
		this.puk = puk;
	}

	public String getMessage() {
		return this.message;
	}
	
	public void setMessage(String message) {
		this.message = message;
	}
	
	public Aes(String message, String puk) {
		this.message = message;
		this.puk = puk;
	}
	
	public Aes() {
	}
	/*
	public static byte[] encryptAes(String mensaje) throws NoSuchAlgorithmException, NoSuchPaddingException, InvalidKeyException, IllegalBlockSizeException, BadPaddingException{
        byte[] encoded = "AsegurarAsegurar".getBytes();
        SecretKey secKey = new SecretKeySpec(encoded, "AES");        
        
        Cipher aesCipher = Cipher.getInstance("AES");
        byte[] byteText = mensaje.getBytes();
        
        aesCipher.init(Cipher.ENCRYPT_MODE, secKey);
        byte[] byteCipherText = aesCipher.doFinal(byteText);
        return byteCipherText;
	}
	
	public static byte[] decryptAes(String mensaje) throws NoSuchAlgorithmException, NoSuchPaddingException, InvalidKeyException, IllegalBlockSizeException, BadPaddingException {
        byte[] encoded = "AsegurarAsegurar".getBytes();
        SecretKey secKey = new SecretKeySpec(encoded, "AES");		
        Cipher aesCipher = Cipher.getInstance("AES");
		byte[] cipherText = Base64.decodeBase64(mensaje);
        aesCipher.init(Cipher.DECRYPT_MODE, secKey);
        byte[] bytePlainText = aesCipher.doFinal(cipherText);
        return bytePlainText;
	}
	*/
	public static void encryptAes(String mensaje, String fileName) throws NoSuchAlgorithmException, NoSuchPaddingException, InvalidKeyException, IllegalBlockSizeException, BadPaddingException, IOException {
        //byte[] encoded = "AsegurarAsegurar".getBytes();
		byte[] encoded =  "AsegurarAsegurar".getBytes();
        SecretKey secKey = new SecretKeySpec(encoded, "AES");        
        
        Cipher aesCipher = Cipher.getInstance("AES");
        byte[] byteText = Files.readAllBytes(Paths.get(mensaje));
        
        aesCipher.init(Cipher.ENCRYPT_MODE, secKey);
        byte[] byteCipherText = aesCipher.doFinal(byteText);
        Files.write(Paths.get(fileName), byteCipherText);
	}
	
	public static void decryptAes(String fileName2, String fileName1) throws NoSuchAlgorithmException, NoSuchPaddingException, IOException, InvalidKeyException, IllegalBlockSizeException, BadPaddingException {
        byte[] encoded = "AsegurarAsegurar".getBytes();
        SecretKey secKey = new SecretKeySpec(encoded, "AES");		
		
        Cipher aesCipher = Cipher.getInstance("AES");
		byte[] cipherText = Files.readAllBytes(Paths.get(fileName1));
        aesCipher.init(Cipher.DECRYPT_MODE, secKey);
        byte[] bytePlainText = aesCipher.doFinal(cipherText);
        Files.write(Paths.get(fileName2),bytePlainText);		
	}
}
