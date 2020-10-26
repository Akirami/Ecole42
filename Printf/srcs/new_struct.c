/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   new_struct.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: emassard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/26 11:02:06 by emassard     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/26 11:02:27 by emassard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_flags
	*new_struct(t_flags *flags)
{
	if (!(flags = (t_flags *)malloc(sizeof(t_flags))))
		return (NULL);
	flags->star = 0;
	flags->zero = 0;
	flags->prec_zero = 0;
	flags->prec_zero_unsigned = 0;
	flags->prc_val_z = 0;
	flags->is_neg = 0;
	flags->is_neg_p = 0;
	flags->point = 0;
	flags->hexax = 0;
	flags->hex = 0;
	flags->ptr = 0;
	flags->minus = 0;
	flags->p_len = 0;
	flags->p_dec = 0;
	flags->p_len2 = 0;
	flags->p_dec2 = 0;
	flags->value = 0;
	flags->unsigned_value = 0;
	flags->arg_size = 0;
	flags->is_write = 0;
	flags->unsigned_int = 0;
	flags->p_zero = 0;
	return (flags);
}

void
	new_counter(t_count **counter)
{
	if (!(*counter = (t_count *)malloc(sizeof(t_count))))
		*counter = NULL;
	(*counter)->count = 0;
}
