# KIV/PSI - úkol 1 - UDP multicast klient (SSDP) 

## Popis řešení
Program je napsán v C pro použití v unix-like systémech (testováno na macos a Linux-Ubuntu).

## Spuštění
Program neočekává žádný parametr. Připojí se vždy do multicast skupiny 239.255.255.250 za využití portu 1900

## Poznámka k odevzdání
Velice se omlouvám, že tento úkol odevzdávám až nyní, s velkým zpožděním.
Úkol jsem dokončil včas, ale úplně jsem jej zapomněl dát na github a odeslat odkaz do Google Classroom.

## Ukázka získaných dat

```
Listening to multicasts...
M-SEARCH * HTTP/1.1
HOST: 239.255.255.250:1900
MAN: "ssdp:discover"
MX: 1
ST: urn:dial-multiscreen-org:service:dial:1
USER-AGENT: Microsoft Edge/100.0.1185.50 Mac OS X
```