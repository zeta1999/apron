/* ********************************************************************** */
/* numMPQ.h */
/* ********************************************************************** */

#ifndef _NUMMPQ_H_
#define _NUMMPQ_H_

#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <assert.h>

#include "num_types.h"
#include "numMPZ.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ====================================================================== */
/* Rational operations */
/* ====================================================================== */

static inline void numMPQ_canonicalize(numMPQ_t a)
{ mpq_canonicalize(a); }

static inline bool numMPQ_set_numintMPQ2(numMPQ_t a, numMPZ_t b, numMPZ_t c)
{
  numMPZ_set(numMPQ_numref(a),b);
  numMPZ_set(numMPQ_denref(a),c);
  numMPQ_canonicalize(a);
  return true;
}

/* ====================================================================== */
/* Assignement */
/* ====================================================================== */
static inline void numMPQ_set(numMPQ_t a, numMPQ_t b)
{ mpq_set(a,b); }
static inline void numMPQ_set_array(numMPQ_t* a, numMPQ_t* b, size_t size)
{
  size_t i;
  for (i=0; i<size; i++) mpq_set(a[i],b[i]);
}
static inline void numMPQ_set_int(numMPQ_t a, long int i)
{ mpq_set_si(a,i,1); }

/* ====================================================================== */
/* Constructors and Destructors */
/* ====================================================================== */

static inline void numMPQ_init(numMPQ_t a)
{ mpq_init(a); }
static inline void numMPQ_init_array(numMPQ_t* a, size_t size)
{
  size_t i;
  for (i=0; i<size; i++) mpq_init(a[i]);
}
static inline void numMPQ_init_set(numMPQ_t a, numMPQ_t b)
{ mpq_init(a); mpq_set(a,b); }
static inline void numMPQ_init_set_int(numMPQ_t a, long int i)
{ mpq_init(a); mpq_set_si(a,i,1); }

static inline void numMPQ_clear(numMPQ_t a)
{ mpq_clear(a); }
static inline void numMPQ_clear_array(numMPQ_t* a, size_t size)
{
  size_t i;
  for (i=0; i<size; i++) mpq_clear(a[i]);
}
static inline void numMPQ_swap(numMPQ_t a, numMPQ_t b)
{ mpq_swap(a,b); }

/* ====================================================================== */
/* Arithmetic Operations */
/* ====================================================================== */

static inline void numMPQ_neg(numMPQ_t a, numMPQ_t b)
{ mpq_neg(a,b); }
static inline void numMPQ_inv(numMPQ_t a, numMPQ_t b)
{ mpq_inv(a,b); }
static inline void numMPQ_abs(numMPQ_t a, numMPQ_t b)
{ mpq_abs(a,b); }
static inline void numMPQ_add(numMPQ_t a, numMPQ_t b, numMPQ_t c)
{ mpq_add(a,b,c); }
void numMPQ_add_uint(numMPQ_t a, numMPQ_t b, unsigned long int c);
static inline void numMPQ_sub(numMPQ_t a, numMPQ_t b, numMPQ_t c)
{ mpq_sub(a,b,c); }
void numMPQ_sub_uint(numMPQ_t a, numMPQ_t b, unsigned long int c);
static inline void numMPQ_mul(numMPQ_t a, numMPQ_t b, numMPQ_t c)
{ mpq_mul(a,b,c); }
static inline void numMPQ_mul_2(numMPQ_t a, numMPQ_t b)
{ mpq_mul_2exp(a,b,1); }
static inline void numMPQ_div(numMPQ_t a, numMPQ_t b, numMPQ_t c)
{ mpq_div(a,b,c); }
static inline void numMPQ_div_2(numMPQ_t a, numMPQ_t b)
{ mpq_div_2exp(a,b,1); }
static inline void numMPQ_min(numMPQ_t a, numMPQ_t b, numMPQ_t c)
{ mpq_set(a, mpq_cmp(b,c)<=0 ? b : c); }
static inline void numMPQ_max(numMPQ_t a, numMPQ_t b, numMPQ_t c)
{ mpq_set(a, mpq_cmp(b,c)>=0 ? b : c); }
static inline void numMPQ_floor(numMPQ_t a, numMPQ_t b)
{
  numMPZ_fdiv_q(numMPQ_numref(a),numMPQ_numref(b),numMPQ_denref(b));
  numMPZ_set_int(numMPQ_denref(a),1);
}
static inline void numMPQ_ceil(numMPQ_t a, numMPQ_t b)
{
  numMPZ_cdiv_q(numMPQ_numref(a),numMPQ_numref(b),numMPQ_denref(b));
  numMPZ_set_int(numMPQ_denref(a),1);
}
static inline void numMPQ_trunc(numMPQ_t a, numMPQ_t b)
{
  numMPZ_tdiv_q(numMPQ_numref(a),numMPQ_numref(b),numMPQ_denref(b));
  numMPZ_set_int(numMPQ_denref(a),1);
}
void numMPQ_sqrt(numMPQ_t up, numMPQ_t down, numMPQ_t b);
static inline void numMPQ_mul_2exp(numMPQ_t a, numMPQ_t b, int c)
{
  if (c>=0) mpq_mul_2exp(a,b,c);
  else mpq_div_2exp(a,b,-c);
}

