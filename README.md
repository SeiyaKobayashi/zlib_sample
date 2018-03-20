# zlib_sample
Simple implementation of zlib deflation/inflation written in c.

---

### How to compile and execute
$ gcc -lz -o zlib_sample zlib_sample.c  
$ ./zlib_sample

---

### Sample output
    Initial string:  
      Hello, my name is Seiya Kobayashi.  
      with its length of 34  
    Compressed string:  
      x??H????QȭT?K?MU?,NͬLT??OJ?L,???c  
      with its length of 40  
    Uncompressed string:  
      Hello, my name is Seiya Kobayashi.  
      with its length of 34  
