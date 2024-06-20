import random
import sys


def generate_times(number_of_philosophers):
    # Intervalos de tempo em milissegundos
    min_time_to_eat = 100
    max_time_to_eat = 300
    min_time_to_sleep = 100
    max_time_to_sleep = 300

    # Escolha aleatória de tempos para comer e dormir
    time_to_eat = random.randint(min_time_to_eat, max_time_to_eat)
    time_to_sleep = random.randint(min_time_to_sleep, max_time_to_sleep)

    # Margem de segurança
    min_margem = 50
    max_margem = 50
    margem_de_segurança = random.randint(min_margem, max_margem)

    # Calculo de time_to_die
    if number_of_philosophers % 2 == 0:
        time_to_die = time_to_eat + time_to_sleep + margem_de_segurança
    else:
        time_to_die = int(time_to_eat * 2.5) + time_to_sleep +  margem_de_segurança

    return time_to_die, time_to_eat, time_to_sleep


# Exemplo de uso
number_of_philosophers = random.randint(2, 5)
time_to_die, time_to_eat, time_to_sleep = generate_times(number_of_philosophers)
if sys.stdout.isatty():
    print(f"number_of_philosophers: {number_of_philosophers} time_to_die: {time_to_die}, time_to_eat: {time_to_eat}, time_to_sleep: {time_to_sleep}")
else:
    print(f"{number_of_philosophers} {time_to_die} {time_to_eat} {time_to_sleep} 7")
