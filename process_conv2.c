/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_conv2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 12:24:31 by jaelee            #+#    #+#             */
/*   Updated: 2018/12/20 18:30:07 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <stdio.h>

void	get_addr(t_pfinfo *input)
{
	unsigned long int val;

	val = va_arg(input->ap, unsigned long int);
	input->output = ultoa_base(val, 16);
	if (!input->output)
		return ;
	ft_strlower(input->output);
	print_addr(input);
}

void	get_chars(char type, t_pfinfo *input)
{
	char	ch;
	
	if (type == 's')
	{
		input->output = (char*)va_arg(input->ap, const char*);
		print_str(input);
	}
	else
	{
		ch = (char)va_arg(input->ap, int);
		print_char(input, ch);
	}
}
