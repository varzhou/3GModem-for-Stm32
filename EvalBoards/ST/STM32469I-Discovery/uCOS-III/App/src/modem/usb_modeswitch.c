/*
  Mode switching tool for controlling mode of 'multi-state' USB devices
  Version 2.2.5, 2015/07/16

  Copyright (C) 2015 Kaiqin Lin (linkaiqin@sina.com)
    This file is modified in order to run in embeded sysytem.

  Copyright (C) 2007 - 2015 Josua Dietze (mail to "digidietze" at the domain
  of the home page; or write a personal message through the forum to "Josh".
  NO SUPPORT VIA E-MAIL - please use the forum for that)

  Major contributions:

  Command line parsing, decent usage/config output/handling, bugfixes and advanced
  options added by:
    Joakim Wennergren

  TargetClass parameter implementation to support new Option devices/firmware:
    Paul Hardwick (http://www.pharscape.org)

  Created with initial help from:
    "usbsnoop2libusb.pl" by Timo Lindfors (http://iki.fi/lindi/usb/usbsnoop2libusb.pl)

  Config file parsing stuff borrowed from:
    Guillaume Dargaud (http://www.gdargaud.net/Hack/SourceCode.html)

  Hexstr2bin function borrowed from:
    Jouni Malinen (http://hostap.epitest.fi/wpa_supplicant, from "common.c")

  Other contributions: see README

  Device information contributors are named in the "device_reference.txt" file. See
  homepage.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details:

  http://www.gnu.org/licenses/gpl.txt

*/




#include "usbh_linux.h"
#include "string.h"
#include "errno.h"
#include "timer.h"
#include "memory.h"




#define DETACHONLY_MODE     0x00000001
#define HUAWEI_MODE         0x00000002
#define SIERRA_MODE         0x00000004
//#define SONY_MODE           0x00000008
#define GCT_MODE            0x00000010
#define KOBIL_MODE          0x00000020
#define SEQUANS_MODE        0x00000040
#define MOBILEACTION_MODE   0x00000080
#define CISCO_MODE          0x00000100
#define QISDA_MODE          0x00000200
#define QUANTA_MODE         0x00000400
#define BLACKBERRY_MODE     0x00000800
//#define PANTECH_MODE        0x00001000
#define HUAWEINEW_MODE      0x00002000


#define SHOW_PROGRESS if (show_progress) fprintf


struct device_refer
{
    u16 DefaultVendor;
    u16 DefaultProduct;

    u16 ModeMap;

    char *MessageContent;
    char *MessageContent2;
    char *MessageContent3;
    char *uMa;
    char *uPr;

    u8 MessageEndpoint;
    u8 StandardEject;
    u8 NeedResponse;
};



#include "device_refer_tbl.c"