/* ====================================================================== */
/* Arithmetic Tests */
/* ====================================================================== */

static inline int numMPQ_sgn(numMPQ_t a)
{ return mpq_sgn(a); }
static inline int numMPQ_cmp(numMPQ_t a, numMPQ_t b)
{ return mpq_cmp(a,b); }
static inline int numMPQ_cmp_int(numMPQ_t a, long int b)
{ return mpq_cmp_si(a,b,1); }
static inline bool numMPQ_equal(numMPQ_t a, numMPQ_t b)
{ return mpq_equal(a,b); }
static inline bool numMPQ_integer(numMPQ_t a)
{ return (mpz_cmp_ui(mpq_denref(a),1)==0); }
int numMPQ_hash(numMPQ_t a);

/* ====================================================================== */
/* Printing */
/* ====================================================================== */

static inline void numMPQ_print(numMPQ_t a)
{ mpq_out_str(stdout,10,a); }
static inline void numMPQ_fprint(FILE* stream, numMPQ_t a)
{ mpq_out_str(stream,10,a); }
int numMPQ_snprint(char* s, size_t size, numMPQ_t a);

/* ====================================================================== */
/* Serialization */
/* ====================================================================== */

static inline unsigned char numMPQ_serialize_id(void)
{ return 0x1f; }

size_t numMPQ_serialize(void* dst, numMPQ_t src);
size_t numMPQ_deserialize(numMPQ_t dst, const void* src);

/* not the exact size of serialized data, but a sound overapproximation */
static inline size_t numMPQ_serialized_size(numMPQ_t a)
{
  return
    (mpz_sizeinbase(mpq_numref(a),2)+mpz_sizeinbase(mpq_denref(a),2))/8+
    9+2*sizeof(mp_limb_t);
}

size_t numMPQ_serialize_array(void* dst, numMPQ_t* src, size_t size);
size_t numMPQ_deserialize_array(numMPQ_t* dst, const void* src, size_t size);
size_t numMPQ_serialized_size_array(numMPQ_t* src, size_t size);

/* ====================================================================== */
/* Conversions */
/* ====================================================================== */

bool lint_fits_numMPQ(long int a);
bool llint_fits_numMPQ(long long int a);
bool mpz_fits_numMPQ(mpz_t a);
bool lfrac_fits_numMPQ(long int i, long int j);
bool llfrac_fits_numMPQ(long long int i, long long int j);
bool mpq_fits_numMPQ(mpq_t a);
bool double_fits_numMPQ(double k);
bool ldouble_fits_numMPQ(long double k);
bool mpfr_fits_numMPQ(mpfr_t a, num_internal_t intern);
bool numD_fits_numMPQ(numD_t a);
bool numMPQ_fits_numMPQ(numMPQ_t a);
bool numMPFR_fits_numMPQ(numMPFR_t a, num_internal_t intern);

