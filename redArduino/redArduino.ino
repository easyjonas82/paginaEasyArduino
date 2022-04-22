#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0xFA,0x12,0x46,0x56,0x19,0x32};
EthernetServer servidor = EthernetServer(80);



void setup() {
  Serial.begin(9600);
  if(Ethernet.begin(mac) == 1){
    Serial.println("DHCP exitoso");
    Serial.println(Ethernet.localIP());
    }else{
      Serial.println("Fallo en DHCP");
      }
      servidor.begin();
      pinMode(8,OUTPUT);
}

void loop() {
  EthernetClient cliente = servidor.available();
  if(cliente.connected()){
    String dato="";
    if(cliente.available()>20){
      for(int i=0; i<20; i++){
        char c = cliente.read();
        dato = dato+c;
        }
      
      }   
    
    Serial.print(dato);
        if(dato.indexOf("ledOn")>0){
        digitalWrite(8,HIGH);
        delay(2000);
        digitalWrite(8,LOW);
        }else if(dato.indexOf("ledOff")>0){
          digitalWrite(8,LOW);
          }
    cliente.println("HTTP/1.1 200 ok");
    cliente.println("Content-Type: text/html");
    cliente.println("Connetion: close");
    //cliente.println("Refresh: 5");
    cliente.println("");
    cliente.println("<!DOCTYPE HTML>");
    cliente.println("<title>Entrada Sears</title>");
    cliente.println("<body>");

    
    
    cliente.println("<style>.titulo{background-color: rgb(0, 77, 128); margin-bottom: 0px; margin-top: 200px; margin-left: 500px; height: 60px; width: 600px; font-size: 60px; text-align: right;} .color{color: white;} .menu{font-size: 20px; text-align: center; background-color: aqua; width: 600px; margin-left: 500px; margin-top: 0; height: 200px; display: flex; flex-direction: column; justify-content: center;} .menu a{text-decoration: none; } </style>");
    
    cliente.println("<header>");
    cliente.println("<h1 class=\"titulo color\">Sears 1</h1>");
    
    //cliente.println("<img url=\"https://www.google.com/imgres?imgurl=https%3A%2F%2Fsp-ao.shortpixel.ai%2Fclient%2Fq_glossy%2Cret_img%2Cw_200%2Ch_121%2Fhttps%3A%2F%2Feasypaypark.com%2Fwp-content%2Fuploads%2F2017%2F07%2FSmallLogo-e1500354200904.png&imgrefurl=https%3A%2F%2Feasypaypark.com%2F&tbnid=6W2RhZ2p5EsACM&vet=12ahUKEwir9uyV4Kb3AhWsj2oFHQrbDDQQMygAegQIARAd..i&docid=UCciNCTJT0AYmM&w=200&h=121&q=easypaypark%20logo%20easy&ved=2ahUKEwir9uyV4Kb3AhWsj2oFHQrbDDQQMygAegQIARAd\" alt="">");
    //cliente.println("<header>");
    
    cliente.println("</header>");
    
    cliente.println("<nav class=\"menu\">");
    cliente.println("<a href=\"ledOn\" >Abrir Barrera</a>");
    //cliente.println("<a href=\"ledOff\" >Apagar</a>");
    cliente.println("</nav>");
    cliente.println("</body>");
    
    cliente.stop();   
    
  }
    
     
    
    }
  
