# PQC – Proof of Concept

A simple TCP-based client–server application written in C that demonstrates the use of **Post-Quantum Cryptography (PQC)** with the **liboqs** library.

---

## Overview

This project implements a minimal TCP client–server architecture in which two parties—**Alice (client)** and **Bob (server)**—communicate over a socket connection while performing post-quantum cryptographic operations.

The purpose of this project is educational: to illustrate how quantum-resistant cryptographic mechanisms can be integrated into existing C-based networking applications without relying on TLS or higher-level frameworks.

---

## Post-Quantum Cryptography

The project uses [liboqs](https://github.com/open-quantum-safe/liboqs), developed by the [Open Quantum Safe](https://openquantumsafe.org/) initiative, to generate post-quantum cryptographic keys.

- Alice generates a post-quantum keypair using liboqs.
- The public key is transmitted to Bob over a TCP connection.
- Bob receives and processes the key using a command-based protocol.

This approach demonstrates the integration of post-quantum cryptography into traditional TCP-based communication.

---

## Workflow

1. Bob starts a TCP server and listens for incoming connections.
2. Alice establishes a TCP connection to the server.
3. Alice generates a post-quantum keypair using liboqs.
4. Alice sends the public key to Bob.
5. Communication continues using structured TCP commands.

---
