![grafik](https://github.com/user-attachments/assets/7e601aef-fc5a-4730-80ef-66a8625aae23)




# HLiNaKRbCsFr für Windows
```
HLiNaKRbCsFr
  von: Sven Herz
```
* Author: Sven Herz
* Getestet: Windows 11


## Beschreibung
HLiNaKRbCsFr wurde entwickelt, um die Registry automatisiert zu durchsuchen. Das Programm ist für die folgenden zwei Szenarien ausgerichtet:

1. Suche wird nur anhand der Werte durchgeführt. Es werden keine Pfade berücksichtigt
2. Pfade + Werte werden bei der Suche berücksichtigt. Es werden nur exakte Treffer gelistet.


![grafik](https://github.com/user-attachments/assets/e4c0e9dd-db95-40c7-870e-ad1675831004)



## Programmstart
Das Programm ist für Windows programmiert worden. Es kann sowohl mit einer CMD, aber auch mit Powershell ausgeführt werden. Die bessere Darstellung wird mit Powershell erreicht. Um das Programm zu startet, muss lediglich in den Ordner navigiert und der folgende Befehl ausgeführt werden:

```
.\HLiNaKRbCsFr.exe -h
```



## Voraussetzung

#### Werte ohne Pfad
HLiNaKRbCsFr liest aus der Datei **inputfile.csv** Zeile für Zeile die Werte aus der ersten Spalte und sucht in der Registry nach allen Treffern. Diese Treffer werden anschließend in einer Datei mit dem Namen **search_result.csv** gespeichert.

Bsp.:

![grafik](https://github.com/user-attachments/assets/e7c1b375-51c7-4c19-99a1-7583fa3c4c71)





#### Werte mit Pfad
Wird eine Suche nach einem Wert in Abhängigkeit des Pfads durchgeführt, muss in der ersten Spalte der Datei **inputfile.csv** der Pfad stehen. In der zweiten Spalte muss der jeweilige Wert hinterlegt werden, nachdem gesucht werden soll.

Bsp.:

![grafik](https://github.com/user-attachments/assets/0cf9c4f5-3730-4fbc-a5c1-703ea64e9451)






## Optionen
Insgesamt stehen sechs Optionen zur Auswahl:

```
Syntax: .\HLiNaKRbCsFr.exe <options>

-h (show help)
-v (verbose mode)
-a (search in all HKEYs)
-u (search in HKEY_CURRENT_USER)
-m (search in HKEY_LOCAL_MACHINE)
-c (search in HKEY_CURRENT_CONFIG)
```


Als Default ohne gesetzte Option wird der Hilfedialog angezeigt.





## Results
Die Results werden in einer neuen csv-Datei gespeichert. Die Einträge können anschließend formatiert werden.




## Projekt kompilieren

Um das Projekt zu bauen, kann MinGW genutzt werden. Bei dem folgenden Befehl müssen die Pfade zum Projekt noch angegeben werden:

```
gcc -o <PFAD>/HLiNaKRbCsFr.exe <PFAD>/main.c <PFAD>/HLiNaKRbCsFr.h <PFAD>/banner.c <PFAD>/help_functions.c

```