static const struct usb_device_id usb_modeswitch_ids[] =
{
    { USB_DEVICE(0x03f0, 0x002a) },   /* HP LaserJet Professional P1102*/
    { USB_DEVICE(0x0408, 0x1000) },   /* Quanta MU-Q101*/
    { USB_DEVICE(0x0408, 0xea17) },   /* Quanta 1KR / USB-lte 7410*/
    { USB_DEVICE(0x0408, 0xea25) },   /* Quanta 1K3 LTE*/
    { USB_DEVICE(0x0408, 0xea43) },   /* Quanta MobileGenie 4G lte, Quanta 1K6*/
    { USB_DEVICE(0x0408, 0xf000) },   /* Yota Router (Quanta 1QDLZZZ0ST2)*/
    { USB_DEVICE(0x0408, 0xf001) },   /* SpeedUp SU-8500U*/
    { USB_DEVICE(0x0421, 0x060c) },   /* Nokia CS-10*/
    { USB_DEVICE(0x0421, 0x0610) },   /* Nokia CS-15*/
    { USB_DEVICE(0x0421, 0x0618) },   /* Nokia CS-12*/
    { USB_DEVICE(0x0421, 0x061d) },   /* Nokia CS-11*/
    { USB_DEVICE(0x0421, 0x0622) },   /* Nokia CS-17*/
    { USB_DEVICE(0x0421, 0x0627) },   /* Nokia CS-18*/
    { USB_DEVICE(0x0421, 0x062c) },   /* Nokia CS-19*/
    { USB_DEVICE(0x0421, 0x0632) },   /* Nokia CS-7M-01*/
    { USB_DEVICE(0x0421, 0x0637) },   /* Nokia CS-21M-02*/
    { USB_DEVICE(0x0471, 0x1210) },   /* Vodafone MD950 (Wisue Technology)*/
    { USB_DEVICE(0x0471, 0x1210) },   /* Philips (?)*/
    { USB_DEVICE(0x0471, 0x1237) },   /* Philips TalkTalk (NXP Semiconductors "Dragonfly")*/
    { USB_DEVICE(0x0482, 0x024d) },   /* Kyocera W06K CDMA modem*/
    { USB_DEVICE(0x04bb, 0xbccd) },   /* I-O Data WMX2-U Wimax*/
    { USB_DEVICE(0x04cc, 0x2251) },   /* Alcatel-Lucent ABS-T920*/
    { USB_DEVICE(0x04cc, 0x225c) },   /* Alcatel-Lucent T930S*/
    { USB_DEVICE(0x04cc, 0x226e) },   /* Nexperia TM TD-SCDMA*/
    { USB_DEVICE(0x04cc, 0x226f) },   /* Nexperia TM TD-SCDMA (Variant)*/
    { USB_DEVICE(0x04e8, 0x680c) },   /* Samsung GT-B1110*/
    { USB_DEVICE(0x04e8, 0x689a) },   /* Samsung GT-B3730*/
    { USB_DEVICE(0x04e8, 0xf000) },   /* Samsung U209*/
    { USB_DEVICE(0x04fc, 0x2140) },   /* Sunplus Techn. SU-3200U*/
    { USB_DEVICE(0x057c, 0x62ff) },   /* AVM Fritz!Wlan USB Stick N v2*/
    { USB_DEVICE(0x057c, 0x84ff) },   /* AVM Fritz!Wlan USB Stick N*/
    { USB_DEVICE(0x05c6, 0x0010) },   /* Axesstel Modems (w/ initial idProduct 0x0010)*/
    { USB_DEVICE(0x05c6, 0x1000) },   /* StrongRising device */
    { USB_DEVICE(0x05c6, 0x1000) },   /* TechFaith Venus VT-18*/
    { USB_DEVICE(0x05c6, 0x1000) },   /* Option GlobeTrotter GX0201*/
    { USB_DEVICE(0x05c6, 0x1000) },   /* Celot K-300*/
    { USB_DEVICE(0x05c6, 0x1000) },   /* AnyDATA devices, Bless UC165*/
    { USB_DEVICE(0x05c6, 0x1000) },   /* Vertex Wireless 100 Series*/
    { USB_DEVICE(0x05c6, 0x1000) },   /* Older Option devices*/
    { USB_DEVICE(0x05c6, 0x1000) },   /* Prolink P2000 CDMA*/
    { USB_DEVICE(0x05c6, 0x1000) },   /* Quirky Option devices*/
    { USB_DEVICE(0x05c6, 0x1000) },   /* Celot CT-680*/
    { USB_DEVICE(0x05c6, 0x1000) },   /* Samsung SGH-Z810*/
    { USB_DEVICE(0x05c6, 0x1000) },   /* Qualcomm CDMA Technologies*/
    { USB_DEVICE(0x05c6, 0x2000) },   /* Various USB modems*/
    { USB_DEVICE(0x05c6, 0x2001) },   /* D-Link DWM-162-U5, DWM-162 C1, Micromax MMX 300c*/
    { USB_DEVICE(0x05c6, 0x6503) },   /* AnyDATA APE-540H*/
    { USB_DEVICE(0x05c6, 0x9024) },   /* Alcatel-sbell ASB TL131 TD-LTE*/
    { USB_DEVICE(0x05c6, 0xf000) },   /* Siptune LM-75 ("LinuxModem")*/
    { USB_DEVICE(0x05c7, 0x1000) },   /* Qtronix EVDO 3G Modem (for TianYi)*/
    { USB_DEVICE(0x0685, 0x2000) },   /* ZE-3G 7.2Mbs HSPA modem*/
    { USB_DEVICE(0x072f, 0x100d) },   /* InfoCert Business Key (SmartCard/Reader emulation)*/
    { USB_DEVICE(0x07d1, 0xa800) },   /* D-Link DWM-156 HSUPA 3.75G USB Modem */
    { USB_DEVICE(0x07d1, 0xa804) },   /* D-Link DWM-156 HSUPA 3.75G USB Modem*/
    { USB_DEVICE(0x0922, 0x1001) },   /* Dymo LabelManager*/
    { USB_DEVICE(0x0922, 0x1003) },   /* Dymo LabelManager 420P*/
    { USB_DEVICE(0x0930, 0x0d46) },   /* Toshiba G450*/
    { USB_DEVICE(0x0ace, 0x2011) },   /* Zydas ZD1211RW WLAN USB, Sphairon HomeLink 1202 (Variant 1)*/
    { USB_DEVICE(0x0ace, 0x20ff) },   /* Zydas ZD1211RW WLAN USB, Sphairon HomeLink 1202 (Variant 2)*/
    { USB_DEVICE(0x0af0, 0x4007) },   /* Option iCon 711*/
    { USB_DEVICE(0x0af0, 0x6711) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x6731) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x6751) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x6771) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x6791) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x6811) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x6911) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x6951) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x6971) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x7011) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x7031) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x7051) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x7071) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x7111) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x7211) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x7251) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x7271) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x7301) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x7311) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x7361) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x7381) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x7401) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x7501) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x7601) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x7701) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x7706) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x7801) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x7901) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x7a01) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x7a05) },   /* Option iCon 461*/
    { USB_DEVICE(0x0af0, 0x8006) },   /* Option Globetrotter (Variant)*/
    { USB_DEVICE(0x0af0, 0x8200) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x8201) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x8300) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x8302) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x8304) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x8400) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x8600) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x8700) },   /* Option GI0643 (aka XYFI)*/
    { USB_DEVICE(0x0af0, 0x8800) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x8900) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x9000) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0x9200) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0xc031) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0xc100) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0xd001) },   /* Option GlobeTrotter GI1515*/
    { USB_DEVICE(0x0af0, 0xd013) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0xd031) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0xd033) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0xd035) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0xd055) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0xd057) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0xd058) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0xd155) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0xd157) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0xd255) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0xd257) },   /* Option HSO device*/
    { USB_DEVICE(0x0af0, 0xd357) },   /* Option HSO device*/
    { USB_DEVICE(0x0b3c, 0xc700) },   /* Olivetti Olicard 100 and others*/
    { USB_DEVICE(0x0b3c, 0xf000) },   /* Olivetti Olicard 145, 155*/
    { USB_DEVICE(0x0b3c, 0xf00c) },   /* Olivetti Olicard 160*/
    { USB_DEVICE(0x0b3c, 0xf017) },   /* Olivetti Olicard 500*/
    { USB_DEVICE(0x0bdb, 0x190d) },   /* Ericsson F5521gw*/
    { USB_DEVICE(0x0bdb, 0x1910) },   /* Ericsson F5521gw (Variant)*/
    { USB_DEVICE(0x0cf3, 0x20ff) },   /* Atheros Wireless / Netgear WNDA3200*/
    { USB_DEVICE(0x0d46, 0x45a1) },   /* Kobil mIdentity 3G (1)*/
    { USB_DEVICE(0x0d46, 0x45a5) },   /* Kobil mIdentity 3G (2)*/
    { USB_DEVICE(0x0df7, 0x0800) },   /* Mobile Action ("Smart Cable")*/
    { USB_DEVICE(0x0e8d, 0x0002) },   /* MediaTek/Medion S4222 and probably others*/
    { USB_DEVICE(0x0e8d, 0x0002) },   /* MediaTek MT6276M and others*/
    { USB_DEVICE(0x0e8d, 0x7109) },   /* MediaTek Wimax USB Card*/
    { USB_DEVICE(0x0fca, 0x8020) },   /* BlackBerry Q10 and Z10*/
    { USB_DEVICE(0x0fce, 0xd0cf) },   /* Sony Ericsson MD300*/
    { USB_DEVICE(0x0fce, 0xd0df) },   /* Sony Ericsson EC400*/
    { USB_DEVICE(0x0fce, 0xd0e1) },   /* Sony Ericsson MD400*/
    { USB_DEVICE(0x0fce, 0xd103) },   /* Sony Ericsson MD400G*/
    { USB_DEVICE(0x0fd1, 0x1000) },   /* GW D301 (Advinne AMC)*/
    { USB_DEVICE(0x1004, 0x1000) },   /* LG LDU-1900D EV-DO (Rev. A)*/
    { USB_DEVICE(0x1004, 0x607f) },   /* LG HDM-2100 (EVDO Rev.A USB modem)*/
    { USB_DEVICE(0x1004, 0x613a) },   /* LG L-05A*/
    { USB_DEVICE(0x1004, 0x613f) },   /* LG LUU-2100TI (aka AT&T USBConnect Turbo)*/
    { USB_DEVICE(0x1004, 0x614e) },   /* LG L-07A*/
    { USB_DEVICE(0x1004, 0x6156) },   /* LG LUU-2110TI*/
    { USB_DEVICE(0x1004, 0x6190) },   /* LG AD600*/
    { USB_DEVICE(0x1004, 0x61aa) },   /* LG VL600*/
    { USB_DEVICE(0x1004, 0x61dd) },   /* LG L-02C LTE*/
    { USB_DEVICE(0x1004, 0x61e7) },   /* LG SD711*/
    { USB_DEVICE(0x1004, 0x61eb) },   /* LG L-08C (NTT docomo)*/
    { USB_DEVICE(0x1004, 0x6327) },   /* LG L-03D LTE/3G*/
    { USB_DEVICE(0x1033, 0x0035) },   /* Huawei E630*/
    { USB_DEVICE(0x106c, 0x3b03) },   /* UTStarcom UM175 (distributor "Alltel")*/
    { USB_DEVICE(0x106c, 0x3b05) },   /* Pantech / UTStarcom UMW190 (Verizon)*/
    { USB_DEVICE(0x106c, 0x3b06) },   /* UTStarcom UM185E (distributor "Alltel")*/
    { USB_DEVICE(0x106c, 0x3b11) },   /* Pantech UML290*/
    { USB_DEVICE(0x106c, 0x3b14) },   /* Option Beemo / Pantech P4200 LTE*/
    { USB_DEVICE(0x1076, 0x7f40) },   /* Sagem F@ST 9520-35-GLR*/
    { USB_DEVICE(0x109b, 0xf009) },   /* Hisense E910 EVDO Phone*/
    { USB_DEVICE(0x10a9, 0x606f) },   /* Pantech/Verizon UML295*/
    { USB_DEVICE(0x10a9, 0x6080) },   /* Pantech LTE Modem*/
    { USB_DEVICE(0x1199, 0x0fff) },   /* Sierra devices (specific driver)*/
    { USB_DEVICE(0x1266, 0x1000) },   /* Digicom 8E4455 (and all Pirelli devices - EXPERIMENTAL)*/
    { USB_DEVICE(0x12d1, 0x1001) },   /* Huawei E169*/
    { USB_DEVICE(0x12d1, 0x1003) },   /* Huawei E220, E230, E270, E870*/
    { USB_DEVICE(0x12d1, 0x1009) },   /* Huawei V725 Phone (aka Vodafone 725)*/
    { USB_DEVICE(0x12d1, 0x1010) },   /* Huawei ETS1201*/
    { USB_DEVICE(0x12d1, 0x101e) },   /* Huawei U7510 / U7517*/
    { USB_DEVICE(0x12d1, 0x1030) },   /* Huawei U8220, T-Mobile Pulse (Android smartphone)*/
    { USB_DEVICE(0x12d1, 0x1031) },   /* Huawei U8110 / Joy, Vodafone 845 (Android smartphone)*/
    { USB_DEVICE(0x12d1, 0x1413) },   /* Huawei EC168*/
    { USB_DEVICE(0x12d1, 0x1414) },   /* Huawei E180*/
    { USB_DEVICE(0x12d1, 0x1446) },   /* Huawei, newer modems, and rebrandings*/
    { USB_DEVICE(0x12d1, 0x1449) },   /* Huawei E352*/
    { USB_DEVICE(0x12d1, 0x14ad) },   /* Vodafone (Huawei) K3806*/
    { USB_DEVICE(0x12d1, 0x14b5) },   /* Huawei E173 (Viettel 3G)*/
    { USB_DEVICE(0x12d1, 0x14b7) },   /* Vodafone (Huawei) K4511*/
    { USB_DEVICE(0x12d1, 0x14ba) },   /* Huawei E173u-2, E177*/
    { USB_DEVICE(0x12d1, 0x14c1) },   /* Vodafone (Huawei) K4605*/
    { USB_DEVICE(0x12d1, 0x14c3) },   /* K5005 Vodafone/Huawei*/
    { USB_DEVICE(0x12d1, 0x14c4) },   /* Vodafone/Huawei K3771*/
    { USB_DEVICE(0x12d1, 0x14c5) },   /* Vodafone (Huawei) K4510*/
    { USB_DEVICE(0x12d1, 0x14d1) },   /* Vodafone / Huawei K3770*/
    { USB_DEVICE(0x12d1, 0x14fe) },   /* T-Mobile NL (Huawei E352)*/
    { USB_DEVICE(0x12d1, 0x1505) },   /* Huawei EC156, Huawei E372u-8*/
    { USB_DEVICE(0x12d1, 0x151a) },   /* Huawei E392u-12, E3131 (Variant)*/
    { USB_DEVICE(0x12d1, 0x1520) },   /* Huawei K3765*/
    { USB_DEVICE(0x12d1, 0x1521) },   /* Huawei K4505*/
    { USB_DEVICE(0x12d1, 0x1523) },   /* Huawei R201*/
    { USB_DEVICE(0x12d1, 0x1526) },   /* Vodafone / Huawei K3772*/
    { USB_DEVICE(0x12d1, 0x1553) },   /* Huawei E1553*/
    { USB_DEVICE(0x12d1, 0x1557) },   /* Huawei E173*/
    { USB_DEVICE(0x12d1, 0x155a) },   /* Vodafone (Huawei) R205*/
    { USB_DEVICE(0x12d1, 0x155b) },   /* Huawei E171*/
    { USB_DEVICE(0x12d1, 0x156a) },   /* Huawei E3276s-151 and E3251*/
    { USB_DEVICE(0x12d1, 0x157c) },   /* Huawei E3276-s150*/
    { USB_DEVICE(0x12d1, 0x157d) },   /* Huawei E3331, E3372*/
    { USB_DEVICE(0x12d1, 0x1582) },   /* Vodafone / Huawei R215 Router*/
    { USB_DEVICE(0x12d1, 0x1583) },   /* Vodafone / Huawei W5101 Router*/
    { USB_DEVICE(0x12d1, 0x15ca) },   /* Huawei E3131*/
    { USB_DEVICE(0x12d1, 0x15cd) },   /* Huawei E3372*/
    { USB_DEVICE(0x12d1, 0x15cf) },   /* Huawei E3372s-153*/
    { USB_DEVICE(0x12d1, 0x15e7) },   /* Huawei E3531*/
    { USB_DEVICE(0x12d1, 0x1805) },   /* Huawei U2800 Phone*/
    { USB_DEVICE(0x12d1, 0x1c0b) },   /* Huawei E173s*/
    { USB_DEVICE(0x12d1, 0x1c1b) },   /* Huawei GP02 (E587 Variant)*/
    { USB_DEVICE(0x12d1, 0x1c24) },   /* Huawei E173 (Moviestar)*/
    { USB_DEVICE(0x12d1, 0x1d50) },   /* Huawei ET302*/
    { USB_DEVICE(0x12d1, 0x1da1) },   /* Huawei ET8282, Huawei ET127*/
    { USB_DEVICE(0x12d1, 0x1f01) },   /* Huawei E353 (3.se) and others*/
    { USB_DEVICE(0x12d1, 0x1f02) },   /* Huawei E5377*/
    { USB_DEVICE(0x12d1, 0x1f03) },   /* KDDI (Huawei) HWD12 LTE*/
    { USB_DEVICE(0x12d1, 0x1f07) },   /* Huawei/Vodafone R226*/
    { USB_DEVICE(0x12d1, 0x1f09) },   /* Huawei/Vodafone R216*/
    { USB_DEVICE(0x12d1, 0x1f11) },   /* Vodafone / Huawei K3773*/
    { USB_DEVICE(0x12d1, 0x1f15) },   /* Vodafone K4305*/
    { USB_DEVICE(0x12d1, 0x1f16) },   /* Vodafone K5150*/
    { USB_DEVICE(0x12d1, 0x1f17) },   /* Vodafone K4201*/
    { USB_DEVICE(0x12d1, 0x1f18) },   /* Vodafone K4202*/
    { USB_DEVICE(0x12d1, 0x1f19) },   /* Vodafone K4606*/
    { USB_DEVICE(0x12d1, 0x1f1b) },   /* Vodafone / Huawei Kxxxx*/
    { USB_DEVICE(0x12d1, 0x1f1c) },   /* Vodafone / Huawei K4203*/
    { USB_DEVICE(0x12d1, 0x1f1d) },   /* Vodafone / Huawei Kxxxx*/
    { USB_DEVICE(0x12d1, 0x1f1e) },   /* Vodafone / Huawei Kxxxx*/
    { USB_DEVICE(0x12d1, 0x380b) },   /* Huawei BM358 WiMAX*/
    { USB_DEVICE(0x1307, 0x1169) },   /* Cisco AM10 "Valet Connector"*/
    { USB_DEVICE(0x1410, 0x5010) },   /* Novatel Wireless devices*/
    { USB_DEVICE(0x1410, 0x5020) },   /* Novatel MC990D*/
    { USB_DEVICE(0x1410, 0x5023) },   /* Novatel MC996D*/
    { USB_DEVICE(0x1410, 0x5030) },   /* Novatel U760*/
    { USB_DEVICE(0x1410, 0x5031) },   /* Novatel MC760 3G*/
    { USB_DEVICE(0x1410, 0x5041) },   /* Novatel Generic MiFi 2352 / Vodafone MiFi 2352*/
    { USB_DEVICE(0x1410, 0x5055) },   /* Novatel MiFi 4082*/
    { USB_DEVICE(0x1410, 0x5059) },   /* Novatel Wireless MC545 HSPA, U679 LTE*/
    { USB_DEVICE(0x1410, 0x7001) },   /* Novatel Generic MiFi 2372 / Vodafone MiFi 2372*/
    { USB_DEVICE(0x148e, 0xa000) },   /* Sequans SQN1210/SQN1220 (generic chipsets)*/
    { USB_DEVICE(0x148f, 0x2578) },   /* Motorola 802.11 bg WLAN (TER/GUSB3-E)*/
    { USB_DEVICE(0x15eb, 0x7153) },   /* China TeleCom CBP7.0*/
    { USB_DEVICE(0x1614, 0x0800) },   /* Amoi H-01*/
    { USB_DEVICE(0x1614, 0x0802) },   /* Amoi H-02*/
    { USB_DEVICE(0x16d8, 0x6281) },   /* C-motech CHU-628S*/
    { USB_DEVICE(0x16d8, 0x6803) },   /* C-motech D-50 (aka "CDU-680", "CNU-680")*/
    { USB_DEVICE(0x16d8, 0x6804) },   /* C-motech CDU-685a*/
    { USB_DEVICE(0x16d8, 0x700a) },   /* C-motech CHU-629S*/
    { USB_DEVICE(0x16d8, 0x700b) },   /* C-motech CHU-629S (Variant)*/
    { USB_DEVICE(0x16d8, 0xf000) },   /* C-motech CGU-628 (aka "Franklin Wireless CGU-628A" aka "4G Systems XS Stick W12")*/
    { USB_DEVICE(0x1726, 0xf00e) },   /* Axesstel MU130*/
    { USB_DEVICE(0x1782, 0x0003) },   /* Spreadtrum SC7702*/
    { USB_DEVICE(0x198a, 0x0003) },   /* JOA Telecom LM-700r*/
    { USB_DEVICE(0x198f, 0xbccd) },   /* Beceem BCSM250*/
    { USB_DEVICE(0x19d2, 0x0003) },   /* ZTE MU351*/
    { USB_DEVICE(0x19d2, 0x0026) },   /* ZTE AC581*/
    { USB_DEVICE(0x19d2, 0x0040) },   /* Vodafone (ZTE) K2525*/
    { USB_DEVICE(0x19d2, 0x0053) },   /* ZTE MF110 (Variant)*/
    { USB_DEVICE(0x19d2, 0x0083) },   /* ZTE MF110 (Variant)*/
    { USB_DEVICE(0x19d2, 0x0101) },   /* Vodafone (ZTE) K4505-Z*/
    { USB_DEVICE(0x19d2, 0x0103) },   /* ZTE MF112*/
    { USB_DEVICE(0x19d2, 0x0110) },   /* ZTE MF637 (Variant for Orange France)*/
    { USB_DEVICE(0x19d2, 0x0115) },   /* ZTE MF651*/
    { USB_DEVICE(0x19d2, 0x0120) },   /*ZTE-T A356*/
    { USB_DEVICE(0x19d2, 0x0146) },   /* ZTE MF652 (Variant)*/
    { USB_DEVICE(0x19d2, 0x0149) },   /* ZTE MF190 (Variant)*/
    { USB_DEVICE(0x19d2, 0x0150) },   /* ZTE MF656A, MF668A, MF669*/
    { USB_DEVICE(0x19d2, 0x0154) },   /* ZTE MF190 (Variant) and others*/
    { USB_DEVICE(0x19d2, 0x0166) },   /* ZTE MF820 4G LTE*/
    { USB_DEVICE(0x19d2, 0x0169) },   /* ZTE A371B*/
    { USB_DEVICE(0x19d2, 0x0266) },   /* Onda MT8205 LTE*/
    { USB_DEVICE(0x19d2, 0x0304) },   /* ZTE MF821D (Variant)*/
    { USB_DEVICE(0x19d2, 0x0318) },   /* ZTE MF821D/MF826*/
    { USB_DEVICE(0x19d2, 0x0325) },   /* ZTE MF821D*/
    { USB_DEVICE(0x19d2, 0x0388) },   /* ZTE MF90 Mobile Hotspot*/
    { USB_DEVICE(0x19d2, 0x0413) },   /* Telewell TW-LTE 4G*/
    { USB_DEVICE(0x19d2, 0x1001) },   /* Vodafone (ZTE) K3805-Z*/
    { USB_DEVICE(0x19d2, 0x1007) },   /* Vodafone (ZTE) K3570-Z*/
    { USB_DEVICE(0x19d2, 0x1009) },   /* Vodafone (ZTE) K3571-Z*/
    { USB_DEVICE(0x19d2, 0x1013) },   /* Vodafone (ZTE) K3806-Z*/
    { USB_DEVICE(0x19d2, 0x1017) },   /* Vodafone K5006Z (MF821)*/
    { USB_DEVICE(0x19d2, 0x1030) },   /* Vodafone K5008-z (MF823)*/
    { USB_DEVICE(0x19d2, 0x1038) },   /* ZTE / Vodafone K4607-Z*/
    { USB_DEVICE(0x19d2, 0x1171) },   /* Vodafone (ZTE) K4510-Z*/
    { USB_DEVICE(0x19d2, 0x1175) },   /* Vodafone / ZTE K3770-Z*/
    { USB_DEVICE(0x19d2, 0x1179) },   /* Vodafone (ZTE) K3772-Z*/
    { USB_DEVICE(0x19d2, 0x1201) },   /* ZTE MF691 (T-Mobile Rocket 2.0)*/
    { USB_DEVICE(0x19d2, 0x1207) },   /* ZTE MF192 (Variant)*/
    { USB_DEVICE(0x19d2, 0x1210) },   /* ZTE MF195*/
    { USB_DEVICE(0x19d2, 0x1216) },   /* ZTE MF192 (Variant)*/
    { USB_DEVICE(0x19d2, 0x1219) },   /* ZTE MF192 (Variant)*/
    { USB_DEVICE(0x19d2, 0x1224) },   /* ZTE MF190*/
    { USB_DEVICE(0x19d2, 0x1225) },   /* ZTE MF668 (Variant), MF70*/
    { USB_DEVICE(0x19d2, 0x1227) },   /* ZTE MF680*/
    { USB_DEVICE(0x19d2, 0x1232) },   /* ZTE MFxxx*/
    { USB_DEVICE(0x19d2, 0x1233) },   /* ZTE MFxxx*/
    { USB_DEVICE(0x19d2, 0x1237) },   /* ZTE / Vodafone K4201*/
    { USB_DEVICE(0x19d2, 0x1238) },   /* ZTE MF825A*/
    { USB_DEVICE(0x19d2, 0x1420) },   /* ZTE MF730*/
    { USB_DEVICE(0x19d2, 0x1511) },   /* ZTE MFxxx*/
    { USB_DEVICE(0x19d2, 0x1514) },   /* ZTE MF192 (Variant)*/
    { USB_DEVICE(0x19d2, 0x1517) },   /* ZTE MF192 (Variant)*/
    { USB_DEVICE(0x19d2, 0x1520) },   /* ZTE MF652*/
    { USB_DEVICE(0x19d2, 0x1523) },   /* ZTE MF591 TMobile*/
    { USB_DEVICE(0x19d2, 0x1528) },   /* ZTE MF196*/
    { USB_DEVICE(0x19d2, 0x1536) },   /* ZTE MF190J*/
    { USB_DEVICE(0x19d2, 0x1542) },   /* ZTE MF190J*/
    { USB_DEVICE(0x19d2, 0x1588) },   /* ZTE MF710M Variants*/
    { USB_DEVICE(0x19d2, 0x2000) },   /* ZTE devices*/
    { USB_DEVICE(0x19d2, 0x2004) },   /* ZTE MF60*/
    { USB_DEVICE(0x19d2, 0xbccd) },   /* ZTE AX226 WiMax*/
    { USB_DEVICE(0x19d2, 0xffde) },   /* ZTE AC682 (a.k.a. SmartFren Connex)*/
    { USB_DEVICE(0x19d2, 0xffe6) },   /* ZTE "ffe" devices 1 (e.g. Cricket A605)*/
    { USB_DEVICE(0x19d2, 0xfff5) },   /* ZTE "ff" devices 1*/
    { USB_DEVICE(0x19d2, 0xfff6) },   /* ZTE "fff" devices 2*/
    { USB_DEVICE(0x1a8d, 0x1000) },   /* BandRich BandLuxe C100, C120, C170, C270, C3xx, C508*/
    { USB_DEVICE(0x1a8d, 0x2000) },   /* BandRich BandLuxe C339*/
    { USB_DEVICE(0x1ab7, 0x5700) },   /* Hummer DTM5731, Aircard 901 */
    { USB_DEVICE(0x1b7d, 0x0700) },   /* EpiValley SEC-7089 (featured by Alegro and Starcomms / iZAP)*/
    { USB_DEVICE(0x1bbb, 0x000f) },   /* ETCOM E300*/
    { USB_DEVICE(0x1bbb, 0x00ca) },   /* Alcatel OT-X080C*/
    { USB_DEVICE(0x1bbb, 0x011f) },   /* Haier EVDO Rev. A*/
    { USB_DEVICE(0x1bbb, 0x022c) },   /* Alcatel X602D*/
    { USB_DEVICE(0x1bbb, 0xf000) },   /* Alcatel X200/X200L/X060S/L100V, Archos G9 3G Key*/
    { USB_DEVICE(0x1bbb, 0xf017) },   /* Alcatel OT-X220D, L100V*/
    { USB_DEVICE(0x1bbb, 0xf052) },   /* Alcatel OT X220L*/
    { USB_DEVICE(0x1c9e, 0x1001) },   /* Alcatel One Touch X020*/
    { USB_DEVICE(0x1c9e, 0x6000) },   /* TU930, IVIO IV-2010u*/
    { USB_DEVICE(0x1c9e, 0x6061) },   /* Vibe 3G Modem */
    { USB_DEVICE(0x1c9e, 0x9101) },   /* Emobile D12LC*/
    { USB_DEVICE(0x1c9e, 0x9200) },   /* MyWave SW006 Sport Phone/Modem Combination*/
    { USB_DEVICE(0x1c9e, 0x9401) },   /* Emobile D21LC*/
    { USB_DEVICE(0x1c9e, 0x9800) },   /* Longcheer SU9800*/
    { USB_DEVICE(0x1c9e, 0x98ff) },   /* Telewell TW-3G HSPA+, FS01BU 3G, SmartBro WM66E*/
    { USB_DEVICE(0x1c9e, 0x9d00) },   /* Prolink PCM100*/
    { USB_DEVICE(0x1c9e, 0x9e00) },   /* BSNL Capitel*/
    { USB_DEVICE(0x1c9e, 0x9e08) },   /* Explay Slim*/
    { USB_DEVICE(0x1c9e, 0xf000) },   /* MobiData MBD-200HU and others*/
    { USB_DEVICE(0x1c9e, 0xf000) },   /* Longcheer/Longsoon (aka Omega Technology) devices*/
    { USB_DEVICE(0x1d09, 0x1000) },   /* TechFaith BSNL Capitel*/
    { USB_DEVICE(0x1d09, 0x1021) },   /* Aiko 81D*/
    { USB_DEVICE(0x1d09, 0x1025) },   /* TechFaith FlyingLARK46*/
    { USB_DEVICE(0x1da5, 0xf000) },   /* Qisda H21 Flying Beetle*/
    { USB_DEVICE(0x1dbc, 0x0669) },   /* Wisue W340*/
    { USB_DEVICE(0x1dd6, 0x1000) },   /* Solomon S3Gm-660*/
    { USB_DEVICE(0x1de1, 0x1101) },   /* Philips PicoPix 1020 Projector*/
    { USB_DEVICE(0x1e0e, 0xf000) },   /* Option iCON 210, PROLiNK PHS100 + PH300, Hyundai MB-810, A-Link 3GU*/
    { USB_DEVICE(0x1e89, 0xf000) },   /* 3GO 3GO11 HSUPA*/
    { USB_DEVICE(0x1edf, 0x6003) },   /* AirPlus MCD-800*/
    { USB_DEVICE(0x1ee8, 0x0003) },   /* Onda MV815U*/
    { USB_DEVICE(0x1ee8, 0x0009) },   /* Onda MW833UP*/
    { USB_DEVICE(0x1ee8, 0x0013) },   /* Onda MW833UP + MW835UP*/
    { USB_DEVICE(0x1ee8, 0x0018) },   /* Onda MO835UP*/
    { USB_DEVICE(0x1ee8, 0x0040) },   /* Onda MW836UP-K*/
    { USB_DEVICE(0x1ee8, 0x0045) },   /* Onda MDC655*/
    { USB_DEVICE(0x1ee8, 0x004a) },   /* Onda MDC655*/
    { USB_DEVICE(0x1ee8, 0x004f) },   /* Onda MDC655 Variant*/
    { USB_DEVICE(0x1ee8, 0x0054) },   /* Onda MW875UP*/
    { USB_DEVICE(0x1ee8, 0x0060) },   /* Onda MSA 14.4 (TIM Brasil)*/
    { USB_DEVICE(0x1ee8, 0x0063) },   /* Onda TM201 14.4 (TIM Italy)*/
    { USB_DEVICE(0x1ee8, 0x0068) },   /* Onda WM301*/
    { USB_DEVICE(0x1f28, 0x0021) },   /* Cricket A600*/
    { USB_DEVICE(0x1fac, 0x0032) },   /* Franklin Wireless U210 (Variant)*/
    { USB_DEVICE(0x1fac, 0x0130) },   /* Franklin Wireless U210*/
    { USB_DEVICE(0x1fac, 0x0150) },   /* Franklin Wireless U600*/
    { USB_DEVICE(0x1fac, 0x0151) },   /* Franklin Wireless U600*/
    { USB_DEVICE(0x2001, 0x00a6) },   /* D-Link DWM-157 B1*/
    { USB_DEVICE(0x2001, 0x98ff) },   /* D-Link DWM-221*/
    { USB_DEVICE(0x2001, 0xa401) },   /* D-Link DWM-221 B1*/
    { USB_DEVICE(0x2001, 0xa403) },   /* D-Link DWM-156 A8, DWP-157 B1*/
    { USB_DEVICE(0x2001, 0xa405) },   /* D-Link DWM-167 A1*/
    { USB_DEVICE(0x2001, 0xa706) },   /* D-Link DWM-156 A7*/
    { USB_DEVICE(0x2001, 0xa707) },   /* D-Link DWM-157 B1*/
    { USB_DEVICE(0x2001, 0xa708) },   /* D-Link DWM-158 D1*/
    { USB_DEVICE(0x2001, 0xa805) },   /* D-Link DWR-510*/
    { USB_DEVICE(0x2001, 0xa80b) },   /* D-Link DWM-156 (Variant)*/
    { USB_DEVICE(0x201e, 0x1023) },   /* Haier CE682 (EVDO)*/
    { USB_DEVICE(0x201e, 0x2009) },   /* Haier CE 100 */
    { USB_DEVICE(0x2020, 0x0002) },   /* Mediatek MT6229, Micromax MMX 377G, Olicard 300*/
    { USB_DEVICE(0x2020, 0xf00e) },   /* SpeedUp SU-8000*/
    { USB_DEVICE(0x2020, 0xf00f) },   /* SpeedUp SU-8000U*/
    { USB_DEVICE(0x2077, 0x1000) },   /* Changhong CH690, D-Link DWM-163 + DWM-168*/
    { USB_DEVICE(0x2077, 0xf000) },   /* Telenet 3G dongle (T&W WU160) and others*/
    { USB_DEVICE(0x20a6, 0xf00e) },   /* Intex 3.5G*/
    { USB_DEVICE(0x20b9, 0x1682) },   /* Tlaytech TEU800*/
    { USB_DEVICE(0x21f5, 0x1000) },   /* StrongRising (China Telcom), Air FlexiNet*/
    { USB_DEVICE(0x21f5, 0x3010) },   /* StrongRising STD808*/
    { USB_DEVICE(0x2262, 0x0001) },   /* Viettel VT100*/
    { USB_DEVICE(0x22de, 0x6801) },   /* WeTelecom WM-D200*/
    { USB_DEVICE(0x22de, 0x6803) },   /* WeTelecom WM-D300*/
    { USB_DEVICE(0x22f4, 0x0021) },   /* Tata Photon+*/
    { USB_DEVICE(0x230d, 0x0001) },   /* Linktop LW272/LW273 (BSNL Teracom)*/
    { USB_DEVICE(0x230d, 0x0003) },   /* Linktop LW272/LW273 (BSNL Teracom)*/
    { USB_DEVICE(0x230d, 0x0007) },   /* Visiontek 82GH 3G*/
    { USB_DEVICE(0x230d, 0x000b) },   /* Zoom 3G*/
    { USB_DEVICE(0x230d, 0x000d) },   /* Intex Speed 3G v7.2*/
    { USB_DEVICE(0x230d, 0x0101) },   /* Linktop LW272/LW273*/
    { USB_DEVICE(0x230d, 0x0103) },   /* Teracom LW272*/
    { USB_DEVICE(0x2357, 0x0200) },   /* TP-Link MA180*/
    { USB_DEVICE(0x2357, 0xf000) },   /* TP-Link MA260*/
    { USB_DEVICE(0x23a2, 0x1010) },   /* Titan 3.5G*/
    { USB_DEVICE(0x257a, 0xa000) },   /* Unknown devices*/
    { USB_DEVICE(0x257a, 0xb000) },   /* Unknown devices*/
    { USB_DEVICE(0x257a, 0xc000) },   /* Unknown devices*/
    { USB_DEVICE(0x257a, 0xd000) },   /* Unknown devices*/
    { USB_DEVICE(0x8888, 0x6500) },   /* Exiss Mobile E-190 series (made by C-motech)*/
    { USB_DEVICE(0xed09, 0x1021) },   /* Aiko 81D, fw with wrong vendor ID*/
    { } /* Terminating entry */
};