bool numMPQ_fits_lint(numMPQ_t a);
bool numMPQ_fits_llint(numMPQ_t a);
bool numMPQ_fits_mpz(numMPQ_t a);
bool numMPQ_fits_lfrac(numMPQ_t a);
bool numMPQ_fits_llfrac(numMPQ_t a);
bool numMPQ_fits_mpq(numMPQ_t a);
bool numMPQ_fits_float(numMPQ_t a);
bool numMPQ_fits_double(numMPQ_t a);
bool numMPQ_fits_ldouble(numMPQ_t a);
bool numMPQ_fits_mpfr(numMPQ_t a);
bool numMPQ_fits_numD(numMPQ_t a);
bool numMPQ_fits_numMPQ(numMPQ_t a);
bool numMPQ_fits_numMPFR(numMPQ_t a);

bool numMPQ_set_lint(numMPQ_t a, long int i, num_internal_t intern);
bool numMPQ_set_llint(numMPQ_t a, long long int i, num_internal_t intern);
bool numMPQ_set_mpz(numMPQ_t a, mpz_t b, num_internal_t intern);
bool numMPQ_set_lfrac(numMPQ_t a, long int i, long int j, num_internal_t intern);
bool numMPQ_set_llfrac(numMPQ_t a, long long int i, long long int j, num_internal_t intern);
bool numMPQ_set_mpq(numMPQ_t a, mpq_t b, num_internal_t intern);
bool numMPQ_set_double(numMPQ_t a, double k, num_internal_t intern);
bool numMPQ_set_ldouble(numMPQ_t a, long double k, num_internal_t intern);
bool numMPQ_set_mpfr(numMPQ_t a, mpfr_t b, num_internal_t intern);
bool numMPQ_set_numD(numMPQ_t a, numD_t b, num_internal_t intern);
bool numMPQ_set_numMPQ(numMPQ_t a, numMPQ_t b, num_internal_t intern);
bool numMPQ_set_numMPFR(numMPQ_t a, numMPFR_t b, num_internal_t intern);

bool lint_set_numMPQ(long int* a, numMPQ_t b, num_internal_t intern);
bool llint_set_numMPQ(long long int* a, numMPQ_t b, num_internal_t intern);
bool mpz_set_numMPQ(mpz_t a, numMPQ_t b, num_internal_t intern);
bool lfrac_set_numMPQ(long int* i, long int* j, numMPQ_t b, num_internal_t intern);
bool llfrac_set_numMPQ(long long int* i, long long int* j, numMPQ_t b, num_internal_t intern);
bool mpq_set_numMPQ(mpq_t a, numMPQ_t b, num_internal_t intern);
bool double_set_numMPQ(double* a, numMPQ_t b, num_internal_t intern);
bool ldouble_set_numMPQ(long double* a, numMPQ_t b, num_internal_t intern);
bool mpfr_set_numMPQ(mpfr_t a, numMPQ_t b, num_internal_t intern);
bool numD_set_numMPQ(numD_t a, numMPQ_t b, num_internal_t intern);
bool numMPQ_set_numMPQ(numMPQ_t a, numMPQ_t b, num_internal_t intern);
bool numMPFR_set_numMPQ(numMPFR_t a, numMPQ_t b, num_internal_t intern);

/* ********************************************************************** */
/* Underlying integer */
/* ********************************************************************** */

/* ====================================================================== */
/* Assignement */
/* ====================================================================== */

static inline void numintMPQ_set(numintMPQ_t a, numintMPQ_t b)
	      { numMPZ_set(a,b); }
static inline void numintMPQ_set_array(numintMPQ_t* a, numintMPQ_t* b, size_t size)
	      { numMPZ_set_array(a,b,size); }
static inline void numintMPQ_set_int(numintMPQ_t a, long int i)
	      { numMPZ_set_int(a,i); }

/* ====================================================================== */
/* Constructors and Destructors */
/* ====================================================================== */

static inline void numintMPQ_init(numintMPQ_t a)
	      { numMPZ_init(a); }
static inline void numintMPQ_init_array(numintMPQ_t* a, size_t size)
	      { numMPZ_init_array(a,size); }
static inline void numintMPQ_init_set(numintMPQ_t a, numintMPQ_t b)
	      { numMPZ_init_set(a,b); }
static inline void numintMPQ_init_set_int(numintMPQ_t a, long int i)
	      { numMPZ_init_set_int(a,i); }

static inline void numintMPQ_clear(numintMPQ_t a)
	      { numMPZ_clear(a); }
