/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attributes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 10:24:00 by zcanales          #+#    #+#             */
/*   Updated: 2022/01/18 18:37:53 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include "../include/minishell.h"

void	attributes(t_shell *shell)
{
	if (tcgetattr(0, &shell->old) == -1) 
		status_error(strerror(errno), errno);
	if (tcgetattr(0, &shell->changed) == -1)
		status_error(strerror(errno), errno);
	if (tcgetattr(0, &shell->child) == -1)
		status_error(strerror(errno), errno);
	shell->changed.c_lflag = shell->changed.c_lflag &  ~ICANON & ECHO; // ~ICANON | ECHO;
	shell->changed.c_cc[VQUIT] = 0;
	shell->child.c_lflag = shell->child.c_lflag & ECHO;
	if (tcsetattr(0,TCSANOW, &shell->changed) == -1)
		status_error(strerror(errno), errno);
}