char show_progress=1;


struct usb_modeswitch
{
    int DefaultVendor;
    int DefaultProduct;
    int MessageEndpoint;
    int ResponseEndpoint;
    int ReleaseDelay;

    //int PantechMode=0;
    char NeedResponse;
    char StandardEject;
    unsigned int ModeMap;


    char MessageContent[80];   //enough
    char MessageContent2[80];  //enough
    char MessageContent3[80];  //enough
    char ByteString[80];       //enough
};
//int DefaultVendor=0, DefaultProduct=0;
//int MessageEndpoint=0, ResponseEndpoint=0, ReleaseDelay=0;

////int PantechMode=0;
//char NeedResponse=0;
//char StandardEject=0;
//unsigned int ModeMap = 0;



//static char MessageContent[80];   //enough
//static char MessageContent2[80];  //enough
//static char MessageContent3[80];  //enough
//static char ByteString[80];









const struct device_refer *match_device_refer(struct usb_interface *interface,
        const struct usb_device_id *id)
{
    const struct device_refer *refer = device_refer_tbl;
    char *pos;
    char buffer[32];

    for (; refer->DefaultProduct || refer->DefaultVendor; refer++)
    {
        if ((refer->DefaultProduct == id->idProduct)
            && (refer->DefaultVendor == id->idVendor))
        {
            if(!refer->uMa && !refer->uPr)
                return refer;

            if(refer->uMa)
            {
                if(strstr(interface->usb_dev->manufacturer, refer->uMa))
                    return refer;

                strncpy(buffer, refer->uMa, sizeof(buffer));
                for(pos= buffer; *pos != '\0'; pos++)
                {
                    if(*pos == '_')
                        *pos = ' ';
                }

                if(strstr(interface->usb_dev->manufacturer, buffer))
                    return refer;
            }

            if(refer->uPr)
            {
                if(strstr(interface->usb_dev->product, refer->uPr))
                    return refer;

                strncpy(buffer, refer->uPr, sizeof(buffer));
                for(pos= buffer; *pos != '\0'; pos++)
                {
                    if(*pos == '_')
                        *pos = ' ';
                }

                if(strstr(interface->usb_dev->product, buffer))
                    return refer;
            }
        }
    }


    return NULL;
}