static inline void numintMPQ_clear_array(numintMPQ_t* a, size_t size)
	      { numMPZ_clear_array(a,size); }

static inline void numintMPQ_swap(numintMPQ_t a, numintMPQ_t b)
	      { numMPZ_swap(a,b); }

/* ====================================================================== */
/* Arithmetic Operations */
/* ====================================================================== */

static inline void numintMPQ_neg(numintMPQ_t a, numintMPQ_t b)
	      { numMPZ_neg(a,b); }
static inline void numintMPQ_abs(numintMPQ_t a, numintMPQ_t b)
	      { numMPZ_abs(a,b); }
static inline void numintMPQ_add(numintMPQ_t a, numintMPQ_t b, numintMPQ_t c)
	      { numMPZ_add(a,b,c); }
static inline void numintMPQ_add_uint(numintMPQ_t a, numintMPQ_t b, unsigned long int c)
	      { numMPZ_add_uint(a,b,c); }
static inline void numintMPQ_sub(numintMPQ_t a, numintMPQ_t b, numintMPQ_t c)
	      { numMPZ_sub(a,b,c); }
static inline void numintMPQ_sub_uint(numintMPQ_t a, numintMPQ_t b, unsigned long int c)
	      { numMPZ_sub_uint(a,b,c); }
static inline void numintMPQ_mul(numintMPQ_t a, numintMPQ_t b, numintMPQ_t c)
	      { numMPZ_mul(a,b,c); }
static inline void numintMPQ_mul_2(numintMPQ_t a, numintMPQ_t b)
	      { numMPZ_mul_2(a,b); }
static inline void numintMPQ_div(numintMPQ_t a, numintMPQ_t b, numintMPQ_t c)
	      { numMPZ_cdiv_q(a,b,c); }
static inline void numintMPQ_div_2(numintMPQ_t a, numintMPQ_t b)
	      { numMPZ_cdiv_2(a,b); }
static inline void numintMPQ_min(numintMPQ_t a, numintMPQ_t b, numintMPQ_t c)
	      { numMPZ_min(a,b,c); }
static inline void numintMPQ_max(numintMPQ_t a, numintMPQ_t b, numintMPQ_t c)
	      { numMPZ_max(a,b,c); }
static inline void numintMPQ_mul_2exp(numintMPQ_t a, numintMPQ_t b, int c)
	      { numMPZ_mul_2exp(a,b,c); }

static inline void numintMPQ_floor(numintMPQ_t a, numintMPQ_t b)
	      { numMPZ_set(a,b); }
static inline void numintMPQ_ceil(numintMPQ_t a, numintMPQ_t b)
	      { numMPZ_set(a,b); }
static inline void numintMPQ_trunc(numintMPQ_t a, numintMPQ_t b)
	      { numMPZ_set(a,b); }
static inline void numintMPQ_sqrt(numintMPQ_t up, numintMPQ_t down, numintMPQ_t b)
	      { numMPZ_sqrt(up,down,b); }

static inline void numintMPQ_divexact(numintMPQ_t a, numintMPQ_t b, numintMPQ_t c)
	      { numMPZ_divexact(a,b,c); }
static inline void numintMPQ_mod(numintMPQ_t a, numintMPQ_t b, numintMPQ_t c)
	      { numMPZ_mod(a,b,c); }
static inline void numintMPQ_gcd(numintMPQ_t a, numintMPQ_t b, numintMPQ_t c)
	      { numMPZ_gcd(a,b,c); }
static inline void numintMPQ_lcm(numintMPQ_t a, numintMPQ_t b, numintMPQ_t c)
	      { numMPZ_lcm(a,b,c); }
static inline void numintMPQ_fdiv_q(numintMPQ_t a, numintMPQ_t b, numintMPQ_t c)
	      { numMPZ_fdiv_q(a,b,c); }
static inline void numintMPQ_cdiv_q(numintMPQ_t q, numintMPQ_t a, numintMPQ_t b)
	      { numMPZ_cdiv_q(q,a,b); }
static inline void numintMPQ_tdiv_q(numintMPQ_t q, numintMPQ_t a, numintMPQ_t b)
	      { numMPZ_tdiv_q(q,a,b); }
