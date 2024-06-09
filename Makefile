all:
	@make -C "directory philo"
	@cp "directory philo/philo" .

fclean:
	@make -C "directory philo" fclean

val:
	@make -C "directory philo" val

hell:
	@make -C "directory philo" hell

re: fclean all