/* Autodetect bulk endpoints (ab) */

static int find_first_bulk_endpoint(struct usb_interface *intf, int direction)
{
    int i;
    const struct usb_host_endpoint  *ep;


    for(i=0; i < intf->altsetting[0].desc.bNumEndpoints; i++)
    {
        ep=&(intf->altsetting[0].endpoint[i]);
        if( ( (ep->desc.bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) == USB_ENDPOINT_XFER_BULK) &&
            ( (ep->desc.bEndpointAddress & USB_ENDPOINT_DIR_MASK) == direction ) )
        {
            return ep->desc.bEndpointAddress;
        }
    }

    return 0;
}


static int usb_bulk_io(struct usb_interface *intf, int ep, char *bytes,
                       int size, int timeout)
{
    unsigned int pipe;
    int actual_length;
    int r;
//  usbi_dbg("endpoint %x size %d timeout %d", ep, size, timeout);
//  r = libusb_bulk_transfer(handle, ep & 0xff, (unsigned char *)bytes, size,
//      &actual_length, timeout);

    pipe = (PIPE_BULK << 30) | __create_pipe(intf->usb_dev, ep & 0xf) | (ep & USB_DIR_IN);
    r = usb_bulk_msg(intf->usb_dev, pipe, bytes, size, &actual_length, timeout);


    /* if we timed out but did transfer some data, report as successful short
     * read. FIXME: is this how libusb-0.1 works? */
    if (r == 0 || (r == -ETIMEDOUT && actual_length > 0))
        return actual_length;

    return r;
}

