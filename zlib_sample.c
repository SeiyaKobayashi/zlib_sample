/*
 * Author: Seiya Kobayashi
 * Date: Feb.26, 2018
 * Description: Simple implementation of zlib deflation/inflation in c.
 *              Wrote mainly for solidifying my understanding of zlib,
 *              the most widely-used library for data compression.
 *              This would be an important milestone to be able to write
 *              git implementation, which uses zlib to (de)compress
 *              its objects (such as blob).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

// Compress "a" into "b"
void _compress(char *a, char *b)
{
  z_stream zd;
  /* Set zalloc and zfree to Z_NULL, so that deflateInit upadates them
     to use default allocation functions.
   */
  zd.zalloc = Z_NULL;
  zd.zfree = Z_NULL;
  zd.opaque = Z_NULL;

  // Set "a" as an input and "b" as an output
  zd.next_in = (Bytef *)a;
  zd.avail_in  = (uInt)strlen(a)+1;      // String + Terminator
  zd.next_out = (Bytef *)b;
  zd.avail_out = (uInt)sizeof(b);      // Size of the output

  if (deflateInit(&zd, Z_BEST_COMPRESSION) != Z_OK)
    perror("deflateInit failed");
  deflate(&zd, Z_FINISH);
  if (deflateEnd(&zd) != Z_OK)
    perror("deflateEnd failed");

  // Prints the compressed string (and its length) stored in "b"
  printf("Compressed string:\n\t%s\n\twith its length of %lu\n", b, zd.total_out);
}

// Decompress "b" to "c"
void _decompress(char *a, char *b)
{
  z_stream zi;
  /* Set zalloc and zfree to Z_NULL, so that inflateInit upadates them
     to use default allocation functions.
   */
  zi.zalloc = Z_NULL;
  zi.zfree = Z_NULL;
  zi.opaque = Z_NULL;

  // Set "a" as an input and "b" as an output
  zi.next_in = (Bytef *)a;
  zi.avail_in = (uInt)((char *)zi.next_out - b);      // Size of the input
  zi.next_out = (Bytef *)b;
  zi.avail_out = (uInt)sizeof(b);      // Size of the output

  if (inflateInit(&zi) != Z_OK)
    perror("inflateInit failed");
  inflate(&zi, Z_NO_FLUSH);
  if (inflateEnd(&zi) != Z_OK)
    perror("inflateEnd failed");

  // Prints the decompressed string (and its length) stored in "b"
  printf("Decompressed string:\n\t%s\n\twith its length of %lu\n", b, strlen(b));
}

int main(int argc, char* argv[])
{
  // Initial string length = 34
  char a[40] = "Hello, my name is Seiya Kobayashi.";
  // Placeholder for the compressed "a"
  char b[40];
  // Placeholder for the decompressed "b"
  char c[40];
  // Prints the initial string (and its length) stored in "a"
  printf("Initial string:\n\t%s\n\twith its length of %lu\n", a, strlen(a));

  _compress(a, b);
  _decompress(b, c);

  return 0;
}
