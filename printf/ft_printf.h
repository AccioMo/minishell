/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 22:13:26 by zouddach          #+#    #+#             */
/*   Updated: 2023/11/21 10:45:58 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdint.h>
# include <unistd.h>

int		ft_printf(const char *s, ...);
int		ft_printf_putstr(char *str);
int		ft_printf_putchar(char c);
int		ft_printf_nbr(int n);
int		ft_printf_putadr(uintptr_t adr);
int		ft_printf_putunsigned(unsigned int n);
int		ft_printf_puthex(char c, unsigned int nbr);

#endif