import random
import math


# Function to check if a number is prime
def is_prime(num):
    if num < 2:
        return False
    for i in range(2, int(math.sqrt(num)) + 1):
        if num % i == 0:
            return False
    return True


# Function to generate a random prime number in a given range
def generate_prime(minimum, maximum):
    while True:
        num = random.randint(minimum, maximum)
        if is_prime(num):
            return num


# Function to compute the greatest common divisor
def gcd(a, b):
    while b:
        a, b = b, a % b
    return a


# Function to find the modular multiplicative inverse
def mod_inverse(a, m):
    m0, x0, x1 = m, 0, 1
    while a > 1:
        q = a // m
        m, a = a % m, m
        x0, x1 = x1 - q * x0, x0
    return x1 + m0 if x1 < 0 else x1


# Function to generate public and private keys
def generate_keys():
    # Choose two large prime numbers
    p = generate_prime(100, 1000)
    q = generate_prime(100, 1000)

    # Compute n and totient(n)
    n = p * q
    totient_n = (p - 1) * (q - 1)

    # Choose public exponent e
    e = random.randint(2, totient_n - 1)
    while gcd(e, totient_n) != 1:
        e = random.randint(2, totient_n - 1)

    # Calculate private exponent d
    d = mod_inverse(e, totient_n)

    # Public key: (e, n)
    # Private key: (d, n)
    public_key = (e, n)
    private_key = (d, n)

    return public_key, private_key


# Function to encrypt plaintext using public key
def encrypt(plaintext, public_key):
    e, n = public_key
    ciphertext = [pow(ord(char), e, n) for char in plaintext]
    return ciphertext


# Function to decrypt ciphertext using private key
def decrypt(ciphertext, private_key):
    d, n = private_key
    decrypted_text = ''.join([chr(pow(char, d, n)) for char in ciphertext])
    return decrypted_text


# Main function
def main():
    print("RSA Encryption and Decryption")
    public_key, private_key = generate_keys()
    print("Public Key:", public_key)
    print("Private Key:", private_key)

    while True:
        print("\nOptions:")
        print("1. Encrypt")
        print("2. Decrypt")
        print("3. Exit")
        choice = input("Enter your choice (1/2/3): ")

        if choice == '1':
            plaintext = input("Enter plaintext (uppercase letters and spaces only): ")
            ciphertext = encrypt(plaintext, public_key)
            print("Encrypted Text:", ciphertext)

        elif choice == '2':
            ciphertext_str = input("Enter ciphertext (comma-separated numbers): ")
            ciphertext = [int(char) for char in ciphertext_str.split(',')]
            decrypted_text = decrypt(ciphertext, private_key)
            print("Decrypted Text:", decrypted_text)

        elif choice == '3':
            print("Exiting program. Goodbye!")
            break

        else:
            print("Invalid choice. Please enter a valid option.")


if __name__ == "__main__":
    main()
