#ifndef __UTIL_H__
#define __UTIL_H__

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
#define EXTERN_C_BEGIN extern "C" {
#define EXTERN_C_END }
#else
#define EXTERN_C_BEGIN
#define EXTERN_C_END
#endif

/* concatenate the values of the arguments into one */
#define UTIL_PRIMITIVE_CAT(a, ...) a##__VA_ARGS__
#define UTIL_CAT(a, ...) UTIL_PRIMITIVE_CAT(a, __VA_ARGS__)

/**
 * @brief Get a pointer to a structure containing the element
 *
 * Example:
 *
 *	struct foo {
 *		int bar;
 *	};
 *
 *	struct foo my_foo;
 *	int *ptr = &my_foo.bar;
 *
 *	struct foo *container = CONTAINER_OF(ptr, struct foo, bar);
 *
 * Above, @p container points at @p my_foo.
 *
 * @param ptr pointer to a structure element
 * @param type name of the type that @p ptr is an element of
 * @param field the name of the field within the struct @p ptr points to
 * @return a pointer to the structure that contains @p ptr
 */
#define CONTAINER_OF(ptr, type, field) \
	((type *)(((char *)(ptr)) - offsetof(type, field)))

/**
 * @brief Value of @p x rounded up to the next multiple of @p align,
 *        which must be a power of 2.
 */
#define ROUND_UP(x, align)                                   \
	(((uintptr_t)(x) + ((uintptr_t)(align) - 1)) & \
	 ~((uintptr_t)(align) - 1))

/**
 * @brief Value of @p x rounded down to the previous multiple of @p
 *        align, which must be a power of 2.
 */
#define ROUND_DOWN(x, align)                                 \
	((uintptr_t)(x) & ~((uintptr_t)(align) - 1))


#ifndef MAX
/**
 * @brief Obtain the maximum of two values.
 *
 * @note Arguments are evaluated twice. Use Z_MAX for a GCC-only, single
 * evaluation version
 *
 * @param a First value.
 * @param b Second value.
 *
 * @returns Maximum value of @p a and @p b.
 */
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
/**
 * @brief Obtain the minimum of two values.
 *
 * @note Arguments are evaluated twice. Use Z_MIN for a GCC-only, single
 * evaluation version
 *
 * @param a First value.
 * @param b Second value.
 *
 * @returns Minimum value of @p a and @p b.
 */
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef BIT
#if defined(_ASMLANGUAGE)
#define BIT(n)  (1 << (n))
#else
/**
 * @brief Unsigned integer with bit position @p n set (signed in
 * assembly language).
 */
#define BIT(n)  (1UL << (n))
#endif
#endif

/** @brief 64-bit unsigned integer with bit position @p _n set. */
#define BIT64(_n) (1ULL << (_n))

/**
 * @brief Set or clear a bit depending on a boolean value
 *
 * The argument @p var is a variable whose value is written to as a
 * side effect.
 *
 * @param var Variable to be altered
 * @param bit Bit number
 * @param set if 0, clears @p bit in @p var; any other value sets @p bit
 */
#define WRITE_BIT(var, bit, set) \
	((var) = (set) ? ((var) | BIT(bit)) : ((var) & ~BIT(bit)))

/**
 * @brief Bit mask with bits 0 through <tt>n-1</tt> (inclusive) set,
 * or 0 if @p n is 0.
 */
#define BIT_MASK(n) (BIT(n) - 1UL)

/**
 * @brief 64-bit bit mask with bits 0 through <tt>n-1</tt> (inclusive) set,
 * or 0 if @p n is 0.
 */
#define BIT64_MASK(n) (BIT64(n) - 1ULL)

#endif
