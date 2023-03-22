cmd_/home/joelc/CN/cipher_driver/cipher.mod := printf '%s\n'   cipher.o | awk '!x[$$0]++ { print("/home/joelc/CN/cipher_driver/"$$0) }' > /home/joelc/CN/cipher_driver/cipher.mod
