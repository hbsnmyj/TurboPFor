/**
    Copyright (C) powturbo 2013-2017
    GPL v2 License
  
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

    - homepage : https://sites.google.com/site/powturbo/
    - github   : https://github.com/powturbo
    - twitter  : https://twitter.com/powturbo
    - email    : powturbo [_AT_] gmail [_DOT_] com
**/
//  "TurboPFor: Integer Compression" Turbo PFor/PforDelta 
#ifndef USIZE
#include <stdint.h>
 
#include "conf.h"
#include "bitpack.h"
#include "vint.h"		
#include "bitutil.h"
#include "vp4.h"
#undef P4DELTA
//unsigned xbits[64];
#define PAD8(_x_) ( (((_x_)+8-1)/8) )
//------------------------------------------
#define _P4BITS _p4bits
#define  P4BITS _p4bits

//-- Scalar
#define _P4ENC   _p4enc
#define  P4ENC    p4enc
#define  P4NENC   p4nenc
#define  BITPACK  bitpack
#define  BITDELTA bitdienc

#define USIZE 8
#include "vp4c.c"

#define HYBRID 1 // Hybrid TurboPFor : 0=fixed bit packing, 1=fixed BP+Variable byte 
#define USIZE 16
#include "vp4c.c"

#define USIZE 32
#include "vp4c.c"

#define USIZE 64
#include "vp4c.c"

#define P4DELTA 0
#define  P4DENC   p4denc
#define  P4NENC   p4ndenc
#define  P4NENCS  p4denc

#define HYBRID 0
#define USIZE 8
#include "vp4c.c"

#define HYBRID 1
#define USIZE 16
#include "vp4c.c"

#define USIZE 32
#include "vp4c.c"

#define USIZE 64
#include "vp4c.c"

#define P4DELTA 1
#define  P4DENC   p4d1enc
#define  P4NENC   p4nd1enc
#define  P4NENCS  p4d1enc

#define HYBRID 0
#define USIZE 8
#include "vp4c.c"

#define HYBRID 1
#define USIZE 16
#include "vp4c.c"

#define USIZE 32
#include "vp4c.c"

#define USIZE 64
#include "vp4c.c"

#define  BITDELTA  bitzenc
#define  P4DENC   p4zenc
#define  P4NENC   p4nzenc
#define  P4NENCS  p4zenc

#define HYBRID 0
#define USIZE 8
#include "vp4c.c"

#define HYBRID 1
#define USIZE 16
#include "vp4c.c"

#define USIZE 32
#include "vp4c.c"

#define USIZE 64
#include "vp4c.c"
#define  BITDELTA bitdienc

#undef P4DELTA

#define HYBRID 0             // Direct access
#define  P4BITS _p4bitsx
#define _P4BITS _p4bitsx
#define _P4ENC  _p4encx
#define  P4ENC   p4encx
#define  P4NENC  p4nencx

#define USIZE 8
#include "vp4c.c"

#define USIZE 16
#include "vp4c.c"

#define USIZE 32
#include "vp4c.c"

#define USIZE 64
#include "vp4c.c"

#undef _P4ENC
#undef  P4ENC
#undef  BITPACK 

#undef _P4BITS
#define P4BITS _p4bits

  #ifndef NSIMD

#define HYBRID 1 // 
    #ifdef __SSE2__
//-- SIMD: Vertical bitpacking
#define VSIZE 128 
#define _P4ENC    _p4enc128v
#define  P4ENC     p4enc128v
#define  P4NENCS   p4enc
#define  P4NENC    p4nenc128v
#define  BITPACK   bitpack128v
#define USIZE 32
#include "vp4c.c"

#define P4DELTA 0
#define  P4DENC    p4denc128v
#define  P4NENC    p4ndenc128v
#define  P4NENCS   p4denc
#include "vp4c.c"

#define P4DELTA 1
#define  P4DENC    p4d1enc128v
#define  P4NENC    p4nd1enc128v
#define  P4NENCS   p4d1enc
#include "vp4c.c"

#define P4DELTA 0
#define  BITDELTA  bitzenc
#define  P4DENC    p4zenc128v
#define  P4NENC    p4nzenc128v
#define  P4NENCS   p4zenc
#include "vp4c.c"
#define  BITDELTA bitdienc

#undef P4DELTA

#undef  _P4ENC    
#undef   P4ENC    
#undef   BITPACK
    #endif

    #ifdef __AVX2__
