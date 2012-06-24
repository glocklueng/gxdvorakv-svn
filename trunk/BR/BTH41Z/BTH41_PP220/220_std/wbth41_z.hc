 
[hardwarekonfig]
wurzel: 2
[2.1]
spi: OBJEKTID=3
{2.3}
klasse: "HC_Moduluebersicht.Class"
name: _PRJ-Moduluebersicht
[64.1]
[64.100]
moduladr: 1
modulname: Display
art: SUBKOMPONENTE
{64.101}
klasse: "4PP220057165d"
[65.1]
[65.100]
moduladr: 1
art: SUBKOMPONENTE
steckplatzgrp: "syssub"
steckplatzinfo: NUMMER=1, MODULID=4, FLAGS=1
{65.101}
klasse: "4PP220057165si"
[5.1]
[5.100]
moduladr: 0
verbunden: 4
station: 1
busart: 6
version: 1.0.0.0
[5.101]
[5.1824]
{5.1856}
klasse: "X20BR9300"
comparam: 
[6.1]
[6.100]
moduladr: 0
verbunden: 4
station: 2
busart: 6
version: 1.0.0.0
[6.101]
[6.1824]
{6.1856}
klasse: "X20DC1396"
comparam: 
[361.1]
[361.100]
moduladr: 0
verbunden: 4
station: 7
busart: 6
version: 1.0.0.0
[361.101]
[361.1824]
{361.1856}
klasse: "X20AO2622"
comparam: NODE_NUMBER_DEFINED
[23.1]
[23.100]
moduladr: 0
verbunden: 4
station: 4
busart: 6
version: 1.0.0.0
[23.101]
[23.1824]
{23.1856}
klasse: "X20DI9371"
comparam: 
[9.1]
[9.100]
moduladr: 0
verbunden: 4
station: 5
busart: 6
version: 1.0.0.0
[9.101]
[9.1824]
{9.1856}
klasse: "X20DO9322"
comparam: 
[10.1]
[10.100]
moduladr: 0
verbunden: 4
station: 6
busart: 6
version: 1.0.0.0
[10.101]
[10.1824]
{10.1856}
klasse: "X20DO9322"
comparam: 
[4.1]
[4.100]
moduladr: 1
slotnr: 1
version: 1.0.0.0
anschlussgrp: "x2x1"
anschlussinfo: NUMMER=1, MODULID=5, FLAGS=1
anschlussinfo: NUMMER=2, MODULID=6, FLAGS=1
anschlussinfo: NUMMER=3, MODULID=25, FLAGS=1
anschlussinfo: NUMMER=4, MODULID=23, FLAGS=1
anschlussinfo: NUMMER=5, MODULID=9, FLAGS=1
anschlussinfo: NUMMER=6, MODULID=10, FLAGS=1
anschlussinfo: NUMMER=7, MODULID=361, FLAGS=1
[4.101]
[4.1840]
comparam_x2x1: SYNCUSAGE=50, IOSIZE=8, RESPTIME=100, BUSLENGTH=1000, STATIONS=64, ASYNCPAYLOAD=80
timingparam_x2x1: CYCLETIME=1000, PRESCALE=1
{4.1824}
klasse: "3IF791.9"
[3.1]
spi: OBJEKTID=63
spi: OBJEKTID=5
spi: OBJEKTID=6
spi: OBJEKTID=25
spi: OBJEKTID=23
spi: OBJEKTID=9
spi: OBJEKTID=10
spi: OBJEKTID=361
{3.2}
klasse: "HC_SPS.Class"
familie: 50
[25.1]
[25.100]
moduladr: 0
verbunden: 4
station: 3
busart: 6
version: 1.0.0.0
[25.101]
[25.1824]
{25.1856}
klasse: "X20DI9371"
comparam: NODE_NUMBER_DEFINED
[63.1]
[63.100]
moduladr: 0
modulname: CPU
version: 1.0.0.0
steckplatzgrp: "disbus"
steckplatzinfo: NUMMER=1, MODULID=64, FLAGS=1
steckplatzgrp: "sysbus"
steckplatzinfo: NUMMER=1, MODULID=65, FLAGS=1
steckplatzgrp: "pp200d"
steckplatzinfo: NUMMER=1, MODULID=0, FLAGS=0
anschlussgrp: "ser1"
anschlussinfo: NUMMER=1, MODULID=0, FLAGS=0
anschlussgrp: "eth5"
anschlussinfo: NUMMER=1, MODULID=0, FLAGS=0
anschlussgrp: "usb6"
anschlussinfo: NUMMER=1, MODULID=0, FLAGS=0
anschlussgrp: "usb7"
anschlussinfo: NUMMER=1, MODULID=0, FLAGS=0
anschlussgrp: "vir8"
anschlussinfo: NUMMER=1, MODULID=0, FLAGS=0
[63.101]
[63.109]
comparam_ser1: 115200,e,8,1, TYPE="RS232", RIT=5, FORCE
inaparam_ser1: FORCE,NODENUMBER=2, PORTNUMBER=11159
modemparam_ser1: 57600,n,8,1, RIT=255
modeminit_ser1: STRING=ATS0=1
modemescape_ser1: SEQUENCE=+++
modemdelay_ser1: RESPONSE=2500
slipparam_ser1: MTU=1006, COMPRESSION, ALLOWCOMPRESSION
[63.1632]
comparam_eth5: IP=192.168.100.200, MASK=255.255.255.0, BROADCAST=255.255.255.255, FORCE
inaparam_eth5: PORTNO=11159, FORCE
dnsparam_eth5: HOST="BR_HOST", DISABLE, SERVERIP=192.168.1.254
[63.1888]
[63.1824]
[63.1232]
{63.108}
klasse: "4PP220.0571-65"
standardgateway: IP=255.255.255.255
dnsparam: HOST="BR_HOST", DISABLE, SERVERIP=192.168.1.254
