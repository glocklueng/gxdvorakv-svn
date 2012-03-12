 
[hardwarekonfig]
wurzel: 2
[2.1]
spi: OBJEKTID=3
{2.3}
klasse: "HC_Moduluebersicht.Class"
name: _PRJ-Moduluebersicht
[371.1]
[371.100]
moduladr: 0
slotnr: 1
modulname: Display
art: SUBKOMPONENTE
{371.101}
klasse: "4PP065.0571-X74d"
[5.1]
[5.100]
moduladr: 0
verbunden: 63
station: 3
busart: 6
version: 1.0.0.0
[5.101]
[5.1824]
{5.1856}
klasse: "X20DI9371"
comparam: 
[4.1]
[4.100]
moduladr: 0
verbunden: 63
station: 2
busart: 6
version: 1.0.0.0
[4.101]
[4.1824]
{4.1856}
klasse: "X20DC2396"
comparam: 
[10.1]
[10.100]
moduladr: 0
verbunden: 63
station: 1
busart: 6
version: 1.0.0.0
[10.101]
[10.1824]
{10.1856}
klasse: "X20BR9300"
comparam: 
[7.1]
[7.100]
moduladr: 0
verbunden: 63
station: 4
busart: 6
version: 1.0.0.0
[7.101]
[7.1824]
{7.1856}
klasse: "X20DO9322"
comparam: 
[9.1]
[9.100]
moduladr: 0
verbunden: 63
station: 5
busart: 6
version: 1.0.0.0
[9.101]
[9.1824]
{9.1856}
klasse: "X20AO2622"
comparam: 
[3.1]
spi: OBJEKTID=63
spi: OBJEKTID=10
spi: OBJEKTID=4
spi: OBJEKTID=5
spi: OBJEKTID=7
spi: OBJEKTID=9
{3.2}
klasse: "HC_SPS.Class"
familie: 60
[63.1]
[63.100]
modulname: CPU
version: 1.1.3.0
steckplatzgrp: "disbus"
steckplatzinfo: NUMMER=1, MODULID=371, FLAGS=1
steckplatzgrp: "pp400d"
steckplatzinfo: NUMMER=1, MODULID=0, FLAGS=0
steckplatzgrp: "syssub"
steckplatzinfo: NUMMER=1, MODULID=0, FLAGS=0
anschlussgrp: "eth5"
anschlussinfo: NUMMER=1, MODULID=0, FLAGS=0
anschlussgrp: "usb6"
anschlussinfo: NUMMER=1, MODULID=0, FLAGS=0
anschlussgrp: "usb7"
anschlussinfo: NUMMER=1, MODULID=0, FLAGS=0
anschlussgrp: "vir8"
anschlussinfo: NUMMER=1, MODULID=0, FLAGS=0
anschlussgrp: "x2x4"
anschlussinfo: NUMMER=1, MODULID=10, FLAGS=1
anschlussinfo: NUMMER=2, MODULID=4, FLAGS=1
anschlussinfo: NUMMER=3, MODULID=5, FLAGS=1
anschlussinfo: NUMMER=4, MODULID=7, FLAGS=1
anschlussinfo: NUMMER=5, MODULID=9, FLAGS=1
anschlussinfo: NUMMER=6, MODULID=0, FLAGS=0
[63.101]
[63.1840]
comparam_x2x4: SYNCUSAGE=50, IOSIZE=8, RESPTIME=100, BUSLENGTH=1, STATIONS=64, ASYNCPAYLOAD=80
timingparam_x2x4: CYCLETIME=2000, PRESCALE=1
[63.1632]
comparam_eth5: IP=192.168.100.200, MASK=255.255.255.0, BROADCAST=255.255.255.255, FORCE
inaparam_eth5: PORTNO=11159, FORCE
dhcpserverparam_eth5: NAME="BR_065", START=192.168.100.0, STOP=192.168.100.5, MASK=255.255.255.0, GATEWAY=0.0.0.0, BROADCAST=255.255.255.255, DEFLEASETIME=3600
dnsparam_eth5: HOST="BR_HOST", DISABLE
[63.1888]
[63.1232]
[63.1824]
{63.108}
klasse: "4PP065.0571-X74"
dhcpserverparam: NAME="BR_065", START=192.168.100.0, STOP=192.168.100.5, MASK=255.255.255.0, GATEWAY=0.0.0.0, BROADCAST=255.255.255.255, DEFLEASETIME=3600
standardgateway: IP=255.255.255.255
dnsparam: HOST="BR_HOST", DISABLE
