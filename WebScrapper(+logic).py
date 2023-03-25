import requests
import time
import math

mybot1='M4'
mybot2='M3'
mygoal='G43'
enemylist=[]

turing_cost=0

##class datapoints:
##    def __init__(self):
##        self.cornerTR=[-1,0,0] #Top right 
##        self.cornerBL=[-1,0,0] #Botton left
##        self.goalA=[-1,0,0]    #Attack 
##        self.goalD=[-1,0,0]    #Defend
##        self.ball=[-1,0,0]     #Ball
##        self.botA=[-1,0,0]     #My bot 1
##        self.botB=[-1,0,0]     #My bot 2
##        self.enemyA=[-1,0,0]   #Enemy bot 1
##        self.enemyB=[-1,0,0]   #Enemy bot 2
##
##    def updaterecord(data):
##        try:
##            if data[0]=='B':
##                self.ball=data[1:4]
##            elif data[0]=='C0':
##                self.cornerTR=data[1:4]
##            elif data[0]=='C1':
##                self.cornerBL=data[1:4]
##            elif data[0]=='G43':
##                self.goalA=data[1:4]
##            elif data[0]=='G42':
##                self.goalD=data[1:4]
##            elif data[0][0]=='M':
##                if data[0]==mybot1:
##                    self.botA=data[1:4]
##                elif data[0]==mybot2:
##                    self.botB=data[1:4]
##                elif data[0]in enemylist:
##                    if data[0]== enemylist[0]:
##                        self.enemyA=data[1:4]
##                    else:
##                        self.enemyB=data[1:4]
##                else:
##                    enemylist.append(data[0])
##            else:
##                print("unkown record:")
##                print(data)
##        except Exception as e:
##            print("Error with record:")
##            print(data)
##            print(e)
##
##
##    def calc_distance_and_angle(a,b):
##        dlat = a[0] - b[0] 
##        dlon = a[1] - b[1]
##        d=math.sqrt(dlat*dlat+dlon*dlon)
##        a=math.atan2(dlat,dlon)+a[2]%6.28319
##        return d,a
##
##    # example usage
##    a =[5, 0, 0]
##    b =[0, 5, 0]
##
##    distance,angle = calc_distance_and_angle(a,b)
##
##    print("Distance: %.2f Bearing Angle: %.2f"%(distance,angle))





    


    
        

def timetest():
    somelist=[]
    for y in range(10):
        print(".",end='')
        for x in range(100):
            start_time = time.time()
            main()
            somelist.append(time.time() - start_time)
            #print("--- %s seconds ---" % (time.time() - start_time))
    max_value = max(somelist)
    min_value = min(somelist)
    avg_value = 0 if len(somelist) == 0 else sum(somelist)/len(somelist)
    print("\nMAX: "+str(max_value)+" MIN: "+str(min_value)+" AVG "+ str(avg_value))

#datapoints

URL = "http://192.168.4.1"

def main():
    page = requests.get(URL)

    webdata = page.text[106:-17].split('<br>')#[1:]
    data = []

    #print(page.text)
    #print("\n")
    #print(webdata)

    for x in webdata:
        if x!='':
            data.append(x[:-2].split(','))
            

    return data

#timetest()
data=[]
data=main()


#print(data)
print(" Name     X      Y     Theta")
for x in data:
    print (x)