static int usb_interrupt_io(struct usb_interface *intf, int ep, char *bytes,
                            int size, int timeout)
{
    unsigned int pipe;
    int actual_length;
    int r;
//  usbi_dbg("endpoint %x size %d timeout %d", ep, size, timeout);
//  r = libusb_interrupt_transfer(handle, ep & 0xff, (unsigned char *)bytes, size,
//      &actual_length, timeout);

    pipe = (PIPE_INTERRUPT << 30) | __create_pipe(intf->usb_dev, ep & 0xf) | (ep & USB_DIR_IN);
    r = usb_interrupt_msg(intf->usb_dev, pipe, bytes, size, &actual_length, timeout);


    /* if we timed out but did transfer some data, report as successful short
     * read. FIXME: is this how libusb-0.1 works? */
    if (r == 0 || (r == -ETIMEDOUT && actual_length > 0))
        return actual_length;

    return (r);
}


static int write_bulk(struct usb_interface *intf, int endpoint, char *message, int length)
{
    int ret = usb_bulk_io(intf, endpoint, message, length, 3000);
    if (ret >= 0 )
    {
        SHOW_PROGRESS(stdout," OK, message successfully sent\n");
    }
    else if (ret == -ENODEV)
    {
        SHOW_PROGRESS(stdout," Device seems to have vanished right after sending. Good.\n");
    }
    else
        SHOW_PROGRESS(stdout," Sending the message returned error %d. Try to continue\n", ret);
    return ret;

}

static int read_bulk(struct usb_interface *intf, int endpoint, char *buffer, int length)
{
    int ret = usb_bulk_io(intf, endpoint, buffer, length, 3000);
    if (ret >= 0 )
    {
        SHOW_PROGRESS(stdout," Response successfully read (%d bytes).\n", ret);
    }
    else if (ret == -ENODEV)
    {
        SHOW_PROGRESS(stdout," Device seems to have vanished after reading. Good.\n");
    }
    else
        SHOW_PROGRESS(stdout," Response reading failed (error %d)\n", ret);
    return ret;

}
static int hex2num(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    return -1;
}


static int hex2byte(const char *hex)
{
    int a, b;
    a = hex2num(*hex++);
    if (a < 0)
        return -1;
    b = hex2num(*hex++);
    if (b < 0)
        return -1;
    return (a << 4) | b;
}

static int hexstr2bin(const char *hex, char *buffer, int len)
{
    int i;
    int a;
    const char *ipos = hex;
    char *opos = buffer;

    for (i = 0; i < len; i++)
    {
        a = hex2byte(ipos);
        if (a < 0)
            return -1;
        *opos++ = a;
        ipos += 2;
    }
    return 0;
}

static int sendMessage(struct usb_modeswitch *mswitch, struct usb_interface *intf, char* message, int count)
{
    int ret, message_length;

    if (strlen(message) % 2 != 0)
    {
        fprintf(stderr, "Error: MessageContent %d hex string has uneven length. Skipping ...\n", count);
        return 1;
    }
    message_length = strlen(message) / 2;

    if(message_length > sizeof(mswitch->ByteString))
        return 1;

    if ( hexstr2bin(message, mswitch->ByteString, message_length) == -1)
    {
        fprintf(stderr, "Error: MessageContent %d %s\n is not a hex string. Skipping ...\n", count, message);
        return 1;
    }
    SHOW_PROGRESS(stdout,"Trying to send message %d to endpoint 0x%02x ...\n", count, mswitch->MessageEndpoint);

    ret = write_bulk(intf, mswitch->MessageEndpoint, mswitch->ByteString, message_length);
    if (ret == -ENODEV)
        return 1;

    return 0;
}


static int create_bulk_pipe(struct usb_device *dev, unsigned int ep)
{
   	if (ep & USB_DIR_IN)
		return usb_rcvbulkpipe(dev, ep & 0x7f);
	else
		return usb_sndbulkpipe(dev, ep & 0x7f); 
    
}

