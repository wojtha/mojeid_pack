
mojeID module pack pro Drupal 6.x

autor: Vojtěch Kusý - http://vojtechkusy.cz, http://atomicant.co.uk
sponzor vývoje: CZ.NIC - http://nic.cz/


OBSAH BALÍČKU:

mojeid                   ...   mojeID branding a podpora  
└─ mojeid_uc_addresses   ...   mojeID podpora pro Ubercart a UC Addresses 
openid                   ...   upravený modul OpenID z jádra Drupalu [1]
openid_client_ax         ...   upravený modul Openid Client AX [2] 
README.TXT               ...   tento soubor


[1] Nutné použít dokud se nevyřeší chyby jádra: http://drupal.org/node/575810 
a http://drupal.org/node/1120290

[2] Nutné použít dokud se nevyřeší chyby modulu: http://drupal.org/node/1036310
    (http://drupal.org/node/440418 a http://drupal.org/node/1179550 již byly
    opraveny)

ZMĚNY

2011-09-07 6.x-1.0-beta1
 - Pro úspěšné přihlášení je možné vložit i ".mojeid.cz"
 - Oprava chyb v mojeID UC Addresses
 - Update modulu Openid Client AX (http://drupal.org/node/440418 a 
   http://drupal.org/node/1179550 opraveny v oficialni verzi) 
 
2011-07-21 6.x-1.0-alpha2
 - Odstraněny debugovací funkce z openid modulu
 - Přidán XRDS dokument
 - mojeID a mojeID UC Addresses sloučeny do jednoho projektu
 - Vytvořen projekt pro mojeID modul: http://drupal.org/project/mojeid 

2011-07-08 6.x-1.0-alpha1
 - Úvodní verze