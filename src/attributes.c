/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attributes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 10:24:00 by zcanales          #+#    #+#             */
/*   Updated: 2022/01/04 19:20:51 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include "../include/minishell.h"

void	attributes()
{
    struct termios old;
    struct termios changed;

	 if (tcgetattr(0, &old)==-1) 
	 {
    perror ("ioctl/TCGETA old:");
    return ;
	 }

	 if (tcgetattr(0, &changed)==-1)
	 {
  	  perror ("ioctl/TCGETA changed:");
   	 return ;
	 }

	  changed.c_lflag=changed.c_lflag & ~ICANON & ECHO; // ~ICANON | ECHO;
	   changed.c_cc[VQUIT] = 0;
   	 if (tcsetattr(0,TCSANOW, &changed)==-1) 
    perror ("ioctl/TCSETA changed:");

//	  tcsetattr(0,TCSANOW, &old);
}
