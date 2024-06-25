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
    min_margem = 10
    max_margem = 50
    margem_de_segurança = random.randint(min_margem, max_margem)

    # Calculo de time_to_die

    # if time_to_eat + time_to_sleep < time_to_eat * (2 + number_of_philosophers % 2):
    #     time_to_die = time_to_eat * (2 + number_of_philosophers % 2) + margem_de_segurança
    # else:
    #     time_to_die = time_to_eat + time_to_sleep + margem_de_segurança

    if number_of_philosophers % 2 == 0:                             # Se o número de filósofos for par
        if time_to_eat + time_to_sleep < time_to_eat * 2:
            time_to_die = time_to_eat * 2 + margem_de_segurança
        else:
            time_to_die = time_to_eat + time_to_sleep + margem_de_segurança

    else:                                                           # Se o número de filósofos for ímpar
        if time_to_eat + time_to_sleep < time_to_eat * 3:
            time_to_die = time_to_eat * 3 + margem_de_segurança
        else:
            time_to_die = time_to_eat + time_to_sleep + margem_de_segurança

    return time_to_die, time_to_eat, time_to_sleep


if __name__ == "__main__":

    # Gerando valores aleatórios para o número de filósofos e tempos
    number_of_philosophers = random.randint(2, 5)
    times_to_eat = random.randint(1, 10)
    time_to_die, time_to_eat, time_to_sleep = generate_times(number_of_philosophers)

    # Imprimindo valores
    if sys.stdout.isatty():
        print(f"number_of_philosophers: {number_of_philosophers} time_to_die: {time_to_die}, time_to_eat: {time_to_eat}, time_to_sleep: {time_to_sleep}, times_to_eat: {times_to_eat}")
    else:
        print(f"{number_of_philosophers} {time_to_die} {time_to_eat} {time_to_sleep} {times_to_eat}", file=sys.stderr)
        print(f"{number_of_philosophers} {time_to_die} {time_to_eat} {time_to_sleep} {times_to_eat}")
