all:
	@make -C "philo"
	@cp "philo/philo" philo_

fclean:
	@make -C "philo" fclean

val:
	@make -C "philo" val

hell:
	@make -C "philo" hell

re: fclean all
