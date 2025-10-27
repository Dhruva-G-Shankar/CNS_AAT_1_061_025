# Secure Client-Server Communication - AAT 1 
## Project Overview
This project demonstrates secure client-server communication using encrypted messages over TCP sockets. Implementations in both C and Python showcase the use of a substitution cipher for encryption/decryption, focusing on modular code and clarity. The goal is to demonstrate secure, reliable, and well-structured message passing between client and server.
## Architecture & Design
    ┌────────────┐                           ┌────────────┐
    │   CLIENT   │                           │   SERVER   │
    └────────────┘                           └────────────┘
          │                                         │
          │    (1) Send Encrypted Message           │
          ├────────────────────────────────────────>│
          │                                         │
          │    (2) Send Encrypted Acknowledgement    │
          │<────────────────────────────────────────┤
          │                                         │

- Client connects to server via TCP (localhost:9000).
- Client encrypts and sends a message.
- Server decrypts, displays message, then replies with an encrypted acknowledgment.

## Encryption Algorithm
- Substitution cipher: Each character is replaced by another using a fixed, shuffled alphabet mapping.
For example:
Encryption:
Plaintext: HELLO
Ciphertext: ITSSG,
Decryption:
Ciphertext: ITSSG
Plaintext: HELLO

## Comparision Table:
Feature           |  C Implementation       |  Python Implementation
------------------+-------------------------+-----------------------
Socket Setup      |  Winsock2 API, threads  |  socket library       
Encryption Logic  |  Manual char mapping    |  dict/list mapping    
Execution         |  Single/main/threaded   |  Separate scripts/main
Error Handling    |  Manual                 |  Exceptions           


