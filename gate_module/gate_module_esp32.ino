// sent to grp version
#include <WiFi.h>
#include <HardwareSerial.h>
#include <ESP32Servo.h>

WiFiClient client;
WiFiServer server(80);
Servo MyServo;

static const int servoPin = 18;             /*Connect the servo motor to GPIO18 */

const char* ssid = "motorola edge 30_5525";  
// const char* pass="12345678";       /*Enter Your SSID*//*Enter Your Password*/

String _readString, AngleVlue;

void html_page(){
client.println("HTTP/1.1 200 OK");
client.println("Content-type:text/html");
client.println("Connection: close");
client.println();

client.println("<!DOCTYPE html>");
client.println("<html>");
client.println("<head>");
client.println("<title>Password UPDATE</title>");
client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
client.println("<link rel=\"ico\" href=\"data:,\">");
client.println("<style>");
//client.println("body {text-align:center;font-family:\"Roboto\";margin-left:auto;margin-right:auto;}");
//client.println(".slidecontainer {width: 400px; margin:0 auto;}");
//client.println(".slider {");
//  client.println("-webkit-appearance: none;  width: 100%;  height: 25px; background: #d3d3d3;  outline: none;  ");
//  client.println("opacity: 0.7;  -webkit-transition: .2s;  transition: opacity .2s;}");

//client.println(".slider:hover { opacity: 1;}");

//client.println(".slider::-webkit-slider-thumb {");
//   client.println("-webkit-appearance: none;  appearance: none;  width: 25px; height: 25px;  background: #04AA6D;  cursor: pointer;}");

// client.println(".slider::-moz-range-thumb {");
//   client.println("width: 25px;  height: 25px; background: #04AA6D;  cursor: pointer;}");
client.println("</style>");

client.println("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script>");
client.println("</head>");
client.println("<body style=\"background-color: #2e4053; font-family: Cambria, Cochin, Georgia, Times, 'Times New Roman', serif, sans-serif; margin: 0; padding: 0; display: flex; flex-direction: column; justify-content: space-between; align-items: center; height: 80vh;\">");
client.println("<div style=\"height: 3%;\"></div>");
client.println("<div style=\"background-color: #fcfcfc; text-align: center; padding: 10px; border-radius: 10px; display: inline-block; height: 70%; width: 40%; box-sizing: border-box;\">");
client.println("<h1 style=\"color: #ec983e; font-size: 36px;\">Update Password</h1>");
client.println("<h2 style=\"color: #0d2e52; font-size: 24px;\">Please Enter a 4-Digit Password</h2>");
client.println("<input type=\"password\" id=\"password\" name=\"password\" maxlength=\"4\" pattern=\"[0-9]{4}\" title=\"Please enter a 4-digit numeric password\" required style=\"padding: 10px; font-size: 16px; background-color: #f7f7f7; color: #333; border: 2px solid #3498db; border-radius: 5px; margin: 10px 0; width: 100%; box-sizing: border-box;\">");
client.println("<input type=\"button\" value=\"submit\" onclick=getValue() style=\"padding: 10px 20px; font-size: 16px; background-color: #3498db; color: #fff; border: none; border-radius: 5px; cursor: pointer;\">");
client.println("<div id=\"update_response\"></div>");
client.println("</div>");
// client.println("<script>");
// client.println("function getValue()");
// client.println("{");
// client.println("var inputValue=document.getElementById(\"password\").value;");
// client.println("console.log(inputValue);");
// client.println("}");
// client.println("  </script>");
// client.println("");
// client.println("");     
// client.println("<div style=\"height: 1px;\"></div>");
// client.println("</body>");
// client.println("</html>");
client.println("<script>");
  client.println("$.ajaxSetup({timeout:1000});");
  client.println("function getValue(){ ");
  client.println("var inputValue=document.getElementById(\"password\").value;");
      client.println("$.get(\"/@position$\"+inputValue + \"*\");");
      client.println("{Connection: close};");
      client.println("var inputValue=document.getElementById(\"password\").value;");
  client.println("let element = document.createElement(\"h4\");");
  client.println("element.style=\"color:#26fc71;\"");
  client.println("element.innerHTML=\"PINCODE UPDATED SUCCESSFULLY\"");
  client.println("let parent = document.getElementById(\"update_response\"); ");
  client.println("parent.appendChild(element);");
  client.println("event.preventDefault();");
  client.println("}");
client.println("</script></body></html>");

//   client.println("<input type=\"range\" min=\"0\" max=\"180\" value=\"150\" class=\"slider\" id=\"myRange\" onchange=\"servoMotor(this.value)\" value=\"+AngleVlue+\">");
//   client.println("<p>Angle: <span id=\"demo\"></span>&deg</p>");
// client.println("</div>");

// client.println("<script>");
// client.println("var slider = document.getElementById(\"myRange\");");
// client.println("var output = document.getElementById(\"demo\");");
// client.println("output.innerHTML = slider.value;");

// client.println("slider.oninput = function() {slider.value = this.value; output.innerHTML = this.value;}");

//   client.println("$.ajaxSetup({timeout:1000});");

//   client.println("function servoMotor(angle) { ");
//       client.println("$.get(\"/@position$\"+angle + \"*\");");
//       client.println("{Connection: close};");
//   client.println("}");

// client.println("</script></body></html>");
}

void setup() {
  Serial2.begin(9600);
  Serial.begin(115200);             /*Set the baud rate to 115200*/
  MyServo.attach(servoPin);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid);
  while (WiFi.status() != WL_CONNECTED) {/*Wait while connecting to WiFi*/
    delay(100);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());       /*Print the local ip address on the serial window*/
  server.begin();                       /*Start Server*/
}

void loop(){
  client = server.available();
  if (client) {
    Serial.println("New Client Connected"); 
    String currentString = "";   
    while (client.connected()) {
      if (client.available()) { 
        char _readCharacter = client.read();      /*Read the Input data*/
        _readString += _readCharacter;
        if (_readCharacter == '\n') {             /*Read the Input data until newline comein*/
          if (currentString.length() == 0) {
            html_page();                          /*Call the HTML Page Function*/
            if(_readString.indexOf("GET /@position$")>=0) {
              AngleVlue = _readString.substring(_readString.indexOf('$')+1, _readString.indexOf('*'));  /*Parse the data between $ to * */
              // MyServo.write((AngleVlue.toInt())); 
             /*Convert the Updated string value to int and write on servo motor*/
              Serial.print("new pin = ");
              Serial.println(AngleVlue.toInt());  
              Serial2.println(AngleVlue.toInt());        /*Print the Updated Angle in Degree on Serial Monitor*/
            }
            client.println();
            break;                               /*Break the while loop*/
          }
          else {currentString = "";}
        }
        else if (_readCharacter != '\r') {currentString += _readCharacter;}
      }
    }

    _readString = ""; /*clear the string*/
    client.stop();    /*Close the Connection*/
    Serial.println("Client disconnected.");
  }
}
