#include"philo.h"

int main(int argc, char **argv)
{
	t_philo	*philo;
	t_table	table;
	pthread_mutex_t	*forks;

	philo = NULL;
	memset(&table, 0, sizeof(t_table));
	if (!parse(argc, argv))
		return (0);
	init_table(&table, argv);
	forks = init_forks(table.num_philos);
	philo = init_philos(&table, forks);
	start_simulation(&philo, &table);
}
