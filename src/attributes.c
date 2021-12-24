/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attributes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 10:24:00 by zcanales          #+#    #+#             */
/*   Updated: 2021/12/24 10:50:54 by zcanales         ###   ########.fr       */
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
    struct termios vieja;
    struct termios actual;

	 if (tcgetattr(0, &vieja)==-1) 
	 {
    perror ("ioctl/TCGETA vieja:");
    return ;
	 }

	 if (tcgetattr(0, &actual)==-1)
	 {
  	  perror ("ioctl/TCGETA actual:");
   	 return ;
	 }

	  actual.c_lflag=actual.c_lflag & ~ICANON & ECHO; // ~ICANON | ECHO;
	   actual.c_cc[VQUIT] = 0;
   	 if (tcsetattr(0,TCSANOW, &actual)==-1) 
    perror ("ioctl/TCSETA actual:");

//	  tcsetattr(0,TCSANOW, &vieja);



}