#define VSIZE 256
#define _P4ENC    _p4enc256v
#define  P4ENC     p4enc256v
#define  P4NENC    p4nenc256v
#define  P4NENCS   p4enc
#define  BITPACK   bitpack256v
#define USIZE 32
#include "vp4c.c"

#define P4DELTA 0
#define  P4DENC    p4denc256v
#define  P4NENC    p4ndenc256v
#define  P4NENCS   p4denc
#include "vp4c.c"

#define P4DELTA 1
#define  P4DENC    p4d1enc256v
#define  P4NENC    p4nd1enc256v
#define  P4NENCS   p4d1enc
#include "vp4c.c"
#undef P4DELTA

#undef  _P4ENC    
#undef   P4ENC    
#undef   BITPACK
    #endif
  #endif

#undef USIZE

#else
#pragma clang diagnostic push 
#pragma clang diagnostic ignored "-Wparentheses"

#pragma GCC push_options
#pragma GCC optimize ("align-functions=16")

#define uint_t TEMPLATE3(uint, USIZE, _t)

#ifdef VSIZE
  #define CSIZE VSIZE
#else
  #define CSIZE 128
#endif
  
  #ifndef P4DELTA

    #ifdef _P4BITS 	
inline unsigned TEMPLATE2(_P4BITS, USIZE)(uint_t *__restrict in, unsigned n, unsigned *pbx) {
    #if HYBRID == 1
  unsigned _vb[USIZE*2+64] = {0}, *vb=&_vb[USIZE];
	#endif
  unsigned cnt[USIZE+8] = {0}, x, bx, bmp8=(n+7)/8;
  uint_t *ip, u=0; 
  int b,i,ml,l,fx=0;
  	
  #define CNTE(i) { ++cnt[TEMPLATE2(bsr, USIZE)(ip[i])], u |= ip[i]; }
  for(ip = in; ip != in+(n&~3); ip+=4) { CNTE(0); CNTE(1); CNTE(2); CNTE(3); }
  for(;ip != in+n;ip++) CNTE(0);

  b  = TEMPLATE2(bsr, USIZE)(u);  									//xbits[b/*ctz64(b)*/]++;									
  bx = b; 
  ml = PAD8(n*b)+1; x = cnt[b];												
 
    #if HYBRID > 0
  #define VBB(_x_,_b_) vb[_b_-7]+=_x_; vb[_b_-15]+=_x_*2; vb[_b_-19]+=_x_*3; vb[_b_-25]+=_x_*4;
  int vv = x; VBB(x,b); 
    #else
  ml -= 2+bmp8;
	#endif
  for(i = b-1; i >= 0; --i) {
      #if HYBRID > 0
        l = PAD8(n*i) + 2+bmp8 + PAD8(x*(bx-i)); 
    int v = PAD8(n*i) + 2 + x + vv, vx = 0; 
	x  += cnt[i]; 
    vv += cnt[i]+vb[i]; 
    VBB(cnt[i],i);
    int fi = l < ml;  ml = fi?l:ml; b = fi?i:b; fx=fi?0:fx;
        fi = v < ml;  ml = fi?v:ml; b = fi?i:b; fx=fi?1:fx;
      #else 
    l = PAD8(n*i) + PAD8(x*(bx-i)); 
    x += cnt[i]; 
    int fi = l < ml; 												
	ml = fi?l:ml; b = fi?i:b;
	  #endif
  }  											//fx = 0;
    #if HYBRID > 0
  *pbx = fx?(USIZE+1):(bx - b);
      #if USIZE == 64
  if(b == USIZE-1) { b = USIZE; *pbx = 0; }
      #endif
    #else
  *pbx = bx - b;
    #endif
  return b;
} 
   #endif
 
