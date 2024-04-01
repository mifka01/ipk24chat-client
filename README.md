# Klient pro komunikaci - předmět IPK na FIT VUT v Brně.

Autor: Radim Mifka (xmifka00)

## Úvod

Klient pro komunikaci s možností použití protokolu `TCP` nebo `UDP`.
Implementace je v jazyce `C++20`.

## Teorie

Klient pro komunikaci je aplikace, která umožňuje komunikaci mezi dvěma a více uživateli.
Pro tuto komunikaci je využíván nějaký komunikační protokol, například právě `TCP` či `UDP`.

### UDP

UDP (User Datagram Protocol) je transportní protokol, který se využívá pro přenos dat v počítačových sítích.
Jeho datagramy, neboli pakety dat, neposkytují žádnou záruku doručení, což znamená, že není zajištěna spolehlivost.
Tento aspekt UDP ho činí ideálním pro situace, kde je klíčová rychlost přenosu dat před spolehlivostí.

V aplikacích, kde je spolehlivost klíčová, jako je například tento chatovací klient,
je spolehlivost řešena na úrovni aplikace, nikoli prostřednictvím protokolu UDP.

UDP je bezspojový protokol, což znamená, že neprobíhá žádná fáze navazování spojení, a tudíž neexistuje domluva na parametrech spojení
před samotným přenosem dat.

### TCP

TCP (Transmission Control Protocol) je transportní protokol, který se využívá pro přenos dat v počítačových sítích.
Jeho spojení je spojově orientované, což znamená, že před samotným přenosem dat probíhá fáze navazování spojení,
kde se domlouvají parametry spojení.

TCP poskytuje záruku doručení dat, což znamená, že pokud data dorazí, tak dorazí v pořadí, v jakém byla odeslána,
a že dorazí vůbec. Pokud data dorazit nemohou, je odesílatel informován o selhání doručení.

## Implementace

Implementace programu je rozdělena do několika částí.
Cílem bylo vytvořit program, který je jednoduše rozšiřitelný a přehledný.

### Argumenty

Program je schopen zpracovat několik argumentů, které ovlivňují jeho chování.
Argumenty jsou zpracovány pomocí mé třídy `ArgumentParser`.
Tato třida dovoluje zpracovávat jakékoliv argumenty pomocí metody `add_argument`.
Argumenty mohou být povinné, nepovinné, s hodnotou, bez hodnoty, s výchozí hodnotou, či výčtové.

Třída byla implementována s ohledem na znovupoužitelnost v dalších projektech a jednoduchost použití.
Automaticky zpracovává a generuje argument `--help` z argumentů, které byly přidány.

Inspirováno knihovnou `argparse` z jazyka Python.

### Klient

Klient je implementován jako třída `Client`.
Tato třída je hlavní třídou programu. Přijímá argumenty, které využívá k nastavení komunikačního protokolu a adresy serveru.
Vybírá mezi protokoly `TCP` a `UDP` a vytváří příslušné sokety.

Spojuje veskerou funkcionalitu programu, jako je připojení k serveru, odesílání zpráv, příjem zpráv a ukončení spojení.

Klient disponuje stavem, který je využíván protokolem, který je implementován jako stavový automat.

### Neblokující komunikace

Implementace neblokující komunikace je realizována pomocí třídy `SocketPoller`.
Využívá knihovnu `poll` pro monitorování souborových deskriptorů a zjišťování, zda je možné číst nebo zapisovat.

### Protokol

Protokol je implementován jako třída `Protocol`.
Tato třída je abstraktní třídou, která definuje rozhraní pro komunikační protokol.
Je implementována pro možnost vytvoření vlastního protokolu, který by byl odlišný od `TCP` a `UDP`.

Z této třídy jsou odvozeny třídy `TCP` a `UDP`, které implementují konkrétní protokoly.

Protokol pracuje jako statový automat a zpracovává zprávy podle aktuálního stavu klienta.

### Příkazy

Příkazy jsou implementovány jako třída `Command`.
Tato třída je abstraktní třídou, která definuje rozhraní pro příkazy.
Je implementována pro možnost vytvoření vlastních příkazů mimo ty, které byly v zadání.

