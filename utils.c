#include "philo.h"

int ft_atoi(char *str)
{
	int sign;
	ssize_t res;

	res = 0;
	sign = 1;
	if (!str || str[0] == '\0')
		return -1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (check_num(str) == -1)
		return -1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		if (res > INT_MAX || res < 0)
			return -1;
		str++;
	}
	return (sign * res);
}