unsigned char *TEMPLATE2(_P4ENC, USIZE)(uint_t *__restrict in, unsigned n, unsigned char *__restrict out, unsigned b, unsigned bx) {
  if(!bx) 
    return TEMPLATE2(BITPACK, USIZE)(in, n,	out, b);

  uint_t             msk =  (1ull << b)-1, _in[P4D_MAX+32], inx[P4D_MAX+32];
  unsigned long long xmap[P4D_MAX/64] = {0};  
  unsigned           miss[P4D_MAX],i, xn, c;
  #define MISS { miss[xn] = i; xn += in[i] > msk; _in[i] = in[i] & msk; i++; }
  for(xn = i = 0; i != n&~3; ) { MISS; MISS; MISS; MISS; }
  while(i != n) MISS;
  
  for(i = 0; i != xn; ++i) {
    c           = miss[i]; 
    xmap[c>>6] |= (1ull << (c&0x3f)); 
    inx[i]      = in[c] >> b; 
  }	
  unsigned char *_out = out;
  
    #if HYBRID > 0
  if(bx <= USIZE) { 														
    #endif
    for(i = 0; i < (n+63)/64; i++) ctou64(out+i*8) = xmap[i]; out += PAD8(n); 	
    out = TEMPLATE2(bitpack, USIZE)(inx, xn, out, bx);  	 	        					
    out = TEMPLATE2(BITPACK, USIZE)(_in, n,  out, b);  
    #if HYBRID > 0
  } 
  else { 															
    *out++ = xn; 
    out = TEMPLATE2(BITPACK, USIZE)(_in, n, out,  b);
    out = TEMPLATE2(vbenc, USIZE)(inx, xn, out); 				
    for(i = 0; i != xn; ++i) *out++ = miss[i]; 							
  }	  
    #endif
  return out;
}

unsigned char *TEMPLATE2(P4ENC, USIZE)(uint_t *__restrict in, unsigned n, unsigned char *__restrict out) { if(!n) return out;
  unsigned bx, b = TEMPLATE2(P4BITS, USIZE)(in, n, &bx);	//if(bx <= USIZE) printf("%d,%d ", b, bx);else printf("#%d ", b);							
    #if HYBRID > 0
  TEMPLATE2(P4HVE, USIZE)(out,b,bx);
    #else
  P4HDE(out, b, bx); 
    #endif															 
  out = TEMPLATE2(_P4ENC, USIZE)(in, n, out, b, bx); 
  return out;
}

size_t TEMPLATE2(P4NENC, USIZE)(uint_t *__restrict in, size_t n, unsigned char *__restrict out) {
  if(!n) 
    return 0;

  unsigned char *op = out; 
  uint_t *ip; 
  for(ip = in; ip != in+(n&~(CSIZE-1)); ip += CSIZE) { __builtin_prefetch(ip+512); 
    unsigned bx, b = TEMPLATE2(P4BITS, USIZE)(ip, CSIZE, &bx); 									
      #if HYBRID > 0
    TEMPLATE2(P4HVE, USIZE)(op,b,bx);
      #else
    P4HDE(op, b, bx); 
      #endif															 
    op = TEMPLATE2(_P4ENC, USIZE)(ip, CSIZE, op, b, bx);    //op = TEMPLATE2(P4ENC, USIZE)(ip, CSIZE, op);
  }
  return TEMPLATE2(p4enc, USIZE)(ip, n&(CSIZE-1), op) - out; 
}
  #else
ALWAYS_INLINE unsigned char *TEMPLATE2(P4DENC, USIZE)(uint_t *__restrict in, unsigned n, unsigned char *__restrict out, uint_t start) { if(!n) return out;
  uint_t _in[P4D_MAX+8];
  TEMPLATE2(BITDELTA, USIZE)(in, n, _in, start, P4DELTA);
  return TEMPLATE2(P4ENC, USIZE)(_in, n, out);
}

size_t TEMPLATE2(P4NENC, USIZE)(uint_t *__restrict in, size_t n, unsigned char *__restrict out) {
  if(!n) 
    return out;

  unsigned char *op = out; 
  uint_t *ip, start = *in++;
  
  TEMPLATE2(vbxput, USIZE)(op, start);
  for(ip = in, --n; ip != in+(n&~(CSIZE-1)); ip += CSIZE) {	__builtin_prefetch(ip+512);
    uint_t _in[P4D_MAX+8];
    TEMPLATE2(BITDELTA, USIZE)(ip, CSIZE, _in, start, P4DELTA);
    unsigned bx, b = TEMPLATE2(_p4bits, USIZE)(_in, CSIZE, &bx); 									
      #if HYBRID > 0
    TEMPLATE2(P4HVE, USIZE)(op,b,bx);
      #else
    P4HDE(op, b, bx); 
      #endif															 
    op = TEMPLATE2(_P4ENC, USIZE)(_in, CSIZE, op, b, bx);  // op = TEMPLATE2(P4ENC, USIZE)(_in, CSIZE, op);                
    start = ip[CSIZE-1]; 					
  }                   
  return TEMPLATE2(P4NENCS, USIZE)(ip, n&(CSIZE-1), op, start) - out; 
}
  #endif

#pragma clang diagnostic pop
#endif

