import socket

# Substitution mapping (example)
alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
key =    "QWERTYUIOPASDFGHJKLZXCVBNMlkjhgfdsamnbvcxzpoiuytrewq"

def encrypt(text):
    result = ""
    for char in text:
        if char in alphabet:
            idx = alphabet.index(char)
            result += key[idx]
        else:
            result += char
    return result

def decrypt(cipher):
    result = ""
    for char in cipher:
        if char in key:
            idx = key.index(char)
            result += alphabet[idx]
        else:
            result += char
    return result

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(('localhost', 9000))
server_socket.listen(1)
print("Server listening on port 9000...")

while True:
    client_sock, addr = server_socket.accept()
    print("Connection from", addr)
    data = client_sock.recv(1024).decode()
    decrypted = decrypt(data)
    print("Received (decrypted):", decrypted)

    ack_message = "Acknowledged: " + decrypted
    encrypted_ack = encrypt(ack_message)
    client_sock.send(encrypted_ack.encode())
    client_sock.close()
