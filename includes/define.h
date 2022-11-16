/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:14:28 by mcorso            #+#    #+#             */
/*   Updated: 2022/11/16 11:12:49 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

/*		ERROR MANAGEMENT		*/
# define SUCCESS 0
# define ERROR -1
# define NOT_SET -2		// fd

/*		FILE MANAGEMENT			*/
//	O_FLAGS
# define TMP_FILE_FLAGS O_RDWR | O_TRUNC | O_CREAT
# define APPND_FILE_FLAGS O_WRONLY | O_APPEND | O_CREAT
# define TRUNC_FILE_FLAGS O_WRONLY | O_TRUNC | O_CREAT

//	MODE (CREATION RIGHTS)
# define TMP_FILE_ACCESS S_IREAD | S_IWRITE
# define CREAT_FILE_ACCESS S_IRUSR | S_IWUSR | S_IXUSR


#endif