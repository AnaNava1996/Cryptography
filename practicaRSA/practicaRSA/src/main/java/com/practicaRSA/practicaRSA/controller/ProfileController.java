package com.practicaRSA.practicaRSA.controller;

import java.nio.file.Files;
import java.nio.file.Paths;
import java.security.KeyFactory;
import java.security.KeyPair;
import java.security.KeyPairGenerator;
import java.security.NoSuchAlgorithmException;
import java.security.PrivateKey;
import java.security.PublicKey;
import java.security.spec.InvalidKeySpecException;
import java.security.spec.X509EncodedKeySpec;
import java.util.Arrays;
import java.util.Base64;

import javax.crypto.Cipher;

import org.springframework.http.HttpMethod;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.servlet.ModelAndView;

import com.practicaRSA.practicaRSA.model.Aes;
import com.practicaRSA.practicaRSA.model.Sha;

@Controller
@RequestMapping("/perfil")
public class ProfileController {
	
	public String puk;
	public PrivateKey prk;
	public PublicKey pbk;
	public byte[] AESencrypted;
	public byte[] AESdecrypted;
	public byte[] Shaenc;
	public byte[] Shadec;
	public byte[] RSAenc;
	public byte[] RSAdec;
	
	public String fileName = "D:/Users/ana_n/Documents/IPN n.n/6to Semestre/Cryptography/Perfil/normal.txt";
	public String fileName1 = "D:/Users/ana_n/Documents/IPN n.n/6to Semestre/Cryptography/Perfil/encryptedAES.txt";
    public String fileName2 = "D:/Users/ana_n/Documents/IPN n.n/6to Semestre/Cryptography/Perfil/decryptedAES.txt";
    public String fileName3 = "D:/Users/ana_n/Documents/IPN n.n/6to Semestre/Cryptography/Perfil/shash.txt";
    public String fileName4 = "D:/Users/ana_n/Documents/IPN n.n/6to Semestre/Cryptography/Perfil/RSAencrypt.txt";
    public String fileName5 = "D:/Users/ana_n/Documents/IPN n.n/6to Semestre/Cryptography/Perfil/RSAdecrypt.txt";
	public String fileName6 = "D:/Users/ana_n/Documents/IPN n.n/6to Semestre/Cryptography/Perfil/shabob.txt";
	public ProfileController() throws NoSuchAlgorithmException {
		KeyPair keyPair = buildKeyPair();
        pbk = keyPair.getPublic();
        prk = keyPair.getPrivate();
        byte [] keybyte = pbk.getEncoded();
        this.puk = Base64.getEncoder().encodeToString(keybyte);
        this.AESdecrypted = this.AESencrypted = this.Shadec = this.Shaenc = "".getBytes();
	}

	public String getPuk() { return puk; }
	public void setPuk(String puk) { this.puk = puk; }
	public PrivateKey getPrk() { return prk; }
	public void setPrk(PrivateKey prk) { this.prk = prk; }

	@GetMapping("/ana")
	public String showAnaProfile(Model model) {
		model.addAttribute("aes", new Aes());
		return "ANA";
	}
	
	@GetMapping("/bobito")
	public ModelAndView adAes(@ModelAttribute("aes") Aes aes) throws Exception {
		ModelAndView mav = new ModelAndView("BOB");
		mav.addObject("aes", aes);
		
		byte [] RSAdecrypted = RSAdecrypt(this.prk,Files.readAllBytes(Paths.get(fileName4)));
        Files.write(Paths.get(fileName5),RSAdecrypted);
        
        Aes.decryptAes(fileName2, fileName1);//se descifra la parte del AES
        Sha.hashSha(fileName2,fileName6);//se le hace SHA al decrypt de AES
        aes.setAes(Files.readAllBytes(Paths.get(fileName2)).toString());
		aes.setRsa(Files.readAllBytes(Paths.get(fileName5)).toString());//rsa decrypt
		aes.setSha(Files.readAllBytes(Paths.get(fileName6)).toString());//shabob
		
		/*int len=0;
		while(RSAdecrypted[i]!='\0') {
			len++;
		}
		
		for()*/
		
		if(Arrays.equals(
				Files.readAllBytes(Paths.get(fileName5)),
				Files.readAllBytes(Paths.get(fileName6)))) {

			aes.setMessage(Files.readAllLines(Paths.get(fileName2)).get(0).toString());
		
		}
		if(Files.readAllBytes(Paths.get(fileName5)).equals(Files.readAllBytes(Paths.get(fileName6)))) {
			System.out.println("OOOKKK");
		}
		else {
			System.out.println("NOOOOO");
		}
		
		return mav;
	}
	/*
	public String showBobProfile(Model model) {
		model.addAttribute("aes", new Aes("",this.getPuk()));
		return "BOB";
	}*/
	
	@PostMapping("/postanita")
	public ModelAndView addAes(@ModelAttribute("aes") Aes aes) throws Exception {
		ModelAndView mav = new ModelAndView("CHACHAN");
		mav.addObject("aes", aes);
		Files.write(Paths.get(fileName), aes.getMessage().getBytes());
		//Se SHAshea el mensaje
		Sha.hashSha(fileName,fileName3);
		//Se RSAsea el SHA
		byte [] RSAencrypted = RSAencrypt(this.pbk,Files.readAllBytes(Paths.get(fileName3)));
        Files.write(Paths.get(fileName4),RSAencrypted);
		//Se AESea el mensaje
		Aes.encryptAes(fileName,fileName1);
		
		aes.setAes( Base64.getEncoder().encodeToString(Files.readAllBytes(Paths.get(fileName))) );
		aes.setSha( Base64.getEncoder().encodeToString(Files.readAllBytes(Paths.get(fileName3))) );
		aes.setRsa( Base64.getEncoder().encodeToString(Files.readAllBytes(Paths.get(fileName4))) );
		
		return mav;		
	}
	
	@RequestMapping(value="/bobitokey", method=RequestMethod.GET)
	@ResponseBody
	public String foo() {
	    return this.getPuk();
	}
	
	public static KeyPair buildKeyPair() throws NoSuchAlgorithmException {
        final int keySize = 2048;
        KeyPairGenerator keyPairGenerator = KeyPairGenerator.getInstance("RSA");
        keyPairGenerator.initialize(keySize);      
        return keyPairGenerator.genKeyPair();
    }
	
	public static byte[] RSAencrypt(PublicKey publicKey,byte[] message) throws Exception {
        Cipher cipher = Cipher.getInstance("RSA");  
        cipher.init(Cipher.ENCRYPT_MODE, publicKey);  

        return cipher.doFinal(message);  
    }
    
    public static byte[] RSAdecrypt(PrivateKey privateKey, byte [] RSAencrypted) throws Exception {
        Cipher cipher = Cipher.getInstance("RSA");  
        cipher.init(Cipher.DECRYPT_MODE, privateKey);
        
        return cipher.doFinal(RSAencrypted);
    }	
}
	
//}//
