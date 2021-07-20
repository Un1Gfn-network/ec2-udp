// declare X=struct_header &&  gcc -std=gnu11 -g -Wall -Wextra -o "$X".out "$X".c && ./"$X".out

// /opt/x-tools7h/arm-unknown-linux-gnueabihf/bin/gcc
// /opt/x-tools7h/arm-unknown-linux-gnueabihf/arm-unknown-linux-gnueabihf/sysroot/lib/libgcc_s.so.1
// Only LE lib, No BE lib

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h> // offsetof()

static void test_packed(){

  // https://stackoverflow.com/a/119134

  typedef struct {
    uint8_t a;
    uint16_t b;
    uint8_t c;
  } X;

  typedef struct {
    uint8_t a;
    uint32_t b;
    uint8_t c;
  } Y;

  typedef struct {
    uint8_t a;
    uint64_t b;
    uint8_t c;
  } Z;

  typedef struct {
    uint8_t a;
    uint64_t b;
    uint8_t c;
  } __attribute__((__packed__)) P;

  // printf("%s %zu %zu %zu\n",
  //   "Z",
  //   offsetof(Z,b),
  //   offsetof(Z,c),
  //   sizeof(Z));

  static_assert((16+16+16)/8==sizeof(X));
  static_assert((32+32+32)/8==sizeof(Y));
  static_assert((64+64+64)/8==sizeof(Z));
  static_assert(( 8+64+ 8)/8==sizeof(P));

}

static void test_bitfield(){

  /*
  https://en.wikipedia.org/wiki/IPv4#Header
  https://en.wikipedia.org/wiki/Box-drawing_character
  ┌───────┬─────┬───────────────────┐
  │Offsets│Octet│ (LSB)   0   (MSB) │
  ├───────┼─────┼───────┬───────────┤
  │ Octet │ Bit │ 0 1 2 │ 3 4 5 6 7 │
  ├───────┼─────┼───────┼───────────┤
  │   0   │  0  │  u3   │    u5     │
  └───────┴─────┴───────┴───────────┘
  */
  

  // https://en.wikipedia.org/wiki/C_syntax#Bit_fields
  // /usr/include/netinet/ip.h
  // https://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html
  typedef struct {
    // #if __BYTE_ORDER == __LITTLE_ENDIAN
    #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
      #warning "little endian"
      uint8_t u3:3;
      uint8_t u5:5;
    // #elif __BYTE_ORDER == __BIG_ENDIAN
    #elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
      #warning "big endian"
      uint8_t u5:5;
      uint8_t u3:3;
    #else
      #error
    #endif
  } Bitfield;

  static_assert(8/8==sizeof(Bitfield));

  Bitfield bf={};
  const uint8_t *const u8=(const uint8_t*)(&bf);
  printf("▒ ");fflush(stdout);
  for(int i=0;i<8;++i){
    printf("%d ",bf.u3);fflush(stdout);
    assert(!((*u8)&0xF8)); // 0xF8 11111000 // Make sure the upper 5 bits are zero
    assert(i==*u8);        //               // Compare the lower 3 bits
    ++bf.u3;
  }
  printf("▒ %u\n",bf.u3);
  assert(*u8==0x00);

  printf("▒ ");fflush(stdout);
  for(int i=0;i<32;++i){
    printf("%d ",bf.u5);fflush(stdout);
    assert(!((*u8)&0x07)); // 0x07 0000_0111 // Make sure the lower 3 bits are zero
    assert((*u8)>>3==i);   //                // Compare the upper 5 bits
    ++bf.u5;
  }
  printf("▒ %u\n",bf.u5);
  assert(*u8==0x00);

}

int main(){
  // test_bitfield();
  test_packed();
  return 0;
}
