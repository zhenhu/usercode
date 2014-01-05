import os

file="BackgroundStudiesFiles/removedLifetime_2muTrack_DYJets50.txt"

openFile=open(file,"r")
outFile=open(file+".filtered","w")
n=0
for line in openFile.readlines():
    lineParts=line.split(" ")
#    if float(lineParts[0])>130 or float(lineParts[0])<70:
    if n%100 == 0:
        outFile.write(line)
        pass
    n=n+1
    pass

openFile.close()
outFile.close()
