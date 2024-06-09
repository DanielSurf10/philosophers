all:
	@make -C "directory philo"
	@cp "directory philo/philo" .

fclean:
	@make -C "directory philo" fclean

re: fclean all
