#include <SPI.h>
#include <Ethernet.h>
int led1 = 5;
int led2 = 4;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };   //physical mac address
byte ip[] = { 192, 168, 2, 110 };                      // ip in lan (that's what you need to use in your browser. ("192.168.1.178")
byte gateway[] = { 192, 168, 2, 254 };                   // internet access via router
byte subnet[] = { 255, 255, 255, 0 };                  //subnet mask
EthernetServer server(80);                             //server port     
String readString;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {   
      if (client.available()) {
        char c = client.read();
        //read char by char HTTP request
        if (readString.length() < 100) {
          //store characters to string
          readString += c;
          //Serial.print(c);
         }
         //if HTTP request has ended
         if (c == '\n') {          
           Serial.println(readString); //print to serial monitor for debuging
           client.println("HTTP/1.1 200 OK"); //send new page
           client.println("Content-Type: text/html");
           client.println();     
           client.println("<html>");
           client.println("<head>");
           //client.println("<link rel='stylesheet' type='text/css' href='http://randomnerdtutorials.com/ethernetcss.css' />");
           client.println("<title>Belajar Arduino</title>");
		   client.println("<meta charset='utf-8'/>");
           client.println("<meta name='viewport' content='width=device-width, initial-scale=1.0'>");
           client.println("</head>");
           client.println("<body style=\"background-color:#7CFC00\" align=\"center\">");
           client.println("<h2>Arduino with Ethernet Shield</h2>");
           client.println("<h4>Remote Monitor</h4>");
           client.println("<br />");
           client.println("<a href=\"/?button1on\"\">On LED1</a>");
           client.println("<a href=\"/?button1off\"\">Off LED1</a><br />");   
           client.println("<br />");
           client.println("<a href=\"/?button2on\"\">On LED2</a>");
           client.println("<a href=\"/?button2off\"\">Off LED2</a><br />"); 
           client.println("<p>Created by Ardian</p>");  
           client.println("<br />"); 
           client.println("</body></html>");
           delay(1);
           //stopping client
           client.stop();
           //controls the Arduino if you press the buttons
           if (readString.indexOf("?button1on") >0){
               digitalWrite(led1, HIGH);
           }
           if (readString.indexOf("?button1off") >0){
               digitalWrite(led1, LOW);
           }
           if (readString.indexOf("?button2on") >0){
               digitalWrite(led2, HIGH);
           }
           if (readString.indexOf("?button2off") >0){
               digitalWrite(led2, LOW);
           }
           readString="";  
         }
       }
    }
}
}