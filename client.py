import socket

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

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(('localhost', 9000))

message = "Hello Server"
encrypted_msg = encrypt(message)
client_socket.send(encrypted_msg.encode())

ack = client_socket.recv(1024).decode()
decrypted_ack = decrypt(ack)
print("Server response (decrypted):", decrypted_ack)
client_socket.close()