static int switchSendMessage (struct usb_modeswitch *mswitch, struct usb_interface *intf)
{
    const char* cmdHead = "55534243";
    int ret, i;
    char* msg[3];
    msg[0] = mswitch->MessageContent;
    msg[1] = mswitch->MessageContent2;
    msg[2] = mswitch->MessageContent3;

    /* May be activated in future versions */
//  if (MessageContent2[0] != '\0' || MessageContent3[0] != '\0')
//      NeedResponse = 1;

    SHOW_PROGRESS(stdout,"Set up interface %d\n", intf->altsetting[0].desc.bInterfaceNumber);



    usb_clear_halt(intf->usb_dev, create_bulk_pipe(intf->usb_dev, mswitch->MessageEndpoint));



    SHOW_PROGRESS(stdout,"Use endpoint 0x%02x for message sending ...\n", mswitch->MessageEndpoint);


    for (i=0; i<3; i++)
    {
        if (strlen(msg[i]) == 0)
            continue;

        if ( sendMessage(mswitch, intf, msg[i], i+1) )
            return 1;

        if (mswitch->NeedResponse)
        {
            if ( strstr(msg[i],cmdHead) != NULL )
            {
                // UFI command
                SHOW_PROGRESS(stdout,"Read the response to message %d (CSW) ...\n", i+1);
                ret = read_bulk(intf, mswitch->ResponseEndpoint, mswitch->ByteString, 13);
            }
            else
            {
                // Other bulk transfer
                SHOW_PROGRESS(stdout,"Read the response to message %d ...\n", i+1);
                ret = read_bulk(intf, mswitch->ResponseEndpoint, mswitch->ByteString, strlen(msg[i])/2 );
            }
            if (ret < 0)
                return 2;
        }
    }

    SHOW_PROGRESS(stdout,"Reset response endpoint 0x%02x\n", mswitch->ResponseEndpoint);

    ret = usb_clear_halt(intf->usb_dev, create_bulk_pipe(intf->usb_dev, mswitch->ResponseEndpoint));
    if (ret)
        SHOW_PROGRESS(stdout," Could not reset endpoint (probably harmless): %d\n", ret);
    SHOW_PROGRESS(stdout,"Reset message endpoint 0x%02x\n", mswitch->MessageEndpoint);
    
    ret = usb_clear_halt(intf->usb_dev, create_bulk_pipe(intf->usb_dev, mswitch->MessageEndpoint));
    if (ret)
        SHOW_PROGRESS(stdout," Could not reset endpoint (probably harmless): %d\n", ret);
    msleep(50);

    if (mswitch->ReleaseDelay)
    {
        SHOW_PROGRESS(stdout,"Wait for %d ms before releasing interface ...\n", mswitch->ReleaseDelay);
        msleep(mswitch->ReleaseDelay);
    }

    return 1;


}


static int switchHuaweiMode (struct usb_interface *intf)
{
    int ret;
    SHOW_PROGRESS(stdout,"Send old Huawei control message ...\n");
//  ret = libusb_control_transfer(devh, LIBUSB_REQUEST_TYPE_STANDARD | LIBUSB_RECIPIENT_DEVICE, \
//      LIBUSB_REQUEST_SET_FEATURE, 00000001, 0, (unsigned char *)buffer, 0, 1000);
    ret =  usb_control_msg(intf->usb_dev,usb_sndctrlpipe(intf->usb_dev,0), USB_REQ_SET_FEATURE,
                           USB_RECIP_DEVICE | USB_TYPE_STANDARD,
                           00000001, 0, NULL, 0, 1000);

    if (ret < 0)
    {
        fprintf(stderr, "Error: Huawei control message failed (error %d). Abort\n\n", ret);
        return -1;
    }

    return 0;
}

static int switchSierraMode (struct usb_interface *intf)
{
    int ret;
    SHOW_PROGRESS(stdout,"Send Sierra control message\n");
//  ret = libusb_control_transfer(devh, LIBUSB_REQUEST_TYPE_VENDOR, 0x0b, 00000001, 0, (unsigned char *)buffer, 0, 1000);
    ret =  usb_control_msg(intf->usb_dev,usb_sndctrlpipe(intf->usb_dev,0), 0x0b, USB_TYPE_VENDOR, 00000001, 0, NULL, 0, 1000);


    if (ret < 0)
    {
        fprintf(stderr, "Error: Sierra control message failed (error %d). Abort\n\n", ret);
        return -1;
    }

    return 0;
}


static int switchGCTMode (struct usb_interface *intf)
{
    int ret;
    char buffer[32];

    SHOW_PROGRESS(stdout,"Send GCT control message 1 ...\n");
//  ret = libusb_control_transfer(devh, 0xa1, 0xa0, 0, Interface, (unsigned char *)buffer, 1, 1000);
    ret =  usb_control_msg(intf->usb_dev,usb_sndctrlpipe(intf->usb_dev,0), 0xa0, 0xa1, 0, intf->altsetting[0].desc.bInterfaceNumber, buffer, 1, 1000);
    if (ret < 0)
    {
        SHOW_PROGRESS(stdout," GCT control message 1 failed (error %d), continue anyway ...\n", ret);
    }
    SHOW_PROGRESS(stdout,"Send GCT control message 2 ...\n");
//  ret = libusb_control_transfer(devh, 0xa1, 0xfe, 0, Interface, (unsigned char *)buffer, 1, 1000);
    ret =  usb_control_msg(intf->usb_dev,usb_sndctrlpipe(intf->usb_dev,0), 0xfe, 0xa1, 0, intf->altsetting[0].desc.bInterfaceNumber, buffer, 1, 1000);
    if (ret < 0)
    {
        SHOW_PROGRESS(stdout," GCT control message 2 failed (error %d). Abort\n\n", ret);
    }

    if (ret < 0)
        return -1;

    return 0;
}



static int switchKobilMode(struct usb_interface *intf)
{
    int ret;
    char buffer[32];

    SHOW_PROGRESS(stdout,"Send Kobil control message ...\n");
//  ret = libusb_control_transfer(devh, LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_RECIPIENT_DEVICE | LIBUSB_ENDPOINT_IN,
//          0x88, 0, 0, (unsigned char *)buffer, 8, 1000);
    ret =  usb_control_msg(intf->usb_dev,usb_rcvctrlpipe(intf->usb_dev,0), 0x88,
                           USB_RECIP_DEVICE | USB_TYPE_VENDOR | USB_DIR_IN,
                           0, 0, buffer, 8, 1000);
    if (ret < 0)
    {
        fprintf(stderr, "Error: Kobil control message failed (error %d). Abort\n\n", ret);
        return -1;
    }

    return 0;
}


static int switchQisdaMode (struct usb_interface *intf)
{
    int ret;
    char buffer[32];

    SHOW_PROGRESS(stdout,"Sending Qisda control message ...\n");
    memcpy(buffer, "\x05\x8c\x04\x08\xa0\xee\x20\x00\x5c\x01\x04\x08\x98\xcd\xea\xbf", 16);
//  ret = libusb_control_transfer(devh, 0x40, 0x04, 0, 0, (unsigned char *)buffer, 16, 1000);
    ret =  usb_control_msg(intf->usb_dev,usb_sndctrlpipe(intf->usb_dev,0), 0x04, 0x40, 0, 0, buffer, 16, 1000);
    if (ret < 0)
    {
        fprintf(stderr, "Error: Qisda control message failed (error %d). Abort\n\n", ret);
        return -1;
    }

    return 0;
}


static int switchQuantaMode(struct usb_interface *intf)
{
    int ret;
    SHOW_PROGRESS(stdout,"Send Quanta control message ...\n");
//  ret = libusb_control_transfer(devh, LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_RECIPIENT_DEVICE | LIBUSB_ENDPOINT_IN,
//          0xff, 0, 0, (unsigned char *)buffer, 0, 1000);
    ret =  usb_control_msg(intf->usb_dev,usb_rcvctrlpipe(intf->usb_dev,0), 0xff,
                           USB_RECIP_DEVICE | USB_TYPE_VENDOR | USB_DIR_IN,
                           0, 0, NULL, 0, 1000);
    if (ret < 0)
    {
        SHOW_PROGRESS(stdout,"Error: Quanta control message failed (error %d). Abort\n\n", ret);
        return -1;
    }

    return 0;
}


static int switchBlackberryMode (struct usb_interface *intf)
{
    int ret;
    char buffer[32];

    SHOW_PROGRESS(stdout,"Send Blackberry control message 1 ...\n");
//  ret = libusb_control_transfer(devh, LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_RECIPIENT_DEVICE | LIBUSB_ENDPOINT_IN,
//          0xb1, 0x0000, 0, (unsigned char *)buffer, 8, 1000);
    ret =  usb_control_msg(intf->usb_dev,usb_rcvctrlpipe(intf->usb_dev,0), 0xb1,
                           USB_RECIP_DEVICE | USB_TYPE_VENDOR | USB_DIR_IN,
                           0, 0, buffer, 8, 1000);
    if (ret != 8)
    {
        fprintf(stderr, "Error: Blackberry control message 1 failed (result %d)\n", ret);
    }
    SHOW_PROGRESS(stdout,"Send Blackberry control message 2 ...\n");
//  ret = libusb_control_transfer(devh, LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_RECIPIENT_DEVICE | LIBUSB_ENDPOINT_IN,
//          0xa9, 0x000e, 0, (unsigned char *)buffer, 2, 1000);
    ret =  usb_control_msg(intf->usb_dev,usb_rcvctrlpipe(intf->usb_dev,0), 0xa9,
                           USB_RECIP_DEVICE | USB_TYPE_VENDOR | USB_DIR_IN,
                           0x000e, 0, buffer, 2, 1000);
    if (ret != 2)
    {
        fprintf(stderr, "Error: Blackberry control message 2 failed (result %d). Abort\n\n", ret);
        return -1;
    }

    return 0;
}