static inline void numintMPQ_cdiv_qr(numintMPQ_t q, numintMPQ_t r, numintMPQ_t a, numintMPQ_t b)
	      { numMPZ_cdiv_qr(q,r,a,b); }
static inline void numintMPQ_cdiv_2(numintMPQ_t a, numintMPQ_t b)
	      { numMPZ_cdiv_2(a,b); }
static inline void numintMPQ_cdiv_q_2exp(numintMPQ_t a, numintMPQ_t b, unsigned long int c)
	      { numMPZ_cdiv_q_2exp(a,b,c); }
static inline void numintMPQ_fdiv_q_2exp(numintMPQ_t a, numintMPQ_t b, unsigned long int c)
	      { numMPZ_fdiv_q_2exp(a,b,c); }

/* ====================================================================== */
/* Arithmetic Tests */
/* ====================================================================== */

static inline int numintMPQ_sgn(numintMPQ_t a)
	 { return numMPZ_sgn(a); }
static inline int numintMPQ_cmp(numintMPQ_t a, numintMPQ_t b)
      { return numMPZ_cmp(a,b); }
static inline int numintMPQ_cmp_int(numintMPQ_t a, long int b)
      { return numMPZ_cmp_int(a,b); }
static inline bool numintMPQ_equal(numintMPQ_t a, numintMPQ_t b)
      { return numMPZ_equal(a,b); }
static inline bool numintMPQ_integer(numintMPQ_t a)
      { return true; }
static inline int numintMPQ_hash(numintMPQ_t a)
      { return numMPZ_hash(a); }

/* ====================================================================== */
/* Printing */
/* ====================================================================== */

static inline void numintMPQ_print(numintMPQ_t a)
	      { numMPZ_print(a); }
static inline void numintMPQ_fprint(FILE* stream, numintMPQ_t a)
	      { numMPZ_fprint(stream, a); }
static inline int numintMPQ_snprint(char* s, size_t size, numintMPQ_t a)
      { return numMPZ_snprint(s,size,a); }

/* ====================================================================== */
/* Serialization */
/* ====================================================================== */

static inline unsigned char numintMPQ_serialize_id(void)
{ return numMPZ_serialize_id(); }

static inline size_t numintMPQ_serialize(void* dst, numintMPQ_t src)
{ return numMPZ_serialize(dst,src); }

static inline size_t numintMPQ_deserialize(numintMPQ_t dst, const void* src)
{ return numMPZ_deserialize(dst,src); }

static inline size_t numintMPQ_serialized_size(numintMPQ_t src)
{ return numMPZ_serialized_size(src); }

static inline size_t numintMPQ_serialize_array(void* dst, numintMPQ_t* src, size_t size)
{ return numMPZ_serialize_array(dst,src,size); }

static inline size_t numintMPQ_deserialize_array(numintMPQ_t* dst, const void* src, size_t size)
{ return numMPZ_deserialize_array(dst,src,size); }

static inline size_t numintMPQ_serialized_size_array(numintMPQ_t* src, size_t size)
{ return numMPZ_serialized_size_array(src,size); }

/* ====================================================================== */
/* Conversions */
/* ====================================================================== */

static inline bool lint_fits_numintMPQ(long int a)
{ return lint_fits_numMPZ(a); }
static inline bool llint_fits_numintMPQ(long long int a)
{ return llint_fits_numMPZ(a); }
static inline bool mpz_fits_numintMPQ(mpz_t a)
{ return mpz_fits_numMPZ(a); }
static inline bool lfrac_fits_numintMPQ(long int i, long int j)
{ return lfrac_fits_numMPZ(i,j); }
static inline bool llfrac_fits_numintMPQ(long long int i, long long int j)
{ return llfrac_fits_numMPZ(i,j); }
static inline bool mpq_fits_numintMPQ(mpq_t a)
{ return mpq_fits_numMPZ(a); }
static inline bool double_fits_numintMPQ(double a)
{ return double_fits_numMPZ(a); }
static inline bool ldouble_fits_numintMPQ(long double a)
{ return ldouble_fits_numMPZ(a); }
static inline bool mpfr_fits_numintMPQ(mpfr_t a, num_internal_t intern)
{ return mpfr_fits_numMPZ(a,intern); }

