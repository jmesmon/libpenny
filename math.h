#ifndef PENNY_MATH_H_
#define PENNY_MATH_H_

/* potential for overflow when doing (n + d - 1) */
#define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))
#if 0
/* If n == 0, does not result in 0 like it should.  */
#define DIV_ROUND_UP(n,d) (((n) - 1)/(d) + 1)
#define DIV_ROUND_UP(n,d) ((n) / (d) + ((n)%(d) ? 1 : 0))
#endif

#if 0
/* @d is assumed to be positive.
 * If @n is negative, this results in 0.
 * Otherwise, DIV_ROUND_UP is used normally
 */
#define DIV_ROUND_UP_POS_OR_ZERO(n,d)
#endif


static inline uint16_t linear_interp_u16(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x)
{
	/* multiplication overflow */
	return (y2 - y1) * (uint32_t)x / (x2 - x1);
}

#define LINEAR_INTERPOLATE(x1, y1, x2, y2, x) \
	(((y2)-(y1)) * (x) / ((x2)-(x1)))

#define DIV_OR_ZERO(n, d) ((n < 0)?0:(n)/(d))

#define SUB_SAT(a,b) ({					\
		typeof(a) __sub_sat_a = (a);		\
		typeof(b) __sub_sat_b = (b);		\
		(__sub_sat_a > __sub_sat_b)		\
			? __sub_sat_a - __sub_sat_b	\
			: 0;				\
	})

//#define pow4(x) (2ull << (2*(x)-1))
#define pow4(x) (2ULL << (2*(x)-1))

#define SAT_CEIL(val, max) ({		\
		typeof(val) __val = val;\
		if (__val > max)	\
			__val = max;	\
		__val; })

/* WARNING: widens to 'int' */
#define PROMOTE(v, expr_constraint) \
	(1 ? (v) : (expr_constraint))

#define EXPR_IS_SIGNED(e) (PROMOTE(-1, e) < PROMOTE(1, e))
#define TYPE_IS_SIGNED(t) ((t)-1 < (t) 1)

#if 0
#define EXPR_UMAX(expr) (~((TYPE_OF_UNSIGNED(expr))0))
#define EXPR_MAX(expr)  

#define TYPE_UMAX(t)
#define TYPE_MAX(t)

#define SAT_ADD(x, y) ({						\
		check_types_match(x, y);				\
		typeof(x) __sat_add_x = x;				\
		typeof(y) __sat_add_y = y;				\
		TYPE_UNION(x, y) __sat_add_r;				\
		if (EXPR_MAX(x) - __sat_add_x < __sat_add_y)		\
			r = EXPR_MAX(x);				\
		else if (EXPR_MIN(x) + __sat_add_x < __sat_add_y)	\
			r = EXPR_MIN(x);				\
		else							\
			r = x + y;					\
		r;							\
		})
#endif

#define MEGA(x) ((x) * 1000000)
#define KILO(x) ((x) *    1000)

#define ABS(x) ((x) < 0?(-(x)) : (x))

#define MAX(x, y) ((x) > (y)?(x):(y))
#define MAX3(x, y, z) MAX(MAX(x, y), z)
#define MAX4(a, b, c, d) MAX(MAX(a,b),MAX(c,d))
#define MAX6(a,b,c,d,e,f) MAX(MAX4(a,b,c,d),MAX(e,f))
#define MAX8(a,b,c,d,e,f,g,h) MAX(MAX4(a,b,c,d),MAX4(e,f,g,h))

#define MIN(x,y) ((x) < (y)?(x):(y))
#define MIN3(a, b, c) MIN(MIN(a,b),c)
#define MIN4(a, b, c, d) MIN(MIN(a,b),MIN(c,d))
#define MIN6(a,b,c,d,e,f) MIN(MIN4(a,b,c,d),MIN(e,f))
#define MIN8(a,b,c,d,e,f,g,h) MIN(MIN4(a,b,c,d),MIN4(e,f,g,h))

#endif
