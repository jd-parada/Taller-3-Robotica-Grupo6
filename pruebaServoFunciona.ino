#include <ArduinoHardware.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int32.h>
#include <geometry_msgs/Twist.h>
#include <Servo.h>
#include <math.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

int pin1 = 9;
int pin2 = 10;
int pin3 = 11;
int pin4 = 12;

int aumento=10;
int aumentoPinza = 70;

int contadorx = 40;
int contadory = 120;
int contadorz = 40;
int contadorw = 120;

int a1 = 0.081;
int a2 = 0.071; 
double pos_x;
double pos_y;
double pos_z;
int costheta2;
int theta1;
int theta2;      

String caso;
String caso2;

ros::NodeHandle nh;

void messageS( const std_msgs::String& msg) {
  caso2 = msg.data;

}

void messageA( const std_msgs::String& msg) {

  //  aumento= int(msg.data);

}

void messageC(const geometry_msgs::Twist& msg) {
  pos_x = msg.linear.x;
  pos_y = msg.linear.y;
  costheta2 = (1/(2*a1*a2))*((pow(pos_x,2)+pow(pos_y,2))-(pow(a1,2)+pow(a2,2)));
  theta1 = (acos((1/(pos_x*pos_x+pos_y*pos_y))*((pos_x*(a1+a2*costheta2))+(pos_y*a2*sqrt(1-(costheta2*costheta2))))))*(180/3.14);
  theta2 = (acos(1/(2*a1*a2)*((pow(pos_x,2)+pow(pos_y,2))-(pow(a1,2)+pow(a2,2)))))*(180/3.14);

}

void messageCS( const std_msgs::String& msg) {
  caso = msg.data;

}

ros::Subscriber<std_msgs::String> sub("/robot_manipulator_teleop", &messageS );
ros::Subscriber<std_msgs::String> sub2("/angulo", &messageA);
ros::Subscriber<geometry_msgs::Twist> sub3("/robot_manipulator_planner", &messageC );
ros::Subscriber<std_msgs::String> sub4("/robot_manipulator_camara", &messageCS);

geometry_msgs::Twist posicion_brazo;
ros::Publisher Pos_Bra("/turtlebot_position", &posicion_brazo);

void setup() {
  Serial.begin(57600);

  servo1.attach(pin1);
  servo2.attach(pin2);
  servo3.attach(pin3);
  servo4.attach(pin4);

  servo1.write(40);
  servo2.write(120);
  servo3.write(40);
  servo4.write(120);

  nh.initNode();
  nh.subscribe(sub);
  nh.subscribe(sub2);
  nh.subscribe(sub3);
  nh.subscribe(sub4);

  nh.initNode();
  nh.advertise(Pos_Bra);
  posicion_brazo.linear.x=0;
  posicion_brazo.linear.y=0;
  Pos_Bra.publish(&posicion_brazo);
}