//static int switchPantechMode(struct usb_interface *intf)
//{
//  int ret;
//
//  SHOW_PROGRESS(stdout,"Send Pantech control message, wValue %d ...\n", PantechMode);
// //   ret = libusb_control_transfer(devh, LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_RECIPIENT_DEVICE, 0x70, PantechMode, 0, (unsigned char *)buffer, 0, 1000);
//    ret =  usb_control_msg(intf->usb_dev,usb_sndctrlpipe(intf->usb_dev,0), 0x70,
//                             USB_REQ_RECIPIENT_DEVICE | USB_REQ_TYPE_VENDOR,
//                              PantechMode, 0, NULL, 0, 1000);
//    if (ret < 0) {
//      SHOW_PROGRESS(stdout," Error: Pantech control message failed (error %d). Abort\n\n", ret);
//      return -1;
//  }

//    return 0;
//}




#define EP_OUT 0x02
#define EP_IN 0x81
#define SIZE 0x08

#define MOBILE_ACTION_READLOOP1 63
#define MOBILE_ACTION_READLOOP2 73

/* If anyone can test the MobileAction cable - I bet this
 * function (which is confirmed working) can be greatly
 * simplified ...
 */

static void switchActionMode (struct usb_interface *intf)
{
    int ret, i;
    char buffer[32];

    SHOW_PROGRESS(stdout,"Send MobileAction control sequence ...\n");
    memcpy(buffer, "\xb0\x04\x00\x00\x02\x90\x26\x86", SIZE);
//  libusb_control_transfer(devh, LIBUSB_REQUEST_TYPE_CLASS + LIBUSB_RECIPIENT_INTERFACE, 0x09, 0x0300, 0, (unsigned char *)buffer, SIZE, 1000);
    usb_control_msg(intf->usb_dev,usb_sndctrlpipe(intf->usb_dev,0), 0x09,
                    USB_RECIP_INTERFACE | USB_TYPE_CLASS,
                    0x0300, 0, buffer, SIZE, 1000);


    memcpy(buffer, "\xb0\x04\x00\x00\x02\x90\x26\x86", SIZE);
//  libusb_control_transfer(devh, LIBUSB_REQUEST_TYPE_CLASS + LIBUSB_RECIPIENT_INTERFACE, 0x09, 0x0300, 0, (unsigned char *)buffer, SIZE, 1000);
    usb_control_msg(intf->usb_dev,usb_sndctrlpipe(intf->usb_dev,0), 0x09,
                    USB_RECIP_INTERFACE | USB_TYPE_CLASS,
                    0x0300, 0, buffer, SIZE, 1000);

    usb_interrupt_io(intf, EP_IN, buffer, SIZE, 1000);
    usb_interrupt_io(intf, EP_IN, buffer, SIZE, 1000);
    memcpy(buffer, "\x37\x01\xfe\xdb\xc1\x33\x1f\x83", SIZE);
    usb_interrupt_io(intf, EP_OUT, buffer, SIZE, 1000);
    usb_interrupt_io(intf, EP_IN, buffer, SIZE, 1000);
    memcpy(buffer, "\x37\x0e\xb5\x9d\x3b\x8a\x91\x51", SIZE);
    usb_interrupt_io(intf, EP_OUT, buffer, SIZE, 1000);
    usb_interrupt_io(intf, EP_IN, buffer, SIZE, 1000);
    memcpy(buffer, "\x34\x87\xba\x0d\xfc\x8a\x91\x51", SIZE);
    usb_interrupt_io(intf, EP_OUT, buffer, SIZE, 1000);
    for (i=0; i < MOBILE_ACTION_READLOOP1; i++)
    {
        usb_interrupt_io(intf, EP_IN, buffer, SIZE, 1000);
    }
    memcpy(buffer, "\x37\x01\xfe\xdb\xc1\x33\x1f\x83", SIZE);
    usb_interrupt_io(intf, EP_OUT, buffer, SIZE, 1000);
    usb_interrupt_io(intf, EP_IN, buffer, SIZE, 1000);
    memcpy(buffer, "\x37\x0e\xb5\x9d\x3b\x8a\x91\x51", SIZE);
    usb_interrupt_io(intf, EP_OUT, buffer, SIZE, 1000);
    usb_interrupt_io(intf, EP_IN, buffer, SIZE, 1000);
    memcpy(buffer, "\x34\x87\xba\x0d\xfc\x8a\x91\x51", SIZE);
    usb_interrupt_io(intf, EP_OUT, buffer, SIZE, 1000);
    for (i=0; i < MOBILE_ACTION_READLOOP2; i++)
    {
        usb_interrupt_io(intf, EP_IN, buffer, SIZE, 1000);
    }
    memcpy(buffer, "\x33\x04\xfe\x00\xf4\x6c\x1f\xf0", SIZE);
    usb_interrupt_io(intf, EP_OUT, buffer, SIZE, 1000);
    usb_interrupt_io(intf, EP_IN, buffer, SIZE, 1000);
    memcpy(buffer, "\x32\x07\xfe\xf0\x29\xb9\x3a\xf0", SIZE);
    ret = usb_interrupt_io(intf, EP_OUT, buffer, SIZE, 1000);
    usb_interrupt_io(intf, EP_IN, buffer, SIZE, 1000);
    if (ret < 0)
    {
        SHOW_PROGRESS(stdout," MobileAction control sequence did not complete\n Last error was %d\n",ret);
    }
    else
    {
        SHOW_PROGRESS(stdout," MobileAction control sequence complete\n");
    }
}




#define SQN_SET_DEVICE_MODE_REQUEST     0x0b
#define SQN_GET_DEVICE_MODE_REQUEST     0x0a

#define SQN_DEFAULT_DEVICE_MODE         0x00
#define SQN_MASS_STORAGE_MODE           0x01
#define SQN_CUSTOM_DEVICE_MODE          0x02

static int switchSequansMode(struct usb_interface *intf)
{

    int ret;
    SHOW_PROGRESS(stdout,"Send Sequans control message\n");
//  ret = libusb_control_transfer(devh, LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_RECIPIENT_DEVICE, SQN_SET_DEVICE_MODE_REQUEST, SQN_CUSTOM_DEVICE_MODE, 0, (unsigned char *)buffer, 0, 1000);
    ret = usb_control_msg(intf->usb_dev,usb_sndctrlpipe(intf->usb_dev,0), SQN_SET_DEVICE_MODE_REQUEST,
                          USB_RECIP_DEVICE | USB_TYPE_VENDOR,
                          SQN_CUSTOM_DEVICE_MODE, 0, NULL, 0, 1000);

    if (ret < 0)
    {
        fprintf(stderr, "Error: Sequans request failed (error %d). Abort\n\n", ret);
        return -1;
    }

    return 0;
}

static void switchCiscoMode(struct usb_modeswitch *mswitch, struct usb_interface *intf)
{
    int ret, i;
    char* msg[11];

    msg[0] = "55534243f83bcd810002000080000afd000000030000000100000000000000";
    msg[1] = "55534243984300820002000080000afd000000070000000100000000000000";
    msg[2] = "55534243984300820000000000000afd000100071000000000000000000000";
    msg[3] = "55534243984300820002000080000afd000200230000000100000000000000";
    msg[4] = "55534243984300820000000000000afd000300238200000000000000000000";
    msg[5] = "55534243984300820002000080000afd000200260000000100000000000000";
    msg[6] = "55534243984300820000000000000afd00030026c800000000000000000000";
    msg[7] = "55534243d84c04820002000080000afd000010730000000100000000000000";
    msg[8] = "55534243d84c04820002000080000afd000200240000000100000000000000";
    msg[9] = "55534243d84c04820000000000000afd000300241300000000000000000000";
    msg[10] = "55534243d84c04820000000000000afd000110732400000000000000000000";


    for (i=0; i<11; i++)
    {
        if ( sendMessage(mswitch, intf, msg[i], i+1) )
            return;

        SHOW_PROGRESS(stdout," Read the response (CSW) to bulk message %d ...\n",i+1);
        ret = read_bulk(intf, mswitch->ResponseEndpoint, mswitch->ByteString, 13);
        if (ret < 0)
            return;
        if (ret < 13)
        {
            SHOW_PROGRESS(stdout," Repeat reading the response to bulk message %d ...\n",i+1);
            ret = read_bulk(intf, mswitch->ResponseEndpoint, mswitch->ByteString, 13);
        }
        if (ret < 13)
        {
            SHOW_PROGRESS(stdout," Repeat reading the response to bulk message %d ...\n",i+1);
            ret = read_bulk(intf, mswitch->ResponseEndpoint, mswitch->ByteString, 13);
        }
    }

    if (mswitch->ReleaseDelay)
    {
        SHOW_PROGRESS(stdout,"Wait for %d ms before releasing interface ...\n", mswitch->ReleaseDelay);
        msleep(mswitch->ReleaseDelay);
    }

    return;
}






