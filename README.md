myfsec
======

MyFsec is a program designed to facilitate encrypting files with some simple clicks and totally integrated to Finder. 
Once installed, you will be able to encrypt files just by right clicking them and choosing "Encrypt file" in the contextual menu. Then entering a password and option of encryption (For now there is a “insecure” way, designed for big files that don’t have sensitive information, and a “secure” option that actually encodes the file using AES-128 provided by openssl and a random salt, so it meets the industry standards.

For now, there is only a OSX version, but if someone is interested in a windows or linux version, the porting should be quite easy (at least a command line one) as the core uses openssl (available in all [platforms) and written in a standard C. So just let me know and you are welcome to helps well ;-)