static inline bool numintMPQ_fits_lint(numintMPQ_t a)
{ return numMPZ_fits_lint(a); }
static inline bool numintMPQ_fits_llint(numintMPQ_t a)
{ return numMPZ_fits_llint(a); }
static inline bool numintMPQ_fits_mpz(numintMPQ_t a)
{ return numMPZ_fits_mpz(a); }
static inline bool numintMPQ_fits_lfrac(numintMPQ_t a)
{ return numMPZ_fits_lfrac(a); }
static inline bool numintMPQ_fits_llfrac(numintMPQ_t a)
{ return numMPZ_fits_llfrac(a); }
static inline bool numintMPQ_fits_mpq(numintMPQ_t a)
{ return numMPZ_fits_mpq(a); }
static inline bool numintMPQ_fits_double(numintMPQ_t a)
{ return numMPZ_fits_double(a); }
static inline bool numintMPQ_fits_ldouble(numintMPQ_t a)
{ return numMPZ_fits_ldouble(a); }
static inline bool numintMPQ_fits_mpfr(numintMPQ_t a)
{ return numMPZ_fits_mpfr(a); }

static inline bool numintMPQ_set_lint(numintMPQ_t a, long int b, num_internal_t intern)
{ return numMPZ_set_lint(a,b,intern); }
static inline bool numintMPQ_set_llint(numintMPQ_t a, long long int b, num_internal_t intern)
{ return numMPZ_set_llint(a,b,intern); }
static inline bool numintMPQ_set_mpz(numintMPQ_t a, mpz_t b, num_internal_t intern)
{ return numMPZ_set_mpz(a,b,intern); }
static inline bool numintMPQ_set_lfrac(numintMPQ_t a, long int i, long int j, num_internal_t intern)
{ return numMPZ_set_lfrac(a,i,j,intern); }
static inline bool numintMPQ_set_llfrac(numintMPQ_t a, long long int i, long long int j, num_internal_t intern)
{ return numMPZ_set_llfrac(a,i,j,intern); }
static inline bool numintMPQ_set_mpq(numintMPQ_t a, mpq_t b, num_internal_t intern)
{ return numMPZ_set_mpq(a,b,intern); }
static inline bool numintMPQ_set_double(numintMPQ_t a, double b, num_internal_t intern)
{ return numMPZ_set_double(a,b,intern); }
static inline bool numintMPQ_set_ldouble(numintMPQ_t a, long double b, num_internal_t intern)
{ return numMPZ_set_ldouble(a,b,intern); }
static inline bool numintMPQ_set_mpfr(numintMPQ_t a, mpfr_t b, num_internal_t intern)
{ return numMPZ_set_mpfr(a,b,intern); }

static inline bool lint_set_numintMPQ(long int* a, numintMPQ_t b, num_internal_t intern)
{ return lint_set_numMPZ(a,b,intern); }
static inline bool llint_set_numintMPQ(long long int* a, numintMPQ_t b, num_internal_t intern)
{ return llint_set_numMPZ(a,b,intern); }
static inline bool mpz_set_numintMPQ(mpz_t a, numintMPQ_t b, num_internal_t intern)
{ return mpz_set_numMPZ(a,b,intern); }
static inline bool lfrac_set_numintMPQ(long int* i, long int* j, numintMPQ_t b, num_internal_t intern)
{ return lfrac_set_numMPZ(i,j,b,intern); }
static inline bool llfrac_set_numintMPQ(long long int* i, long long int* j, numintMPQ_t b, num_internal_t intern)
{ return llfrac_set_numMPZ(i,j,b,intern); }
static inline bool mpq_set_numintMPQ(mpq_t a, numintMPQ_t b, num_internal_t intern)
{ return mpq_set_numMPZ(a,b,intern); }
static inline bool double_set_numintMPQ(double* a, numintMPQ_t b, num_internal_t intern)
{ return double_set_numMPZ(a,b,intern); }
static inline bool ldouble_set_numintMPQ(long double* a, numintMPQ_t b, num_internal_t intern)
{ return ldouble_set_numMPZ(a,b,intern); }
static inline bool mpfr_set_numintMPQ(mpfr_t a, numintMPQ_t b, num_internal_t intern)
{ return mpfr_set_numMPZ(a,b,intern); }

#ifdef __cplusplus
}
#endif

#endif