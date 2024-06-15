/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste_fila_mutex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 11:10:14 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/15 11:36:59 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

int valor;
pthread_mutex_t	mutex;

void	wait(int num)
{
	if (num == 1)
		usleep(1000);
	else if (num == 2)
		usleep(2000);
}

void *teste1(void *arg)
{
	int	numero = *(int*)arg;

	wait(numero);
	pthread_mutex_lock(&mutex);
	valor = 1;
	pthread_mutex_unlock(&mutex);
}

void *teste2(void *arg)
{
	int	numero = *(int*)arg;

	wait(numero);
	pthread_mutex_lock(&mutex);
	valor = 2;
	pthread_mutex_unlock(&mutex);
}

void *teste3(void *arg)
{
	int	numero = *(int*)arg;

	wait(numero);
	pthread_mutex_lock(&mutex);
	valor = 3;
	pthread_mutex_unlock(&mutex);
}

int main() {
	int			args[3] = {1, 2, 0};
	pthread_t	thread[3];

	valor = 0;
	pthread_mutex_init(&mutex, NULL);

	pthread_create(&thread[0], NULL, teste1, &args[0]);
	// usleep(500);
	pthread_create(&thread[1], NULL, teste2, &args[1]);
	// usleep(500);
	pthread_create(&thread[2], NULL, teste3, &args[2]);

	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);
	pthread_join(thread[2], NULL);

	printf("%d\n", valor);

	return (0);
}
