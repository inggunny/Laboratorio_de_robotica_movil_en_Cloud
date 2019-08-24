import shlex, subprocess
import time
import csv
import math
fila =0
comuna=0
conta =0
latini=0
lonini=0
latact=0
lonact=0
#pedir posicion final al usuario (posicion final)
#latfinal=(abs(float (input("latitud final: ")))-32.88)*1000000
#lonfinal=(abs(float (input("longitud final: ")))-68.86)*1000000

latfinal=(abs(-32.8821375)-32.88)*1000000
lonfinal=(abs(-68.8612375)-68.86)*1000000

############################################################################
def leerposicionini():
        fila=0
        global conta
        global latini
        global lonini
        with open('server.csv') as File:
                reader = csv.reader(File)
                for datos in reader:
                        fila = fila + 1
                        if (fila > conta):
                                conta = conta + 1
                                if (datos[0]=="robot1"):
                                        if(datos[1]=="sensor"):
                                                if(datos[2]=="posicion"):
                                                        latini=(abs(float(datos[3]))- 32.88)*1000000
                                                        lonini=(abs(float(datos[4]))- 68.86)*1000000
                                                        #print ("lat=",latini)
                                                        #print ("lon=",lonini)                               
########################################################################
def leerposicionact():
        fila=0
        global conta
        global latact
        global lonact
        with open('server.csv') as File:
                reader = csv.reader(File)
                for datos in reader:
                        fila = fila + 1
                        #print ("fila=",fila)
                        #print ("conta=",conta)
                        if(fila > conta):
                                conta = conta + 1
                                #print ("conta=",conta)
                                if (datos[0]=="robot1"):
                                        if(datos[1]=="sensor"):
                                                if(datos[2]=="posicion"):
                                                        latact=(abs(float(datos[3]))- 32.88)*1000000
                                                        lonact=(abs(float(datos[4]))- 68.86)*1000000
                                                        #print ("lat=",latact)
                                                        #print ("lon=",lonact)
########################################################################

                                                        
#obtener posicion del robot (posicion inicial)
command_line = 'mosquitto_pub -h localhost -t campo/desplazamiento/robot1 -m P'
args = shlex.split(command_line)
subprocess.call(args)
time.sleep(15)
leerposicionini()
print ("latini=",latini)
print ("lonini=",lonini)
#obtener hipotenusa
latdif=latfinal - latini
londif=lonfinal - lonini
#moduloini=((latdif)**2 + (londif)**2)**(1/2)
print ("latdifini=",latdif)
print ("londifini=",londif)
#---esto deberia ir a una funcion(o quizas no)--------
moduloini= math.hypot(latdif,londif)

faseini= math.degrees(math.atan(londif/latdif))
print ("modulo inicial=",moduloini," ,fase inicial=",faseini)

#-----------------------------------------------------
#avanza robot. delay
command_line = 'mosquitto_pub -h localhost -t campo/desplazamiento/robot1 -m W'
args = shlex.split(command_line)
subprocess.call(args)
time.sleep(10)
#detener robot. posicion  robot. calcular hipotenusa
command_line = 'mosquitto_pub -h localhost -t campo/desplazamiento/robot1 -m F'
args = shlex.split(command_line)
subprocess.call(args)

while(1):  
        time.sleep(5)
        command_line = 'mosquitto_pub -h localhost -t campo/desplazamiento/robot1 -m P'
        args = shlex.split(command_line)
        subprocess.call(args)
        time.sleep(1)
        leerposicionact()
        #print ("latitud actual=",latact," ,longitud actual",lonact)
        #print ("lat=",latact)
        #print ("lon=",lonact)
        latdif=latfinal - latact
        londif=lonfinal - lonact
        print ("latdifact=",latdif)
        print ("londifact=",londif)
        moduloact= math.hypot(latdif,londif)
        if(latdif != 0):
                faseact= math.degrees(math.atan(londif/latdif))
                print ("modulo actual=",moduloact," ,fase actual=",faseact)
        #comparacion modulo
        if(moduloact < 50):
                print("robot en posicion final")
                while(1):
                        time.sleep(60)
                        #FIN!!
        else:
                if( (faseact + (faseact * 0.1)) > faseini >(faseact - (faseact * 0.1))):
                        print("robot adelante")
                        command_line = 'mosquitto_pub -h localhost -t campo/desplazamiento/robot1 -m W'
                        args = shlex.split(command_line)
                        subprocess.call(args)
                if((faseact - (faseact * 0.1)) < faseini):
                        print("robot dobla izquierda")
                        command_line = 'mosquitto_pub -h localhost -t campo/desplazamiento/robot1 -m A'
                        args = shlex.split(command_line)
                        subprocess.call(args)
                if((faseact + (faseact * 0.1)) > faseini):
                        print("robot dobla derecha")
                        command_line = 'mosquitto_pub -h localhost -t campo/desplazamiento/robot1 -m D'
                        args = shlex.split(command_line)
                        subprocess.call(args)
                

