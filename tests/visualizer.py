import pygame
import math

pygame.init()
screen = pygame.display.set_mode((800, 600))
pygame.display.set_caption('Jantarzinho metafisico')
clock = pygame.time.Clock()

philo_number = 5


# Funções de desenho
def draw_table():
    screen.fill((255, 255, 255))
    pygame.draw.circle(screen, (0, 0, 0), (400, 300), 200, 5)


def draw_philosopher(x, y, state):
    colors = {
        'thinking': (0, 0, 255),
        'eating': (0, 255, 0),
        'sleeping': (255, 0, 0)
    }
    color = colors.get(state, (0, 0, 0))
    pygame.draw.circle(screen, color, (x, y), 20)


def read_output():
    with open("test", "r") as arq:
        for line in arq:
            yield line.strip()


# Mapeamento de posições dos filósofos
positions = [
    (
        400 + 150 * math.cos(i * 2 * 3.14 / philo_number),
        300 + 150 * math.sin(i * 2 * 3.14 / philo_number)
    )
    for i in range(philo_number)
]
states = ['thinking'] * philo_number  # Estados iniciais dos filósofos

lines = read_output()

# Renderização
draw_table()
for i, (x, y) in enumerate(positions):
    draw_philosopher(int(x), int(y), states[i])

pygame.display.flip()

# Loop principal
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Atualização dos estados com base na saída do programa externo
    # for line in read_output():
    #     parts = line.split()
    #     philosopher_id = int(parts[1]) - 1
    #     state = parts[-1]
    #     states[philosopher_id] = state

    try:
        while True:
            line = next(lines)
            if 'fork' not in line:
                break
    except StopIteration:
        break

    parts = line.split()
    philosopher_id = int(parts[1]) - 1
    state = parts[-1]
    states[philosopher_id] = state

    # Renderização
    draw_table()
    for i, (x, y) in enumerate(positions):
        draw_philosopher(int(x), int(y), states[i])
        font = pygame.font.Font(None, 20)
        text = font.render(states[i], True, (0, 0, 0))
        text_rect = text.get_rect(center=(x, y-30))
        screen.blit(text, text_rect)

    pygame.display.flip()
    clock.tick(1)

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

pygame.quit()
