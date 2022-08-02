/*************************************************
* CAST256 Source File                            *
* (C) 1999-2001 The OpenCL Project               *
*************************************************/

#include <opencl/cast256.h>

namespace OpenCL {

/*************************************************
* CAST256 Encryption                             *
*************************************************/
void CAST256::encrypt(const byte in[BLOCKSIZE], byte out[BLOCKSIZE]) const
   {
   u32bit A = make_u32bit(in[ 0], in[ 1], in[ 2], in[ 3]),
          B = make_u32bit(in[ 4], in[ 5], in[ 6], in[ 7]),
          C = make_u32bit(in[ 8], in[ 9], in[10], in[11]),
          D = make_u32bit(in[12], in[13], in[14], in[15]);
   round1(C, D, MK[ 0], RK[ 0]); round2(B, C, MK[ 1], RK[ 1]);
   round3(A, B, MK[ 2], RK[ 2]); round1(D, A, MK[ 3], RK[ 3]);
   round1(C, D, MK[ 4], RK[ 4]); round2(B, C, MK[ 5], RK[ 5]);
   round3(A, B, MK[ 6], RK[ 6]); round1(D, A, MK[ 7], RK[ 7]);
   round1(C, D, MK[ 8], RK[ 8]); round2(B, C, MK[ 9], RK[ 9]);
   round3(A, B, MK[10], RK[10]); round1(D, A, MK[11], RK[11]);
   round1(C, D, MK[12], RK[12]); round2(B, C, MK[13], RK[13]);
   round3(A, B, MK[14], RK[14]); round1(D, A, MK[15], RK[15]);
   round1(C, D, MK[16], RK[16]); round2(B, C, MK[17], RK[17]);
   round3(A, B, MK[18], RK[18]); round1(D, A, MK[19], RK[19]);
   round1(C, D, MK[20], RK[20]); round2(B, C, MK[21], RK[21]);
   round3(A, B, MK[22], RK[22]); round1(D, A, MK[23], RK[23]);
   round1(D, A, MK[27], RK[27]); round3(A, B, MK[26], RK[26]);
   round2(B, C, MK[25], RK[25]); round1(C, D, MK[24], RK[24]);
   round1(D, A, MK[31], RK[31]); round3(A, B, MK[30], RK[30]);
   round2(B, C, MK[29], RK[29]); round1(C, D, MK[28], RK[28]);
   round1(D, A, MK[35], RK[35]); round3(A, B, MK[34], RK[34]);
   round2(B, C, MK[33], RK[33]); round1(C, D, MK[32], RK[32]);
   round1(D, A, MK[39], RK[39]); round3(A, B, MK[38], RK[38]);
   round2(B, C, MK[37], RK[37]); round1(C, D, MK[36], RK[36]);
   round1(D, A, MK[43], RK[43]); round3(A, B, MK[42], RK[42]);
   round2(B, C, MK[41], RK[41]); round1(C, D, MK[40], RK[40]);
   round1(D, A, MK[47], RK[47]); round3(A, B, MK[46], RK[46]);
   round2(B, C, MK[45], RK[45]); round1(C, D, MK[44], RK[44]);
   out[ 0] = get_byte(0, A); out[ 1] = get_byte(1, A);
   out[ 2] = get_byte(2, A); out[ 3] = get_byte(3, A);
   out[ 4] = get_byte(0, B); out[ 5] = get_byte(1, B);
   out[ 6] = get_byte(2, B); out[ 7] = get_byte(3, B);
   out[ 8] = get_byte(0, C); out[ 9] = get_byte(1, C);
   out[10] = get_byte(2, C); out[11] = get_byte(3, C);
   out[12] = get_byte(0, D); out[13] = get_byte(1, D);
   out[14] = get_byte(2, D); out[15] = get_byte(3, D);
   }

/*************************************************
* CAST256 Decryption                             *
*************************************************/
void CAST256::decrypt(const byte in[BLOCKSIZE], byte out[BLOCKSIZE]) const
   {
   u32bit A = make_u32bit(in[ 0], in[ 1], in[ 2], in[ 3]),
          B = make_u32bit(in[ 4], in[ 5], in[ 6], in[ 7]),
          C = make_u32bit(in[ 8], in[ 9], in[10], in[11]),
          D = make_u32bit(in[12], in[13], in[14], in[15]);
   round1(C, D, MK[44], RK[44]); round2(B, C, MK[45], RK[45]);
   round3(A, B, MK[46], RK[46]); round1(D, A, MK[47], RK[47]);
   round1(C, D, MK[40], RK[40]); round2(B, C, MK[41], RK[41]);
   round3(A, B, MK[42], RK[42]); round1(D, A, MK[43], RK[43]);
   round1(C, D, MK[36], RK[36]); round2(B, C, MK[37], RK[37]);
   round3(A, B, MK[38], RK[38]); round1(D, A, MK[39], RK[39]);
   round1(C, D, MK[32], RK[32]); round2(B, C, MK[33], RK[33]);
   round3(A, B, MK[34], RK[34]); round1(D, A, MK[35], RK[35]);
   round1(C, D, MK[28], RK[28]); round2(B, C, MK[29], RK[29]);
   round3(A, B, MK[30], RK[30]); round1(D, A, MK[31], RK[31]);
   round1(C, D, MK[24], RK[24]); round2(B, C, MK[25], RK[25]);
   round3(A, B, MK[26], RK[26]); round1(D, A, MK[27], RK[27]);
   round1(D, A, MK[23], RK[23]); round3(A, B, MK[22], RK[22]);
   round2(B, C, MK[21], RK[21]); round1(C, D, MK[20], RK[20]);
   round1(D, A, MK[19], RK[19]); round3(A, B, MK[18], RK[18]);
   round2(B, C, MK[17], RK[17]); round1(C, D, MK[16], RK[16]);
   round1(D, A, MK[15], RK[15]); round3(A, B, MK[14], RK[14]);
   round2(B, C, MK[13], RK[13]); round1(C, D, MK[12], RK[12]);
   round1(D, A, MK[11], RK[11]); round3(A, B, MK[10], RK[10]);
   round2(B, C, MK[ 9], RK[ 9]); round1(C, D, MK[ 8], RK[ 8]);
   round1(D, A, MK[ 7], RK[ 7]); round3(A, B, MK[ 6], RK[ 6]);
   round2(B, C, MK[ 5], RK[ 5]); round1(C, D, MK[ 4], RK[ 4]);
   round1(D, A, MK[ 3], RK[ 3]); round3(A, B, MK[ 2], RK[ 2]);
   round2(B, C, MK[ 1], RK[ 1]); round1(C, D, MK[ 0], RK[ 0]);
   out[ 0] = get_byte(0, A); out[ 1] = get_byte(1, A);
   out[ 2] = get_byte(2, A); out[ 3] = get_byte(3, A);
   out[ 4] = get_byte(0, B); out[ 5] = get_byte(1, B);
   out[ 6] = get_byte(2, B); out[ 7] = get_byte(3, B);
   out[ 8] = get_byte(0, C); out[ 9] = get_byte(1, C);
   out[10] = get_byte(2, C); out[11] = get_byte(3, C);
   out[12] = get_byte(0, D); out[13] = get_byte(1, D);
   out[14] = get_byte(2, D); out[15] = get_byte(3, D);
   }

/*************************************************
* CAST256 Round Type 1                           *
*************************************************/
void CAST256::round1(u32bit& out, u32bit in, u32bit mask, u32bit rot)
   {
   u32bit temp = rotate_left(mask + in, rot);
   out  ^= (CAST_SBOX1[get_byte(0, temp)] ^ CAST_SBOX2[get_byte(1, temp)]) -
            CAST_SBOX3[get_byte(2, temp)] + CAST_SBOX4[get_byte(3, temp)];
   }

/*************************************************
* CAST256 Round Type 2                           *
*************************************************/
void CAST256::round2(u32bit& out, u32bit in, u32bit mask, u32bit rot)
   {
   u32bit temp = rotate_left(mask ^ in, rot);
   out  ^= (CAST_SBOX1[get_byte(0, temp)]  - CAST_SBOX2[get_byte(1, temp)] +
            CAST_SBOX3[get_byte(2, temp)]) ^ CAST_SBOX4[get_byte(3, temp)];
   }

/*************************************************
* CAST256 Round Type 3                           *
*************************************************/
void CAST256::round3(u32bit& out, u32bit in, u32bit mask, u32bit rot)
   {
   u32bit temp = rotate_left(mask - in, rot);
   out  ^= ((CAST_SBOX1[get_byte(0, temp)]  + CAST_SBOX2[get_byte(1, temp)]) ^
             CAST_SBOX3[get_byte(2, temp)]) - CAST_SBOX4[get_byte(3, temp)];
   }

/*************************************************
* CAST256 Key Schedule                           *
*************************************************/
void CAST256::set_key(const byte key[], u32bit length) throw(InvalidKeyLength)
   {
   if(!valid_keylength(length))
      throw InvalidKeyLength(name(), length);
   SecureBuffer<u32bit, 16> TMP;
   for(u32bit j = 0; j != length; j++)
      TMP[j/4] = (TMP[j/4] << 8) + key[j];

   u32bit A = TMP[0], B = TMP[1], C = TMP[2], D = TMP[3],
          E = TMP[4], F = TMP[5], G = TMP[6], H = TMP[7];
   for(u32bit j = 0; j != 48; j += 4)
      {
      round1(G, H, KEY_MASK[4*j+ 0], KEY_ROT[4*j+ 0]);
      round2(F, G, KEY_MASK[4*j+ 1], KEY_ROT[4*j+ 1]);
      round3(E, F, KEY_MASK[4*j+ 2], KEY_ROT[4*j+ 2]);
      round1(D, E, KEY_MASK[4*j+ 3], KEY_ROT[4*j+ 3]);
      round2(C, D, KEY_MASK[4*j+ 4], KEY_ROT[4*j+ 4]);
      round3(B, C, KEY_MASK[4*j+ 5], KEY_ROT[4*j+ 5]);
      round1(A, B, KEY_MASK[4*j+ 6], KEY_ROT[4*j+ 6]);
      round2(H, A, KEY_MASK[4*j+ 7], KEY_ROT[4*j+ 7]);
      round1(G, H, KEY_MASK[4*j+ 8], KEY_ROT[4*j+ 8]);
      round2(F, G, KEY_MASK[4*j+ 9], KEY_ROT[4*j+ 9]);
      round3(E, F, KEY_MASK[4*j+10], KEY_ROT[4*j+10]);
      round1(D, E, KEY_MASK[4*j+11], KEY_ROT[4*j+11]);
      round2(C, D, KEY_MASK[4*j+12], KEY_ROT[4*j+12]);
      round3(B, C, KEY_MASK[4*j+13], KEY_ROT[4*j+13]);
      round1(A, B, KEY_MASK[4*j+14], KEY_ROT[4*j+14]);
      round2(H, A, KEY_MASK[4*j+15], KEY_ROT[4*j+15]);

      RK[j  ] = (A % 32);
      RK[j+1] = (C % 32);
      RK[j+2] = (E % 32);
      RK[j+3] = (G % 32);
      MK[j  ] = H;
      MK[j+1] = F;
      MK[j+2] = D;
      MK[j+3] = B;
      }
   }

}
