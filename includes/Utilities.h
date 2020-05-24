/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nallani@student.s19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 02:07:43 by nathan            #+#    #+#             */
/*   Updated: 2020/05/24 02:56:34 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef UTILITIES_H
# define UTILITIES_H

#include <iostream>
# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600


# ifndef NDEBUG
#   define M_Assert(Expr, Msg) \
	__M_Assert(#Expr, Expr, __FILE__, __LINE__, Msg)
#else
#   define M_Assert(Expr, Msg) ;
#endif

#endif