void loop() {
  if(caso2 == "u") {
    for(int i=contadorx;i<=contadorx+aumento;i++){
      servo1.write(i);   
    }
    contadorx=contadorx+aumento; 
    posicion_brazo.linear.x=-contadorx;
    Pos_Bra.publish(&posicion_brazo);
    delay(150);
  }
  else if (caso2 == "j") {
    for(int j=contadorx;j>=contadorx-aumento;j--){
      servo1.write(j);   
    }
    contadorx=contadorx-aumento;
    posicion_brazo.linear.x=-contadorx;
    Pos_Bra.publish(&posicion_brazo);
    delay(150);
  }
  else if (caso2 == "i") {
    for(int k=contadory;k<=contadory+aumento;k++){
      servo2.write(k);   
    }
    contadory=contadory+aumento;
    posicion_brazo.linear.y=-contadory;
    Pos_Bra.publish(&posicion_brazo);
    delay(150);
  }
  else if (caso2 == "k") {
    for(int l=contadory;l>=contadory-aumento;l--){
      servo2.write(l);   
    }
    contadory=contadory-aumento;
    posicion_brazo.linear.y=-contadory;
    Pos_Bra.publish(&posicion_brazo);
    delay(150);
  }

  else if (caso2 == "o") {
    for(int a=contadorz;a<=contadorz+aumento;a++){
      servo3.write(a);   
    }
    contadorz=contadorz+aumento;
    delay(150);
  }
  else if (caso2 == "l") {
    for(int b=contadorz;b>=contadorz-aumento;b--){
      servo3.write(b);   
    }
    contadorz=contadorz-aumento;
    delay(150);
  }

  else if (caso2 == "y") {
    for(int c=contadorw;c<=contadorw+aumentoPinza;c++){
      servo4.write(c);   
    }
    contadorw=contadorw+aumentoPinza;
    delay(150);
  }
  else if (caso2 == "h") {
    for(int d=contadorw;d>=contadorw-aumentoPinza;d--){
      servo4.write(d);   
    }
    contadorw=contadorw-aumentoPinza;
    delay(150);
  }

  if((pos_x && pos_y) > 0.0){
    servo1.write(theta2);
    servo2.write(theta2);
    delay(150);

  }
  if (caso == "izq1arr1") {
    servo1.write(20);
    servo2.write(120);
    delay(500);
    servo4.write(80);
  }
  else if (caso == "izq1arr2") {
    servo1.write(20);
    servo2.write(135);
    delay(500);
    servo4.write(80);
  }
  else if (caso == "izq1ctr") {
    servo1.write(20);
    servo2.write(140);
    delay(500);
    servo4.write(80);
  }
  else if (caso == "izq1aba2") {
    servo1.write(20);
    servo2.write(140);
    delay(500);
    servo4.write(80);
  }
  else if (caso == "izq1aba1") {
    servo1.write(20);
    servo2.write(140);
    delay(500);
    servo4.write(80);
  }
  else if (caso == "izq2arr2") {
    servo1.write(26);
    servo2.write(135);
    delay(500);
    servo4.write(80);
  }
  else if (caso == "izq2ctr") {
    servo1.write(26);
    servo2.write(140);
    delay(500);
    servo4.write(80);
  }
  else if (caso == "izq2aba2") {
    servo1.write(26);
    servo2.write(140);
    delay(500);
    servo4.write(80);
  }
  else if (caso == "izq2aba1") {
    servo1.write(26);
    servo2.write(140);
    delay(500);
    servo4.write(80);
  }

  else if (caso == "izq3arr1") {
    servo1.write(33);
    servo2.write(120);
    delay(500);
    servo4.write(80);
  }
  else if (caso == "izq3arr2") {
    servo1.write(33);
    servo2.write(135);
    delay(500);
    servo4.write(80);
  }
  else if (caso == "izq3ctr") {
    servo1.write(33);
    servo2.write(140);
    delay(500);
    servo4.write(80);
  }
  else if (caso == "izq3aba2") {
    servo1.write(33);
    servo2.write(140);
    delay(500);
    servo4.write(80);
  }
  else if (caso == "izq3aba1") {
    servo1.write(33);
    servo2.write(140);
    delay(500);
    servo4.write(80);
  }

  else if (caso == "ctrarr1") {
    servo1.write(40);
    servo2.write(120);
    delay(500);
    servo4.write(80);
  }
  else if (caso == "ctrarr2") {
    servo1.write(40);
    servo2.write(135);
    delay(500);
    servo4.write(80);
  }
  else if (caso == "ctrctr") {
    servo1.write(40);
    servo2.write(140);
    delay(500);
    servo4.write(80);
  }
  else if (caso == "ctraba2") {
    servo1.write(40);
    servo2.write(140);
    delay(500);
    servo4.write(80);
  }
  else if (caso == "ctraba1") {
    servo1.write(40);
    servo2.write(140);
    delay(500);
    servo4.write(80);
  }

  else if (caso == "der1arr1") {
    servo1.write(47);
    servo2.write(120);
    delay(500);
    servo4.write(80);
  }
  else if (caso == "der1arr2") {
    servo1.write(47);
    servo2.write(135);
    delay(500);
    servo4.write(80);
  }
  else if (caso == "der1ctr") {
    servo1.write(47);
    servo2.write(140);
    delay(500);
    servo4.write(80);
  }
  else if (caso == "der1aba2") {
    servo1.write(47);
    servo2.write(140);
    delay(500);
    servo4.write(80);
  }
  else if (caso == "der1aba1") {
    servo1.write(47);
    servo2.write(140);
    delay(500);
    servo4.write(80);
  }

  else if (caso == "der2arr1") {
    servo1.write(54);
    servo2.write(120);
    delay(500);
    servo4.write(80);
  }
  else if (caso == "der2arr2") {
    servo1.write(54);
    servo2.write(135);
    delay(500);
    servo4.write(80);
  }
  else if (caso == "der2ctr") {
    servo1.write(54);
    servo2.write(140);
    delay(500);
    servo4.write(80);
  }
  else if (caso == "der2aba2") {
    servo1.write(54);
    servo2.write(140);
    delay(500);
    servo4.write(80);
  }
  else if (caso == "der2aba1") {
    servo1.write(54);
    servo2.write(140);
    delay(500);
    servo4.write(80);
  }

  else if (caso == "der3arr1") {
    servo1.write(60);
    servo2.write(120);
    delay(500);
    servo4.write(80);
  }
  else if (caso == "der3arr2") {
    servo1.write(60);
    servo2.write(135);
    delay(500);
    servo4.write(80);
  }
  else if (caso == "der3ctr") {
    servo1.write(60);
    servo2.write(140);
    delay(500);
    servo4.write(80);
  }
  else if (caso == "der3aba2") {
    servo1.write(60);
    servo2.write(140);
    delay(500);
    servo4.write(80);
  }
  else if (caso == "der3aba1") {
    servo1.write(60);
    servo2.write(140);
    delay(500);
    servo4.write(80);
  }

  nh.spinOnce();
}




