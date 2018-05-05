function cifdes() {
    var cifrar = document.getElementById("cifrado");
    var descifrar = document.getElementById("descifrado");
    var selcif = cifrar.options[cifrar.selectedIndex];
    var seldes = descifrar.options[descifrar.selectedIndex];
    //alert(selcif.value+"  "+seldes.value);
    var xhttp = new XMLHttpRequest();

    xhttp.onreadystatechange = function() {
	if (this.readyState == 4 && this.status == 200) {
	    if(this.responseText=="success") {
		document.getElementById("cifrado_img").setAttribute("src", "static/encrypt.bmp");
		document.getElementById("descifrado_img").setAttribute("src", "static/decrypt.bmp");
	    }
	}
    }
    xhttp.open("POST", "/cripto", true);
    xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    xhttp.send("cif="+selcif.value+"&des="+seldes.value);
}

document.addEventListener("DOMContentLoaded", function() {});
