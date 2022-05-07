#!/usr/bin/env python3

#Paquetes
import rospy
import threading
import matplotlib.pyplot as plt
from matplotlib import pyplot
from geometry_msgs.msg import Twist
from matplotlib.animation import FuncAnimation

#Datos a Graficar
global x_data,y_data

x_data=[]
y_data=[]

#Funcion para graficar
def grafica():
    rospy.init_node('turtle_bot_interface',anonymous=False)
    rospy.Subscriber('/turtlebot_position',Twist, lectura)
    tiempo=threading.Thread(target=mapa)
    tiempo.setDaemon(True)
    tiempo.start()

#Funcion para leer mensajes
def lectura(msg):
    px=msg.linear.x
    py=msg.linear.y
    print(px)
    print(py)
    x_data.append(px)
    y_data.append(py)
    
def mapa():
    fig=FuncAnimation(plt.gcf(),dibujo,interval=1000)
    pyplot.show()

def dibujo(i):
    plt.cla()
    plt.plot(x_data,y_data)
    plt.xlim([-90,90])
    plt.ylim([-90,90])
    plt.xlabel("Eje X")
    plt.ylabel("Eje Y")
    plt.title("Posicion Robot")

#Creacion de nodo y subcripcion 
if __name__ == '__main__':
    try:
        grafica()
        rospy.spin()
    except rospy.ROSInterruptException:
        pass
