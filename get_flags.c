/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 17:50:53 by jaelee            #+#    #+#             */
/*   Updated: 2018/12/01 12:45:49 by dolee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_prec(const char *fmt, t_pfinfo *input)
{
	if (input->flags.prec >= 0)
	{
		input->i++;
		return ;
	}
	else if (fmt[input->i] == '.' && fmt[input->i + 1] == '*')
	{
		input->flags.prec = va_arg(input->ap[1], int); //TODO need check
		input->i += 2;
	}
	else if (fmt[input->i] == '.' && fmt[input->i + 1] >= '1'
			&& fmt[input->i + 1] <= '9')
	{
		input->i++;
		input->flags.prec = ft_atoi(fmt + input->i);
		while (ft_strchr(NBR, fmt[input->i]))
			input->i++;
	}
}

void	get_width(const char *fmt, t_pfinfo *input)
{
	//TODO not sure if it's correct!!!
	input->flags.width = va_arg(input->ap[1], int);
	input->i++;
}

void	get_flags(const char *fmt, t_pfinfo *input)
{
	init_flags(input->flags);
	while (ft_strchr(FLAGS, fmt[input->i]))
	{
		fmt[input->i] == '#' ? input->flags.zero = 1 : 0;
		input->flags.zero = fmt[input->i] == '0' ? 1 : 0;
		input->flags.minus = fmt[input->i] == '-' ? 1 : 0;
		input->flags.plus = fmt[input->i] == '+' ? 1 : 0;
		input->flags.space = fmt[input->i] == ' ' ? 1 : 0;
		fmt[input->i] == '*' ? get_width(fmt, input) : 0;
		if (fmt[input->i] == '.')
			process_prec(fmt, input);
		else if (fmt[input->i] >= '1' && fmt[input->i] <= '9')
		{
			input->flags.width = ft_atoi(fmt + input->i);
			while (fmt[input->i] >= '1' && fmt[input->i] <= '9')
				input->i++;
		}
		else
			input->i++;
	}
}

void	get_mod(const char *fmt, t_pfinfo *input) //TODO need check!!!
{
	if (fmt[input->i] == 'l' && fmt[input->i + 1] != 'l')
		input->mod = mod_l;
	else if (fmt[input->i] == 'l' && fmt[input->i + 1] == 'l')
		input->mod = mod_ll;
	else if (fmt[input->i] == 'h' && fmt[input->i + 1] != 'h')
		input->mod = mod_h;
	else if (fmt[input->i] == 'h' && fmt[input->i + 1] == 'h')
		input->mod = mod_hh;
	else if (fmt[input->i] == 'L')
		input->mod = mod_L;
}