# KPN-ARV7519-WPA-generator

WPA/WPS Generator for KPN Experiabox 7 (Arcadyan ARV7519) routers

Tool to create a list of default WPA/WPS keys based on MAC-address and (a range of) serialnumbers


FOR DEMONSTRATION PURPOSES ONLY !

USE IT ONLY ON YOUR OWN ROUTER !



parameters/usage:

-m [required]: MAC-address of router

-s [optional]: range start for last 5 digits of serial#. (Also use this to generate WPA key for just one unique serial#)

-e [optional]: range end for serial# (max. 99999)

-v [optional]: verbose - outputs serial# , WPA-key and WPS pin

example 1: kpn_ARV7519WPA -m 74:31:70:BA:BA:A9

example 2: kpn_ARV7519WPA -s 85894 -m 00:00:00:B8:68:21 -v 0
