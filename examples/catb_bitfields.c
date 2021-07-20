
struct foo6 {
    short s;
    char c;
    int flip:1;
    int nybble:4;
    int septet:7;
};

// http://www.catb.org/esr/structure-packing/#_bitfields

/* Big-endian (network byte order)
┌─────┬─────────────────┐
│Octet│ (LSB)     (MSB) │
├─────┼─────────────────┤
│ Bit │ 0 1 2 3 4 5 6 7 │
├─────┼─────────────────┤
│  0  │                 │
│     │        s        │
│  1  │                 │
│     ├─────────────────┤
│  2  │        c        │
│     ├─────────────────┤
│  3  │ f n n n n - - - │
├─────┼──────────────┬──┤
│  4  │ s s s s s s s│- │
│     ├──────────────┘  │
│  5  │ - - - - - - - - │
│     │                 │
│  6  │ - - - - - - - - │
│     │                 │
│  7  │ - - - - - - - - │
└─────┴─────────────────┘
*/

struct foo6_BE {
    short s;
    char c;
    int flip:1;
    int nybble:4;
    int :3;
    int septet:7;
    int :25;
};

/* Little-endian
┌─────┬─────────────────┐
│Octet│ (?SB)     (?SB) │
├─────┼─────────────────┤
│ Bit │ ? ? ? ? ? ? ? ? │
├─────┼─────────────────┤
│  ?  │                 │
│     │        s        │
│  ?  │                 │
│     ├─────────────────┤
│  ?  │        c        │
│     ├─────────────────┤
│  ?  │ - - - f n n n n │
├─────┼─────────────────┤
│  ?  │ - - - - - - - - │
│     │                 │
│  ?  │ - - - - - - - - │
│     │                 │
│  ?  │ - - - - - - - - │
│     │  ┌──────────────┤
│  ?  │ -│s s s s s s s │
└─────┴──┴──────────────┘
*/

struct foo6_LE {
    short s;
    char c;
    int flip:1;
    int nybble:4;
    int septet:7;
};
