/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: emassard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/13 15:55:51 by emassard     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/13 15:59:01 by emassard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <limits.h>
# include "../libft/includes/libft.h"
# define HEXA_MAJ  "0123456789ABCDEF"
# define HEXA_MINI  "0123456789abcdef"
# define DECI "0123456789"

typedef struct
{
	int		star;
	int		zero;
	int		prec_zero;
	int		prec_zero_unsigned;
	int		prc_val_z;
	int		is_neg;
	int		is_neg_p;
	int		point;
	int		minus;
	int		p_len;
	int		p_dec;
	int		p_len2;
	int		p_dec2;
	int64_t	value;
	int64_t	unsigned_value;
	int		unsigned_int;
	int		hexax;
	int		hex;
	int		ptr;
	int		arg_size;
	int		is_write;
	int		p_zero;
}			t_flags;
typedef struct
{
	int		count;
}			t_count;
int			ft_printf(const char *s, ...) __attribute__((format(printf,1,2)));
void		set_args_type1(char *str, t_flags *flags,
	va_list params2, t_count *counter);
void		ft_putnbr_base(int64_t nbr, char *base, t_count *counter);
void		ft_base_convert(uint64_t nbr, char *base,
	uint64_t i, t_count *counter);
int			size_int(int64_t n);
int			size_unsigned(int64_t n);
char		*ft_hexa(uint64_t nbr, char *base, uint64_t i);
t_flags		*new_struct(t_flags *flags);
void		new_counter(t_count **counter);
void		set_offset_int(t_flags *flags, t_count *counter);
void		write_int(t_flags *flags, t_count *counter);
void		write_int15(t_flags *flags, t_count *counter);
void		set_offset_str(t_flags *flags, char *str, t_count *counter);
void		write_str(t_flags *flags, char *str, t_count *counter);
int			my_test_star(t_flags *flags, int star_value);
void		ft_putstr_or_null(char *s, t_count *counter);
void		ft_putchar_count(char c, t_count *counter);
void		ft_putnbr_custom(int n, t_flags *flags, t_count *counter);
void		ft_putnbr_unsigned(uint64_t n, t_flags *flags, t_count *counter);
void		ft_base_p_convert(uint64_t nbr, char *base,
	uint64_t i, t_count *counter);
char		*char_convert(char c);

#endif
