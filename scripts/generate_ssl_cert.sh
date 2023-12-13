## Created by Assoc. Prof. Wiroon Sriborrirux
# This shell script will generate the certificate, private key and public key for root, server and client

#!/bin/bash

set -e

RED=$'\e[1;31m'
GREEN=$'\e[1;32m'
YELLOW=$'\e[1;33m'
NC=$'\e[0m' # No Color

IP_ADDRESS=$1
OPENSSL_SUBJECT_INFO="/C=TH/ST=Chonburi/L=Bangsaen/O=BUU/OU=EASTPark"

## This string contains several attributes that identify the CA: ##
# /C specifies the country of the entity, which is "TH" (Thailand) in this case.
# /ST specifies the state or province of the entity, which is "Chonburi" in this case.
# /L specifies the city of the entity, which is "Bangsaen" in this case.
# /O specifies the organization of the entity, which is "BUU" in this case.
# /OU specifies the organizational unit of the entity, which is "EASTPark" in this case.
# /CN specifies the common name of the entity, which is "<entity name>" in this case.

if [ -z "$1" ]
  then
    echo "Specify IP address of the SSL-based Server as argument"
	read -p "Press any key to exit ..."
	exit 1
fi

################################
# Become a Certificate Authority
################################
ROOT_CA_NAME=root_ca

OPENSSL_SUBJECT_INFO_CA="$OPENSSL_SUBJECT_INFO/CN=BiiL"

# Generate a private root key
openssl genrsa -out $ROOT_CA_NAME.key 2048

# Self-sign a certificate.
openssl req -x509 -new -nodes -key $ROOT_CA_NAME.key -sha256 \
-days 3650 -out $ROOT_CA_NAME.crt -subj $OPENSSL_SUBJECT_INFO_CA

###############################
# Create CA-signed server cert
###############################

MY_SERVER_NAME=server


OPENSSL_SUBJECT_INFO_SERVER="$OPENSSL_SUBJECT_INFO/CN=$MY_SERVER_NAME"


# Generate a private key
openssl genrsa -out $MY_SERVER_NAME.key 2048

# Create the Certificate Signing Request (CSR).
# Make sure to set the "Common Name" field with MY_SERVER_NAME.
openssl req -new -key $MY_SERVER_NAME.key -out $MY_SERVER_NAME.csr \
-subj $OPENSSL_SUBJECT_INFO_SERVER

# Create a config file for the extensions
>$MY_SERVER_NAME.ext cat <<-EOF
authorityKeyIdentifier=keyid,issuer
basicConstraints=CA:FALSE
keyUsage = digitalSignature, nonRepudiation, keyEncipherment, dataEncipherment
subjectAltName = @alt_names
[alt_names]
DNS.1 = $MY_SERVER_NAME
DNS.2 = IP:$IP_ADDRESS
EOF

# Create the signed certificate
openssl x509 -req -in $MY_SERVER_NAME.csr -CA $ROOT_CA_NAME.crt \
-CAkey $ROOT_CA_NAME.key -CAcreateserial -out $MY_SERVER_NAME.crt \
-days 3650 -sha256 -extfile $MY_SERVER_NAME.ext

###############################
# Create CA-signed client cert
###############################

MY_CLIENT_NAME=client

OPENSSL_SUBJECT_INFO_CLIENT="$OPENSSL_SUBJECT_INFO/CN=$MY_CLIENT_NAME"

# Generate a private key
openssl genrsa -out $MY_CLIENT_NAME.key 2048

# Create the Certificate Signing Request (CSR).
openssl req -new -key $MY_CLIENT_NAME.key -out $MY_CLIENT_NAME.csr \
-subj $OPENSSL_SUBJECT_INFO_CLIENT

# Create the signed certificate
openssl x509 -req -in $MY_CLIENT_NAME.csr -CA $ROOT_CA_NAME.crt \
-CAkey $ROOT_CA_NAME.key -CAcreateserial -out $MY_CLIENT_NAME.crt \
-days 3650 -sha256

# Remove the intermediate files.
rm $ROOT_CA_NAME.srl $MY_SERVER_NAME.csr $MY_CLIENT_NAME.csr $MY_SERVER_NAME.ext

echo ""
echo ""
echo "${GREEN}Below is the C header file text format....${NC}"
read -p "${YELLOW}Press any key to continue ...${NC}"

python3 format_cert_key.py $ROOT_CA_NAME.key $ROOT_CA_NAME.crt $MY_CLIENT_NAME.key $MY_CLIENT_NAME.crt
