#include <sodium.h>
#include <stdio.h>
#include <unistd.h>

#define BUFSIZE 65536
#define HASHSIZE 32

int main() {
  if (sodium_init() == -1) {
    return 1;
  }

  crypto_generichash_state state;
  crypto_generichash_init(&state, NULL, 0, HASHSIZE);

  unsigned char buf[BUFSIZE];
  ssize_t n;
  while ((n = read(STDIN_FILENO, buf, BUFSIZE))) {
    crypto_generichash_update(&state, buf, n);
  }

  unsigned char hash[HASHSIZE];
  crypto_generichash_final(&state, hash, HASHSIZE);

  char hex[2 * HASHSIZE + 1];
  sodium_bin2hex(hex, sizeof hex, hash, sizeof hash);

  printf("%s\n", hex);
}