static int usb_modeswitch(struct usb_modeswitch *mswitch, struct usb_interface *intf, const struct device_refer *refer)
{
    int defaultClass=0, interfaceClass=0;


    mswitch->MessageContent[0] = '\0';
    mswitch->MessageContent2[0] = '\0';
    mswitch->MessageContent3[0] = '\0';




    mswitch->DefaultVendor = refer->DefaultVendor;
    mswitch->DefaultProduct = refer->DefaultProduct;


    if(refer->MessageContent)
        strcpy(mswitch->MessageContent, refer->MessageContent);
    if(refer->MessageContent2)
        strcpy(mswitch->MessageContent2, refer->MessageContent2);
    if(refer->MessageContent3)
        strcpy(mswitch->MessageContent3, refer->MessageContent3);

    mswitch->ModeMap = refer->ModeMap;
    mswitch->NeedResponse = refer->NeedResponse;
    mswitch->StandardEject = refer->StandardEject;

    /* Some sanity checks. The default IDs are mandatory */
    if (!(mswitch->DefaultVendor && mswitch->DefaultProduct))
    {
        SHOW_PROGRESS(stdout,"No default vendor/product ID given. Abort\n\n");
        return -2;
    }

    if (strlen(mswitch->MessageContent) )
    {
        if (strlen(mswitch->MessageContent) % 2 != 0)
        {
            fprintf(stderr, "Error: MessageContent hex string has uneven length. Abort\n\n");
            return -3;
        }

        if((strlen(mswitch->MessageContent)/2) > sizeof(mswitch->ByteString))
        {
            fprintf(stderr, "Error: strlen(MessageContent)/2:%d is not less than sizeof(ByteString):%d\n\n", strlen(mswitch->MessageContent)/2, sizeof(mswitch->ByteString));
            return -4;
        }

        if ( hexstr2bin(mswitch->MessageContent, mswitch->ByteString, strlen(mswitch->MessageContent)/2) == -1)
        {
            fprintf(stderr, "Error: MessageContent %s\n is not a hex string. Abort\n\n", mswitch->MessageContent);
            return -5;
        }
    }



    defaultClass = intf->usb_dev->descriptor.bDeviceClass;
    SHOW_PROGRESS(stdout,"Use interface number %d\n", intf->altsetting[0].desc.bInterfaceNumber);

    /* Get class of default device/interface */
    interfaceClass = intf->altsetting[0].desc.bInterfaceClass;




    /* Check or get endpoints */
    if (strlen(mswitch->MessageContent)  || mswitch->StandardEject || mswitch->ModeMap & CISCO_MODE || mswitch->ModeMap & HUAWEINEW_MODE)
    {
        if (!mswitch->MessageEndpoint)
            mswitch->MessageEndpoint = find_first_bulk_endpoint(intf, USB_DIR_OUT);
        if (!mswitch->ResponseEndpoint)
            mswitch->ResponseEndpoint = find_first_bulk_endpoint(intf, USB_DIR_IN);
        if (!mswitch->MessageEndpoint)
        {
            fprintf(stderr,"Error: message endpoint not given or found. Abort\n\n");
            return -6;
        }
        if (!mswitch->ResponseEndpoint)
        {
            fprintf(stderr,"Error: response endpoint not given or found. Abort\n\n");
            return -7;
        }
        SHOW_PROGRESS(stdout,"Use endpoints 0x%02x (out) and 0x%02x (in)\n", mswitch->MessageEndpoint, mswitch->ResponseEndpoint);
    }


    if (interfaceClass == -1)
    {
        fprintf(stderr, "Error: Could not get class of interface %d. Does it exist? Abort\n\n",intf->altsetting[0].desc.bInterfaceNumber);
        return -8;
    }

    if (defaultClass == 0)
        defaultClass = interfaceClass;
    else if (interfaceClass == 8 && defaultClass != 8 && defaultClass != 0xef && defaultClass != 0xff)
    {
        /* Unexpected default class combined with differing interface class */
        SHOW_PROGRESS(stdout,"Bogus Class/InterfaceClass: 0x%02x/0x08\n", defaultClass);
        defaultClass = 8;
    }

    if (strlen(mswitch->MessageContent)  && strncmp("55534243",mswitch->MessageContent,8) == 0)
        if (defaultClass != 8)
        {
            fprintf(stderr, "Error: can't use storage command in MessageContent with interface %d;\n"
                    "       interface class is %d, expected 8. Abort\n\n", intf->altsetting[0].desc.bInterfaceNumber, defaultClass);
            return -9;
        }



    if (show_progress)
    {
        fprintf(stdout,"\nUSB description data (for identification)\n");
        fprintf(stdout,"-------------------------\n");
        fprintf(stdout,"Manufacturer: %s\n", intf->usb_dev->manufacturer);
        fprintf(stdout,"     Product: %s\n", intf->usb_dev->product);
        fprintf(stdout,"  Serial No.: %s\n", intf->usb_dev->serial);
        fprintf(stdout,"-------------------------\n");
    }

    /* Special modes are exclusive, so check for illegal combinations.
     * More than one bit set?
     */
    if ( mswitch->ModeMap & (mswitch->ModeMap-1) )
    {
        fprintf(stdout,"Multiple special modes selected; check configuration. Abort\n\n");
        return -10;
    }

    if ((strlen(mswitch->MessageContent) || mswitch->StandardEject) && mswitch->ModeMap )
    {
        mswitch->MessageContent[0] = '\0';
        mswitch->StandardEject = 0;
        fprintf(stdout,"Warning: MessageContent/StandardEject ignored; can't combine with special mode\n");
    }

    if (mswitch->StandardEject && (strlen(mswitch->MessageContent2)  || strlen(mswitch->MessageContent3) ))
    {
        fprintf(stdout,"Warning: MessageContent2/3 ignored; only one allowed with StandardEject\n");
    }

    if ( !mswitch->ModeMap && !strlen(mswitch->MessageContent)  && !mswitch->StandardEject )
        SHOW_PROGRESS(stdout,"Warning: no switching method given. See documentation\n");




    if(mswitch->ModeMap & HUAWEI_MODE)
    {
        switchHuaweiMode(intf);
    }
    if(mswitch->ModeMap & SIERRA_MODE)
    {
        switchSierraMode(intf);
    }
    if(mswitch->ModeMap & GCT_MODE)
    {
        //      detachDriver();
        switchGCTMode(intf);
    }
    if(mswitch->ModeMap & QISDA_MODE)
    {
        switchQisdaMode(intf);
    }
    if(mswitch->ModeMap & KOBIL_MODE)
    {
        //      detachDriver();
        switchKobilMode(intf);
    }
    if(mswitch->ModeMap & QUANTA_MODE)
    {
        switchQuantaMode(intf);
    }
    if(mswitch->ModeMap & SEQUANS_MODE)
    {
        switchSequansMode(intf);
    }
    if(mswitch->ModeMap & MOBILEACTION_MODE)
    {
        switchActionMode(intf);
    }
    if(mswitch->ModeMap & CISCO_MODE)
    {
        //      detachDriver();
        switchCiscoMode(mswitch, intf);
    }
    if(mswitch->ModeMap & BLACKBERRY_MODE)
    {
        //      detachDriver();
        switchBlackberryMode(intf);
    }
    //  if(ModeMap & PANTECH_MODE) {
    //      detachDriver();
    //      if (PantechMode > 1)
    //          switchPantechMode(intf);
    //      else
    //          SHOW_PROGRESS(stdout,"Waiting for auto-switch of Pantech modem ...\n");
    //  }
    //  if(ModeMap & SONY_MODE) {
    //      if (CheckSuccess)
    //          SHOW_PROGRESS(stdout,"Note: CheckSuccess ignored; Sony mode does separate checks\n");
    //      CheckSuccess = 0; /* separate and implied success control */
    //      sonySuccess = switchSonyMode();
    //  }

    if (mswitch->StandardEject)
    {
        SHOW_PROGRESS(stdout,"Sending standard EJECT sequence\n");
        //      detachDriver();
        if ((mswitch->MessageContent[0] != '\0'))
            strcpy(mswitch->MessageContent3, mswitch->MessageContent);
        else
            mswitch->MessageContent3[0] = '\0';

        strcpy(mswitch->MessageContent,"5553424387654321000000000000061e000000000000000000000000000000");
        strcpy(mswitch->MessageContent2,"5553424397654321000000000000061b000000020000000000000000000000");
        mswitch->NeedResponse = 1;
        switchSendMessage(mswitch, intf);
    }
    else if (mswitch->ModeMap & HUAWEINEW_MODE)
    {
        SHOW_PROGRESS(stdout,"Using standard Huawei switching message\n");
        //      detachDriver();
        strcpy(mswitch->MessageContent,"55534243123456780000000000000011062000000101000100000000000000");
        mswitch->NeedResponse = 0;
        switchSendMessage(mswitch, intf);
    }
    else if (strlen(mswitch->MessageContent))
    {
        switchSendMessage(mswitch, intf);
    }



    SHOW_PROGRESS(stdout,"-> Run lsusb to note any changes. Bye!\n\n");

    return 0;





}



static int usb_modeswitch_probe(struct usb_interface *intf, const struct usb_device_id *id)
{
    struct usb_modeswitch *mswitch;
    const struct device_refer *refer;
    int ret;
        
    if((refer = match_device_refer(intf, id)) == NULL)
    {
        printf("usb_modeswitch_probe match idVendor:%x  idProduct%x failed\r\n", id->idVendor, id->idProduct);

        return -1;
    }

    mswitch = kmalloc(sizeof(struct usb_modeswitch), 0);
    if(!mswitch)
        return -2;

    memset(mswitch, 0, sizeof(struct usb_modeswitch));

    ret = usb_modeswitch(mswitch, intf, refer);

    kfree(mswitch);

    return ret;
}



void usb_modeswitch_disconnect(struct usb_interface *intf)
{
    return;
}



struct usb_driver usb_modeswitch_driver =
{
name:
    "usb_modeswitch"
    ,
probe:
    usb_modeswitch_probe,
disconnect:
    usb_modeswitch_disconnect,
id_table:
    usb_modeswitch_ids,
};


int usb_modeswitch_init(void)
{
    return usb_register(&usb_modeswitch_driver);
}