### Zprávy

Zprávy jsou implementovány jako třída `Message`.
Tato třída je abstraktní třídou, která definuje rozhraní pro zprávy.
Implementuje základní metody pro zpracování zpráv.
Opět je jednoduše rozšiřitelná pro vytvoření vlastních zpráv.

Nad těmito zprávami je implementovaný návrhový vzor `Visitor`,
který umožňuje jednoduché zpracování zpráv pomocí návštěvníka bez nutnosti změny typu zprávy.

Implementace tohoto návrhového vzoru je dostupná ve třídě `MessageVisitor`.

## Testování

Testování bylo prováděno především pomocí programu `netcat` a sledováním komunikace pomocí programu `Wireshark`.
Toto bylo dostačující hlavně pro testování komunikace pomocí protokolu `TCP`.

### Příklady Testů

#### Příkaz auth a následná reply (chyba/úspěch) testováno pro TCP i UDP.

Testováno pomocí netcat + Wireshark.

```shell
/auth xmifka00 sec radim
--
AUTH xmifka00 AS radim USING sec

                                    REPLY NOK IS error

/auth xmifka00 sec radim
--
AUTH xmifka00 AS radim USING sec2
                                    REPLY OK IS success
```

#### Přikaz help

Testováno pomocí netcat.

```shell
/help
--
/help
Commands:
 /auth {Username} {Secret} {DisplayName}
 /join {ChannelID}
 /rename {DisplayName}
 /help
```

#### Odeslání/Přijmutí zprávy testováno pro TCP i UDP.

Testováná komunikace mezi dvěma klienty. (jeden je nyní server)
Pomocí netcat(xxd) a Wireshark.

```shell
/auth xmifka00 sec radim
--
ID=1, Type=auth, UserName=xmifka00, DisplayName=radim, Secret=sec
                                            Type=confirm, RefID-1
                                            ID=0, Type=reply, Result=OK, RefID=1, Content=odpoved od serveru
Type=confirm, RefID=0
ID=2, Type=msg, DisplayName=radim, Content=ahoj
                                            Type=confirm, RefID=2
                                            ID=256, Type=msg, DisplayName=Server, Content=Cau
ID=3, Type=msg, DisplayName=radim, Content=Jak se mas?
Type=confirm, RefID=256
                                            Type=confirm, RefID3
                                            ID=512, Type=msg, DisplayName=Server, Content=Dobre
Type=confirm, RefID=512
```

#### Testování join/rename/leave

Testováno pomocí referenčního discord serveru.
Klient byl schopen správně reagovat na příkazy join, rename a leave.

#### Testování odpojení klienta/serveru a změna portu

Testováno na vlastní implementaci jednoduchého python serveru kvůli zajištění funkčnosti UDP.
Klient byl schopen správně reagovat na odpojení serveru, klienta i změnu portu.

#### Testování opakovaného odeslání zprávy

Opět testováno pomocí python serveru, který neodesílal potvrzení o přijetí zprávy.
A očekával přijetí 4 zpráv (1 + 3 opakované zprávy).

## Rozšíření

Rozšíření nad rámec zadání bylo především v obecnosti implementace většiny částí programu.
Dovoluje to jednoduchý způsob přidání dalších argumentů, příkazů, protokolů, či zpráv.

## Citace

HALL, Brian. Beej's Guide to Network Programming. [online]. 2023. [cit. 2024-04-01]. Dostupné z: https://beej.us/guide/bgnet/html/.

PYTHON. Argparse [modul/knihovna]. [cit. 2024-04-01]. Dostupné z: https://docs.python.org/3/library/argparse.html

RFC 9293. [online/rfc]. 2022 [cit. 2024-04-01]. Dostupné z: https://datatracker.ietf.org/doc/html/rfc9293.

RFC 768 [online/rfc]. 1980 [cit. 2024-04-01]. Dostupné z: https://datatracker.ietf.org/doc/html/rfc768

PYTHON. UDPCommunication [online/dokumentace]. [cit. 2024-04-01]. Dostupné z: https://wiki.python.org/moin/UdpCommunication

## Licence

[GNU/AGPL](LICENSE)
